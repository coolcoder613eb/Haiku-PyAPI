#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/SplitLayoutBuilder.h>
#include <SplitView.h>

namespace py = pybind11;


PYBIND11_MODULE(SplitLayoutBuilder,m)
{
py::class_<BSplitLayoutBuilder>(m, "BSplitLayoutBuilder")
.def(py::init<orientation, float>(), "", py::arg("orientation")=B_HORIZONTAL, py::arg("spacing")=B_USE_DEFAULT_SPACING)
.def(py::init<BSplitView *>(), "", py::arg("view"))
.def("SplitView", &BSplitLayoutBuilder::SplitView, "")
.def("GetSplitView", &BSplitLayoutBuilder::GetSplitView, "", py::arg("view"))
.def("Add", py::overload_cast<BView *>(&BSplitLayoutBuilder::Add), "", py::arg("view"))
.def("Add", py::overload_cast<BView *, float>(&BSplitLayoutBuilder::Add), "", py::arg("view"), py::arg("weight"))
.def("Add", py::overload_cast<BLayoutItem *>(&BSplitLayoutBuilder::Add), "", py::arg("item"))
.def("Add", py::overload_cast<BLayoutItem *, float>(&BSplitLayoutBuilder::Add), "", py::arg("item"), py::arg("weight"))
.def("SetCollapsible", &BSplitLayoutBuilder::SetCollapsible, "", py::arg("collapsible"))
.def("SetInsets", &BSplitLayoutBuilder::SetInsets, "", py::arg("left"), py::arg("top"), py::arg("right"), py::arg("bottom"))
.def("operatorBSplitView*", &BSplitLayoutBuilder::operatorBSplitView*, "")
;


}
