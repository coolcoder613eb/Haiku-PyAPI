#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/InterfaceDefs.h>
#include <GraphicsDefs.h>
#include <OS.h>
#include <String.h>
#include <Bitmap.h>
#include <Point.h>
#include <Rect.h>

namespace py = pybind11;


PYBIND11_MODULE(InterfaceDefs,m)
{
m.attr("B_BACKSPACE") = 8;
m.attr("B_RETURN") = 10;
m.attr("B_ENTER") = 10;
m.attr("B_SPACE") = 32;
m.attr("B_TAB") = 9;
m.attr("B_ESCAPE") = 27;
m.attr("B_SUBSTITUTE") = 26;
m.attr("B_LEFT_ARROW") = 28;
m.attr("B_RIGHT_ARROW") = 29;
m.attr("B_UP_ARROW") = 30;
m.attr("B_DOWN_ARROW") = 31;
m.attr("B_INSERT") = 5;
m.attr("B_DELETE") = 127;
m.attr("B_HOME") = 1;
m.attr("B_END") = 4;
m.attr("B_PAGE_UP") = 11;
m.attr("B_PAGE_DOWN") = 12;
m.attr("B_FUNCTION_KEY") = 16;
m.attr("B_KATAKANA_HIRAGANA") = 242;
m.attr("B_HANKAKU_ZENKAKU") = 243;
m.attr("B_HANGUL") = 240;
m.attr("B_HANGUL_HANJA") = 241;

m.attr("B_F1_KEY") = 2;
m.attr("B_F2_KEY") = 3;
m.attr("B_F3_KEY") = 4;
m.attr("B_F4_KEY") = 5;
m.attr("B_F5_KEY") = 6;
m.attr("B_F6_KEY") = 7;
m.attr("B_F7_KEY") = 8;
m.attr("B_F8_KEY") = 9;
m.attr("B_F9_KEY") = 10;
m.attr("B_F10_KEY") = 11;
m.attr("B_F11_KEY") = 12;
m.attr("B_F12_KEY") = 13;
m.attr("B_PRINT_KEY") = 14;
m.attr("B_SCROLL_KEY") = 15;
m.attr("B_PAUSE_KEY") = 16;

m.attr("B_CONTROL_TABLE") = 1;
m.attr("B_OPTION_CAPS_SHIFT_TABLE") = 2;
m.attr("B_OPTION_CAPS_TABLE") = 4;
m.attr("B_OPTION_SHIFT_TABLE") = 8;
m.attr("B_OPTION_TABLE") = 16;
m.attr("B_CAPS_SHIFT_TABLE") = 32;
m.attr("B_CAPS_TABLE") = 64;
m.attr("B_SHIFT_TABLE") = 128;
m.attr("B_NORMAL_TABLE") = 256;

m.attr("B_SHIFT_KEY") = 1;
m.attr("B_COMMAND_KEY") = 2;
m.attr("B_CONTROL_KEY") = 4;
m.attr("B_CAPS_LOCK") = 8;
m.attr("B_SCROLL_LOCK") = 16;
m.attr("B_NUM_LOCK") = 32;
m.attr("B_OPTION_KEY") = 64;
m.attr("B_MENU_KEY") = 128;
m.attr("B_LEFT_SHIFT_KEY") = 256;
m.attr("B_RIGHT_SHIFT_KEY") = 512;
m.attr("B_LEFT_COMMAND_KEY") = 1024;
m.attr("B_RIGHT_COMMAND_KEY") = 2048;
m.attr("B_LEFT_CONTROL_KEY") = 4096;
m.attr("B_RIGHT_CONTROL_KEY") = 8192;
m.attr("B_LEFT_OPTION_KEY") = 16384;
m.attr("B_RIGHT_OPTION_KEY") = 32768;

py::enum_<mode_mouse>(m, "mode_mouse", "")
.value("B_NORMAL_MOUSE", mode_mouse::B_NORMAL_MOUSE, "")
.value("B_CLICK_TO_FOCUS_MOUSE", mode_mouse::B_CLICK_TO_FOCUS_MOUSE, "")
.value("B_FOCUS_FOLLOWS_MOUSE", mode_mouse::B_FOCUS_FOLLOWS_MOUSE, "")
.export_values();

py::enum_<mode_focus_follows_mouse>(m, "mode_focus_follows_mouse", "")
.value("B_NORMAL_FOCUS_FOLLOWS_MOUSE", mode_focus_follows_mouse::B_NORMAL_FOCUS_FOLLOWS_MOUSE, "")
.value("B_WARP_FOCUS_FOLLOWS_MOUSE", mode_focus_follows_mouse::B_WARP_FOCUS_FOLLOWS_MOUSE, "")
.value("B_INSTANT_WARP_FOCUS_FOLLOWS_MOUSE", mode_focus_follows_mouse::B_INSTANT_WARP_FOCUS_FOLLOWS_MOUSE, "")
.export_values();

py::enum_<border_style>(m, "border_style", "")
.value("B_PLAIN_BORDER", border_style::B_PLAIN_BORDER, "")
.value("B_FANCY_BORDER", border_style::B_FANCY_BORDER, "")
.value("B_NO_BORDER", border_style::B_NO_BORDER, "")
.export_values();

py::enum_<orientation>(m, "orientation", "")
.value("B_HORIZONTAL", orientation::B_HORIZONTAL, "")
.value("B_VERTICAL", orientation::B_VERTICAL, "")
.export_values();

py::enum_<button_width>(m, "button_width", "")
.value("B_WIDTH_AS_USUAL", button_width::B_WIDTH_AS_USUAL, "")
.value("B_WIDTH_FROM_WIDEST", button_width::B_WIDTH_FROM_WIDEST, "")
.value("B_WIDTH_FROM_LABEL", button_width::B_WIDTH_FROM_LABEL, "")
.export_values();

py::enum_<alignment>(m, "alignment", "")
.value("B_ALIGN_LEFT", alignment::B_ALIGN_LEFT, "")
.value("B_ALIGN_RIGHT", alignment::B_ALIGN_RIGHT, "")
.value("B_ALIGN_CENTER", alignment::B_ALIGN_CENTER, "")
.value("B_ALIGN_HORIZONTAL_CENTER", alignment::B_ALIGN_HORIZONTAL_CENTER, "")
.value("B_ALIGN_HORIZONTAL_UNSET", alignment::B_ALIGN_HORIZONTAL_UNSET, "")
.value("B_ALIGN_USE_FULL_WIDTH", alignment::B_ALIGN_USE_FULL_WIDTH, "")
.export_values();

py::enum_<vertical_alignment>(m, "vertical_alignment", "")
.value("B_ALIGN_TOP", vertical_alignment::B_ALIGN_TOP, "")
.value("B_ALIGN_MIDDLE", vertical_alignment::B_ALIGN_MIDDLE, "")
.value("B_ALIGN_BOTTOM", vertical_alignment::B_ALIGN_BOTTOM, "")
.value("B_ALIGN_VERTICAL_CENTER", vertical_alignment::B_ALIGN_VERTICAL_CENTER, "")
.value("B_ALIGN_VERTICAL_UNSET", vertical_alignment::B_ALIGN_VERTICAL_UNSET, "")
.value("B_ALIGN_NO_VERTICAL", vertical_alignment::B_ALIGN_NO_VERTICAL, "")
.value("B_ALIGN_USE_FULL_HEIGHT", vertical_alignment::B_ALIGN_USE_FULL_HEIGHT, "")
.export_values();

// WHY ARE THESE ASSIGNED AS STRINGS?
/*
m.attr("B_USE_DEFAULT_SPACING") = "- 1002";
m.attr("B_USE_ITEM_SPACING") = "- 1003";
m.attr("B_USE_ITEM_INSETS") = "B_USE_ITEM_SPACING";
m.attr("B_USE_HALF_ITEM_SPACING") = "- 1004";
m.attr("B_USE_HALF_ITEM_INSETS") = "B_USE_HALF_ITEM_SPACING";
m.attr("B_USE_WINDOW_SPACING") = "- 1005";
m.attr("B_USE_WINDOW_INSETS") = "B_USE_WINDOW_SPACING";
m.attr("B_USE_SMALL_SPACING") = "- 1006";
m.attr("B_USE_SMALL_INSETS") = "B_USE_SMALL_SPACING";
m.attr("B_USE_CORNER_SPACING") = "- 1007";
m.attr("B_USE_CORNER_INSETS") = "B_USE_CORNER_SPACING";
m.attr("B_USE_BIG_SPACING") = "- 1008";
m.attr("B_USE_BIG_INSETS") = "B_USE_BIG_SPACING";
m.attr("B_USE_BORDER_SPACING") = "- 1009";
m.attr("B_USE_BORDER_INSETS") = "B_USE_BORDER_SPACING";
*/

m.attr("B_USE_DEFAULT_SPACING") = -1002;
m.attr("B_USE_ITEM_SPACING") = -1003;
m.attr("B_USE_ITEM_INSETS") = -1003;
m.attr("B_USE_HALF_ITEM_SPACING") = -1004;
m.attr("B_USE_HALF_ITEM_INSETS") = -1004;
m.attr("B_USE_WINDOW_SPACING") = -1005;
m.attr("B_USE_WINDOW_INSETS") = -1005;
m.attr("B_USE_SMALL_SPACING") = -1006;
m.attr("B_USE_SMALL_INSETS") = -1006;
m.attr("B_USE_CORNER_SPACING") = -1007;
m.attr("B_USE_CORNER_INSETS") = -1007;
m.attr("B_USE_BIG_SPACING") = -1008;
m.attr("B_USE_BIG_INSETS") = -1008;
m.attr("B_USE_BORDER_SPACING") = -1009;
m.attr("B_USE_BORDER_INSETS") = -1009;

py::enum_<join_mode>(m, "join_mode", "")
.value("B_ROUND_JOIN", join_mode::B_ROUND_JOIN, "")
.value("B_MITER_JOIN", join_mode::B_MITER_JOIN, "")
.value("B_BEVEL_JOIN", join_mode::B_BEVEL_JOIN, "")
.value("B_BUTT_JOIN", join_mode::B_BUTT_JOIN, "")
.value("B_SQUARE_JOIN", join_mode::B_SQUARE_JOIN, "")
.export_values();

py::enum_<cap_mode>(m, "cap_mode", "")
.value("B_ROUND_CAP", cap_mode::B_ROUND_CAP, "")
.value("B_BUTT_CAP", cap_mode::B_BUTT_CAP, "")
.value("B_SQUARE_CAP", cap_mode::B_SQUARE_CAP, "")
.export_values();

m.attr("B_EVEN_ODD") = 0;
m.attr("B_NONZERO") = 1;

py::enum_<bitmap_tiling>(m, "bitmap_tiling", "")
.value("B_TILE_BITMAP_X", bitmap_tiling::B_TILE_BITMAP_X, "")
.value("B_TILE_BITMAP_Y", bitmap_tiling::B_TILE_BITMAP_Y, "")
.value("B_TILE_BITMAP", bitmap_tiling::B_TILE_BITMAP, "")
.export_values();

py::enum_<overlay_options>(m, "overlay_options", "")
.value("B_OVERLAY_FILTER_HORIZONTAL", overlay_options::B_OVERLAY_FILTER_HORIZONTAL, "")
.value("B_OVERLAY_FILTER_VERTICAL", overlay_options::B_OVERLAY_FILTER_VERTICAL, "")
.value("B_OVERLAY_MIRROR", overlay_options::B_OVERLAY_MIRROR, "")
.value("B_OVERLAY_TRANSFER_CHANNEL", overlay_options::B_OVERLAY_TRANSFER_CHANNEL, "")
.export_values();

py::enum_<bitmap_drawing_options>(m, "bitmap_drawing_options", "")
.value("B_FILTER_BITMAP_BILINEAR", bitmap_drawing_options::B_FILTER_BITMAP_BILINEAR, "")
.value("B_WAIT_FOR_RETRACE", bitmap_drawing_options::B_WAIT_FOR_RETRACE, "")
.export_values();

py::enum_<color_which>(m, "color_which", "")
.value("B_NO_COLOR", color_which::B_NO_COLOR, "")
.value("B_PANEL_BACKGROUND_COLOR", color_which::B_PANEL_BACKGROUND_COLOR, "")
.value("B_PANEL_TEXT_COLOR", color_which::B_PANEL_TEXT_COLOR, "")
.value("B_DOCUMENT_BACKGROUND_COLOR", color_which::B_DOCUMENT_BACKGROUND_COLOR, "")
.value("B_DOCUMENT_TEXT_COLOR", color_which::B_DOCUMENT_TEXT_COLOR, "")
.value("B_CONTROL_BACKGROUND_COLOR", color_which::B_CONTROL_BACKGROUND_COLOR, "")
.value("B_CONTROL_TEXT_COLOR", color_which::B_CONTROL_TEXT_COLOR, "")
.value("B_CONTROL_BORDER_COLOR", color_which::B_CONTROL_BORDER_COLOR, "")
.value("B_CONTROL_HIGHLIGHT_COLOR", color_which::B_CONTROL_HIGHLIGHT_COLOR, "")
.value("B_CONTROL_MARK_COLOR", color_which::B_CONTROL_MARK_COLOR, "")
.value("B_NAVIGATION_BASE_COLOR", color_which::B_NAVIGATION_BASE_COLOR, "")
.value("B_NAVIGATION_PULSE_COLOR", color_which::B_NAVIGATION_PULSE_COLOR, "")
.value("B_SHINE_COLOR", color_which::B_SHINE_COLOR, "")
.value("B_SHADOW_COLOR", color_which::B_SHADOW_COLOR, "")
.value("B_LINK_TEXT_COLOR", color_which::B_LINK_TEXT_COLOR, "")
.value("B_LINK_HOVER_COLOR", color_which::B_LINK_HOVER_COLOR, "")
.value("B_LINK_VISITED_COLOR", color_which::B_LINK_VISITED_COLOR, "")
.value("B_LINK_ACTIVE_COLOR", color_which::B_LINK_ACTIVE_COLOR, "")
.value("B_MENU_BACKGROUND_COLOR", color_which::B_MENU_BACKGROUND_COLOR, "")
.value("B_MENU_SELECTED_BACKGROUND_COLOR", color_which::B_MENU_SELECTED_BACKGROUND_COLOR, "")
.value("B_MENU_ITEM_TEXT_COLOR", color_which::B_MENU_ITEM_TEXT_COLOR, "")
.value("B_MENU_SELECTED_ITEM_TEXT_COLOR", color_which::B_MENU_SELECTED_ITEM_TEXT_COLOR, "")
.value("B_MENU_SELECTED_BORDER_COLOR", color_which::B_MENU_SELECTED_BORDER_COLOR, "")
.value("B_LIST_BACKGROUND_COLOR", color_which::B_LIST_BACKGROUND_COLOR, "")
.value("B_LIST_SELECTED_BACKGROUND_COLOR", color_which::B_LIST_SELECTED_BACKGROUND_COLOR, "")
.value("B_LIST_ITEM_TEXT_COLOR", color_which::B_LIST_ITEM_TEXT_COLOR, "")
.value("B_LIST_SELECTED_ITEM_TEXT_COLOR", color_which::B_LIST_SELECTED_ITEM_TEXT_COLOR, "")
.value("B_SCROLL_BAR_THUMB_COLOR", color_which::B_SCROLL_BAR_THUMB_COLOR, "")
.value("B_TOOL_TIP_BACKGROUND_COLOR", color_which::B_TOOL_TIP_BACKGROUND_COLOR, "")
.value("B_TOOL_TIP_TEXT_COLOR", color_which::B_TOOL_TIP_TEXT_COLOR, "")
.value("B_STATUS_BAR_COLOR", color_which::B_STATUS_BAR_COLOR, "")
.value("B_SUCCESS_COLOR", color_which::B_SUCCESS_COLOR, "")
.value("B_FAILURE_COLOR", color_which::B_FAILURE_COLOR, "")
.value("B_WINDOW_TAB_COLOR", color_which::B_WINDOW_TAB_COLOR, "")
.value("B_WINDOW_TEXT_COLOR", color_which::B_WINDOW_TEXT_COLOR, "")
.value("B_WINDOW_INACTIVE_TAB_COLOR", color_which::B_WINDOW_INACTIVE_TAB_COLOR, "")
.value("B_WINDOW_INACTIVE_TEXT_COLOR", color_which::B_WINDOW_INACTIVE_TEXT_COLOR, "")
.value("B_WINDOW_BORDER_COLOR", color_which::B_WINDOW_BORDER_COLOR, "")
.value("B_WINDOW_INACTIVE_BORDER_COLOR", color_which::B_WINDOW_INACTIVE_BORDER_COLOR, "")
.value("B_KEYBOARD_NAVIGATION_COLOR", color_which::B_KEYBOARD_NAVIGATION_COLOR, "")
.value("B_MENU_SELECTION_BACKGROUND_COLOR", color_which::B_MENU_SELECTION_BACKGROUND_COLOR, "")
.value("B_DESKTOP_COLOR", color_which::B_DESKTOP_COLOR, "")
.export_values();

m.attr("B_INACTIVE_ICON_BITMAP") = 0;
m.attr("B_ACTIVE_ICON_BITMAP") = 1;
m.attr("B_PARTIALLY_ACTIVATE_ICON_BITMAP") = 2;
m.attr("B_DISABLED_ICON_BITMAP") = 128;

m.attr("B_KEEP_ICON_BITMAP") = 1;

m.attr("B_TRIM_ICON_BITMAP") = 256;
m.attr("B_TRIM_ICON_BITMAP_KEEP_ASPECT") = 512;
m.attr("B_CREATE_ACTIVE_ICON_BITMAP") = 1024;
m.attr("B_CREATE_PARTIALLY_ACTIVE_ICON_BITMAP") = 2048;
m.attr("B_CREATE_DISABLED_ICON_BITMAPS") = 4096;

m.attr("B_DEFAULT_MITER_LIMIT") = B_DEFAULT_MITER_LIMIT;

m.attr("B_LIGHTEN_MAX_TINT") = B_LIGHTEN_MAX_TINT;

m.attr("B_LIGHTEN_2_TINT") = B_LIGHTEN_2_TINT;

m.attr("B_LIGHTEN_1_TINT") = B_LIGHTEN_1_TINT;

m.attr("B_NO_TINT") = B_NO_TINT;

m.attr("B_DARKEN_1_TINT") = B_DARKEN_1_TINT;

m.attr("B_DARKEN_2_TINT") = B_DARKEN_2_TINT;

m.attr("B_DARKEN_3_TINT") = B_DARKEN_3_TINT;

m.attr("B_DARKEN_4_TINT") = B_DARKEN_4_TINT;

m.attr("B_DARKEN_MAX_TINT") = B_DARKEN_MAX_TINT;

m.attr("B_DISABLED_LABEL_TINT") = B_DISABLED_LABEL_TINT;

m.attr("B_HIGHLIGHT_BACKGROUND_TINT") = B_HIGHLIGHT_BACKGROUND_TINT;

m.attr("B_DISABLED_MARK_TINT") = B_DISABLED_MARK_TINT;

py::class_<key_info>(m, "key_info")
.def_readwrite("modifiers", &key_info::modifiers, "")
.def_readonly("key_states", &key_info::key_states, "") //TODO is this really Read-Only?
;

py::class_<key_map>(m, "key_map")
.def_readwrite("version", &key_map::version, "")
.def_readwrite("caps_key", &key_map::caps_key, "")
.def_readwrite("scroll_key", &key_map::scroll_key, "")
.def_readwrite("num_key", &key_map::num_key, "")
.def_readwrite("left_shift_key", &key_map::left_shift_key, "")
.def_readwrite("right_shift_key", &key_map::right_shift_key, "")
.def_readwrite("left_command_key", &key_map::left_command_key, "")
.def_readwrite("right_command_key", &key_map::right_command_key, "")
.def_readwrite("left_control_key", &key_map::left_control_key, "")
.def_readwrite("right_control_key", &key_map::right_control_key, "")
.def_readwrite("left_option_key", &key_map::left_option_key, "")
.def_readwrite("right_option_key", &key_map::right_option_key, "")
.def_readwrite("menu_key", &key_map::menu_key, "")
.def_readwrite("lock_settings", &key_map::lock_settings, "")
// TODO are these read-only?
.def_readonly("control_map", &key_map::control_map, "")
.def_readonly("option_caps_shift_map", &key_map::option_caps_shift_map, "")
.def_readonly("option_caps_map", &key_map::option_caps_map, "")
.def_readonly("option_shift_map", &key_map::option_shift_map, "")
.def_readonly("option_map", &key_map::option_map, "")
.def_readonly("caps_shift_map", &key_map::caps_shift_map, "")
.def_readonly("caps_map", &key_map::caps_map, "")
.def_readonly("shift_map", &key_map::shift_map, "")
.def_readonly("normal_map", &key_map::normal_map, "")
//.def_readonly("acute_dead_key", &key_map::acute_dead_key, "")
.def_readonly("grave_dead_key", &key_map::grave_dead_key, "")
.def_readonly("circumflex_dead_key", &key_map::circumflex_dead_key, "")
.def_readonly("dieresis_dead_key", &key_map::dieresis_dead_key, "")
.def_readonly("tilde_dead_key", &key_map::tilde_dead_key, "")
.def_readwrite("acute_tables", &key_map::acute_tables, "")
.def_readwrite("grave_tables", &key_map::grave_tables, "")
.def_readwrite("circumflex_tables", &key_map::circumflex_tables, "")
.def_readwrite("dieresis_tables", &key_map::dieresis_tables, "")
.def_readwrite("tilde_tables", &key_map::tilde_tables, "")
;

py::class_<mouse_map>(m, "mouse_map")
.def_readonly("button", &mouse_map::button, "")
;

py::class_<scroll_bar_info>(m, "scroll_bar_info")
.def_readwrite("proportional", &scroll_bar_info::proportional, "")
.def_readwrite("double_arrows", &scroll_bar_info::double_arrows, "")
.def_readwrite("knob", &scroll_bar_info::knob, "")
.def_readwrite("min_knob_size", &scroll_bar_info::min_knob_size, "")
;

m.def("get_deskbar_frame", &get_deskbar_frame, "", py::arg("frame"));

m.def("system_colors", &system_colors, "");

m.def("set_screen_space", &set_screen_space, "", py::arg("index"), py::arg("resolution"), py::arg("save")=true);

m.def("get_scroll_bar_info", &get_scroll_bar_info, "", py::arg("info"));

m.def("set_scroll_bar_info", &set_scroll_bar_info, "", py::arg("info"));


//#if (B_HAIKU_VERSION > B_HAIKU_VERSION_1_BETA_4)
m.def("get_mouse_type", py::overload_cast<int32*>(&get_mouse_type), "", py::arg("type"));
m.def("get_mouse_type", py::overload_cast<const char *, int32*>(&get_mouse_type), "", py::arg("mouse_name"), py::arg("type"));
//#endif

m.def("set_mouse_type", &set_mouse_type, "", py::arg("mouse_name"), py::arg("type"));

#if (B_HAIKU_VERSION > B_HAIKU_VERSION_1_BETA_4)
m.def("get_mouse_map", py::overload_cast<mouse_map*>(&get_mouse_map), "", py::arg("map"));
m.def("get_mouse_map", py::overload_cast<const char* ,mouse_map*>(&get_mouse_map), "",py::arg("mouse_name"), py::arg("map"));
#else
m.def("get_mouse_map", &get_mouse_map, "", py::arg("map"));
#endif

#if (B_HAIKU_VERSION > B_HAIKU_VERSION_1_BETA_4)
m.def("set_mouse_map", py::overload_cast<mouse_map*>(&set_mouse_map), "", py::arg("map"));
m.def("set_mouse_map", py::overload_cast<const char* ,mouse_map*>(&set_mouse_map), "", py::arg("mouse_name"), py::arg("map"));
#else
m.def("set_mouse_map", &set_mouse_map, "", py::arg("map"));
#endif

#if (B_HAIKU_VERSION > B_HAIKU_VERSION_1_BETA_4)
m.def("get_click_speed", py::overload_cast<bigtime_t*>(&get_click_speed), "", py::arg("speed"));
m.def("get_click_speed", py::overload_cast<const char*, bigtime_t*>(&get_click_speed), "", py::arg("mouse_name"), py::arg("speed"));
#else
m.def("get_click_speed", &get_click_speed, "", py::arg("speed"));
#endif

#if (B_HAIKU_VERSION > B_HAIKU_VERSION_1_BETA_4)
m.def("set_click_speed", py::overload_cast<bigtime_t>(&set_click_speed), "", py::arg("speed"));
m.def("set_click_speed", py::overload_cast<const char*, bigtime_t>(&set_click_speed), "", py::arg("mouse_name"), py::arg("speed"));
#else
m.def("set_click_speed", &set_click_speed, "", py::arg("speed"));
#endif

m.def("get_mouse_speed", py::overload_cast<int32*>(&get_mouse_speed), "", py::arg("speed"));
m.def("get_mouse_speed", py::overload_cast<const char *, int32*>(&get_mouse_speed), "", py::arg("mouse_name"), py::arg("speed"));

m.def("set_mouse_speed", &set_mouse_speed, "", py::arg("mouse_name"), py::arg("speed"));

m.def("get_mouse_acceleration", py::overload_cast<int32*>(&get_mouse_acceleration), "", py::arg("speed"));
m.def("get_mouse_acceleration", py::overload_cast<const char *, int32*>(&get_mouse_acceleration), "", py::arg("mouse_name"), py::arg("speed"));

m.def("set_mouse_acceleration", &set_mouse_acceleration, "", py::arg("mouse_name"), py::arg("speed"));

m.def("get_key_repeat_rate", &get_key_repeat_rate, "", py::arg("rate"));

m.def("set_key_repeat_rate", &set_key_repeat_rate, "", py::arg("rate"));

m.def("get_key_repeat_delay", &get_key_repeat_delay, "", py::arg("delay"));

m.def("set_key_repeat_delay", &set_key_repeat_delay, "", py::arg("delay"));

m.def("modifiers", &modifiers, "");

m.def("get_key_info", &get_key_info, "", py::arg("info"));

//m.def("get_key_map", &get_key_map, "", py::arg("_map"), py::arg("_keyBuffer"));

m.def("get_keyboard_id", &get_keyboard_id, "", py::arg("_id"));

m.def("get_modifier_key", &get_modifier_key, "", py::arg("modifier"), py::arg("key"));

m.def("set_modifier_key", &set_modifier_key, "", py::arg("modifier"), py::arg("key"));

m.def("set_keyboard_locks", &set_keyboard_locks, "", py::arg("modifiers"));

m.def("keyboard_navigation_color", &keyboard_navigation_color, "");

m.def("count_workspaces", &count_workspaces, "");

m.def("set_workspace_count", &set_workspace_count, "", py::arg("count"));

m.def("current_workspace", &current_workspace, "");

m.def("activate_workspace", &activate_workspace, "", py::arg("workspace"));

m.def("idle_time", &idle_time, "");

m.def("run_select_printer_panel", &run_select_printer_panel, "");

m.def("run_add_printer_panel", &run_add_printer_panel, "");

m.def("run_be_about", &run_be_about, "");

m.def("set_focus_follows_mouse", &set_focus_follows_mouse, "", py::arg("follow"));

m.def("focus_follows_mouse", &focus_follows_mouse, "");

m.def("set_mouse_mode", &set_mouse_mode, "", py::arg("mode"));

m.def("mouse_mode", &mouse_mode, "");

m.def("set_focus_follows_mouse_mode", &set_focus_follows_mouse_mode, "", py::arg("mode"));

m.def("focus_follows_mouse_mode", &focus_follows_mouse_mode, "");

m.def("get_mouse", &get_mouse, "", py::arg("screenWhere"), py::arg("buttons"));

//m.def("get_mouse_bitmap", &get_mouse_bitmap, "", py::arg("bitmap"), py::arg("hotspot"));

m.def("set_accept_first_click", &set_accept_first_click, "", py::arg("acceptFirstClick"));

m.def("accept_first_click", &accept_first_click, "");

m.def("ui_color", &ui_color, "", py::arg("which"));

m.def("ui_color_name", &ui_color_name, "", py::arg("which"));

m.def("which_ui_color", &which_ui_color, "", py::arg("name"));

m.def("set_ui_color", &set_ui_color, "", py::arg("which"), py::arg("color"));

m.def("set_ui_colors", &set_ui_colors, "", py::arg("colors"));

m.def("tint_color", &tint_color, "", py::arg("color"), py::arg("tint"));

m.def("_init_interface_kit_", &_init_interface_kit_, "");

}
