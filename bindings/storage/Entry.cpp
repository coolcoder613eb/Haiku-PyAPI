#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <storage/Entry.h>
//#include <sys/types.h>
//#include <sys/stat.h>
#include <SupportDefs.h>
#include <Statable.h>

#include <Directory.h>
#include <Path.h>

namespace py = pybind11;


PYBIND11_MODULE(Entry,m)
{
py::class_<entry_ref>(m, "entry_ref")
.def(py::init(), "")
.def(py::init<dev_t, ino_t, const char *>(), "", py::arg("device"), py::arg("dir"), py::arg("name"))
.def(py::init<const entry_ref&>(), "", py::arg("ref"))
.def("set_name", &entry_ref::set_name, "", py::arg("name"))
.def("__ne__", &entry_ref::operator!=, "", py::arg("ref"))
.def("__eq__", &entry_ref::operator==, "", py::arg("ref"))
.def("operator=", &entry_ref::operator=, "", py::arg("ref"))
.def_readwrite("device", &entry_ref::device, "")
.def_readwrite("directory", &entry_ref::directory, "")
.def_readwrite("name", &entry_ref::name, "")
;

py::class_<BEntry>(m, "BEntry")//, BStatable
.def(py::init(), "")
.def(py::init<const BDirectory *, const char *, bool>(), "", py::arg("dir"), py::arg("path"), py::arg("traverse")=false)
.def(py::init<const entry_ref *, bool>(), "", py::arg("ref"), py::arg("traverse")=false)
.def(py::init<const char *, bool>(), "", py::arg("path"),py::arg("traverse")=false)
.def(py::init<const BEntry&>(), "", py::arg("entry"))
//vecchio.def_static("Instantiate", &BBox::Instantiate, "", py::arg("archive"))
.def("InitCheck", &BEntry::InitCheck, "")
.def("Exists", &BEntry::Exists, "")
.def("Name", &BEntry::Name, "")
.def("GetStat", &BEntry::GetStat, "", py::arg("stat"))
//vecchio.def("SetLabel", py::overload_cast<const char *>(&BBox::SetLabel), "", py::arg("string"))
//vecchio.def("SetLabel", py::overload_cast<BView *>(&BBox::SetLabel), "", py::arg("viewLabel"))
//.def("SetTo", &BEntry::SetTo, "",py::arg("dir"),py::arg("path"),py::arg("traverse")=false)
//.def("SetTo", &BEntry::SetTo, "",py::arg("ref"),py::arg("traverse")=false)
//.def("SetTo", &BEntry::SetTo, "",py::arg("path"),py::arg("traverse")=false)
.def("Unset", &BEntry::Unset, "")
.def("GetRef", &BEntry::GetRef, "",py::arg("ref"))
.def("GetPath", &BEntry::GetPath, "",py::arg("path"))
//.def("GetParent", &BEntry::GetParent, "",py::arg("entry"))
//.def("GetParent", &BEntry::GetParent, "",py::arg("dir"))
.def("GetName", &BEntry::GetName, "", py::arg("buffer"))
.def("Rename", &BEntry::Rename, "", py::arg("path"),py::arg("clobber")=false)
.def("MoveTo", &BEntry::MoveTo, "", py::arg("dir"),py::arg("path"),py::arg("clobber")=false)
.def("Remove", &BEntry::Remove, "")
.def("operator=", &BEntry::operator=, "", py::arg("item"))
.def("__eq__", &BEntry::operator==, "", py::arg("item"))
.def("__ne__", &BEntry::operator!=, "", py::arg("item"))
;

m.def("get_ref_for_path",&get_ref_for_path, "", py::arg("path"), py::arg("ref"));
m.def("operator<", &operator<, "", py::arg("a"),py::arg("b"));


}
