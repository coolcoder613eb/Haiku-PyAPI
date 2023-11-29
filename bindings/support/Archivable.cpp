#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/Archivable.h>

namespace py = pybind11;
using namespace BPrivate;
using namespace BPrivate::Archiving;

void define_Archivable(py::module_& m)
{
m.attr("BArchiveManager") = py::cast(BArchiveManager);

m.attr("BUnarchiveManager") = py::cast(BUnarchiveManager);

m.attr("BArchiveManager") = py::cast(BArchiveManager);

m.attr("BUnarchiveManager") = py::cast(BUnarchiveManager);

py::class_<BArchivable>(m, "BArchivable")
.def(py::init<BMessage *>(), "", py::arg("from"))
.def(py::init(), "")
.def("Archive", &BArchivable::Archive, "", py::arg("into"), py::arg("deep")=true)
.def_static("Instantiate", &BArchivable::Instantiate, "", py::arg("archive"))
.def("Perform", &BArchivable::Perform, "", py::arg("d"), py::arg("arg"))
.def("AllUnarchived", &BArchivable::AllUnarchived, "", py::arg("archive"))
.def("AllArchived", &BArchivable::AllArchived, "", py::arg("archive"))
;

py::class_<BArchiver>(m, "BArchiver")
.def(py::init<BMessage *>(), "", py::arg("archive"))
.def("AddArchivable", &BArchiver::AddArchivable, "", py::arg("name"), py::arg("archivable"), py::arg("deep")=true)
.def("GetTokenForArchivable", py::overload_cast<BArchivable *, int>(&BArchiver::GetTokenForArchivable), "", py::arg("archivable"), py::arg("_token"))
.def("GetTokenForArchivable", py::overload_cast<BArchivable *, bool, int>(&BArchiver::GetTokenForArchivable), "", py::arg("archivable"), py::arg("deep"), py::arg("_token"))
.def("IsArchived", &BArchiver::IsArchived, "", py::arg("archivable"))
.def("Finish", &BArchiver::Finish, "", py::arg("err")=B_OK)
.def("ArchiveMessage", &BArchiver::ArchiveMessage, "")
;

py::class_<BUnarchiver>(m, "BUnarchiver")
.def(py::init<const BMessage *>(), "", py::arg("archive"))
.def("GetObject", [](BUnarchiver& self,int token) {
    T *  object;
    inline status_t r = self.GetObject(token, object);
    return std::make_tuple(r,object);
}
, "", py::arg("token"))
.def("GetObject", [](BUnarchiver& self,int token,ownership_policy owning) {
    T *  object;
    status_t r = self.GetObject(token, owning, object);
    return std::make_tuple(r,object);
}
, "", py::arg("token"), py::arg("owning"))
.def("FindObject", [](BUnarchiver& self,const char * name) {
    T *  object;
    inline status_t r = self.FindObject(name, object);
    return std::make_tuple(r,object);
}
, "", py::arg("name"))
.def("FindObject", [](BUnarchiver& self,const char * name,ownership_policy owning) {
    T *  object;
    inline status_t r = self.FindObject(name, owning, object);
    return std::make_tuple(r,object);
}
, "", py::arg("name"), py::arg("owning"))
.def("FindObject", [](BUnarchiver& self,const char * name,int index) {
    T *  object;
    inline status_t r = self.FindObject(name, index, object);
    return std::make_tuple(r,object);
}
, "", py::arg("name"), py::arg("index"))
.def("FindObject", [](BUnarchiver& self,const char * name,int index,ownership_policy owning) {
    T *  object;
    status_t r = self.FindObject(name, index, owning, object);
    return std::make_tuple(r,object);
}
, "", py::arg("name"), py::arg("index"), py::arg("owning"))
.def("EnsureUnarchived", py::overload_cast<const char *, int>(&BUnarchiver::EnsureUnarchived), "", py::arg("name"), py::arg("index")=0)
.def("EnsureUnarchived", py::overload_cast<int>(&BUnarchiver::EnsureUnarchived), "", py::arg("token"))
.def("IsInstantiated", py::overload_cast<int>(&BUnarchiver::IsInstantiated), "", py::arg("token"))
.def("IsInstantiated", py::overload_cast<const char *, int>(&BUnarchiver::IsInstantiated), "", py::arg("name"), py::arg("index")=0)
.def("Finish", &BUnarchiver::Finish, "", py::arg("err")=B_OK)
.def("ArchiveMessage", &BUnarchiver::ArchiveMessage, "")
.def("AssumeOwnership", &BUnarchiver::AssumeOwnership, "", py::arg("archivable"))
.def("RelinquishOwnership", &BUnarchiver::RelinquishOwnership, "", py::arg("archivable"))
.def_static("IsArchiveManaged", &BUnarchiver::IsArchiveManaged, "", py::arg("archive"))
.def_static("PrepareArchive", [](BUnarchiver& self) {
    BMessage *  archive;
    static BMessage * r = self.PrepareArchive(archive);
    return std::make_tuple(r,archive);
}
, "")
.def_static("InstantiateObject", [](BUnarchiver& self,BMessage * archive) {
    T *  object;
    static status_t r = self.InstantiateObject(archive, object);
    return std::make_tuple(r,object);
}
, "", py::arg("archive"))
;

m.def("instantiate_object", py::overload_cast<BMessage *, image_id *>(&instantiate_object), "", py::arg("from"), py::arg("id"));

m.def("instantiate_object", py::overload_cast<BMessage *>(&instantiate_object), "", py::arg("from"));

m.def("validate_instantiation", &validate_instantiation, "", py::arg("from"), py::arg("className"));

m.def("find_instantiation_func", py::overload_cast<const char *, const char *>(&find_instantiation_func), "", py::arg("className"), py::arg("signature"));

m.def("find_instantiation_func", py::overload_cast<const char *>(&find_instantiation_func), "", py::arg("className"));

m.def("find_instantiation_func", py::overload_cast<BMessage *>(&find_instantiation_func), "", py::arg("archive"));

m.def(">", [](const char * name,int index,ownership_policy owning) {
    BArchivable *  archivable;
    status_t BUnarchiver::FindObject<BArchivable r = >(name, index, owning, archivable);
    return std::make_tuple(r,archivable);
}
, "", py::arg("name"), py::arg("index"), py::arg("owning"));

m.def(">", [](int token,ownership_policy owning) {
    BArchivable *  object;
    status_t BUnarchiver::GetObject<BArchivable r = >(token, owning, object);
    return std::make_tuple(r,object);
}
, "", py::arg("token"), py::arg("owning"));

m.def(">", [](BMessage * from) {
    BArchivable *  object;
    status_t BUnarchiver::InstantiateObject<BArchivable r = >(from, object);
    return std::make_tuple(r,object);
}
, "", py::arg("from"));

}
