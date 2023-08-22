#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/GridView.h>
#include <GridLayout.h>
#include <View.h>

namespace py = pybind11;


PYBIND11_MODULE(GridView,m)
{
py::class_<BGridView, BView>(m, "BGridView")
.def(py::init<float, float>(), "", py::arg("horizontal")=B_USE_DEFAULT_SPACING, py::arg("vertical")=B_USE_DEFAULT_SPACING)
.def(py::init<const char *, float, float>(), "", py::arg("name"), py::arg("horizontal")=B_USE_DEFAULT_SPACING, py::arg("vertical")=B_USE_DEFAULT_SPACING)
.def(py::init<BMessage *>(), "", py::arg("from"))
.def("SetLayout", &BGridView::SetLayout, "", py::arg("layout"))
.def("GridLayout", &BGridView::GridLayout, "")
.def_static("Instantiate", &BGridView::Instantiate, "", py::arg("from"))
.def("Perform", &BGridView::Perform, "", py::arg("d"), py::arg("arg"))
;


}
