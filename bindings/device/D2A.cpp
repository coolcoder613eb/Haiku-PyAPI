#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <device/D2A.h>

namespace py = pybind11;


PYBIND11_MODULE(D2A,m)
{
py::class_<BD2A>(m, "BD2A")
.def(py::init(), "")
.def("Open", &BD2A::Open, "", py::arg("portName"))
.def("Close", &BD2A::Close, "")
.def("IsOpen", &BD2A::IsOpen, "")
.def("Read", &BD2A::Read, "", py::arg("buf"))
.def("Write", &BD2A::Write, "", py::arg("value"))
;


}
