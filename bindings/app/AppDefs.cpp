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

py::enum_<system_message_code>(m, "system_message_code", R"doc(
Standard system message codes for basic application events.
)doc")
.value("B_ABOUT_REQUESTED", system_message_code::B_ABOUT_REQUESTED, R"doc(Message code when the user requests an application's 'About' box.)doc")
.value("B_WINDOW_ACTIVATED", system_message_code::B_WINDOW_ACTIVATED, R"doc(Message code when a window gains or loses focus.)doc")
.value("B_APP_ACTIVATED", system_message_code::B_APP_ACTIVATED, R"doc(Message code when an application is activated.)doc")
.value("B_ARGV_RECEIVED", system_message_code::B_ARGV_RECEIVED, R"doc(Message code when the application is launched with arguments.)doc")
.value("B_QUIT_REQUESTED", system_message_code::B_QUIT_REQUESTED, R"doc(Message code when there's a request for closing a window or the application.)doc")
.value("B_CLOSE_REQUESTED", system_message_code::B_CLOSE_REQUESTED, R"doc(Message code when there's a request for a window to close.)doc")
.value("B_CANCEL", system_message_code::B_CANCEL, R"doc(Message code when an action has been cancelled by user interaction.)doc")
.value("B_INVALIDATE", system_message_code::B_INVALIDATE, R"doc(Message code when there's a request for redrawing a view.)doc")
.value("B_KEY_DOWN", system_message_code::B_KEY_DOWN, R"doc(Message code when a key has been pressed.)doc")
.value("B_KEY_UP", system_message_code::B_KEY_UP, R"doc(Message code when a key has been released.)doc")
.value("B_UNMAPPED_KEY_DOWN", system_message_code::B_UNMAPPED_KEY_DOWN, R"doc(Message code when an unmapped key has been pressed.)doc")
.value("B_UNMAPPED_KEY_UP", system_message_code::B_UNMAPPED_KEY_UP, R"doc(Message code when an unmapped key has been released.)doc")
.value("B_KEY_MAP_LOADED", system_message_code::B_KEY_MAP_LOADED, R"doc(Message code when a keymap has been loaded/reloaded.)doc")
.value("B_LAYOUT_WINDOW", system_message_code::B_LAYOUT_WINDOW, R"doc(Message code when the layout of the window has been changed.)doc")
.value("B_MODIFIERS_CHANGED", system_message_code::B_MODIFIERS_CHANGED, R"doc(Message code when the state of modifier keys (Shift, Ctrl, etc.) changes.)doc")
.value("B_MINIMIZE", system_message_code::B_MINIMIZE, R"doc(Message code when a window is minimized.)doc")
.value("B_MOUSE_DOWN", system_message_code::B_MOUSE_DOWN, R"doc(Message code when a mouse button is pressed.)doc")
.value("B_MOUSE_MOVED", system_message_code::B_MOUSE_MOVED, R"doc(Message code when the mouse moves.)doc")
.value("B_MOUSE_ENTER_EXIT", system_message_code::B_MOUSE_ENTER_EXIT, R"doc(Message code when the mouse enters or exits a view.)doc")
.value("B_MOUSE_IDLE", system_message_code::B_MOUSE_IDLE, R"doc(Message code when the mouse has been idle for some time.)doc")
.value("B_MOUSE_UP", system_message_code::B_MOUSE_UP, R"doc(Message code when a mouse button is released.)doc")
.value("B_MOUSE_WHEEL_CHANGED", system_message_code::B_MOUSE_WHEEL_CHANGED, R"doc(Message code when the mouse wheel is scrolled.)doc")
.value("B_OPEN_IN_WORKSPACE", system_message_code::B_OPEN_IN_WORKSPACE, R"doc(Internal message related to opening windows in specific workspaces.)doc")
.value("B_PACKAGE_UPDATE", system_message_code::B_PACKAGE_UPDATE, R"doc(Message code that notifies changes in the Haiku package system.)doc")
.value("B_PRINTER_CHANGED", system_message_code::B_PRINTER_CHANGED, R"doc(Message code when printer status changes.)doc")
.value("B_PULSE", system_message_code::B_PULSE, R"doc(Periodic message code sent to BViews, BWindows, BHandlers or (enabled) BApplications by App Server for background tasks.)doc")
.value("B_READY_TO_RUN", system_message_code::B_READY_TO_RUN, R"doc(Message code sent by the BApplication when it is ready to handle messages. )doc")
.value("B_REFS_RECEIVED", system_message_code::B_REFS_RECEIVED, R"doc(Message code when files (entry_ref) are dropped onto the application or opened.)doc")
.value("B_RELEASE_OVERLAY_LOCK", system_message_code::B_RELEASE_OVERLAY_LOCK, R"doc(Message code for internal graphics message.)doc")
.value("B_ACQUIRE_OVERLAY_LOCK", system_message_code::B_ACQUIRE_OVERLAY_LOCK, R"doc(Message code for internal graphics message.)doc")
.value("B_SCREEN_CHANGED", system_message_code::B_SCREEN_CHANGED, R"doc(Message code when screen resolution or depth has been changed.)doc")
.value("B_VALUE_CHANGED", system_message_code::B_VALUE_CHANGED, R"doc(Message code when a control's value has changed.)doc")
.value("B_TRANSLATOR_ADDED", system_message_code::B_TRANSLATOR_ADDED, R"doc(Message code when there's a new installed translator.)doc")
.value("B_TRANSLATOR_REMOVED", system_message_code::B_TRANSLATOR_REMOVED, R"doc(Message code when an installed translator has been removed.)doc")
.value("B_DELETE_TRANSLATOR", system_message_code::B_DELETE_TRANSLATOR, R"doc(Message code when there's a reequest to delete a translator.)doc")
.value("B_VIEW_MOVED", system_message_code::B_VIEW_MOVED, R"doc(Message code sent after a BView has been moved.)doc")
.value("B_VIEW_RESIZED", system_message_code::B_VIEW_RESIZED, R"doc(Message code sent after a BView has been resized.)doc")
.value("B_WINDOW_MOVED", system_message_code::B_WINDOW_MOVED, R"doc(Message code sent after a BWindow has been moved.)doc")
.value("B_WINDOW_RESIZED", system_message_code::B_WINDOW_RESIZED, R"doc(Message code sent after a BWindow has been resized.)doc")
.value("B_WORKSPACES_CHANGED", system_message_code::B_WORKSPACES_CHANGED, R"doc(Message code sent when available workspaces change.)doc")
.value("B_WORKSPACE_ACTIVATED", system_message_code::B_WORKSPACE_ACTIVATED, R"doc(Message code when the active workspace changes.)doc")
.value("B_ZOOM", system_message_code::B_ZOOM, R"doc(Message code sent when user clicks the Zoom button on the title, maximizing or restoring the window size.)doc")
.value("B_COLORS_UPDATED", system_message_code::B_COLORS_UPDATED, R"doc(Message code when system color settings change.)doc")
.value("B_FONTS_UPDATED", system_message_code::B_FONTS_UPDATED, R"doc(Message code when system font settings change.)doc")
.value("B_TRACKER_ADDON_MESSAGE", system_message_code::B_TRACKER_ADDON_MESSAGE, R"doc(essage intended for Tracker add-ons.)doc")
.value("_APP_MENU_", system_message_code::_APP_MENU_, R"doc(Internal message related to the application menu.)doc")
.value("_BROWSER_MENUS_", system_message_code::_BROWSER_MENUS_, R"doc(Internal message related to browser menus.)doc")
.value("_MENU_EVENT_", system_message_code::_MENU_EVENT_, R"doc(Internal message related to menu events.)doc")
.value("_PING_", system_message_code::_PING_, R"doc(Internal message for checking validity and reactivity of a looper.)doc")
.value("_QUIT_", system_message_code::_QUIT_, R"doc(Internal message sent after B_QUIT_REQUESTED has been approved.)doc")
.value("_VOLUME_MOUNTED_", system_message_code::_VOLUME_MOUNTED_, R"doc(Internal message when a new volume has been mounted.)doc")
.value("_VOLUME_UNMOUNTED_", system_message_code::_VOLUME_UNMOUNTED_, R"doc(Internal message when a volume has been unmounted.)doc")
.value("_MESSAGE_DROPPED_", system_message_code::_MESSAGE_DROPPED_, R"doc(Internal message sent when a drag-and-drop operation is dropped onto a view but no handler accepts it.)doc")
.value("_DISPOSE_DRAG_", system_message_code::_DISPOSE_DRAG_, R"doc(Internal system message used to finalize and dispose of a drag-and-drop operation.)doc")
.value("_MENUS_DONE_", system_message_code::_MENUS_DONE_, R"doc(Internal message indicating that menu event tracking is complete.)doc")
.value("_SHOW_DRAG_HANDLES_", system_message_code::_SHOW_DRAG_HANDLES_, R"doc(Internal message to show drag handles.)doc")
.value("_EVENTS_PENDING_", system_message_code::_EVENTS_PENDING_, R"doc(Internal message notifying the window of pending events.)doc")
.value("_UPDATE_", system_message_code::_UPDATE_, R"doc(Internal message requesting a window redraw/update.)doc")
.value("_UPDATE_IF_NEEDED_", system_message_code::_UPDATE_IF_NEEDED_, R"doc(Internal message requesting a redraw only if an update is required.)doc")
.value("_PRINTER_INFO_", system_message_code::_PRINTER_INFO_, R"doc(Internal message used to retrieve printer information.)doc")
.value("_SETUP_PRINTER_", system_message_code::_SETUP_PRINTER_, R"doc(Internal message invoking the printer setup operation.)doc")
.value("_SELECT_PRINTER_", system_message_code::_SELECT_PRINTER_, R"doc(Internal message requesting printer selection.)doc")
.export_values();

