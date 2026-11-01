#!/usr/bin/env python3
#
# test_interface.py — interface-kit binding fixes (2026-10-25). One row per
# fix, paired with it (the pattern for future contributors):
#   * constant rows pin beta6 header values in the merged Be namespace;
#   * out-param rebind rows pin the NEW Pythonic shape via the pybind11
#     docstring (import-safe — no GUI instance needed) and, where a
#     headless-safe object exists (BScreen server proxy, BAffineTransform
#     pure data, BBitmap with B_BITMAP_NO_SERVER_LINK, BFont), functionally;
#   * "removed in beta6" rows pin the ABSENCE of classic-Haiku methods so a
#     future binding cannot re-add a non-existent API.
# Spec = the beta6 C headers (os/interface/*).
#
import sys

import common


Be = common.load(common.closure("Errors", "InterfaceDefs", "ControlLook",
                                "Font", "GraphicsDefs", "Bitmap", "View",
                                "Screen", "AffineTransform", "Alert",
                                "ListView", "TabView", "Deskbar", "Input",
                                "PrintJob", "MenuItem", "Dragger", "Slider",
                                "ScrollBar", "ChannelControl", "TextControl",
                                "TextView", "LayoutItem", "TwoDimensionalLayout",
                                "CardLayout", "Window", "Rect", "Point",
                                "Accelerant"))
globals().update(common.bind_names(Be,
    "BView BControl BFont BScreen BAffineTransform BBitmap BAlert BListView "
    "BTabView BDeskbar BInputDevice BPrintJob BMenuItem BDragger BSlider "
    "BScrollBar BChannelControl BTextControl BTextView BLayoutItem "
    "BTwoDimensionalLayout BCardLayout BRect BPoint B_OK B_LEFT_ARROW "
    "B_RIGHT_ARROW B_UP_ARROW B_DOWN_ARROW B_NO_TRUNCATION "
    "B_BITMAP_NO_SERVER_LINK"))


def doc(cls, name):
    return getattr(cls, name).__doc__ or ""


# ------------------------------------------------------------- constants
def t_const_no_truncation():
    # beta6 Font.h: B_NO_TRUNCATION = ~0U (truncation-mode enum, 0xFFFFFFFF).
    # Was bound as the Python STRING "~0U" before the fix.
    assert isinstance(B_NO_TRUNCATION, int), repr(B_NO_TRUNCATION)
    assert B_NO_TRUNCATION == 0xFFFFFFFF, hex(B_NO_TRUNCATION)
common.check("interface:Font.B_NO_TRUNCATION", t_const_no_truncation)


def t_const_cursor_ids():
    # beta6 InterfaceDefs.h:74-77 — the GLOBAL cursor ids must survive in
    # the merged namespace (ControlLook's nested enum 0..3 no longer shadows).
    assert B_LEFT_ARROW == 0x1c, hex(B_LEFT_ARROW)
    assert B_RIGHT_ARROW == 0x1d, hex(B_RIGHT_ARROW)
    assert B_UP_ARROW == 0x1e, hex(B_UP_ARROW)
    assert B_DOWN_ARROW == 0x1f, hex(B_DOWN_ARROW)
common.check("interface:InterfaceDefs.cursor_ids", t_const_cursor_ids)


# EXAMPLE of a paired row for a binding fix (not active in the suite): the
# ControlLook fix exposed the nested arrow values (BControlLook::B_*_ARROW =
# 0..3, ControlLook.h:67-70) as B_CONTROL_LOOK_* to disambiguate them from the
# global cursor ids (B_LEFT_ARROW = 0x1c, InterfaceDefs.h) — a binding-design
# choice, not a C-API constant, so the suite (which pins the C API) doesn't own
# it. When you fix a binding, add a paired row like this asserting the fixed
# API (it reads ABSENT against the base until the fix lands). The
# Be.BControlLookEnum.* asserts below are header spec (base-available); keep
# those, drop the B_CONTROL_LOOK_* lines, if you want that coverage.
# def t_const_control_look_nested():
#     assert B_CONTROL_LOOK_LEFT_ARROW == 0   # … RIGHT=1, UP=2, DOWN=3
#     assert Be.BControlLookEnum.B_LEFT_ARROW == 0
#     assert Be.BControlLookEnum.B_KNOB_LINES == 2
# common.check("interface:ControlLook.nested_arrows", t_const_control_look_nested)


