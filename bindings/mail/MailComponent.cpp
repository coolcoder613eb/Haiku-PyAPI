#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <mail/MailComponent.h>
#include <MimeType.h>

namespace py = pybind11;

PYBIND11_MODULE(MailComponent, m)
{
py::enum_<component_type>(m, "component_type", "")
.value("B_MAIL_PLAIN_TEXT_BODY", component_type::B_MAIL_PLAIN_TEXT_BODY, "")
.value("B_MAIL_SIMPLE_ATTACHMENT", component_type::B_MAIL_SIMPLE_ATTACHMENT, "")
.value("B_MAIL_ATTRIBUTED_ATTACHMENT", component_type::B_MAIL_ATTRIBUTED_ATTACHMENT, "")
.value("B_MAIL_MULTIPART_CONTAINER", component_type::B_MAIL_MULTIPART_CONTAINER, "")
.export_values();

m.attr("kHeaderCharsetString") = py::cast(kHeaderCharsetString);

m.attr("kHeaderEncodingString") = py::cast(kHeaderEncodingString);

py::class_<BMailComponent>(m, "BMailComponent")
.def(py::init<uint32>(), "", py::arg("defaultCharSet")=B_MAIL_NULL_CONVERSION)
.def("ComponentType", &BMailComponent::ComponentType, "")
.def("WhatIsThis", &BMailComponent::WhatIsThis, "")
.def("IsAttachment", &BMailComponent::IsAttachment, "")
.def("SetHeaderField", py::overload_cast<const char *, const char *, uint32, mail_encoding, bool>(&BMailComponent::SetHeaderField), "", py::arg("key"), py::arg("value"), py::arg("charset")=B_MAIL_NULL_CONVERSION, py::arg("encoding")=null_encoding, py::arg("replace_existing")=true)
.def("SetHeaderField", py::overload_cast<const char *, BMessage *, bool>(&BMailComponent::SetHeaderField), "", py::arg("key"), py::arg("structured_header"), py::arg("replace_existing")=true)
.def("HeaderAt", &BMailComponent::HeaderAt, "", py::arg("index"))
.def("HeaderField", py::overload_cast<const char *, int32>(&BMailComponent::HeaderField, py::const_), "", py::arg("key"), py::arg("index")=0)
.def("HeaderField", py::overload_cast<const char *, BMessage *, int32>(&BMailComponent::HeaderField, py::const_), "", py::arg("key"), py::arg("structured_header"), py::arg("index")=0)
.def("RemoveHeader", &BMailComponent::RemoveHeader, "", py::arg("key"))
.def("GetDecodedData", &BMailComponent::GetDecodedData, "", py::arg("data"))
.def("SetDecodedData", &BMailComponent::SetDecodedData, "", py::arg("data"))
.def("SetToRFC822", &BMailComponent::SetToRFC822, "", py::arg("data"), py::arg("length"), py::arg("parse_now")=false)
.def("RenderToRFC822", &BMailComponent::RenderToRFC822, "", py::arg("render_to"))
.def("MIMEType", &BMailComponent::MIMEType, "", py::arg("mime"))
;

py::class_<BTextMailComponent, BMailComponent>(m, "BTextMailComponent")
.def(py::init<const char *, uint32>(), "", py::arg("text")=NULL, py::arg("defaultCharSet")=B_MAIL_NULL_CONVERSION)
.def("SetEncoding", &BTextMailComponent::SetEncoding, "", py::arg("encoding"), py::arg("charset"))
.def("SetText", &BTextMailComponent::SetText, "", py::arg("text"))
.def("AppendText", &BTextMailComponent::AppendText, "", py::arg("text"))
.def("Text", &BTextMailComponent::Text, "")
.def("BStringText", &BTextMailComponent::BStringText, "")
.def("Quote", &BTextMailComponent::Quote, "", py::arg("message")=NULL, py::arg("quote_style")="> ")
.def("GetDecodedData", &BTextMailComponent::GetDecodedData, "", py::arg("data"))
.def("SetDecodedData", &BTextMailComponent::SetDecodedData, "", py::arg("data"))
.def("SetToRFC822", &BTextMailComponent::SetToRFC822, "", py::arg("data"), py::arg("length"), py::arg("parse_now")=false)
.def("RenderToRFC822", &BTextMailComponent::RenderToRFC822, "", py::arg("render_to"))
;


}
