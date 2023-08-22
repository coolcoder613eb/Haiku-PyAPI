#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/GradientLinear.h>
#include <Gradient.h>

namespace py = pybind11;


PYBIND11_MODULE(GradientLinear,m)
{
py::class_<BGradientLinear, BGradient>(m, "BGradientLinear")
.def(py::init(), "")
.def(py::init<const BPoint &, const BPoint &>(), "", py::arg("start"), py::arg("end"))
.def(py::init<float, float, float, float>(), "", py::arg("x1"), py::arg("y1"), py::arg("x2"), py::arg("y2"))
.def("Start", &BGradientLinear::Start, "")
.def("SetStart", py::overload_cast<const BPoint &>(&BGradientLinear::SetStart), "", py::arg("start"))
.def("SetStart", py::overload_cast<float, float>(&BGradientLinear::SetStart), "", py::arg("x1"), py::arg("y1"))
.def("End", &BGradientLinear::End, "")
.def("SetEnd", py::overload_cast<const BPoint &>(&BGradientLinear::SetEnd), "", py::arg("end"))
.def("SetEnd", py::overload_cast<float, float>(&BGradientLinear::SetEnd), "", py::arg("x2"), py::arg("y2"))
;


}
