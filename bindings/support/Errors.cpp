#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/Errors.h>

namespace py = pybind11;


void define_Errors(py::module_& m)
{
m.def("_to_positive_error", &_to_positive_error, "", py::arg("error"));

m.def("_to_negative_error", &_to_negative_error, "", py::arg("error"));

}
