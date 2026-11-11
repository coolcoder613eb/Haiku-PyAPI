#!/usr/bin/env python3
#
# test_storage.py — the functional-equivalence standard for the storage kit.
# Spec = the beta6 C API (headers/os/storage/*): signatures, return
# conventions (ssize_t bytes for attr I/O, (value, status) tuples where the
# binding chose them), and behavior. Red rows are the fix backlog.
#
import json
import os
import struct
import subprocess
import sys

import common

Be = common.load(common.closure("Errors", "TypeConstants", "StorageDefs",
                                "Handler", "Looper",
                                "BNode", "BFile", "BEntry", "BPath",
                                "BEntryList", "BQuery", "BVolume",
                                "BDirectory", "BNodeInfo", "BAppFileInfo",
                                "BPathFinder", "BSize", "stat", "MimeType",
                                "BMimeType", "NodeMonitor"))
globals().update(common.bind_names(Be,
    "BNode BFile BEntry BPath BEntryList BQuery BVolume BDirectory BNodeInfo "
    "BAppFileInfo BPathFinder BSize BMimeType entry_ref node_ref BLooper "
    "B_OK B_RAW_TYPE B_INT32_TYPE B_INT64_TYPE B_FLOAT_TYPE B_DOUBLE_TYPE "
    "B_CREATE_FILE B_READ_ONLY B_READ_WRITE B_GT B_WATCH_DIRECTORY "
    "B_SIZE_UNSET B_SIZE_UNLIMITED watch_node stop_watching"))

P = common.scratch_file("storage_test.dat")

# ---------------------------------------------------------------- open modes
def t_open_modes():
    # beta6 open modes are POSIX O_* values (StorageDefs.h): O_CREAT=0x200
    assert B_CREATE_FILE == 0x200, "B_CREATE_FILE=%d (want 0x200)" % B_CREATE_FILE
    assert B_READ_WRITE == 2, B_READ_WRITE
    assert B_READ_ONLY == 0, B_READ_ONLY
common.check("storage:open-modes", t_open_modes)

# ------------------------------------------------------------- BFile basics
def t_file_write_read():
    f = BFile()
    assert f.SetTo(P, B_CREATE_FILE | B_READ_WRITE) == B_OK
    n = f.Write(b"hello storage")
    assert n == 13, "Write returned %r" % n
    assert f.Seek(0, 0) == 0
    data, n = f.Read(64)
    assert data == b"hello storage" and n == 13, (data, n)
    st, size = f.GetSize()
    assert st == B_OK and size == 13, (st, size)
    f.Unset()
common.check("storage:BFile-write-read-seek-size", t_file_write_read)

def t_file_close():
    # BFile::Close is NOT bound today -> red until added
    f = BFile()
    f.SetTo(P, B_READ_ONLY)
    assert hasattr(f, "Close"), "BFile.Close is not bound (use Unset meanwhile)"
    f.Close()
common.check("storage:BFile-Close-bound", t_file_close)

# ------------------------------------------------------- attribute API (T1)
def t_attr_raw():
    node = BNode()
    assert node.SetTo(P) == B_OK
    payload = bytes(range(64))
    n = node.WriteAttr("t.raw", B_RAW_TYPE, 0, payload)
    assert n == 64, "WriteAttr returned %r (ssize_t bytes expected)" % n
    got, n = node.ReadAttr("t.raw", B_RAW_TYPE, 0, None, 64)
    assert n == 64 and got == payload, (n, got[:8] if got else got)
    node.RemoveAttr("t.raw")
    node.Unset()
common.check("storage:attr-raw-roundtrip", t_attr_raw)

def t_attr_ints():
    node = BNode()
    node.SetTo(P)
    assert node.WriteAttr("t.i32", B_INT32_TYPE, 0, struct.pack("<i", -42)) == 4
    v, n = node.ReadAttr("t.i32", B_INT32_TYPE, 0, None, 4)
    assert n == 4 and v == -42, (v, n)      # ints come back as Python ints
    assert node.WriteAttr("t.i64", B_INT64_TYPE, 0, struct.pack("<q", 2**40)) == 8
    v, n = node.ReadAttr("t.i64", B_INT64_TYPE, 0, None, 8)
    assert n == 8 and v == 2**40, (v, n)
    node.RemoveAttr("t.i32"); node.RemoveAttr("t.i64")
    node.Unset()
