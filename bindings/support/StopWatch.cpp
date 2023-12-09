#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/StopWatch.h>

namespace py = pybind11;


void define_StopWatch(py::module_& m)
{
py::class_<BStopWatch>(m, "BStopWatch")
.def(py::init<const char *, bool>(), "", py::arg("name"), py::arg("silent")=false)
.def("Suspend", &BStopWatch::Suspend, "")
.def("Resume", &BStopWatch::Resume, "")
.def("Lap", &BStopWatch::Lap, "")
.def("ElapsedTime", &BStopWatch::ElapsedTime, "")
.def("Reset", &BStopWatch::Reset, "")
.def("Name", &BStopWatch::Name, "")
;


}
