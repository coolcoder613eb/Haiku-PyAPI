#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <mail/MailComponent.h>
#include <MimeType.h>

namespace py = pybind11;

class PyBMailComponent : public BMailComponent{
	public:
        using BMailComponent::BMailComponent;
        status_t GetDecodedData(BPositionIO *data) override {
            PYBIND11_OVERLOAD(status_t, BMailComponent, GetDecodedData, data);
        }
        status_t SetDecodedData(BPositionIO *data) override {
            PYBIND11_OVERLOAD(status_t, BMailComponent, SetDecodedData, data);
        }
        status_t SetToRFC822(BPositionIO *data, size_t length, bool parse_now = false) override {
            PYBIND11_OVERLOAD(status_t, BMailComponent, SetToRFC822, data, length, parse_now);
        }
        status_t RenderToRFC822(BPositionIO *render_to) override {
            PYBIND11_OVERLOAD(status_t, BMailComponent, RenderToRFC822, render_to);
        }
        status_t MIMEType(BMimeType *mime) override {
            PYBIND11_OVERLOAD(status_t, BMailComponent, MIMEType, mime);
        }
};

class PyBTextMailComponent : public BTextMailComponent{
	public:
        using BTextMailComponent::BTextMailComponent;
        status_t GetDecodedData(BPositionIO *data) override {
            PYBIND11_OVERLOAD(status_t, BTextMailComponent, GetDecodedData, data);
        }
        status_t SetDecodedData(BPositionIO *data) override {
            PYBIND11_OVERLOAD(status_t, BTextMailComponent, SetDecodedData, data);
        }
        status_t SetToRFC822(BPositionIO *data, size_t length, bool parse_now = false) override {
            PYBIND11_OVERLOAD(status_t, BTextMailComponent, SetToRFC822, data, length, parse_now);
        }
        status_t RenderToRFC822(BPositionIO *render_to) override {
            PYBIND11_OVERLOAD(status_t, BTextMailComponent, RenderToRFC822, render_to);
        }
};

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

py::class_<BMailComponent,PyBMailComponent>(m, "BMailComponent")
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

py::class_<BTextMailComponent, PyBTextMailComponent, BMailComponent>(m, "BTextMailComponent")
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
