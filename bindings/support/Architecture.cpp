#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/Architecture.h>

namespace py = pybind11;


void define_Architecture(py::module_& m)
{
m.def("get_architecture", &get_architecture, "");

m.def("get_primary_architecture", &get_primary_architecture, "");

m.def("get_secondary_architectures", py::overload_cast<const char * *, size_t>(&get_secondary_architectures), "", py::arg("architectures"), py::arg("count"));

m.def("get_architectures", py::overload_cast<const char * *, size_t>(&get_architectures), "", py::arg("architectures"), py::arg("count"));

m.def("guess_architecture_for_path", &guess_architecture_for_path, "", py::arg("path"));

m.def("get_secondary_architectures", []() {
    BStringList  _architectures;
    status_t r = get_secondary_architectures(_architectures);
    return std::make_tuple(r,_architectures);
}
, "");

m.def("get_architectures", []() {
    BStringList  _architectures;
    status_t r = get_architectures(_architectures);
    return std::make_tuple(r,_architectures);
}
, "");

}
