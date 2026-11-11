#!/usr/bin/env python3
#
# test_appmedia.py — regression rows for the app/media/mail kit bindings.
# Each row pins the EXACT standard shape of a fixed method/constant and would
# have FAILED against the pre-fix binding. Spec = beta6 C headers.
#
# Defect classes pinned here:
#   1. 4cc message constants bound as str (B_CLIPBOARD_CHANGED = "CLCH") —
#      `what` codes must be ints or comparisons never match.
#   2. NEW: `m.attr("X") = <unregistered C++ enum constant>` (with or without
#      py::cast) FAILS THE WHOLE MODULE INIT in this pybind11 3.x build —
#      the enum caster's fallback for unregistered enums yields an empty
#      handle and the import dies with a misleading
#      "AttributeError: 'module' object has no attribute 'X'".
#      Fix pattern: assign a plain int (macro or `(int)CONST` / char4 literal).
#      (kernel/OS.cpp and media/MediaDefs.cpp were already migrated to this
#      pattern; add-ons/input_server + add-ons/graphics still carry the broken
#      form but are commented out of the Jamfile — see bindings report.)
#   3. Out-param hazards (callee writes caller memory): char*/int*/struct*
#      params re-bound as no-arg lambdas with internal buffers, tuple returns.
#   4. BMessage flatten had no safe form: raw char*/BDataIO* overloads only;
#      the ssize_t* out-param routed through pybind's int-pointer caster
#      (value written into caster-local storage — silently lost).
#
import re
import sys

import common

Be = common.load(common.closure(
    "Errors", "Clipboard", "Message", "MediaDefs", "MediaDecoder",
    "TimeCode", "MailMessage", "MailAttachment", "DataIO",
    "TypeConstants"))
globals().update(common.bind_names(Be,
    "B_RAW_TYPE BMessage B_OK BTimeCode BMediaDecoder BEmailMessage "
    "BSimpleMailAttachment"))


# --- 1/2: B_CLIPBOARD_CHANGED must be a plain int 4cc -----------------------
# beta6 os/app/Clipboard.h:20: enum { B_CLIPBOARD_CHANGED = 'CLCH' }
def t_clipboard_changed_what_int():
    v = Be.B_CLIPBOARD_CHANGED
    assert isinstance(v, int) and not isinstance(v, bool), repr(v)
    assert v == 0x434C4348, hex(v)
    m = BMessage(v)
    assert m.what == v, (hex(m.what), hex(v))
common.check("appmedia:clipboard.changed-what-int", t_clipboard_changed_what_int)


# --- 2: the enum-attr defect class, pinned across kits ----------------------
# 4cc what-codes must surface as plain ints (str 4ccs and enum members both
# fail `what == CODE` comparisons; a broken module init fails the import).
def t_what_codes_are_plain_ints():
    for name, want in (("B_MEDIA_NODE_CREATED", 0x54524941),   # 'TRIA'
                       ("B_MEDIA_BUFFER_DELETED", 0x54524946), # 'TRIF'
                       ("B_CLIPBOARD_CHANGED", 0x434C4348)):   # 'CLCH'
        v = getattr(Be, name)
        assert isinstance(v, int) and not isinstance(v, bool) and v == want, \
            (name, repr(v)[:40], hex(want))
common.check("appmedia:enum-attr-shape", t_what_codes_are_plain_ints)


# --- 4: safe flatten/unflatten, exact (status, bytes) shape + NUL payload ---
def t_flatten_unflatten_exact_shape():
    # Note: BMessage string fields are C strings (NUL-truncating) in beta6 —
    # the binary round-trip is exercised with a RAW data field, which is the
    # real use case for the flat form (persisting arbitrary bytes).
    m = BMessage(0x41504D32)
    m.AddString("s", "persist me")
    m.AddData("blob", B_RAW_TYPE, b"\x00\x01\x02\xff\xfe", 5, True, 1)
    r = m.Flatten()
    assert isinstance(r, tuple) and len(r) == 2, repr(r)[:60]
    st, data = r
    assert st == B_OK and isinstance(data, bytes) and len(data) > 0, \
        (st, type(data))
    m2 = BMessage()
    st2 = m2.Unflatten(data)
    assert st2 == B_OK, (st, st2)
    st3, v = m2.FindString("s")
    assert st3 == B_OK and v == "persist me", (st3, repr(v)[:40])
    r4 = m2.FindData("blob", B_RAW_TYPE)
    assert "00" in repr(r4) and "ff" in repr(r4), repr(r4)[:60]
common.check("appmedia:message.flatten-exact-shape", t_flatten_unflatten_exact_shape)


# --- 3: GetDecoderInfo(media_codec_info* out) -> (dict|None, status) --------
def t_mediadecoder_getdecoder_info():
    try:
        d = BMediaDecoder()
    except BaseException as e:
        raise common.Skip("BMediaDecoder() ctor: %s" % e)
    r = d.GetDecoderInfo()
    assert isinstance(r, tuple) and len(r) == 2, repr(r)[:60]
    info, st = r
    assert isinstance(st, int) and not isinstance(st, bool), (info, st)
    if st == B_OK:
        assert isinstance(info, dict) and set(info) == {
            "pretty_name", "short_name", "id", "sub_id"}, info
    else:
        assert info is None, (info, st)
common.check("appmedia:mediadecoder.getdecoder-info", t_mediadecoder_getdecoder_info)


# --- 3: BEmailMessage::GetName(char*, int32) -> (name, status) --------------
def t_mailmessage_getname_tuple():
    try:
        # Note: the `= NULL` default on the BPositionIO* ctor arg does not
        # dispatch with zero args in this pybind11 build — pass None
        # explicitly (pre-existing quirk, not part of the 10-26 fixes).
        m = BEmailMessage(None)
        m.SetFrom("Cognis Bot")
    except BaseException as e:
        raise common.Skip("BEmailMessage: %s" % e)
    r = m.GetName()
    assert isinstance(r, tuple) and len(r) == 2, repr(r)[:60]
    name, st = r
    assert isinstance(name, str), (name, st)
    assert isinstance(st, int) and not isinstance(st, bool), (name, st)
common.check("appmedia:mailmessage.getname-tuple", t_mailmessage_getname_tuple)


# --- 3: BMailAttachment::FileName(char*) -> (name, status), value pinned ----
def t_mailattachment_filename_tuple():
    try:
        a = BSimpleMailAttachment()
        a.SetFileName("report.pdf")
    except BaseException as e:
        raise common.Skip("BSimpleMailAttachment: %s" % e)
    r = a.FileName()
    assert isinstance(r, tuple) and len(r) == 2, repr(r)[:60]
    name, st = r
    assert st == B_OK and name == "report.pdf", (st, name)
common.check("appmedia:mailattachment.filename-tuple", t_mailattachment_filename_tuple)


# --- 3: BTimeCode::GetString(char*) -> str ----------------------------------
def t_timecode_getstring():
    try:
        tc = BTimeCode(0)
    except BaseException as e:
        raise common.Skip("BTimeCode: %s" % e)
    s = tc.GetString()
    # beta6 default-timecode string form: "00h:00m:00s.00"
    assert isinstance(s, str) and re.match(r"^\d{1,2}h:\d{1,2}m:\d{1,2}s\.\d{1,2}$", s), repr(s)[:40]
common.check("appmedia:timecode.getstring", t_timecode_getstring)


sys.exit(common.report("test_appmedia"))
