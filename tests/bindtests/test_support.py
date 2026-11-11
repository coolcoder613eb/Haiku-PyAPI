#!/usr/bin/env python3
#
# test_support.py — runtime regression tests for the SUPPORT KIT bindings.
# Spec = the beta6 headers (os/support/*). Headless-safe: no app, no windows,
# BJob::Run is synchronous in beta6 (Job.cpp, no worker thread).
#
# Conventions pinned here (each fix pairs with 1-3 rows named
# support:<Class>.<method> that would have FAILED on the pre-fix bindings):
#   * Flattenable family: Flatten() -> (status, bytes), Unflatten(code, bytes)
#     -> status. The raw void* out-param forms are NOT bound.
#   * DataIO family: Read/Write take PEP 3118 buffers; a bytearray comes back
#     MUTATED; a read-only `bytes` object passed to a READ raises ValueError;
#     *Exactly/GetSize absorb C out-params into (status, n) tuples.
#   * Buffered streams: pass ownsStream=False when Python owns the wrapped
#     stream — the default (True) double-frees it at teardown (heap hang).
#   * beta6 error bases are INT_MIN-anchored, NOT the classic -1000/-10000
#     scheme (Errors.h:13-28).
#   * type_code 4cc values are ints: B_INT32_TYPE=0x4C4F4E47,
#     B_RAW_TYPE=0x52415754, B_STRING_TYPE=0x43535452 (TypeConstants.h).
#
# NOTE: BMemoryIO wraps the buffer pointer, it does NOT copy
# (beta6 DataIO.cpp) — keep the bytearray/bytes alive while the stream lives.
#
import common

mods = common.closure("BString", "BStringList", "BList", "BPoint",
                      "BAffineTransform", "BMemoryIO", "BMallocIO",
                      "BBufferedDataIO", "BBufferIO", "BUrl", "BJob",
                      "BDate", "Flattenable", "Message", "Path",
                      "parsedate", "UTF8", "TLS", "TypeConstants", "Errors")
Be = common.load(mods)
globals().update(common.bind_names(Be,
    "BString BStringList BList BPoint BAffineTransform BMemoryIO BMallocIO "
    "BBufferedDataIO BBufferIO BUrl BJob BJobStateListener BDate BFlattenable "
    "B_JOB_STATE_SUCCEEDED B_OK B_ERROR B_NO_MEMORY B_BAD_INDEX "
    "B_APP_ERROR_BASE B_STORAGE_ERROR_BASE B_RAW_TYPE B_INT32_TYPE B_STRING_TYPE"))


# ---------------------------------------------------------------- BString
# (runtime smoke — String.cpp unchanged by this round; rows pin the standard
#  shape for the next contributor)

def t_string_setto():
    s = BString()
    s.SetTo("hello")
    assert s.String() == "hello", s.String()
    assert s.Length() == 5, s.Length()
common.check("support:string-setto", t_string_setto)


def t_string_append_find():
    s = BString()
    s.SetTo("hello")
    s.Append(" world")
    assert s.Length() == 11, s.Length()
    assert s.FindFirst("world") == 6, s.FindFirst("world")
common.check("support:string-append-find", t_string_append_find)


def t_string_compare_byteat():
    assert BString("abc").Compare("abd") < 0
    s = BString()
    s.SetTo("abc")
    # pybind11 maps C char to a 1-char str (pin the standard shape)
    assert s.ByteAt(1) == "b", repr(s.ByteAt(1))
common.check("support:string-compare-byteat", t_string_compare_byteat)


# ------------------------------------------------------------- BStringList

def t_stringlist_sort():
    sl = BStringList()
    sl.Add(BString("bravo"))
    sl.Add(BString("alpha"))
    sl.Add(BString("charlie"))
    assert sl.CountStrings() == 3, sl.CountStrings()
    sl.Sort(False)                      # beta6 Sort(bool ignoreCase=false)
    assert sl.StringAt(0).String() == "alpha"
    assert sl.Remove(BString("bravo")) is True
    assert sl.CountStrings() == 2
    assert sl.Join(",").String() == "alpha,charlie"
common.check("support:stringlist-sort", t_stringlist_sort)


def t_stringlist_flatten():
    # FIX: raw Flatten(void*, ssize_t) out-param was bound -> None crashed /
    # wrote caller memory. Now: no-arg safe form returns (status, bytes).
    sl = BStringList()
    sl.Add(BString("alpha"))
    sl.Add(BString("charlie"))
    st, data = sl.Flatten()
    assert st == B_OK, st
    assert isinstance(data, (bytes, bytearray)) and len(data) > 0, repr(data)
    # the raw 2-arg form must be GONE
    try:
        sl.Flatten(None, 100)
        raise AssertionError("raw Flatten(buffer, size) is still bound")
    except TypeError:
        pass