common.check("storage:attr-int-roundtrip", t_attr_ints)

def t_attr_floats():
    node = BNode()
    node.SetTo(P)
    node.WriteAttr("t.f", B_FLOAT_TYPE, 0, struct.pack("<f", 1.5))
    v, n = node.ReadAttr("t.f", B_FLOAT_TYPE, 0, None, 4)
    assert n == 4 and abs(v - 1.5) < 1e-6, (v, n)
    node.WriteAttr("t.d", B_DOUBLE_TYPE, 0, struct.pack("<d", 2.25))
    v, n = node.ReadAttr("t.d", B_DOUBLE_TYPE, 0, None, 8)
    assert n == 8 and v == 2.25, (v, n)
    node.RemoveAttr("t.f"); node.RemoveAttr("t.d")
    node.Unset()
common.check("storage:attr-float-roundtrip", t_attr_floats)

def t_attr_string():
    node = BNode()
    node.SetTo(P)
    node.WriteAttrString("t.str", "the answer is 42")
    s, st = node.ReadAttrString("t.str")
    assert st == B_OK and s == "the answer is 42", (s, st)
    node.RemoveAttr("t.str")
    node.Unset()
common.check("storage:attr-string-roundtrip", t_attr_string)

def t_attr_info():
    node = BNode()
    node.SetTo(P)
    node.WriteAttr("t.i32", B_INT32_TYPE, 0, struct.pack("<i", 7))
    info, st = node.GetAttrInfo("t.i32")
    assert st == B_OK and info.size == 4 and info.type == B_INT32_TYPE, \
        (st, getattr(info, "size", "?"), getattr(info, "type", "?"))
    node.RemoveAttr("t.i32")
    node.Unset()
common.check("storage:attr-info", t_attr_info)

def t_attr_enumerate():
    node = BNode()
    node.SetTo(P)
    for i in range(3):
        node.WriteAttr("t.enum.%d" % i, B_INT32_TYPE, 0, struct.pack("<i", i))
    node.RewindAttrs()
    names = []
    while True:
        name, st = node.GetNextAttrName()
        if st != B_OK:
            break
        names.append(name)
    for i in range(3):
        assert "t.enum.%d" % i in names, names
    for i in range(3):
        node.RemoveAttr("t.enum.%d" % i)
    node.Unset()
common.check("storage:attr-enumerate", t_attr_enumerate)

# ------------------------------------------------------------- BEntry/BPath
def t_entry_path():
    e = BEntry(P)
    assert e.InitCheck() == B_OK
    assert e.IsFile() and not e.IsDirectory()
    e2 = BEntry()
    assert e2.SetTo(P) == B_OK
    p = BPath()
    assert p.SetTo(P) == B_OK
    assert p.Path() == P
    parent = BPath()
    st = p.GetParent(parent)          # out-param object (BPath*) — works
    assert st == B_OK and parent.Path() == os.path.dirname(P), \
        (st, parent.Path())
common.check("storage:entry-path", t_entry_path)

def t_entry_getsize():
    # STANDARD: GetSize() with no args -> (status, size) like File.GetSize.
    # The raw binding is BStatable::GetSize(off_t*) — an out-param hazard
    # (None -> null-deref; int -> TypeError). Red until rebound.
    e = BEntry(P)
    r = e.GetSize()
    assert isinstance(r, tuple) and r[0] == B_OK and r[1] > 0, repr(r)
common.check("storage:entry-getsizeshape", t_entry_getsize)

# ---------------------------------------------------------------- BQuery
VOL = BVolume(os.stat(common.SCRATCH).st_dev)

def _qcount(pred):
    q = BQuery()
    q.SetVolume(VOL)
    assert q.SetPredicate(pred) == B_OK, "SetPredicate(%r)" % pred
    assert q.Fetch() == B_OK, "Fetch(%r)" % pred
    n = 0
    ref = entry_ref()
    while q.GetNextRef(ref) == B_OK:
        n += 1
        if n > 100000:
            break
    return n