# ------------------------------------------- removed-in-beta6 spec pins
def t_view_getfocus_removed():
    # beta6 View.h: no GetFocus (focus is MakeFocus/IsFocus only)
    assert not hasattr(BView, "GetFocus")
    assert hasattr(BView, "MakeFocus") and hasattr(BView, "IsFocus")
common.check("interface:View.GetFocus-removed", t_view_getfocus_removed)


def t_control_pulse_shape():
    # beta6: Pulse() lives on BView (View.h:192), inherited by BControl;
    # it returns void (classic's status-returning form is gone)
    assert hasattr(BView, "Pulse") and hasattr(BControl, "Pulse")
    d = doc(BView, "Pulse")
    assert "-> None" in d, d
common.check("interface:Control.Pulse-void", t_control_pulse_shape)


def t_font_setto_removed():
    # beta6 Font.h: no BFont::SetTo — family/size go through
    # SetFamilyAndStyle/SetSize
    assert not hasattr(BFont, "SetTo")
    assert hasattr(BFont, "SetSize") and hasattr(BFont, "SetFamilyAndStyle")
common.check("interface:Font.SetTo-removed", t_font_setto_removed)


def t_bitmap_init_getbits_removed():
    # beta6 Bitmap.h: no Init()/GetBits() — constructors + Bits()/LockBits()
    assert not hasattr(BBitmap, "Init")
    assert not hasattr(BBitmap, "GetBits")
    assert hasattr(BBitmap, "Bits") and hasattr(BBitmap, "LockBits")
common.check("interface:Bitmap.Init-GetBits-removed", t_bitmap_init_getbits_removed)


def t_listview_finditem_removed():
    # beta6 ListView.h: no FindItem/FindString — IndexOf(point)/IndexOf(item)
    assert not hasattr(BListView, "FindItem")
    assert not hasattr(BListView, "FindString")
    assert hasattr(BListView, "IndexOf")
common.check("interface:ListView.FindItem-removed", t_listview_finditem_removed)


def t_tabview_currenttab_removed():
    # beta6 TabView.h: no CurrentTab — AddTab/TabAt/RemoveTab
    assert not hasattr(BTabView, "CurrentTab")
    assert hasattr(BTabView, "TabAt") and hasattr(BTabView, "AddTab")
common.check("interface:TabView.CurrentTab-removed", t_tabview_currenttab_removed)


def t_deskbar_menubar_removed():
    # beta6 Deskbar.h: no MenuBar()
    assert not hasattr(BDeskbar, "MenuBar")
    assert hasattr(BDeskbar, "Location")
common.check("interface:Deskbar.MenuBar-removed", t_deskbar_menubar_removed)


def t_input_mappings_removed():
    # beta6 Input.h: no FindKeyboardMapping/FindButtonMapping (classic
    # BKeyboard/BMouse API); BInputDevice is driven via Control(code, msg)
    assert not hasattr(BInputDevice, "FindKeyboardMapping")
    assert not hasattr(BInputDevice, "FindButtonMapping")
    assert hasattr(BInputDevice, "Control")
common.check("interface:Input.mappings-removed", t_input_mappings_removed)


# ------------------------------------- out-param rebinds: shape (docstring)
def t_view_clip_to_picture_shape():
    # input-only BPicture* — still bound; a wrong-arity call must raise a
    # clean TypeError (never a segfault)
    d = doc(BView, "ClipToPicture")
    assert "ClipToPicture" in d
    try:
        BView.ClipToPicture(None)
        raise AssertionError("no TypeError")
    except TypeError:
        pass