common.check("support:BStringList.Flatten", t_stringlist_flatten)


def t_stringlist_unflatten():
    # FIX: Unflatten(code, const void*, ssize_t) -> bytes-in form.
    sl = BStringList()
    sl.Add(BString("alpha"))
    sl.Add(BString("charlie"))
    code = sl.TypeCode()
    assert code == 0x5354524C, hex(code)          # 'STRL'
    st, data = sl.Flatten()
    sl2 = BStringList()
    st2 = sl2.Unflatten(code, data)
    assert st2 == B_OK, st2
    assert sl2.CountStrings() == 2
    assert sl2.StringAt(0).String() == "alpha"
common.check("support:BStringList.Unflatten", t_stringlist_unflatten)


# ------------------------------------------------------------ BFlattenable

def t_flattenable_base_forms():
    # base-class safe forms must stay reachable even where a subclass binds
    # its own Flatten/Unflatten (pybase registration intact)
    sl = BStringList()
    sl.Add(BString("x"))
    st, data = BFlattenable.Flatten(sl)
    assert st == B_OK and isinstance(data, (bytes, bytearray)), (st, data)
    sl2 = BStringList()
    st2 = BFlattenable.Unflatten(sl2, sl.TypeCode(), data)
    assert st2 == B_OK, st2
    assert sl2.CountStrings() == 1 and sl2.StringAt(0).String() == "x"
common.check("support:BFlattenable.Flatten", t_flattenable_base_forms)


# ------------------------------------------------------------------- BList

def t_list_basics():
    # BList stores raw void*; from Python the pointer type is a capsule
    # (BMallocIO.Buffer() hands one over).
    src1 = BMallocIO()
    src1.Write(bytearray(b"item1"))
    src2 = BMallocIO()
    src2.Write(bytearray(b"item2"))
    src3 = BMallocIO()
    src3.Write(bytearray(b"item3"))
    c1, c2, c3 = src1.Buffer(), src2.Buffer(), src3.Buffer()
    lst = BList()
    assert lst.AddItem(c1) is True
    assert lst.AddItem(c2) is True
    assert lst.AddItem(c3) is True
    assert lst.CountItems() == 3, lst.CountItems()
    assert lst.ItemAt(1) is not None
    lst.RemoveItem(c2)
    assert lst.CountItems() == 2, lst.CountItems()
common.check("support:list-basics", t_list_basics)


# ------------------------------------------------------- DataIO family
# FIX: Read/Write/ReadAt/WriteAt/ReadExactly/WriteExactly/GetSize were bound
# with raw void*/off_t* params (unusable from Python); now buffer-protocol
# with (status, n) tuples for the C out-param variants.

def t_memoryio_read():
    ba = bytearray(b"0123456789")
    mem = BMemoryIO(ba, 10)
    out = bytearray(10)
    n = mem.Read(out)
    assert n == 10 and bytes(out) == b"0123456789", (n, bytes(out))
    # a read-only buffer passed to a READ is a user error -> ValueError
    try:
        mem.Read(b"0123456789")
        raise AssertionError("Read(bytes) should raise ValueError")
    except ValueError:
        pass
common.check("support:BMemoryIO.Read", t_memoryio_read)


def t_memoryio_writeat():
    # the bytearray must come back MUTATED (in-place, not a copy)
    ba = bytearray(b"abcde")
    mem = BMemoryIO(ba, 5)
    n = mem.WriteAt(1, bytearray(b"XYZ"), 3)
    assert n == 3, n
    assert bytes(ba) == b"aXYZe", bytes(ba)
    st, size = mem.GetSize()
    assert st == B_OK and size == 5, (st, size)
common.check("support:BMemoryIO.WriteAt", t_memoryio_writeat)


def t_positionio_getsize():
    # GetSize() -> (status, size); the old off_t* out-param form is gone
    ba = bytearray(b"0123456789")
    mem = BMemoryIO(ba, 10)
    st, size = mem.GetSize()
    assert st == B_OK and size == 10, (st, size)
    try:
        mem.GetSize(0)
        raise AssertionError("GetSize(off_t*) form should be gone")
    except TypeError:
        pass
common.check("support:BPositionIO.GetSize", t_positionio_getsize)


