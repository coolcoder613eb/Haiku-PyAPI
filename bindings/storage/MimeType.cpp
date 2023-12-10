#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>
#include <pybind11/numpy.h>

#include <MimeType.h>
#include <Mime.h>
#include <Bitmap.h>

namespace py = pybind11;
using namespace BPrivate;
using namespace BPrivate::Storage;
using namespace BPrivate::Storage::Mime;

PYBIND11_MODULE(MimeType, m)
{
py::enum_<app_verb>(m, "app_verb", "")
.value("B_OPEN", app_verb::B_OPEN, "")
.export_values();

m.attr("B_META_MIME_CHANGED") = 'MMCH';

m.attr("B_ICON_CHANGED") = 0x00000001;
m.attr("B_PREFERRED_APP_CHANGED") = 0x00000002;
m.attr("B_ATTR_INFO_CHANGED") = 0x00000004;
m.attr("B_FILE_EXTENSIONS_CHANGED") = 0x00000008;
m.attr("B_SHORT_DESCRIPTION_CHANGED") = 0x00000010;
m.attr("B_LONG_DESCRIPTION_CHANGED") = 0x00000020;
m.attr("B_ICON_FOR_TYPE_CHANGED") = 0x00000040;
m.attr("B_APP_HINT_CHANGED") = 0x00000080;
m.attr("B_MIME_TYPE_CREATED") = 0x00000100;
m.attr("B_MIME_TYPE_DELETED") = 0x00000200;
m.attr("B_SNIFFER_RULE_CHANGED") = 0x00000400;
m.attr("B_SUPPORTED_TYPES_CHANGED") = 0x00000800;
m.attr("B_EVERYTHING_CHANGED") = (int)0xFFFFFFFF;

m.attr("B_META_MIME_MODIFIED") = 'MMMD';
m.attr("B_META_MIME_DELETED") = 'MMDL';

//m.attr("MimeDatabase") = py::cast(BPrivate::MimeDatabase);

//m.attr("CreateAppMetaMimeThread") = py::cast(CreateAppMetaMimeThread);

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
.def("IsValid", py::overload_cast<>(&BMimeType::IsValid, py::const_), "")
.def("IsSupertypeOnly", &BMimeType::IsSupertypeOnly, "")
.def("GetSupertype", &BMimeType::GetSupertype, "", py::arg("supertype"))
.def("__eq__", py::overload_cast<const BMimeType &>(&BMimeType::operator==, py::const_), "", py::arg("type"))
.def("__eq__", py::overload_cast<const char *>(&BMimeType::operator==, py::const_), "", py::arg("type"))
.def("Contains", &BMimeType::Contains, "", py::arg("type"))
.def("Install", &BMimeType::Install, "")
.def("Delete", &BMimeType::Delete, "")
.def("IsInstalled", &BMimeType::IsInstalled, "")
//.def("GetIcon_toBitmap", py::overload_cast<BBitmap *, icon_size>(&BMimeType::GetIcon, py::const_), "", py::arg("icon"), py::arg("size")) //changed names to GetIcon
.def("GetIcon", [](const BMimeType &self, icon_size size) {
            BBitmap *icon;
            // Chiamata alla funzione C++
            if(size==B_LARGE_ICON){
            	icon = new BBitmap(BRect(0, 0, 31, 31), B_RGBA32);
            } else {
            	icon = new BBitmap(BRect(0, 0, 15, 15), B_RGBA32);
            }
            status_t result = self.GetIcon(icon, size);

            // Restituisci una tupla contenente il risultato e l'oggetto BBitmap
            return std::make_tuple(result, icon);
        }, "", py::arg("size")=B_LARGE_ICON)
//.def("GetIcon", py::overload_cast<unsigned char, size_t *>(&BMimeType::GetIcon, py::const_), "", py::arg("_data"), py::arg("_size"))
.def("GetIcon", [](const BMimeType &self) {
            uint8 *data = nullptr;
            size_t size = 0;
            
            // Chiamata alla funzione C++
            status_t result = self.GetIcon(&data, &size);

            // Creazione di un array NumPy dalla memoria ottenuta
            auto capsule = py::capsule(data, [](void *d) {
                // Implementa la logica per deallocare la memoria
                // In questo esempio, si presume che la memoria sia stata allocata con new[]
                delete[] static_cast<uint8 *>(d);
            });

            return std::make_tuple(result, py::array_t<uint8>({static_cast<ssize_t>(size)}, {sizeof(uint8)}, data, capsule));
}, "")
.def("GetPreferredApp", &BMimeType::GetPreferredApp, "", py::arg("signature"), py::arg("verb")=B_OPEN)
.def("GetAttrInfo", &BMimeType::GetAttrInfo, "", py::arg("info"))
.def("GetFileExtensions", &BMimeType::GetFileExtensions, "", py::arg("extensions"))
.def("GetShortDescription", &BMimeType::GetShortDescription, "", py::arg("description"))
.def("GetLongDescription", &BMimeType::GetLongDescription, "", py::arg("description"))
.def("GetSupportingApps", &BMimeType::GetSupportingApps, "", py::arg("signatures"))
.def("SetIcon", py::overload_cast<const BBitmap *, icon_size>(&BMimeType::SetIcon), "", py::arg("icon"), py::arg("size"))
.def("SetIcon", py::overload_cast<const uint8*, size_t>(&BMimeType::SetIcon), "", py::arg("data"), py::arg("size"))
.def("SetPreferredApp", &BMimeType::SetPreferredApp, "", py::arg("signature"), py::arg("verb")=B_OPEN)
.def("SetAttrInfo", &BMimeType::SetAttrInfo, "", py::arg("info"))
.def("SetFileExtensions", &BMimeType::SetFileExtensions, "", py::arg("extensions"))
.def("SetShortDescription", &BMimeType::SetShortDescription, "", py::arg("description"))
.def("SetLongDescription", &BMimeType::SetLongDescription, "", py::arg("description"))
.def_static("GetInstalledSupertypes", &BMimeType::GetInstalledSupertypes, "", py::arg("supertypes"))
.def_static("GetInstalledTypes", py::overload_cast<BMessage *>(&BMimeType::GetInstalledTypes), "", py::arg("types"))
.def_static("GetInstalledTypes", py::overload_cast<const char *, BMessage *>(&BMimeType::GetInstalledTypes), "", py::arg("supertype"), py::arg("subtypes"))
.def_static("GetWildcardApps", &BMimeType::GetWildcardApps, "", py::arg("wildcardApps"))
.def_static("IsValid_static", py::overload_cast<const char *>(&BMimeType::IsValid), "", py::arg("mimeType"))
.def("GetAppHint", &BMimeType::GetAppHint, "", py::arg("ref"))
.def("SetAppHint", &BMimeType::SetAppHint, "", py::arg("ref"))
//.def("GetIconForType", py::overload_cast<const char *, BBitmap *, icon_size>(&BMimeType::GetIconForType, py::const_), "", py::arg("type"), py::arg("icon"), py::arg("which"))
.def("GetIconForType", [](const BMimeType &self, const char *type, icon_size size) {
            BBitmap *icon;
            // Chiamata alla funzione C++
            if(size==B_LARGE_ICON){
            	icon = new BBitmap(BRect(0, 0, 31, 31), B_RGBA32);
            } else {
            	icon = new BBitmap(BRect(0, 0, 15, 15), B_RGBA32);
            }
            status_t result = self.GetIconForType(type, icon, size);

            // Restituisci una tupla contenente il risultato e l'oggetto BBitmap
            return std::make_tuple(result, icon);
        }, "", py::arg("type"), py::arg("size")=B_LARGE_ICON)
//.def("GetIconForType", py::overload_cast<const char *, unsigned char, size_t *>(&BMimeType::GetIconForType, py::const_), "", py::arg("type"), py::arg("_data"), py::arg("_size"))
.def("GetIconForType", [](const BMimeType &self, const char *type) {
            size_t size;
            uint8_t *data;
            status_t result = self.GetIconForType(type, &data, &size);
            auto capsule = py::capsule(data, [](void *d) {
                delete[] static_cast<uint8_t *>(d);
            });

            return std::make_tuple(result, py::array_t<uint8_t>({static_cast<ssize_t>(size)}, {sizeof(uint8_t)}, data, capsule));
        }, "",py::arg("type"))
.def("SetIconForType", py::overload_cast<const char *, const BBitmap *, icon_size>(&BMimeType::SetIconForType), "", py::arg("type"), py::arg("icon"), py::arg("which"))
.def("SetIconForType", py::overload_cast<const char *, const uint8*, size_t>(&BMimeType::SetIconForType), "", py::arg("type"), py::arg("data"), py::arg("size"))
.def("GetSnifferRule", &BMimeType::GetSnifferRule, "", py::arg("result"))
.def("SetSnifferRule", &BMimeType::SetSnifferRule, "", py::arg(""))
.def_static("CheckSnifferRule", &BMimeType::CheckSnifferRule, "", py::arg("rule"), py::arg("parseError"))
.def_static("GuessMimeType", py::overload_cast<const entry_ref *, BMimeType *>(&BMimeType::GuessMimeType), "", py::arg("file"), py::arg("type"))
.def_static("GuessMimeType", py::overload_cast<const void *, int32, BMimeType *>(&BMimeType::GuessMimeType), "", py::arg("buffer"), py::arg("length"), py::arg("type"))
.def_static("GuessMimeType", py::overload_cast<const char *, BMimeType *>(&BMimeType::GuessMimeType), "", py::arg("filename"), py::arg("type"))
.def_static("StartWatching", &BMimeType::StartWatching, "", py::arg("target"))
.def_static("StopWatching", &BMimeType::StopWatching, "", py::arg("target"))
.def("SetType", &BMimeType::SetType, "", py::arg("mimeType"))
;


}
