#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/parsedate.h>

namespace py = pybind11;


void define_parsedate(py::module_& m)
{
m.def("parsedate", &parsedate, "", py::arg("dateString"), py::arg("now"));

m.def("parsedate_etc", &parsedate_etc, "", py::arg("dateString"), py::arg("now"), py::arg("_storedFlags"));

m.def("set_dateformats", &set_dateformats, "", py::arg("table"));

m.def("get_dateformats", &get_dateformats, "", py::arg(""));

}
