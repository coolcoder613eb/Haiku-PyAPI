#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/CheckBox.h>
#include <interface/Bitmap.h>
#include <Control.h>

namespace py = pybind11;


class PyBCheckBox : public BCheckBox{
	public:
        using BCheckBox::BCheckBox;
        status_t	Archive(BMessage* data, bool deep = true) const override {
        	PYBIND11_OVERLOAD(status_t, BCheckBox, Archive, data, deep);
        }
        void				Draw(BRect updateRect) override {
            PYBIND11_OVERLOAD(void, BCheckBox, Draw, updateRect);
        }
        void				AttachedToWindow() override {
            PYBIND11_OVERLOAD(void, BCheckBox, AttachedToWindow);
        }
        void				DetachedFromWindow() override {
            PYBIND11_OVERLOAD(void, BCheckBox, DetachedFromWindow);
        }
        void				AllAttached() override {
            PYBIND11_OVERLOAD(void, BCheckBox, AllAttached);
        }
        void				AllDetached() override {
            PYBIND11_OVERLOAD(void, BCheckBox, AllDetached);
        }
        void				FrameMoved(BPoint newPosition) override {
            PYBIND11_OVERLOAD(void, BCheckBox, FrameMoved, newPosition);
        }
        void				FrameResized(float newWidth, float newHeight) override {
            PYBIND11_OVERLOAD(void, BCheckBox, FrameResized, newWidth, newHeight);
        }
        void				WindowActivated(bool active) override {
            PYBIND11_OVERLOAD(void, BCheckBox, WindowActivated, active);
        }
        void				MessageReceived(BMessage* message) override {
            PYBIND11_OVERLOAD(void, BCheckBox, MessageReceived, message);
        }
        void				KeyDown(const char* bytes, int32 numBytes) override {
            PYBIND11_OVERLOAD(void, BCheckBox, KeyDown, bytes, numBytes);
        }
        void				MouseDown(BPoint where) override {
            PYBIND11_OVERLOAD(void, BCheckBox, MouseDown, where);
        }
        void				MouseUp(BPoint where) override {
            PYBIND11_OVERLOAD(void, BCheckBox, MouseUp, where);
        }
        void				MouseMoved(BPoint where, uint32 code, const BMessage* dragMessage) override {
        	PYBIND11_OVERLOAD(void, BCheckBox, MouseMoved, where, code, dragMessage);
        }
        void				GetPreferredSize(float* _width, float* _height) override {
            PYBIND11_OVERLOAD(void, BCheckBox, GetPreferredSize, _width, _height);
        }
        void				ResizeToPreferred() override {
            PYBIND11_OVERLOAD(void, BCheckBox, ResizeToPreferred);
        }
        BSize				MinSize() override {
            PYBIND11_OVERLOAD(BSize, BCheckBox, MinSize);
        }
        BSize				MaxSize() override {
            PYBIND11_OVERLOAD(BSize, BCheckBox, MaxSize);
        }
        BSize				PreferredSize() override {
            PYBIND11_OVERLOAD(BSize, BCheckBox, PreferredSize);
        }
        BAlignment			LayoutAlignment() override {
            PYBIND11_OVERLOAD(BAlignment, BCheckBox, LayoutAlignment);
        }
        void				MakeFocus(bool focused = true) override {
            PYBIND11_OVERLOAD(void, BCheckBox, MakeFocus, focused);
        }
        void				SetValue(int32 value) override {
            PYBIND11_OVERLOAD(void, BCheckBox, SetValue, value);
        }
        status_t			Invoke(BMessage* message = NULL) override {
            PYBIND11_OVERLOAD(status_t, BCheckBox, Invoke, message);
        }
        BHandler*			ResolveSpecifier(BMessage* message, int32 index, BMessage* specifier, int32 what, const char* property) override {
            PYBIND11_OVERLOAD(BHandler*, BCheckBox, ResolveSpecifier, message, index, specifier, what, property);
        }
        status_t			GetSupportedSuites(BMessage* message) override {
            PYBIND11_OVERLOAD(status_t, BCheckBox, GetSupportedSuites, message);
        }
        status_t			Perform(perform_code code, void* data) override {
            PYBIND11_OVERLOAD(status_t, BCheckBox, Perform, code, data);
        }
        status_t			SetIcon(const BBitmap* icon, uint32 flags = 0) override {
            PYBIND11_OVERLOAD(status_t, BCheckBox, SetIcon, icon, flags);
        }
};

