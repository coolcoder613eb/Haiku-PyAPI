#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/StringView.h>
#include <View.h>

namespace py = pybind11;


PYBIND11_MODULE(StringView,m)
{
py::class_<BStringView, BView>(m, "BStringView")
.def(py::init<BRect, const char *, const char *, unsigned int, unsigned int>(), "", py::arg("frame"), py::arg("name"), py::arg("text"), py::arg("resizingMode")=B_FOLLOW_LEFT_TOP, py::arg("flags")=B_WILL_DRAW)
.def(py::init<const char *, const char *, unsigned int>(), "", py::arg("name"), py::arg("text"), py::arg("flags")=B_WILL_DRAW)
.def(py::init<BMessage *>(), "", py::arg("archive"))
.def_static("Instantiate", &BStringView::Instantiate, "", py::arg("archive"))
.def("Archive", &BStringView::Archive, "", py::arg("archive"), py::arg("deep")=true)
.def("SetText", &BStringView::SetText, "", py::arg("text"))
.def("Text", &BStringView::Text, "")
.def("SetAlignment", &BStringView::SetAlignment, "", py::arg("flag"))
.def("Alignment", &BStringView::Alignment, "")
.def("SetTruncation", &BStringView::SetTruncation, "", py::arg("truncationMode"))
.def("Truncation", &BStringView::Truncation, "")
.def("AttachedToWindow", &BStringView::AttachedToWindow, "")
.def("DetachedFromWindow", &BStringView::DetachedFromWindow, "")
.def("AllAttached", &BStringView::AllAttached, "")
.def("AllDetached", &BStringView::AllDetached, "")
.def("MakeFocus", &BStringView::MakeFocus, "", py::arg("focus")=true)
.def("GetPreferredSize", &BStringView::GetPreferredSize, "", py::arg("_width"), py::arg("_height"))
.def("MinSize", &BStringView::MinSize, "")
.def("MaxSize", &BStringView::MaxSize, "")
.def("PreferredSize", &BStringView::PreferredSize, "")
.def("ResizeToPreferred", &BStringView::ResizeToPreferred, "")
.def("LayoutAlignment", &BStringView::LayoutAlignment, "")
.def("FrameMoved", &BStringView::FrameMoved, "", py::arg("newPosition"))
.def("FrameResized", &BStringView::FrameResized, "", py::arg("newWidth"), py::arg("newHeight"))
.def("Draw", &BStringView::Draw, "", py::arg("bounds"))
.def("MessageReceived", &BStringView::MessageReceived, "", py::arg("message"))
.def("MouseDown", &BStringView::MouseDown, "", py::arg("point"))
.def("MouseUp", &BStringView::MouseUp, "", py::arg("point"))
.def("MouseMoved", &BStringView::MouseMoved, "", py::arg("point"), py::arg("transit"), py::arg("dragMessage"))
.def("ResolveSpecifier", &BStringView::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("form"), py::arg("property"))
.def("GetSupportedSuites", &BStringView::GetSupportedSuites, "", py::arg("data"))
.def("SetFont", &BStringView::SetFont, "", py::arg("font"), py::arg("mask")=B_FONT_ALL)
;


}
