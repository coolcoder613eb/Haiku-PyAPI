#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <mail/MailMessage.h>
#include <Directory.h>

namespace py = pybind11;

class PyBEmailMessage : public BEmailMessage{
	public:
        using BEmailMessage::BEmailMessage;
        status_t			AddComponent(BMailComponent *component) override {
            PYBIND11_OVERLOAD(status_t, BEmailMessage, AddComponent, component);
        }
        status_t			RemoveComponent(BMailComponent *component) override {
            PYBIND11_OVERLOAD(status_t, BEmailMessage, RemoveComponent, component);
        }
        status_t			RemoveComponent(int32 index) override {
            PYBIND11_OVERLOAD(status_t, BEmailMessage, RemoveComponent, index);
        }
        BMailComponent*		GetComponent(int32 index, bool parseNow = false) override {
            PYBIND11_OVERLOAD(BMailComponent*, BEmailMessage, GetComponent, index, parseNow);
        }
        int32				CountComponents() const override {
            PYBIND11_OVERLOAD(int32, BEmailMessage, CountComponents);
        }
        status_t			SetToRFC822(BPositionIO* data, size_t length, bool parseNow = false) override {
            PYBIND11_OVERLOAD(status_t, BEmailMessage, SetToRFC822, data, length, parseNow);
        }
        status_t			RenderToRFC822(BPositionIO* renderTo) override {
            PYBIND11_OVERLOAD(status_t, BEmailMessage, RenderToRFC822, renderTo);
        }
};

PYBIND11_MODULE(MailMessage, m)
{
py::enum_<mail_reply_to_mode>(m, "mail_reply_to_mode", "")
.value("B_MAIL_REPLY_TO", mail_reply_to_mode::B_MAIL_REPLY_TO, "")
.value("B_MAIL_REPLY_TO_ALL", mail_reply_to_mode::B_MAIL_REPLY_TO_ALL, "")
.value("B_MAIL_REPLY_TO_SENDER", mail_reply_to_mode::B_MAIL_REPLY_TO_SENDER, "")
.export_values();

py::class_<BEmailMessage, PyBEmailMessage, BMailContainer>(m, "BEmailMessage")
.def(py::init<BPositionIO *, bool, unsigned int>(), "", py::arg("stream")=NULL, py::arg("ownStream")=false, py::arg("defaultCharSet")=B_MAIL_NULL_CONVERSION)
.def(py::init<const entry_ref *, unsigned int>(), "", py::arg("ref"), py::arg("defaultCharSet")=B_MAIL_NULL_CONVERSION)
.def("InitCheck", &BEmailMessage::InitCheck, "")
.def("Data", &BEmailMessage::Data, "")
.def("ReplyMessage", &BEmailMessage::ReplyMessage, "", py::arg("replyTo"), py::arg("accountFromMail"), py::arg("quoteStyle")="> ")
.def("ForwardMessage", &BEmailMessage::ForwardMessage, "", py::arg("accountFromMail"), py::arg("includeAttachments")=false)
.def("To", &BEmailMessage::To, "")
.def("From", &BEmailMessage::From, "")
.def("ReplyTo", &BEmailMessage::ReplyTo, "")
.def("CC", &BEmailMessage::CC, "")
.def("Subject", &BEmailMessage::Subject, "")
.def("Date", &BEmailMessage::Date, "")
.def("Priority", &BEmailMessage::Priority, "")
.def("SetSubject", &BEmailMessage::SetSubject, "", py::arg("to"), py::arg("charset")=B_MAIL_NULL_CONVERSION, py::arg("encoding")=null_encoding)
.def("SetReplyTo", &BEmailMessage::SetReplyTo, "", py::arg("to"), py::arg("charset")=B_MAIL_NULL_CONVERSION, py::arg("encoding")=null_encoding)
.def("SetFrom", &BEmailMessage::SetFrom, "", py::arg("to"), py::arg("charset")=B_MAIL_NULL_CONVERSION, py::arg("encoding")=null_encoding)
.def("SetTo", &BEmailMessage::SetTo, "", py::arg("to"), py::arg("charset")=B_MAIL_NULL_CONVERSION, py::arg("encoding")=null_encoding)
.def("SetCC", &BEmailMessage::SetCC, "", py::arg("to"), py::arg("charset")=B_MAIL_NULL_CONVERSION, py::arg("encoding")=null_encoding)
.def("SetBCC", &BEmailMessage::SetBCC, "", py::arg("to"))
.def("SetPriority", &BEmailMessage::SetPriority, "", py::arg("to"))
.def("GetName", py::overload_cast<char *, int32>(&BEmailMessage::GetName,py::const_), "", py::arg("name"), py::arg("maxLength"))
.def("GetName", py::overload_cast<BString *>(&BEmailMessage::GetName,py::const_), "", py::arg("name"))
.def("SendViaAccountFrom", &BEmailMessage::SendViaAccountFrom, "", py::arg("message"))
.def("SendViaAccount", py::overload_cast<const char *>(&BEmailMessage::SendViaAccount), "", py::arg("accountName"))
.def("SendViaAccount", py::overload_cast<int>(&BEmailMessage::SendViaAccount), "", py::arg("account"))
.def("Account", &BEmailMessage::Account, "")
.def("GetAccountName", [](BEmailMessage& self) {
    BString  accountName;
    status_t r = self.GetAccountName(accountName);
    return std::make_tuple(r,accountName);
}
, "")
.def("AddComponent", &BEmailMessage::AddComponent, "", py::arg("component"))
.def("RemoveComponent", py::overload_cast<BMailComponent *>(&BEmailMessage::RemoveComponent), "", py::arg("component"))
.def("RemoveComponent", py::overload_cast<int>(&BEmailMessage::RemoveComponent), "", py::arg("index"))
.def("GetComponent", &BEmailMessage::GetComponent, "", py::arg("index"), py::arg("parseNow")=false)
.def("CountComponents", &BEmailMessage::CountComponents, "")
.def("Attach", &BEmailMessage::Attach, "", py::arg("ref"), py::arg("includeAttributes")=true)
.def("IsComponentAttachment", &BEmailMessage::IsComponentAttachment, "", py::arg("index"))
.def("SetBodyTextTo", &BEmailMessage::SetBodyTextTo, "", py::arg("text"))
.def("BodyText", &BEmailMessage::BodyText, "")
.def("SetBody", &BEmailMessage::SetBody, "", py::arg("body"))
.def("Body", &BEmailMessage::Body, "")
.def("SetToRFC822", &BEmailMessage::SetToRFC822, "", py::arg("data"), py::arg("length"), py::arg("parseNow")=false)
.def("RenderToRFC822", &BEmailMessage::RenderToRFC822, "", py::arg("renderTo"))
.def("RenderTo", &BEmailMessage::RenderTo, "", py::arg("dir"), py::arg("message")=NULL)
.def("Send", &BEmailMessage::Send, "", py::arg("sendNow"))
;


}
