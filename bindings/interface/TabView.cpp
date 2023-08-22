#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/TabView.h>
#include <View.h>

namespace py = pybind11;


PYBIND11_MODULE(TabView,m)
{
py::enum_<tab_position>(m, "tab_position", "")
.value("B_TAB_FIRST", tab_position::B_TAB_FIRST, "")
.value("B_TAB_FRONT", tab_position::B_TAB_FRONT, "")
.value("B_TAB_ANY", tab_position::B_TAB_ANY, "")
.export_values();

py::class_<BTab, BArchivable>(m, "BTab")
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
.def_readwrite("Private", &BTab::Private, "")
;

py::class_<BTabView, BView>(m, "BTabView")
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
