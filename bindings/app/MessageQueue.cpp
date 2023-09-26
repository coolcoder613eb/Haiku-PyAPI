#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <app/MessageQueue.h>
#include <Locker.h>
#include <Message.h>

namespace py = pybind11;


PYBIND11_MODULE(MessageQueue,m)
{
py::class_<BMessageQueue>(m, "BMessageQueue")
.def(py::init(), "")
.def("AddMessage", &BMessageQueue::AddMessage, "", py::arg("message"))
.def("RemoveMessage", &BMessageQueue::RemoveMessage, "", py::arg("message"))
.def("CountMessages", &BMessageQueue::CountMessages, "")
.def("IsEmpty", &BMessageQueue::IsEmpty, "")
.def("FindMessage", py::overload_cast<int32>(&BMessageQueue::FindMessage, py::const_), "", py::arg("index"))
.def("FindMessage", py::overload_cast<uint32, int32>(&BMessageQueue::FindMessage, py::const_), "", py::arg("what"), py::arg("index")=0)
.def("Lock", &BMessageQueue::Lock, "")
.def("Unlock", &BMessageQueue::Unlock, "")
//.def("IsLocked", &BMessageQueue::IsLocked, "")
.def("NextMessage", &BMessageQueue::NextMessage, "")
.def("IsNextMessage", &BMessageQueue::IsNextMessage, "", py::arg("message"))
;


}
