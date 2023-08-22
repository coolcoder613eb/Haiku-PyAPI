#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/GroupView.h>
#include <GroupLayout.h>
#include <View.h>

namespace py = pybind11;


PYBIND11_MODULE(GroupView,m)
{
py::class_<BGroupView, BView>(m, "BGroupView")
.def(py::init<orientation, float>(), "", py::arg("orientation")=B_HORIZONTAL, py::arg("spacing")=B_USE_DEFAULT_SPACING)
.def(py::init<const char *, orientation, float>(), "", py::arg("name"), py::arg("orientation")=B_HORIZONTAL, py::arg("spacing")=B_USE_DEFAULT_SPACING)
.def(py::init<BMessage *>(), "", py::arg("from"))
.def("SetLayout", &BGroupView::SetLayout, "", py::arg("layout"))
.def("GroupLayout", &BGroupView::GroupLayout, "")
.def_static("Instantiate", &BGroupView::Instantiate, "", py::arg("from"))
.def("Perform", &BGroupView::Perform, "", py::arg("d"), py::arg("arg"))
;


}
