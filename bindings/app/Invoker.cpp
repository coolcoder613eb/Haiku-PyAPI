#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <app/Invoker.h>
#include <BeBuild.h>
#include <Messenger.h>
#include <Handler.h>
#include <Looper.h>
#include <AppDefs.h>

namespace py = pybind11;


py::tuple TargetWrapper(BInvoker& self) {
	BHandler* handler;
	BLooper* looper;

	handler = self.Target(&looper);

	return py::make_tuple(handler, looper);
}

PYBIND11_MODULE(Invoker,m)
{
py::class_<BInvoker>(m, "BInvoker")
.def(py::init(), "")
.def(py::init<BMessage *, const BHandler *, const BLooper *>(), "", py::arg("message"), py::arg("handler"), py::arg("looper")=NULL)
.def(py::init<BMessage *, BMessenger>(), "", py::arg("message"), py::arg("target"))
.def("SetMessage", &BInvoker::SetMessage, "", py::arg("message"))
.def("Message", &BInvoker::Message, "")
.def("Command", &BInvoker::Command, "")
.def("SetTarget", py::overload_cast<const BHandler *, const BLooper *>(&BInvoker::SetTarget), "", py::arg("handler"), py::arg("looper")=NULL)
.def("SetTarget", py::overload_cast<BMessenger>(&BInvoker::SetTarget), "", py::arg("messenger"))
.def("IsTargetLocal", &BInvoker::IsTargetLocal, "")
.def("Target", &TargetWrapper, "Returns a tuple containing the handler and looper the Invoker is pointing to.")
.def("Messenger", &BInvoker::Messenger, "")
.def("SetHandlerForReply", &BInvoker::SetHandlerForReply, "", py::arg("handler"))
.def("HandlerForReply", &BInvoker::HandlerForReply, "")
.def("Invoke", &BInvoker::Invoke, "", py::arg("message")=NULL)
.def("InvokeNotify", &BInvoker::InvokeNotify, "", py::arg("message"), py::arg("kind")=py::int_('CIVK'))//B_CONTROL_INVOKED
.def("SetTimeout", &BInvoker::SetTimeout, "", py::arg("timeout"))
.def("Timeout", &BInvoker::Timeout, "")
;


}
