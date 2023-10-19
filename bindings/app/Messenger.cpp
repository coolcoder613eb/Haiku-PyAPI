#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <app/Messenger.h>
#include <OS.h>
#include <ByteOrder.h>
#include <Message.h>
#include <Looper.h>
#include <Handler.h>

namespace py = pybind11;


BHandler* TargetWrapper(BMessenger& self, std::vector<BLooper*> looper) {
	return self.Target(looper.data());
}

PYBIND11_MODULE(Messenger,m)
{
py::class_<BMessenger>(m, "BMessenger")
.def(py::init(), "")
.def(py::init<const char *, team_id, status_t *>(), "", py::arg("signature"), py::arg("team")=- 1, py::arg("result")=NULL)
.def(py::init<const BHandler *, const BLooper *, status_t *>(), "", py::arg("handler"), py::arg("looper")=NULL, py::arg("result")=NULL)
.def(py::init<const BMessenger &>(), "", py::arg("other"))
.def("IsTargetLocal", &BMessenger::IsTargetLocal, "")
.def("Target", &TargetWrapper, "", py::arg("looper"))
.def("LockTarget", &BMessenger::LockTarget, "")
.def("LockTargetWithTimeout", &BMessenger::LockTargetWithTimeout, "", py::arg("timeout"))
.def("SendMessage", py::overload_cast<uint32, BHandler *>(&BMessenger::SendMessage, py::const_), "", py::arg("command"), py::arg("replyTo")=NULL)
.def("SendMessage", py::overload_cast<BMessage *, BHandler *, bigtime_t>(&BMessenger::SendMessage, py::const_), "", py::arg("message"), py::arg("replyTo")=NULL, py::arg("timeout")=B_INFINITE_TIMEOUT)
.def("SendMessage", py::overload_cast<BMessage *, BMessenger, bigtime_t>(&BMessenger::SendMessage, py::const_), "", py::arg("message"), py::arg("replyTo"), py::arg("timeout")=B_INFINITE_TIMEOUT)
.def("SendMessage", py::overload_cast<uint32, BMessage *>(&BMessenger::SendMessage, py::const_), "", py::arg("command"), py::arg("reply"))
.def("SendMessage", py::overload_cast<BMessage *, BMessage *, bigtime_t, bigtime_t>(&BMessenger::SendMessage, py::const_), "", py::arg("message"), py::arg("reply"), py::arg("deliveryTimeout")=B_INFINITE_TIMEOUT, py::arg("replyTimeout")=B_INFINITE_TIMEOUT)
.def("SetTo", py::overload_cast<const char *, team_id>(&BMessenger::SetTo), "", py::arg("signature"), py::arg("team")=- 1)
.def("SetTo", py::overload_cast<const BHandler *, const BLooper *>(&BMessenger::SetTo), "", py::arg("handler"), py::arg("looper")=NULL)
.def("operator=", &BMessenger::operator=, "", py::arg("other"))
.def("__eq__", &BMessenger::operator==, "", py::arg("other"))
.def("IsValid", &BMessenger::IsValid, "")
.def("Team", &BMessenger::Team, "")
.def("HashValue", &BMessenger::HashValue, "")
//.def_readwrite("Private", &BMessenger::Private, "")
;

m.def("__lt__", py::overload_cast<const BMessenger &, const BMessenger &>(&operator<), "", py::arg("a"), py::arg("b"));

m.def("__ne__", &operator!=, "", py::arg("a"), py::arg("b"));

}
