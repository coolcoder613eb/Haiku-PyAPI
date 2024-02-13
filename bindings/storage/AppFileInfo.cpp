#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <AppFileInfo.h>
#include <Bitmap.h>

namespace py = pybind11;

/*
// promemoria
struct version_info {
    uint32_t major;
    uint32_t middle;
    uint32_t minor;
    uint32_t variety;
    uint32_t internal;
    char short_info[64];
    char long_info[256];
};*/

PYBIND11_MODULE(AppFileInfo, m)
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
.def(py::init<>())
.def_readwrite("major", &version_info::major, "")
.def_readwrite("middle", &version_info::middle, "")
.def_readwrite("minor", &version_info::minor, "")
.def_readwrite("variety", &version_info::variety, "")
.def_readwrite("internal", &version_info::internal, "")
// TODO Test short_info & long_info
//.def_readwrite("short_info", &version_info::short_info, "")
.def_property(
            "short_info",
            [](const version_info &info) {
                return py::cast(info.short_info);
            },
            	//tentativo non provato n.1
                /*py::array_t<char> result(){
                	char data[64];
                	return py::array_t<char>{64},{1},data
                };
                }.
                std::memcpy(result.mutable_data(), &info.short_info, sizeof(info.short_info));
                return result;
            },
            [](version_info &info, py::array_t<char> value) {
                if (value.size() != 64) { //check how write minor
                    throw std::runtime_error("Array must have size 64");
                }
                std::memcpy(&info.short_info, value.data(), sizeof(info.short_info));
            }*/
            [](version_info &info, const std::string &value) {
            	if (value.size()<sizeof(info.short_info)) {
            		std::copy(value.begin(), value.end(), info.short_info);
            		info.short_info[value.size()] = '\0';
            	} else { 
            		throw std::invalid_argument("Wrong short_info dimension, it exceeds 64 chars");
            	}
            }
        , "")
//.def_readwrite("long_info", &version_info::long_info, "")
.def_property(
            "long_info",
            [](const version_info &info) {
                return py::cast(info.long_info);
            },
            [](version_info &info, const std::string &value) {
            	if (value.size()<sizeof(info.long_info)) {
            		std::copy(value.begin(), value.end(), info.long_info);
            		info.long_info[value.size()] = '\0';
            	} else { 
            		throw std::invalid_argument("Wrong long_info dimension, it exceeds 256 chars");
            	}
            }
        , "")
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
.def("GetIcon", py::overload_cast<BBitmap *, icon_size>(&BAppFileInfo::GetIcon, py::const_), "", py::arg("icon"), py::arg("which"))
.def("SetIcon", py::overload_cast<const BBitmap *, icon_size, bool>(&BAppFileInfo::SetIcon), "", py::arg("icon"), py::arg("which"), py::arg("updateMimeDB"))
.def("SetIcon", py::overload_cast<const BBitmap *, icon_size>(&BAppFileInfo::SetIcon), "", py::arg("icon"), py::arg("which"))
//.def("GetIcon", py::overload_cast<unsigned char, size_t *>(&BAppFileInfo::GetIcon), "", py::arg("data"), py::arg("size"))
.def("GetIcon", [](const BAppFileInfo& self, py::list& _data, size_t& _size) {
            uint8* data = nullptr;
            size_t size = 0;
            status_t result = self.GetIcon(&data, &size);
            for (size_t i = 0; i < size; ++i) {
                _data.append(data[i]);
            }
            _size = size;
            delete[] data;
            return result;
},"", py::arg("_data"), py::arg("_size"))
//.def("SetIcon", py::overload_cast<unsigned char, size_t, bool>(&BAppFileInfo::SetIcon), "", py::arg("data"), py::arg("size"), py::arg("updateMimeDB")) //TODO
//.def("SetIcon", py::overload_cast<unsigned char, size_t>(&BAppFileInfo::SetIcon), "", py::arg("data"), py::arg("size"))  //TODO
.def("GetVersionInfo", &BAppFileInfo::GetVersionInfo, "", py::arg("info"), py::arg("kind"))
.def("SetVersionInfo", &BAppFileInfo::SetVersionInfo, "", py::arg("info"), py::arg("kind"))
.def("GetIconForType", py::overload_cast<const char *, BBitmap *, icon_size>(&BAppFileInfo::GetIconForType, py::const_), "", py::arg("type"), py::arg("icon"), py::arg("which"))
//.def("GetIconForType", py::overload_cast<const char *, unsigned char, size_t *>(&BAppFileInfo::GetIconForType), "", py::arg("type"), py::arg("data"), py::arg("size"))
.def("GetIconForType", [](const BAppFileInfo &self, const char *type, py::list& _data, size_t& _size) {
            uint8* data = nullptr;
            size_t size = 0;
            status_t result = self.GetIconForType(type, &data, &size);
            for (size_t i = 0; i < size; ++i) {
                _data.append(data[i]);
            }
            _size = size;
            delete[] data;
            return result;
},"", py::arg("type"), py::arg("_data"), py::arg("_size"))
.def("SetIconForType", py::overload_cast<const char *, const BBitmap *, icon_size, bool>(&BAppFileInfo::SetIconForType), "", py::arg("type"), py::arg("icon"), py::arg("which"), py::arg("updateMimeDB"))
.def("SetIconForType", py::overload_cast<const char *, const BBitmap *, icon_size>(&BAppFileInfo::SetIconForType), "", py::arg("type"), py::arg("icon"), py::arg("which"))
//.def("SetIconForType", py::overload_cast<const char *, unsigned char, size_t, bool>(&BAppFileInfo::SetIconForType), "", py::arg("type"), py::arg("data"), py::arg("size"), py::arg("updateMimeDB")) //TODO
//.def("SetIconForType", py::overload_cast<const char *, unsigned char, size_t>(&BAppFileInfo::SetIconForType), "", py::arg("type"), py::arg("data"), py::arg("size")) //TODO
.def("SetInfoLocation", &BAppFileInfo::SetInfoLocation, "", py::arg("location"))
.def("IsUsingAttributes", &BAppFileInfo::IsUsingAttributes, "")
.def("IsUsingResources", &BAppFileInfo::IsUsingResources, "")
;


}
