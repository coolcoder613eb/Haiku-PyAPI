#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/Window.h>
#include <Looper.h>
#include <StorageDefs.h>
#include <View.h>
#include <Button.h>
#include <LayoutItem.h>
#include <Layout.h>
#include <MenuBar.h>

namespace py = pybind11;
using namespace BPrivate;

class PyBWindow : public BWindow, py::trampoline_self_life_support {
    public:
        using BWindow::BWindow;
 
        void MessageReceived(BMessage* msg) override {
            PYBIND11_OVERLOAD(
                void,
                BWindow,
                MessageReceived,
                msg
            );
        }
 
        bool QuitRequested() override {
            PYBIND11_OVERLOAD(
                bool,
                BWindow,
                QuitRequested,
            );
        }
        status_t		Archive(BMessage* archive, bool deep = true) const override {
        	PYBIND11_OVERLOAD(status_t, BWindow, Archive, archive, deep);
        }
        void			Quit() override {
			// limit the scope of py::gil_scoped_acquire, otherwise there may
			// be a deadlock, likely due to us holding the lock even after
			// the window thread has terminated.
			{
				py::gil_scoped_acquire acquire;

				// FIXME: What if the Python overload never actually calls
				// BWindow::Quit?
				do_not_delete.release();
			}

			PYBIND11_OVERLOAD(void, BWindow, Quit);
        }
        void			DispatchMessage(BMessage* message, BHandler* handler) override {
        	PYBIND11_OVERLOAD(void, BWindow, DispatchMessage, message, handler);
        }
        void			FrameMoved(BPoint newPosition) override {
        	PYBIND11_OVERLOAD(void, BWindow, FrameMoved, newPosition);
        }
        void			WorkspacesChanged(uint32 oldWorkspaces, uint32 newWorkspaces) override {
        	PYBIND11_OVERLOAD(void, BWindow, WorkspacesChanged, oldWorkspaces, newWorkspaces);
        }
        void			WorkspaceActivated(int32 workspace, bool state) override {
        	PYBIND11_OVERLOAD(void, BWindow, WorkspaceActivated, workspace, state);
        }
        void			FrameResized(float newWidth, float newHeight) override {
        	PYBIND11_OVERLOAD(void, BWindow, FrameResized, newWidth, newHeight);
        }
        void			Minimize(bool minimize) override {
        	PYBIND11_OVERLOAD(void, BWindow, Minimize, minimize);
        }
        void			Zoom(BPoint origin, float width, float height) override {
        	PYBIND11_OVERLOAD(void, BWindow, Zoom, origin, width, height);
        }
        void			ScreenChanged(BRect screenSize, color_space depth) override {
        	PYBIND11_OVERLOAD(void, BWindow, ScreenChanged, screenSize, depth);
        }
        void			MenusBeginning() override {
        	PYBIND11_OVERLOAD(void, BWindow, MenusBeginning);
        }
        void			MenusEnded() override {
        	PYBIND11_OVERLOAD(void, BWindow, MenusEnded);
        }
        void			WindowActivated(bool focus) override {
        	PYBIND11_OVERLOAD(void, BWindow, WindowActivated, focus);
        }
        void			Show() override {
        	PYBIND11_OVERLOAD(void, BWindow, Show);
        }
        void			Hide() override {
        	PYBIND11_OVERLOAD(void, BWindow, Hide);
        }
        BHandler*		ResolveSpecifier(BMessage* message, int32 index, BMessage* specifier, int32 what, const char* property) override {
        	PYBIND11_OVERLOAD(BHandler*, BWindow, ResolveSpecifier, message, index, specifier, what, property);
        }
        status_t		GetSupportedSuites(BMessage* data) override {
        	PYBIND11_OVERLOAD(status_t, BWindow, GetSupportedSuites, data);
        }
        status_t		Perform(perform_code code, void* data) override {
        	PYBIND11_OVERLOAD(status_t, BWindow, Perform, code, data);
        }
        thread_id		Run() override {
			py::gil_scoped_acquire acquire;

			// FIXME: What if the Python overload never actually calls
			// BWindow::Run?
			do_not_delete = py::cast(this);

			PYBIND11_OVERLOAD(thread_id, BWindow, Run);
        }
        void			SetLayout(BLayout* layout) override {
        	PYBIND11_OVERLOAD(void, BWindow, SetLayout, layout);
        }

