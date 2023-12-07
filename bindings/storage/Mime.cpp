#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <Mime.h>
#include <Bitmap.h>

namespace py = pybind11;


PYBIND11_MODULE(Mime, m)
{
py::enum_<icon_size>(m, "icon_size", "")
.value("B_LARGE_ICON", icon_size::B_LARGE_ICON, "")
.value("B_MINI_ICON", icon_size::B_MINI_ICON, "")
.export_values();

m.attr("B_UPDATE_MIME_INFO_NO_FORCE") = 0; //hardcoded, not reading enum
m.attr("B_UPDATE_MIME_INFO_FORCE_KEEP_TYPE") = 1;
m.attr("B_UPDATE_MIME_INFO_FORCE_UPDATE_ALL") = 2;

//m.attr("BBitmap") = py::cast(BBitmap);

m.def("update_mime_info", &update_mime_info, "", py::arg("path"), py::arg("recursive"), py::arg("synchronous"), py::arg("force"));

m.def("create_app_meta_mime", &create_app_meta_mime, "", py::arg("path"), py::arg("recursive"), py::arg("synchronous"), py::arg("force"));

m.def("get_device_icon", py::overload_cast<const char *, void *, int32>(&get_device_icon), "", py::arg("device"), py::arg("icon"), py::arg("size"));

m.def("get_device_icon", py::overload_cast<const char *, BBitmap *, icon_size>(&get_device_icon), "", py::arg("device"), py::arg("icon"), py::arg("which"));

//m.def("get_device_icon", py::overload_cast<const char *, unsigned char, size_t *, type_code *>(&get_device_icon), "", py::arg("device"), py::arg("_data"), py::arg("_size"), py::arg("_type"));
// unsigned char ->uint8**
m.def("get_named_icon", py::overload_cast<const char *, BBitmap *, icon_size>(&get_named_icon), "", py::arg("name"), py::arg("icon"), py::arg("which"));

//m.def("get_named_icon", py::overload_cast<const char *, unsigned char, size_t *, type_code *>(&get_named_icon), "", py::arg("name"), py::arg("_data"), py::arg("_size"), py::arg("_type"));
// unsigned char ->uint8**
}