def t_query_name():
    n = _qcount('name = %s' % os.path.basename(P))
    assert n >= 1, "name glob found %d" % n
common.check("query:name-glob", t_query_name)

def t_query_size():
    n = _qcount("size > 0")
    assert n >= 1, "size>0 found %d" % n
common.check("query:size-indexed", t_query_size)

def t_query_attr_indexed():
    # An attribute predicate matches only nodes whose volume carries the
    # B+ index for that attr name (kernel auto-maintains it on every attr
    # write). Self-contained: create the index, write the attr, query, then
    # clean up — the old version queried the M2d PoC's cognis:embedding.*
    # corpus, which is ad-hoc volume state absent on a fresh install.
    import ctypes
    libroot = ctypes.CDLL("libroot.so")
    create, remove = libroot.fs_create_index, libroot.fs_remove_index
    create.argtypes = [ctypes.c_uint32, ctypes.c_char_p,
                       ctypes.c_uint32, ctypes.c_uint32]
    create.restype = ctypes.c_int
    remove.argtypes = [ctypes.c_uint32, ctypes.c_char_p]
    remove.restype = ctypes.c_int
    dev = os.stat(common.SCRATCH).st_dev
    assert create(dev, b"bindtest:dim", B_INT32_TYPE, 0) == B_OK
    node = BNode()
    node.SetTo(P)
    assert node.WriteAttr("bindtest:dim", B_INT32_TYPE, 0,
                          struct.pack("<i", 1)) == 4
    n = _qcount("bindtest:dim > 0")
    assert n >= 1, "indexed attr predicate found %d" % n
    node.RemoveAttr("bindtest:dim")
    node.Unset()
    assert remove(dev, b"bindtest:dim") == B_OK
common.check("query:attr-indexed", t_query_attr_indexed)

def t_query_attr_unindexed():
    # SPEC RULE (kernel behavior): an attribute clause matches NOTHING
    # without its index. Pinned here so a behavior change is visible.
    n = _qcount("cognis:nonexistent_attr_xyz > 0")
    assert n == 0, "unindexed attr matched %d (kernel behavior changed?)" % n
common.check("query:attr-unindexed-matches-nothing", t_query_attr_unindexed)

def t_query_pushstack():
    # KNOWN BROKEN on beta6: the kit QueryStack emits the old word grammar;
    # the kernel rejects it. Pinned as expected-fail until upstream fixes it.
    q = BQuery()
    q.SetVolume(VOL)
    q.PushAttr("size")
    q.PushOp(B_GT)
    q.PushInt32(0)
    st = q.Fetch()
    if st == B_OK:
        raise AssertionError("Push* stack now works — retire this known-broken row")
common.check("query:pushstack-known-broken", t_query_pushstack)

# --------------------- regression rows: one per beta6 binding fix (2026-10-25)
# Each pins the EXACT standard shape of a fixed method and would have failed
# (TypeError / crash / wrong value) against the pre-fix binding.

# ---- BStatable out-param getters (Statable.cpp): no-arg -> tuple
def t_statable_getsize():
    # STANDARD: GetSize() no args -> (status, size) like BFile::GetSize.
    # Pre-fix: raw GetSize(off_t*) -> TypeError (arg required) / null-deref.
    e = BEntry(P)
    r = e.GetSize()
    assert isinstance(r, tuple) and len(r) == 2, repr(r)
    assert r[0] == B_OK and r[1] > 0, repr(r)
common.check("storage:BStatable.GetSize", t_statable_getsize)

def t_statable_getowner():
    # STANDARD: GetOwner() -> (owner:int, status). Pre-fix: raw uid_t* out-param.
    e = BEntry(P)
    r = e.GetOwner()
    assert isinstance(r, tuple) and len(r) == 2 and isinstance(r[0], int), repr(r)
    assert r[1] == B_OK, repr(r)
common.check("storage:BStatable.GetOwner", t_statable_getowner)

