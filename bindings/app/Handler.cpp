#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <app/Handler.h>
#include <Archivable.h>
#include <Messenger.h>
#include <Looper.h>
#include <MessageFilter.h>
#include <List.h>

namespace py = pybind11;
using namespace BPrivate;

PYBIND11_MODULE(Handler,m)
{
m.attr("B_OBSERVER_OBSERVE_ALL") = B_OBSERVER_OBSERVE_ALL;

//m.attr("ObserverList") = ObserverList;

py::class_<BHandler>(m, "BHandler")
.def(py::init<const char *>(), "", py::arg("name")=NULL)
.def(py::init<BMessage *>(), "", py::arg("data"))
.def_static("Instantiate", &BHandler::Instantiate, "", py::arg("data"))
.def("Archive", &BHandler::Archive, "", py::arg("data"), py::arg("deep")=true)
.def("MessageReceived", &BHandler::MessageReceived, "", py::arg("message"))
.def("Looper", &BHandler::Looper, "")
.def("SetName", &BHandler::SetName, "", py::arg("name"))
.def("Name", &BHandler::Name, "")
.def("SetNextHandler", &BHandler::SetNextHandler, "", py::arg("handler"))
.def("NextHandler", &BHandler::NextHandler, "")
.def("AddFilter", &BHandler::AddFilter, "", py::arg("filter"))
.def("RemoveFilter", &BHandler::RemoveFilter, "", py::arg("filter"))
.def("SetFilterList", &BHandler::SetFilterList, "", py::arg("filters"))
.def("FilterList", &BHandler::FilterList, "")
.def("LockLooper", &BHandler::LockLooper, "")
.def("LockLooperWithTimeout", &BHandler::LockLooperWithTimeout, "", py::arg("timeout"))
.def("UnlockLooper", &BHandler::UnlockLooper, "")
.def("ResolveSpecifier", &BHandler::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("what"), py::arg("property"))
.def("GetSupportedSuites", &BHandler::GetSupportedSuites, "", py::arg("data"))
.def("StartWatching", py::overload_cast<BMessenger, unsigned int>(&BHandler::StartWatching), "", py::arg("target"), py::arg("what"))
.def("StartWatchingAll", py::overload_cast<BMessenger>(&BHandler::StartWatchingAll), "", py::arg("target"))
.def("StopWatching", py::overload_cast<BMessenger, unsigned int>(&BHandler::StopWatching), "", py::arg("target"), py::arg("what"))
.def("StopWatchingAll", py::overload_cast<BMessenger>(&BHandler::StopWatchingAll), "", py::arg("target"))
.def("StartWatching", py::overload_cast<BHandler *, unsigned int>(&BHandler::StartWatching), "", py::arg("observer"), py::arg("what"))
.def("StartWatchingAll", py::overload_cast<BHandler *>(&BHandler::StartWatchingAll), "", py::arg("observer"))
.def("StopWatching", py::overload_cast<BHandler *, unsigned int>(&BHandler::StopWatching), "", py::arg("observer"), py::arg("what"))
.def("StopWatchingAll", py::overload_cast<BHandler *>(&BHandler::StopWatchingAll), "", py::arg("observer"))
.def("Perform", &BHandler::Perform, "", py::arg("d"), py::arg("arg"))
.def("SendNotices", &BHandler::SendNotices, "", py::arg("what"), py::arg("notice")=NULL)
.def("IsWatched", &BHandler::IsWatched, "")
;


}
