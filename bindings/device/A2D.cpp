#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <device/A2D.h>

namespace py = pybind11;


PYBIND11_MODULE(A2D,m)
{
py::class_<BA2D>(m, "BA2D")
.def(py::init(), "")
.def("Open", &BA2D::Open, "", py::arg("portName"))
.def("Close", &BA2D::Close, "")
.def("IsOpen", &BA2D::IsOpen, "")
.def("Read", &BA2D::Read, "", py::arg("buf"))
;


}