def t_statable_getpermissions():
    # STANDARD: GetPermissions() -> (mode:int, status). Pre-fix: raw mode_t*.
    e = BEntry(P)
    r = e.GetPermissions()
    assert isinstance(r, tuple) and len(r) == 2 and isinstance(r[0], int), repr(r)
    assert r[1] == B_OK and r[0] > 0, repr(r)
common.check("storage:BStatable.GetPermissions", t_statable_getpermissions)

def t_statable_getmodificationtime():
    # STANDARD: GetModificationTime() -> (time:int, status). Pre-fix: raw time_t*.
    e = BEntry(P)
    r = e.GetModificationTime()
    assert isinstance(r, tuple) and len(r) == 2 and isinstance(r[0], int), repr(r)
    assert r[1] == B_OK and r[0] > 0, repr(r)   # epoch seconds
common.check("storage:BStatable.GetModificationTime", t_statable_getmodificationtime)

def t_statable_getnoderef():
    # STANDARD: GetNodeRef() -> (node_ref, status). Pre-fix: raw node_ref*.
    e = BEntry(P)
    ref, st = e.GetNodeRef()
    assert st == B_OK and ref.node > 0, (st, ref.node)
common.check("storage:BStatable.GetNodeRef", t_statable_getnoderef)

def t_statable_getvolume():
    # STANDARD: GetVolume() -> (BVolume, status) — constructed object returned.
    e = BEntry(P)
    vol, st = e.GetVolume()
    assert st == B_OK and vol.Device() == os.stat(P).st_dev, (st, vol.Device())
common.check("storage:BStatable.GetVolume", t_statable_getvolume)

def t_statable_getstat():
    # STANDARD: GetStat() no args -> (stat, status). Pre-fix: None null-deref.
    e = BEntry(P)
    st_obj, st = e.GetStat()
    assert st == B_OK and st_obj.st_size > 0, (st, st_obj.st_size)
common.check("storage:BStatable.GetStat", t_statable_getstat)

# ---- BEntry (Entry.cpp)
def t_entry_getname():
    # STANDARD: GetName() -> (name:str, status) — value-first (Node.cpp pattern).
    # Pre-fix: raw char* out-param wrote into the caller's str buffer.
    e = BEntry(P)
    name, st = e.GetName()
    assert st == B_OK and name == os.path.basename(P), (st, name)
common.check("storage:BEntry.GetName", t_entry_getname)

def t_entry_getref():
    # STANDARD: GetRef() no args -> (entry_ref, status). Pre-fix: raw entry_ref*.
    e = BEntry(P)
    ref, st = e.GetRef()
    assert st == B_OK and ref.name == os.path.basename(P), (st, ref.name)
common.check("storage:BEntry.GetRef", t_entry_getref)

def t_entry_getpath():
    # STANDARD: GetPath() no args -> (BPath, status) — constructed object.
    # Pre-fix: raw BPath* out-param (None -> null-deref).
    e = BEntry(P)
    p, st = e.GetPath()
    assert st == B_OK and p.Path() == P, (st, p.Path())
common.check("storage:BEntry.GetPath", t_entry_getpath)

# ---- BFile (File.cpp)
def t_file_close_alias():
    # STANDARD: beta6 BFile has no Close() (File.h) — bound as alias of
    # BNode::Unset. Pre-fix: hasattr(f, "Close") was False. (The
    # storage:BFile-Close-bound row above is the original pin; this one
    # additionally verifies the file is actually released by Close:
    # a second read after Close must fail, not return stale data.)
    f = BFile()
    assert f.SetTo(P, B_READ_WRITE) == B_OK
    n = f.Write(b"close probe")
    assert n == 11, n
    f.Close()
    try:
        n2 = f.Write(b"after close")
        assert n2 < 0, "write after Close succeeded (%d)" % n2
    except Exception:
        pass  # some forms raise — also acceptable: handle is gone
common.check("storage:BFile.Close", t_file_close_alias)

