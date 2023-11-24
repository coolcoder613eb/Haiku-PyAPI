#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <MimeType.h>

namespace py = pybind11;
using namespace BPrivate;
using namespace BPrivate::Storage;
using namespace BPrivate::Storage::Mime;

void define_MimeType(py::module_& m)
{
py::enum_<app_verb>(m, "app_verb", "")
.value("B_OPEN", app_verb::B_OPEN, "")
.export_values();

m.attr("B_META_MIME_CHANGED") = py::cast(B_META_MIME_CHANGED);

m.attr("B_ICON_CHANGED") = py::cast(B_ICON_CHANGED);
m.attr("B_PREFERRED_APP_CHANGED") = py::cast(B_PREFERRED_APP_CHANGED);
m.attr("B_ATTR_INFO_CHANGED") = py::cast(B_ATTR_INFO_CHANGED);
m.attr("B_FILE_EXTENSIONS_CHANGED") = py::cast(B_FILE_EXTENSIONS_CHANGED);
m.attr("B_SHORT_DESCRIPTION_CHANGED") = py::cast(B_SHORT_DESCRIPTION_CHANGED);
m.attr("B_LONG_DESCRIPTION_CHANGED") = py::cast(B_LONG_DESCRIPTION_CHANGED);
m.attr("B_ICON_FOR_TYPE_CHANGED") = py::cast(B_ICON_FOR_TYPE_CHANGED);
m.attr("B_APP_HINT_CHANGED") = py::cast(B_APP_HINT_CHANGED);
m.attr("B_MIME_TYPE_CREATED") = py::cast(B_MIME_TYPE_CREATED);
m.attr("B_MIME_TYPE_DELETED") = py::cast(B_MIME_TYPE_DELETED);
m.attr("B_SNIFFER_RULE_CHANGED") = py::cast(B_SNIFFER_RULE_CHANGED);
m.attr("B_SUPPORTED_TYPES_CHANGED") = py::cast(B_SUPPORTED_TYPES_CHANGED);
m.attr("B_EVERYTHING_CHANGED") = py::cast(B_EVERYTHING_CHANGED);

m.attr("B_META_MIME_MODIFIED") = py::cast(B_META_MIME_MODIFIED);
m.attr("B_META_MIME_DELETED") = py::cast(B_META_MIME_DELETED);

m.attr("MimeDatabase") = py::cast(MimeDatabase);

m.attr("CreateAppMetaMimeThread") = py::cast(CreateAppMetaMimeThread);

m.attr("B_APP_MIME_TYPE") = py::cast(B_APP_MIME_TYPE);

m.attr("B_PEF_APP_MIME_TYPE") = py::cast(B_PEF_APP_MIME_TYPE);

m.attr("B_PE_APP_MIME_TYPE") = py::cast(B_PE_APP_MIME_TYPE);

m.attr("B_ELF_APP_MIME_TYPE") = py::cast(B_ELF_APP_MIME_TYPE);

m.attr("B_RESOURCE_MIME_TYPE") = py::cast(B_RESOURCE_MIME_TYPE);

m.attr("B_FILE_MIME_TYPE") = py::cast(B_FILE_MIME_TYPE);

py::class_<BMimeType>(m, "BMimeType")
.def(py::init(), "")
.def(py::init<const char *>(), "", py::arg("mimeType"))
.def("SetTo", &BMimeType::SetTo, "", py::arg("mimeType"))
.def("Unset", &BMimeType::Unset, "")
.def("InitCheck", &BMimeType::InitCheck, "")
.def("Type", &BMimeType::Type, "")
.def("IsValid", py::overload_cast<>(&BMimeType::IsValid), "")
.def("IsSupertypeOnly", &BMimeType::IsSupertypeOnly, "")
.def("GetSupertype", &BMimeType::GetSupertype, "", py::arg("supertype"))
.def("__eq__", py::overload_cast<const BMimeType &>(&BMimeType::operator==), "", py::arg("type"))
.def("__eq__", py::overload_cast<const char *>(&BMimeType::operator==), "", py::arg("type"))
.def("Contains", &BMimeType::Contains, "", py::arg("type"))
.def("Install", &BMimeType::Install, "")
.def("Delete", &BMimeType::Delete, "")
.def("IsInstalled", &BMimeType::IsInstalled, "")
.def("GetIcon", py::overload_cast<BBitmap *, icon_size>(&BMimeType::GetIcon), "", py::arg("icon"), py::arg("size"))
.def("GetIcon", py::overload_cast<unsigned char, size_t *>(&BMimeType::GetIcon), "", py::arg("_data"), py::arg("_size"))
.def("GetPreferredApp", &BMimeType::GetPreferredApp, "", py::arg("signature"), py::arg("verb")=B_OPEN)
.def("GetAttrInfo", &BMimeType::GetAttrInfo, "", py::arg("info"))
.def("GetFileExtensions", &BMimeType::GetFileExtensions, "", py::arg("extensions"))
.def("GetShortDescription", &BMimeType::GetShortDescription, "", py::arg("description"))
.def("GetLongDescription", &BMimeType::GetLongDescription, "", py::arg("description"))
.def("GetSupportingApps", &BMimeType::GetSupportingApps, "", py::arg("signatures"))
.def("SetIcon", py::overload_cast<const BBitmap *, icon_size>(&BMimeType::SetIcon), "", py::arg("icon"), py::arg("size"))
.def("SetIcon", py::overload_cast<unsigned char, size_t>(&BMimeType::SetIcon), "", py::arg("data"), py::arg("size"))
.def("SetPreferredApp", &BMimeType::SetPreferredApp, "", py::arg("signature"), py::arg("verb")=B_OPEN)
.def("SetAttrInfo", &BMimeType::SetAttrInfo, "", py::arg("info"))
.def("SetFileExtensions", &BMimeType::SetFileExtensions, "", py::arg("extensions"))
.def("SetShortDescription", &BMimeType::SetShortDescription, "", py::arg("description"))
.def("SetLongDescription", &BMimeType::SetLongDescription, "", py::arg("description"))
.def_static("GetInstalledSupertypes", &BMimeType::GetInstalledSupertypes, "", py::arg("supertypes"))
.def_static("GetInstalledTypes", py::overload_cast<BMessage *>(&BMimeType::GetInstalledTypes), "", py::arg("types"))
.def_static("GetInstalledTypes", py::overload_cast<const char *, BMessage *>(&BMimeType::GetInstalledTypes), "", py::arg("supertype"), py::arg("subtypes"))
.def_static("GetWildcardApps", &BMimeType::GetWildcardApps, "", py::arg("wildcardApps"))
.def_static("IsValid", py::overload_cast<const char *>(&BMimeType::IsValid), "", py::arg("mimeType"))
.def("GetAppHint", &BMimeType::GetAppHint, "", py::arg("ref"))
.def("SetAppHint", &BMimeType::SetAppHint, "", py::arg("ref"))
.def("GetIconForType", py::overload_cast<const char *, BBitmap *, icon_size>(&BMimeType::GetIconForType), "", py::arg("type"), py::arg("icon"), py::arg("which"))
.def("GetIconForType", py::overload_cast<const char *, unsigned char, size_t *>(&BMimeType::GetIconForType), "", py::arg("type"), py::arg("_data"), py::arg("_size"))
.def("SetIconForType", py::overload_cast<const char *, const BBitmap *, icon_size>(&BMimeType::SetIconForType), "", py::arg("type"), py::arg("icon"), py::arg("which"))
.def("SetIconForType", py::overload_cast<const char *, unsigned char, size_t>(&BMimeType::SetIconForType), "", py::arg("type"), py::arg("data"), py::arg("size"))
.def("GetSnifferRule", &BMimeType::GetSnifferRule, "", py::arg("result"))
.def("SetSnifferRule", &BMimeType::SetSnifferRule, "", py::arg(""))
.def_static("CheckSnifferRule", &BMimeType::CheckSnifferRule, "", py::arg("rule"), py::arg("parseError"))
.def_static("GuessMimeType", py::overload_cast<const entry_ref *, BMimeType *>(&BMimeType::GuessMimeType), "", py::arg("file"), py::arg("type"))
.def_static("GuessMimeType", py::overload_cast<const void *, int, BMimeType *>(&BMimeType::GuessMimeType), "", py::arg("buffer"), py::arg("length"), py::arg("type"))
.def_static("GuessMimeType", py::overload_cast<const char *, BMimeType *>(&BMimeType::GuessMimeType), "", py::arg("filename"), py::arg("type"))
.def_static("StartWatching", &BMimeType::StartWatching, "", py::arg("target"))
.def_static("StopWatching", &BMimeType::StopWatching, "", py::arg("target"))
.def("SetType", &BMimeType::SetType, "", py::arg("mimeType"))
;


}