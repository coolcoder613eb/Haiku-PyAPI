#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <app/Looper.h>
#include <BeBuild.h>
#include <Handler.h>
#include <List.h>
#include <OS.h>
#include <MessageFilter.h>
#include <MessageQueue.h>

namespace py = pybind11;
using namespace BPrivate;

PYBIND11_MODULE(Looper,m)
{
//m.attr("BDirectMessageTarget") = BDirectMessageTarget;

//m.attr("BLooperList") = BLooperList;

py::class_<BLooper,BHandler>(m, "BLooper")
.def(py::init<const char *, int, int>(), "", py::arg("name")=NULL, py::arg("priority")=B_NORMAL_PRIORITY, py::arg("portCapacity")=B_LOOPER_PORT_DEFAULT_CAPACITY)
.def(py::init<BMessage *>(), "", py::arg("data"))
.def_static("Instantiate", &BLooper::Instantiate, "", py::arg("data"))
.def("Archive", &BLooper::Archive, "", py::arg("data"), py::arg("deep")=true)
.def("PostMessage", py::overload_cast<uint32>(&BLooper::PostMessage), "", py::arg("command"))
.def("PostMessage", py::overload_cast<BMessage *>(&BLooper::PostMessage), "", py::arg("message"))
.def("PostMessage", py::overload_cast<uint32, BHandler *, BHandler *>(&BLooper::PostMessage), "", py::arg("command"), py::arg("handler"), py::arg("replyTo")=NULL)
.def("PostMessage", py::overload_cast<BMessage *, BHandler *, BHandler *>(&BLooper::PostMessage), "", py::arg("message"), py::arg("handler"), py::arg("replyTo")=NULL)
.def("DispatchMessage", &BLooper::DispatchMessage, "", py::arg("message"), py::arg("handler"))
.def("MessageReceived", &BLooper::MessageReceived, "", py::arg("message"))
.def("CurrentMessage", &BLooper::CurrentMessage, "")
.def("DetachCurrentMessage", &BLooper::DetachCurrentMessage, "")
.def("DispatchExternalMessage", [](BLooper& self,BMessage * message,BHandler * handler) {
    bool  _detached;
    self.DispatchExternalMessage(message, handler, _detached);
    return _detached;
}
, "", py::arg("message"), py::arg("handler"))
.def("MessageQueue", &BLooper::MessageQueue, "")
.def("IsMessageWaiting", &BLooper::IsMessageWaiting, "")
.def("AddHandler", &BLooper::AddHandler, "", py::arg("handler"))
.def("RemoveHandler", &BLooper::RemoveHandler, "", py::arg("handler"))
.def("CountHandlers", &BLooper::CountHandlers, "")
.def("HandlerAt", &BLooper::HandlerAt, "", py::arg("index"))
.def("IndexOf", &BLooper::IndexOf, "", py::arg("handler"))
.def("PreferredHandler", &BLooper::PreferredHandler, "")
.def("SetPreferredHandler", &BLooper::SetPreferredHandler, "", py::arg("handler"))
.def("Run", &BLooper::Run, "")
.def("Loop", &BLooper::Loop, "")
.def("Quit", &BLooper::Quit, "")
.def("QuitRequested", &BLooper::QuitRequested, "")
.def("Lock", &BLooper::Lock, "")
.def("Unlock", &BLooper::Unlock, "")
.def("IsLocked", &BLooper::IsLocked, "")
.def("LockWithTimeout", &BLooper::LockWithTimeout, "", py::arg("timeout"))
.def("Thread", &BLooper::Thread, "")
.def("Team", &BLooper::Team, "")
.def_static("LooperForThread", &BLooper::LooperForThread, "", py::arg("thread"))
.def("LockingThread", &BLooper::LockingThread, "")
.def("CountLocks", &BLooper::CountLocks, "")
.def("CountLockRequests", &BLooper::CountLockRequests, "")
.def("Sem", &BLooper::Sem, "")
.def("ResolveSpecifier", &BLooper::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("what"), py::arg("property"))
.def("GetSupportedSuites", &BLooper::GetSupportedSuites, "", py::arg("data"))
.def("AddCommonFilter", &BLooper::AddCommonFilter, "", py::arg("filter"))
.def("RemoveCommonFilter", &BLooper::RemoveCommonFilter, "", py::arg("filter"))
.def("SetCommonFilterList", &BLooper::SetCommonFilterList, "", py::arg("filters"))
.def("CommonFilterList", &BLooper::CommonFilterList, "")
.def("Perform", &BLooper::Perform, "", py::arg("d"), py::arg("arg"))
;


}