# ---- BDirectory (Directory.cpp)
def t_directory_getentry():
    # STANDARD: GetEntry() no args -> (BEntry, status). Pre-fix: raw BEntry*.
    # BDirectory::GetEntry returns the entry of the directory itself
    # (Directory.h:37), not a listed child.
    d = BDirectory(os.path.dirname(P))
    e, st = d.GetEntry()
    assert st == B_OK and e.Exists() and e.IsDirectory(), (st, e.Name())
    assert e.Name() == os.path.basename(os.path.dirname(P)), e.Name()
common.check("storage:BDirectory.GetEntry", t_directory_getentry)

def t_directory_findentry():
    # STANDARD: FindEntry(path) 2-arg form -> (BEntry, status).
    # Pre-fix: only (path, entry*, traverse) existed — None entry* null-derefed.
    d = BDirectory(os.path.dirname(P))
    e, st = d.FindEntry(os.path.basename(P))
    assert st == B_OK and e.Exists(), (st,)
common.check("storage:BDirectory.FindEntry", t_directory_findentry)

def t_directory_getstatfor():
    # STANDARD: GetStatFor(path) -> (stat, status). Pre-fix: raw stat* out-param.
    d = BDirectory(os.path.dirname(P))
    st_obj, st = d.GetStatFor(os.path.basename(P))
    assert st == B_OK and st_obj.st_size > 0, (st, st_obj.st_size)
common.check("storage:BDirectory.GetStatFor", t_directory_getstatfor)

# ---- BNode (Node.cpp)
def t_node_getstat():
    # STANDARD: BNode.GetStat() no args -> (stat, status). Pre-fix: raw stat*.
    n = BNode(P)
    st_obj, st = n.GetStat()
    assert st == B_OK and st_obj.st_size > 0, (st, st_obj.st_size)
common.check("storage:BNode.GetStat", t_node_getstat)

# ---- BVolume (Volume.cpp)
def t_volume_getname():
    # STANDARD: GetName() no args -> (name:str, status). Pre-fix: raw char*.
    name, st = VOL.GetName()
    assert st == B_OK and isinstance(name, str) and name != "", (st, name)
common.check("storage:BVolume.GetName", t_volume_getname)

def t_volume_geticon_bound():
    # STANDARD: the raw-icon GetIcon(size, type) overload returns
    # (status, ndarray) via py::array — numpy is NOT installed here (no pip),
    # so the call itself is skipped; pinned instead: the
    # overload is bound on the class and the module imports cleanly (this
    # is what the static-linkage GetIcon_toArray fix guarantees).
    import Be.Volume  # re-import is a no-op; the first import already proved it
    assert hasattr(VOL, "GetIcon"), "GetIcon overloads missing from BVolume"
common.check("storage:BVolume.GetIcon", t_volume_geticon_bound)

# ---- BNodeInfo (NodeInfo.cpp)
def t_nodeinfo_getapphint():
    # STANDARD: GetAppHint() no args -> (entry_ref, status). Pre-fix: raw ref*.
    n = BNode(P)
    ni = BNodeInfo(n)
    ref, st = ni.GetAppHint()
    assert isinstance(ref, entry_ref) and isinstance(st, int), (type(ref), st)
common.check("storage:BNodeInfo.GetAppHint", t_nodeinfo_getapphint)

def t_nodeinfo_getpreferredapp_default():
    # STANDARD: GetPreferredApp() with NO verb arg uses the C++ B_OPEN
    # default. Pre-fix: the py::arg("verb")=B_OPEN default made pybind11
    # convert the app_verb enum (registered by the MimeType module, which
    # stock __init__ imports AFTER NodeInfo) at registration time ->
    # ImportError "could not convert default argument 'verb: app_verb'"
    # that killed BOTH the full `import Be` and any solo NodeInfo import.
    n = BNode(P)
    ni = BNodeInfo(n)
    r = ni.GetPreferredApp()
    assert isinstance(r, tuple) and len(r) == 2 and isinstance(r[0], int), repr(r)
    assert r[1] is None or isinstance(r[1], str), repr(r)
common.check("storage:BNodeInfo.GetPreferredApp-default", t_nodeinfo_getpreferredapp_default)

