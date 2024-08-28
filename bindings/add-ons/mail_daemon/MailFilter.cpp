#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <add-ons/mail_daemon/MailFilter.h>
#include <add-ons/mail_daemon/MailProtocol.h>
#include <add-ons/mail_daemon/MailSettingsView.h>
namespace py = pybind11;

class PyBMailFilter : public BMailFilter{
	public:
		using BMailFilter::BMailFilter;
        BMailFilterAction	HeaderFetched(entry_ref& ref, BFile& file,	BMessage& attributes) override {
        		PYBIND11_OVERLOAD(BMailFilterAction, BMailFilter, HeaderFetched, ref, file, attributes);
        }
		void				BodyFetched(const entry_ref& ref, BFile& file, BMessage& attributes) override {
        		PYBIND11_OVERLOAD(void, BMailFilter, BodyFetched, ref, file, attributes);
        }
		void				MailboxSynchronized(status_t status) override {
        		PYBIND11_OVERLOAD(void, BMailFilter, MailboxSynchronized, status);
        }
		void				MessageReadyToSend(const entry_ref& ref, BFile& file) override {
        		PYBIND11_OVERLOAD(void, BMailFilter, MessageReadyToSend, ref, file);
        }
		void				MessageSent(const entry_ref& ref, BFile& file) override {
        		PYBIND11_OVERLOAD(void, BMailFilter, MessageSent, ref, file);
        }
};

PYBIND11_MODULE(MailFilter, m)
{
py::class_<BMailFilter, PyBMailFilter>(m, "BMailFilter")
.def(py::init<BMailProtocol&,const BMailAddOnSettings *>(), "", py::arg("protocol"),py::arg("settings"))
.def("HeaderFetched", &BMailFilter::HeaderFetched, "", py::arg("ref"),py::arg("file"), py::arg("attributes"))
/*.def("HeaderFetched", [](BMailFilter& self) {
    entry_ref  ref;
BFile  file;
BMessage  attributes;
    BMailFilterAction r = self.HeaderFetched(ref, file, attributes);
    return std::make_tuple(r,ref,file,attributes);
}
, "")*/
.def("BodyFetched", &BMailFilter::BodyFetched, "", py::arg("ref"),py::arg("file"), py::arg("attributes"))
/*.def("BodyFetched", [](BMailFilter& self,const entry_ref & ref) {
    BFile  file;
BMessage  attributes;
    self.BodyFetched(ref, file, attributes);
    return std::make_tuple(file,attributes);
}
, "", py::arg("ref"))*/
.def("MailboxSynchronized", &BMailFilter::MailboxSynchronized, "", py::arg("status"))
.def("MessageReadyToSend", &BMailFilter::MessageReadyToSend, "", py::arg("ref"), py::arg("file"))
/*.def("MessageReadyToSend", [](BMailFilter& self,const entry_ref & ref) {
    BFile  file;
    self.MessageReadyToSend(ref, file);
    return file;
}
, "", py::arg("ref"))*/
.def("MessageSent", &BMailFilter::MessageSent, "", py::arg("ref"), py::arg("file"))
/*.def("MessageSent", [](BMailFilter& self,const entry_ref & ref) {
    BFile  file;
    self.MessageSent(ref, file);
    return file;
}
, "", py::arg("ref"))*/
;

m.def("instantiate_filter_settings_view", &instantiate_filter_settings_view, "", py::arg("accountSettings"), py::arg("settings"));

m.def("filter_name", &filter_name, "", py::arg("accountSettings"), py::arg("settings"));

m.def("instantiate_filter", [](BMailProtocol&  protocol, const BMailAddOnSettings & settings) {
    BMailFilter * r = instantiate_filter(protocol, settings);
    return r;//std::make_tuple(r,protocol);
}
, "", py::arg("protocol"), py::arg("settings"));

}
