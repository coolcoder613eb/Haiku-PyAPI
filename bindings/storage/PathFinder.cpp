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

class BPathFinderWrapper {
public:
    static std::tuple<status_t, BStringList> FindPaths(const char* architecture, path_base_directory baseDirectory, const char* subPath, uint32 flags, BStringList& _paths) {
        //BStringList _paths;
        status_t result = BPathFinder::FindPaths(architecture, baseDirectory, subPath, flags, _paths);
        return std::make_tuple(result, _paths);
    }
    static std::tuple<status_t, BStringList> FindPaths(path_base_directory baseDirectory, const char* subPath, uint32 flags, BStringList& _paths) {
        //BStringList _paths;
        status_t result = BPathFinder::FindPaths(baseDirectory, subPath, flags, _paths);
        return std::make_tuple(result, _paths);
    }
    static std::tuple<status_t, BStringList> FindPaths(path_base_directory baseDirectory, const char* subPath, BStringList& _paths) {
        //BStringList _paths;
        status_t result = BPathFinder::FindPaths(baseDirectory, subPath, _paths);
        return std::make_tuple(result, _paths);
    }
    static std::tuple<status_t, BStringList> FindPaths(path_base_directory baseDirectory, BStringList& _paths) {
        //BStringList _paths;
        status_t result = BPathFinder::FindPaths(baseDirectory, _paths);
        return std::make_tuple(result, _paths);
    }
};


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
/*.def_static("FindPaths", [](BPathFinder& self,const char * architecture,path_base_directory baseDirectory,const char * subPath,uint32 flags) {
    BStringList  _paths;
    status_t r = self.FindPaths(architecture, baseDirectory, subPath, flags, _paths);
    return std::make_tuple(r,_paths);
}
, "", py::arg("architecture"), py::arg("baseDirectory"), py::arg("subPath"), py::arg("flags"))*/
.def_static("FindPaths", py::overload_cast<const char*, path_base_directory, const char*, uint32, BStringList&>(&BPathFinderWrapper::FindPaths), "", py::arg("architecture"), py::arg("baseDirectory"), py::arg("subPath"), py::arg("flags"), py::arg("_paths"))
/*.def("FindPaths", [](BPathFinder& self,path_base_directory baseDirectory,const char * subPath,uint32 flags) {
    BStringList  _paths;
    status_t r = self.FindPaths(baseDirectory, subPath, flags, _paths);
    return std::make_tuple(r,_paths);
}
, "", py::arg("baseDirectory"), py::arg("subPath"), py::arg("flags"))*/
.def_static("FindPaths", py::overload_cast<path_base_directory,const char*, uint32, BStringList&>(&BPathFinderWrapper::FindPaths), "", py::arg("baseDirectory"), py::arg("subPath"), py::arg("flags"), py::arg("_paths"))
/*.def("FindPaths", [](BPathFinder& self,path_base_directory baseDirectory,const char * subPath) {
    BStringList  _paths;
    status_t r = self.FindPaths(baseDirectory, subPath, _paths);
    return std::make_tuple(r,_paths);
}
, "", py::arg("baseDirectory"), py::arg("subPath"))*/
.def_static("FindPaths", py::overload_cast<path_base_directory, const char*, BStringList&>(&BPathFinderWrapper::FindPaths), "", py::arg("baseDirectory"), py::arg("subPath"), py::arg("_paths"))
/*.def("FindPaths", [](BPathFinder& self,path_base_directory baseDirectory) {
    BStringList  _paths;
    status_t r = self.FindPaths(baseDirectory, _paths);
    return std::make_tuple(r,_paths);
}
, "", py::arg("baseDirectory"))*/
.def_static("FindPaths", py::overload_cast<path_base_directory, BStringList&>(&BPathFinderWrapper::FindPaths), "", py::arg("baseDirectory"), py::arg("_paths"))
;

}