	private:
		// For an explanation, see do_not_delete in Looper.cpp
		py::object do_not_delete;
};

void QuitWrapper(BWindow& self) {
	// For an explanation, see QuitWrapper in Looper.cpp
	py::gil_scoped_release release;
	self.Quit();
}

PYBIND11_MODULE(Window,m)
{
py::enum_<window_type>(m, "window_type", "")
.value("B_UNTYPED_WINDOW", window_type::B_UNTYPED_WINDOW, "")
.value("B_TITLED_WINDOW", window_type::B_TITLED_WINDOW, "")
.value("B_MODAL_WINDOW", window_type::B_MODAL_WINDOW, "")
.value("B_DOCUMENT_WINDOW", window_type::B_DOCUMENT_WINDOW, "")
.value("B_BORDERED_WINDOW", window_type::B_BORDERED_WINDOW, "")
.value("B_FLOATING_WINDOW", window_type::B_FLOATING_WINDOW, "")
.export_values();

py::enum_<window_look>(m, "window_look", "")
.value("B_BORDERED_WINDOW_LOOK", window_look::B_BORDERED_WINDOW_LOOK, "")
.value("B_NO_BORDER_WINDOW_LOOK", window_look::B_NO_BORDER_WINDOW_LOOK, "")
.value("B_TITLED_WINDOW_LOOK", window_look::B_TITLED_WINDOW_LOOK, "")
.value("B_DOCUMENT_WINDOW_LOOK", window_look::B_DOCUMENT_WINDOW_LOOK, "")
.value("B_MODAL_WINDOW_LOOK", window_look::B_MODAL_WINDOW_LOOK, "")
.value("B_FLOATING_WINDOW_LOOK", window_look::B_FLOATING_WINDOW_LOOK, "")
.export_values();

py::enum_<window_feel>(m, "window_feel", "")
.value("B_NORMAL_WINDOW_FEEL", window_feel::B_NORMAL_WINDOW_FEEL, "")
.value("B_MODAL_SUBSET_WINDOW_FEEL", window_feel::B_MODAL_SUBSET_WINDOW_FEEL, "")
.value("B_MODAL_APP_WINDOW_FEEL", window_feel::B_MODAL_APP_WINDOW_FEEL, "")
.value("B_MODAL_ALL_WINDOW_FEEL", window_feel::B_MODAL_ALL_WINDOW_FEEL, "")
.value("B_FLOATING_SUBSET_WINDOW_FEEL", window_feel::B_FLOATING_SUBSET_WINDOW_FEEL, "")
.value("B_FLOATING_APP_WINDOW_FEEL", window_feel::B_FLOATING_APP_WINDOW_FEEL, "")
.value("B_FLOATING_ALL_WINDOW_FEEL", window_feel::B_FLOATING_ALL_WINDOW_FEEL, "")
.export_values();

py::enum_<window_alignment>(m, "window_alignment", "")
.value("B_BYTE_ALIGNMENT", window_alignment::B_BYTE_ALIGNMENT, "")
.value("B_PIXEL_ALIGNMENT", window_alignment::B_PIXEL_ALIGNMENT, "")
.export_values();

m.attr("B_NOT_MOVABLE") = 1;
m.attr("B_NOT_CLOSABLE") = 32;
m.attr("B_NOT_ZOOMABLE") = 64;
m.attr("B_NOT_MINIMIZABLE") = 16384;
m.attr("B_NOT_RESIZABLE") = 2;
m.attr("B_NOT_H_RESIZABLE") = 4;
m.attr("B_NOT_V_RESIZABLE") = 8;
m.attr("B_AVOID_FRONT") = 128;
m.attr("B_AVOID_FOCUS") = 8192;
m.attr("B_WILL_ACCEPT_FIRST_CLICK") = 16;
m.attr("B_OUTLINE_RESIZE") = 4096;
m.attr("B_NO_WORKSPACE_ACTIVATION") = 256;
m.attr("B_NOT_ANCHORED_ON_ACTIVATE") = 131072;
m.attr("B_ASYNCHRONOUS_CONTROLS") = 524288;
m.attr("B_QUIT_ON_WINDOW_CLOSE") = 1048576;
m.attr("B_SAME_POSITION_IN_ALL_WORKSPACES") = 2097152;
m.attr("B_AUTO_UPDATE_SIZE_LIMITS") = 4194304;
m.attr("B_CLOSE_ON_ESCAPE") = 8388608;
m.attr("B_NO_SERVER_SIDE_WINDOW_MODIFIERS") = 512;

m.attr("B_DO_NOT_RESIZE_TO_FIT") = 1;
m.attr("B_MOVE_IF_PARTIALLY_OFFSCREEN") = 2;

//m.attr("PortLink") = PortLink;

py::class_<BWindow,PyBWindow,BLooper, py::smart_holder>(m, "BWindow")
.def(py::init_alias<BRect, const char *, window_type, uint32, uint32>(), "", py::arg("frame"), py::arg("title"), py::arg("type"), py::arg("flags"), py::arg("workspace")=B_CURRENT_WORKSPACE)
.def(py::init_alias<BRect, const char *, window_look, window_feel, uint32, uint32>(), "", py::arg("frame"), py::arg("title"), py::arg("look"), py::arg("feel"), py::arg("flags"), py::arg("workspace")=B_CURRENT_WORKSPACE)
.def(py::init_alias<BMessage *>(), "", py::arg("archive"))
.def_static("Instantiate", &BWindow::Instantiate, "", py::arg("archive"))
.def("Archive", &BWindow::Archive, "", py::arg("archive"), py::arg("deep")=true)
.def("Quit", &QuitWrapper, "")
.def("Close", &BWindow::Close, "")
.def("AddChild", py::overload_cast<BView *, BView *>(&BWindow::AddChild), "", py::arg("child"), py::arg("before")=NULL)
.def("AddChild", py::overload_cast<BLayoutItem *>(&BWindow::AddChild), "", py::arg("child"))
.def("RemoveChild", &BWindow::RemoveChild, "", py::arg("child"))
.def("CountChildren", &BWindow::CountChildren, "")
.def("ChildAt", &BWindow::ChildAt, "", py::arg("index"))
.def("DispatchMessage", &BWindow::DispatchMessage, "", py::arg("message"), py::arg("handler"))
.def("MessageReceived", &BWindow::MessageReceived, "", py::arg("message"))
.def("FrameMoved", &BWindow::FrameMoved, "", py::arg("newPosition"))
.def("WorkspacesChanged", &BWindow::WorkspacesChanged, "", py::arg("oldWorkspaces"), py::arg("newWorkspaces"))
.def("WorkspaceActivated", &BWindow::WorkspaceActivated, "", py::arg("workspace"), py::arg("state"))
.def("FrameResized", &BWindow::FrameResized, "", py::arg("newWidth"), py::arg("newHeight"))
.def("Minimize", &BWindow::Minimize, "", py::arg("minimize"))
.def("Zoom", py::overload_cast<BPoint, float, float>(&BWindow::Zoom), "", py::arg("origin"), py::arg("width"), py::arg("height"))
.def("Zoom", py::overload_cast<>(&BWindow::Zoom), "")
.def("SetZoomLimits", &BWindow::SetZoomLimits, "", py::arg("maxWidth"), py::arg("maxHeight"))
.def("ScreenChanged", &BWindow::ScreenChanged, "", py::arg("screenSize"), py::arg("depth"))
.def("SetPulseRate", &BWindow::SetPulseRate, "", py::arg("rate"))
.def("PulseRate", &BWindow::PulseRate, "")
.def("AddShortcut", py::overload_cast<uint32, uint32, BMessage *>(&BWindow::AddShortcut), "", py::arg("key"), py::arg("modifiers"), py::arg("message"))
.def("AddShortcut", py::overload_cast<uint32, uint32, BMessage *, BHandler *>(&BWindow::AddShortcut), "", py::arg("key"), py::arg("modifiers"), py::arg("message"), py::arg("target"))
.def("HasShortcut", &BWindow::HasShortcut, "", py::arg("key"), py::arg("modifiers"))
.def("RemoveShortcut", &BWindow::RemoveShortcut, "", py::arg("key"), py::arg("modifiers"))
.def("SetDefaultButton", &BWindow::SetDefaultButton, "", py::arg("button"))
.def("DefaultButton", &BWindow::DefaultButton, "")
.def("MenusBeginning", &BWindow::MenusBeginning, "")
.def("MenusEnded", &BWindow::MenusEnded, "")
.def("NeedsUpdate", &BWindow::NeedsUpdate, "")
.def("UpdateIfNeeded", &BWindow::UpdateIfNeeded, "")
.def("FindView", py::overload_cast<const char *>(&BWindow::FindView, py::const_), "", py::arg("viewName"))
.def("FindView", py::overload_cast<BPoint>(&BWindow::FindView, py::const_), "", py::arg(""))
.def("CurrentFocus", &BWindow::CurrentFocus, "")
.def("Activate", &BWindow::Activate, "", py::arg("bool")=true)
.def("WindowActivated", &BWindow::WindowActivated, "", py::arg("focus"))
.def("ConvertToScreen", py::overload_cast<BPoint *>(&BWindow::ConvertToScreen, py::const_), "", py::arg("point"))
.def("ConvertToScreen", py::overload_cast<BPoint>(&BWindow::ConvertToScreen, py::const_), "", py::arg("point"))
.def("ConvertFromScreen", py::overload_cast<BPoint *>(&BWindow::ConvertFromScreen, py::const_), "", py::arg("point"))
.def("ConvertFromScreen", py::overload_cast<BPoint>(&BWindow::ConvertFromScreen, py::const_), "", py::arg("point"))
.def("ConvertToScreen", py::overload_cast<BRect *>(&BWindow::ConvertToScreen, py::const_), "", py::arg("rect"))
.def("ConvertToScreen", py::overload_cast<BRect>(&BWindow::ConvertToScreen, py::const_), "", py::arg("rect"))
.def("ConvertFromScreen", py::overload_cast<BRect *>(&BWindow::ConvertFromScreen, py::const_), "", py::arg("rect"))
.def("ConvertFromScreen", py::overload_cast<BRect>(&BWindow::ConvertFromScreen, py::const_), "", py::arg("rect"))
.def("MoveBy", &BWindow::MoveBy, "", py::arg("dx"), py::arg("dy"))
.def("MoveTo", py::overload_cast<BPoint>(&BWindow::MoveTo), "", py::arg(""))
.def("MoveTo", py::overload_cast<float, float>(&BWindow::MoveTo), "", py::arg("x"), py::arg("y"))
.def("ResizeBy", &BWindow::ResizeBy, "", py::arg("dx"), py::arg("dy"))
.def("ResizeTo", &BWindow::ResizeTo, "", py::arg("width"), py::arg("height"))
.def("ResizeToPreferred", &BWindow::ResizeToPreferred, "")
.def("CenterIn", &BWindow::CenterIn, "", py::arg("rect"))
.def("CenterOnScreen", py::overload_cast<>(&BWindow::CenterOnScreen), "")
.def("CenterOnScreen", py::overload_cast<screen_id>(&BWindow::CenterOnScreen), "", py::arg("id"))
.def("MoveOnScreen", &BWindow::MoveOnScreen, "", py::arg("flags")=0)
.def("Show", &BWindow::Show, "")
.def("Hide", &BWindow::Hide, "")
.def("IsHidden", &BWindow::IsHidden, "")
.def("IsMinimized", &BWindow::IsMinimized, "")
.def("Flush", &BWindow::Flush, "")
.def("Sync", &BWindow::Sync, "")
.def("SendBehind", &BWindow::SendBehind, "", py::arg("window"))
.def("DisableUpdates", &BWindow::DisableUpdates, "")
.def("EnableUpdates", &BWindow::EnableUpdates, "")
.def("BeginViewTransaction", &BWindow::BeginViewTransaction, "")
.def("EndViewTransaction", &BWindow::EndViewTransaction, "")
.def("InViewTransaction", &BWindow::InViewTransaction, "")
.def("Bounds", &BWindow::Bounds, "")
.def("Frame", &BWindow::Frame, "")
.def("DecoratorFrame", &BWindow::DecoratorFrame, "")
.def("Size", &BWindow::Size, "")
.def("Title", &BWindow::Title, "")
.def("SetTitle", &BWindow::SetTitle, "", py::arg("title"))
.def("IsFront", &BWindow::IsFront, "")
.def("IsActive", &BWindow::IsActive, "")
.def("SetKeyMenuBar", &BWindow::SetKeyMenuBar, "", py::arg("bar"))
.def("KeyMenuBar", &BWindow::KeyMenuBar, "")
.def("SetSizeLimits", &BWindow::SetSizeLimits, "", py::arg("minWidth"), py::arg("maxWidth"), py::arg("minHeight"), py::arg("maxHeight"))
.def("GetSizeLimits", &BWindow::GetSizeLimits, "", py::arg("minWidth"), py::arg("maxWidth"), py::arg("minHeight"), py::arg("maxHeight"))
.def("UpdateSizeLimits", &BWindow::UpdateSizeLimits, "")
.def("SetDecoratorSettings", &BWindow::SetDecoratorSettings, "", py::arg("settings"))
.def("GetDecoratorSettings", &BWindow::GetDecoratorSettings, "", py::arg("settings"))
.def("Workspaces", &BWindow::Workspaces, "")
.def("SetWorkspaces", &BWindow::SetWorkspaces, "", py::arg(""))
.def("LastMouseMovedView", &BWindow::LastMouseMovedView, "")
.def("ResolveSpecifier", &BWindow::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("what"), py::arg("property"))
.def("GetSupportedSuites", &BWindow::GetSupportedSuites, "", py::arg("data"))
.def("AddToSubset", &BWindow::AddToSubset, "", py::arg("window"))
.def("RemoveFromSubset", &BWindow::RemoveFromSubset, "", py::arg("window"))
.def("Perform", &BWindow::Perform, "", py::arg("code"), py::arg("data"))
.def("SetType", &BWindow::SetType, "", py::arg("type"))
.def("Type", &BWindow::Type, "")
.def("SetLook", &BWindow::SetLook, "", py::arg("look"))
.def("Look", &BWindow::Look, "")
.def("SetFeel", &BWindow::SetFeel, "", py::arg("feel"))
.def("Feel", &BWindow::Feel, "")
.def("SetFlags", &BWindow::SetFlags, "", py::arg(""))
.def("Flags", &BWindow::Flags, "")
.def("IsModal", &BWindow::IsModal, "")
.def("IsFloating", &BWindow::IsFloating, "")
.def("SetWindowAlignment", &BWindow::SetWindowAlignment, "", py::arg("mode"), py::arg("h"), py::arg("hOffset")=0, py::arg("width")=0, py::arg("widthOffset")=0, py::arg("v")=0, py::arg("vOffset")=0, py::arg("height")=0, py::arg("heightOffset")=0)
.def("GetWindowAlignment", &BWindow::GetWindowAlignment, "", py::arg("mode")=NULL, py::arg("h")=NULL, py::arg("hOffset")=NULL, py::arg("width")=NULL, py::arg("widthOffset")=NULL, py::arg("v")=NULL, py::arg("vOffset")=NULL, py::arg("height")=NULL, py::arg("heightOffset")=NULL)
.def("QuitRequested", &BWindow::QuitRequested, "")
.def("Run", &BWindow::Run, "")
.def("SetLayout", &BWindow::SetLayout, "", py::arg("layout"))
.def("GetLayout", &BWindow::GetLayout, "")
.def("InvalidateLayout", &BWindow::InvalidateLayout, "", py::arg("descendants")=false)
.def("Layout", &BWindow::Layout, "", py::arg("force"))
.def("IsOffscreenWindow", &BWindow::IsOffscreenWindow, "")
;


}
