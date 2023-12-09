#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/TextControl.h>
#include <Control.h>
#include <TextView.h>
#include <LayoutItem.h>

namespace py = pybind11;
using namespace BPrivate;

class PyBTextControl : public BTextControl{
	public:
        using BTextControl::BTextControl;
        status_t			Archive(BMessage* archive, bool deep = true) const override {
        	PYBIND11_OVERLOAD(status_t, BTextControl, Archive, archive, deep);
        }
        void				SetText(const char* text) override {
        	PYBIND11_OVERLOAD(void, BTextControl, SetText, text);
        }
        void				SetValue(int32 value) override {
        	PYBIND11_OVERLOAD(void, BTextControl, SetValue, value);
        }
        status_t			Invoke(BMessage* message = NULL) override {
        	PYBIND11_OVERLOAD(status_t, BTextControl, Invoke, message);
        }
        void				SetModificationMessage(BMessage* message) override {
        	PYBIND11_OVERLOAD(void, BTextControl, SetModificationMessage, message);
        }
        void				SetAlignment(alignment label, alignment text) override {
        	PYBIND11_OVERLOAD(void, BTextControl, SetAlignment, label, text);
        }
        void				SetDivider(float position) override {
        	PYBIND11_OVERLOAD(void, BTextControl, SetDivider, position);
        }
        void				Draw(BRect updateRect) override {
        	PYBIND11_OVERLOAD(void, BTextControl, Draw, updateRect);
        }
        void				MouseDown(BPoint where) override {
        	PYBIND11_OVERLOAD(void, BTextControl, MouseDown, where);
        }
        void				AttachedToWindow() override {
        	PYBIND11_OVERLOAD(void, BTextControl, AttachedToWindow);
        }
        void				MakeFocus(bool focus = true) override {
        	PYBIND11_OVERLOAD(void, BTextControl, MakeFocus, focus);
        }
        void				SetEnabled(bool enable) override {
        	PYBIND11_OVERLOAD(void, BTextControl, SetEnabled, enable);
        }
        void				FrameMoved(BPoint newPosition) override {
        	PYBIND11_OVERLOAD(void, BTextControl, FrameMoved, newPosition);
        }
        void				FrameResized(float newWidth, float newHeight) override {
        	PYBIND11_OVERLOAD(void, BTextControl, FrameResized, newWidth, newHeight);
        }
        void				WindowActivated(bool active) override {
        	PYBIND11_OVERLOAD(void, BTextControl, WindowActivated, active);
        }
        void				GetPreferredSize(float* _width, float* _height) override {
        	PYBIND11_OVERLOAD(void, BTextControl, GetPreferredSize, _width, _height);
        }
        void				ResizeToPreferred() override {
        	PYBIND11_OVERLOAD(void, BTextControl, ResizeToPreferred);
        }
        void				MessageReceived(BMessage* message) override {
        	PYBIND11_OVERLOAD(void, BTextControl, MessageReceived, message);
        }
        BHandler*			ResolveSpecifier(BMessage* message, int32 index, BMessage* specifier, int32 what, const char* property) override {
        	PYBIND11_OVERLOAD(BHandler*, BTextControl, ResolveSpecifier, message, index, specifier, what, property);
        }
        void				MouseUp(BPoint where) override {
        	PYBIND11_OVERLOAD(void, BTextControl, MouseUp, where);
        }
        void				MouseMoved(BPoint where, uint32 transit, const BMessage* dragMessage) override {
        	PYBIND11_OVERLOAD(void, BTextControl, MouseMoved, where, transit, dragMessage);
        }
        void				DetachedFromWindow() override {
        	PYBIND11_OVERLOAD(void, BTextControl, DetachedFromWindow);
        }
        void				AllAttached() override {
        	PYBIND11_OVERLOAD(void, BTextControl, AllAttached);
        }
        void				AllDetached() override {
        	PYBIND11_OVERLOAD(void, BTextControl, AllDetached);
        }
        status_t			GetSupportedSuites(BMessage* data) override {
        	PYBIND11_OVERLOAD(status_t, BTextControl, GetSupportedSuites, data);
        }
        void				SetFlags(uint32 flags) override {
        	PYBIND11_OVERLOAD(void, BTextControl, SetFlags, flags);
        }
        BSize				MinSize() override {
        	PYBIND11_OVERLOAD(BSize, BTextControl, MinSize);
        }
        BSize				MaxSize() override {
        	PYBIND11_OVERLOAD(BSize, BTextControl, MaxSize);
        }
        BSize				PreferredSize() override {
        	PYBIND11_OVERLOAD(BSize, BTextControl, PreferredSize);
        }
        BAlignment			LayoutAlignment() override {
        	PYBIND11_OVERLOAD(BAlignment, BTextControl, LayoutAlignment);
        }
};

