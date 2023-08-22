#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <app/Notification.h>
#include <Archivable.h>
#include <Entry.h>
#include <List.h>
#include <String.h>
#include <Bitmap.h>

namespace py = pybind11;


PYBIND11_MODULE(Notification,m)
{
py::enum_<notification_type>(m, "notification_type", "")
.value("B_INFORMATION_NOTIFICATION", notification_type::B_INFORMATION_NOTIFICATION, "")
.value("B_IMPORTANT_NOTIFICATION", notification_type::B_IMPORTANT_NOTIFICATION, "")
.value("B_ERROR_NOTIFICATION", notification_type::B_ERROR_NOTIFICATION, "")
.value("B_PROGRESS_NOTIFICATION", notification_type::B_PROGRESS_NOTIFICATION, "")
.export_values();

py::class_<BNotification>(m, "BNotification")
.def(py::init<notification_type>(), "", py::arg("type"))
.def(py::init<BMessage *>(), "", py::arg("archive"))
.def("InitCheck", &BNotification::InitCheck, "")
.def_static("Instantiate", &BNotification::Instantiate, "", py::arg("archive"))
.def("Archive", &BNotification::Archive, "", py::arg("archive"), py::arg("deep")=true)
.def("SourceSignature", &BNotification::SourceSignature, "")
.def("SourceName", &BNotification::SourceName, "")
.def("Type", &BNotification::Type, "")
.def("Group", &BNotification::Group, "")
.def("SetGroup", &BNotification::SetGroup, "", py::arg("group"))
.def("Title", &BNotification::Title, "")
.def("SetTitle", &BNotification::SetTitle, "", py::arg("title"))
.def("Content", &BNotification::Content, "")
.def("SetContent", &BNotification::SetContent, "", py::arg("content"))
.def("MessageID", &BNotification::MessageID, "")
.def("SetMessageID", &BNotification::SetMessageID, "", py::arg("id"))
.def("Progress", &BNotification::Progress, "")
.def("SetProgress", &BNotification::SetProgress, "", py::arg("progress"))
.def("OnClickApp", &BNotification::OnClickApp, "")
.def("SetOnClickApp", &BNotification::SetOnClickApp, "", py::arg("app"))
.def("OnClickFile", &BNotification::OnClickFile, "")
.def("SetOnClickFile", &BNotification::SetOnClickFile, "", py::arg("file"))
.def("AddOnClickRef", &BNotification::AddOnClickRef, "", py::arg("ref"))
.def("CountOnClickRefs", &BNotification::CountOnClickRefs, "")
.def("OnClickRefAt", &BNotification::OnClickRefAt, "", py::arg("index"))
.def("AddOnClickArg", &BNotification::AddOnClickArg, "", py::arg("arg"))
.def("CountOnClickArgs", &BNotification::CountOnClickArgs, "")
.def("OnClickArgAt", &BNotification::OnClickArgAt, "", py::arg("index"))
.def("Icon", &BNotification::Icon, "")
.def("SetIcon", &BNotification::SetIcon, "", py::arg("icon"))
.def("Send", &BNotification::Send, "", py::arg("timeout")=- 1)
;


}
