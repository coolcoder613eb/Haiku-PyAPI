#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <FindDirectory.h>

namespace py = pybind11;


void define_FindDirectory(py::module_& m)
{
py::enum_<directory_which>(m, "directory_which", "")
.value("B_DESKTOP_DIRECTORY", directory_which::B_DESKTOP_DIRECTORY, "")
.value("B_TRASH_DIRECTORY", directory_which::B_TRASH_DIRECTORY, "")
.value("B_SYSTEM_DIRECTORY", directory_which::B_SYSTEM_DIRECTORY, "")
.value("B_SYSTEM_ADDONS_DIRECTORY", directory_which::B_SYSTEM_ADDONS_DIRECTORY, "")
.value("B_SYSTEM_BOOT_DIRECTORY", directory_which::B_SYSTEM_BOOT_DIRECTORY, "")
.value("B_SYSTEM_FONTS_DIRECTORY", directory_which::B_SYSTEM_FONTS_DIRECTORY, "")
.value("B_SYSTEM_LIB_DIRECTORY", directory_which::B_SYSTEM_LIB_DIRECTORY, "")
.value("B_SYSTEM_SERVERS_DIRECTORY", directory_which::B_SYSTEM_SERVERS_DIRECTORY, "")
.value("B_SYSTEM_APPS_DIRECTORY", directory_which::B_SYSTEM_APPS_DIRECTORY, "")
.value("B_SYSTEM_BIN_DIRECTORY", directory_which::B_SYSTEM_BIN_DIRECTORY, "")
.value("B_SYSTEM_DOCUMENTATION_DIRECTORY", directory_which::B_SYSTEM_DOCUMENTATION_DIRECTORY, "")
.value("B_SYSTEM_PREFERENCES_DIRECTORY", directory_which::B_SYSTEM_PREFERENCES_DIRECTORY, "")
.value("B_SYSTEM_TRANSLATORS_DIRECTORY", directory_which::B_SYSTEM_TRANSLATORS_DIRECTORY, "")
.value("B_SYSTEM_MEDIA_NODES_DIRECTORY", directory_which::B_SYSTEM_MEDIA_NODES_DIRECTORY, "")
.value("B_SYSTEM_SOUNDS_DIRECTORY", directory_which::B_SYSTEM_SOUNDS_DIRECTORY, "")
.value("B_SYSTEM_DATA_DIRECTORY", directory_which::B_SYSTEM_DATA_DIRECTORY, "")
.value("B_SYSTEM_DEVELOP_DIRECTORY", directory_which::B_SYSTEM_DEVELOP_DIRECTORY, "")
.value("B_SYSTEM_PACKAGES_DIRECTORY", directory_which::B_SYSTEM_PACKAGES_DIRECTORY, "")
.value("B_SYSTEM_HEADERS_DIRECTORY", directory_which::B_SYSTEM_HEADERS_DIRECTORY, "")
.value("B_SYSTEM_ETC_DIRECTORY", directory_which::B_SYSTEM_ETC_DIRECTORY, "")
.value("B_SYSTEM_SETTINGS_DIRECTORY", directory_which::B_SYSTEM_SETTINGS_DIRECTORY, "")
.value("B_SYSTEM_LOG_DIRECTORY", directory_which::B_SYSTEM_LOG_DIRECTORY, "")
.value("B_SYSTEM_SPOOL_DIRECTORY", directory_which::B_SYSTEM_SPOOL_DIRECTORY, "")
.value("B_SYSTEM_TEMP_DIRECTORY", directory_which::B_SYSTEM_TEMP_DIRECTORY, "")
.value("B_SYSTEM_VAR_DIRECTORY", directory_which::B_SYSTEM_VAR_DIRECTORY, "")
.value("B_SYSTEM_CACHE_DIRECTORY", directory_which::B_SYSTEM_CACHE_DIRECTORY, "")
.value("B_SYSTEM_NONPACKAGED_DIRECTORY", directory_which::B_SYSTEM_NONPACKAGED_DIRECTORY, "")
.value("B_SYSTEM_NONPACKAGED_ADDONS_DIRECTORY", directory_which::B_SYSTEM_NONPACKAGED_ADDONS_DIRECTORY, "")
.value("B_SYSTEM_NONPACKAGED_TRANSLATORS_DIRECTORY", directory_which::B_SYSTEM_NONPACKAGED_TRANSLATORS_DIRECTORY, "")
.value("B_SYSTEM_NONPACKAGED_MEDIA_NODES_DIRECTORY", directory_which::B_SYSTEM_NONPACKAGED_MEDIA_NODES_DIRECTORY, "")
.value("B_SYSTEM_NONPACKAGED_BIN_DIRECTORY", directory_which::B_SYSTEM_NONPACKAGED_BIN_DIRECTORY, "")
.value("B_SYSTEM_NONPACKAGED_DATA_DIRECTORY", directory_which::B_SYSTEM_NONPACKAGED_DATA_DIRECTORY, "")
.value("B_SYSTEM_NONPACKAGED_FONTS_DIRECTORY", directory_which::B_SYSTEM_NONPACKAGED_FONTS_DIRECTORY, "")
.value("B_SYSTEM_NONPACKAGED_SOUNDS_DIRECTORY", directory_which::B_SYSTEM_NONPACKAGED_SOUNDS_DIRECTORY, "")
.value("B_SYSTEM_NONPACKAGED_DOCUMENTATION_DIRECTORY", directory_which::B_SYSTEM_NONPACKAGED_DOCUMENTATION_DIRECTORY, "")
.value("B_SYSTEM_NONPACKAGED_LIB_DIRECTORY", directory_which::B_SYSTEM_NONPACKAGED_LIB_DIRECTORY, "")
.value("B_SYSTEM_NONPACKAGED_HEADERS_DIRECTORY", directory_which::B_SYSTEM_NONPACKAGED_HEADERS_DIRECTORY, "")
.value("B_SYSTEM_NONPACKAGED_DEVELOP_DIRECTORY", directory_which::B_SYSTEM_NONPACKAGED_DEVELOP_DIRECTORY, "")
.value("B_USER_DIRECTORY", directory_which::B_USER_DIRECTORY, "")
.value("B_USER_CONFIG_DIRECTORY", directory_which::B_USER_CONFIG_DIRECTORY, "")
.value("B_USER_ADDONS_DIRECTORY", directory_which::B_USER_ADDONS_DIRECTORY, "")
.value("B_USER_BOOT_DIRECTORY", directory_which::B_USER_BOOT_DIRECTORY, "")
.value("B_USER_FONTS_DIRECTORY", directory_which::B_USER_FONTS_DIRECTORY, "")
.value("B_USER_LIB_DIRECTORY", directory_which::B_USER_LIB_DIRECTORY, "")
.value("B_USER_SETTINGS_DIRECTORY", directory_which::B_USER_SETTINGS_DIRECTORY, "")
.value("B_USER_DESKBAR_DIRECTORY", directory_which::B_USER_DESKBAR_DIRECTORY, "")
.value("B_USER_PRINTERS_DIRECTORY", directory_which::B_USER_PRINTERS_DIRECTORY, "")
.value("B_USER_TRANSLATORS_DIRECTORY", directory_which::B_USER_TRANSLATORS_DIRECTORY, "")
.value("B_USER_MEDIA_NODES_DIRECTORY", directory_which::B_USER_MEDIA_NODES_DIRECTORY, "")
.value("B_USER_SOUNDS_DIRECTORY", directory_which::B_USER_SOUNDS_DIRECTORY, "")
.value("B_USER_DATA_DIRECTORY", directory_which::B_USER_DATA_DIRECTORY, "")
.value("B_USER_CACHE_DIRECTORY", directory_which::B_USER_CACHE_DIRECTORY, "")
.value("B_USER_PACKAGES_DIRECTORY", directory_which::B_USER_PACKAGES_DIRECTORY, "")
.value("B_USER_HEADERS_DIRECTORY", directory_which::B_USER_HEADERS_DIRECTORY, "")
.value("B_USER_NONPACKAGED_DIRECTORY", directory_which::B_USER_NONPACKAGED_DIRECTORY, "")
.value("B_USER_NONPACKAGED_ADDONS_DIRECTORY", directory_which::B_USER_NONPACKAGED_ADDONS_DIRECTORY, "")
.value("B_USER_NONPACKAGED_TRANSLATORS_DIRECTORY", directory_which::B_USER_NONPACKAGED_TRANSLATORS_DIRECTORY, "")
.value("B_USER_NONPACKAGED_MEDIA_NODES_DIRECTORY", directory_which::B_USER_NONPACKAGED_MEDIA_NODES_DIRECTORY, "")
.value("B_USER_NONPACKAGED_BIN_DIRECTORY", directory_which::B_USER_NONPACKAGED_BIN_DIRECTORY, "")
.value("B_USER_NONPACKAGED_DATA_DIRECTORY", directory_which::B_USER_NONPACKAGED_DATA_DIRECTORY, "")
.value("B_USER_NONPACKAGED_FONTS_DIRECTORY", directory_which::B_USER_NONPACKAGED_FONTS_DIRECTORY, "")
.value("B_USER_NONPACKAGED_SOUNDS_DIRECTORY", directory_which::B_USER_NONPACKAGED_SOUNDS_DIRECTORY, "")
.value("B_USER_NONPACKAGED_DOCUMENTATION_DIRECTORY", directory_which::B_USER_NONPACKAGED_DOCUMENTATION_DIRECTORY, "")
.value("B_USER_NONPACKAGED_LIB_DIRECTORY", directory_which::B_USER_NONPACKAGED_LIB_DIRECTORY, "")
.value("B_USER_NONPACKAGED_HEADERS_DIRECTORY", directory_which::B_USER_NONPACKAGED_HEADERS_DIRECTORY, "")
.value("B_USER_NONPACKAGED_DEVELOP_DIRECTORY", directory_which::B_USER_NONPACKAGED_DEVELOP_DIRECTORY, "")
.value("B_USER_DEVELOP_DIRECTORY", directory_which::B_USER_DEVELOP_DIRECTORY, "")
.value("B_USER_DOCUMENTATION_DIRECTORY", directory_which::B_USER_DOCUMENTATION_DIRECTORY, "")
.value("B_USER_SERVERS_DIRECTORY", directory_which::B_USER_SERVERS_DIRECTORY, "")
.value("B_USER_APPS_DIRECTORY", directory_which::B_USER_APPS_DIRECTORY, "")
.value("B_USER_BIN_DIRECTORY", directory_which::B_USER_BIN_DIRECTORY, "")
.value("B_USER_PREFERENCES_DIRECTORY", directory_which::B_USER_PREFERENCES_DIRECTORY, "")
.value("B_USER_ETC_DIRECTORY", directory_which::B_USER_ETC_DIRECTORY, "")
.value("B_USER_LOG_DIRECTORY", directory_which::B_USER_LOG_DIRECTORY, "")
.value("B_USER_SPOOL_DIRECTORY", directory_which::B_USER_SPOOL_DIRECTORY, "")
.value("B_USER_VAR_DIRECTORY", directory_which::B_USER_VAR_DIRECTORY, "")
.value("B_APPS_DIRECTORY", directory_which::B_APPS_DIRECTORY, "")
.value("B_PREFERENCES_DIRECTORY", directory_which::B_PREFERENCES_DIRECTORY, "")
.value("B_UTILITIES_DIRECTORY", directory_which::B_UTILITIES_DIRECTORY, "")
.value("B_PACKAGE_LINKS_DIRECTORY", directory_which::B_PACKAGE_LINKS_DIRECTORY, "")
.value("B_BEOS_DIRECTORY", directory_which::B_BEOS_DIRECTORY, "")
.value("B_BEOS_SYSTEM_DIRECTORY", directory_which::B_BEOS_SYSTEM_DIRECTORY, "")
.value("B_BEOS_ADDONS_DIRECTORY", directory_which::B_BEOS_ADDONS_DIRECTORY, "")
.value("B_BEOS_BOOT_DIRECTORY", directory_which::B_BEOS_BOOT_DIRECTORY, "")
.value("B_BEOS_FONTS_DIRECTORY", directory_which::B_BEOS_FONTS_DIRECTORY, "")
.value("B_BEOS_LIB_DIRECTORY", directory_which::B_BEOS_LIB_DIRECTORY, "")
.value("B_BEOS_SERVERS_DIRECTORY", directory_which::B_BEOS_SERVERS_DIRECTORY, "")
.value("B_BEOS_APPS_DIRECTORY", directory_which::B_BEOS_APPS_DIRECTORY, "")
.value("B_BEOS_BIN_DIRECTORY", directory_which::B_BEOS_BIN_DIRECTORY, "")
.value("B_BEOS_ETC_DIRECTORY", directory_which::B_BEOS_ETC_DIRECTORY, "")
.value("B_BEOS_DOCUMENTATION_DIRECTORY", directory_which::B_BEOS_DOCUMENTATION_DIRECTORY, "")
.value("B_BEOS_PREFERENCES_DIRECTORY", directory_which::B_BEOS_PREFERENCES_DIRECTORY, "")
.value("B_BEOS_TRANSLATORS_DIRECTORY", directory_which::B_BEOS_TRANSLATORS_DIRECTORY, "")
.value("B_BEOS_MEDIA_NODES_DIRECTORY", directory_which::B_BEOS_MEDIA_NODES_DIRECTORY, "")
.value("B_BEOS_SOUNDS_DIRECTORY", directory_which::B_BEOS_SOUNDS_DIRECTORY, "")
.export_values();

m.attr("B_FIND_PATH_CREATE_DIRECTORY") = py::cast(B_FIND_PATH_CREATE_DIRECTORY);
m.attr("B_FIND_PATH_CREATE_PARENT_DIRECTORY") = py::cast(B_FIND_PATH_CREATE_PARENT_DIRECTORY);
m.attr("B_FIND_PATH_EXISTING_ONLY") = py::cast(B_FIND_PATH_EXISTING_ONLY);
m.attr("B_FIND_PATHS_SYSTEM_ONLY") = py::cast(B_FIND_PATHS_SYSTEM_ONLY);
m.attr("B_FIND_PATHS_USER_ONLY") = py::cast(B_FIND_PATHS_USER_ONLY);

py::enum_<path_base_directory>(m, "path_base_directory", "")
.value("B_FIND_PATH_INSTALLATION_LOCATION_DIRECTORY", path_base_directory::B_FIND_PATH_INSTALLATION_LOCATION_DIRECTORY, "")
.value("B_FIND_PATH_ADD_ONS_DIRECTORY", path_base_directory::B_FIND_PATH_ADD_ONS_DIRECTORY, "")
.value("B_FIND_PATH_APPS_DIRECTORY", path_base_directory::B_FIND_PATH_APPS_DIRECTORY, "")
.value("B_FIND_PATH_BIN_DIRECTORY", path_base_directory::B_FIND_PATH_BIN_DIRECTORY, "")
.value("B_FIND_PATH_BOOT_DIRECTORY", path_base_directory::B_FIND_PATH_BOOT_DIRECTORY, "")
.value("B_FIND_PATH_CACHE_DIRECTORY", path_base_directory::B_FIND_PATH_CACHE_DIRECTORY, "")
.value("B_FIND_PATH_DATA_DIRECTORY", path_base_directory::B_FIND_PATH_DATA_DIRECTORY, "")
.value("B_FIND_PATH_DEVELOP_DIRECTORY", path_base_directory::B_FIND_PATH_DEVELOP_DIRECTORY, "")
.value("B_FIND_PATH_DEVELOP_LIB_DIRECTORY", path_base_directory::B_FIND_PATH_DEVELOP_LIB_DIRECTORY, "")
.value("B_FIND_PATH_DOCUMENTATION_DIRECTORY", path_base_directory::B_FIND_PATH_DOCUMENTATION_DIRECTORY, "")
.value("B_FIND_PATH_ETC_DIRECTORY", path_base_directory::B_FIND_PATH_ETC_DIRECTORY, "")
.value("B_FIND_PATH_FONTS_DIRECTORY", path_base_directory::B_FIND_PATH_FONTS_DIRECTORY, "")
.value("B_FIND_PATH_HEADERS_DIRECTORY", path_base_directory::B_FIND_PATH_HEADERS_DIRECTORY, "")
.value("B_FIND_PATH_LIB_DIRECTORY", path_base_directory::B_FIND_PATH_LIB_DIRECTORY, "")
.value("B_FIND_PATH_LOG_DIRECTORY", path_base_directory::B_FIND_PATH_LOG_DIRECTORY, "")
.value("B_FIND_PATH_MEDIA_NODES_DIRECTORY", path_base_directory::B_FIND_PATH_MEDIA_NODES_DIRECTORY, "")
.value("B_FIND_PATH_PACKAGES_DIRECTORY", path_base_directory::B_FIND_PATH_PACKAGES_DIRECTORY, "")
.value("B_FIND_PATH_PREFERENCES_DIRECTORY", path_base_directory::B_FIND_PATH_PREFERENCES_DIRECTORY, "")
.value("B_FIND_PATH_SERVERS_DIRECTORY", path_base_directory::B_FIND_PATH_SERVERS_DIRECTORY, "")
.value("B_FIND_PATH_SETTINGS_DIRECTORY", path_base_directory::B_FIND_PATH_SETTINGS_DIRECTORY, "")
.value("B_FIND_PATH_SOUNDS_DIRECTORY", path_base_directory::B_FIND_PATH_SOUNDS_DIRECTORY, "")
.value("B_FIND_PATH_SPOOL_DIRECTORY", path_base_directory::B_FIND_PATH_SPOOL_DIRECTORY, "")
.value("B_FIND_PATH_TRANSLATORS_DIRECTORY", path_base_directory::B_FIND_PATH_TRANSLATORS_DIRECTORY, "")
.value("B_FIND_PATH_VAR_DIRECTORY", path_base_directory::B_FIND_PATH_VAR_DIRECTORY, "")
.value("B_FIND_PATH_IMAGE_PATH", path_base_directory::B_FIND_PATH_IMAGE_PATH, "")
.value("B_FIND_PATH_PACKAGE_PATH", path_base_directory::B_FIND_PATH_PACKAGE_PATH, "")
.export_values();

m.attr("BVolume") = py::cast(BVolume);

m.def("find_directory", py::overload_cast<directory_which, dev_t, bool, char *, int>(&find_directory), "", py::arg("which"), py::arg("volume"), py::arg("createIt"), py::arg("pathString"), py::arg("length"));

m.def("find_path", &find_path, "", py::arg("codePointer"), py::arg("baseDirectory"), py::arg("subPath"), py::arg("pathBuffer"), py::arg("bufferSize"));

m.def("find_path_etc", &find_path_etc, "", py::arg("codePointer"), py::arg("dependency"), py::arg("architecture"), py::arg("baseDirectory"), py::arg("subPath"), py::arg("flags"), py::arg("pathBuffer"), py::arg("bufferSize"));

m.def("find_path_for_path", &find_path_for_path, "", py::arg("path"), py::arg("baseDirectory"), py::arg("subPath"), py::arg("pathBuffer"), py::arg("bufferSize"));

m.def("find_path_for_path_etc", &find_path_for_path_etc, "", py::arg("path"), py::arg("dependency"), py::arg("architecture"), py::arg("baseDirectory"), py::arg("subPath"), py::arg("flags"), py::arg("pathBuffer"), py::arg("bufferSize"));

m.def("find_paths", &find_paths, "", py::arg("baseDirectory"), py::arg("subPath"), py::arg("_paths"), py::arg("_pathCount"));

m.def("find_paths_etc", &find_paths_etc, "", py::arg("architecture"), py::arg("baseDirectory"), py::arg("subPath"), py::arg("flags"), py::arg("_paths"), py::arg("_pathCount"));

m.def("find_directory", py::overload_cast<directory_which, BPath *, bool, BVolume *>(&find_directory), "", py::arg("which"), py::arg("path"), py::arg("createIt")=false, py::arg("volume")=NULL);

}
