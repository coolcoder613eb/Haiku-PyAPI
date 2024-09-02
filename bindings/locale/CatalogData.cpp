#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <locale/CatalogData.h>
#include <Message.h>

namespace py = pybind11;

class PyBCatalogData : public BCatalogData{
	public:
		using BCatalogData::BCatalogData;
		const char*			GetString(const char* string, const char* context = NULL, const char* comment = NULL) override {
            PYBIND11_OVERLOAD_PURE(const char*, BCatalogData, GetString, string, context, comment);
        }
        const char*			GetString(uint32 id) override {
            PYBIND11_OVERLOAD_PURE(const char*, BCatalogData, GetString, id);
        }
        bool				CanHaveData() const override {
            PYBIND11_OVERLOAD(bool, BCatalogData, CanHaveData);
        }
        status_t			GetData(const char* name, BMessage* msg) override {
            PYBIND11_OVERLOAD(status_t, BCatalogData, GetData, name, msg);
        }
        status_t			GetData(uint32 id, BMessage* msg) override {
            PYBIND11_OVERLOAD(status_t, BCatalogData, GetData, id, msg);
        }
        status_t			SetString(const char* string, const char* translated, const char* context = NULL, const char* comment = NULL) override {
            PYBIND11_OVERLOAD(status_t, BCatalogData, SetString, string, translated, context, comment);
        }
        status_t			SetString(int32 id, const char* translated) override {
            PYBIND11_OVERLOAD(status_t, BCatalogData, SetString, id, translated);
        }
        bool				CanWriteData() const override {
            PYBIND11_OVERLOAD(bool, BCatalogData, CanWriteData);
        }
        status_t			SetData(const char* name, BMessage* msg) override {
            PYBIND11_OVERLOAD(status_t, BCatalogData, SetData, name, msg);
        }
        status_t			SetData(uint32 id, BMessage* msg) override {
            PYBIND11_OVERLOAD(status_t, BCatalogData, SetData, id, msg);
        }
        status_t			ReadFromFile(const char* path = NULL) override {
            PYBIND11_OVERLOAD(status_t, BCatalogData, ReadFromFile, path);
        }
        status_t			ReadFromAttribute(const entry_ref& appOrAddOnRef) override {
            PYBIND11_OVERLOAD(status_t, BCatalogData, ReadFromAttribute, appOrAddOnRef);
        }
        status_t			ReadFromResource(const entry_ref& appOrAddOnRef) override {
            PYBIND11_OVERLOAD(status_t, BCatalogData, ReadFromResource, appOrAddOnRef);
        }
        status_t			WriteToFile(const char* path = NULL) override {
            PYBIND11_OVERLOAD(status_t, BCatalogData, WriteToFile, path);
        }
        status_t			WriteToAttribute(const entry_ref& appOrAddOnRef) override {
            PYBIND11_OVERLOAD(status_t, BCatalogData, WriteToAttribute, appOrAddOnRef);
        }
        status_t			WriteToResource(const entry_ref& appOrAddOnRef) override {
            PYBIND11_OVERLOAD(status_t, BCatalogData, WriteToResource, appOrAddOnRef);
        }
        void				MakeEmpty() override {
            PYBIND11_OVERLOAD(void, BCatalogData, MakeEmpty);
        }
        int32				CountItems() const override {
            PYBIND11_OVERLOAD(int32, BCatalogData, CountItems);
        }
};

PYBIND11_MODULE(CatalogData, m)
{
//m.attr("gCatalogAddOnPriority") = py::cast(gCatalogAddOnPriority);
m.attr("gCatalogAddOnPriority") = 99; // from haiku source /add-ons/locale/catalogs/plaintext/Catalog.cpp

py::class_<BCatalogData, PyBCatalogData>(m, "BCatalogData")
.def(py::init<const char *, const char *, uint32>(), "", py::arg("signature"), py::arg("language"), py::arg("fingerprint"))
.def("GetString", py::overload_cast<const char *, const char *, const char *>(&BCatalogData::GetString), "", py::arg("string"), py::arg("context")=NULL, py::arg("comment")=NULL)
.def("GetString", py::overload_cast<uint32>(&BCatalogData::GetString), "", py::arg("id"))
.def("InitCheck", &BCatalogData::InitCheck, "")
.def("Next", &BCatalogData::Next, "")
.def("CanHaveData", &BCatalogData::CanHaveData, "")
.def("GetData", py::overload_cast<const char *, BMessage *>(&BCatalogData::GetData), "", py::arg("name"), py::arg("msg"))
.def("GetData", py::overload_cast<uint32, BMessage *>(&BCatalogData::GetData), "", py::arg("id"), py::arg("msg"))
.def("SetString", py::overload_cast<const char *, const char *, const char *, const char *>(&BCatalogData::SetString), "", py::arg("string"), py::arg("translated"), py::arg("context")=NULL, py::arg("comment")=NULL)
.def("SetString", py::overload_cast<int32, const char *>(&BCatalogData::SetString), "", py::arg("id"), py::arg("translated"))
.def("CanWriteData", &BCatalogData::CanWriteData, "")
.def("SetData", py::overload_cast<const char *, BMessage *>(&BCatalogData::SetData), "", py::arg("name"), py::arg("msg"))
.def("SetData", py::overload_cast<uint32, BMessage *>(&BCatalogData::SetData), "", py::arg("id"), py::arg("msg"))
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

//m.def("instantiate_catalog", &instantiate_catalog, "", py::arg("signature"), py::arg("language"), py::arg("fingerprint"));// as below

//m.def("create_catalog", &create_catalog, "", py::arg("signature"), py::arg("language"));// in src/add-ons/locale/catalogs/plaintext/Catalog.cpp or src/tools/locale/PlainTextCatalog.cpp

}
