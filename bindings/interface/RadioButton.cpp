#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/RadioButton.h>
#include <Bitmap.h>
#include <Control.h>

namespace py = pybind11;


PYBIND11_MODULE(RadioButton,m)
{
py::class_<BRadioButton, BControl>(m, "BRadioButton")
.def(py::init<BRect, const char *, const char *, BMessage *, unsigned int, unsigned int>(), "", py::arg("frame"), py::arg("name"), py::arg("label"), py::arg("message"), py::arg("resizingMode")=B_FOLLOW_LEFT_TOP, py::arg("flags")=B_WILL_DRAW | B_NAVIGABLE)
.def(py::init<const char *, const char *, BMessage *, unsigned int>(), "", py::arg("name"), py::arg("label"), py::arg("message"), py::arg("flags")=B_WILL_DRAW | B_NAVIGABLE)
.def(py::init<const char *, BMessage *>(), "", py::arg("label"), py::arg("message"))
.def(py::init<BMessage *>(), "", py::arg("data"))
.def_static("Instantiate", &BRadioButton::Instantiate, "", py::arg("data"))
.def("Archive", &BRadioButton::Archive, "", py::arg("data"), py::arg("deep")=true)
.def("Draw", &BRadioButton::Draw, "", py::arg("updateRect"))
.def("MouseDown", &BRadioButton::MouseDown, "", py::arg("where"))
.def("AttachedToWindow", &BRadioButton::AttachedToWindow, "")
.def("KeyDown", &BRadioButton::KeyDown, "", py::arg("bytes"), py::arg("numBytes"))
.def("SetValue", &BRadioButton::SetValue, "", py::arg("value"))
.def("GetPreferredSize", &BRadioButton::GetPreferredSize, "", py::arg("_width"), py::arg("_height"))
.def("ResizeToPreferred", &BRadioButton::ResizeToPreferred, "")
.def("Invoke", &BRadioButton::Invoke, "", py::arg("message")=NULL)
.def("MessageReceived", &BRadioButton::MessageReceived, "", py::arg("message"))
.def("WindowActivated", &BRadioButton::WindowActivated, "", py::arg("active"))
.def("MouseUp", &BRadioButton::MouseUp, "", py::arg("where"))
.def("MouseMoved", &BRadioButton::MouseMoved, "", py::arg("where"), py::arg("code"), py::arg("dragMessage"))
.def("DetachedFromWindow", &BRadioButton::DetachedFromWindow, "")
.def("FrameMoved", &BRadioButton::FrameMoved, "", py::arg("newPosition"))
.def("FrameResized", &BRadioButton::FrameResized, "", py::arg("newWidth"), py::arg("newHeight"))
.def("ResolveSpecifier", &BRadioButton::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("what"), py::arg("property"))
.def("MakeFocus", &BRadioButton::MakeFocus, "", py::arg("focus")=true)
.def("AllAttached", &BRadioButton::AllAttached, "")
.def("AllDetached", &BRadioButton::AllDetached, "")
.def("GetSupportedSuites", &BRadioButton::GetSupportedSuites, "", py::arg("message"))
.def("Perform", &BRadioButton::Perform, "", py::arg("d"), py::arg("argument"))
.def("MaxSize", &BRadioButton::MaxSize, "")
.def("LayoutAlignment", &BRadioButton::LayoutAlignment, "")
.def("SetIcon", &BRadioButton::SetIcon, "", py::arg("icon"), py::arg("flags")=0)
;


}