common.check("interface:View.ClipToPicture-shape", t_view_clip_to_picture_shape)


def t_view_convert_value_returns():
    # beta6 View.h:216-231 added by-value overloads; the in/out pointer
    # overloads are no longer bound. (cross-module types are printed fully
    # qualified in pybind docstrings)
    for name in ("ConvertToScreen", "ConvertFromScreen",
                 "ConvertToParent", "ConvertFromParent"):
        d = doc(BView, name)
        assert "BPoint" in d and "BRect" in d, (name, d)
        assert "BPoint*" not in d and "BRect*" not in d, (name, d)
        assert d.count("->") == 2, d  # both value overloads, no pointer form
common.check("interface:View.Convert-value-return", t_view_convert_value_returns)


def t_view_get_clipping_region():
    # out BRegion* -> construct-and-return
    assert "-> BRegion" in doc(BView, "GetClippingRegion")
    assert "-> BRegion" in doc(BView, "ConstrainClippingRegion")
common.check("interface:View.GetClippingRegion", t_view_get_clipping_region)


def t_view_get_blending_mode():
    # two out enum-pointers (a write through them corrupted static data)
    d = doc(BView, "GetBlendingMode")
    assert "source_alpha" in d and "alpha_function" in d and "tuple" in d, d
common.check("interface:View.GetBlendingMode", t_view_get_blending_mode)


def t_view_ui_colors():
    # float* tint out-param -> (color_which, float)
    for name in ("ViewUIColor", "HighUIColor", "LowUIColor"):
        d = doc(BView, name)
        assert "color_which" in d and "float" in d and "tuple" in d, (name, d)
common.check("interface:View.UIColors-tint", t_view_ui_colors)


def t_view_draw_string():
    # in/out escapement_delta* -> internal buffer, delta returned
    d = doc(BView, "DrawString")
    assert "-> escapement_delta" in d, d
common.check("interface:View.DrawString-delta", t_view_draw_string)


def t_view_get_font_height():
    assert "-> BFont" in doc(BView, "GetFont")
    assert "-> font_height" in doc(BView, "GetFontHeight")
common.check("interface:View.GetFont-GetFontHeight", t_view_get_font_height)


def t_view_get_preferred_size():
    d = doc(BView, "GetPreferredSize")
    assert "tuple[float, float]" in d, d
    try:
        BView.GetPreferredSize(None, 1.0)
        raise AssertionError("no TypeError")
    except TypeError:
        pass
common.check("interface:View.GetPreferredSize", t_view_get_preferred_size)


def t_view_get_height_for_width():
    d = doc(BView, "GetHeightForWidth")
    assert "tuple[float, float, float]" in d, d
common.check("interface:View.GetHeightForWidth", t_view_get_height_for_width)


def t_controls_get_preferred_size_fleet():
    # (BAlert is a BWindow, not a BControl — no GetPreferredSize)
    for cls in (BControl, BSlider, BScrollBar, BChannelControl,
                BTextControl, BTextView, BDragger, BListView):
        d = doc(cls, "GetPreferredSize")
        assert "tuple[float, float]" in d, (cls.__name__, d)
common.check("interface:controls.GetPreferredSize-fleet",
      t_controls_get_preferred_size_fleet)


def t_layouts_get_height_for_width_fleet():
    for cls in (BLayoutItem, BTwoDimensionalLayout, BCardLayout, BTextView):
        d = doc(cls, "GetHeightForWidth")
        assert "tuple[float, float, float]" in d, (cls.__name__, d)
common.check("interface:layouts.GetHeightForWidth-fleet",
      t_layouts_get_height_for_width_fleet)


