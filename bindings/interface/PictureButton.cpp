#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/PictureButton.h>
#include <Control.h>
#include <Picture.h>
#include <Bitmap.h>

namespace py = pybind11;


PYBIND11_MODULE(PictureButton,m)
{
//m.attr("B_ONE_STATE_BUTTON") = 0;
//m.attr("B_TWO_STATE_BUTTON") = 1;
py::enum_<picture_button_behavior>(m, "picture_button_behavior", "")
.value("B_ONE_STATE_BUTTON", picture_button_behavior::B_ONE_STATE_BUTTON, "")
.value("B_TWO_STATE_BUTTON", picture_button_behavior::B_TWO_STATE_BUTTON, "")
.export_values();

py::class_<BPictureButton, BControl,std::unique_ptr<BPictureButton, py::nodelete>>(m, "BPictureButton")
.def(py::init<BRect, const char *, BPicture *, BPicture *, BMessage *, unsigned int, unsigned int, unsigned int>(), "", py::arg("frame"), py::arg("name"), py::arg("off"), py::arg("on"), py::arg("message"), py::arg("behavior")=B_ONE_STATE_BUTTON, py::arg("resizingMode")=B_FOLLOW_LEFT_TOP, py::arg("flgs")=B_WILL_DRAW | B_NAVIGABLE)
.def(py::init<BMessage *>(), "", py::arg("archive"))
.def_static("Instantiate", &BPictureButton::Instantiate, "", py::arg("archive"))
.def("Archive", &BPictureButton::Archive, "", py::arg("archive"), py::arg("deep")=true)
.def("AttachedToWindow", &BPictureButton::AttachedToWindow, "")
.def("DetachedFromWindow", &BPictureButton::DetachedFromWindow, "")
.def("AllAttached", &BPictureButton::AllAttached, "")
.def("AllDetached", &BPictureButton::AllDetached, "")
.def("ResizeToPreferred", &BPictureButton::ResizeToPreferred, "")
.def("GetPreferredSize", &BPictureButton::GetPreferredSize, "", py::arg("_width"), py::arg("_height"))
.def("FrameMoved", &BPictureButton::FrameMoved, "", py::arg("newPosition"))
.def("FrameResized", &BPictureButton::FrameResized, "", py::arg("newWidth"), py::arg("newHeight"))
.def("WindowActivated", &BPictureButton::WindowActivated, "", py::arg("active"))
.def("MakeFocus", &BPictureButton::MakeFocus, "", py::arg("focus")=true)
.def("Draw", &BPictureButton::Draw, "", py::arg("updateRect"))
.def("MessageReceived", &BPictureButton::MessageReceived, "", py::arg("message"))
.def("KeyDown", &BPictureButton::KeyDown, "", py::arg("bytes"), py::arg("numBytes"))
.def("MouseDown", &BPictureButton::MouseDown, "", py::arg("where"))
.def("MouseUp", &BPictureButton::MouseUp, "", py::arg("where"))
.def("MouseMoved", &BPictureButton::MouseMoved, "", py::arg("where"), py::arg("code"), py::arg("dragMessage"))
.def("SetEnabledOn", &BPictureButton::SetEnabledOn, "", py::arg("picture"))
.def("SetEnabledOff", &BPictureButton::SetEnabledOff, "", py::arg("picture"))
.def("SetDisabledOn", &BPictureButton::SetDisabledOn, "", py::arg("picture"))
.def("SetDisabledOff", &BPictureButton::SetDisabledOff, "", py::arg("picture"))
.def("EnabledOn", &BPictureButton::EnabledOn, "")
.def("EnabledOff", &BPictureButton::EnabledOff, "")
.def("DisabledOn", &BPictureButton::DisabledOn, "")
.def("DisabledOff", &BPictureButton::DisabledOff, "")
.def("SetBehavior", &BPictureButton::SetBehavior, "", py::arg("behavior"))
.def("Behavior", &BPictureButton::Behavior, "")
.def("SetValue", &BPictureButton::SetValue, "", py::arg("value"))
.def("Invoke", &BPictureButton::Invoke, "", py::arg("message")=NULL)
.def("ResolveSpecifier", &BPictureButton::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("what"), py::arg("property"))
.def("GetSupportedSuites", &BPictureButton::GetSupportedSuites, "", py::arg("data"))
.def("Perform", &BPictureButton::Perform, "", py::arg("code"), py::arg("data"))
.def("SetIcon", &BPictureButton::SetIcon, "", py::arg("icon"), py::arg("flags")=0)
;


}
