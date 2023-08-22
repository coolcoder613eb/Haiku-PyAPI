#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/StatusBar.h>
#include <String.h>
#include <View.h>

namespace py = pybind11;


PYBIND11_MODULE(StatusBar,m)
{
py::class_<BStatusBar, BView>(m, "BStatusBar")
.def(py::init<BRect, const char *, const char *, const char *>(), "", py::arg("frame"), py::arg("name"), py::arg("label")=NULL, py::arg("trailingLabel")=NULL)
.def(py::init<const char *, const char *, const char *>(), "", py::arg("name"), py::arg("label")=NULL, py::arg("trailingLabel")=NULL)
.def(py::init<BMessage *>(), "", py::arg("archive"))
.def_static("Instantiate", &BStatusBar::Instantiate, "", py::arg("archive"))
.def("Archive", &BStatusBar::Archive, "", py::arg("archive"), py::arg("deep")=true)
.def("AttachedToWindow", &BStatusBar::AttachedToWindow, "")
.def("DetachedFromWindow", &BStatusBar::DetachedFromWindow, "")
.def("AllAttached", &BStatusBar::AllAttached, "")
.def("AllDetached", &BStatusBar::AllDetached, "")
.def("WindowActivated", &BStatusBar::WindowActivated, "", py::arg("state"))
.def("MakeFocus", &BStatusBar::MakeFocus, "", py::arg("focus")=true)
.def("GetPreferredSize", &BStatusBar::GetPreferredSize, "", py::arg("_width"), py::arg("_height"))
.def("MinSize", &BStatusBar::MinSize, "")
.def("MaxSize", &BStatusBar::MaxSize, "")
.def("PreferredSize", &BStatusBar::PreferredSize, "")
.def("ResizeToPreferred", &BStatusBar::ResizeToPreferred, "")
.def("FrameMoved", &BStatusBar::FrameMoved, "", py::arg("newPosition"))
.def("FrameResized", &BStatusBar::FrameResized, "", py::arg("newWidth"), py::arg("newHeight"))
.def("Draw", &BStatusBar::Draw, "", py::arg("updateRect"))
.def("MessageReceived", &BStatusBar::MessageReceived, "", py::arg("message"))
.def("MouseDown", &BStatusBar::MouseDown, "", py::arg("where"))
.def("MouseUp", &BStatusBar::MouseUp, "", py::arg("where"))
.def("MouseMoved", &BStatusBar::MouseMoved, "", py::arg("where"), py::arg("transit"), py::arg("dragMessage"))
.def("SetBarColor", &BStatusBar::SetBarColor, "", py::arg("color"))
.def("SetBarHeight", &BStatusBar::SetBarHeight, "", py::arg("height"))
.def("SetText", &BStatusBar::SetText, "", py::arg("string"))
.def("SetTrailingText", &BStatusBar::SetTrailingText, "", py::arg("string"))
.def("SetMaxValue", &BStatusBar::SetMaxValue, "", py::arg("max"))
.def("Update", &BStatusBar::Update, "", py::arg("delta"), py::arg("text")=NULL, py::arg("trailingText")=NULL)
.def("Reset", &BStatusBar::Reset, "", py::arg("label")=NULL, py::arg("trailingLabel")=NULL)
.def("SetTo", &BStatusBar::SetTo, "", py::arg("value"), py::arg("text")=NULL, py::arg("trailingText")=NULL)
.def("CurrentValue", &BStatusBar::CurrentValue, "")
.def("MaxValue", &BStatusBar::MaxValue, "")
.def("BarColor", &BStatusBar::BarColor, "")
.def("BarHeight", &BStatusBar::BarHeight, "")
.def("Text", &BStatusBar::Text, "")
.def("TrailingText", &BStatusBar::TrailingText, "")
.def("Label", &BStatusBar::Label, "")
.def("TrailingLabel", &BStatusBar::TrailingLabel, "")
.def("ResolveSpecifier", &BStatusBar::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("what"), py::arg("property"))
.def("GetSupportedSuites", &BStatusBar::GetSupportedSuites, "", py::arg("data"))
.def("Perform", &BStatusBar::Perform, "", py::arg("d"), py::arg("arg"))
;


}
