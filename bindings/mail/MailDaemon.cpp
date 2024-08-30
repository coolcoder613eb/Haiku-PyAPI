#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <mail/E-mail.h>
#include <mail/MailDaemon.h>

namespace py = pybind11;


PYBIND11_MODULE(MailDaemon, m)
{
//m.attr("B_MAIL_BODY_FETCHED") = py::cast(B_MAIL_BODY_FETCHED); //
m.attr("B_MAIL_BODY_FETCHED") = '_Mbf';

py::class_<BMailDaemon>(m, "BMailDaemon")
.def(py::init(), "")
.def("IsRunning", &BMailDaemon::IsRunning, "")
.def("CheckMail", &BMailDaemon::CheckMail, "", py::arg("accountID")=- 1)
.def("CheckAndSendQueuedMail", &BMailDaemon::CheckAndSendQueuedMail, "", py::arg("accountID")=- 1)
.def("SendQueuedMail", &BMailDaemon::SendQueuedMail, "")
.def("CountNewMessages", &BMailDaemon::CountNewMessages, "", py::arg("waitForFetchCompletion")=false)
.def("MarkAsRead", &BMailDaemon::MarkAsRead, "", py::arg("account"), py::arg("ref"), py::arg("flag")=B_READ)
.def("FetchBody", &BMailDaemon::FetchBody, "", py::arg("ref"), py::arg("listener")=NULL)
.def("Quit", &BMailDaemon::Quit, "")
.def("Launch", &BMailDaemon::Launch, "")
;


}
