#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>
#include <vector>

#include <app/AppDefs.h>
#include <Cursor.h>
#include <BeBuild.h>


namespace py = pybind11;

// calculates the size of an old-style cursor array
int cursor_array_size(const unsigned char cursor[]) {
	int width = cursor[0]; // width in pixels
	int height = cursor[0]; // height in pixels
	int depth = cursor[1]; // number of bits per pixel

	// number of bytes in each section of the data structure
	int header_size = 4;
	int image_mask_size = width * height * depth / 8;
	int transparency_mask_size = width * height * depth / 8;
	
	return header_size + image_mask_size + transparency_mask_size;
}

PYBIND11_MODULE(AppDefs,m)
{
py::module_::import("Be.Cursor");

py::enum_<system_message_code>(m, "system_message_code", "")
.value("B_ABOUT_REQUESTED", system_message_code::B_ABOUT_REQUESTED, "")
.value("B_WINDOW_ACTIVATED", system_message_code::B_WINDOW_ACTIVATED, "")
.value("B_APP_ACTIVATED", system_message_code::B_APP_ACTIVATED, "")
.value("B_ARGV_RECEIVED", system_message_code::B_ARGV_RECEIVED, "")
.value("B_QUIT_REQUESTED", system_message_code::B_QUIT_REQUESTED, "")
.value("B_CLOSE_REQUESTED", system_message_code::B_CLOSE_REQUESTED, "")
.value("B_CANCEL", system_message_code::B_CANCEL, "")
.value("B_INVALIDATE", system_message_code::B_INVALIDATE, "")
.value("B_KEY_DOWN", system_message_code::B_KEY_DOWN, "")
.value("B_KEY_UP", system_message_code::B_KEY_UP, "")
.value("B_UNMAPPED_KEY_DOWN", system_message_code::B_UNMAPPED_KEY_DOWN, "")
.value("B_UNMAPPED_KEY_UP", system_message_code::B_UNMAPPED_KEY_UP, "")
.value("B_KEY_MAP_LOADED", system_message_code::B_KEY_MAP_LOADED, "")
.value("B_LAYOUT_WINDOW", system_message_code::B_LAYOUT_WINDOW, "")
.value("B_MODIFIERS_CHANGED", system_message_code::B_MODIFIERS_CHANGED, "")
.value("B_MINIMIZE", system_message_code::B_MINIMIZE, "")
.value("B_MOUSE_DOWN", system_message_code::B_MOUSE_DOWN, "")
.value("B_MOUSE_MOVED", system_message_code::B_MOUSE_MOVED, "")
.value("B_MOUSE_ENTER_EXIT", system_message_code::B_MOUSE_ENTER_EXIT, "")
.value("B_MOUSE_IDLE", system_message_code::B_MOUSE_IDLE, "")
.value("B_MOUSE_UP", system_message_code::B_MOUSE_UP, "")
.value("B_MOUSE_WHEEL_CHANGED", system_message_code::B_MOUSE_WHEEL_CHANGED, "")
.value("B_OPEN_IN_WORKSPACE", system_message_code::B_OPEN_IN_WORKSPACE, "")
.value("B_PACKAGE_UPDATE", system_message_code::B_PACKAGE_UPDATE, "")
.value("B_PRINTER_CHANGED", system_message_code::B_PRINTER_CHANGED, "")
.value("B_PULSE", system_message_code::B_PULSE, "")
.value("B_READY_TO_RUN", system_message_code::B_READY_TO_RUN, "")
.value("B_REFS_RECEIVED", system_message_code::B_REFS_RECEIVED, "")
.value("B_RELEASE_OVERLAY_LOCK", system_message_code::B_RELEASE_OVERLAY_LOCK, "")
.value("B_ACQUIRE_OVERLAY_LOCK", system_message_code::B_ACQUIRE_OVERLAY_LOCK, "")
.value("B_SCREEN_CHANGED", system_message_code::B_SCREEN_CHANGED, "")
.value("B_VALUE_CHANGED", system_message_code::B_VALUE_CHANGED, "")
.value("B_TRANSLATOR_ADDED", system_message_code::B_TRANSLATOR_ADDED, "")
.value("B_TRANSLATOR_REMOVED", system_message_code::B_TRANSLATOR_REMOVED, "")
.value("B_DELETE_TRANSLATOR", system_message_code::B_DELETE_TRANSLATOR, "")
.value("B_VIEW_MOVED", system_message_code::B_VIEW_MOVED, "")
.value("B_VIEW_RESIZED", system_message_code::B_VIEW_RESIZED, "")
.value("B_WINDOW_MOVED", system_message_code::B_WINDOW_MOVED, "")
.value("B_WINDOW_RESIZED", system_message_code::B_WINDOW_RESIZED, "")
.value("B_WORKSPACES_CHANGED", system_message_code::B_WORKSPACES_CHANGED, "")
.value("B_WORKSPACE_ACTIVATED", system_message_code::B_WORKSPACE_ACTIVATED, "")
.value("B_ZOOM", system_message_code::B_ZOOM, "")
.value("B_COLORS_UPDATED", system_message_code::B_COLORS_UPDATED, "")
.value("B_FONTS_UPDATED", system_message_code::B_FONTS_UPDATED, "")
.value("B_TRACKER_ADDON_MESSAGE", system_message_code::B_TRACKER_ADDON_MESSAGE, "")
.value("_APP_MENU_", system_message_code::_APP_MENU_, "")
.value("_BROWSER_MENUS_", system_message_code::_BROWSER_MENUS_, "")
.value("_MENU_EVENT_", system_message_code::_MENU_EVENT_, "")
.value("_PING_", system_message_code::_PING_, "")
.value("_QUIT_", system_message_code::_QUIT_, "")
.value("_VOLUME_MOUNTED_", system_message_code::_VOLUME_MOUNTED_, "")
.value("_VOLUME_UNMOUNTED_", system_message_code::_VOLUME_UNMOUNTED_, "")
.value("_MESSAGE_DROPPED_", system_message_code::_MESSAGE_DROPPED_, "")
.value("_DISPOSE_DRAG_", system_message_code::_DISPOSE_DRAG_, "")
.value("_MENUS_DONE_", system_message_code::_MENUS_DONE_, "")
.value("_SHOW_DRAG_HANDLES_", system_message_code::_SHOW_DRAG_HANDLES_, "")
.value("_EVENTS_PENDING_", system_message_code::_EVENTS_PENDING_, "")
.value("_UPDATE_", system_message_code::_UPDATE_, "")
.value("_UPDATE_IF_NEEDED_", system_message_code::_UPDATE_IF_NEEDED_, "")
.value("_PRINTER_INFO_", system_message_code::_PRINTER_INFO_, "")
.value("_SETUP_PRINTER_", system_message_code::_SETUP_PRINTER_, "")
.value("_SELECT_PRINTER_", system_message_code::_SELECT_PRINTER_, "")
.export_values();

py::enum_<command_code>(m, "command_code", "")
.value("B_SET_PROPERTY", command_code::B_SET_PROPERTY, "")
.value("B_GET_PROPERTY", command_code::B_GET_PROPERTY, "")
.value("B_CREATE_PROPERTY", command_code::B_CREATE_PROPERTY, "")
.value("B_DELETE_PROPERTY", command_code::B_DELETE_PROPERTY, "")
.value("B_COUNT_PROPERTIES", command_code::B_COUNT_PROPERTIES, "")
.value("B_EXECUTE_PROPERTY", command_code::B_EXECUTE_PROPERTY, "")
.value("B_GET_SUPPORTED_SUITES", command_code::B_GET_SUPPORTED_SUITES, "")
.value("B_UNDO", command_code::B_UNDO, "")
.value("B_REDO", command_code::B_REDO, "")
.value("B_CUT", command_code::B_CUT, "")
.value("B_COPY", command_code::B_COPY, "")
.value("B_PASTE", command_code::B_PASTE, "")
.value("B_SELECT_ALL", command_code::B_SELECT_ALL, "")
.value("B_SAVE_REQUESTED", command_code::B_SAVE_REQUESTED, "")
.value("B_MESSAGE_NOT_UNDERSTOOD", command_code::B_MESSAGE_NOT_UNDERSTOOD, "")
.value("B_NO_REPLY", command_code::B_NO_REPLY, "")
.value("B_REPLY", command_code::B_REPLY, "")
.value("B_SIMPLE_DATA", command_code::B_SIMPLE_DATA, "")
.value("B_MIME_DATA", command_code::B_MIME_DATA, "")
.value("B_ARCHIVED_OBJECT", command_code::B_ARCHIVED_OBJECT, "")
.value("B_UPDATE_STATUS_BAR", command_code::B_UPDATE_STATUS_BAR, "")
.value("B_RESET_STATUS_BAR", command_code::B_RESET_STATUS_BAR, "")
.value("B_NODE_MONITOR", command_code::B_NODE_MONITOR, "")
.value("B_QUERY_UPDATE", command_code::B_QUERY_UPDATE, "")
.value("B_ENDORSABLE", command_code::B_ENDORSABLE, "")
.value("B_COPY_TARGET", command_code::B_COPY_TARGET, "")
.value("B_MOVE_TARGET", command_code::B_MOVE_TARGET, "")
.value("B_TRASH_TARGET", command_code::B_TRASH_TARGET, "")
.value("B_LINK_TARGET", command_code::B_LINK_TARGET, "")
.value("B_INPUT_DEVICES_CHANGED", command_code::B_INPUT_DEVICES_CHANGED, "")
.value("B_INPUT_METHOD_EVENT", command_code::B_INPUT_METHOD_EVENT, "")
.value("B_WINDOW_MOVE_TO", command_code::B_WINDOW_MOVE_TO, "")
.value("B_WINDOW_MOVE_BY", command_code::B_WINDOW_MOVE_BY, "")
.value("B_SILENT_RELAUNCH", command_code::B_SILENT_RELAUNCH, "")
.value("B_OBSERVER_NOTICE_CHANGE", command_code::B_OBSERVER_NOTICE_CHANGE, "")
.value("B_CONTROL_INVOKED", command_code::B_CONTROL_INVOKED, "")
.value("B_CONTROL_MODIFIED", command_code::B_CONTROL_MODIFIED, "")
.export_values();
// old-style cursors
m.attr("B_HAND_CURSOR") = std::vector<unsigned char>(
	B_HAND_CURSOR, B_HAND_CURSOR + cursor_array_size(B_HAND_CURSOR));
m.attr("B_I_BEAM_CURSOR") = std::vector<unsigned char>(
	B_I_BEAM_CURSOR, B_I_BEAM_CURSOR + cursor_array_size(B_I_BEAM_CURSOR));

// new-style cursors
m.attr("B_CURSOR_SYSTEM_DEFAULT") = B_CURSOR_SYSTEM_DEFAULT;
m.attr("B_CURSOR_I_BEAM") = B_CURSOR_I_BEAM;

}


