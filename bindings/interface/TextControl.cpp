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

PYBIND11_MODULE(TextControl,m)
{


py::class_<BTextControl, BControl>(m, "BTextControl")
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
