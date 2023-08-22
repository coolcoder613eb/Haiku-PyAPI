#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/GradientRadial.h>
#include <Gradient.h>

namespace py = pybind11;


PYBIND11_MODULE(GradientRadial,m)
{
py::class_<BGradientRadial, BGradient>(m, "BGradientRadial")
.def(py::init(), "")
.def(py::init<const BPoint &, float>(), "", py::arg("center"), py::arg("radius"))
.def(py::init<float, float, float>(), "", py::arg("cx"), py::arg("cy"), py::arg("radius"))
.def("Center", &BGradientRadial::Center, "")
.def("SetCenter", py::overload_cast<const BPoint &>(&BGradientRadial::SetCenter), "", py::arg("center"))
.def("SetCenter", py::overload_cast<float, float>(&BGradientRadial::SetCenter), "", py::arg("cx"), py::arg("cy"))
.def("Radius", &BGradientRadial::Radius, "")
.def("SetRadius", &BGradientRadial::SetRadius, "", py::arg("radius"))
;


}
