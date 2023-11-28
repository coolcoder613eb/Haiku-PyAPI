#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/Beep.h>

namespace py = pybind11;


void define_Beep(py::module_& m)
{
m.def("beep", &beep, "");

m.def("system_beep", &system_beep, "", py::arg("eventName"));

m.def("add_system_beep_event", &add_system_beep_event, "", py::arg("eventName"), py::arg("flags")=0);

}
