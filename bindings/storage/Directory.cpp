#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>


#include <Directory.h>
#include <Node.h>
#include <EntryList.h>
#include <StorageDefs.h>
#include <Entry.h>
#include <File.h>
#include <SymLink.h>

namespace py = pybind11;


PYBIND11_MODULE(Directory,m)
{
py::class_<BDirectory, BNode, BEntryList>(m, "BDirectory")// verify if needed
.def(py::init(), "")
.def(py::init<const BDirectory &>(), "", py::arg("dir"))
.def(py::init<const entry_ref *>(), "", py::arg("ref"))
.def(py::init<const node_ref *>(), "", py::arg("nref"))
.def(py::init<const BEntry *>(), "", py::arg("entry"))
.def(py::init<const char *>(), "", py::arg("path"))
.def(py::init<const BDirectory *, const char *>(), "", py::arg("dir"), py::arg("path"))
.def("SetTo", py::overload_cast<const entry_ref *>(&BDirectory::SetTo), "", py::arg("ref"))
.def("SetTo", py::overload_cast<const node_ref *>(&BDirectory::SetTo), "", py::arg("nref"))
.def("SetTo", py::overload_cast<const BEntry *>(&BDirectory::SetTo), "", py::arg("entry"))
.def("SetTo", py::overload_cast<const char *>(&BDirectory::SetTo), "", py::arg("path"))
.def("SetTo", py::overload_cast<const BDirectory *, const char *>(&BDirectory::SetTo), "", py::arg("dir"), py::arg("path"))
// works also as
//.def("GetEntry", &BDirectory::GetEntry, "", py::arg("entry"))
.def("GetEntry", py::overload_cast<BEntry *>(&BDirectory::GetEntry, py::const_), "",py::arg("entry")) // verificare
.def("IsRootDirectory", &BDirectory::IsRootDirectory, "")
.def("FindEntry", &BDirectory::FindEntry, "", py::arg("path"), py::arg("entry"), py::arg("traverse")=false)
.def("Contains", py::overload_cast<const char *, int32>(&BDirectory::Contains, py::const_), "",py::arg("path"),py::arg("nodeFlags")=B_ANY_NODE)
.def("Contains", py::overload_cast<const BEntry *, int32>(&BDirectory::Contains, py::const_), "",py::arg("entry"),py::arg("nodeFlags")=B_ANY_NODE)
.def("GetStatFor", &BDirectory::GetStatFor, "", py::arg("path"), py::arg("st"))
.def("GetNextEntry", &BDirectory::GetNextEntry, "", py::arg("entry"), py::arg("traverse")=false)
.def("GetNextRef", &BDirectory::GetNextRef, "", py::arg("ref"))
.def("GetNextDirents", &BDirectory::GetNextDirents, "", py::arg("buf"), py::arg("bufSize"), py::arg("count")=INT_MAX)
.def("Rewind", &BDirectory::Rewind, "")
.def("CountEntries", &BDirectory::CountEntries, "")
.def("CreateDirectory", &BDirectory::CreateDirectory, "", py::arg("path"), py::arg("dir"))
.def("CreateFile", &BDirectory::CreateFile, "", py::arg("path"), py::arg("file"), py::arg("failIfExists")=false)
.def("CreateSymLink", &BDirectory::CreateSymLink, "", py::arg("path"), py::arg("linkToPath"), py::arg("link"))
.def("operator=", &BDirectory::operator=, "", py::arg("dir"))
;

m.def("create_directory", &create_directory, "", py::arg("path"), py::arg("mode"));

}
