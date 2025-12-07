#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>
#include <pybind11/functional.h>

#include <support/StringList.h>

namespace py = pybind11;

class PyBStringList : public BStringList{
	public:
        using BStringList::BStringList;
        bool				IsFixedSize() const override {
        	PYBIND11_OVERLOAD(bool, BStringList, IsFixedSize);
        }
        type_code			TypeCode() const override {
        	PYBIND11_OVERLOAD(type_code, BStringList, TypeCode);
        }
        bool				AllowsTypeCode(type_code code) const override {
        	PYBIND11_OVERLOAD(bool, BStringList, AllowsTypeCode, code);
        }
        ssize_t				FlattenedSize() const override {
        	PYBIND11_OVERLOAD(ssize_t, BStringList, FlattenedSize);
        }
        status_t			Flatten(void* buffer, ssize_t size) const override {
        	PYBIND11_OVERLOAD(status_t, BStringList, Flatten, buffer, size);
        }
        status_t			Unflatten(type_code code, const void* buffer, ssize_t size) override {
        	PYBIND11_OVERLOAD(status_t, BStringList, Unflatten, code, buffer, size);
        }
};

bool CallPythonFunction(const BString& item, py::function& func) {
    // Chiamare la funzione Python passando l'elemento
    // Questo richiede la conversione tra tipi C++ e Python
    // Includere eventuali conversioni necessarie qui
    // Esempio di chiamata della funzione Python
    py::object result = func(item);

    // Convertire il risultato della funzione Python in un booleano
    return py::cast<bool>(result);
}
/* or this way
bool CallPythonFunction(const BString& str, const py::function& func) {
    // Chiamare la funzione Python
    return func(str).template cast<bool>();
}*/


PYBIND11_MODULE(StringList, m)
{
py::class_<BStringList, BFlattenable>(m, "BStringList")
.def(py::init<int32>(), "", py::arg("count")=20)
.def(py::init<const BStringList &>(), "", py::arg("other"))
.def("Add", py::overload_cast<const BString &, int32>(&BStringList::Add), "", py::arg("string"), py::arg("index"))
.def("Add", py::overload_cast<const BString &>(&BStringList::Add), "", py::arg("string"))
.def("Add", py::overload_cast<const BStringList &, int32>(&BStringList::Add), "", py::arg("list"), py::arg("index"))
.def("Add", py::overload_cast<const BStringList &>(&BStringList::Add), "", py::arg("list"))
.def("Remove", py::overload_cast<const BString &, bool>(&BStringList::Remove), "", py::arg("string"), py::arg("ignoreCase")=false)
.def("Remove", py::overload_cast<const BStringList &, bool>(&BStringList::Remove), "", py::arg("list"), py::arg("ignoreCase")=false)
.def("Remove", py::overload_cast<int32>(&BStringList::Remove), "", py::arg("index"))
.def("Remove", py::overload_cast<int32, int32>(&BStringList::Remove), "", py::arg("index"), py::arg("count"))
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
//.def("DoForEach", py::overload_cast<bool(*func)(constBString&string)>(&BStringList::DoForEach), "", py::arg(""))
.def("DoForEach", [](BStringList& self, py::function& func) -> void {
    self.DoForEach(static_cast<bool (*)(const BString&, void*)>(+[](const BString& item, void* userData) -> bool {
        return CallPythonFunction(item, *static_cast<py::function*>(userData));
    }), &func);
}, "", py::arg("func"))
//.def("DoForEach", py::overload_cast<bool(*func)(constBString&string,void*arg2), void *>(&BStringList::DoForEach), "", py::arg(""), py::arg("arg2"))
.def("DoForEach", [](BStringList& self, py::function& func, void* arg2) -> void {
    self.DoForEach(static_cast<bool (*)(const BString&, void*)>(+[](const BString& item, void* userData) -> bool {
        return CallPythonFunction(item, *static_cast<py::function*>(userData));
    }), arg2);
}, "", py::arg("func"), py::arg("arg2"))
.def("__copy__", &BStringList::operator=, "", py::arg("other"))
.def("__eq__", &BStringList::operator==, "", py::arg("other"))
.def("__ne__", &BStringList::operator!=, "", py::arg("other"))
.def("IsFixedSize", &BStringList::IsFixedSize, "")
.def("TypeCode", &BStringList::TypeCode, "")
.def("AllowsTypeCode", &BStringList::AllowsTypeCode, "", py::arg("code"))
.def("FlattenedSize", &BStringList::FlattenedSize, "")
.def("Flatten", &BStringList::Flatten, "", py::arg("buffer"), py::arg("size"))
.def("Unflatten", &BStringList::Unflatten, "", py::arg("code"), py::arg("buffer"), py::arg("size"))
;

//m.def("__ne__", &operator!=, "", py::arg("other"));

}
