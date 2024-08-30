#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <device/DigitalPort.h>

namespace py = pybind11;


PYBIND11_MODULE(DigitalPort,m)
{
py::class_<BDigitalPort>(m, "BDigitalPort")
.def(py::init(), "")
.def("Open", &BDigitalPort::Open, "", py::arg("portName"))
.def("Close", &BDigitalPort::Close, "")
.def("IsOpen", &BDigitalPort::IsOpen, "")
.def("Read", &BDigitalPort::Read, "", py::arg("buf"))
.def("Write", &BDigitalPort::Write, "", py::arg("value"))
.def("SetAsOutput", &BDigitalPort::SetAsOutput, "")
.def("IsOutput", &BDigitalPort::IsOutput, "")
.def("SetAsInput", &BDigitalPort::SetAsInput, "")
.def("IsInput", &BDigitalPort::IsInput, "")
;


}
