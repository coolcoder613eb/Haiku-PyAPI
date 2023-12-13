#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/ChannelSlider.h>
#include <ChannelControl.h>
#include <Bitmap.h>

namespace py = pybind11;

class PyBChannelSlider : public BChannelSlider{
	public:
        using BChannelSlider::BChannelSlider;
        status_t	Archive(BMessage* into, bool deep = true) const override {
        	PYBIND11_OVERLOAD(status_t, BChannelSlider, Archive, into, deep);
        }
        void		AttachedToWindow() override {
        	PYBIND11_OVERLOAD(void, BChannelSlider, AttachedToWindow);
        }
        void		AllAttached() override {
        	PYBIND11_OVERLOAD(void, BChannelSlider, AllAttached);
        }
        void		DetachedFromWindow() override {
        	PYBIND11_OVERLOAD(void, BChannelSlider, DetachedFromWindow);
        }
        void		AllDetached() override {
        	PYBIND11_OVERLOAD(void, BChannelSlider, AllDetached);
        }
        void		MessageReceived(BMessage* message) override {
        	PYBIND11_OVERLOAD(void, BChannelSlider, MessageReceived, message);
        }
        void				Draw(BRect updateRect) override {
        	PYBIND11_OVERLOAD(void, BChannelSlider, Draw, updateRect);
        }
        void				MouseDown(BPoint where) override {
        	PYBIND11_OVERLOAD(void, BChannelSlider, MouseDown, where);
        }
        void				MouseUp(BPoint where) override {
        	PYBIND11_OVERLOAD(void, BChannelSlider, MouseUp, where);
        }
        void				MouseMoved(BPoint where, uint32 transit, const BMessage* dragMessage) override {
        	PYBIND11_OVERLOAD(void, BChannelSlider, MouseMoved, where, transit, dragMessage);
        }
        void				WindowActivated(bool state) override {
        	PYBIND11_OVERLOAD(void, BChannelSlider, WindowActivated, state);
        }
        void				KeyDown(const char* bytes, int32 numBytes) override {
        	PYBIND11_OVERLOAD(void, BChannelSlider, KeyDown, bytes, numBytes);
        }
        void				KeyUp(const char* bytes, int32 numBytes) override {
        	PYBIND11_OVERLOAD(void, BChannelSlider, KeyUp, bytes, numBytes);
        }
        void				FrameResized(float width, float height) override {
        	PYBIND11_OVERLOAD(void, BChannelSlider, FrameResized, width, height);
        }
        void				SetFont(const BFont* font, uint32 mask = B_FONT_ALL) override {
        	PYBIND11_OVERLOAD(void, BChannelSlider, SetFont, font, mask);
        }
        void				MakeFocus(bool focusState = true) override {
        	PYBIND11_OVERLOAD(void, BChannelSlider, MakeFocus, focusState);
        }
        void				GetPreferredSize(float* _width, float* _height) override {
        	PYBIND11_OVERLOAD(void, BChannelSlider, GetPreferredSize, _width, _height);
        }
        BHandler*			ResolveSpecifier(BMessage* message, int32 index, BMessage* specifier, int32 form, const char* property) override {
        	PYBIND11_OVERLOAD(BHandler*, BChannelSlider, ResolveSpecifier, message, index, specifier, form, property);
        }
        status_t			GetSupportedSuites(BMessage* data) override {
        	PYBIND11_OVERLOAD(status_t, BChannelSlider, GetSupportedSuites, data);
        }
        void				SetEnabled(bool on) override {
        	PYBIND11_OVERLOAD(void, BChannelSlider, SetEnabled, on);
        }
        orientation			Orientation() const override {
        	PYBIND11_OVERLOAD(orientation, BChannelSlider, Orientation);
        }
        int32				MaxChannelCount() const override {
        	PYBIND11_OVERLOAD(int32, BChannelSlider, MaxChannelCount);
        }
        bool				SupportsIndividualLimits() const override {
        	PYBIND11_OVERLOAD(bool, BChannelSlider, SupportsIndividualLimits);
        }
        void				DrawChannel(BView* into, int32 channel, BRect area, bool pressed) override {
        	PYBIND11_OVERLOAD(void, BChannelSlider, DrawChannel, into, channel, area, pressed);
        }
        void				DrawGroove(BView* into, int32 channel, BPoint leftTop, BPoint rightBottom) override {
        	PYBIND11_OVERLOAD(void, BChannelSlider, DrawGroove, into, channel, leftTop, rightBottom);
        }
        void				DrawThumb(BView* into, int32 channel, BPoint where, bool pressed) override {
        	PYBIND11_OVERLOAD(void, BChannelSlider, DrawThumb, into, channel, where, pressed);
        }
        const BBitmap*		ThumbFor(int32 channel, bool pressed) override {
        	PYBIND11_OVERLOAD(const BBitmap*, BChannelSlider, ThumbFor, channel, pressed);
        }
        BRect				ThumbFrameFor(int32 channel) override {
        	PYBIND11_OVERLOAD(BRect, BChannelSlider, ThumbFrameFor, channel);
        }
        float				ThumbDeltaFor(int32 channel) override {
        	PYBIND11_OVERLOAD(float, BChannelSlider, ThumbDeltaFor, channel);
        }
        float				ThumbRangeFor(int32 channel) override {
        	PYBIND11_OVERLOAD(float, BChannelSlider, ThumbRangeFor, channel);
        }
};



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
