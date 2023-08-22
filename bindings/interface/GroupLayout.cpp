#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/GroupLayout.h>
#include <TwoDimensionalLayout.h>

namespace py = pybind11;


PYBIND11_MODULE(GroupLayout,m)
{
py::class_<BGroupLayout, BTwoDimensionalLayout>(m, "BGroupLayout")
.def(py::init<orientation, float>(), "", py::arg("orientation"), py::arg("spacing")=B_USE_DEFAULT_SPACING)
.def(py::init<BMessage *>(), "", py::arg("from"))
.def("Spacing", &BGroupLayout::Spacing, "")
.def("SetSpacing", &BGroupLayout::SetSpacing, "", py::arg("spacing"))
.def("Orientation", &BGroupLayout::Orientation, "")
.def("SetOrientation", &BGroupLayout::SetOrientation, "", py::arg("orientation"))
.def("ItemWeight", &BGroupLayout::ItemWeight, "", py::arg("index"))
.def("SetItemWeight", &BGroupLayout::SetItemWeight, "", py::arg("index"), py::arg("weight"))
.def("AddView", py::overload_cast<BView *>(&BGroupLayout::AddView), "", py::arg("child"))
.def("AddView", py::overload_cast<int, BView *>(&BGroupLayout::AddView), "", py::arg("index"), py::arg("child"))
.def("AddView", py::overload_cast<BView *, float>(&BGroupLayout::AddView), "", py::arg("child"), py::arg("weight"))
.def("AddView", py::overload_cast<int, BView *, float>(&BGroupLayout::AddView), "", py::arg("index"), py::arg("child"), py::arg("weight"))
.def("AddItem", py::overload_cast<BLayoutItem *>(&BGroupLayout::AddItem), "", py::arg("item"))
.def("AddItem", py::overload_cast<int, BLayoutItem *>(&BGroupLayout::AddItem), "", py::arg("index"), py::arg("item"))
.def("AddItem", py::overload_cast<BLayoutItem *, float>(&BGroupLayout::AddItem), "", py::arg("item"), py::arg("weight"))
.def("AddItem", py::overload_cast<int, BLayoutItem *, float>(&BGroupLayout::AddItem), "", py::arg("index"), py::arg("item"), py::arg("weight"))
.def("Archive", &BGroupLayout::Archive, "", py::arg("into"), py::arg("deep")=true)
.def_static("Instantiate", &BGroupLayout::Instantiate, "", py::arg("from"))
.def("Perform", &BGroupLayout::Perform, "", py::arg("d"), py::arg("arg"))
;


}