# ------------------------------------------------- Screen: functional
# NOTE (2026-10-26): from an ssh session the app_server answers screen
# queries with B_ERROR and a zero frame (no screen attached to that
# session), so every row below skips unless a screen is visible; run from
# the console session (or with the desktop up for the user) and they pin
# st == B_OK for real.
def _screen():
    try:
        s = BScreen()
        frame = s.Frame()  # force a server round-trip
        if frame.right - frame.left <= 0:
            raise common.Skip("no screen visible from this session")
        return s
    except common.Skip:
        raise
    except BaseException:
        raise common.Skip("no app_server connection")


def t_screen_get_mode():
    s = _screen()
    mode, st = s.GetMode()
    assert st == B_OK, st
    assert mode.virtual_width > 0, mode.virtual_width
common.check("interface:Screen.GetMode", t_screen_get_mode)


def t_screen_get_device_info():
    s = _screen()
    info, st = s.GetDeviceInfo()
    assert st == B_OK, st
common.check("interface:Screen.GetDeviceInfo", t_screen_get_device_info)


def t_screen_get_monitor_info():
    s = _screen()
    info, st = s.GetMonitorInfo()
    assert st == B_OK, st
common.check("interface:Screen.GetMonitorInfo", t_screen_get_monitor_info)


def t_screen_get_timing_constraints():
    s = _screen()
    tc, st = s.GetTimingConstraints()
    assert st == B_OK, st
common.check("interface:Screen.GetTimingConstraints", t_screen_get_timing_constraints)


def t_screen_get_brightness():
    s = _screen()
    brightness, st = s.GetBrightness()
    assert st == B_OK, st
    assert isinstance(brightness, float)
common.check("interface:Screen.GetBrightness", t_screen_get_brightness)


def t_screen_get_bitmap_frame():
    # The 2026-10-25 fix: the old lambda segfaulted on the default NULL
    # frame (it did `new BBitmap(*frame, ...)`); now frame is optional and
    # the bitmap is allocated by the API itself (Screen.h GetBitmap).
    s = _screen()
    bitmap, st = s.GetBitmap(False)
    assert st == B_OK, st
    assert isinstance(bitmap, BBitmap)
    b = bitmap.Bounds()
    assert b.right - b.left > 0 and b.bottom - b.top > 0, b
    frame = s.Frame()
    bitmap2, st2 = s.GetBitmap(False, frame)
    assert st2 == B_OK, st2
    assert bitmap2.Bounds() == frame
common.check("interface:Screen.GetBitmap", t_screen_get_bitmap_frame)


def t_screen_get_pixel_clock_limits():
    s = _screen()
    mode, st = s.GetMode()
    assert st == B_OK, st
    low, high, st2 = s.GetPixelClockLimits(mode)
    assert st2 == B_OK, st2
    assert high >= low, (low, high)
common.check("interface:Screen.GetPixelClockLimits", t_screen_get_pixel_clock_limits)


# ------------------------------------------------- Bitmap: functional
def _local_bitmap():
    try:
        b = BBitmap(BRect(0, 0, 8, 8), B_BITMAP_NO_SERVER_LINK, Be.B_RGBA32)
        b.Bounds()
        return b
    except BaseException:
        return None


def t_bitmap_lock_bits():
    # beta6 Bitmap.h: status_t LockBits(uint32* state = NULL) — the state
    # out-param was unusable from Python (None -> value lost).
    b = _local_bitmap()
    if b is None:
        raise common.Skip("BBitmap unavailable headless")
    state, st = b.LockBits()
    assert st == B_OK, st
    b.UnlockBits()
common.check("interface:Bitmap.LockBits", t_bitmap_lock_bits)


def t_bitmap_bits_bytes():
    b = _local_bitmap()
    if b is None:
        raise common.Skip("BBitmap unavailable headless")
    data = b.Bits()
    assert isinstance(data, (bytes, bytearray)) and len(data) > 0
common.check("interface:Bitmap.Bits", t_bitmap_bits_bytes)


