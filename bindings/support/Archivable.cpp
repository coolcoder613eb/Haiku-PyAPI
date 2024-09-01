#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/Archivable.h>
//#include <image.h>
//#include <Message.h>
//#include <SupportDefs.h>

namespace py = pybind11;
using namespace BPrivate;
using namespace BPrivate::Archiving;


PYBIND11_MODULE(Archivable, m)
{
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
.def("GetTokenForArchivable", py::overload_cast<BArchivable *, int32&>(&BArchiver::GetTokenForArchivable), "", py::arg("archivable"), py::arg("_token")) //TODO Check this function
.def("GetTokenForArchivable", py::overload_cast<BArchivable *, bool, int32&>(&BArchiver::GetTokenForArchivable), "", py::arg("archivable"), py::arg("deep"), py::arg("_token")) //TODO Check this function
.def("IsArchived", &BArchiver::IsArchived, "", py::arg("archivable"))
.def("Finish", &BArchiver::Finish, "", py::arg("err")=B_OK)
.def("ArchiveMessage", &BArchiver::ArchiveMessage, "")
;

py::class_<BUnarchiver>(m, "BUnarchiver")
.def(py::init<const BMessage *>(), "", py::arg("archive"))
/*.def("GetObject", [](BUnarchiver& self,int token) {
    T *  object;
    inline status_t r = self.GetObject(token, object);
    return std::make_tuple(r,object);
}, "", py::arg("token"))*/
/*.def("GetObject", [](BUnarchiver& self,int token,ownership_policy owning) {
    T *  object;
    status_t r = self.GetObject(token, owning, object);
    return std::make_tuple(r,object);
}, "", py::arg("token"), py::arg("owning"))*/
/*.def("FindObject", [](BUnarchiver& self,const char * name) {
    T *  object;
    inline status_t r = self.FindObject(name, object);
    return std::make_tuple(r,object);
}, "", py::arg("name"))*/
/*.def("FindObject", [](BUnarchiver& self,const char * name,ownership_policy owning) {
    T *  object;
    inline status_t r = self.FindObject(name, owning, object);
    return std::make_tuple(r,object);
}, "", py::arg("name"), py::arg("owning"))*/
/*.def("FindObject", [](BUnarchiver& self,const char * name,int index) {
    T *  object;
    inline status_t r = self.FindObject(name, index, object);
    return std::make_tuple(r,object);
}, "", py::arg("name"), py::arg("index"))*/
/*.def("FindObject", [](BUnarchiver& self,const char * name,int index,ownership_policy owning) {
    T *  object;
    status_t r = self.FindObject(name, index, owning, object);
    return std::make_tuple(r,object);
}, "", py::arg("name"), py::arg("index"), py::arg("owning"))*/
.def("EnsureUnarchived", py::overload_cast<const char *, int32>(&BUnarchiver::EnsureUnarchived), "", py::arg("name"), py::arg("index")=0)
.def("EnsureUnarchived", py::overload_cast<int32>(&BUnarchiver::EnsureUnarchived), "", py::arg("token"))
.def("IsInstantiated", py::overload_cast<int32>(&BUnarchiver::IsInstantiated), "", py::arg("token"))
.def("IsInstantiated", py::overload_cast<const char *, int32>(&BUnarchiver::IsInstantiated), "", py::arg("name"), py::arg("index")=0)
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
/*.def_static("InstantiateObject", [](BUnarchiver& self,BMessage * archive) {
    T *  object;
    static status_t r = self.InstantiateObject(archive, object);
    return std::make_tuple(r,object);
}, "", py::arg("archive"))*/
;

///* these do not generate errors on compile-time

m.def("instantiate_object", py::overload_cast<BMessage *, image_id *>(&instantiate_object), "", py::arg("from"), py::arg("id"));

m.def("instantiate_object", py::overload_cast<BMessage *>(&instantiate_object), "", py::arg("from"));

m.def("validate_instantiation", &validate_instantiation, "", py::arg("from"), py::arg("className"));
//*/

//m.def("find_instantiation_func", py::overload_cast<const char *, const char *>(&find_instantiation_func), "", py::arg("className"), py::arg("signature"));
//TODO: check these 3 functions
m.def("find_instantiation_func", [](const char* className, const char* signature) -> py::object {
        instantiation_func func = find_instantiation_func(className, signature);
        if (func == nullptr) {
            return py::none();
        }
        return py::cpp_function([func](BMessage* msg) -> BArchivable* {
            return func(msg);
        });
}, py::arg("className"), py::arg("signature"));

//m.def("find_instantiation_func", py::overload_cast<const char *>(&find_instantiation_func), "", py::arg("className"));
m.def("find_instantiation_func", [](const char* className) -> py::object {
        instantiation_func func = find_instantiation_func(className);
        if (func == nullptr) {
            return py::none();
        }

        return py::cpp_function([func](BMessage* msg) -> BArchivable* {
            return func(msg);
        });
}, py::arg("className"));

//m.def("find_instantiation_func", py::overload_cast<BMessage *>(&find_instantiation_func), "", py::arg("archive"));
m.def("find_instantiation_func", [](BMessage* archive) -> py::object {
        instantiation_func func = find_instantiation_func(archive);
        if (func == nullptr) {
            return py::none();
        }
        
        return py::cpp_function([func](BMessage* msg) -> BArchivable* {
            return func(msg);
        });
}, py::arg("archive"));
/*
m.def(">", [](const char * name,int index,ownership_policy owning) {
    BArchivable *  archivable;
    status_t BUnarchiver::FindObject<BArchivable r = >(name, index, owning, archivable);
    return std::make_tuple(r,archivable);
}
, "", py::arg("name"), py::arg("index"), py::arg("owning"));
*/
/*
m.def(">", [](int token,ownership_policy owning) {
    BArchivable *  object;
    status_t BUnarchiver::GetObject<BArchivable r = >(token, owning, object);
    return std::make_tuple(r,object);
}
, "", py::arg("token"), py::arg("owning"));
*/
/*
m.def(">", [](BMessage * from) {
    BArchivable *  object;
    status_t BUnarchiver::InstantiateObject<BArchivable r = >(from, object);
    return std::make_tuple(r,object);
}
, "", py::arg("from"));
*/

//m.attr("BArchiveManager") = py::cast(BArchiveManager);

//m.attr("BUnarchiveManager") = py::cast(BUnarchiveManager);

//m.attr("BArchiveManager") = py::cast(BArchiveManager);

//m.attr("BUnarchiveManager") = py::cast(BUnarchiveManager);

//my attempt to add ownership_policy:
//m.attr("B_ASSUME_OWNERSHIP") = py::cast(BUnarchiver::ownership_policy::B_ASSUME_OWNERSHIP);
m.attr("B_ASSUME_OWNERSHIP") = 0;
//m.attr("B_DONT_ASSUME_OWNERSHIP") = py::cast(BUnarchiver::ownership_policy::B_DONT_ASSUME_OWNERSHIP);
m.attr("B_DONT_ASSUME_OWNERSHIP") = 1;
}
