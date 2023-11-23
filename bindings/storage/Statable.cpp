#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <Statable.h>

namespace py = pybind11;
using namespace BPrivate;
using namespace BPrivate::Storage;
using namespace BPrivate::Storage::Mime;
using namespace BPackageKit;

void define_Statable(py::module_& m)
{
py::class_<BStatable>(m, "BStatable")
.def("GetStat", &BStatable::GetStat, "", py::arg("stat"))
.def("IsFile", &BStatable::IsFile, "")
.def("IsDirectory", &BStatable::IsDirectory, "")
.def("IsSymLink", &BStatable::IsSymLink, "")
.def("GetNodeRef", &BStatable::GetNodeRef, "", py::arg("ref"))
.def("GetOwner", &BStatable::GetOwner, "", py::arg("owner"))
.def("SetOwner", &BStatable::SetOwner, "", py::arg("owner"))
.def("GetGroup", &BStatable::GetGroup, "", py::arg("group"))
.def("SetGroup", &BStatable::SetGroup, "", py::arg("group"))
.def("GetPermissions", &BStatable::GetPermissions, "", py::arg("permissions"))
.def("SetPermissions", &BStatable::SetPermissions, "", py::arg("permissions"))
.def("GetSize", &BStatable::GetSize, "", py::arg("size"))
.def("GetModificationTime", &BStatable::GetModificationTime, "", py::arg("mtime"))
.def("SetModificationTime", &BStatable::SetModificationTime, "", py::arg("mtime"))
.def("GetCreationTime", &BStatable::GetCreationTime, "", py::arg("ctime"))
.def("SetCreationTime", &BStatable::SetCreationTime, "", py::arg("ctime"))
.def("GetAccessTime", &BStatable::GetAccessTime, "", py::arg("atime"))
.def("SetAccessTime", &BStatable::SetAccessTime, "", py::arg("atime"))
.def("GetVolume", &BStatable::GetVolume, "", py::arg("volume"))
.def_readwrite("Private", &BStatable::Private, "")
;


}