def t_dataio_readexactly():
    # ReadExactly() -> (status, bytesRead)
    ba = bytearray(b"0123456789")
    mem = BMemoryIO(ba, 10)
    st, n = mem.ReadExactly(bytearray(4))
    assert st == B_OK and n == 4, (st, n)
    mem.Seek(0, 0)                          # SEEK_SET (beta6: no B_SEEK_*)
    # asking for more than available -> partial read, not B_OK
    ba3 = bytearray(b"abc")
    mem3 = BMemoryIO(ba3, 3)
    st2, n2 = mem3.ReadExactly(bytearray(10))
    assert n2 == 3 and st2 != B_OK, (st2, n2)
common.check("support:BDataIO.ReadExactly", t_dataio_readexactly)


def t_mallocio_bufferbytes():
    m = BMallocIO()
    assert m.Write(bytearray(b"hello world")) == 11
    assert m.BufferBytes() == b"hello world"
    st, size = m.GetSize()
    assert st == B_OK and size == 11, (st, size)
    m.Seek(0, 0)
    out = bytearray(11)
    assert m.Read(out) == 11 and bytes(out) == b"hello world"
common.check("support:BMallocIO.BufferBytes", t_mallocio_bufferbytes)


def t_buffered_io():
    # ownsStream=False is REQUIRED here: the default (True) makes
    # BBufferedDataIO delete the wrapped stream in its destructor while
    # Python's `mem` holder deletes the same C++ object -> double-free
    # corrupts the heap and a later check hangs. Pins both the buffer
    # mutation and the ownership contract.
    ba = bytearray(b"hello world")
    mem = BMemoryIO(ba, 11)
    b = BBufferedDataIO(mem, 65536, False)
    out = bytearray(11)
    n = b.Read(out)
    assert n == 11 and bytes(out) == b"hello world", (n, bytes(out))
common.check("support:buffered-io", t_buffered_io)


def t_bufferio():
    # ownsStream=False for the same double-free reason as above.
    ba = bytearray(b"hello world")
    mem = BMemoryIO(ba, 11)
    b = BBufferIO(mem, 4, False)
    out = bytearray(11)
    n = b.ReadAt(0, out)
    assert n == 11 and bytes(out) == b"hello world", (n, bytes(out))
    assert b.Flush() == B_OK
common.check("support:bufferio", t_bufferio)


# --------------------------------------------------------------------- Url
# FIX: __eq__/__ne__ compared against a throwaway default BUrl and returned a
# (bool, BUrl) tuple — every comparison was truthy. Now real 2-arg bools.

def t_url_eq():
    u1 = BUrl("file:///boot/home")
    u2 = BUrl("file:///boot/home")
    u3 = BUrl("http://example.com/x")
    assert (u1 == u2) is True, repr(u1 == u2)
    assert (u1 == u3) is False, repr(u1 == u3)
    assert (u1 != u3) is True
common.check("support:BUrl.__eq__", t_url_eq)


def t_url_fields():
    u = BUrl("file:///boot/home")
    assert u.IsValid(), "url invalid"
    assert u.Protocol().String() == "file"
    assert u.Path().String() == "/boot/home"
common.check("support:url-fields", t_url_fields)


# -------------------------------------------------------- BAffineTransform
# (runtime smoke — AffineTransform.cpp unchanged by this round)

def t_transform():
    t = BAffineTransform()
    t.TranslateBy(1.0, 2.0)
    p = t.Apply(BPoint(3.0, 4.0))
    assert abs(p.x - 4.0) < 1e-6 and abs(p.y - 6.0) < 1e-6, (p.x, p.y)
common.check("support:transform", t_transform)


# ---------------------------------------------------------------- parsedate

def t_parsedate_parse():
    # 2021-01-01 00:00 UTC = 1609459200; local tz keeps it inside +-2 days
    t = Be.parsedate("1 Jan 2021", 1600000000)
    assert 1609000000 < t < 1610000000, t
common.check("support:parsedate.parse", t_parsedate_parse)


def t_parsedate_etc():
    # FIX: raw int* _storedFlags out-param -> (time, flags) tuple form.
    t, flags = Be.parsedate_etc("1 Jan 2021", 1600000000)
    assert 1609000000 < t < 1610000000, t
    assert isinstance(flags, int), type(flags)
    assert not (flags & Be.PARSEDATE_INVALID_DATE), flags
common.check("support:parsedate.parsedate_etc", t_parsedate_etc)


def t_parsedate_constants():
    # beta6: parsedate.h:13-17
    assert Be.PARSEDATE_RELATIVE_TIME == 0x0001
    assert Be.PARSEDATE_MINUTE_RELATIVE_TIME == 0x0002
    assert Be.PARSEDATE_INVALID_DATE == 0x0100
