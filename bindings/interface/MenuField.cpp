#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/MenuField.h>
#include <Menu.h>
#include <LayoutItem.h>
#include <MenuItem.h>
#include <MenuBar.h>

namespace py = pybind11;


PYBIND11_MODULE(MenuField,m)
{
py::class_<BMenuField, BView, std::unique_ptr<BMenuField,py::nodelete>>(m, "BMenuField")
.def(py::init<BRect, const char *, const char *, BMenu *, unsigned int, unsigned int>(), "", py::arg("frame"), py::arg("name"), py::arg("label"), py::arg("menu"), py::arg("resizingMode")=B_FOLLOW_LEFT_TOP, py::arg("flags")=B_WILL_DRAW | B_NAVIGABLE)
.def(py::init<BRect, const char *, const char *, BMenu *, bool, unsigned int, unsigned int>(), "", py::arg("frame"), py::arg("name"), py::arg("label"), py::arg("menu"), py::arg("fixed_size"), py::arg("resizingMode")=B_FOLLOW_LEFT_TOP, py::arg("flags")=B_WILL_DRAW | B_NAVIGABLE)
.def(py::init<const char *, const char *, BMenu *, unsigned int>(), "", py::arg("name"), py::arg("label"), py::arg("menu"), py::arg("flags")=B_WILL_DRAW | B_NAVIGABLE)
.def(py::init<const char *, BMenu *, unsigned int>(), "", py::arg("label"), py::arg("menu"), py::arg("flags")=B_WILL_DRAW | B_NAVIGABLE)
.def(py::init<BMessage *>(), "", py::arg("data"))
.def_static("Instantiate", &BMenuField::Instantiate, "", py::arg("archive"))
.def("Archive", &BMenuField::Archive, "", py::arg("archive"), py::arg("deep")=true)
.def("Draw", &BMenuField::Draw, "", py::arg("updateRect"))
.def("AttachedToWindow", &BMenuField::AttachedToWindow, "")
.def("AllAttached", &BMenuField::AllAttached, "")
.def("MouseDown", &BMenuField::MouseDown, "", py::arg("where"))
.def("KeyDown", &BMenuField::KeyDown, "", py::arg("bytes"), py::arg("numBytes"))
.def("MakeFocus", &BMenuField::MakeFocus, "", py::arg("focused"))
.def("MessageReceived", &BMenuField::MessageReceived, "", py::arg("message"))
.def("WindowActivated", &BMenuField::WindowActivated, "", py::arg("active"))
.def("MouseUp", &BMenuField::MouseUp, "", py::arg("where"))
.def("MouseMoved", &BMenuField::MouseMoved, "", py::arg("where"), py::arg("transit"), py::arg("dragMessage"))
.def("DetachedFromWindow", &BMenuField::DetachedFromWindow, "")
.def("AllDetached", &BMenuField::AllDetached, "")
.def("FrameMoved", &BMenuField::FrameMoved, "", py::arg("where"))
.def("FrameResized", &BMenuField::FrameResized, "", py::arg("width"), py::arg("height"))
.def("Menu", &BMenuField::Menu)
.def("MenuBar", &BMenuField::MenuBar, "")
.def("MenuItem", &BMenuField::MenuItem, "")
.def("SetLabel", &BMenuField::SetLabel, "", py::arg("label"))
.def("Label", &BMenuField::Label, "")
.def("SetEnabled", &BMenuField::SetEnabled, "", py::arg("on"))
.def("IsEnabled", &BMenuField::IsEnabled, "")
.def("SetAlignment", &BMenuField::SetAlignment, "", py::arg("label"))
.def("Alignment", &BMenuField::Alignment, "")
.def("SetDivider", &BMenuField::SetDivider, "", py::arg("position"))
.def("Divider", &BMenuField::Divider, "")
.def("ShowPopUpMarker", &BMenuField::ShowPopUpMarker, "")
.def("HidePopUpMarker", &BMenuField::HidePopUpMarker, "")
.def("ResolveSpecifier", &BMenuField::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("form"), py::arg("property"))
.def("GetSupportedSuites", &BMenuField::GetSupportedSuites, "", py::arg("data"))
.def("ResizeToPreferred", &BMenuField::ResizeToPreferred, "")
.def("GetPreferredSize", &BMenuField::GetPreferredSize, "", py::arg("width"), py::arg("height"))
.def("MinSize", &BMenuField::MinSize, "")
.def("MaxSize", &BMenuField::MaxSize, "")
.def("PreferredSize", &BMenuField::PreferredSize, "")
.def("CreateLabelLayoutItem", &BMenuField::CreateLabelLayoutItem, "")
.def("CreateMenuBarLayoutItem", &BMenuField::CreateMenuBarLayoutItem, "")
.def("Perform", &BMenuField::Perform, "", py::arg("d"), py::arg("arg"))
;


}