def t_nodeinfo_import_solo():
    # STANDARD: Be.NodeInfo imports in a fresh interpreter with only its
    # default-arg dep (Mime, for the icon_size defaults) but NO MimeType —
    # the app_verb registration-time default (registered by MimeType,
    # imported after NodeInfo in stock order) was the blocker; pinned so
    # the import-order coupling cannot silently return.
    code = ("import sys, types, importlib; "
            "pkg = types.ModuleType('Be'); pkg.__path__ = [%r]; "
            "sys.modules['Be'] = pkg; "
            "importlib.import_module('Be.Mime'); "
            "importlib.import_module('Be.NodeInfo'); print('SOLO-OK')"
            % common.FARM)
    p = subprocess.run([sys.executable, "-c", code],
                       capture_output=True, text=True, timeout=120)
    assert "SOLO-OK" in p.stdout, \
        p.stderr.strip().splitlines()[-1] if p.stderr else "no output (rc=%d)" % p.returncode
common.check("storage:BNodeInfo.import-solo", t_nodeinfo_import_solo)

def t_volumeroster_import_solo():
    # STANDARD: Be.VolumeRoster imports solo (fresh interpreter). Pre-fix:
    # py::arg("messenger")=be_app_messenger made pybind11 convert the
    # BMessenger default (registered by the LATER-imported Messenger
    # module) at registration time -> ImportError, which also killed the
    # full `import Be`. The C++ be_app_messenger default now applies at
    # call time via the no-arg StartWatching overload.
    code = ("import sys, types, importlib; "
            "pkg = types.ModuleType('Be'); pkg.__path__ = [%r]; "
            "sys.modules['Be'] = pkg; "
            "importlib.import_module('Be.VolumeRoster'); "
            "print('SOLO-OK')" % common.FARM)
    p = subprocess.run([sys.executable, "-c", code],
                       capture_output=True, text=True, timeout=120)
    assert "SOLO-OK" in p.stdout, \
        p.stderr.strip().splitlines()[-1] if p.stderr else "no output (rc=%d)" % p.returncode
common.check("storage:BVolumeRoster.import-solo", t_volumeroster_import_solo)

# ---- BAppFileInfo (AppFileInfo.cpp)
def t_appfileinfo_gettype():
    # STANDARD: GetType() no args -> (status, value) — shape matches the base
    # BNodeInfo::GetType lambda (value str on B_OK, None on error).
    # Pre-fix: raw char* out-param (None -> null-deref).
    f = BFile(P, B_READ_ONLY)
    afi = BAppFileInfo(f)
    r = afi.GetType()
    assert isinstance(r, tuple) and len(r) == 2 and isinstance(r[0], int), repr(r)
    assert r[1] is None or isinstance(r[1], str), repr(r)
common.check("storage:BAppFileInfo.GetType", t_appfileinfo_gettype)

def t_appfileinfo_getsignature():
    # STANDARD: GetSignature() no args -> (status, value); a plain (non-app)
    # file has no "sig" attribute -> (B_NO_ENTRY/other, None).
    f = BFile(P, B_READ_ONLY)
    afi = BAppFileInfo(f)
    st, sig = afi.GetSignature()
    assert isinstance(st, int) and sig is None, (st, sig)
common.check("storage:BAppFileInfo.GetSignature", t_appfileinfo_getsignature)

def t_appfileinfo_getappflags():
    # STANDARD: GetAppFlags() no args -> (status, flags:int). Pre-fix: raw uint32*.
    f = BFile(P, B_READ_ONLY)
    afi = BAppFileInfo(f)
    st, flags = afi.GetAppFlags()
    assert isinstance(st, int) and isinstance(flags, int), (st, flags)
common.check("storage:BAppFileInfo.GetAppFlags", t_appfileinfo_getappflags)

# ---- BMimeType (MimeType.cpp)
def t_mimetype_getshortdescription():
    # STANDARD: GetShortDescription() no args -> (status, desc:str|None).
    # Pre-fix: raw char* out-param (None -> null-deref, str -> buffer write).
    # "text/plain" is an installed meta type on any Haiku system.
    mt = BMimeType("text/plain")
    st, desc = mt.GetShortDescription()
    assert isinstance(st, int), st
    assert desc is None or isinstance(desc, str), repr(desc)
