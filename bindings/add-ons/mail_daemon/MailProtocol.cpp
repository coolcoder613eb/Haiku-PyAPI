#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <add-ons/mail_daemon/MailProtocol.h>
#include <add-ons/mail_daemon/MailSettingsView.h>
#include <add-ons/mail_daemon/MailFilter.h>
#include <MailSettings.h>
#include <Messenger.h>

namespace py = pybind11;

class PyBMailNotifier : public BMailNotifier{
	public:
		using BMailNotifier::BMailNotifier;
		BMailNotifier*			Clone() override {
        		PYBIND11_OVERLOAD_PURE(BMailNotifier*, BMailNotifier, Clone);
        }
        void					ShowError(const char* error) override {
        		PYBIND11_OVERLOAD_PURE(void, BMailNotifier, ShowError, error);
        }
		void					ShowMessage(const char* message) override {
        		PYBIND11_OVERLOAD_PURE(void, BMailNotifier, ShowMessage, message);
        }
		void					SetTotalItems(uint32 items) override {
        		PYBIND11_OVERLOAD_PURE(void, BMailNotifier, SetTotalItems, items);
        }
		void					SetTotalItemsSize(uint64 size) override {
        		PYBIND11_OVERLOAD_PURE(void, BMailNotifier, SetTotalItemsSize, size);
        }
		void				ReportProgress(uint32 items, uint64 bytes, const char* message = NULL)  override {
        		PYBIND11_OVERLOAD_PURE(void, BMailNotifier, ReportProgress, items, bytes, message);
        }
		void				ResetProgress(const char* message = NULL)  override {
        		PYBIND11_OVERLOAD_PURE(void, BMailNotifier, ResetProgress, message);
        }
};

class PyBMailProtocol : public BMailProtocol{
	public:
		using BMailProtocol::BMailProtocol;
		void				MessageReceived(BMessage* message) override {
				PYBIND11_OVERLOAD(void, BMailProtocol, MessageReceived, message);
		}
};


PYBIND11_MODULE(MailProtocol, m)
{
py::class_<BMailNotifier,PyBMailNotifier>(m, "BMailNotifier")
.def("Clone", &BMailNotifier::Clone, "")
.def("ShowError", &BMailNotifier::ShowError, "", py::arg("error"))
.def("ShowMessage", &BMailNotifier::ShowMessage, "", py::arg("message"))
.def("SetTotalItems", &BMailNotifier::SetTotalItems, "", py::arg("items"))
.def("SetTotalItemsSize", &BMailNotifier::SetTotalItemsSize, "", py::arg("size"))
.def("ReportProgress", &BMailNotifier::ReportProgress, "", py::arg("items"), py::arg("bytes"), py::arg("message")=NULL)
.def("ResetProgress", &BMailNotifier::ResetProgress, "", py::arg("message")=NULL)
;

py::class_<BMailProtocol,PyBMailProtocol, BLooper>(m, "BMailProtocol")
.def(py::init<const char *, const BMailAccountSettings &>(), "", py::arg("name"), py::arg("settings"))
.def("AccountSettings", &BMailProtocol::AccountSettings, "")
.def("SetMailNotifier", &BMailProtocol::SetMailNotifier, "", py::arg("mailNotifier"))
.def("MailNotifier", &BMailProtocol::MailNotifier, "")
.def("AddFilter", py::overload_cast<BMailFilter*>(&BMailProtocol::AddFilter), "", py::arg("filter"))
.def("CountFilter", &BMailProtocol::CountFilter, "")
.def("FilterAt", &BMailProtocol::FilterAt, "", py::arg("index"))
.def("RemoveFilter", py::overload_cast<int>(&BMailProtocol::RemoveFilter), "", py::arg("index"))
.def("RemoveFilter", py::overload_cast<BMailFilter *>(&BMailProtocol::RemoveFilter), "", py::arg("filter"))
.def("MessageReceived", &BMailProtocol::MessageReceived, "", py::arg("message"))
.def("ShowError", &BMailProtocol::ShowError, "", py::arg("error"))
.def("ShowMessage", &BMailProtocol::ShowMessage, "", py::arg("message"))
//.def_readwrite("AddFilter",  &BMailProtocol::AddFilter, "")
//.def_readwrite("RemoveFilter", &BMailProtocol::RemoveFilter, "")
;

/*
py::class_<BInboundMailProtocol, BMailProtocol>(m, "BInboundMailProtocol")
.def(py::init<const char *, const BMailAccountSettings &>(), "", py::arg("name"), py::arg("settings"))
.def("MessageReceived", &BInboundMailProtocol::MessageReceived, "", py::arg("message"))
.def("SyncMessages", &BInboundMailProtocol::SyncMessages, "")
.def("FetchBody", &BInboundMailProtocol::FetchBody, "", py::arg("ref"), py::arg("replyTo"))
.def("MarkMessageAsRead", &BInboundMailProtocol::MarkMessageAsRead, "", py::arg("ref"), py::arg("flags")=B_READ)
.def_static("ReplyBodyFetched", &BInboundMailProtocol::ReplyBodyFetched, "", py::arg("replyTo"), py::arg("ref"), py::arg("status"))
;

py::class_<BOutboundMailProtocol, BMailProtocol>(m, "BOutboundMailProtocol")
.def(py::init<const char *, const BMailAccountSettings &>(), "", py::arg("name"), py::arg("settings"))
.def("SendMessages", &BOutboundMailProtocol::SendMessages, "", py::arg("message"), py::arg("totalBytes"))
.def("MessageReceived", &BOutboundMailProtocol::MessageReceived, "", py::arg("message"))
;*/

m.def("instantiate_inbound_protocol", &instantiate_inbound_protocol, "", py::arg("settings"));

m.def("instantiate_outbound_protocol", &instantiate_outbound_protocol, "", py::arg("settings"));

m.def("instantiate_protocol_settings_view", &instantiate_protocol_settings_view, "", py::arg("accountSettings"), py::arg("settings"));

//#define B_NO_MAIL_ACTION		0
//#define B_MOVE_MAIL_ACTION		1
//#define B_DELETE_MAIL_ACTION	2

}
