#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/MenuBar.h>
#include <InterfaceDefs.h>
#include <Menu.h>
#include <OS.h>

namespace py = pybind11;


PYBIND11_MODULE(MenuBar,m)
{
py::enum_<menu_bar_border>(m, "menu_bar_border", "")
.value("B_BORDER_FRAME", menu_bar_border::B_BORDER_FRAME, "")
.value("B_BORDER_CONTENTS", menu_bar_border::B_BORDER_CONTENTS, "")
.value("B_BORDER_EACH_ITEM", menu_bar_border::B_BORDER_EACH_ITEM, "")
.export_values();

py::class_<BMenuBar, BMenu>(m, "BMenuBar")
.def(py::init<BRect, const char *, unsigned int, menu_layout, bool>(), "", py::arg("frame"), py::arg("name"), py::arg("resizingMode")=B_FOLLOW_LEFT_RIGHT | B_FOLLOW_TOP, py::arg("layout")=B_ITEMS_IN_ROW, py::arg("resizeToFit")=true)
.def(py::init<const char *, menu_layout, unsigned int>(), "", py::arg("name"), py::arg("layout")=B_ITEMS_IN_ROW, py::arg("flags")=B_WILL_DRAW | B_FRAME_EVENTS)
.def(py::init<BMessage *>(), "", py::arg("archive"))
.def_static("Instantiate", &BMenuBar::Instantiate, "", py::arg("archive"))
.def("Archive", &BMenuBar::Archive, "", py::arg("archive"), py::arg("deep")=true)
.def("AttachedToWindow", &BMenuBar::AttachedToWindow, "")
.def("DetachedFromWindow", &BMenuBar::DetachedFromWindow, "")
.def("AllAttached", &BMenuBar::AllAttached, "")
.def("AllDetached", &BMenuBar::AllDetached, "")
.def("WindowActivated", &BMenuBar::WindowActivated, "", py::arg("state"))
.def("MakeFocus", &BMenuBar::MakeFocus, "", py::arg("state")=true)
.def("ResizeToPreferred", &BMenuBar::ResizeToPreferred, "")
.def("GetPreferredSize", &BMenuBar::GetPreferredSize, "", py::arg("_width"), py::arg("_height"))
.def("MinSize", &BMenuBar::MinSize, "")
.def("MaxSize", &BMenuBar::MaxSize, "")
.def("PreferredSize", &BMenuBar::PreferredSize, "")
.def("FrameMoved", &BMenuBar::FrameMoved, "", py::arg("newPosition"))
.def("FrameResized", &BMenuBar::FrameResized, "", py::arg("newWidth"), py::arg("newHeight"))
.def("Show", &BMenuBar::Show, "")
.def("Hide", &BMenuBar::Hide, "")
.def("Draw", &BMenuBar::Draw, "", py::arg("updateRect"))
.def("MessageReceived", &BMenuBar::MessageReceived, "", py::arg("message"))
.def("MouseDown", &BMenuBar::MouseDown, "", py::arg("where"))
.def("MouseUp", &BMenuBar::MouseUp, "", py::arg("where"))
.def("ResolveSpecifier", &BMenuBar::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("form"), py::arg("property"))
.def("GetSupportedSuites", &BMenuBar::GetSupportedSuites, "", py::arg("data"))
.def("SetBorder", &BMenuBar::SetBorder, "", py::arg("border"))
.def("Border", &BMenuBar::Border, "")
.def("SetBorders", &BMenuBar::SetBorders, "", py::arg("borders"))
.def("Borders", &BMenuBar::Borders, "")
.def("Perform", &BMenuBar::Perform, "", py::arg("code"), py::arg("data"))
;


}
