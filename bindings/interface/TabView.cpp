#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/TabView.h>
#include <View.h>

namespace py = pybind11;

class PyBTab : public BTab{
	public:
        using BTab::BTab;
        status_t			Archive(BMessage* data, bool deep = true) const override {
        	PYBIND11_OVERLOAD(status_t, BTab, Archive, data, deep);
        }
        status_t			Perform(uint32 d, void* arg) override {
        	PYBIND11_OVERLOAD(status_t, BTab, Perform, d, arg);
        }
        void				SetLabel(const char* label) override {
        	PYBIND11_OVERLOAD(void, BTab, SetLabel, label);
        }
        void				Select(BView* owner) override {
        	PYBIND11_OVERLOAD(void, BTab, Select, owner);
        }
        void				Deselect() override {
        	PYBIND11_OVERLOAD(void, BTab, Deselect);
        }
        void				SetEnabled(bool enable) override {
        	PYBIND11_OVERLOAD(void, BTab, SetEnabled, enable);
        }
        void				SetView(BView* view) override {
        	PYBIND11_OVERLOAD(void, BTab, SetView, view);
        }
        void				DrawFocusMark(BView* owner, BRect frame) override {
        	PYBIND11_OVERLOAD(void, BTab, DrawFocusMark, owner, frame);
        }
        void				DrawLabel(BView* owner, BRect frame) override {
        	PYBIND11_OVERLOAD(void, BTab, DrawLabel, owner, frame);
        }
        void				DrawTab(BView* owner, BRect frame, tab_position position, bool full = true) override {
        	PYBIND11_OVERLOAD(void, BTab, DrawTab, owner, frame, position, full);
        }
};

class PyBTabView : public BTabView{
	public:
        using BTabView::BTabView;
        status_t			Archive(BMessage* into, bool deep = true) const override {
        	PYBIND11_OVERLOAD(status_t, BTabView, Archive, into, deep);
        }
        status_t			AllUnarchived(const BMessage* from) override {
        	PYBIND11_OVERLOAD(status_t, BTabView, AllUnarchived, from);
        }
        status_t			Perform(perform_code d, void* arg) override {
        	PYBIND11_OVERLOAD(status_t, BTabView, Perform, d, arg);
        }
        void 				AttachedToWindow() override {
        	PYBIND11_OVERLOAD(void, BTabView, AttachedToWindow);
        }
        void				DetachedFromWindow() override {
        	PYBIND11_OVERLOAD(void, BTabView, DetachedFromWindow);
        }
        void				AllAttached() override {
        	PYBIND11_OVERLOAD(void, BTabView, AllAttached);
        }
        void				AllDetached() override {
        	PYBIND11_OVERLOAD(void, BTabView, AllDetached);
        }
        void 				MessageReceived(BMessage* message) override {
        	PYBIND11_OVERLOAD(void, BTabView, MessageReceived, message);
        }
        void				KeyDown(const char* bytes, int32 numBytes) override {
        	PYBIND11_OVERLOAD(void, BTabView, KeyDown, bytes, numBytes);
        }
        void				MouseDown(BPoint where) override {
        	PYBIND11_OVERLOAD(void, BTabView, MouseDown, where);
        }
        void				MouseUp(BPoint where) override {
        	PYBIND11_OVERLOAD(void, BTabView, MouseUp, where);
        }
        void 				MouseMoved(BPoint where, uint32 transit, const BMessage* dragMessage) override {
        	PYBIND11_OVERLOAD(void, BTabView, MouseMoved, where, transit, dragMessage);
        }
        void				Pulse() override {
        	PYBIND11_OVERLOAD(void, BTabView, Pulse);
        }
        void				Select(int32 index) override {
        	PYBIND11_OVERLOAD(void, BTabView, Select, index);
        }
        void				WindowActivated(bool active) override {
        	PYBIND11_OVERLOAD(void, BTabView, WindowActivated, active);
        }
        void				MakeFocus(bool focused = true) override {
        	PYBIND11_OVERLOAD(void, BTabView, MakeFocus, focused);
        }
        void				SetFocusTab(int32 tab, bool focused) override {
        	PYBIND11_OVERLOAD(void, BTabView, SetFocusTab, tab, focused);
        }
        void				Draw(BRect updateRect) override {
        	PYBIND11_OVERLOAD(void, BTabView, Draw, updateRect);
        }
        BRect				DrawTabs() override {
        	PYBIND11_OVERLOAD(BRect, BTabView, DrawTabs);
        }
        void				DrawBox(BRect selectedTabRect) override {
        	PYBIND11_OVERLOAD(void, BTabView, DrawBox, selectedTabRect);
        }
        BRect				TabFrame(int32 index) const override {
        	PYBIND11_OVERLOAD(BRect, BTabView, TabFrame, index);
        }
        void				SetFlags(uint32 flags) override {
        	PYBIND11_OVERLOAD(void, BTabView, SetFlags, flags);
        }
        void				SetResizingMode(uint32 mode) override {
        	PYBIND11_OVERLOAD(void, BTabView, SetResizingMode, mode);
        }
        void				ResizeToPreferred() override {
        	PYBIND11_OVERLOAD(void, BTabView, ResizeToPreferred);
        }
        void				GetPreferredSize(float* _width, float* _height) override {
        	PYBIND11_OVERLOAD(void, BTabView, GetPreferredSize, _width, _height);
        }
        BSize				MinSize() override {
        	PYBIND11_OVERLOAD(BSize, BTabView, MinSize);
        }
        BSize				MaxSize() override {
        	PYBIND11_OVERLOAD(BSize, BTabView, MaxSize);
        }
        BSize				PreferredSize() override {
        	PYBIND11_OVERLOAD(BSize, BTabView, PreferredSize);
        }
        void 				FrameMoved(BPoint newPosition) override {
        	PYBIND11_OVERLOAD(void, BTabView, FrameMoved, newPosition);
        }
        void				FrameResized(float newWidth, float newHeight) override {
        	PYBIND11_OVERLOAD(void, BTabView, FrameResized, newWidth, newHeight);
        }
        BHandler*			ResolveSpecifier(BMessage* message, int32 index, BMessage* specifier, int32 what, const char* property) override {
        	PYBIND11_OVERLOAD(BHandler*, BTabView, ResolveSpecifier, message, index, specifier, what, property);
        }
        status_t			GetSupportedSuites(BMessage* message) override {
        	PYBIND11_OVERLOAD(status_t, BTabView, GetSupportedSuites, message);
        }
        void				AddTab(BView* target, BTab* tab = NULL) override {
        	PYBIND11_OVERLOAD(void, BTabView, AddTab, target, tab);
        }
        BTab*				RemoveTab(int32 tabIndex) override {
        	PYBIND11_OVERLOAD(BTab*, BTabView, RemoveTab, tabIndex);
        }
        BTab*				TabAt(int32 index) const override {
        	PYBIND11_OVERLOAD(BTab*, BTabView, TabAt, index);
        }
        void				SetTabWidth(button_width width) override {
        	PYBIND11_OVERLOAD(void, BTabView, SetTabWidth, width);
        }
        void				SetTabHeight(float height) override {
        	PYBIND11_OVERLOAD(void, BTabView, SetTabHeight, height);
        }
        void				SetBorder(border_style borderStyle) override {
        	PYBIND11_OVERLOAD(void, BTabView, SetBorder, borderStyle);
        }
        void				SetTabSide(tab_side tabSide) override {
        	PYBIND11_OVERLOAD(void, BTabView, SetTabSide, tabSide);
        }
};


