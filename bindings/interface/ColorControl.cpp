#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/ColorControl.h>
#include <interface/Layout.h>
#include <interface/Bitmap.h>
#include <Control.h>

namespace py = pybind11;


PYBIND11_MODULE(ColorControl,m)
{
py::enum_<color_control_layout>(m, "color_control_layout", "")
.value("B_CELLS_4x64", color_control_layout::B_CELLS_4x64, "")
.value("B_CELLS_8x32", color_control_layout::B_CELLS_8x32, "")
.value("B_CELLS_16x16", color_control_layout::B_CELLS_16x16, "")
.value("B_CELLS_32x8", color_control_layout::B_CELLS_32x8, "")
.value("B_CELLS_64x4", color_control_layout::B_CELLS_64x4, "")
.export_values();

py::class_<BColorControl, BControl,std::unique_ptr<BColorControl, py::nodelete>>(m, "BColorControl")
.def(py::init<BPoint, color_control_layout, float, const char *, BMessage *, bool>(), "", py::arg("start"), py::arg("layout"), py::arg("cellSize"), py::arg("name"), py::arg("message")=NULL, py::arg("useOffscreen")=false)
.def(py::init<BMessage *>(), "", py::arg("data"))
.def_static("Instantiate", &BColorControl::Instantiate, "", py::arg("data"))
.def("Archive", &BColorControl::Archive, "", py::arg("data"), py::arg("deep")=true)
.def("SetLayout", py::overload_cast<BLayout *>(&BColorControl::SetLayout), "", py::arg("layout"))
.def("SetValue", py::overload_cast<int>(&BColorControl::SetValue), "", py::arg("color_value"))
.def("SetValue", py::overload_cast<rgb_color>(&BColorControl::SetValue), "", py::arg("color"))
.def("ValueAsColor", &BColorControl::ValueAsColor, "")
.def("SetEnabled", &BColorControl::SetEnabled, "", py::arg("state"))
.def("AttachedToWindow", &BColorControl::AttachedToWindow, "")
.def("MessageReceived", &BColorControl::MessageReceived, "", py::arg("message"))
.def("Draw", &BColorControl::Draw, "", py::arg("updateRect"))
.def("MouseDown", &BColorControl::MouseDown, "", py::arg("where"))
.def("KeyDown", &BColorControl::KeyDown, "", py::arg("bytes"), py::arg("numBytes"))
.def("SetCellSize", &BColorControl::SetCellSize, "", py::arg("size"))
.def("CellSize", &BColorControl::CellSize, "")
.def("SetLayout", py::overload_cast<color_control_layout>(&BColorControl::SetLayout), "", py::arg("layout"))
.def("Layout", &BColorControl::Layout, "")
.def("WindowActivated", &BColorControl::WindowActivated, "", py::arg("state"))
.def("MouseUp", &BColorControl::MouseUp, "", py::arg("point"))
.def("MouseMoved", &BColorControl::MouseMoved, "", py::arg("point"), py::arg("code"), py::arg("dragMessage"))
.def("DetachedFromWindow", &BColorControl::DetachedFromWindow, "")
.def("GetPreferredSize", &BColorControl::GetPreferredSize, "", py::arg("_width"), py::arg("_height"))
.def("ResizeToPreferred", &BColorControl::ResizeToPreferred, "")
.def("Invoke", &BColorControl::Invoke, "", py::arg("message")=NULL)
.def("FrameMoved", &BColorControl::FrameMoved, "", py::arg("newPosition"))
.def("FrameResized", &BColorControl::FrameResized, "", py::arg("newWidth"), py::arg("newHeight"))
.def("ResolveSpecifier", &BColorControl::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("what"), py::arg("property"))
.def("GetSupportedSuites", &BColorControl::GetSupportedSuites, "", py::arg("data"))
.def("MakeFocus", &BColorControl::MakeFocus, "", py::arg("focused")=true)
.def("AllAttached", &BColorControl::AllAttached, "")
.def("AllDetached", &BColorControl::AllDetached, "")
.def("SetIcon", &BColorControl::SetIcon, "", py::arg("icon"), py::arg("flags")=0)
;


}
