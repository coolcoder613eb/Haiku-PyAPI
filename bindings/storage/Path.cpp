#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <Path.h>

namespace py = pybind11;
using namespace BPrivate;
using namespace BPrivate::Storage;
using namespace BPrivate::Storage::Mime;

void define_Path(py::module_& m)
{
py::class_<BPath, BFlattenable>(m, "BPath")
.def(py::init(), "")
.def(py::init<const BPath &>(), "", py::arg("path"))
.def(py::init<const entry_ref *>(), "", py::arg("ref"))
.def(py::init<const BEntry *>(), "", py::arg("entry"))
.def(py::init<const char *, const char *, bool>(), "", py::arg("dir"), py::arg("leaf")=NULL, py::arg("normalize")=false)
.def(py::init<const BDirectory *, const char *, bool>(), "", py::arg("dir"), py::arg("leaf")=NULL, py::arg("normalize")=false)
.def("InitCheck", &BPath::InitCheck, "")
.def("SetTo", py::overload_cast<const entry_ref *>(&BPath::SetTo), "", py::arg("ref"))
.def("SetTo", py::overload_cast<const BEntry *>(&BPath::SetTo), "", py::arg("entry"))
.def("SetTo", py::overload_cast<const char *, const char *, bool>(&BPath::SetTo), "", py::arg("path"), py::arg("leaf")=NULL, py::arg("normalize")=false)
.def("SetTo", py::overload_cast<const BDirectory *, const char *, bool>(&BPath::SetTo), "", py::arg("dir"), py::arg("leaf")=NULL, py::arg("normalize")=false)
.def("Unset", &BPath::Unset, "")
.def("Append", &BPath::Append, "", py::arg("path"), py::arg("normalize")=false)
.def("Path", &BPath::Path, "")
.def("Leaf", &BPath::Leaf, "")
.def("GetParent", &BPath::GetParent, "", py::arg("path"))
.def("IsAbsolute", &BPath::IsAbsolute, "")
.def("__eq__", py::overload_cast<const BPath &>(&BPath::operator==), "", py::arg("item"))
.def("__eq__", py::overload_cast<const char *>(&BPath::operator==), "", py::arg("path"))
.def("__ne__", py::overload_cast<const BPath &>(&BPath::operator!=), "", py::arg("item"))
.def("__ne__", py::overload_cast<const char *>(&BPath::operator!=), "", py::arg("path"))
.def("operator=", py::overload_cast<const BPath &>(&BPath::operator=), "", py::arg("item"))
.def("operator=", py::overload_cast<const char *>(&BPath::operator=), "", py::arg("path"))
.def("IsFixedSize", &BPath::IsFixedSize, "")
.def("TypeCode", &BPath::TypeCode, "")
.def("FlattenedSize", &BPath::FlattenedSize, "")
.def("Flatten", &BPath::Flatten, "", py::arg("buffer"), py::arg("size"))
.def("AllowsTypeCode", &BPath::AllowsTypeCode, "", py::arg("code"))
.def("Unflatten", &BPath::Unflatten, "", py::arg("code"), py::arg("buffer"), py::arg("size"))
;


}
