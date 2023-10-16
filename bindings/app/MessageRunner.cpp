#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <app/MessageRunner.h>
#include <Messenger.h>

namespace py = pybind11;


PYBIND11_MODULE(MessageRunner,m)
{
py::class_<BMessageRunner>(m, "BMessageRunner")
.def(py::init<BMessenger, const BMessage *, bigtime_t, int>(), "", py::arg("target"), py::arg("message"), py::arg("interval"), py::arg("count")=- 1)
.def(py::init<BMessenger, const BMessage &, bigtime_t, int>(), "", py::arg("target"), py::arg("message"), py::arg("interval"), py::arg("count")=- 1)
.def(py::init<BMessenger, const BMessage *, bigtime_t, int, BMessenger>(), "", py::arg("target"), py::arg("message"), py::arg("interval"), py::arg("count"), py::arg("replyTo"))
.def(py::init<BMessenger, const BMessage &, bigtime_t, int, BMessenger>(), "", py::arg("target"), py::arg("message"), py::arg("interval"), py::arg("count"), py::arg("replyTo"))
.def("InitCheck", &BMessageRunner::InitCheck, "")
.def("SetInterval", &BMessageRunner::SetInterval, "", py::arg("interval"))
.def("SetCount", &BMessageRunner::SetCount, "", py::arg("count"))
.def("GetInfo", &BMessageRunner::GetInfo, "", py::arg("interval"), py::arg("count"))
.def_static("StartSending", py::overload_cast<BMessenger, const BMessage *, bigtime_t, int32>(&BMessageRunner::StartSending), "", py::arg("target"), py::arg("message"), py::arg("interval"), py::arg("count"))
.def_static("StartSending", py::overload_cast<BMessenger, const BMessage *, bigtime_t, int32, BMessenger>(&BMessageRunner::StartSending), "", py::arg("target"), py::arg("message"), py::arg("interval"), py::arg("count"), py::arg("replyTo"))
;


}
