#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <AppFileInfo.h>

namespace py = pybind11;


void define_AppFileInfo(py::module_& m)
{
py::enum_<info_variety>(m, "info_variety", "")
.value("B_DEVELOPMENT_VERSION", info_variety::B_DEVELOPMENT_VERSION, "")
.value("B_ALPHA_VERSION", info_variety::B_ALPHA_VERSION, "")
.value("B_BETA_VERSION", info_variety::B_BETA_VERSION, "")
.value("B_GAMMA_VERSION", info_variety::B_GAMMA_VERSION, "")
.value("B_GOLDEN_MASTER_VERSION", info_variety::B_GOLDEN_MASTER_VERSION, "")
.value("B_FINAL_VERSION", info_variety::B_FINAL_VERSION, "")
.export_values();

py::enum_<info_location>(m, "info_location", "")
.value("B_USE_ATTRIBUTES", info_location::B_USE_ATTRIBUTES, "")
.value("B_USE_RESOURCES", info_location::B_USE_RESOURCES, "")
.value("B_USE_BOTH_LOCATIONS", info_location::B_USE_BOTH_LOCATIONS, "")
.export_values();

py::enum_<version_kind>(m, "version_kind", "")
.value("B_APP_VERSION_KIND", version_kind::B_APP_VERSION_KIND, "")
.value("B_SYSTEM_VERSION_KIND", version_kind::B_SYSTEM_VERSION_KIND, "")
.export_values();

py::class_<version_info>(m, "version_info")
.def_readwrite("major", &version_info::major, "")
.def_readwrite("middle", &version_info::middle, "")
.def_readwrite("minor", &version_info::minor, "")
.def_readwrite("variety", &version_info::variety, "")
.def_readwrite("internal", &version_info::internal, "")
.def_readwrite("short_info", &version_info::short_info, "")
.def_readwrite("long_info", &version_info::long_info, "")
;

py::class_<BAppFileInfo, BNodeInfo>(m, "BAppFileInfo")
.def(py::init(), "")
.def(py::init<BFile *>(), "", py::arg("file"))
.def("SetTo", &BAppFileInfo::SetTo, "", py::arg("file"))
.def("GetType", &BAppFileInfo::GetType, "", py::arg("type"))
.def("SetType", &BAppFileInfo::SetType, "", py::arg("type"))
.def("GetSignature", &BAppFileInfo::GetSignature, "", py::arg("signature"))
.def("SetSignature", &BAppFileInfo::SetSignature, "", py::arg("signature"))
.def("GetCatalogEntry", &BAppFileInfo::GetCatalogEntry, "", py::arg("catalogEntry"))
.def("SetCatalogEntry", &BAppFileInfo::SetCatalogEntry, "", py::arg("catalogEntry"))
.def("GetAppFlags", &BAppFileInfo::GetAppFlags, "", py::arg("flags"))
.def("SetAppFlags", &BAppFileInfo::SetAppFlags, "", py::arg("flags"))
.def("RemoveAppFlags", &BAppFileInfo::RemoveAppFlags, "")
.def("GetSupportedTypes", &BAppFileInfo::GetSupportedTypes, "", py::arg("types"))
.def("SetSupportedTypes", py::overload_cast<const BMessage *, bool, bool>(&BAppFileInfo::SetSupportedTypes), "", py::arg("types"), py::arg("updateMimeDB"), py::arg("syncAll"))
.def("SetSupportedTypes", py::overload_cast<const BMessage *, bool>(&BAppFileInfo::SetSupportedTypes), "", py::arg("types"), py::arg("syncAll"))
.def("SetSupportedTypes", py::overload_cast<const BMessage *>(&BAppFileInfo::SetSupportedTypes), "", py::arg("types"))
.def("IsSupportedType", &BAppFileInfo::IsSupportedType, "", py::arg("type"))
.def("Supports", &BAppFileInfo::Supports, "", py::arg("type"))
.def("GetIcon", py::overload_cast<BBitmap *, icon_size>(&BAppFileInfo::GetIcon), "", py::arg("icon"), py::arg("which"))
.def("SetIcon", py::overload_cast<const BBitmap *, icon_size, bool>(&BAppFileInfo::SetIcon), "", py::arg("icon"), py::arg("which"), py::arg("updateMimeDB"))
.def("SetIcon", py::overload_cast<const BBitmap *, icon_size>(&BAppFileInfo::SetIcon), "", py::arg("icon"), py::arg("which"))
.def("GetIcon", py::overload_cast<unsigned char, size_t *>(&BAppFileInfo::GetIcon), "", py::arg("data"), py::arg("size"))
.def("SetIcon", py::overload_cast<unsigned char, size_t, bool>(&BAppFileInfo::SetIcon), "", py::arg("data"), py::arg("size"), py::arg("updateMimeDB"))
.def("SetIcon", py::overload_cast<unsigned char, size_t>(&BAppFileInfo::SetIcon), "", py::arg("data"), py::arg("size"))
.def("GetVersionInfo", &BAppFileInfo::GetVersionInfo, "", py::arg("info"), py::arg("kind"))
.def("SetVersionInfo", &BAppFileInfo::SetVersionInfo, "", py::arg("info"), py::arg("kind"))
.def("GetIconForType", py::overload_cast<const char *, BBitmap *, icon_size>(&BAppFileInfo::GetIconForType), "", py::arg("type"), py::arg("icon"), py::arg("which"))
.def("GetIconForType", py::overload_cast<const char *, unsigned char, size_t *>(&BAppFileInfo::GetIconForType), "", py::arg("type"), py::arg("data"), py::arg("size"))
.def("SetIconForType", py::overload_cast<const char *, const BBitmap *, icon_size, bool>(&BAppFileInfo::SetIconForType), "", py::arg("type"), py::arg("icon"), py::arg("which"), py::arg("updateMimeDB"))
.def("SetIconForType", py::overload_cast<const char *, const BBitmap *, icon_size>(&BAppFileInfo::SetIconForType), "", py::arg("type"), py::arg("icon"), py::arg("which"))
.def("SetIconForType", py::overload_cast<const char *, unsigned char, size_t, bool>(&BAppFileInfo::SetIconForType), "", py::arg("type"), py::arg("data"), py::arg("size"), py::arg("updateMimeDB"))
.def("SetIconForType", py::overload_cast<const char *, unsigned char, size_t>(&BAppFileInfo::SetIconForType), "", py::arg("type"), py::arg("data"), py::arg("size"))
.def("SetInfoLocation", &BAppFileInfo::SetInfoLocation, "", py::arg("location"))
.def("IsUsingAttributes", &BAppFileInfo::IsUsingAttributes, "")
.def("IsUsingResources", &BAppFileInfo::IsUsingResources, "")
;


}
