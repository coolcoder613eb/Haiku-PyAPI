#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/TwoDimensionalLayout.h>
#include <AbstractLayout.h>

namespace py = pybind11;


PYBIND11_MODULE(TwoDimensionalLayout,m)
{
py::class_<BTwoDimensionalLayout, BAbstractLayout>(m, "BTwoDimensionalLayout")
.def(py::init(), "")
.def(py::init<BMessage *>(), "", py::arg("from"))
.def("SetInsets", py::overload_cast<float, float, float, float>(&BTwoDimensionalLayout::SetInsets), "", py::arg("left"), py::arg("top"), py::arg("right"), py::arg("bottom"))
.def("SetInsets", py::overload_cast<float, float>(&BTwoDimensionalLayout::SetInsets), "", py::arg("horizontal"), py::arg("vertical"))
.def("SetInsets", py::overload_cast<float>(&BTwoDimensionalLayout::SetInsets), "", py::arg("insets"))
.def("GetInsets", &BTwoDimensionalLayout::GetInsets, "", py::arg("left"), py::arg("top"), py::arg("right"), py::arg("bottom"))
.def("AlignLayoutWith", &BTwoDimensionalLayout::AlignLayoutWith, "", py::arg("other"), py::arg("orientation"))
.def("BaseMinSize", &BTwoDimensionalLayout::BaseMinSize, "")
.def("BaseMaxSize", &BTwoDimensionalLayout::BaseMaxSize, "")
.def("BasePreferredSize", &BTwoDimensionalLayout::BasePreferredSize, "")
.def("BaseAlignment", &BTwoDimensionalLayout::BaseAlignment, "")
.def("HasHeightForWidth", &BTwoDimensionalLayout::HasHeightForWidth, "")
.def("GetHeightForWidth", &BTwoDimensionalLayout::GetHeightForWidth, "", py::arg("width"), py::arg("min"), py::arg("max"), py::arg("preferred"))
.def("SetFrame", &BTwoDimensionalLayout::SetFrame, "", py::arg("frame"))
.def("Archive", &BTwoDimensionalLayout::Archive, "", py::arg("into"), py::arg("deep")=true)
.def("Perform", &BTwoDimensionalLayout::Perform, "", py::arg("d"), py::arg("arg"))
;

py::class_<ColumnRowConstraints>(m, "ColumnRowConstraints")
.def_readwrite("weight", &ColumnRowConstraints::weight, "")
.def_readwrite("min", &ColumnRowConstraints::min, "")
.def_readwrite("max", &ColumnRowConstraints::max, "")
;

py::class_<Dimensions>(m, "Dimensions")
.def_readwrite("x", &Dimensions::x, "")
.def_readwrite("y", &Dimensions::y, "")
.def_readwrite("width", &Dimensions::width, "")
.def_readwrite("height", &Dimensions::height, "")
;


}
