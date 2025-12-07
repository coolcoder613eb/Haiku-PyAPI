#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/List.h>

namespace py = pybind11;

bool CallPythonFunction(void* item, py::function& func) {
    py::object result = func(item);
    return py::cast<bool>(result);
}

PYBIND11_MODULE(List, m)
{
py::class_<BList>(m, "BList")
.def(py::init<int32>(), "", py::arg("count")=20)
.def(py::init<const BList &>(), "", py::arg("other"))
.def("__copy__", &BList::operator=, "", py::arg("other"))
.def("__eq__", &BList::operator==, "", py::arg("other"))
.def("__ne__", &BList::operator!=, "", py::arg("other"))
.def("AddItem", py::overload_cast<void *, int32>(&BList::AddItem), "", py::arg("item"), py::arg("index"))
.def("AddItem", py::overload_cast<void *>(&BList::AddItem), "", py::arg("item"))
.def("AddList", py::overload_cast<const BList *, int32>(&BList::AddList), "", py::arg("list"), py::arg("index"))
.def("AddList", py::overload_cast<const BList *>(&BList::AddList), "", py::arg("list"))
.def("RemoveItem", py::overload_cast<void *>(&BList::RemoveItem), "", py::arg("item"))
.def("RemoveItem", py::overload_cast<int32>(&BList::RemoveItem), "", py::arg("index"))
.def("RemoveItems", &BList::RemoveItems, "", py::arg("index"), py::arg("count"))
.def("ReplaceItem", &BList::ReplaceItem, "", py::arg("index"), py::arg("item"))
.def("MakeEmpty", &BList::MakeEmpty, "")
.def("SortItems", &BList::SortItems, "", py::arg(""))
.def("SwapItems", &BList::SwapItems, "", py::arg("indexA"), py::arg("indexB"))
.def("MoveItem", &BList::MoveItem, "", py::arg("from"), py::arg("to"))
.def("ItemAt", &BList::ItemAt, "", py::arg("index"))
.def("FirstItem", &BList::FirstItem, "")
.def("ItemAtFast", &BList::ItemAtFast, "", py::arg("index"))
.def("LastItem", &BList::LastItem, "")
.def("Items", &BList::Items, "")
.def("HasItem", py::overload_cast<void *>(&BList::HasItem, py::const_), "", py::arg("item"))
.def("HasItem", py::overload_cast<const void *>(&BList::HasItem, py::const_), "", py::arg("item"))
.def("IndexOf", py::overload_cast<void *>(&BList::IndexOf, py::const_), "", py::arg("item"))
.def("IndexOf", py::overload_cast<const void *>(&BList::IndexOf, py::const_), "", py::arg("item"))
.def("CountItems", &BList::CountItems, "")
.def("IsEmpty", &BList::IsEmpty, "")
//.def("DoForEach", py::overload_cast<bool(*func)(void*item)>(&BList::DoForEach), "", py::arg(""))
.def("DoForEach", [](BList& self,py::function& func, void* item) -> void {
	self.DoForEach(static_cast<bool (*)(void*, void*)>(+[](void* item, void* userData) -> bool {
            return CallPythonFunction(item, *static_cast<py::function*>(userData));
        }), item);
}, "", py::arg("func"), py::arg("item"))

//.def("DoForEach", py::overload_cast<bool(*func)(void*item,void*arg2), void *>(&BList::DoForEach), "", py::arg(""), py::arg("arg2"))
.def("DoForEach", [](BList& self, py::function& func, void* arg2) -> void {
            self.DoForEach(static_cast<bool (*)(void*, void*)>(+[](void* item, void* userData) -> bool {
                return CallPythonFunction(item, *static_cast<py::function*>(userData));
            }), arg2);
        }, "", py::arg("func"), py::arg("arg2"))
;
}
