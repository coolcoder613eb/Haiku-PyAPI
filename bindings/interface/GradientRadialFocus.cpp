#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/GradientRadialFocus.h>
#include <Gradient.h>

namespace py = pybind11;


PYBIND11_MODULE(GradientRadialFocus,m)
{
py::class_<BGradientRadialFocus, BGradient>(m, "BGradientRadialFocus")
.def(py::init(), "")
.def(py::init<const BPoint &, float, const BPoint &>(), "", py::arg("center"), py::arg("radius"), py::arg("focal"))
.def(py::init<float, float, float, float, float>(), "", py::arg("cx"), py::arg("cy"), py::arg("radius"), py::arg("fx"), py::arg("fy"))
.def("Center", &BGradientRadialFocus::Center, "")
.def("SetCenter", py::overload_cast<const BPoint &>(&BGradientRadialFocus::SetCenter), "", py::arg("center"))
.def("SetCenter", py::overload_cast<float, float>(&BGradientRadialFocus::SetCenter), "", py::arg("cx"), py::arg("cy"))
.def("Focal", &BGradientRadialFocus::Focal, "")
.def("SetFocal", py::overload_cast<const BPoint &>(&BGradientRadialFocus::SetFocal), "", py::arg("focal"))
.def("SetFocal", py::overload_cast<float, float>(&BGradientRadialFocus::SetFocal), "", py::arg("fx"), py::arg("fy"))
.def("Radius", &BGradientRadialFocus::Radius, "")
.def("SetRadius", &BGradientRadialFocus::SetRadius, "", py::arg("radius"))
;


}
