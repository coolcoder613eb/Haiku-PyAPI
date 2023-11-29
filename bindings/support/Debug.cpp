#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/Debug.h>

namespace py = pybind11;


void define_Debug(py::module_& m)
{
m.attr("_rtDebugFlag") = py::cast(_rtDebugFlag);

m.def("_debugFlag", &_debugFlag, "", py::arg(""));

m.def("_setDebugFlag", &_setDebugFlag, "", py::arg(""));

m.def("_debugPrintf", py::overload_cast<const char *,)>(&_debugPrintf), "", py::arg("_PRINTFLIKE(1,2"));

m.def("_sPrintf", py::overload_cast<const char *,)>(&_sPrintf), "", py::arg("_PRINTFLIKE(1,2"));

m.def("_debugPrintf", py::overload_cast<const char *>(&_debugPrintf), "", py::arg(""));

m.def("_sPrintf", py::overload_cast<const char *>(&_sPrintf), "", py::arg(""));

m.def("_xdebugPrintf", &_xdebugPrintf, "", py::arg(""));

m.def("_debuggerAssert", &_debuggerAssert, "", py::arg(""), py::arg(""), py::arg(""));

}
