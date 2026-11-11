#!/usr/bin/env python3
# select.py — dependency-aware curated `Be` import-set builder.
#
# WHY: the CPython 3.14 TSS-key pool (~507 usable) limits a process to
# ~120 binding modules (each pybind11 v3 module costs ~4 keys). So services
# import a CURATED set — and that set must (a) include every cross-module
# base class + default-arg type its modules need, and (b) respect the stock
# import order. This tool computes the closure and emits the init lines.
#
# Deps are derived statically from the binding sources (two passes over
# py::class_/py::enum_), plus the empirically-observed default-arg deps
# (from the fullmap solo survey — see the DEFAULT_ARG_DEPS table below).
#
# Usage:
#   python3 select.py BFile BEntry BPath BVolumeRoster        # closure + order
#   python3 select.py BFile BEntry --emit                     # print init lines
#   python3 select.py --budget BFile BEntry ...               # also TSS-budget it
#
import os, re, subprocess, sys

# Configuration (env-overridable; defaults match the standard VM layout):
#   PYAPI_BINDINGS    bindings source tree for the static dep analysis
#                     (host: ~/src/haiku-pyapi-dev/bindings)
#   PYAPI_STOCK_INIT  the stock import-order file (defaults to $PYAPI_BINDINGS/__init__.py)
#   PYAPI_BUDGET      the budget.py used by --budget (skipped if absent)
BINDINGS = os.environ.get("PYAPI_BINDINGS", "/boot/home/Haiku-PyAPI/bindings")
STOCK_INIT = os.environ.get("PYAPI_STOCK_INIT", BINDINGS + "/__init__.py")
BUDGET = os.environ.get("PYAPI_BUDGET", "/boot/home/budget.py")

# module -> [(type, registering module), ...]  [fullmap 2026-10-19: these fail
# solo with "arg(): could not convert default argument '... (type not
# registered yet?)'; the type IS registered, just in another module;
# 2026-10-25: Bitmap/View additions from the bindtests baseline]
DEFAULT_ARG_DEPS = {
    "Screen":           [("screen_id", "GraphicsDefs")],
    "View":             [("BPoint", "Point"), ("bitmap_tiling", "InterfaceDefs"), ("pattern", "GraphicsDefs")],
    "Bitmap":           [("screen_id", "GraphicsDefs")],
    "Alert":            [("button_width", "InterfaceDefs")],
    "GridLayoutBuilder":[("BSpacing", "InterfaceDefs")],
    "GroupLayoutBuilder":[("orientation", "InterfaceDefs")],
    "ControlLook":      [("orientation", "InterfaceDefs")],
    "ChannelControl":   [("command_code", "AppDefs")],
    "SeparatorView":    [("BAlignment", "Alignment")],
    "GridLayout":       [("BSpace", "InterfaceDefs")],
    "Node":             [("attr_info", "fs_attr")],
    "VolumeRoster":     [("BMessenger", "Messenger")],
    "NodeInfo":         [("icon_size", "Mime"), ("app_verb", "MimeType")],
    "MailComponent":    [("mail_encoding", "mail_encoding")],
    "MailDaemon":       [("read_flags", "Email")],
    "MediaFormats":     [("media_type", "MediaDefs")],
    "MediaRecorder":    [("media_type", "MediaDefs")],
}

def modules():
    """module name -> cpp path, and stock import order (first occurrence)"""
    stock_order = []
    with open(STOCK_INIT) as f:
        for line in f:
            m = re.match(r"^from \.(\w+) import", line)
            if m and m.group(1) not in stock_order:
                stock_order.append(m.group(1))
    found = {}
    for root, _, files in os.walk(BINDINGS):
        for fn in files:
            if not fn.endswith(".cpp"):
                continue
            p = os.path.join(root, fn)
            try:
                src = open(p, errors="replace").read()
            except OSError:
                continue
            m = re.search(r"PYBIND11_MODULE\((\w+)", src)
            if m and m.group(1) not in found:
                found[m.group(1)] = p
    return found, stock_order

