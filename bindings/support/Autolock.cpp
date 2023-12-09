#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/Autolock.h>

namespace py = pybind11;


PYBIND11_MODULE(Autolock, m)
{
py::class_<BAutolock>(m, "BAutolock")
.def(py::init<BLooper *>(), "", py::arg("looper"))
.def(py::init<BLocker *>(), "", py::arg("locker"))
.def(py::init<BLocker &>(), "", py::arg("locker"))
.def("IsLocked", &BAutolock::IsLocked, "")
.def("Lock", &BAutolock::Lock, "")
.def("Unlock", &BAutolock::Unlock, "")
;


}
