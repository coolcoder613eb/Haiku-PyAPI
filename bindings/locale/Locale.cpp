#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <locale/Locale.h>

namespace py = pybind11;


void define_Locale(py::module_& m)
{
py::class_<BLocale>(m, "BLocale")
.def(py::init<const BLanguage *, const BFormattingConventions *>(), "", py::arg("language")=NULL, py::arg("conventions")=NULL)
.def(py::init<const BLocale &>(), "", py::arg("other"))
.def_static("Default", &BLocale::Default, "")
.def("operator=", &BLocale::operator=, "", py::arg("other"))
.def("GetCollator", &BLocale::GetCollator, "", py::arg("collator"))
.def("GetLanguage", &BLocale::GetLanguage, "", py::arg("language"))
.def("GetFormattingConventions", &BLocale::GetFormattingConventions, "", py::arg("conventions"))
.def("SetFormattingConventions", &BLocale::SetFormattingConventions, "", py::arg("conventions"))
.def("SetCollator", &BLocale::SetCollator, "", py::arg("newCollator"))
.def("SetLanguage", &BLocale::SetLanguage, "", py::arg("newLanguage"))
.def("GetString", &BLocale::GetString, "", py::arg("id"))
.def("StringCompare", py::overload_cast<const char *, const char *>(&BLocale::StringCompare), "", py::arg("s1"), py::arg("s2"))
.def("StringCompare", py::overload_cast<const BString *, const BString *>(&BLocale::StringCompare), "", py::arg("s1"), py::arg("s2"))
.def("GetSortKey", &BLocale::GetSortKey, "", py::arg("string"), py::arg("sortKey"))
;


}