PYBIND11_MODULE(TabView,m)
{
py::enum_<tab_position>(m, "tab_position", "")
.value("B_TAB_FIRST", tab_position::B_TAB_FIRST, "")
.value("B_TAB_FRONT", tab_position::B_TAB_FRONT, "")
.value("B_TAB_ANY", tab_position::B_TAB_ANY, "")
.export_values();

py::class_<BTab, PyBTab, BArchivable,std::unique_ptr<BTab, py::nodelete>>(m, "BTab")
.def(py::init<BView *>(), "", py::arg("contentsView")=NULL)
.def(py::init<BMessage *>(), "", py::arg("archive"))
.def_static("Instantiate", &BTab::Instantiate, "", py::arg("archive"))
.def("Archive", &BTab::Archive, "", py::arg("data"), py::arg("deep")=true)
.def("Perform", &BTab::Perform, "", py::arg("d"), py::arg("arg"))
.def("Label", &BTab::Label, "")
.def("SetLabel", &BTab::SetLabel, "", py::arg("label"))
.def("IsSelected", &BTab::IsSelected, "")
.def("Select", &BTab::Select, "", py::arg("owner"))
.def("Deselect", &BTab::Deselect, "")
.def("SetEnabled", &BTab::SetEnabled, "", py::arg("enable"))
.def("IsEnabled", &BTab::IsEnabled, "")
.def("MakeFocus", &BTab::MakeFocus, "", py::arg("focus")=true)
.def("IsFocus", &BTab::IsFocus, "")
.def("SetView", &BTab::SetView, "", py::arg("view"))
.def("View", &BTab::View, "")
.def("DrawFocusMark", &BTab::DrawFocusMark, "", py::arg("owner"), py::arg("frame"))
.def("DrawLabel", &BTab::DrawLabel, "", py::arg("owner"), py::arg("frame"))
.def("DrawTab", &BTab::DrawTab, "", py::arg("owner"), py::arg("frame"), py::arg("position"), py::arg("full")=true)
//.def_readwrite("Private", &BTab::Private, "")
;

py::class_<BTabView, PyBTabView, BView,std::unique_ptr<BTabView, py::nodelete>>(m, "BTabView")
.def(py::init<const char *, button_width, unsigned int>(), "", py::arg("name"), py::arg("width")=B_WIDTH_FROM_WIDEST, py::arg("flags")=B_FULL_UPDATE_ON_RESIZE | B_WILL_DRAW | B_NAVIGABLE_JUMP | B_FRAME_EVENTS | B_NAVIGABLE)
.def(py::init<BRect, const char *, button_width, unsigned int, unsigned int>(), "", py::arg("frame"), py::arg("name"), py::arg("width")=B_WIDTH_AS_USUAL, py::arg("resizeMask")=B_FOLLOW_ALL, py::arg("flags")=B_FULL_UPDATE_ON_RESIZE | B_WILL_DRAW | B_NAVIGABLE_JUMP | B_FRAME_EVENTS | B_NAVIGABLE)
.def(py::init<BMessage *>(), "", py::arg("archive"))
.def_static("Instantiate", &BTabView::Instantiate, "", py::arg("archive"))
.def("Archive", &BTabView::Archive, "", py::arg("into"), py::arg("deep")=true)
.def("AllUnarchived", &BTabView::AllUnarchived, "", py::arg("from"))
.def("Perform", &BTabView::Perform, "", py::arg("d"), py::arg("arg"))
.def("AttachedToWindow", &BTabView::AttachedToWindow, "")
.def("DetachedFromWindow", &BTabView::DetachedFromWindow, "")
.def("AllAttached", &BTabView::AllAttached, "")
.def("AllDetached", &BTabView::AllDetached, "")
.def("MessageReceived", &BTabView::MessageReceived, "", py::arg("message"))
.def("KeyDown", &BTabView::KeyDown, "", py::arg("bytes"), py::arg("numBytes"))
.def("MouseDown", &BTabView::MouseDown, "", py::arg("where"))
.def("MouseUp", &BTabView::MouseUp, "", py::arg("where"))
.def("MouseMoved", &BTabView::MouseMoved, "", py::arg("where"), py::arg("transit"), py::arg("dragMessage"))
.def("Pulse", &BTabView::Pulse, "")
.def("Select", &BTabView::Select, "", py::arg("index"))
.def("Selection", &BTabView::Selection, "")
.def("WindowActivated", &BTabView::WindowActivated, "", py::arg("active"))
.def("MakeFocus", &BTabView::MakeFocus, "", py::arg("focused")=true)
.def("SetFocusTab", &BTabView::SetFocusTab, "", py::arg("tab"), py::arg("focused"))
.def("FocusTab", &BTabView::FocusTab, "")
.def("Draw", &BTabView::Draw, "", py::arg("updateRect"))
.def("DrawTabs", &BTabView::DrawTabs, "")
.def("DrawBox", &BTabView::DrawBox, "", py::arg("selectedTabRect"))
.def("TabFrame", &BTabView::TabFrame, "", py::arg("index"))
.def("SetFlags", &BTabView::SetFlags, "", py::arg("flags"))
.def("SetResizingMode", &BTabView::SetResizingMode, "", py::arg("mode"))
.def("ResizeToPreferred", &BTabView::ResizeToPreferred, "")
.def("GetPreferredSize", &BTabView::GetPreferredSize, "", py::arg("_width"), py::arg("_height"))
.def("MinSize", &BTabView::MinSize, "")
.def("MaxSize", &BTabView::MaxSize, "")
.def("PreferredSize", &BTabView::PreferredSize, "")
.def("FrameMoved", &BTabView::FrameMoved, "", py::arg("newPosition"))
.def("FrameResized", &BTabView::FrameResized, "", py::arg("newWidth"), py::arg("newHeight"))
.def("ResolveSpecifier", &BTabView::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("what"), py::arg("property"))
.def("GetSupportedSuites", &BTabView::GetSupportedSuites, "", py::arg("message"))
.def("AddTab", &BTabView::AddTab, "", py::arg("target"), py::arg("tab")=NULL)
.def("RemoveTab", &BTabView::RemoveTab, "", py::arg("tabIndex"))
.def("TabAt", &BTabView::TabAt, "", py::arg("index"))
.def("SetTabWidth", &BTabView::SetTabWidth, "", py::arg("width"))
.def("TabWidth", &BTabView::TabWidth, "")
.def("SetTabHeight", &BTabView::SetTabHeight, "", py::arg("height"))
.def("TabHeight", &BTabView::TabHeight, "")
.def("SetBorder", &BTabView::SetBorder, "", py::arg("borderStyle"))
.def("Border", &BTabView::Border, "")
.def("SetTabSide", &BTabView::SetTabSide, "", py::arg("tabSide"))
.def("TabSide", &BTabView::TabSide, "")
.def("ContainerView", &BTabView::ContainerView, "")
.def("CountTabs", &BTabView::CountTabs, "")
.def("ViewForTab", &BTabView::ViewForTab, "", py::arg("tabIndex"))
.def("IndexOf", &BTabView::IndexOf, "", py::arg("tab"))
;


}
