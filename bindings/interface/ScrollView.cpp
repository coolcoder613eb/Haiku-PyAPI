#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/ScrollView.h>
#include <ScrollBar.h>

namespace py = pybind11;


PYBIND11_MODULE(ScrollView,m)
{
py::class_<BScrollView, BView>(m, "BScrollView")
.def(py::init<const char *, BView *, unsigned int, unsigned int, bool, bool, border_style>(), "", py::arg("name"), py::arg("target"), py::arg("resizingMode")=B_FOLLOW_LEFT_TOP, py::arg("flags")=0, py::arg("horizontal")=false, py::arg("vertical")=false, py::arg("border")=B_FANCY_BORDER)
.def(py::init<const char *, BView *, unsigned int, bool, bool, border_style>(), "", py::arg("name"), py::arg("target"), py::arg("flags"), py::arg("horizontal"), py::arg("vertical"), py::arg("border")=B_FANCY_BORDER)
.def(py::init<BMessage *>(), "", py::arg("archive"))
.def_static("Instantiate", &BScrollView::Instantiate, "", py::arg("archive"))
.def("Archive", &BScrollView::Archive, "", py::arg("archive"), py::arg("deep")=true)
.def("AllUnarchived", &BScrollView::AllUnarchived, "", py::arg("archive"))
.def("AllAttached", &BScrollView::AllAttached, "")
.def("AllDetached", &BScrollView::AllDetached, "")
.def("AttachedToWindow", &BScrollView::AttachedToWindow, "")
.def("DetachedFromWindow", &BScrollView::DetachedFromWindow, "")
.def("Draw", &BScrollView::Draw, "", py::arg("updateRect"))
.def("FrameMoved", &BScrollView::FrameMoved, "", py::arg("newPosition"))
.def("FrameResized", &BScrollView::FrameResized, "", py::arg("newWidth"), py::arg("newHeight"))
.def("MessageReceived", &BScrollView::MessageReceived, "", py::arg("message"))
.def("MouseDown", &BScrollView::MouseDown, "", py::arg("where"))
.def("MouseMoved", &BScrollView::MouseMoved, "", py::arg("where"), py::arg("code"), py::arg("dragMessage"))
.def("MouseUp", &BScrollView::MouseUp, "", py::arg("where"))
.def("WindowActivated", &BScrollView::WindowActivated, "", py::arg("active"))
.def("GetPreferredSize", &BScrollView::GetPreferredSize, "", py::arg("_width"), py::arg("_height"))
.def("ResizeToPreferred", &BScrollView::ResizeToPreferred, "")
.def("MakeFocus", &BScrollView::MakeFocus, "", py::arg("focus")=true)
.def("MinSize", &BScrollView::MinSize, "")
.def("MaxSize", &BScrollView::MaxSize, "")
.def("PreferredSize", &BScrollView::PreferredSize, "")
.def("ScrollBar", &BScrollView::ScrollBar, "", py::arg("direction"))
.def("SetBorder", &BScrollView::SetBorder, "", py::arg("border"))
.def("Border", &BScrollView::Border, "")
.def("SetBorders", &BScrollView::SetBorders, "", py::arg("borders"))
.def("Borders", &BScrollView::Borders, "")
.def("SetBorderHighlighted", &BScrollView::SetBorderHighlighted, "", py::arg("highlight"))
.def("IsBorderHighlighted", &BScrollView::IsBorderHighlighted, "")
.def("SetTarget", &BScrollView::SetTarget, "", py::arg("target"))
.def("Target", &BScrollView::Target, "")
.def("ResolveSpecifier", &BScrollView::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("what"), py::arg("property"))
.def("GetSupportedSuites", &BScrollView::GetSupportedSuites, "", py::arg("message"))
.def("Perform", &BScrollView::Perform, "", py::arg("d"), py::arg("arg"))
;


}