PYBIND11_MODULE(CheckBox,m)
{
py::class_<BCheckBox, BControl, std::unique_ptr<BCheckBox, py::nodelete>>(m, "BCheckBox")
.def(py::init<BRect, const char *, const char *, BMessage *, unsigned int, unsigned int>(), "", py::arg("frame"), py::arg("name"), py::arg("label"), py::arg("message"), py::arg("resizingMode")=B_FOLLOW_LEFT_TOP, py::arg("flags")=B_WILL_DRAW | B_NAVIGABLE)
.def(py::init<const char *, const char *, BMessage *, unsigned int>(), "", py::arg("name"), py::arg("label"), py::arg("message"), py::arg("flags")=B_WILL_DRAW | B_NAVIGABLE)
.def(py::init<const char *, BMessage *>(), "", py::arg("label"), py::arg("message")=NULL)
.def(py::init<BMessage *>(), "", py::arg("data"))
.def_static("Instantiate", &BCheckBox::Instantiate, "", py::arg("data"))
.def("Archive", &BCheckBox::Archive, "", py::arg("data"), py::arg("deep")=true)
.def("Draw", &BCheckBox::Draw, "", py::arg("updateRect"))
.def("AttachedToWindow", &BCheckBox::AttachedToWindow, "")
.def("DetachedFromWindow", &BCheckBox::DetachedFromWindow, "")
.def("AllAttached", &BCheckBox::AllAttached, "")
.def("AllDetached", &BCheckBox::AllDetached, "")
.def("FrameMoved", &BCheckBox::FrameMoved, "", py::arg("newPosition"))
.def("FrameResized", &BCheckBox::FrameResized, "", py::arg("newWidth"), py::arg("newHeight"))
.def("WindowActivated", &BCheckBox::WindowActivated, "", py::arg("active"))
.def("MessageReceived", &BCheckBox::MessageReceived, "", py::arg("message"))
.def("KeyDown", &BCheckBox::KeyDown, "", py::arg("bytes"), py::arg("numBytes"))
.def("MouseDown", &BCheckBox::MouseDown, "", py::arg("where"))
.def("MouseUp", &BCheckBox::MouseUp, "", py::arg("where"))
.def("MouseMoved", &BCheckBox::MouseMoved, "", py::arg("where"), py::arg("code"), py::arg("dragMessage"))
.def("GetPreferredSize", &BCheckBox::GetPreferredSize, "", py::arg("_width"), py::arg("_height"))
.def("ResizeToPreferred", &BCheckBox::ResizeToPreferred, "")
.def("MinSize", &BCheckBox::MinSize, "")
.def("MaxSize", &BCheckBox::MaxSize, "")
.def("PreferredSize", &BCheckBox::PreferredSize, "")
.def("LayoutAlignment", &BCheckBox::LayoutAlignment, "")
.def("MakeFocus", &BCheckBox::MakeFocus, "", py::arg("focused")=true)
.def("SetValue", &BCheckBox::SetValue, "", py::arg("value"))
.def("Invoke", &BCheckBox::Invoke, "", py::arg("message")=NULL)
.def("ResolveSpecifier", &BCheckBox::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("what"), py::arg("property"))
.def("GetSupportedSuites", &BCheckBox::GetSupportedSuites, "", py::arg("message"))
.def("Perform", &BCheckBox::Perform, "", py::arg("code"), py::arg("data"))
.def("SetIcon", &BCheckBox::SetIcon, "", py::arg("icon"), py::arg("flags")=0)
.def("IsPartialStateToOff", &BCheckBox::IsPartialStateToOff, "")
.def("SetPartialStateToOff", &BCheckBox::SetPartialStateToOff, "", py::arg("partialToOff"))
;


}