def analyze():
    found, stock_order = modules()
    reg_types = {}      # C++ type -> module that registers it
    bases = {}          # module -> [base types declared in py::class_<T, B,...>]
    for mod, path in found.items():
        src = open(path, errors="replace").read()
        for m in re.finditer(r"py::(?:class_|enum_)\s*<\s*([A-Za-z_]\w*)", src):
            reg_types.setdefault(m.group(1), mod)
        blist = []
        # match the py::class_<...>(m, ... registration header; greedy so
        # nested template args (std::unique_ptr<T, py::nodelete>) survive
        for m in re.finditer(r"py::class_<(.*)>\(m, ", src):
            args = [a.strip() for a in m.group(1).split(",")]
            if len(args) > 1:
                for a in args[1:]:
                    # bases are the non-holder args: skip Py* trampolines,
                    # std::*, py::smart_holder, unique_ptr/shared_ptr
                    t = a.split("<")[0].split("::")[-1].strip()
                    if t.startswith("Py") or a.startswith("std::") or \
                       "holder" in a or "unique_ptr" in a or "shared_ptr" in a:
                        continue
                    blist.append(a.split("<")[0].strip())
        bases[mod] = blist
    deps = {mod: set() for mod in found}
    for mod, blist in bases.items():
        for b in blist:
            reg = reg_types.get(b)
            if reg and reg != mod:
                deps[mod].add(reg)
    for mod, pairs in DEFAULT_ARG_DEPS.items():
        for t, reg in pairs:
            if mod in deps and reg in found:
                deps[mod].add(reg)
    order = {m: i for i, m in enumerate(stock_order)}
    return found, deps, order, stock_order, reg_types

def main():
    args = [a for a in sys.argv[1:]]
    emit = "--emit" in args; budget = "--budget" in args
    wanted = [a for a in args if not a.startswith("--")]
    if not wanted:
        print(__doc__); return 1

    found, deps, order, stock_order, cls_map = analyze()
    resolved = []
    unknown = []
    for w in wanted:
        if w in found:
            resolved.append(w)
        elif w in cls_map:          # a C++ class/enum name -> its module
            resolved.append(cls_map[w])
        else:
            unknown.append(w)
    if unknown:
        print("UNKNOWN (not a module or registered class): %s" % ", ".join(unknown))
        print("modules: %s" % ", ".join(m for m in stock_order if m in found))
        print("classes (sample): %s" % ", ".join(sorted(cls_map)[:60]))
        return 1
    wanted = resolved

    closure = set()
    stack = list(wanted)
    while stack:
        m = stack.pop()
        if m in closure:
            continue
        closure.add(m)
        stack.extend(deps.get(m, ()))

    ordered = sorted(closure, key=lambda m: order.get(m, 9999))
    missing_order = [m for m in ordered if m not in order]
    print("wanted %d module(s) -> closure %d (deps added: %s)"
          % (len(wanted), len(ordered),
             ", ".join(m for m in ordered if m not in wanted) or "none"))
    if missing_order:
        print("NOTE: not in stock init order (appended last): %s" % ", ".join(missing_order))
    print("ordered: %s" % " ".join(ordered))
    if emit:
        print("\n# init lines for a curated Be/__init__.py:")
        for m in ordered:
            print("from .%s import *" % m)
        print("from struct import unpack")
        print("def int32(bytestr): return unpack('i', bytestr)[0]")
    if budget:
        if not os.path.exists(BUDGET):
            print("(budget checker not found at %s — skipped; set PYAPI_BUDGET)"
                  % BUDGET)
            return
        r = subprocess.run([sys.executable, BUDGET] + ordered,
                           capture_output=True, text=True, timeout=300)
        print(r.stdout)
        if r.returncode != 0:
            print(r.stderr[-2000:])
    return 0

if __name__ == "__main__":
    sys.exit(main())
