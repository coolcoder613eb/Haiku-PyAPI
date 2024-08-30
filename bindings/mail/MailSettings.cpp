#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <mail/MailSettings.h>

namespace py = pybind11;


void define_MailSettings(py::module_& m)
{
py::enum_<b_mail_status_window_option>(m, "b_mail_status_window_option", "")
.value("B_MAIL_SHOW_STATUS_WINDOW_NEVER", b_mail_status_window_option::B_MAIL_SHOW_STATUS_WINDOW_NEVER, "")
.value("B_MAIL_SHOW_STATUS_WINDOW_WHEN_SENDING", b_mail_status_window_option::B_MAIL_SHOW_STATUS_WINDOW_WHEN_SENDING, "")
.value("B_MAIL_SHOW_STATUS_WINDOW_WHEN_ACTIVE", b_mail_status_window_option::B_MAIL_SHOW_STATUS_WINDOW_WHEN_ACTIVE, "")
.value("B_MAIL_SHOW_STATUS_WINDOW_ALWAYS", b_mail_status_window_option::B_MAIL_SHOW_STATUS_WINDOW_ALWAYS, "")
.export_values();

py::class_<BMailSettings>(m, "BMailSettings")
.def(py::init(), "")
.def("Save", &BMailSettings::Save, "")
.def("Reload", &BMailSettings::Reload, "")
.def("InitCheck", &BMailSettings::InitCheck, "")
.def("WindowFollowsCorner", &BMailSettings::WindowFollowsCorner, "")
.def("SetWindowFollowsCorner", &BMailSettings::SetWindowFollowsCorner, "", py::arg("which_corner"))
.def("ShowStatusWindow", &BMailSettings::ShowStatusWindow, "")
.def("SetShowStatusWindow", &BMailSettings::SetShowStatusWindow, "", py::arg("mode"))
.def("DaemonAutoStarts", &BMailSettings::DaemonAutoStarts, "")
.def("SetDaemonAutoStarts", &BMailSettings::SetDaemonAutoStarts, "", py::arg("does_it"))
.def("SetConfigWindowFrame", &BMailSettings::SetConfigWindowFrame, "", py::arg("frame"))
.def("ConfigWindowFrame", &BMailSettings::ConfigWindowFrame, "")
.def("SetStatusWindowFrame", &BMailSettings::SetStatusWindowFrame, "", py::arg("frame"))
.def("StatusWindowFrame", &BMailSettings::StatusWindowFrame, "")
.def("StatusWindowWorkspaces", &BMailSettings::StatusWindowWorkspaces, "")
.def("SetStatusWindowWorkspaces", &BMailSettings::SetStatusWindowWorkspaces, "", py::arg("workspaces"))
.def("StatusWindowLook", &BMailSettings::StatusWindowLook, "")
.def("SetStatusWindowLook", &BMailSettings::SetStatusWindowLook, "", py::arg("look"))
.def("AutoCheckInterval", &BMailSettings::AutoCheckInterval, "")
.def("SetAutoCheckInterval", &BMailSettings::SetAutoCheckInterval, "", py::arg(""))
.def("CheckOnlyIfPPPUp", &BMailSettings::CheckOnlyIfPPPUp, "")
.def("SetCheckOnlyIfPPPUp", &BMailSettings::SetCheckOnlyIfPPPUp, "", py::arg("yes"))
.def("SendOnlyIfPPPUp", &BMailSettings::SendOnlyIfPPPUp, "")
.def("SetSendOnlyIfPPPUp", &BMailSettings::SetSendOnlyIfPPPUp, "", py::arg("yes"))
.def("DefaultOutboundAccount", &BMailSettings::DefaultOutboundAccount, "")
.def("SetDefaultOutboundAccount", &BMailSettings::SetDefaultOutboundAccount, "", py::arg("to"))
;

py::class_<BMailAddOnSettings, BMessage>(m, "BMailAddOnSettings")
.def(py::init(), "")
.def("Load", &BMailAddOnSettings::Load, "", py::arg("message"))
.def("Save", [](BMailAddOnSettings& self) {
    BMessage  message;
    status_t r = self.Save(message);
    return std::make_tuple(r,message);
}
, "")
.def("SetAddOnRef", &BMailAddOnSettings::SetAddOnRef, "", py::arg("ref"))
.def("AddOnRef", &BMailAddOnSettings::AddOnRef, "")
.def("HasBeenModified", &BMailAddOnSettings::HasBeenModified, "")
;

py::class_<BMailProtocolSettings, BMailAddOnSettings>(m, "BMailProtocolSettings")
.def(py::init(), "")
.def("Load", &BMailProtocolSettings::Load, "", py::arg("message"))
.def("Save", [](BMailProtocolSettings& self) {
    BMessage  message;
    status_t r = self.Save(message);
    return std::make_tuple(r,message);
}
, "")
.def("CountFilterSettings", &BMailProtocolSettings::CountFilterSettings, "")
.def("AddFilterSettings", &BMailProtocolSettings::AddFilterSettings, "", py::arg("ref")=NULL)
.def("RemoveFilterSettings", &BMailProtocolSettings::RemoveFilterSettings, "", py::arg("index"))
.def("MoveFilterSettings", &BMailProtocolSettings::MoveFilterSettings, "", py::arg("from"), py::arg("to"))
.def("FilterSettingsAt", &BMailProtocolSettings::FilterSettingsAt, "", py::arg("index"))
.def("HasBeenModified", &BMailProtocolSettings::HasBeenModified, "")
;

py::class_<BMailAccountSettings>(m, "BMailAccountSettings")
.def(py::init(), "")
.def(py::init<BEntry>(), "", py::arg("account"))
.def("InitCheck", &BMailAccountSettings::InitCheck, "")
.def("SetAccountID", &BMailAccountSettings::SetAccountID, "", py::arg("id"))
.def("AccountID", &BMailAccountSettings::AccountID, "")
.def("SetName", &BMailAccountSettings::SetName, "", py::arg("name"))
.def("Name", &BMailAccountSettings::Name, "")
.def("SetRealName", &BMailAccountSettings::SetRealName, "", py::arg("realName"))
.def("RealName", &BMailAccountSettings::RealName, "")
.def("SetReturnAddress", &BMailAccountSettings::SetReturnAddress, "", py::arg("returnAddress"))
.def("ReturnAddress", &BMailAccountSettings::ReturnAddress, "")
.def("SetInboundAddOn", &BMailAccountSettings::SetInboundAddOn, "", py::arg("name"))
.def("SetOutboundAddOn", &BMailAccountSettings::SetOutboundAddOn, "", py::arg("name"))
.def("InboundAddOnRef", &BMailAccountSettings::InboundAddOnRef, "")
.def("OutboundAddOnRef", &BMailAccountSettings::OutboundAddOnRef, "")
.def("InboundSettings", py::overload_cast<>(&BMailAccountSettings::InboundSettings), "")
.def("InboundSettings", py::overload_cast<>(&BMailAccountSettings::InboundSettings), "")
.def("OutboundSettings", py::overload_cast<>(&BMailAccountSettings::OutboundSettings), "")
.def("OutboundSettings", py::overload_cast<>(&BMailAccountSettings::OutboundSettings), "")
.def("HasInbound", &BMailAccountSettings::HasInbound, "")
.def("HasOutbound", &BMailAccountSettings::HasOutbound, "")
.def("SetInboundEnabled", &BMailAccountSettings::SetInboundEnabled, "", py::arg("enabled")=true)
.def("IsInboundEnabled", &BMailAccountSettings::IsInboundEnabled, "")
.def("SetOutboundEnabled", &BMailAccountSettings::SetOutboundEnabled, "", py::arg("enabled")=true)
.def("IsOutboundEnabled", &BMailAccountSettings::IsOutboundEnabled, "")
.def("Reload", &BMailAccountSettings::Reload, "")
.def("Save", &BMailAccountSettings::Save, "")
.def("Delete", &BMailAccountSettings::Delete, "")
.def("HasBeenModified", &BMailAccountSettings::HasBeenModified, "")
.def("AccountFile", &BMailAccountSettings::AccountFile, "")
;

py::class_<BMailAccounts>(m, "BMailAccounts")
.def(py::init(), "")
.def_static("AccountsPath", [](BMailAccounts& self) {
    BPath  path;
    static status_t r = self.AccountsPath(path);
    return std::make_tuple(r,path);
}
, "")
.def("CountAccounts", &BMailAccounts::CountAccounts, "")
.def("AccountAt", &BMailAccounts::AccountAt, "", py::arg("index"))
.def("AccountByID", &BMailAccounts::AccountByID, "", py::arg("id"))
.def("AccountByName", &BMailAccounts::AccountByName, "", py::arg("name"))
;


}
