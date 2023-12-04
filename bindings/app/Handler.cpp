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


class PyBHandler : public BHandler{
	public:
        using BHandler::BHandler;
        status_t			Archive(BMessage* data, bool deep = true) const override {
        	PYBIND11_OVERLOAD(status_t, BHandler, Archive, data, deep);
        }
        void			MessageReceived(BMessage* message) override {
        	PYBIND11_OVERLOAD(void, BHandler, MessageReceived, message);
        }
        void			SetNextHandler(BHandler* handler) override {
        	PYBIND11_OVERLOAD(void, BHandler, SetNextHandler, handler);
        }
        void			AddFilter(BMessageFilter* filter) override {
        	PYBIND11_OVERLOAD(void, BHandler, AddFilter, filter);
        }
        bool			RemoveFilter(BMessageFilter* filter) override {
        	PYBIND11_OVERLOAD(bool, BHandler, RemoveFilter, filter);
        }
        void			SetFilterList(BList* filters) override {
        	PYBIND11_OVERLOAD(void, BHandler, SetFilterList, filters);
        }
        BHandler*		ResolveSpecifier(BMessage* message, int32 index, BMessage* specifier, int32 what, const char* property) override {
        	PYBIND11_OVERLOAD(BHandler*, BHandler, ResolveSpecifier, message, index, specifier, what, property);
        }
        status_t		GetSupportedSuites(BMessage* data) override {
        	PYBIND11_OVERLOAD(status_t, BHandler, GetSupportedSuites, data);
        }
        status_t		Perform(perform_code d, void* arg) override {
        	PYBIND11_OVERLOAD(status_t, BHandler, Perform, d, arg);
        }
        void 			SendNotices(uint32 what, const BMessage* notice = NULL) override {
        	PYBIND11_OVERLOAD(void, BHandler, SendNotices, what, notice);
        }
};

PYBIND11_MODULE(Handler,m)
{
m.attr("B_OBSERVER_OBSERVE_ALL") = B_OBSERVER_OBSERVE_ALL;

py::class_<BHandler, PyBHandler>(m, "BHandler")
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
.def("StartWatching", py::overload_cast<BMessenger, uint32>(&BHandler::StartWatching), "", py::arg("target"), py::arg("what"))
.def("StartWatchingAll", py::overload_cast<BMessenger>(&BHandler::StartWatchingAll), "", py::arg("target"))
.def("StopWatching", py::overload_cast<BMessenger, uint32>(&BHandler::StopWatching), "", py::arg("target"), py::arg("what"))
.def("StopWatchingAll", py::overload_cast<BMessenger>(&BHandler::StopWatchingAll), "", py::arg("target"))
.def("StartWatching", py::overload_cast<BHandler *, uint32>(&BHandler::StartWatching), "", py::arg("observer"), py::arg("what"))
.def("StartWatchingAll", py::overload_cast<BHandler *>(&BHandler::StartWatchingAll), "", py::arg("observer"))
.def("StopWatching", py::overload_cast<BHandler *, uint32>(&BHandler::StopWatching), "", py::arg("observer"), py::arg("what"))
.def("StopWatchingAll", py::overload_cast<BHandler *>(&BHandler::StopWatchingAll), "", py::arg("observer"))
.def("Perform", &BHandler::Perform, "", py::arg("d"), py::arg("arg"))
.def("SendNotices", &BHandler::SendNotices, "", py::arg("what"), py::arg("notice")=NULL)
.def("IsWatched", &BHandler::IsWatched, "")
;


}
