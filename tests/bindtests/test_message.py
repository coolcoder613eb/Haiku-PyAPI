#!/usr/bin/env python3
#
# test_message.py — pins the messaging core (the microservice foundation).
# Spec = beta6 <app/BMessage.h> + the established Pythonic conventions
# (Find* -> (status, value) tuples, ssize_t/bytes where C says so).
# Red rows = the fix backlog (Flatten/Unflatten have no safe form today).
#
import sys

import common

Be = common.load(["Errors", "AppDefs", "TypeConstants", "String", "Handler",
                  "Looper", "Message", "Messenger", "Roster", "Application"])
# note: B_FAILED was removed in beta6 — assert `st != B_OK` instead
globals().update(common.bind_names(Be,
    "BMessage B_OK B_RAW_TYPE B_INT32_TYPE B_INT64_TYPE B_STRING_TYPE"))


def t_what():
    m = BMessage(0x43474C31)              # 'cgl1' built C++-way (source order)
    assert m.what == 0x43474C31, hex(m.what)
    m.what = 0x44454647
    assert m.what == 0x44454647
common.check("message:what-4cc", t_what)


def t_add_find_string():
    m = BMessage(0x54455354)
    m.AddString("who", "cognis")
    st, v = m.FindString("who")
    assert st == B_OK and v == "cognis", (st, v)
    st = m.FindString("absent")
    assert st != B_OK, "FindString(absent) should not be B_OK: %r" % st
common.check("message:add-find-string", t_add_find_string)


def t_add_find_ints():
    m = BMessage(0x54455354)
    m.AddInt32("a", -123456)
    m.AddInt64("b", 2 ** 40)
    st, v = m.FindInt32("a")
    assert st == B_OK and v == -123456, (st, v)
    st, v = m.FindInt64("b")
    assert st == B_OK and v == 2 ** 40, (st, v)
common.check("message:add-find-ints", t_add_find_ints)


def t_add_find_double():
    m = BMessage(0x54455354)
    m.AddDouble("d", 3.75)
    r = m.FindDouble("d")
    st, v = (r[0], r[1]) if isinstance(r, tuple) else (B_OK, r)
    assert st == B_OK and v == 3.75, (st, v)
common.check("message:add-find-double", t_add_find_double)


def t_add_find_data():
    m = BMessage(0x54455354)
    m.AddData("blob", B_RAW_TYPE, b"\x01\x02\x03", 3, True, 1)
    r = m.FindData("blob", B_RAW_TYPE)
    flat = repr(r)
    assert "01" in flat and "02" in flat and "03" in flat, flat
common.check("message:add-find-data", t_add_find_data)


def t_flatten():
    # STANDARD: a safe flatten — Pythonic (bytes, size) or (status, bytes).
    # Today: only raw out-param overloads (char*/BDataIO*) — None crashes,
    # char* from a str would corrupt. Red until a bytes-based overload.
    m = BMessage(0x464C5431)
    m.AddString("s", "persist me")
    m.AddInt32("i", 777)
    r = m.Flatten()
    if isinstance(r, tuple) and len(r) >= 2:
        payload = r[1] if isinstance(r[1], (bytes, bytearray)) else r[0]
    else:
        payload = r
    assert isinstance(payload, (bytes, bytearray)) and len(payload) > 0, repr(r)[:80]
common.check("message:flatten-safe-form", t_flatten)


def t_unflatten_roundtrip():
    # STANDARD: Unflatten accepts bytes (arbitrary payload, incl. NULs).
    m = BMessage(0x464C5432)
    m.AddInt32("i", 777)
    m.AddString("s", "persist me")
    r = m.Flatten()
    payload = r[1] if isinstance(r, tuple) else r
    m2 = BMessage()
    st = m2.Unflatten(payload)
    st2, v = m2.FindInt32("i")
    assert st2 == B_OK and v == 777, (st, st2, v)
common.check("message:unflatten-roundtrip", t_unflatten_roundtrip)


def t_type_codes_are_4cc():
    # beta6 type_code migration (TypeConstants.h)
    assert B_INT32_TYPE == 0x4C4F4E47, hex(B_INT32_TYPE)   # 'LONG'
    assert B_INT64_TYPE == 0x4C4C4E47, hex(B_INT64_TYPE)   # 'LLNG'
    assert B_RAW_TYPE == 0x52415754, hex(B_RAW_TYPE)       # 'RAWT'
    assert B_STRING_TYPE == 0x43535452, hex(B_STRING_TYPE) # 'CSTR'
common.check("message:type-codes-4cc", t_type_codes_are_4cc)


sys.exit(common.report("test_message"))
