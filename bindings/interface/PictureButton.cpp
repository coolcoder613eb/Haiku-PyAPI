#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/PictureButton.h>
#include <Control.h>
#include <Picture.h>
#include <Bitmap.h>

namespace py = pybind11;

class PyBPictureButton : public BPictureButton{
	public:
        using BPictureButton::BPictureButton;
        status_t			Archive(BMessage* archive, bool deep = true) const override {
        	PYBIND11_OVERLOAD(status_t, BPictureButton, Archive, archive, deep);
        }
        void				AttachedToWindow() override {
            PYBIND11_OVERLOAD(void, BPictureButton, AttachedToWindow);
        }
        void				DetachedFromWindow() override {
            PYBIND11_OVERLOAD(void, BPictureButton, DetachedFromWindow);
        }
        void				AllAttached() override {
            PYBIND11_OVERLOAD(void, BPictureButton, AllAttached);
        }
        void				AllDetached() override {
            PYBIND11_OVERLOAD(void, BPictureButton, AllDetached);
        }
        void				ResizeToPreferred() override {
            PYBIND11_OVERLOAD(void, BPictureButton, ResizeToPreferred);
        }
        void				GetPreferredSize(float* _width,float* _height) override {
            PYBIND11_OVERLOAD(void, BPictureButton, GetPreferredSize, _width, _height);
        }
        void				FrameMoved(BPoint newPosition) override {
            PYBIND11_OVERLOAD(void, BPictureButton, FrameMoved, newPosition);
        }
        void				FrameResized(float newWidth, float newHeight) override {
            PYBIND11_OVERLOAD(void, BPictureButton, FrameResized, newWidth, newHeight);
        }
        void				WindowActivated(bool active) override {
            PYBIND11_OVERLOAD(void, BPictureButton, WindowActivated, active);
        }
        void				MakeFocus(bool focus = true) override {
            PYBIND11_OVERLOAD(void, BPictureButton, MakeFocus, focus);
        }
        void				Draw(BRect updateRect) override {
            PYBIND11_OVERLOAD(void, BPictureButton, Draw, updateRect);
        }
        void				MessageReceived(BMessage* message) override {
            PYBIND11_OVERLOAD(void, BPictureButton, MessageReceived, message);
        }
        void				KeyDown(const char* bytes, int32 numBytes) override {
            PYBIND11_OVERLOAD(void, BPictureButton, KeyDown, bytes, numBytes);
        }
        void				MouseDown(BPoint where) override {
            PYBIND11_OVERLOAD(void, BPictureButton, MouseDown, where);
        }
        void				MouseUp(BPoint where) override {
            PYBIND11_OVERLOAD(void, BPictureButton, MouseUp, where);
        }
        void				MouseMoved(BPoint where, uint32 code, const BMessage* dragMessage) override {
        	PYBIND11_OVERLOAD(void, BPictureButton, MouseMoved, where, code, dragMessage);
        }
        void				SetEnabledOn(BPicture* picture) override {
            PYBIND11_OVERLOAD(void, BPictureButton, SetEnabledOn, picture);
        }
        void				SetEnabledOff(BPicture* picture) override {
            PYBIND11_OVERLOAD(void, BPictureButton, SetEnabledOff, picture);
        }
        void				SetDisabledOn(BPicture* picture) override {
            PYBIND11_OVERLOAD(void, BPictureButton, SetDisabledOn, picture);
        }
        void				SetDisabledOff(BPicture* picture) override {
            PYBIND11_OVERLOAD(void, BPictureButton, SetDisabledOff, picture);
        }
        void				SetBehavior(uint32 behavior) override {
            PYBIND11_OVERLOAD(void, BPictureButton, SetBehavior, behavior);
        }
        void				SetValue(int32 value) override {
            PYBIND11_OVERLOAD(void, BPictureButton, SetValue, value);
        }
        status_t			Invoke(BMessage* message = NULL) override {
            PYBIND11_OVERLOAD(status_t, BPictureButton, Invoke, message);
        }
        BHandler*			ResolveSpecifier(BMessage* message, int32 index, BMessage* specifier, int32 what, const char* property) override {
            PYBIND11_OVERLOAD(BHandler*, BPictureButton, ResolveSpecifier, message, index, specifier, what, property);
        }
        status_t			GetSupportedSuites(BMessage* data) override {
            PYBIND11_OVERLOAD(status_t, BPictureButton, GetSupportedSuites, data);
        }
        status_t			Perform(perform_code code, void* data) override {
            PYBIND11_OVERLOAD(status_t, BPictureButton, Perform, code, data);
        }
        status_t			SetIcon(const BBitmap* icon, uint32 flags = 0) override {
            PYBIND11_OVERLOAD(status_t, BPictureButton, SetIcon, icon, flags);
        }
};

PYBIND11_MODULE(PictureButton,m)
{
//m.attr("B_ONE_STATE_BUTTON") = 0;
//m.attr("B_TWO_STATE_BUTTON") = 1;
py::enum_<picture_button_behavior>(m, "picture_button_behavior", "")
.value("B_ONE_STATE_BUTTON", picture_button_behavior::B_ONE_STATE_BUTTON, "")
.value("B_TWO_STATE_BUTTON", picture_button_behavior::B_TWO_STATE_BUTTON, "")
.export_values();

py::class_<BPictureButton, PyBPictureButton, BControl,std::unique_ptr<BPictureButton, py::nodelete>>(m, "BPictureButton")
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
