#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/SeparatorItem.h>
#include <MenuItem.h>

namespace py = pybind11;


PYBIND11_MODULE(SeparatorItem,m)
{
py::class_<BSeparatorItem, BMenuItem>(m, "BSeparatorItem")
.def(py::init(), "")
.def(py::init<BMessage *>(), "", py::arg("data"))
.def_static("Instantiate", &BSeparatorItem::Instantiate, "", py::arg("data"))
.def("Archive", &BSeparatorItem::Archive, "", py::arg("data"), py::arg("deep")=true)
.def("SetEnabled", &BSeparatorItem::SetEnabled, "", py::arg("enable"))
;

}
