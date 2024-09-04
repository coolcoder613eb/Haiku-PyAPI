#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <media/Controllable.h>
#include <media/ParameterWeb.h>

namespace py = pybind11;
using namespace BPrivate;
//using namespace BPrivate::media;

PYBIND11_MODULE(Controllable, m)
{
py::class_<BControllable, BMediaNode, std::unique_ptr<BControllable,py::nodelete>>(m, "BControllable")
.def("Web", &BControllable::Web, "")
.def("LockParameterWeb", &BControllable::LockParameterWeb, "")
.def("UnlockParameterWeb", &BControllable::UnlockParameterWeb, "")
;


}