def t_bitmap_overlay_restrictions():
    b = _local_bitmap()
    if b is None:
        raise common.Skip("BBitmap unavailable headless")
    res, st = b.GetOverlayRestrictions()
    assert isinstance(res, Be.overlay_restrictions), type(res)
common.check("interface:Bitmap.GetOverlayRestrictions", t_bitmap_overlay_restrictions)


# ------------------------------------------------- AffineTransform: functional
def t_affine_apply():
    # pure data class — always headless-safe. init(sx, shy, shx, sy, tx, ty)
    t = BAffineTransform(2.0, 0.0, 0.0, 2.0, 10.0, 20.0)
    p = t.Apply(BPoint(1.0, 1.0))
    assert (p.x, p.y) == (12.0, 22.0), (p.x, p.y)
    x, y = t.Apply(1.0, 1.0)
    assert (x, y) == (12.0, 22.0), (x, y)
    pts = t.Apply([BPoint(1.0, 1.0), BPoint(0.0, 0.0)])
    assert len(pts) == 2 and pts[0].x == 12.0 and pts[1].y == 20.0
common.check("interface:AffineTransform.Apply", t_affine_apply)


def t_affine_apply_inverse():
    t = BAffineTransform(2.0, 0.0, 0.0, 2.0, 10.0, 20.0)
    p = t.ApplyInverse(BPoint(12.0, 22.0))
    assert abs(p.x - 1.0) < 1e-9 and abs(p.y - 1.0) < 1e-9, (p.x, p.y)
common.check("interface:AffineTransform.ApplyInverse", t_affine_apply_inverse)


def t_affine_params():
    t = BAffineTransform(2.0, 0.0, 0.5, 3.0, 10.0, 20.0)
    tx, ty = t.GetTranslation()
    assert (tx, ty) == (10.0, 20.0), (tx, ty)
    params = t.GetAffineParameters()
    assert len(params) == 7, params
    # beta6 GetScale folds the shear in (|sx|+|shx|, |shy|+|sy|) and
    # GetScaleAbs is the Euclidean norm sqrt(sx^2+shx^2) — both pinned on
    # a shear-free matrix for exactness
    t2 = BAffineTransform(2.0, 0.0, 0.0, 3.0, 0.0, 0.0)
    sx, sy = t2.GetScale()
    assert (sx, sy) == (2.0, 3.0), (sx, sy)
    absx, absy = t2.GetScaleAbs()
    assert (absx, absy) == (2.0, 3.0), (absx, absy)
    import math
    ax, ay = t.GetScaleAbs()
    assert abs(ax - math.sqrt(2.0**2 + 0.5**2)) < 1e-9 and ay == 3.0, (ax, ay)
common.check("interface:AffineTransform.Parameters", t_affine_params)


# ------------------------------------------------- Font: functional (guarded)
def _font():
    try:
        f = BFont()
        f.Size()
        return f
    except BaseException:
        return None


def t_font_get_height():
    f = _font()
    if f is None:
        raise common.Skip("font server unavailable")
    h = f.GetHeight()
    assert h.ascent > 0 or h.descent > 0, (h.ascent, h.descent)
common.check("interface:Font.GetHeight", t_font_get_height)


# NOTE (2026-10-26): glyph-level font queries (CountTuned/GetTunedInfo/
# TruncateString/GetEdges/GetBoundingBoxes*) BLOCK IN KERNEL IPC from an ssh
# session on this VM (the font server query never answers; the thread sits
# in uninterruptible state — even kill -9 cannot reap it). Only family-level
# queries (Size/GetHeight) are provably safe headless, so those rows are
# shape-pins via docstring, not functional calls.
def t_font_get_tuned_info_shape():
    d = doc(BFont, "GetTunedInfo")
    assert "tuned_font_info" in d and "->" in d, d
common.check("interface:Font.GetTunedInfo-shape", t_font_get_tuned_info_shape)


