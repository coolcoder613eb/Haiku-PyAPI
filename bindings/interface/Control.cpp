#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/Control.h>
#include <Invoker.h>
#include <Message.h>	// For convenience
#include <View.h>

namespace py = pybind11;
using namespace BPrivate;

PYBIND11_MODULE(Control,m)
{
m.attr("B_CONTROL_OFF") = 0;
m.attr("B_CONTROL_ON") = 1;
m.attr("B_CONTROL_PARTIALLY_ON") = 2;

m.attr("BIcon") = BIcon;

py::class_<BControl, BView, BInvoker>(m, "BControl")
.def(py::init<BRect, const char *, const char *, BMessage *, unsigned int, unsigned int>(), "", py::arg("frame"), py::arg("name"), py::arg("label"), py::arg("message"), py::arg("resizingMode"), py::arg("flags"))
.def(py::init<const char *, const char *, BMessage *, unsigned int>(), "", py::arg("name"), py::arg("label"), py::arg("message"), py::arg("flags"))
.def(py::init<BMessage *>(), "", py::arg("data"))
.def_static("Instantiate", &BControl::Instantiate, "", py::arg("data"))
.def("Archive", &BControl::Archive, "", py::arg("data"), py::arg("deep")=true)
.def("WindowActivated", &BControl::WindowActivated, "", py::arg("active"))
.def("AttachedToWindow", &BControl::AttachedToWindow, "")
.def("DetachedFromWindow", &BControl::DetachedFromWindow, "")
.def("AllAttached", &BControl::AllAttached, "")
.def("AllDetached", &BControl::AllDetached, "")
.def("MessageReceived", &BControl::MessageReceived, "", py::arg("message"))
.def("MakeFocus", &BControl::MakeFocus, "", py::arg("focus")=true)
.def("KeyDown", &BControl::KeyDown, "", py::arg("bytes"), py::arg("numBytes"))
.def("MouseDown", &BControl::MouseDown, "", py::arg("where"))
.def("MouseUp", &BControl::MouseUp, "", py::arg("where"))
.def("MouseMoved", &BControl::MouseMoved, "", py::arg("where"), py::arg("code"), py::arg("dragMessage"))
.def("SetLabel", &BControl::SetLabel, "", py::arg("string"))
.def("Label", &BControl::Label, "")
.def("SetValue", &BControl::SetValue, "", py::arg("value"))
.def("Value", &BControl::Value, "")
.def("SetEnabled", &BControl::SetEnabled, "", py::arg("enabled"))
.def("IsEnabled", &BControl::IsEnabled, "")
.def("GetPreferredSize", &BControl::GetPreferredSize, "", py::arg("_width"), py::arg("_height"))
.def("ResizeToPreferred", &BControl::ResizeToPreferred, "")
.def("Invoke", &BControl::Invoke, "", py::arg("message")=NULL)
.def("ResolveSpecifier", &BControl::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("what"), py::arg("property"))
.def("GetSupportedSuites", &BControl::GetSupportedSuites, "", py::arg("message"))
.def("Perform", &BControl::Perform, "", py::arg("d"), py::arg("arg"))
.def("SetIcon", &BControl::SetIcon, "", py::arg("bitmap"), py::arg("flags")=0)
.def("SetIconBitmap", &BControl::SetIconBitmap, "", py::arg("bitmap"), py::arg("which"), py::arg("flags")=0)
.def("IconBitmap", &BControl::IconBitmap, "", py::arg("which"))
;


}