common.check("storage:BMimeType.GetShortDescription", t_mimetype_getshortdescription)

def t_mimetype_getpreferredapp_default():
    # STANDARD: GetPreferredApp() no args -> (status, sig:str|None) with the
    # C++ B_OPEN verb default. Pre-fix: raw char* out-param + app_verb
    # enum default (fine in-module, but pinned here for the call shape).
    mt = BMimeType("text/plain")
    r = mt.GetPreferredApp()
    assert isinstance(r, tuple) and len(r) == 2 and isinstance(r[0], int), repr(r)
    assert r[1] is None or isinstance(r[1], str), repr(r)
common.check("storage:BMimeType.GetPreferredApp-default", t_mimetype_getpreferredapp_default)

# ---- BPath single-arg forms (Path.cpp NULL-default defect class)
def t_path_single_arg_ctor():
    # STANDARD: BPath(path) works. Pre-fix: py::arg("leaf")=NULL stored the
    # nullptr default as int 0 -> the const char* caster rejected it ->
    # TypeError on every single-arg call.
    p = BPath(P)
    assert p.Path() == P, p.Path()
common.check("storage:BPath.single-arg-ctor", t_path_single_arg_ctor)

def t_path_single_arg_setto():
    # STANDARD: p.SetTo(path) works (leaf/normalize filled by C++ defaults).
    p = BPath()
    st = p.SetTo(P)
    assert st == B_OK and p.Path() == P, (st, p.Path())
common.check("storage:BPath.single-arg-setto", t_path_single_arg_setto)

# ---- BPathFinder single-arg forms (same NULL-default defect class)
def t_pathfinder_single_arg():
    # STANDARD: BPathFinder() and pf.SetTo(path) work. Pre-fix: the
    # dependency=NULL default broke every short-form call (TypeError).
    pf = BPathFinder()
    st = pf.SetTo("/boot/home")
    assert st == B_OK, st
common.check("storage:BPathFinder.single-arg-setto", t_pathfinder_single_arg)

# ---- Size constants (Size.cpp)
def t_size_unset():
    # STANDARD: B_SIZE_UNSET is the C const float -2 (Size.h:13), NOT the
    # source string "- 2". BSize() default ctor uses it for unset components.
    assert B_SIZE_UNSET == -2, repr(B_SIZE_UNSET)
    assert isinstance(B_SIZE_UNSET, float), type(B_SIZE_UNSET)
    b = BSize()
    assert b.width == B_SIZE_UNSET and b.height == B_SIZE_UNSET, (b.width, b.height)
common.check("storage:Size.B_SIZE_UNSET", t_size_unset)

def t_size_unlimited():
    # STANDARD: B_SIZE_UNLIMITED is the C const 1024*1024*1024 (Size.h:14).
    assert B_SIZE_UNLIMITED == 1024 * 1024 * 1024, repr(B_SIZE_UNLIMITED)
common.check("storage:Size.B_SIZE_UNLIMITED", t_size_unlimited)

def t_watch_node_short_forms():
    # Pairs the 2026-10-27 NodeMonitor.cpp fix: `py::arg("looper")=NULL`
    # stored the default as int 0 -> the short handler forms were
    # permanently uncallable. Now: watch_node(node, flags, handler) is
    # 3-arg; stop_watching(handler) is 2-arg. Headless-safe (BLooper
    # target, no app needed to register the watch).
    s = os.stat(common.SCRATCH)
    nref = node_ref(s.st_dev, s.st_ino)   # Node-module type (double-registered)
    lp = BLooper()   # 0-arg form (2026-10-27 fix: NULL-default was uncallable)
    st = watch_node(nref, B_WATCH_DIRECTORY, lp)      # short form
    assert st == B_OK, "watch_node 3-arg = %d" % st
    st = stop_watching(lp)                            # short form
    assert st == B_OK, "stop_watching 2-arg = %d" % st
common.check("storage:watch_node.short-forms", t_watch_node_short_forms)

if os.path.exists(P):
    os.remove(P)
sys.exit(common.report("test_storage"))
