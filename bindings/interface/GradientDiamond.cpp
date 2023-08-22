#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/GradientDiamond.h>
#include <Gradient.h>

namespace py = pybind11;


PYBIND11_MODULE(GradientDiamond,m)
{
py::class_<BGradientDiamond, BGradient>(m, "BGradientDiamond")
.def(py::init(), "")
.def(py::init<const BPoint &>(), "", py::arg("center"))
.def(py::init<float, float>(), "", py::arg("cx"), py::arg("cy"))
.def("Center", &BGradientDiamond::Center, "")
.def("SetCenter", py::overload_cast<const BPoint &>(&BGradientDiamond::SetCenter), "", py::arg("center"))
.def("SetCenter", py::overload_cast<float, float>(&BGradientDiamond::SetCenter), "", py::arg("cx"), py::arg("cy"))
;


}
