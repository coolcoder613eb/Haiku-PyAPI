#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/Url.h>

namespace py = pybind11;


PYBIND11_MODULE(Url, m)
{
py::class_<BUrl, BArchivable>(m, "BUrl")
.def(py::init<const char *, bool>(), "", py::arg("url"),py::arg("encode")=true)
.def(py::init<BMessage *>(), "", py::arg("archive"))
.def(py::init<const BUrl &>(), "", py::arg("other"))
.def(py::init<const BUrl &, const BString &>(), "", py::arg("base"), py::arg("relative"))
.def(py::init<const BPath &>(), "", py::arg("path"))
.def(py::init(), "")
.def("SetUrlString", py::overload_cast<const BString&, bool>(&BUrl::SetUrlString), "", py::arg("url"),py::arg("encode")=true)
//.def("SetUrlString", py::overload_cast<const BString&>(&BUrl::SetUrlString), "", py::arg("url"))
.def("SetProtocol", &BUrl::SetProtocol, "", py::arg("scheme"))
.def("SetUserName", &BUrl::SetUserName, "", py::arg("user"))
.def("SetPassword", &BUrl::SetPassword, "", py::arg("password"))
.def("SetAuthority", &BUrl::SetAuthority, "", py::arg("authority"))
.def("SetHost", &BUrl::SetHost, "", py::arg("host"))
.def("SetPort", &BUrl::SetPort, "", py::arg("port"))
.def("SetPath", &BUrl::SetPath, "", py::arg("path"))
.def("SetRequest", &BUrl::SetRequest, "", py::arg("request"))
.def("SetFragment", &BUrl::SetFragment, "", py::arg("fragment"))
.def("UrlString", &BUrl::UrlString, "")
.def("Protocol", &BUrl::Protocol, "")
.def("UserName", &BUrl::UserName, "")
.def("Password", &BUrl::Password, "")
.def("UserInfo", &BUrl::UserInfo, "")
.def("Host", &BUrl::Host, "")
.def("Port", &BUrl::Port, "")
.def("Authority", &BUrl::Authority, "")
.def("Path", &BUrl::Path, "")
.def("Request", &BUrl::Request, "")
.def("Fragment", &BUrl::Fragment, "")
.def("IsValid", &BUrl::IsValid, "")
.def("HasProtocol", &BUrl::HasProtocol, "")
.def("HasUserName", &BUrl::HasUserName, "")
.def("HasPassword", &BUrl::HasPassword, "")
.def("HasUserInfo", &BUrl::HasUserInfo, "")
.def("HasHost", &BUrl::HasHost, "")
.def("HasPort", &BUrl::HasPort, "")
.def("HasAuthority", &BUrl::HasAuthority, "")
.def("HasPath", &BUrl::HasPath, "")
.def("HasRequest", &BUrl::HasRequest, "")
.def("HasFragment", &BUrl::HasFragment, "")
//.def("UrlEncode", py::overload_cast<bool>(&BUrl::UrlEncode), "", py::arg("strict")=false)
//.def("UrlDecode", py::overload_cast<bool>(&BUrl::UrlDecode), "", py::arg("strict")=false)
.def("IDNAToAscii", &BUrl::IDNAToAscii, "")
.def("IDNAToUnicode", &BUrl::IDNAToUnicode, "")
.def_static("UrlEncodeStatic", py::overload_cast<const BString &, bool, bool>(&BUrl::UrlEncode), "", py::arg("url"), py::arg("strict")=false, py::arg("directory")=false)
.def_static("UrlDecodeStatic", py::overload_cast<const BString &, bool>(&BUrl::UrlDecode), "", py::arg("url"), py::arg("strict")=false)
.def("HasPreferredApplication", &BUrl::HasPreferredApplication, "")
.def("PreferredApplication", &BUrl::PreferredApplication, "")
.def("OpenWithPreferredApplication", &BUrl::OpenWithPreferredApplication, "", py::arg("onProblemAskUser")=true)
.def("Archive", &BUrl::Archive, "", py::arg("into"), py::arg("deep")=true)
.def_static("Instantiate", &BUrl::Instantiate, "", py::arg("archive"))
.def("__eq__", [](BUrl& self) {
    BUrl  other;
    bool r = self.operator==(other);
    return std::make_tuple(r,other);
}
, "")
.def("__ne__", [](BUrl& self) {
    BUrl  other;
    bool r = self.operator!=(other);
    return std::make_tuple(r,other);
}
, "")
.def("operator=", py::overload_cast<const BUrl &>(&BUrl::operator=), "", py::arg("other"))
.def("operator=", py::overload_cast<const BString &>(&BUrl::operator=), "", py::arg("string"))
.def("operator=", py::overload_cast<const char *>(&BUrl::operator=), "", py::arg("string"))
//.def("operatorconstchar*", &BUrl::operatorconstchar*, "")
;


}