py::enum_<command_code>(m, "command_code", R"doc(Standard command and scripting message codes used by the Haiku messaging system.)doc")
.value("B_SET_PROPERTY", command_code::B_SET_PROPERTY, R"doc(Command to set a property on a target object via the scripting interface.)doc")
.value("B_GET_PROPERTY", command_code::B_GET_PROPERTY, R"doc(Command to retrieve a property from a target object via the scripting interface.)doc")
.value("B_CREATE_PROPERTY", command_code::B_CREATE_PROPERTY, R"doc(Command requesting the creation of a new property within a target object.)doc")
.value("B_DELETE_PROPERTY", command_code::B_DELETE_PROPERTY, R"doc(Command requesting deletion of an existing property.)doc")
.value("B_COUNT_PROPERTIES", command_code::B_COUNT_PROPERTIES, R"doc(Command requesting the number of properties supported by a target object.)doc")
.value("B_EXECUTE_PROPERTY", command_code::B_EXECUTE_PROPERTY, R"doc(Command requesting execution of a callable property (method) on the target object.)doc")
.value("B_GET_SUPPORTED_SUITES", command_code::B_GET_SUPPORTED_SUITES, R"doc(Command used by scripting to query the suites and messages supported by an object.)doc")
.value("B_UNDO", command_code::B_UNDO, R"doc(Command to undo the last operation.)doc")
.value("B_REDO", command_code::B_REDO, R"doc(Command to redo the last undone operation.)doc")
.value("B_CUT", command_code::B_CUT, R"doc(Command to cut the current selection.)doc")
.value("B_COPY", command_code::B_COPY, R"doc(Command to copy the current selection.)doc")
.value("B_PASTE", command_code::B_PASTE, R"doc(Command to paste clipboard data.)doc")
.value("B_SELECT_ALL", command_code::B_SELECT_ALL, R"doc(Command to select all available content.)doc")
.value("B_SAVE_REQUESTED", command_code::B_SAVE_REQUESTED, R"doc(Command sent when an application or view is asked to save contents.)doc")
.value("B_MESSAGE_NOT_UNDERSTOOD", command_code::B_MESSAGE_NOT_UNDERSTOOD, R"doc(Reply indicating that the received message could not be understood.)doc")
.value("B_NO_REPLY", command_code::B_NO_REPLY, R"doc(Indicates that the message does not expect a reply.)doc")
.value("B_REPLY", command_code::B_REPLY, R"doc(Indicates that the message is a reply to a previous message.)doc")
.value("B_SIMPLE_DATA", command_code::B_SIMPLE_DATA, R"doc(Standard drag-and-drop code for simple text or binary data.)doc")
.value("B_MIME_DATA", command_code::B_MIME_DATA, R"doc(Standard drag-and-drop code for typed (MIME-identified) data.)doc")
.value("B_ARCHIVED_OBJECT", command_code::B_ARCHIVED_OBJECT, R"doc(Message containing an archived BArchivable object.)doc")
.value("B_UPDATE_STATUS_BAR", command_code::B_UPDATE_STATUS_BAR, R"doc(Request to update the status bar.)doc")
.value("B_RESET_STATUS_BAR", command_code::B_RESET_STATUS_BAR, R"doc(Request to reset the status bar.)doc")
.value("B_NODE_MONITOR", command_code::B_NODE_MONITOR, R"doc(Notification message for filesystem node monitoring events.)doc")
.value("B_QUERY_UPDATE", command_code::B_QUERY_UPDATE, R"doc(Notification message for updates to live queries.)doc")
.value("B_ENDORSABLE", command_code::B_ENDORSABLE, R"doc(Internal message used for dealing with endorser/endorsee relationships between objects. Poor documentation)doc")
.value("B_COPY_TARGET", command_code::B_COPY_TARGET, R"doc(Drag-and-drop command indicating that the data should be copied to the drop target.)doc")
.value("B_MOVE_TARGET", command_code::B_MOVE_TARGET, R"doc(Drag-and-drop command indicating that the data should be moved to the drop target.)doc")
.value("B_TRASH_TARGET", command_code::B_TRASH_TARGET, R"doc(Drag-and-drop command indicating that the data should be moved to the Trash.)doc")
.value("B_LINK_TARGET", command_code::B_LINK_TARGET, R"doc(Drag-and-drop command indicating that a symbolic link should be created at the drop target.)doc")
.value("B_INPUT_DEVICES_CHANGED", command_code::B_INPUT_DEVICES_CHANGED, R"doc(Notification that the list or configuration of input devices has changed.)doc")
.value("B_INPUT_METHOD_EVENT", command_code::B_INPUT_METHOD_EVENT, R"doc(Message used for input method (IME) events such as composed text updates.)doc")
.value("B_WINDOW_MOVE_TO", command_code::B_WINDOW_MOVE_TO, R"doc(Command requesting a window be moved to specific screen coordinates.)doc")
.value("B_WINDOW_MOVE_BY", command_code::B_WINDOW_MOVE_BY, R"doc(Command requesting a window be moved by a relative offset.)doc")
.value("B_SILENT_RELAUNCH", command_code::B_SILENT_RELAUNCH, R"doc(Command telling an application to relaunch itself without user interaction.)doc")
.value("B_OBSERVER_NOTICE_CHANGE", command_code::B_OBSERVER_NOTICE_CHANGE, R"doc(Notification message indicating that an observed object has changed state.)doc")
.value("B_CONTROL_INVOKED", command_code::B_CONTROL_INVOKED, R"doc(Notification that a BControl has been invoked (e.g. a button press).)doc")
.value("B_CONTROL_MODIFIED", command_code::B_CONTROL_MODIFIED, R"doc(Notification that a BControl’s value has been modified without being invoked.)doc")
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


