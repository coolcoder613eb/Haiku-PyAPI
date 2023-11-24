#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <Resources.h>

namespace py = pybind11;
using namespace BPrivate;
using namespace BPrivate::Storage;
using namespace BPrivate::Storage::Mime;
using namespace BPackageKit;

void define_Resources(py::module_& m)
{
m.attr("ResourcesContainer") = py::cast(ResourcesContainer);

m.attr("ResourceFile") = py::cast(ResourceFile);

py::class_<BResources>(m, "BResources")
.def(py::init(), "")
.def(py::init<const BFile *, bool>(), "", py::arg("file"), py::arg("clobber")=false)
.def(py::init<const char *, bool>(), "", py::arg("path"), py::arg("clobber")=false)
.def(py::init<const entry_ref *, bool>(), "", py::arg("ref"), py::arg("clobber")=false)
.def("SetTo", py::overload_cast<const BFile *, bool>(&BResources::SetTo), "", py::arg("file"), py::arg("clobber")=false)
.def("SetTo", py::overload_cast<const char *, bool>(&BResources::SetTo), "", py::arg("path"), py::arg("clobber")=false)
.def("SetTo", py::overload_cast<const entry_ref *, bool>(&BResources::SetTo), "", py::arg("ref"), py::arg("clobber")=false)
.def("SetToImage", py::overload_cast<image_id, bool>(&BResources::SetToImage), "", py::arg("image"), py::arg("clobber")=false)
.def("SetToImage", py::overload_cast<const void *, bool>(&BResources::SetToImage), "", py::arg("codeOrDataPointer"), py::arg("clobber")=false)
.def("Unset", &BResources::Unset, "")
.def("InitCheck", &BResources::InitCheck, "")
.def("File", &BResources::File, "")
.def("LoadResource", py::overload_cast<type_code, int, size_t *>(&BResources::LoadResource), "", py::arg("type"), py::arg("id"), py::arg("_size"))
.def("LoadResource", py::overload_cast<type_code, const char *, size_t *>(&BResources::LoadResource), "", py::arg("type"), py::arg("name"), py::arg("_size"))
.def("PreloadResourceType", &BResources::PreloadResourceType, "", py::arg("type")=0)
.def("Sync", &BResources::Sync, "")
.def("MergeFrom", &BResources::MergeFrom, "", py::arg("fromFile"))
.def("WriteTo", &BResources::WriteTo, "", py::arg("file"))
.def("AddResource", &BResources::AddResource, "", py::arg("type"), py::arg("id"), py::arg("data"), py::arg("length"), py::arg("name")=NULL)
.def("HasResource", py::overload_cast<type_code, int>(&BResources::HasResource), "", py::arg("type"), py::arg("id"))
.def("HasResource", py::overload_cast<type_code, const char *>(&BResources::HasResource), "", py::arg("type"), py::arg("name"))
.def("GetResourceInfo", py::overload_cast<int, type_code *, int, const char * *, size_t *>(&BResources::GetResourceInfo), "", py::arg("byIndex"), py::arg("typeFound"), py::arg("idFound"), py::arg("nameFound"), py::arg("lengthFound"))
.def("GetResourceInfo", py::overload_cast<type_code, int, int, const char * *, size_t *>(&BResources::GetResourceInfo), "", py::arg("byType"), py::arg("andIndex"), py::arg("idFound"), py::arg("nameFound"), py::arg("lengthFound"))
.def("GetResourceInfo", py::overload_cast<type_code, int, const char * *, size_t *>(&BResources::GetResourceInfo), "", py::arg("byType"), py::arg("andID"), py::arg("nameFound"), py::arg("lengthFound"))
.def("GetResourceInfo", py::overload_cast<type_code, const char *, int, size_t *>(&BResources::GetResourceInfo), "", py::arg("byType"), py::arg("andName"), py::arg("idFound"), py::arg("lengthFound"))
.def("GetResourceInfo", py::overload_cast<const void *, type_code *, int, size_t *, const char * *>(&BResources::GetResourceInfo), "", py::arg("byPointer"), py::arg("typeFound"), py::arg("idFound"), py::arg("lengthFound"), py::arg("nameFound"))
.def("RemoveResource", py::overload_cast<const void *>(&BResources::RemoveResource), "", py::arg("resource"))
.def("RemoveResource", py::overload_cast<type_code, int>(&BResources::RemoveResource), "", py::arg("type"), py::arg("id"))
.def("WriteResource", &BResources::WriteResource, "", py::arg("type"), py::arg("id"), py::arg("data"), py::arg("offset"), py::arg("length"))
.def("ReadResource", &BResources::ReadResource, "", py::arg("type"), py::arg("id"), py::arg("data"), py::arg("offset"), py::arg("length"))
.def("FindResource", py::overload_cast<type_code, int, size_t *>(&BResources::FindResource), "", py::arg("type"), py::arg("id"), py::arg("lengthFound"))
.def("FindResource", py::overload_cast<type_code, const char *, size_t *>(&BResources::FindResource), "", py::arg("type"), py::arg("name"), py::arg("lengthFound"))
;


}