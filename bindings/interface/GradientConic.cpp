#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/GradientConic.h>
#include <Gradient.h>

namespace py = pybind11;


PYBIND11_MODULE(GradientConic,m)
{
py::class_<BGradientConic, BGradient>(m, "BGradientConic")
.def(py::init(), "")
.def(py::init<const BPoint &, float>(), "", py::arg("center"), py::arg("angle"))
.def(py::init<float, float, float>(), "", py::arg("cx"), py::arg("cy"), py::arg("angle"))
.def("Center", &BGradientConic::Center, "")
.def("SetCenter", py::overload_cast<const BPoint &>(&BGradientConic::SetCenter), "", py::arg("center"))
.def("SetCenter", py::overload_cast<float, float>(&BGradientConic::SetCenter), "", py::arg("cx"), py::arg("cy"))
.def("Angle", &BGradientConic::Angle, "")
.def("SetAngle", &BGradientConic::SetAngle, "", py::arg("angle"))
;


}
