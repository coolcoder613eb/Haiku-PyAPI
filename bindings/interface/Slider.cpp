#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/Slider.h>
#include <View.h>
#include <Control.h>
#include <Bitmap.h>

namespace py = pybind11;


PYBIND11_MODULE(Slider,m)
{
py::enum_<hash_mark_location>(m, "hash_mark_location", "")
.value("B_HASH_MARKS_NONE", hash_mark_location::B_HASH_MARKS_NONE, "")
.value("B_HASH_MARKS_TOP", hash_mark_location::B_HASH_MARKS_TOP, "")
.value("B_HASH_MARKS_LEFT", hash_mark_location::B_HASH_MARKS_LEFT, "")
.value("B_HASH_MARKS_BOTTOM", hash_mark_location::B_HASH_MARKS_BOTTOM, "")
.value("B_HASH_MARKS_RIGHT", hash_mark_location::B_HASH_MARKS_RIGHT, "")
.value("B_HASH_MARKS_BOTH", hash_mark_location::B_HASH_MARKS_BOTH, "")
.export_values();

py::enum_<thumb_style>(m, "thumb_style", "")
.value("B_BLOCK_THUMB", thumb_style::B_BLOCK_THUMB, "")
.value("B_TRIANGLE_THUMB", thumb_style::B_TRIANGLE_THUMB, "")
.export_values();

py::class_<BSlider, BControl>(m, "BSlider")
.def(py::init<BRect, const char *, const char *, BMessage *, int, int, thumb_style, unsigned int, unsigned int>(), "", py::arg("frame"), py::arg("name"), py::arg("label"), py::arg("message"), py::arg("minValue"), py::arg("maxValue"), py::arg("thumbType")=B_BLOCK_THUMB, py::arg("resizingMode")=B_FOLLOW_LEFT_TOP, py::arg("flags")=B_NAVIGABLE | B_WILL_DRAW | B_FRAME_EVENTS)
.def(py::init<BRect, const char *, const char *, BMessage *, int, int, orientation, thumb_style, unsigned int, unsigned int>(), "", py::arg("frame"), py::arg("name"), py::arg("label"), py::arg("message"), py::arg("minValue"), py::arg("maxValue"), py::arg("posture"), py::arg("thumbType")=B_BLOCK_THUMB, py::arg("resizingMode")=B_FOLLOW_LEFT_TOP, py::arg("flags")=B_NAVIGABLE | B_WILL_DRAW | B_FRAME_EVENTS)
.def(py::init<const char *, const char *, BMessage *, int, int, orientation, thumb_style, unsigned int>(), "", py::arg("name"), py::arg("label"), py::arg("message"), py::arg("minValue"), py::arg("maxValue"), py::arg("posture"), py::arg("thumbType")=B_BLOCK_THUMB, py::arg("flags")=B_NAVIGABLE | B_WILL_DRAW | B_FRAME_EVENTS)
.def(py::init<BMessage *>(), "", py::arg("archive"))
.def_static("Instantiate", &BSlider::Instantiate, "", py::arg("archive"))
.def("Archive", &BSlider::Archive, "", py::arg("archive"), py::arg("deep")=true)
.def("Perform", &BSlider::Perform, "", py::arg("code"), py::arg("data"))
.def("WindowActivated", &BSlider::WindowActivated, "", py::arg("state"))
.def("AttachedToWindow", &BSlider::AttachedToWindow, "")
.def("AllAttached", &BSlider::AllAttached, "")
.def("AllDetached", &BSlider::AllDetached, "")
.def("DetachedFromWindow", &BSlider::DetachedFromWindow, "")
.def("MessageReceived", &BSlider::MessageReceived, "", py::arg("message"))
.def("FrameMoved", &BSlider::FrameMoved, "", py::arg("newPosition"))
.def("FrameResized", &BSlider::FrameResized, "", py::arg("width"), py::arg("height"))
.def("KeyDown", &BSlider::KeyDown, "", py::arg("bytes"), py::arg("numBytes"))
.def("KeyUp", &BSlider::KeyUp, "", py::arg("bytes"), py::arg("numBytes"))
.def("MouseDown", &BSlider::MouseDown, "", py::arg("point"))
.def("MouseUp", &BSlider::MouseUp, "", py::arg("point"))
.def("MouseMoved", &BSlider::MouseMoved, "", py::arg("point"), py::arg("transit"), py::arg("dragMessage"))
.def("Pulse", &BSlider::Pulse, "")
.def("SetLabel", &BSlider::SetLabel, "", py::arg("label"))
.def("SetLimitLabels", &BSlider::SetLimitLabels, "", py::arg("minLabel"), py::arg("maxLabel"))
.def("MinLimitLabel", &BSlider::MinLimitLabel, "")
.def("MaxLimitLabel", &BSlider::MaxLimitLabel, "")
.def("SetValue", &BSlider::SetValue, "", py::arg("value"))
.def("ValueForPoint", &BSlider::ValueForPoint, "", py::arg("point"))
.def("SetPosition", &BSlider::SetPosition, "", py::arg(""))
.def("Position", &BSlider::Position, "")
.def("SetEnabled", &BSlider::SetEnabled, "", py::arg("on"))
.def("GetLimits", &BSlider::GetLimits, "", py::arg("minimum"), py::arg("maximum"))
.def("Draw", &BSlider::Draw, "", py::arg("updateRect"))
.def("DrawSlider", &BSlider::DrawSlider, "")
.def("DrawBar", &BSlider::DrawBar, "")
.def("DrawHashMarks", &BSlider::DrawHashMarks, "")
.def("DrawThumb", &BSlider::DrawThumb, "")
.def("DrawFocusMark", &BSlider::DrawFocusMark, "")
.def("DrawText", &BSlider::DrawText, "")
.def("UpdateText", &BSlider::UpdateText, "")
.def("UpdateTextChanged", &BSlider::UpdateTextChanged, "")
.def("BarFrame", &BSlider::BarFrame, "")
.def("HashMarksFrame", &BSlider::HashMarksFrame, "")
.def("ThumbFrame", &BSlider::ThumbFrame, "")
.def("SetFlags", &BSlider::SetFlags, "", py::arg("flags"))
.def("SetResizingMode", &BSlider::SetResizingMode, "", py::arg("mode"))
.def("GetPreferredSize", &BSlider::GetPreferredSize, "", py::arg("_width"), py::arg("_height"))
.def("ResizeToPreferred", &BSlider::ResizeToPreferred, "")
.def("Invoke", &BSlider::Invoke, "", py::arg("message")=NULL)
.def("ResolveSpecifier", &BSlider::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("form"), py::arg("property"))
.def("GetSupportedSuites", &BSlider::GetSupportedSuites, "", py::arg("data"))
.def("SetModificationMessage", &BSlider::SetModificationMessage, "", py::arg("message"))
.def("ModificationMessage", &BSlider::ModificationMessage, "")
.def("SetSnoozeAmount", &BSlider::SetSnoozeAmount, "", py::arg("microSeconds"))
.def("SnoozeAmount", &BSlider::SnoozeAmount, "")
.def("SetKeyIncrementValue", &BSlider::SetKeyIncrementValue, "", py::arg("value"))
.def("KeyIncrementValue", &BSlider::KeyIncrementValue, "")
.def("SetHashMarkCount", &BSlider::SetHashMarkCount, "", py::arg("count"))
.def("HashMarkCount", &BSlider::HashMarkCount, "")
.def("SetHashMarks", &BSlider::SetHashMarks, "", py::arg("where"))
.def("HashMarks", &BSlider::HashMarks, "")
.def("SetStyle", &BSlider::SetStyle, "", py::arg("style"))
.def("Style", &BSlider::Style, "")
.def("SetBarColor", &BSlider::SetBarColor, "", py::arg("color"))
.def("BarColor", &BSlider::BarColor, "")
.def("UseFillColor", &BSlider::UseFillColor, "", py::arg("useFill"), py::arg("color")=NULL)
.def("FillColor", &BSlider::FillColor, "", py::arg("color"))
.def("OffscreenView", &BSlider::OffscreenView, "")
.def("Orientation", &BSlider::Orientation, "")
.def("SetOrientation", &BSlider::SetOrientation, "", py::arg(""))
.def("BarThickness", &BSlider::BarThickness, "")
.def("SetBarThickness", &BSlider::SetBarThickness, "", py::arg("thickness"))
.def("SetFont", &BSlider::SetFont, "", py::arg("font"), py::arg("properties")=B_FONT_ALL)
.def("SetLimits", &BSlider::SetLimits, "", py::arg("minimum"), py::arg("maximum"))
.def("MaxUpdateTextWidth", &BSlider::MaxUpdateTextWidth, "")
.def("MinSize", &BSlider::MinSize, "")
.def("MaxSize", &BSlider::MaxSize, "")
.def("PreferredSize", &BSlider::PreferredSize, "")
.def("SetIcon", &BSlider::SetIcon, "", py::arg("icon"), py::arg("flags")=0)
;


}
