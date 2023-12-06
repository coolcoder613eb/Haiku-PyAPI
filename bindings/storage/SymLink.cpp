#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <SymLink.h>
#include <Path.h>
#include <Directory.h>
#include <Node.h>
#include <Entry.h>

namespace py = pybind11;
//using namespace BPrivate;
//using namespace BPrivate::Storage;
//using namespace BPrivate::Storage::Mime;
//using namespace BPackageKit;

PYBIND11_MODULE(SymLink, m)
{
py::class_<BSymLink, BNode>(m, "BSymLink")
.def(py::init(), "")
.def(py::init<const BSymLink &>(), "", py::arg("other"))
.def(py::init<const entry_ref *>(), "", py::arg("ref"))
.def(py::init<const BEntry *>(), "", py::arg("entry"))
.def(py::init<const char *>(), "", py::arg("path"))
.def(py::init<const BDirectory *, const char *>(), "", py::arg("dir"), py::arg("path"))
.def("ReadLink", &BSymLink::ReadLink, "", py::arg("buf"), py::arg("size"))
.def("MakeLinkedPath", py::overload_cast<const char *, BPath *>(&BSymLink::MakeLinkedPath), "", py::arg("dirPath"), py::arg("path"))
.def("MakeLinkedPath", py::overload_cast<const BDirectory *, BPath *>(&BSymLink::MakeLinkedPath), "", py::arg("dir"), py::arg("path"))
.def("IsAbsolute", &BSymLink::IsAbsolute, "")
;


}
