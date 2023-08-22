#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/Alignment.h>
#include <InterfaceDefs.h>

namespace py = pybind11;


PYBIND11_MODULE(Alignment,m)
{
py::class_<BAlignment>(m, "BAlignment")
.def(py::init(), "")
.def(py::init<const BAlignment &>(), "", py::arg("other"))
.def(py::init<alignment, vertical_alignment>(), "", py::arg("horizontal"), py::arg("vertical"))
.def("Horizontal", &BAlignment::Horizontal, "")
.def("Vertical", &BAlignment::Vertical, "")
.def("RelativeHorizontal", &BAlignment::RelativeHorizontal, "")
.def("RelativeVertical", &BAlignment::RelativeVertical, "")
.def("SetHorizontal", &BAlignment::SetHorizontal, "", py::arg("horizontal"))
.def("SetVertical", &BAlignment::SetVertical, "", py::arg("vertical"))
.def("IsHorizontalSet", &BAlignment::IsHorizontalSet, "")
.def("IsVerticalSet", &BAlignment::IsVerticalSet, "")
.def("__eq__", &BAlignment::operator==, "", py::arg("other"))
.def("__ne__", &BAlignment::operator!=, "", py::arg("other"))
.def("operator=", &BAlignment::operator=, "", py::arg("other"))
.def_readwrite("horizontal", &BAlignment::horizontal, "")
.def_readwrite("vertical", &BAlignment::vertical, "")
;

m.def("__eq__", &operator==, "", py::arg("other"));

m.def("__ne__", &operator!=, "", py::arg("other"));

m.def("operator=", &operator=, "", py::arg("other"));

}
