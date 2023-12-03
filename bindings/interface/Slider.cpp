#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/Slider.h>
#include <View.h>
#include <Control.h>
#include <Bitmap.h>

namespace py = pybind11;

class PyBSlider : public BSlider{
	public:
        using BSlider::BSlider;
        status_t		Archive(BMessage* archive, bool deep = true) const override {
        	PYBIND11_OVERLOAD(status_t, BSlider, Archive, archive, deep);
        }
        status_t			Perform(perform_code code, void* data) override {
        	PYBIND11_OVERLOAD(status_t, BSlider, Perform, code, data);
        }
        void				WindowActivated(bool state) override {
        	PYBIND11_OVERLOAD(void, BSlider, WindowActivated, state);
        }
        void				AttachedToWindow() override {
        	PYBIND11_OVERLOAD(void, BSlider, AttachedToWindow);
        }
        void				AllAttached() override {
        	PYBIND11_OVERLOAD(void, BSlider, AllAttached);
        }
        void				AllDetached() override {
        	PYBIND11_OVERLOAD(void, BSlider, AllDetached);
        }
        void				DetachedFromWindow() override {
        	PYBIND11_OVERLOAD(void, BSlider, DetachedFromWindow);
        }
        void				MessageReceived(BMessage* message) override {
        	PYBIND11_OVERLOAD(void, BSlider, MessageReceived, message);
        }
        void				FrameMoved(BPoint newPosition) override {
        	PYBIND11_OVERLOAD(void, BSlider, FrameMoved, newPosition);
        }
        void				FrameResized(float width, float height) override {
        	PYBIND11_OVERLOAD(void, BSlider, FrameResized, width, height);
        }
        void				KeyDown(const char* bytes, int32 numBytes) override {
        	PYBIND11_OVERLOAD(void, BSlider, KeyDown, bytes, numBytes);
        }
        void				KeyUp(const char* bytes, int32 numBytes) override {
        	PYBIND11_OVERLOAD(void, BSlider, KeyUp, bytes, numBytes);
        }
        void				MouseDown(BPoint point) override {
        	PYBIND11_OVERLOAD(void, BSlider, MouseDown, point);
        }
        void				MouseUp(BPoint point) override {
        	PYBIND11_OVERLOAD(void, BSlider, MouseUp, point);
        }
        void				MouseMoved(BPoint point, uint32 transit, const BMessage* dragMessage) override {
        	PYBIND11_OVERLOAD(void, BSlider, MouseMoved, point, transit, dragMessage);
        }
        void				Pulse() override {
        	PYBIND11_OVERLOAD(void, BSlider, Pulse);
        }
        void				SetLabel(const char* label) override {
        	PYBIND11_OVERLOAD(void, BSlider, SetLabel, label);
        }
        void				SetLimitLabels(const char* minLabel, const char* maxLabel) override {
        	PYBIND11_OVERLOAD(void, BSlider, SetLimitLabels, minLabel, maxLabel);
        }
        void				SetValue(int32 value) override {
        	PYBIND11_OVERLOAD(void, BSlider, SetValue, value);
        }
        int32				ValueForPoint(BPoint point) const override {
        	PYBIND11_OVERLOAD(int32, BSlider, ValueForPoint, point);
        }
        void				SetPosition(float position) override {
        	PYBIND11_OVERLOAD(void, BSlider, SetPosition, position);
        }
        void				SetEnabled(bool on) override {
        	PYBIND11_OVERLOAD(void, BSlider, SetEnabled, on);
        }
        void				Draw(BRect updateRect) override {
        	PYBIND11_OVERLOAD(void, BSlider, Draw, updateRect);
        }
        void				DrawSlider() override {
        	PYBIND11_OVERLOAD(void, BSlider, DrawSlider);
        }
        void				DrawBar() override {
        	PYBIND11_OVERLOAD(void, BSlider, DrawBar);
        }
        void				DrawHashMarks() override {
        	PYBIND11_OVERLOAD(void, BSlider, DrawHashMarks);
        }
        void				DrawThumb() override {
        	PYBIND11_OVERLOAD(void, BSlider, DrawThumb);
        }
        void				DrawFocusMark() override {
        	PYBIND11_OVERLOAD(void, BSlider, DrawFocusMark);
        }
        void				DrawText() override {
        	PYBIND11_OVERLOAD(void, BSlider, DrawText);
        }
        const char*			UpdateText() const override {
        	PYBIND11_OVERLOAD(const char*, BSlider, UpdateText);
        }
        BRect				BarFrame() const override {
        	PYBIND11_OVERLOAD(BRect, BSlider, BarFrame);
        }
        BRect				HashMarksFrame() const override {
        	PYBIND11_OVERLOAD(BRect, BSlider, HashMarksFrame);
        }
        BRect				ThumbFrame() const override {
        	PYBIND11_OVERLOAD(BRect, BSlider, ThumbFrame);
        }
        void				SetFlags(uint32 flags) override {
        	PYBIND11_OVERLOAD(void, BSlider, SetFlags, flags);
        }
        void				SetResizingMode(uint32 mode) override {
        	PYBIND11_OVERLOAD(void, BSlider, SetResizingMode, mode);
        }
        void				GetPreferredSize(float* _width, float* _height) override {
        	PYBIND11_OVERLOAD(void, BSlider, GetPreferredSize, _width, _height);
        }
        void				ResizeToPreferred() override {
        	PYBIND11_OVERLOAD(void, BSlider, ResizeToPreferred);
        }
        status_t			Invoke(BMessage* message = NULL) override {
        	PYBIND11_OVERLOAD(status_t, BSlider, Invoke, message);
        }
        BHandler*			ResolveSpecifier(BMessage* message, int32 index, BMessage* specifier, int32 form, const char* property) override {
        	PYBIND11_OVERLOAD(BHandler*, BSlider, ResolveSpecifier, message, index, specifier, form, property);
        }        
        status_t			GetSupportedSuites(BMessage* data) override {
        	PYBIND11_OVERLOAD(status_t, BSlider, GetSupportedSuites, data);
        }
        void				SetModificationMessage(BMessage* message) override {
        	PYBIND11_OVERLOAD(void, BSlider, SetModificationMessage, message);
        }
        void				SetSnoozeAmount(int32 microSeconds) override {
        	PYBIND11_OVERLOAD(void, BSlider, SetSnoozeAmount, microSeconds);
        }
        void				SetKeyIncrementValue(int32 value) override {
        	PYBIND11_OVERLOAD(void, BSlider, SetKeyIncrementValue, value);
        }
        void				SetHashMarkCount(int32 count) override {
        	PYBIND11_OVERLOAD(void, BSlider, SetHashMarkCount, count);
        }
        void				SetHashMarks(hash_mark_location where) override {
        	PYBIND11_OVERLOAD(void, BSlider, SetHashMarks, where);
        }
        void				SetStyle(thumb_style style) override {
        	PYBIND11_OVERLOAD(void, BSlider, SetStyle, style);
        }
        void				SetBarColor(rgb_color color) override {
        	PYBIND11_OVERLOAD(void, BSlider, SetBarColor, color);
        }
        void				UseFillColor(bool useFill, const rgb_color* color = NULL) override {
        	PYBIND11_OVERLOAD(void, BSlider, UseFillColor, useFill, color);
        }
        void				SetOrientation(orientation orient) override {
        	PYBIND11_OVERLOAD(void, BSlider, SetOrientation, orient);
        }
        void				SetBarThickness(float thickness) override {
        	PYBIND11_OVERLOAD(void, BSlider, SetBarThickness, thickness);
        }
        void				SetFont(const BFont* font, uint32 properties = B_FONT_ALL) override {
        	PYBIND11_OVERLOAD(void, BSlider, SetFont, font, properties);
        }
        void				SetLimits(int32 minimum, int32 maximum) override {
        	PYBIND11_OVERLOAD(void, BSlider, SetLimits, minimum, maximum);
        }
        float				MaxUpdateTextWidth() override {
        	PYBIND11_OVERLOAD(float, BSlider, MaxUpdateTextWidth);
        }
        BSize				MinSize() override {
        	PYBIND11_OVERLOAD(BSize, BSlider, MinSize);
        }
        BSize				MaxSize() override {
        	PYBIND11_OVERLOAD(BSize, BSlider, MaxSize);
        }
        BSize				PreferredSize() override {
        	PYBIND11_OVERLOAD(BSize, BSlider, PreferredSize);
        }
        status_t			SetIcon(const BBitmap* icon, uint32 flags = 0) override {
        	PYBIND11_OVERLOAD(status_t, BSlider, SetIcon, icon, flags);
        }
};

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

py::class_<BSlider, PyBSlider, BControl>(m, "BSlider")
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
