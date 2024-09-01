#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <locale/Catalog.h>

namespace py = pybind11;


void define_Catalog(py::module_& m)
{
py::class_<BCatalog>(m, "BCatalog")
.def(py::init(), "")
.def(py::init<const entry_ref &, const char *, unsigned int>(), "", py::arg("catalogOwner"), py::arg("language")=NULL, py::arg("fingerprint")=0)
.def(py::init<const char *, const char *>(), "", py::arg("signature"), py::arg("language")=NULL)
.def("GetString", py::overload_cast<const char *, const char *, const char *>(&BCatalog::GetString), "", py::arg("string"), py::arg("context")=NULL, py::arg("comment")=NULL)
.def("GetString", py::overload_cast<unsigned int>(&BCatalog::GetString), "", py::arg("id"))
.def("GetData", py::overload_cast<const char *, BMessage *>(&BCatalog::GetData), "", py::arg("name"), py::arg("msg"))
.def("GetData", py::overload_cast<unsigned int, BMessage *>(&BCatalog::GetData), "", py::arg("id"), py::arg("msg"))
.def("GetSignature", &BCatalog::GetSignature, "", py::arg("signature"))
.def("GetLanguage", &BCatalog::GetLanguage, "", py::arg("language"))
.def("GetFingerprint", &BCatalog::GetFingerprint, "", py::arg("fingerprint"))
.def("SetTo", py::overload_cast<const entry_ref &, const char *, unsigned int>(&BCatalog::SetTo), "", py::arg("catalogOwner"), py::arg("language")=NULL, py::arg("fingerprint")=0)
.def("SetTo", py::overload_cast<const char *, const char *>(&BCatalog::SetTo), "", py::arg("signature"), py::arg("language")=NULL)
.def("InitCheck", &BCatalog::InitCheck, "")
.def("CountItems", &BCatalog::CountItems, "")
;


}
