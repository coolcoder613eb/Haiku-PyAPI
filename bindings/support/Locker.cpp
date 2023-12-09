#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/Locker.h>

namespace py = pybind11;


PYBIND11_MODULE(Locker, m)
{
py::class_<BLocker>(m, "BLocker")
.def(py::init(), "")
.def(py::init<const char *>(), "", py::arg("name"))
.def(py::init<bool>(), "", py::arg("benaphoreStyle"))
.def(py::init<const char *, bool>(), "", py::arg("name"), py::arg("benaphoreStyle"))
.def("InitCheck", &BLocker::InitCheck, "")
.def("Lock", &BLocker::Lock, "")
.def("LockWithTimeout", &BLocker::LockWithTimeout, "", py::arg("timeout"))
.def("Unlock", &BLocker::Unlock, "")
.def("LockingThread", &BLocker::LockingThread, "")
.def("IsLocked", &BLocker::IsLocked, "")
.def("CountLocks", &BLocker::CountLocks, "")
.def("CountLockRequests", &BLocker::CountLockRequests, "")
.def("Sem", &BLocker::Sem, "")
;


}
