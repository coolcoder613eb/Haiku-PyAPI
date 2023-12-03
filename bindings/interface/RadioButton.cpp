#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/RadioButton.h>
#include <Bitmap.h>
#include <Control.h>

namespace py = pybind11;

class PyBRadioButton : public BRadioButton{
	public:
        using BRadioButton::BRadioButton;
        status_t		Archive(BMessage* data, bool deep = true) const override {
        	PYBIND11_OVERLOAD(status_t, BRadioButton, Archive, data, deep);
        }
        void			Draw(BRect updateRect) override {
            PYBIND11_OVERLOAD(void, BRadioButton, Draw, updateRect);
        }
        void			MouseDown(BPoint where) override {
            PYBIND11_OVERLOAD(void, BRadioButton, MouseDown, where);
        }
        void			AttachedToWindow() override {
            PYBIND11_OVERLOAD(void, BRadioButton, AttachedToWindow);
        }
        void			KeyDown(const char* bytes, int32 numBytes) override {
            PYBIND11_OVERLOAD(void, BRadioButton, KeyDown, bytes, numBytes);
        }
        void			SetValue(int32 value) override {
            PYBIND11_OVERLOAD(void, BRadioButton, SetValue, value);
        }
        void			GetPreferredSize(float* _width, float* _height) override {
            PYBIND11_OVERLOAD(void, BRadioButton, GetPreferredSize, _width, _height);
        }
        void			ResizeToPreferred() override {
            PYBIND11_OVERLOAD(void, BRadioButton, ResizeToPreferred);
        }
        status_t		Invoke(BMessage* message = NULL) override {
            PYBIND11_OVERLOAD(status_t, BRadioButton, Invoke, message);
        }
        void			MessageReceived(BMessage* message) override {
            PYBIND11_OVERLOAD(void, BRadioButton, MessageReceived, message);
        }
        void			WindowActivated(bool active) override {
            PYBIND11_OVERLOAD(void, BRadioButton, WindowActivated, active);
        }
        void			MouseUp(BPoint where) override {
            PYBIND11_OVERLOAD(void, BRadioButton, MouseUp, where);
        }
        void			MouseMoved(BPoint where, uint32 code, const BMessage* dragMessage) override {
            PYBIND11_OVERLOAD(void, BRadioButton, MouseMoved, where, code, dragMessage);
        }
        void			DetachedFromWindow() override {
            PYBIND11_OVERLOAD(void, BRadioButton, DetachedFromWindow);
        }
        void			FrameMoved(BPoint newPosition) override {
            PYBIND11_OVERLOAD(void, BRadioButton, FrameMoved, newPosition);
        }
        void			FrameResized(float newWidth, float newHeight) override {
            PYBIND11_OVERLOAD(void, BRadioButton, FrameResized, newWidth, newHeight);
        }
        BHandler*		ResolveSpecifier(BMessage* message, int32 index, BMessage* specifier, int32 what, const char* property) override {
            PYBIND11_OVERLOAD(BHandler*, BRadioButton, ResolveSpecifier, message, index, specifier, what, property);
        }
        void			MakeFocus(bool focus = true) override {
            PYBIND11_OVERLOAD(void, BRadioButton, MakeFocus, focus);
        }
        void			AllAttached() override {
            PYBIND11_OVERLOAD(void, BRadioButton, AllAttached);
        }
        void			AllDetached() override {
            PYBIND11_OVERLOAD(void, BRadioButton, AllDetached);
        }
        status_t		GetSupportedSuites(BMessage* message) override {
            PYBIND11_OVERLOAD(status_t, BRadioButton, GetSupportedSuites, message);
        }
        status_t		Perform(perform_code d, void* argument) override {
            PYBIND11_OVERLOAD(status_t, BRadioButton, Perform, d, argument);
        }
        BSize			MaxSize() override {
            PYBIND11_OVERLOAD(BSize, BRadioButton, MaxSize);
        }
        BAlignment		LayoutAlignment() override {
            PYBIND11_OVERLOAD(BAlignment, BRadioButton, LayoutAlignment);
        }
        status_t		SetIcon(const BBitmap* icon, uint32 flags = 0) override {
            PYBIND11_OVERLOAD(status_t, BRadioButton, SetIcon, icon, flags);
        }
};

PYBIND11_MODULE(RadioButton,m)
{
py::class_<BRadioButton, PyBRadioButton, BControl,std::unique_ptr<BRadioButton, py::nodelete>>(m, "BRadioButton")
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