common.check("support:parsedate.constants", t_parsedate_constants)


# --------------------------------------------------------------------- UTF8
# FIX: convert_to/from_utf8 were bound with raw int32*/char* out-params
# (uncallable from Python) + a hardcoded substitute; now Pythonic forms
# return (status, dest_bytes, state), substitute defaults to B_SUBSTITUTE.

def t_utf8_from():
    err, out, state = Be.convert_from_utf8(
        Be.B_ISO1_CONVERSION, "café".encode("utf-8"))
    assert err == B_OK and out == b"caf\xe9", (err, out)
common.check("support:UTF8.convert_from_utf8", t_utf8_from)


def t_utf8_to():
    err, out, state = Be.convert_to_utf8(Be.B_ISO1_CONVERSION, b"caf\xe9")
    assert err == B_OK and out == "café".encode("utf-8"), (err, out)
common.check("support:UTF8.convert_to_utf8", t_utf8_to)


# ---------------------------------------------------------------------- Job
# FIX: BJobStateListener had no trampoline/py::init — Python listeners were
# unconstructible and their overrides silently dead. BJob.Run stays
# synchronous (beta6 Job.cpp: no worker thread) -> headless-safe.

def t_job_run():
    class MyJob(BJob):
        def __init__(self):
            super().__init__(BString("smoke"))
        def Execute(self):
            return B_OK
    j = MyJob()
    st = j.Run()
    assert st == B_OK, st
    assert j.State() == B_JOB_STATE_SUCCEEDED, j.State()
    assert j.Result() == B_OK
common.check("support:BJob.Run", t_job_run)


def t_job_listener():
    events = []
    class L(BJobStateListener):
        def __init__(self):
            super().__init__()
        def JobStarted(self, job):
            events.append("started")
        def JobSucceeded(self, job):
            events.append("succeeded")
    class MyJob(BJob):
        def __init__(self):
            super().__init__(BString("listener-test"))
        def Execute(self):
            return B_OK
    j = MyJob()
    # keep a Python reference: AddStateListener stores the RAW C++ listener
    # pointer (BJobStateListener*); a temporary would be freed by the GC and
    # BJob would call into a dangling trampoline.
    listener = L()
    assert j.AddStateListener(listener) == B_OK
    st = j.Run()
    assert st == B_OK, st
    assert "started" in events and "succeeded" in events, events
common.check("support:BJobStateListener.JobStarted", t_job_listener)


# ---------------------------------------------------------------------- TLS

def t_tls():
    # FIX: TLS_MAX_KEYS (TLS.h:21) was not bound.
    assert Be.TLS_MAX_KEYS == 64
    idx = Be.tls_allocate()
    assert isinstance(idx, int) and 0 <= idx < 64, idx
common.check("support:TLS.tls_allocate", t_tls)


# ------------------------------------------------- TypeConstants / Errors

def t_typeconstants():
    # beta6 type_code 4cc values are ints (TypeConstants.h:28/46/55)
    assert B_INT32_TYPE == 0x4C4F4E47, hex(B_INT32_TYPE)    # 'LONG'
    assert B_RAW_TYPE == 0x52415754, hex(B_RAW_TYPE)        # 'RAWT'
    assert B_STRING_TYPE == 0x43535452, hex(B_STRING_TYPE)  # 'CSTR'
common.check("support:TypeConstants.B_RAW_TYPE", t_typeconstants)


def t_errors():
    # beta6 error bases are INT_MIN-anchored (Errors.h:13-22), NOT the
    # classic -1000/-10000 scheme.
    assert B_OK == 0 and B_ERROR == -1
    assert B_NO_MEMORY == -2147483648, B_NO_MEMORY          # INT_MIN + 0
    assert B_BAD_INDEX == -2147483648 + 3, B_BAD_INDEX
    assert B_APP_ERROR_BASE == -2147483648 + 0x2000
    assert B_STORAGE_ERROR_BASE == -2147483648 + 0x6000
common.check("support:Errors.B_OK", t_errors)


# ---------------------------------------------------------------- DateTime
# FIX: BDate.GetDate(int32*, int32*, int32*) out-params -> (y, m, d) tuple.

def t_bdate_getdate():
    d = BDate(2026, 3, 15)
    y, mo, da = d.GetDate()
    assert (y, mo, da) == (2026, 3, 15), (y, mo, da)
common.check("support:BDate.GetDate", t_bdate_getdate)


raise SystemExit(common.report("test_support"))
