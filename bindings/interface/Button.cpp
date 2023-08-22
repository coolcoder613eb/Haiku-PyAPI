#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/Button.h>
#include <Control.h>
#include <Bitmap.h>

namespace py = pybind11;


PYBIND11_MODULE(Button,m)
{
py::class_<BButton,BView>(m, "BButton")
.def(py::init<BRect, const char *, const char *, BMessage *, unsigned int, unsigned int>(), "", py::arg("frame"), py::arg("name"), py::arg("label"), py::arg("message"), py::arg("resizingMode")=B_FOLLOW_LEFT_TOP, py::arg("flags")=B_WILL_DRAW | B_NAVIGABLE | B_FULL_UPDATE_ON_RESIZE)
.def(py::init<const char *, const char *, BMessage *, unsigned int>(), "", py::arg("name"), py::arg("label"), py::arg("message"), py::arg("flags")=B_WILL_DRAW | B_NAVIGABLE | B_FULL_UPDATE_ON_RESIZE)
.def(py::init<const char *, BMessage *>(), "", py::arg("label"), py::arg("message")=NULL)
.def(py::init<BMessage *>(), "", py::arg("data"))
.def_static("Instantiate", &BButton::Instantiate, "", py::arg("data"))
.def("Archive", &BButton::Archive, "", py::arg("data"), py::arg("deep")=true)
.def("Draw", &BButton::Draw, "", py::arg("updateRect"))
.def("MouseDown", &BButton::MouseDown, "", py::arg("where"))
.def("AttachedToWindow", &BButton::AttachedToWindow, "")
.def("KeyDown", &BButton::KeyDown, "", py::arg("bytes"), py::arg("numBytes"))
.def("MakeDefault", &BButton::MakeDefault, "", py::arg("flag"))
.def("SetLabel", &BButton::SetLabel, "", py::arg("string"))
.def("IsDefault", &BButton::IsDefault, "")
.def("IsFlat", &BButton::IsFlat, "")
.def("SetFlat", &BButton::SetFlat, "", py::arg("flat"))
.def("Behavior", &BButton::Behavior, "")
.def("SetBehavior", &BButton::SetBehavior, "", py::arg("behavior"))
.def("PopUpMessage", &BButton::PopUpMessage, "")
.def("SetPopUpMessage", &BButton::SetPopUpMessage, "", py::arg("message"))
.def("MessageReceived", &BButton::MessageReceived, "", py::arg("message"))
.def("WindowActivated", &BButton::WindowActivated, "", py::arg("active"))
.def("MouseMoved", &BButton::MouseMoved, "", py::arg("where"), py::arg("code"), py::arg("dragMessage"))
.def("MouseUp", &BButton::MouseUp, "", py::arg("where"))
.def("DetachedFromWindow", &BButton::DetachedFromWindow, "")
.def("SetValue", &BButton::SetValue, "", py::arg("value"))
.def("GetPreferredSize", &BButton::GetPreferredSize, "", py::arg("_width"), py::arg("_height"))
.def("ResizeToPreferred", &BButton::ResizeToPreferred, "")
.def("Invoke", &BButton::Invoke, "", py::arg("message")=NULL)
.def("FrameMoved", &BButton::FrameMoved, "", py::arg("newPosition"))
.def("FrameResized", &BButton::FrameResized, "", py::arg("newWidth"), py::arg("newHeight"))
.def("MakeFocus", &BButton::MakeFocus, "", py::arg("focus")=true)
.def("AllAttached", &BButton::AllAttached, "")
.def("AllDetached", &BButton::AllDetached, "")
.def("ResolveSpecifier", &BButton::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("what"), py::arg("property"))
.def("GetSupportedSuites", &BButton::GetSupportedSuites, "", py::arg("message"))
.def("Perform", &BButton::Perform, "", py::arg("d"), py::arg("arg"))
.def("MinSize", &BButton::MinSize, "")
.def("MaxSize", &BButton::MaxSize, "")
.def("PreferredSize", &BButton::PreferredSize, "")
.def("SetIcon", &BButton::SetIcon, "", py::arg("icon"), py::arg("flags")=0)
;


}