PYBIND11_MODULE(TextControl,m)
{
py::class_<BTextControl, PyBTextControl, BControl, std::unique_ptr<BTextControl, py::nodelete>>(m, "BTextControl")
.def(py::init<BRect, const char *, const char *, const char *, BMessage *, unsigned int, unsigned int>(), "", py::arg("frame"), py::arg("name"), py::arg("label"), py::arg("initialText"), py::arg("message"), py::arg("resizeMask")=B_FOLLOW_LEFT_TOP, py::arg("flags")=B_WILL_DRAW | B_NAVIGABLE)
.def(py::init<const char *, const char *, const char *, BMessage *, unsigned int>(), "", py::arg("name"), py::arg("label"), py::arg("initialText"), py::arg("message"), py::arg("flags")=B_WILL_DRAW | B_NAVIGABLE)
.def(py::init<const char *, const char *, BMessage *>(), "", py::arg("label"), py::arg("initialText"), py::arg("message"))
.def(py::init<BMessage *>(), "", py::arg("archive"))
.def_static("Instantiate", &BTextControl::Instantiate, "", py::arg("archive"))
.def("Archive", &BTextControl::Archive, "", py::arg("archive"), py::arg("deep")=true)
.def("SetText", &BTextControl::SetText, "", py::arg("text"))
.def("Text", &BTextControl::Text, "")
.def("TextLength", &BTextControl::TextLength, "")
.def("MarkAsInvalid", &BTextControl::MarkAsInvalid, "", py::arg("invalid"))
.def("SetValue", &BTextControl::SetValue, "", py::arg("value"))
.def("Invoke", &BTextControl::Invoke, "", py::arg("message")=NULL)
.def("TextView", &BTextControl::TextView, "")
.def("SetModificationMessage", &BTextControl::SetModificationMessage, "", py::arg("message"))
.def("ModificationMessage", &BTextControl::ModificationMessage, "")
.def("SetAlignment", &BTextControl::SetAlignment, "", py::arg("label"), py::arg("text"))
.def("GetAlignment", &BTextControl::GetAlignment, "", py::arg("_label"), py::arg("_text"))
.def("SetDivider", &BTextControl::SetDivider, "", py::arg("position"))
.def("Divider", &BTextControl::Divider, "")
.def("Draw", &BTextControl::Draw, "", py::arg("updateRect"))
.def("MouseDown", &BTextControl::MouseDown, "", py::arg("where"))
.def("AttachedToWindow", &BTextControl::AttachedToWindow, "")
.def("MakeFocus", &BTextControl::MakeFocus, "", py::arg("focus")=true)
.def("SetEnabled", &BTextControl::SetEnabled, "", py::arg("enable"))
.def("FrameMoved", &BTextControl::FrameMoved, "", py::arg("newPosition"))
.def("FrameResized", &BTextControl::FrameResized, "", py::arg("newWidth"), py::arg("newHeight"))
.def("WindowActivated", &BTextControl::WindowActivated, "", py::arg("active"))
.def("GetPreferredSize", &BTextControl::GetPreferredSize, "", py::arg("_width"), py::arg("_height"))
.def("ResizeToPreferred", &BTextControl::ResizeToPreferred, "")
.def("MessageReceived", &BTextControl::MessageReceived, "", py::arg("message"))
.def("ResolveSpecifier", &BTextControl::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("what"), py::arg("property"))
.def("MouseUp", &BTextControl::MouseUp, "", py::arg("where"))
.def("MouseMoved", &BTextControl::MouseMoved, "", py::arg("where"), py::arg("transit"), py::arg("dragMessage"))
.def("DetachedFromWindow", &BTextControl::DetachedFromWindow, "")
.def("AllAttached", &BTextControl::AllAttached, "")
.def("AllDetached", &BTextControl::AllDetached, "")
.def("GetSupportedSuites", &BTextControl::GetSupportedSuites, "", py::arg("data"))
.def("SetFlags", &BTextControl::SetFlags, "", py::arg("flags"))
.def("MinSize", &BTextControl::MinSize, "")
.def("MaxSize", &BTextControl::MaxSize, "")
.def("PreferredSize", &BTextControl::PreferredSize, "")
.def("LayoutAlignment", &BTextControl::LayoutAlignment, "")
.def("CreateLabelLayoutItem", &BTextControl::CreateLabelLayoutItem, "")
.def("CreateTextViewLayoutItem", &BTextControl::CreateTextViewLayoutItem, "")
;

//m.attr("_BTextInput_") = _BTextInput_;
}
