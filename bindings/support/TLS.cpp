#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/TLS.h>

namespace py = pybind11;


void define_TLS(py::module_& m)
{
m.def("tls_allocate", &tls_allocate, "", py::arg(""));

m.def("tls_get", &tls_get, "", py::arg("index"));

m.def("tls_address", &tls_address, "", py::arg("index"));

m.def("tls_set", &tls_set, "", py::arg("index"), py::arg("value"));

}
