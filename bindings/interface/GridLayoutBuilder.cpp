#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/GridLayoutBuilder.h>
#include <GridView.h>

namespace py = pybind11;


PYBIND11_MODULE(GridLayoutBuilder,m)
{
py::class_<BGridLayoutBuilder>(m, "BGridLayoutBuilder")
.def(py::init<float, float>(), "", py::arg("horizontal")=B_USE_DEFAULT_SPACING, py::arg("vertical")=B_USE_DEFAULT_SPACING)
.def(py::init<BGridLayout *>(), "", py::arg("layout"))
.def(py::init<BGridView *>(), "", py::arg("view"))
.def("GridLayout", &BGridLayoutBuilder::GridLayout, "")
.def("GetGridLayout", &BGridLayoutBuilder::GetGridLayout, "", py::arg("_layout"))
.def("View", &BGridLayoutBuilder::View, "")
.def("GetView", &BGridLayoutBuilder::GetView, "", py::arg("_view"))
.def("Add", py::overload_cast<BView *, int, int, int, int>(&BGridLayoutBuilder::Add), "", py::arg("view"), py::arg("column"), py::arg("row"), py::arg("columnCount")=1, py::arg("rowCount")=1)
.def("Add", py::overload_cast<BLayoutItem *, int, int, int, int>(&BGridLayoutBuilder::Add), "", py::arg("item"), py::arg("column"), py::arg("row"), py::arg("columnCount")=1, py::arg("rowCount")=1)
.def("SetColumnWeight", &BGridLayoutBuilder::SetColumnWeight, "", py::arg("column"), py::arg("weight"))
.def("SetRowWeight", &BGridLayoutBuilder::SetRowWeight, "", py::arg("row"), py::arg("weight"))
.def("SetInsets", &BGridLayoutBuilder::SetInsets, "", py::arg("left"), py::arg("top"), py::arg("right"), py::arg("bottom"))
.def("operatorBGridLayout*", &BGridLayoutBuilder::operatorBGridLayout*, "")
;


}
