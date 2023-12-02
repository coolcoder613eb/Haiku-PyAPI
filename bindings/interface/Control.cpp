#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/Control.h>
#include <Invoker.h>
#include <Message.h>	// For convenience
#include <View.h>
#include <Bitmap.h>

namespace py = pybind11;
using namespace BPrivate;

class PyBControl : public BControl{
	public:
        using BControl::BControl;
        status_t	Archive(BMessage* data, bool deep = true) const override {
        	PYBIND11_OVERLOAD(status_t, BControl, Archive, data, deep);
        }
        void				WindowActivated(bool active) override {
            PYBIND11_OVERLOAD(void, BControl, WindowActivated, active);
        }
        void				AttachedToWindow() override {
            PYBIND11_OVERLOAD(void, BControl, AttachedToWindow);
        }
        void				DetachedFromWindow() override {
            PYBIND11_OVERLOAD(void, BControl, DetachedFromWindow);
        }
        void				AllAttached() override {
            PYBIND11_OVERLOAD(void, BControl, AllAttached);
        }
        void				AllDetached() override {
            PYBIND11_OVERLOAD(void, BControl, AllDetached);
        }
        void				MessageReceived(BMessage* message) override {
            PYBIND11_OVERLOAD(void, BControl, MessageReceived, message);
        }
        void				MakeFocus(bool focus = true) override {
            PYBIND11_OVERLOAD(void, BControl, MakeFocus, focus);
        }
        void				KeyDown(const char* bytes, int32 numBytes) override {
            PYBIND11_OVERLOAD(void, BControl, KeyDown, bytes, numBytes);
        }
        void				MouseDown(BPoint where) override {
            PYBIND11_OVERLOAD(void, BControl, MouseDown, where);
        }
        void				MouseUp(BPoint where) override {
            PYBIND11_OVERLOAD(void, BControl, MouseUp, where);
        }
        void				MouseMoved(BPoint where, uint32 code, const BMessage* dragMessage) override {
        	PYBIND11_OVERLOAD(void, BControl, MouseMoved, where, code, dragMessage);
        }
        void				SetLabel(const char* string) override {
            PYBIND11_OVERLOAD(void, BControl, SetLabel, string);
        }
        void				SetValue(int32 value) override {
            PYBIND11_OVERLOAD(void, BControl, SetValue, value);
        }
        void				SetEnabled(bool enabled) override {
            PYBIND11_OVERLOAD(void, BControl, SetEnabled, enabled);
        }
        void				GetPreferredSize(float* _width, float* _height) override {
            PYBIND11_OVERLOAD(void, BControl, GetPreferredSize, _width, _height);
        }
        void				ResizeToPreferred() override {
            PYBIND11_OVERLOAD(void, BControl, ResizeToPreferred);
        }
        status_t			Invoke(BMessage* message = NULL) override {
            PYBIND11_OVERLOAD(status_t, BControl, Invoke, message);
        }
        BHandler*			ResolveSpecifier(BMessage* message, int32 index, BMessage* specifier, int32 what, const char* property) override {
            PYBIND11_OVERLOAD(BHandler*, BControl, ResolveSpecifier, message, index, specifier, what, property);
        }
        status_t			GetSupportedSuites(BMessage* message) override {
            PYBIND11_OVERLOAD(status_t, BControl, GetSupportedSuites, message);
        }
        status_t			Perform(perform_code d, void* arg) override {
            PYBIND11_OVERLOAD(status_t, BControl, Perform, d, arg);
        }
        status_t			SetIcon(const BBitmap* bitmap, uint32 flags = 0) override {
            PYBIND11_OVERLOAD(status_t, BControl, SetIcon, bitmap, flags);
        }
};


PYBIND11_MODULE(Control,m)
{
m.attr("B_CONTROL_OFF") = 0;
m.attr("B_CONTROL_ON") = 1;
m.attr("B_CONTROL_PARTIALLY_ON") = 2;

//m.attr("BIcon") = BIcon;

py::class_<BControl, PyBControl, BView, BInvoker>(m, "BControl")
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
