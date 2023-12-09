#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>
#include <pybind11/numpy.h>

#include <Mime.h>
#include <Bitmap.h>

namespace py = pybind11;
/*
std::tuple<status_t,py::array_t<uint8>> get_device_icon_py(const char *device) {
    uint8 *data = nullptr;
    size_t size = 0;
    type_code type = B_MINI_ICON_TYPE;  // default value

    // Chiamata alla funzione C++
    status_t result = get_device_icon(device, &data, &size, &type);

    //if (result != B_OK) {
    //    // Gestisci l'errore in qualche modo
    //    throw std::runtime_error("Errore nella funzione get_device_icon");
    //}

    // Creazione di un array NumPy dalla memoria ottenuta
    auto capsule = py::capsule(data, [](void *d) {
        // Implementa la logica per deallocare la memoria
        // In questo esempio, si presume che la memoria sia stata allocata con new[]
        delete[] static_cast<uint8 *>(d);
    });

    return std::make_tuple(result,py::array_t<uint8>({static_cast<ssize_t>(size)}, {sizeof(uint8)}, data, capsule));
}*/

PYBIND11_MODULE(Mime, m)
{
py::enum_<icon_size>(m, "icon_size", "")
.value("B_LARGE_ICON", icon_size::B_LARGE_ICON, "")
.value("B_MINI_ICON", icon_size::B_MINI_ICON, "")
.export_values();

m.attr("B_UPDATE_MIME_INFO_NO_FORCE") = 0; //hardcoded, not reading enum
m.attr("B_UPDATE_MIME_INFO_FORCE_KEEP_TYPE") = 1; //hardcoded, not reading enum
m.attr("B_UPDATE_MIME_INFO_FORCE_UPDATE_ALL") = 2; //hardcoded, not reading enum

//m.attr("BBitmap") = py::cast(BBitmap);

m.def("update_mime_info", &update_mime_info, "", py::arg("path"), py::arg("recursive"), py::arg("synchronous"), py::arg("force"));

m.def("create_app_meta_mime", &create_app_meta_mime, "", py::arg("path"), py::arg("recursive"), py::arg("synchronous"), py::arg("force"));

m.def("get_device_icon_toVoid", py::overload_cast<const char *, void *, int32>(&get_device_icon), "", py::arg("device"), py::arg("icon"), py::arg("size"));

m.def("get_device_icon_toBitmap", py::overload_cast<const char *, BBitmap *, icon_size>(&get_device_icon), "", py::arg("device"), py::arg("icon"), py::arg("which"));

//m.def("get_device_icon", py::overload_cast<const char *, unsigned char, size_t *, type_code *>(&get_device_icon), "", py::arg("device"), py::arg("_data"), py::arg("_size"), py::arg("_type"));
m.def("get_device_icon_toArray", [](const char * device){
 	uint8 *data = nullptr;
    size_t size = 0;
    type_code type = B_MINI_ICON_TYPE;  // default value
	status_t result = get_device_icon(device, &data, &size, &type);
	auto capsule = py::capsule(data, [](void *d) {
        // Implementa la logica per deallocare la memoria
        // In questo esempio, si presume che la memoria sia stata allocata con new[]
        delete[] static_cast<uint8 *>(d);
    });

    return std::make_tuple(result,py::array_t<uint8>({static_cast<ssize_t>(size)}, {sizeof(uint8)}, data, capsule));
 }, "", py::arg("device"));
// unsigned char ->uint8**
m.def("get_named_icon_toBitmap", py::overload_cast<const char *, BBitmap *, icon_size>(&get_named_icon), "", py::arg("name"), py::arg("icon"), py::arg("which"));

//m.def("get_named_icon", py::overload_cast<const char *, unsigned char, size_t *, type_code *>(&get_named_icon), "", py::arg("name"), py::arg("_data"), py::arg("_size"), py::arg("_type"));
// unsigned char ->uint8**
m.def("get_named_icon_toArray", [](const char *name, unsigned char iconSize, size_t *size, type_code *iconType) {
    uint8 *data = nullptr;
    status_t result = get_named_icon(name, &data, size, iconType);

    auto capsule = py::capsule(data, [](void *d) {
        // Implementa la logica per deallocare la memoria, se necessario
        // In questo esempio, si presume che la memoria sia stata allocata con new[]
        delete[] static_cast<uint8 *>(d);
    });

    return std::make_tuple(result, py::array_t<uint8>({static_cast<ssize_t>(*size)}, {sizeof(uint8)}, data, capsule));
}, "", py::arg("name"), py::arg("iconSize"), py::arg("size"), py::arg("iconType"));
}
