#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <locale/CatalogData.h>

namespace py = pybind11;


void define_CatalogData(py::module_& m)
{
m.attr("gCatalogAddOnPriority") = py::cast(gCatalogAddOnPriority);

py::class_<BCatalogData>(m, "BCatalogData")
.def(py::init<const char *, const char *, unsigned int>(), "", py::arg("signature"), py::arg("language"), py::arg("fingerprint"))
.def("GetString", py::overload_cast<const char *, const char *, const char *>(&BCatalogData::GetString), "", py::arg("string"), py::arg("context")=NULL, py::arg("comment")=NULL)
.def("GetString", py::overload_cast<unsigned int>(&BCatalogData::GetString), "", py::arg("id"))
.def("InitCheck", &BCatalogData::InitCheck, "")
.def("Next", &BCatalogData::Next, "")
.def("CanHaveData", &BCatalogData::CanHaveData, "")
.def("GetData", py::overload_cast<const char *, BMessage *>(&BCatalogData::GetData), "", py::arg("name"), py::arg("msg"))
.def("GetData", py::overload_cast<unsigned int, BMessage *>(&BCatalogData::GetData), "", py::arg("id"), py::arg("msg"))
.def("SetString", py::overload_cast<const char *, const char *, const char *, const char *>(&BCatalogData::SetString), "", py::arg("string"), py::arg("translated"), py::arg("context")=NULL, py::arg("comment")=NULL)
.def("SetString", py::overload_cast<int, const char *>(&BCatalogData::SetString), "", py::arg("id"), py::arg("translated"))
.def("CanWriteData", &BCatalogData::CanWriteData, "")
.def("SetData", py::overload_cast<const char *, BMessage *>(&BCatalogData::SetData), "", py::arg("name"), py::arg("msg"))
.def("SetData", py::overload_cast<unsigned int, BMessage *>(&BCatalogData::SetData), "", py::arg("id"), py::arg("msg"))
.def("ReadFromFile", &BCatalogData::ReadFromFile, "", py::arg("path")=NULL)
.def("ReadFromAttribute", &BCatalogData::ReadFromAttribute, "", py::arg("appOrAddOnRef"))
.def("ReadFromResource", &BCatalogData::ReadFromResource, "", py::arg("appOrAddOnRef"))
.def("WriteToFile", &BCatalogData::WriteToFile, "", py::arg("path")=NULL)
.def("WriteToAttribute", &BCatalogData::WriteToAttribute, "", py::arg("appOrAddOnRef"))
.def("WriteToResource", &BCatalogData::WriteToResource, "", py::arg("appOrAddOnRef"))
.def("MakeEmpty", &BCatalogData::MakeEmpty, "")
.def("CountItems", &BCatalogData::CountItems, "")
.def("SetNext", &BCatalogData::SetNext, "", py::arg("next"))
;

m.def("instantiate_catalog", &instantiate_catalog, "", py::arg("signature"), py::arg("language"), py::arg("fingerprint"));

m.def("create_catalog", &create_catalog, "", py::arg("signature"), py::arg("language"));

}
