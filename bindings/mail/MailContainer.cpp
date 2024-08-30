#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <mail/MailContainer.h>

namespace py = pybind11;


void define_MailContainer(py::module_& m)
{
py::class_<BMailContainer, BMailComponent>(m, "BMailContainer")
.def(py::init<unsigned int>(), "", py::arg("defaultCharSet")=B_MAIL_NULL_CONVERSION)
.def("AddComponent", &BMailContainer::AddComponent, "", py::arg("component"))
.def("RemoveComponent", py::overload_cast<BMailComponent *>(&BMailContainer::RemoveComponent), "", py::arg("component"))
.def("RemoveComponent", py::overload_cast<int>(&BMailContainer::RemoveComponent), "", py::arg("index"))
.def("GetComponent", &BMailContainer::GetComponent, "", py::arg("index"), py::arg("parse_now")=false)
.def("CountComponents", &BMailContainer::CountComponents, "")
;

py::class_<BMIMEMultipartMailContainer, BMailContainer>(m, "BMIMEMultipartMailContainer")
.def(py::init<const char *, const char *, unsigned int>(), "", py::arg("boundary")=NULL, py::arg("this_is_an_MIME_message_text")=NULL, py::arg("defaultCharSet")=B_MAIL_NULL_CONVERSION)
.def(py::init(), "")
.def("SetBoundary", &BMIMEMultipartMailContainer::SetBoundary, "", py::arg("boundary"))
.def("SetThisIsAnMIMEMessageText", &BMIMEMultipartMailContainer::SetThisIsAnMIMEMessageText, "", py::arg("text"))
.def("AddComponent", &BMIMEMultipartMailContainer::AddComponent, "", py::arg("component"))
.def("RemoveComponent", py::overload_cast<BMailComponent *>(&BMIMEMultipartMailContainer::RemoveComponent), "", py::arg("component"))
.def("RemoveComponent", py::overload_cast<int>(&BMIMEMultipartMailContainer::RemoveComponent), "", py::arg("index"))
.def("GetComponent", &BMIMEMultipartMailContainer::GetComponent, "", py::arg("index"), py::arg("parse_now")=false)
.def("CountComponents", &BMIMEMultipartMailContainer::CountComponents, "")
.def("GetDecodedData", &BMIMEMultipartMailContainer::GetDecodedData, "", py::arg("data"))
.def("SetDecodedData", &BMIMEMultipartMailContainer::SetDecodedData, "", py::arg("data"))
.def("SetToRFC822", &BMIMEMultipartMailContainer::SetToRFC822, "", py::arg("data"), py::arg("length"), py::arg("parse_now")=false)
.def("RenderToRFC822", &BMIMEMultipartMailContainer::RenderToRFC822, "", py::arg("render_to"))
;


}
