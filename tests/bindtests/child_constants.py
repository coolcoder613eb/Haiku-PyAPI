#!/usr/bin/env python3
# child_constants.py — the Python side of the constants sweep: dump each
# module's constant values/types at runtime, one process per module (or one
# "chunk" process for the whole union closure when the TSS pool fits it —
# see common.import_strategy; a failed import poisons the process, so the
# solo->closure retry always runs in a fresh subprocess).
#
# Usage:
#   python3 child_constants.py <module> '<json [names]>' <solo|closure>
#   python3 child_constants.py chunk '<json [modules]>' '<json {mod: [names]}>'
# Prints one JSON line:
#   per-module: [[name, typeclass, value], ...]
#   chunk:      {"loaded": [...], "failed_at": mod|null, "results": {mod: rows}}
# typeclass: T = the C "integral" class — int (bool included) and pybind
#            enum instances (int()-extractable), S = str, F = float,
#            C = anything else (a C++ composite on the emitter side —
#            matched by typeclass only), MISSING = not in the module.
import importlib
import json
import os
import sys
import types

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import common                # FARM lives here

FARM = common.FARM


def try_load(mods):
    pkg = types.ModuleType("Be")
    pkg.__path__ = [FARM]
    sys.modules["Be"] = pkg
    for m in mods:
        mod = importlib.import_module("Be." + m)
        for k, v in vars(mod).items():
            # dunders only: _VIEW_TOP_ & co. are real m.attr exports
            if k.startswith("__") and k.endswith("__"):
                continue
            setattr(pkg, k, v)
    return pkg


def dump_rows(Be, names):
    res = []
    for n in names:
        if not hasattr(Be, n):
            res.append([n, "MISSING", None])
        else:
            v = getattr(Be, n)
            if isinstance(v, str):
                res.append([n, "S", v])
            elif isinstance(v, int):       # bool is an int subclass: T, as in C
                res.append([n, "T", str(int(v))])
            elif isinstance(v, float):
                res.append([n, "F", repr(v)])
            else:
                try:
                    # pybind enum_ instances (e.g. BSpacing values auto-exported
                    # to module scope by .value()) are integral in C
                    res.append([n, "T", str(int(v))])
                except BaseException:
                    res.append([n, "C", repr(v)[:40]])
    return res


mode = sys.argv[1]
if mode == "chunk":
    # ONE process imports the WHOLE union closure. A failure at module X
    # poisons the process (partial C++ registrations), so report what was
    # loaded and stop; the parent falls back to per-module children for the
    # remainder.
    union = json.loads(sys.argv[2])
    names_by_mod = json.loads(sys.argv[3])
    results, failed_at = {}, None
    for m in union:
        try:
            try_load([m])     # the Be package persists across try_load calls
        except BaseException:
            failed_at = m
            break
        results[m] = dump_rows(sys.modules["Be"], names_by_mod[m])
    print("JSON " + json.dumps({"loaded": list(results),
                                "failed_at": failed_at,
                                "results": results}))
    sys.exit(0)

mod = sys.argv[1]
names = json.loads(sys.argv[2])
if mode == "solo":
    Be = try_load([mod])
else:  # closure
    import selectmods
    found, deps, order, stock, _ = selectmods.analyze()
    got, stack = set(), [mod]
    while stack:
        m = stack.pop()
        if m in got:
            continue
        got.add(m)
        stack.extend(deps.get(m, ()))
    Be = try_load(sorted(got, key=lambda m: order.get(m, 9999)))

print("JSON " + json.dumps(dump_rows(Be, names)))
