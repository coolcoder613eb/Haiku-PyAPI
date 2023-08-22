#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/CheckBox.h>
#include <Control.h>

namespace py = pybind11;


PYBIND11_MODULE(CheckBox,m)
{
py::class_<BCheckBox, BControl>(m, "BCheckBox")
.def(py::init<BRect, const char *, const char *, BMessage *, unsigned int, unsigned int>(), "", py::arg("frame"), py::arg("name"), py::arg("label"), py::arg("message"), py::arg("resizingMode")=B_FOLLOW_LEFT_TOP, py::arg("flags")=B_WILL_DRAW | B_NAVIGABLE)
.def(py::init<const char *, const char *, BMessage *, unsigned int>(), "", py::arg("name"), py::arg("label"), py::arg("message"), py::arg("flags")=B_WILL_DRAW | B_NAVIGABLE)
.def(py::init<const char *, BMessage *>(), "", py::arg("label"), py::arg("message")=NULL)
.def(py::init<BMessage *>(), "", py::arg("data"))
.def_static("Instantiate", &BCheckBox::Instantiate, "", py::arg("data"))
.def("Archive", &BCheckBox::Archive, "", py::arg("data"), py::arg("deep")=true)
.def("Draw", &BCheckBox::Draw, "", py::arg("updateRect"))
.def("AttachedToWindow", &BCheckBox::AttachedToWindow, "")
.def("DetachedFromWindow", &BCheckBox::DetachedFromWindow, "")
.def("AllAttached", &BCheckBox::AllAttached, "")
.def("AllDetached", &BCheckBox::AllDetached, "")
.def("FrameMoved", &BCheckBox::FrameMoved, "", py::arg("newPosition"))
.def("FrameResized", &BCheckBox::FrameResized, "", py::arg("newWidth"), py::arg("newHeight"))
.def("WindowActivated", &BCheckBox::WindowActivated, "", py::arg("active"))
.def("MessageReceived", &BCheckBox::MessageReceived, "", py::arg("message"))
.def("KeyDown", &BCheckBox::KeyDown, "", py::arg("bytes"), py::arg("numBytes"))
.def("MouseDown", &BCheckBox::MouseDown, "", py::arg("where"))
.def("MouseUp", &BCheckBox::MouseUp, "", py::arg("where"))
.def("MouseMoved", &BCheckBox::MouseMoved, "", py::arg("where"), py::arg("code"), py::arg("dragMessage"))
.def("GetPreferredSize", &BCheckBox::GetPreferredSize, "", py::arg("_width"), py::arg("_height"))
.def("ResizeToPreferred", &BCheckBox::ResizeToPreferred, "")
.def("MinSize", &BCheckBox::MinSize, "")
.def("MaxSize", &BCheckBox::MaxSize, "")
.def("PreferredSize", &BCheckBox::PreferredSize, "")
.def("LayoutAlignment", &BCheckBox::LayoutAlignment, "")
.def("MakeFocus", &BCheckBox::MakeFocus, "", py::arg("focused")=true)
.def("SetValue", &BCheckBox::SetValue, "", py::arg("value"))
.def("Invoke", &BCheckBox::Invoke, "", py::arg("message")=NULL)
.def("ResolveSpecifier", &BCheckBox::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("what"), py::arg("property"))
.def("GetSupportedSuites", &BCheckBox::GetSupportedSuites, "", py::arg("message"))
.def("Perform", &BCheckBox::Perform, "", py::arg("code"), py::arg("data"))
.def("SetIcon", &BCheckBox::SetIcon, "", py::arg("icon"), py::arg("flags")=0)
.def("IsPartialStateToOff", &BCheckBox::IsPartialStateToOff, "")
.def("SetPartialStateToOff", &BCheckBox::SetPartialStateToOff, "", py::arg("partialToOff"))
;


}
