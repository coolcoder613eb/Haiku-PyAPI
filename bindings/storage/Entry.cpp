#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <Entry.h>

#include <SupportDefs.h>
#include <Statable.h>

#include <Directory.h>
#include <Path.h>

namespace py = pybind11;


PYBIND11_MODULE(Entry,m)
{
py::class_<entry_ref>(m, "entry_ref")
.def(py::init(), "")
.def(py::init<dev_t, ino_t, const char *>(), "", py::arg("dev"), py::arg("dir"), py::arg("name"))
.def(py::init<const entry_ref &>(), "", py::arg("ref"))
.def("set_name", &entry_ref::set_name, "", py::arg("name"))
.def("__eq__", &entry_ref::operator==, "", py::arg("ref"))
.def("__ne__", &entry_ref::operator!=, "", py::arg("ref"))
.def("operator=", &entry_ref::operator=, "", py::arg("ref"))
.def_readwrite("device", &entry_ref::device, "")
.def_readwrite("directory", &entry_ref::directory, "")
.def_readwrite("name", &entry_ref::name, "")
;

py::class_<BEntry>(m, "BEntry") //Commented out BStatable verify if needed
.def(py::init(), "")
.def(py::init<const BDirectory *, const char *, bool>(), "", py::arg("dir"), py::arg("path"), py::arg("traverse")=false)
.def(py::init<const entry_ref *, bool>(), "", py::arg("ref"), py::arg("traverse")=false)
.def(py::init<const char *, bool>(), "", py::arg("path"), py::arg("traverse")=false)
.def(py::init<const BEntry &>(), "", py::arg("entry"))
.def("InitCheck", &BEntry::InitCheck, "")
.def("Exists", &BEntry::Exists, "")
.def("Name", &BEntry::Name, "")
.def("GetStat", &BEntry::GetStat, "", py::arg("stat"))
.def("SetTo", py::overload_cast<const BDirectory *, const char *, bool>(&BEntry::SetTo), "", py::arg("dir"), py::arg("path"), py::arg("traverse")=false)
.def("SetTo", py::overload_cast<const entry_ref *, bool>(&BEntry::SetTo), "", py::arg("ref"), py::arg("traverse")=false)
.def("SetTo", py::overload_cast<const char *, bool>(&BEntry::SetTo), "", py::arg("path"), py::arg("traverse")=false)
.def("Unset", &BEntry::Unset, "")
.def("GetRef", &BEntry::GetRef, "",py::arg("ref"))
.def("GetPath", &BEntry::GetPath, "",py::arg("path"))
.def("GetParent", py::overload_cast<BEntry *>(&BEntry::GetParent, py::const_), "",py::arg("entry")) //added py::const_
.def("GetParent", py::overload_cast<BDirectory *>(&BEntry::GetParent, py::const_), "",py::arg("dir")) //added py::const_
.def("GetName", &BEntry::GetName, "", py::arg("buffer"))
.def("Rename", &BEntry::Rename, "", py::arg("path"), py::arg("clobber")=false)
.def("MoveTo", &BEntry::MoveTo, "", py::arg("dir"), py::arg("path")=NULL, py::arg("clobber")=false)
.def("Remove", &BEntry::Remove, "")
.def("__eq__", &BEntry::operator==, "", py::arg("item"))
.def("__ne__", &BEntry::operator!=, "", py::arg("item"))
.def("operator=", &BEntry::operator=, "", py::arg("item"))
;

m.def("get_ref_for_path", &get_ref_for_path, "", py::arg("path"), py::arg("ref"));

m.def("__lt__", &operator<, "", py::arg("a"), py::arg("b"));

}
