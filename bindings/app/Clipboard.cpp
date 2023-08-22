#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <app/Clipboard.h>
#include <BeBuild.h>
#include <Locker.h>
#include <Messenger.h>

namespace py = pybind11;


PYBIND11_MODULE(Clipboard,m)
{
m.attr("B_CLIPBOARD_CHANGED") = "CLCH";

//m.attr("be_clipboard") = be_clipboard;

py::class_<BClipboard>(m, "BClipboard")
.def(py::init<const char *, bool>(), "", py::arg("name"), py::arg("transient")=false)
.def("Name", &BClipboard::Name, "")
.def("LocalCount", &BClipboard::LocalCount, "")
.def("SystemCount", &BClipboard::SystemCount, "")
.def("StartWatching", &BClipboard::StartWatching, "", py::arg("target"))
.def("StopWatching", &BClipboard::StopWatching, "", py::arg("target"))
.def("Lock", &BClipboard::Lock, "")
.def("Unlock", &BClipboard::Unlock, "")
.def("IsLocked", &BClipboard::IsLocked, "")
.def("Clear", &BClipboard::Clear, "")
.def("Commit", py::overload_cast<>(&BClipboard::Commit), "")
.def("Commit", py::overload_cast<bool>(&BClipboard::Commit), "", py::arg("failIfChanged"))
.def("Revert", &BClipboard::Revert, "")
.def("DataSource", &BClipboard::DataSource, "")
.def("Data", &BClipboard::Data, "")
;


}
