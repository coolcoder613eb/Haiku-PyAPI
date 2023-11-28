#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/StringList.h>

namespace py = pybind11;


void define_StringList(py::module_& m)
{
py::class_<BStringList, BFlattenable>(m, "BStringList")
.def(py::init<int>(), "", py::arg("count")=20)
.def(py::init<const BStringList &>(), "", py::arg("other"))
.def("Add", py::overload_cast<const BString &, int>(&BStringList::Add), "", py::arg("string"), py::arg("index"))
.def("Add", py::overload_cast<const BString &>(&BStringList::Add), "", py::arg("string"))
.def("Add", py::overload_cast<const BStringList &, int>(&BStringList::Add), "", py::arg("list"), py::arg("index"))
.def("Add", py::overload_cast<const BStringList &>(&BStringList::Add), "", py::arg("list"))
.def("Remove", py::overload_cast<const BString &, bool>(&BStringList::Remove), "", py::arg("string"), py::arg("ignoreCase")=false)
.def("Remove", py::overload_cast<const BStringList &, bool>(&BStringList::Remove), "", py::arg("list"), py::arg("ignoreCase")=false)
.def("Remove", py::overload_cast<int>(&BStringList::Remove), "", py::arg("index"))
.def("Remove", py::overload_cast<int, int>(&BStringList::Remove), "", py::arg("index"), py::arg("count"))
.def("Replace", &BStringList::Replace, "", py::arg("index"), py::arg("string"))
.def("MakeEmpty", &BStringList::MakeEmpty, "")
.def("Sort", &BStringList::Sort, "", py::arg("ignoreCase")=false)
.def("Swap", &BStringList::Swap, "", py::arg("indexA"), py::arg("indexB"))
.def("Move", &BStringList::Move, "", py::arg("fromIndex"), py::arg("toIndex"))
.def("StringAt", &BStringList::StringAt, "", py::arg("index"))
.def("First", &BStringList::First, "")
.def("Last", &BStringList::Last, "")
.def("HasString", &BStringList::HasString, "", py::arg("string"), py::arg("ignoreCase")=false)
.def("IndexOf", &BStringList::IndexOf, "", py::arg("string"), py::arg("ignoreCase")=false)
.def("CountStrings", &BStringList::CountStrings, "")
.def("IsEmpty", &BStringList::IsEmpty, "")
.def("Join", &BStringList::Join, "", py::arg("separator"), py::arg("length")=- 1)
.def("DoForEach", py::overload_cast<bool(*func)(constBString&string)>(&BStringList::DoForEach), "", py::arg(""))
.def("DoForEach", py::overload_cast<bool(*func)(constBString&string,void*arg2), void *>(&BStringList::DoForEach), "", py::arg(""), py::arg("arg2"))
.def("operator=", &BStringList::operator=, "", py::arg("other"))
.def("__eq__", &BStringList::operator==, "", py::arg("other"))
.def("__ne__", &BStringList::operator!=, "", py::arg("other"))
.def("IsFixedSize", &BStringList::IsFixedSize, "")
.def("TypeCode", &BStringList::TypeCode, "")
.def("AllowsTypeCode", &BStringList::AllowsTypeCode, "", py::arg("code"))
.def("FlattenedSize", &BStringList::FlattenedSize, "")
.def("Flatten", &BStringList::Flatten, "", py::arg("buffer"), py::arg("size"))
.def("Unflatten", &BStringList::Unflatten, "", py::arg("code"), py::arg("buffer"), py::arg("size"))
;

m.def("__ne__", &operator!=, "", py::arg("other"));

}
