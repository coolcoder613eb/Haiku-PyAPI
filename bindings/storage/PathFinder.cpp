#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <PathFinder.h>
#include <FindDirectory.h>
#include <package/PackageResolvableExpression.h>
#include <Path.h>

namespace py = pybind11;
//using namespace BPrivate;
//using namespace BPrivate::Storage;
//using namespace BPrivate::Storage::Mime;
//using namespace BPackageKit;

PYBIND11_MODULE(PathFinder, m)
{
//m.attr("BPackageResolvableExpression") = py::cast(BPackageResolvableExpression);

py::class_<BPathFinder>(m, "BPathFinder")
.def(py::init<const void *, const char *>(), "", py::arg("codePointer")=NULL, py::arg("dependency")=NULL)
.def(py::init<const char *, const char *>(), "", py::arg("path"), py::arg("dependency")=NULL)
.def(py::init<const entry_ref &, const char *>(), "", py::arg("ref"), py::arg("dependency")=NULL)
//.def(py::init<const BPackageKit::BPackageResolvableExpression &, const char *>(), "", py::arg("expression"), py::arg("dependency")=NULL) //BResolvableExpression
.def("SetTo", py::overload_cast<const void *, const char *>(&BPathFinder::SetTo), "", py::arg("codePointer")=NULL, py::arg("dependency")=NULL)
.def("SetTo", py::overload_cast<const char *, const char *>(&BPathFinder::SetTo), "", py::arg("path"), py::arg("dependency")=NULL)
.def("SetTo", py::overload_cast<const entry_ref &, const char *>(&BPathFinder::SetTo), "", py::arg("ref"), py::arg("dependency")=NULL)
//.def("SetTo", py::overload_cast<const BPackageKit::BPackageResolvableExpression &, const char *>(&BPathFinder::SetTo), "", py::arg("expression"), py::arg("dependency")=NULL) //BResolvableExpression
.def("FindPath", [](BPathFinder& self,const char * architecture,path_base_directory baseDirectory,const char * subPath,unsigned int flags) {
    BPath  _path;
    status_t r = self.FindPath(architecture, baseDirectory, subPath, flags, _path);
    return std::make_tuple(r,_path);
}
, "", py::arg("architecture"), py::arg("baseDirectory"), py::arg("subPath"), py::arg("flags"))
.def("FindPath", [](BPathFinder& self,path_base_directory baseDirectory,const char * subPath,unsigned int flags) {
    BPath  _path;
    status_t r = self.FindPath(baseDirectory, subPath, flags, _path);
    return std::make_tuple(r,_path);
}
, "", py::arg("baseDirectory"), py::arg("subPath"), py::arg("flags"))
.def("FindPath", [](BPathFinder& self,path_base_directory baseDirectory,const char * subPath) {
    BPath  _path;
    status_t r = self.FindPath(baseDirectory, subPath, _path);
    return std::make_tuple(r,_path);
}
, "", py::arg("baseDirectory"), py::arg("subPath"))
.def("FindPath", [](BPathFinder& self,path_base_directory baseDirectory) {
    BPath  _path;
    status_t r = self.FindPath(baseDirectory, _path);
    return std::make_tuple(r,_path);
}
, "", py::arg("baseDirectory"))
.def("FindPaths", [](BPathFinder& self,const char * architecture,path_base_directory baseDirectory,const char * subPath,uint32 flags) {
    BStringList  _paths;
    static status_t r = self.FindPaths(architecture, baseDirectory, subPath, flags, _paths);
    return std::make_tuple(r,_paths);
}
, "", py::arg("architecture"), py::arg("baseDirectory"), py::arg("subPath"), py::arg("flags"))
.def("FindPaths", [](BPathFinder& self,path_base_directory baseDirectory,const char * subPath,uint32 flags) {
    BStringList  _paths;
    static status_t r = self.FindPaths(baseDirectory, subPath, flags, _paths);
    return std::make_tuple(r,_paths);
}
, "", py::arg("baseDirectory"), py::arg("subPath"), py::arg("flags"))
.def("FindPaths", [](BPathFinder& self,path_base_directory baseDirectory,const char * subPath) {
    BStringList  _paths;
    static status_t r = self.FindPaths(baseDirectory, subPath, _paths);
    return std::make_tuple(r,_paths);
}
, "", py::arg("baseDirectory"), py::arg("subPath"))
.def("FindPaths", [](BPathFinder& self,path_base_directory baseDirectory) {
    BStringList  _paths;
    static status_t r = self.FindPaths(baseDirectory, _paths);
    return std::make_tuple(r,_paths);
}
, "", py::arg("baseDirectory"))
;


}
