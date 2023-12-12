#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/ChannelSlider.h>
#include <ChannelControl.h>
#include <Bitmap.h>

namespace py = pybind11;


PYBIND11_MODULE(ChannelSlider,m)
{
py::class_<BChannelSlider, BChannelControl>(m, "BChannelSlider")
.def(py::init<BRect, const char *, const char *, BMessage *, int, unsigned int, unsigned int>(), "", py::arg("area"), py::arg("name"), py::arg("label"), py::arg("message"), py::arg("channels")=1, py::arg("resizeMode")=B_FOLLOW_LEFT_TOP, py::arg("flags")=B_WILL_DRAW)
.def(py::init<BRect, const char *, const char *, BMessage *, orientation, int, unsigned int, unsigned int>(), "", py::arg("area"), py::arg("name"), py::arg("label"), py::arg("message"), py::arg("orientation"), py::arg("channels")=1, py::arg("resizeMode")=B_FOLLOW_LEFT_TOP, py::arg("flags")=B_WILL_DRAW)
.def(py::init<const char *, const char *, BMessage *, orientation, int, unsigned int>(), "", py::arg("name"), py::arg("label"), py::arg("message"), py::arg("orientation"), py::arg("channels")=1, py::arg("flags")=B_WILL_DRAW)
.def(py::init<BMessage *>(), "", py::arg("archive"))
.def_static("Instantiate", &BChannelSlider::Instantiate, "", py::arg("from"))
.def("Archive", &BChannelSlider::Archive, "", py::arg("into"), py::arg("deep")=true)
.def("AttachedToWindow", &BChannelSlider::AttachedToWindow, "")
.def("AllAttached", &BChannelSlider::AllAttached, "")
.def("DetachedFromWindow", &BChannelSlider::DetachedFromWindow, "")
.def("AllDetached", &BChannelSlider::AllDetached, "")
.def("MessageReceived", &BChannelSlider::MessageReceived, "", py::arg("message"))
.def("Draw", &BChannelSlider::Draw, "", py::arg("updateRect"))
.def("MouseDown", &BChannelSlider::MouseDown, "", py::arg("where"))
.def("MouseUp", &BChannelSlider::MouseUp, "", py::arg("where"))
.def("MouseMoved", &BChannelSlider::MouseMoved, "", py::arg("where"), py::arg("transit"), py::arg("dragMessage"))
.def("WindowActivated", &BChannelSlider::WindowActivated, "", py::arg("state"))
.def("KeyDown", &BChannelSlider::KeyDown, "", py::arg("bytes"), py::arg("numBytes"))
.def("KeyUp", &BChannelSlider::KeyUp, "", py::arg("bytes"), py::arg("numBytes"))
.def("FrameResized", &BChannelSlider::FrameResized, "", py::arg("width"), py::arg("height"))
.def("SetFont", &BChannelSlider::SetFont, "", py::arg("font"), py::arg("mask")=B_FONT_ALL)
.def("MakeFocus", &BChannelSlider::MakeFocus, "", py::arg("focusState")=true)
.def("GetPreferredSize", &BChannelSlider::GetPreferredSize, "", py::arg("_width"), py::arg("_height"))
.def("ResolveSpecifier", &BChannelSlider::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("form"), py::arg("property"))
.def("GetSupportedSuites", &BChannelSlider::GetSupportedSuites, "", py::arg("data"))
.def("SetEnabled", &BChannelSlider::SetEnabled, "", py::arg("on"))
.def("Orientation", &BChannelSlider::Orientation, "")
.def("SetOrientation", &BChannelSlider::SetOrientation, "", py::arg("orientation"))
.def("MaxChannelCount", &BChannelSlider::MaxChannelCount, "")
.def("SupportsIndividualLimits", &BChannelSlider::SupportsIndividualLimits, "")
.def("DrawChannel", &BChannelSlider::DrawChannel, "", py::arg("into"), py::arg("channel"), py::arg("area"), py::arg("pressed"))
.def("DrawGroove", &BChannelSlider::DrawGroove, "", py::arg("into"), py::arg("channel"), py::arg("leftTop"), py::arg("rightBottom"))
.def("DrawThumb", &BChannelSlider::DrawThumb, "", py::arg("into"), py::arg("channel"), py::arg("where"), py::arg("pressed"))
.def("ThumbFor", &BChannelSlider::ThumbFor, "", py::arg("channel"), py::arg("pressed"))
.def("ThumbFrameFor", &BChannelSlider::ThumbFrameFor, "", py::arg("channel"))
.def("ThumbDeltaFor", &BChannelSlider::ThumbDeltaFor, "", py::arg("channel"))
.def("ThumbRangeFor", &BChannelSlider::ThumbRangeFor, "", py::arg("channel"))
;


}
