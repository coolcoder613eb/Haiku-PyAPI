#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/ChannelControl.h>
#include <Control.h>
#include <String.h>

namespace py = pybind11;


PYBIND11_MODULE(ChannelControl,m)
{
py::class_<BChannelControl, BControl>(m, "BChannelControl")
.def(py::init<BRect, const char *, const char *, BMessage *, int, unsigned int, unsigned int>(), "", py::arg("frame"), py::arg("name"), py::arg("label"), py::arg("model"), py::arg("channelCount")=1, py::arg("resizingMode")=B_FOLLOW_LEFT_TOP, py::arg("flags")=B_WILL_DRAW)
.def(py::init<const char *, const char *, BMessage *, int, unsigned int>(), "", py::arg("name"), py::arg("label"), py::arg("model"), py::arg("channelCount")=1, py::arg("flags")=B_WILL_DRAW)
.def(py::init<BMessage *>(), "", py::arg("archive"))
.def("Archive", &BChannelControl::Archive, "", py::arg("data"), py::arg("deep")=true)
.def("Draw", &BChannelControl::Draw, "", py::arg("updateRect"))
.def("MouseDown", &BChannelControl::MouseDown, "", py::arg("where"))
.def("KeyDown", &BChannelControl::KeyDown, "", py::arg("bytes"), py::arg("numBytes"))
.def("FrameResized", &BChannelControl::FrameResized, "", py::arg("newWidth"), py::arg("newHeight"))
.def("SetFont", &BChannelControl::SetFont, "", py::arg("font"), py::arg("mask")=B_FONT_ALL)
.def("AttachedToWindow", &BChannelControl::AttachedToWindow, "")
.def("DetachedFromWindow", &BChannelControl::DetachedFromWindow, "")
.def("ResizeToPreferred", &BChannelControl::ResizeToPreferred, "")
.def("GetPreferredSize", &BChannelControl::GetPreferredSize, "", py::arg("width"), py::arg("height"))
.def("MessageReceived", &BChannelControl::MessageReceived, "", py::arg("message"))
.def("ResolveSpecifier", &BChannelControl::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("what"), py::arg("property"))
.def("GetSupportedSuites", &BChannelControl::GetSupportedSuites, "", py::arg("data"))
.def("SetModificationMessage", &BChannelControl::SetModificationMessage, "", py::arg("message"))
.def("ModificationMessage", &BChannelControl::ModificationMessage, "")
.def("Invoke", &BChannelControl::Invoke, "", py::arg("message")=NULL)
.def("InvokeChannel", &BChannelControl::InvokeChannel, "//! These methods are similar to Invoke() Invoke() and InvokeNotify(), but", py::arg("message")=NULL, py::arg("fromChannel")=0, py::arg("channelCount")=- 1, py::arg("_mask")=NULL)
.def("InvokeNotifyChannel", &BChannelControl::InvokeNotifyChannel, "", py::arg("message")=NULL, py::arg("kind")=B_CONTROL_INVOKED, py::arg("fromChannel")=0, py::arg("channelCount")=- 1, py::arg("_mask")=NULL)
.def("SetValue", py::overload_cast<int>(&BChannelControl::SetValue), "", py::arg("value"))
.def("SetCurrentChannel", &BChannelControl::SetCurrentChannel, "", py::arg("index"))
.def("CurrentChannel", &BChannelControl::CurrentChannel, "")
.def("CountChannels", &BChannelControl::CountChannels, "")
.def("MaxChannelCount", &BChannelControl::MaxChannelCount, "")
.def("SetChannelCount", &BChannelControl::SetChannelCount, "", py::arg("count"))
.def("ValueFor", &BChannelControl::ValueFor, "", py::arg("channel"))
.def("GetValue", &BChannelControl::GetValue, "", py::arg("_values"), py::arg("fromChannel"), py::arg("channelCount"))
.def("SetValueFor", &BChannelControl::SetValueFor, "", py::arg("channel"), py::arg("value"))
.def("SetValue", py::overload_cast<int, int, int>(&BChannelControl::SetValue), "", py::arg("fromChannel"), py::arg("channelCount"), py::arg("values"))
.def("SetAllValue", &BChannelControl::SetAllValue, "", py::arg("values"))
.def("SetLimitsFor", py::overload_cast<int, int, int>(&BChannelControl::SetLimitsFor), "", py::arg("channel"), py::arg("minimum"), py::arg("maximum"))
.def("GetLimitsFor", py::overload_cast<int, int, int>(&BChannelControl::GetLimitsFor), "", py::arg("channel"), py::arg("_minimum"), py::arg("_maximum"))
.def("SetLimitsFor", py::overload_cast<int, int, int, int>(&BChannelControl::SetLimitsFor), "", py::arg("fromChannel"), py::arg("channelCount"), py::arg("minima"), py::arg("maxima"))
.def("GetLimitsFor", py::overload_cast<int, int, int, int>(&BChannelControl::GetLimitsFor), "", py::arg("fromChannel"), py::arg("channelCount"), py::arg("minima"), py::arg("maxima"))
.def("SetLimits", &BChannelControl::SetLimits, "", py::arg("minimum"), py::arg("maximum"))
.def("GetLimits", &BChannelControl::GetLimits, "", py::arg("_minimum"), py::arg("_maximum"))
.def("SupportsIndividualLimits", &BChannelControl::SupportsIndividualLimits, "")
.def("SetLimitLabels", &BChannelControl::SetLimitLabels, "", py::arg("minLabel"), py::arg("maxLabel"))
.def("MinLimitLabel", &BChannelControl::MinLimitLabel, "")
.def("MaxLimitLabel", &BChannelControl::MaxLimitLabel, "")
.def("SetLimitLabelsFor", py::overload_cast<int, const char *, const char *>(&BChannelControl::SetLimitLabelsFor), "", py::arg("channel"), py::arg("minLabel"), py::arg("maxLabel"))
.def("SetLimitLabelsFor", py::overload_cast<int, int, const char *, const char *>(&BChannelControl::SetLimitLabelsFor), "", py::arg("fromChannel"), py::arg("channelCount"), py::arg("minLabel"), py::arg("maxLabel"))
.def("MinLimitLabelFor", &BChannelControl::MinLimitLabelFor, "", py::arg("channel"))
.def("MaxLimitLabelFor", &BChannelControl::MaxLimitLabelFor, "", py::arg("channel"))
;


}
