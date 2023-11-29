#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/Autolock.h>

namespace py = pybind11;


void define_Autolock(py::module_& m)
{
py::class_<BAutolock>(m, "BAutolock")
.def(py::init<BLooper *>(), "", py::arg("looper"))
.def(py::init<BLocker *>(), "", py::arg("locker"))
.def(py::init(), "")
.def("IsLocked", &BAutolock::IsLocked, "")
.def("Lock", &BAutolock::Lock, "")
.def("Unlock", &BAutolock::Unlock, "")
;


}