def t_font_truncate_string_shape():
    d = doc(BFont, "TruncateString")
    assert "-> str" in d, d
common.check("interface:Font.TruncateString-shape", t_font_truncate_string_shape)


def t_font_get_edges_shape():
    d = doc(BFont, "GetEdges")
    assert "-> list" in d, d
common.check("interface:Font.GetEdges-shape", t_font_get_edges_shape)


def t_font_get_bounding_boxes_shape():
    d = doc(BFont, "GetBoundingBoxesAsGlyphs")
    assert "list[Be.Rect.BRect]" in d, d
    d = doc(BFont, "GetBoundingBoxesAsString")
    assert "list[Be.Rect.BRect]" in d and "escapement_delta" in d, d
common.check("interface:Font.GetBoundingBoxes-shape", t_font_get_bounding_boxes_shape)


# --------------------------------- the rest of the rebinds: shape (docstring)
def t_alert_add_button():
    d = doc(BAlert, "AddButton")
    assert "label" in d, d
    assert "= " in d, d  # key has a default (1-arg form)
common.check("interface:Alert.AddButton", t_alert_add_button)


def t_slider_scrollbar_channel():
    d = doc(BSlider, "GetLimits")
    assert "tuple[int, int]" in d, d
    d = doc(BSlider, "FillColor")
    assert "rgb_color" in d and "bool" in d and "tuple" in d, d
    assert "tuple[float, float]" in doc(BScrollBar, "GetRange")
    assert "tuple[float, float]" in doc(BScrollBar, "GetSteps")
    assert "tuple[int, int, int]" in doc(BChannelControl, "GetLimits")
common.check("interface:Slider-ScrollBar-ChannelControl", t_slider_scrollbar_channel)


def t_textcontrol_textview():
    d = doc(BTextControl, "GetAlignment")
    assert "alignment" in d and "tuple" in d, d
    d = doc(BTextView, "GetFontAndColor")
    assert "BFont" in d and "tuple" in d, d
    assert "-> list" in doc(BTextView, "RunArray")
    assert "-> BRegion" in doc(BTextView, "GetTextRegion")
    d = doc(BTextView, "GetInsets")
    assert "tuple[float, float, float, float]" in d, d
    d = doc(BTextView, "UndoState")
    assert "undo_state" in d and "bool" in d, d
common.check("interface:TextControl-TextView", t_textcontrol_textview)


def t_printjob_menuitem_dragger():
    assert "tuple[int, int]" in doc(BPrintJob, "GetResolution")
    d = doc(BPrintJob, "PrinterType")
    assert "tuple" in d, d
    d = doc(BMenuItem, "Shortcut")
    assert "tuple" in d, d
    d = doc(BDragger, "DragBitmap")
    assert "BPoint" in d and "drawing_mode" in d and "tuple" in d, d
common.check("interface:PrintJob-MenuItem-Dragger", t_printjob_menuitem_dragger)


def t_deskbar_rebinds():
    d = doc(BDeskbar, "Location")
    assert "deskbar_location" in d and "bool" in d, d
    assert "tuple" in doc(BDeskbar, "GetItemInfo")
    assert "tuple" in doc(BDeskbar, "AddItem")
common.check("interface:Deskbar.rebinds", t_deskbar_rebinds)


# --------------------------------------- modules not in the jam build list
common.absent("interface:OptionPopUp.rebinds",
              "OptionPopUp.cpp not in the Jamfile sourceFiles list (not built)")
common.absent("interface:SplitView.GetInsets",
              "SplitView.cpp not in the Jamfile sourceFiles list (not built)")
common.absent("interface:SplitLayoutBuilder.GetSplitView",
              "SplitLayoutBuilder.cpp not in the Jamfile sourceFiles list (not built)")
common.absent("interface:Shelf.SaveLocation-ReplicantAt",
              "Shelf.cpp not in the Jamfile sourceFiles list (not built)")

sys.exit(common.report("test_interface"))
