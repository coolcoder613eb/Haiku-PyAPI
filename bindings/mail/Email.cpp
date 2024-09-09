#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>
#include <Entry.h>
#include <support/UTF8.h>
#include <mail/E-mail.h>

namespace py = pybind11;

std::string get_pop_name(const mail_pop_account& self) {
    return std::string(self.pop_name);
}

void set_pop_name(mail_pop_account& self, const std::string& name) {
    std::strncpy(self.pop_name, name.c_str(), B_MAX_USER_NAME_LENGTH - 1);
    self.pop_name[B_MAX_USER_NAME_LENGTH - 1] = '\0';
}

std::string get_pop_password(const mail_pop_account& self) {
    return std::string(self.pop_password);
}

void set_pop_password(mail_pop_account& self, const std::string& name) {
    std::strncpy(self.pop_password, name.c_str(), B_MAX_USER_NAME_LENGTH - 1);
    self.pop_password[B_MAX_USER_NAME_LENGTH - 1] = '\0';
}

std::string get_pop_host(const mail_pop_account& self) {
    return std::string(self.pop_host);
}

void set_pop_host(mail_pop_account& self, const std::string& name) {
    std::strncpy(self.pop_host, name.c_str(), B_MAX_HOST_NAME_LENGTH - 1);
    self.pop_host[B_MAX_HOST_NAME_LENGTH - 1] = '\0';
}

std::string get_real_name(const mail_pop_account& self) {
    return std::string(self.real_name);
}

void set_real_name(mail_pop_account& self, const std::string& name) {
    std::strncpy(self.real_name, name.c_str(), 128 - 1);
    self.real_name[128 - 1] = '\0';
}

std::string get_reply_to(const mail_pop_account& self) {
    return std::string(self.reply_to);
}

void set_reply_to(mail_pop_account& self, const std::string& name) {
    std::strncpy(self.reply_to, name.c_str(), 128 - 1);
    self.reply_to[128 - 1] = '\0';
}

status_t	AddEnclosure_wrapper(BMailMessage& self, const char* MIME_type, py::buffer data, int32 len, bool clobber = false) {
	py::buffer_info info = data.request();
	void* buffer = info.ptr;
	return self.AddEnclosure(MIME_type, buffer, len, clobber);
}


PYBIND11_MODULE(Email, m)
{
py::enum_<read_flags>(m, "read_flags", "")
.value("B_UNREAD", read_flags::B_UNREAD, "")
.value("B_SEEN", read_flags::B_SEEN, "")
.value("B_READ", read_flags::B_READ, "")
.export_values();

py::enum_<mail_flags>(m, "mail_flags", "")
.value("B_MAIL_PENDING", mail_flags::B_MAIL_PENDING, "")
.value("B_MAIL_SENT", mail_flags::B_MAIL_SENT, "")
.value("B_MAIL_SAVE", mail_flags::B_MAIL_SAVE, "")
.export_values();

py::class_<mail_pop_account>(m, "mail_pop_account")
//.def_readwrite("pop_name", &mail_pop_account::pop_name, "")
.def_property("pop_name", &get_pop_name, &set_pop_name, "")
//.def_readwrite("pop_password", &mail_pop_account::pop_password, "")
.def_property("pop_password", &get_pop_password, &set_pop_password, "")
//.def_readwrite("pop_host", &mail_pop_account::pop_host, "")
.def_property("pop_host", &get_pop_host, &set_pop_host, "")
//.def_readwrite("real_name", &mail_pop_account::real_name, "")
.def_property("real_name", &get_real_name, &set_real_name, "")
//.def_readwrite("reply_to", &mail_pop_account::reply_to, "")
.def_property("reply_to", &get_reply_to, &set_reply_to, "")
.def_readwrite("days", &mail_pop_account::days, "")
.def_readwrite("interval", &mail_pop_account::interval, "")
.def_readwrite("begin_time", &mail_pop_account::begin_time, "")
.def_readwrite("end_time", &mail_pop_account::end_time, "")
;

py::class_<mail_notification>(m, "mail_notification")
.def_readwrite("alert", &mail_notification::alert, "")
.def_readwrite("beep", &mail_notification::beep, "")
;

py::class_<BMailMessage>(m, "BMailMessage")
.def(py::init(), "")
.def("AddContent", py::overload_cast<const char *, int32, uint32, bool>(&BMailMessage::AddContent), "", py::arg("text"), py::arg("length"), py::arg("encoding")=0, py::arg("clobber")=false)//hardcoded B_ISO1_CONVERSION to 0
.def("AddContent", py::overload_cast<const char *, int32, const char *, bool>(&BMailMessage::AddContent), "", py::arg("text"), py::arg("length"), py::arg("encoding"), py::arg("clobber")=false)
.def("AddEnclosure", py::overload_cast<entry_ref *, bool>(&BMailMessage::AddEnclosure), "", py::arg("ref"), py::arg("clobber")=false)
.def("AddEnclosure", py::overload_cast<const char *, bool>(&BMailMessage::AddEnclosure), "", py::arg("path"), py::arg("clobber")=false)
//.def("AddEnclosure", py::overload_cast<const char *, void *, int32, bool>(&BMailMessage::AddEnclosure), "", py::arg("MIME_type"), py::arg("data"), py::arg("len"), py::arg("clobber")=false)
.def("AddEnclosure", &AddEnclosure_wrapper, "", py::arg("MIME_type"), py::arg("data"), py::arg("len"), py::arg("clobber")=false)
.def("AddHeaderField", py::overload_cast<uint32, const char *, const char *, bool>(&BMailMessage::AddHeaderField), "", py::arg("encoding"), py::arg("field_name"), py::arg("str"), py::arg("clobber")=false)
.def("AddHeaderField", py::overload_cast<const char *, const char *, bool>(&BMailMessage::AddHeaderField), "", py::arg("field_name"), py::arg("str"), py::arg("clobber")=false)
.def("Send", &BMailMessage::Send, "", py::arg("sendNow")=false, py::arg("removeAfterSending")=false)
;

m.def("count_pop_accounts", &count_pop_accounts, "");

m.def("get_pop_account", &get_pop_account, "", py::arg(""), py::arg("index")=0);

m.def("set_pop_account", &set_pop_account, "", py::arg(""), py::arg("index")=0, py::arg("save")=true);

}
