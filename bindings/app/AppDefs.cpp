#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <Cursor.h>
#include <app/AppDefs.h>
#include <BeBuild.h>


namespace py = pybind11;

PYBIND11_MODULE(AppDefs,m)
{
m.attr("B_ABOUT_REQUESTED") = py::int_('_ABR');
m.attr("B_WINDOW_ACTIVATED") = py::int_('_ACT');
m.attr("B_APP_ACTIVATED") = py::int_('_ACT');
m.attr("B_ARGV_RECEIVED") = py::int_('_ARG');
m.attr("B_QUIT_REQUESTED") = py::int_('_QRQ');
m.attr("B_CLOSE_REQUESTED") = py::int_('_QRQ');
m.attr("B_CANCEL") = py::int_('_CNC');
m.attr("B_INVALIDATE") = py::int_('_IVL');
m.attr("B_KEY_DOWN") = py::int_('_KYD');
m.attr("B_KEY_UP") = py::int_('_KYU');
m.attr("B_UNMAPPED_KEY_DOWN") = py::int_('_UKD');
m.attr("B_UNMAPPED_KEY_UP") = py::int_('_UKU');
m.attr("B_KEY_MAP_LOADED") = py::int_('_KML');
m.attr("B_LAYOUT_WINDOW") = py::int_('_LAY');
m.attr("B_MODIFIERS_CHANGED") = py::int_('_MCH');
m.attr("B_MINIMIZE") = py::int_('_WMN');
m.attr("B_MOUSE_DOWN") = py::int_('_MDN');
m.attr("B_MOUSE_MOVED") = py::int_('_MMV');
m.attr("B_MOUSE_ENTER_EXIT") = py::int_('_MEX');
m.attr("B_MOUSE_IDLE") = py::int_('_MSI');
m.attr("B_MOUSE_UP") = py::int_('_MUP');
m.attr("B_MOUSE_WHEEL_CHANGED") = py::int_('_MWC');
m.attr("B_OPEN_IN_WORKSPACE") = py::int_('_OWS');
m.attr("B_PACKAGE_UPDATE") = py::int_('_PKU');
m.attr("B_PRINTER_CHANGED") = py::int_('_PCH');
m.attr("B_PULSE") = py::int_('_PUL');
m.attr("B_READY_TO_RUN") = py::int_('_RTR');
m.attr("B_REFS_RECEIVED") = py::int_('_RRC');
m.attr("B_RELEASE_OVERLAY_LOCK") = py::int_('_ROV');
m.attr("B_ACQUIRE_OVERLAY_LOCK") = py::int_('_AOV');
m.attr("B_SCREEN_CHANGED") = py::int_('_SCH');
m.attr("B_VALUE_CHANGED") = py::int_('_VCH');
m.attr("B_TRANSLATOR_ADDED") = py::int_('_ART');
m.attr("B_TRANSLATOR_REMOVED") = py::int_('_RRT');
m.attr("B_DELETE_TRANSLATOR") = py::int_('_DRT');
m.attr("B_VIEW_MOVED") = py::int_('_VMV');
m.attr("B_VIEW_RESIZED") = py::int_('_VRS');
m.attr("B_WINDOW_MOVED") = py::int_('_WMV');
m.attr("B_WINDOW_RESIZED") = py::int_('_WRS');
m.attr("B_WORKSPACES_CHANGED") = py::int_('_WCG');
m.attr("B_WORKSPACE_ACTIVATED") = py::int_('_WAC');
m.attr("B_ZOOM") = py::int_('_WZM');
m.attr("B_COLORS_UPDATED") = py::int_('_CLU');
m.attr("B_FONTS_UPDATED") = py::int_('_FNU');
m.attr("B_TRACKER_ADDON_MESSAGE") = py::int_('_TAM');
m.attr("_APP_MENU_") = py::int_('_AMN');
m.attr("_BROWSER_MENUS_") = py::int_('_BRM');
m.attr("_MENU_EVENT_") = py::int_('_MEV');
m.attr("_PING_") = py::int_('_PBL');
m.attr("_QUIT_") = py::int_('_QIT');
m.attr("_VOLUME_MOUNTED_") = py::int_('_NVL');
m.attr("_VOLUME_UNMOUNTED_") = py::int_('_VRM');
m.attr("_MESSAGE_DROPPED_") = py::int_('_MDP');
m.attr("_DISPOSE_DRAG_") = py::int_('_DPD');
m.attr("_MENUS_DONE_") = py::int_('_MND');
m.attr("_SHOW_DRAG_HANDLES_") = py::int_('_SDH');
m.attr("_EVENTS_PENDING_") = py::int_('_EVP');
m.attr("_UPDATE_") = py::int_('_UPD');
m.attr("_UPDATE_IF_NEEDED_") = py::int_('_UPN');
m.attr("_PRINTER_INFO_") = py::int_('_PIN');
m.attr("_SETUP_PRINTER_") = py::int_('_SUP');
m.attr("_SELECT_PRINTER_") = py::int_('_PSL');

m.attr("B_SET_PROPERTY") = py::int_('PSET');
m.attr("B_GET_PROPERTY") = py::int_('PGET');
m.attr("B_CREATE_PROPERTY") = py::int_('PCRT');
m.attr("B_DELETE_PROPERTY") = py::int_('PDEL');
m.attr("B_COUNT_PROPERTIES") = py::int_('PCNT');
m.attr("B_EXECUTE_PROPERTY") = py::int_('PEXE');
m.attr("B_GET_SUPPORTED_SUITES") = py::int_('SUIT');
m.attr("B_UNDO") = py::int_('UNDO');
m.attr("B_REDO") = py::int_('REDO');
m.attr("B_CUT") = py::int_('CCUT');
m.attr("B_COPY") = py::int_('COPY');
m.attr("B_PASTE") = py::int_('PSTE');
m.attr("B_SELECT_ALL") = py::int_('SALL');
m.attr("B_SAVE_REQUESTED") = py::int_('SAVE');
m.attr("B_MESSAGE_NOT_UNDERSTOOD") = py::int_('MNOT');
m.attr("B_NO_REPLY") = py::int_('NONE');
m.attr("B_REPLY") = py::int_('RPLY');
m.attr("B_SIMPLE_DATA") = py::int_('DATA');
m.attr("B_MIME_DATA") = py::int_('MIME');
m.attr("B_ARCHIVED_OBJECT") = py::int_('ARCV');
m.attr("B_UPDATE_STATUS_BAR") = py::int_('SBUP');
m.attr("B_RESET_STATUS_BAR") = py::int_('SBRS');
m.attr("B_NODE_MONITOR") = py::int_('NDMN');
m.attr("B_QUERY_UPDATE") = py::int_('QUPD');
m.attr("B_ENDORSABLE") = py::int_('ENDO');
m.attr("B_COPY_TARGET") = py::int_('DDCP');
m.attr("B_MOVE_TARGET") = py::int_('DDMV');
m.attr("B_TRASH_TARGET") = py::int_('DDRM');
m.attr("B_LINK_TARGET") = py::int_('DDLN');
m.attr("B_INPUT_DEVICES_CHANGED") = py::int_('IDCH');
m.attr("B_INPUT_METHOD_EVENT") = py::int_('IMEV');
m.attr("B_WINDOW_MOVE_TO") = py::int_('WDMT');
m.attr("B_WINDOW_MOVE_BY") = py::int_('WDMB');
m.attr("B_SILENT_RELAUNCH") = py::int_('AREL');
m.attr("B_OBSERVER_NOTICE_CHANGE") = py::int_('NTCH');
m.attr("B_CONTROL_INVOKED") = py::int_('CIVK');
m.attr("B_CONTROL_MODIFIED") = py::int_('CMOD');

//m.attr("B_HAND_CURSOR") = B_HAND_CURSOR;
//m.attr("B_I_BEAM_CURSOR") = B_I_BEAM_CURSOR;
//m.attr("B_CURSOR_SYSTEM_DEFAULT") = B_CURSOR_SYSTEM_DEFAULT;
//m.attr("B_CURSOR_I_BEAM") = B_CURSOR_I_BEAM;

}


