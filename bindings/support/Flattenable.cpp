#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/Flattenable.h>

namespace py = pybind11;


PYBIND11_MODULE(Flattenable, m)
{
py::class_<BFlattenable>(m, "BFlattenable")
.def("IsFixedSize", &BFlattenable::IsFixedSize, "")
.def("TypeCode", &BFlattenable::TypeCode, "")
.def("FlattenedSize", &BFlattenable::FlattenedSize, "")
.def("Flatten", &BFlattenable::Flatten, "", py::arg("buffer"), py::arg("size"))
.def("AllowsTypeCode", &BFlattenable::AllowsTypeCode, "", py::arg("code"))
.def("Unflatten", &BFlattenable::Unflatten, "", py::arg("code"), py::arg("buffer"), py::arg("size"))
;


}
