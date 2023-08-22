#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/Layout.h>
#include <Alignment.h>
#include <Archivable.h>
#include <LayoutItem.h>
#include <List.h>
#include <Size.h>

namespace py = pybind11;


PYBIND11_MODULE(Layout,m)
{
py::class_<BLayout, BLayoutItem>(m, "BLayout")
.def(py::init(), "")
.def(py::init<BMessage *>(), "", py::arg("archive"))
.def("Owner", &BLayout::Owner, "")
.def("TargetView", &BLayout::TargetView, "")
.def("View", &BLayout::View, "")
.def("AddView", py::overload_cast<BView *>(&BLayout::AddView), "", py::arg("child"))
.def("AddView", py::overload_cast<int, BView *>(&BLayout::AddView), "", py::arg("index"), py::arg("child"))
.def("AddItem", py::overload_cast<BLayoutItem *>(&BLayout::AddItem), "", py::arg("item"))
.def("AddItem", py::overload_cast<int, BLayoutItem *>(&BLayout::AddItem), "", py::arg("index"), py::arg("item"))
.def("RemoveView", &BLayout::RemoveView, "", py::arg("child"))
.def("RemoveItem", py::overload_cast<BLayoutItem *>(&BLayout::RemoveItem), "", py::arg("item"))
.def("RemoveItem", py::overload_cast<int>(&BLayout::RemoveItem), "", py::arg("index"))
.def("ItemAt", &BLayout::ItemAt, "", py::arg("index"))
.def("CountItems", &BLayout::CountItems, "")
.def("IndexOfItem", &BLayout::IndexOfItem, "", py::arg("item"))
.def("IndexOfView", &BLayout::IndexOfView, "", py::arg("child"))
.def("AncestorsVisible", &BLayout::AncestorsVisible, "")
.def("InvalidateLayout", &BLayout::InvalidateLayout, "", py::arg("children")=false)
.def("Relayout", &BLayout::Relayout, "", py::arg("immediate")=false)
.def("RequireLayout", &BLayout::RequireLayout, "")
.def("IsValid", &BLayout::IsValid, "")
.def("EnableLayoutInvalidation", &BLayout::EnableLayoutInvalidation, "")
.def("DisableLayoutInvalidation", &BLayout::DisableLayoutInvalidation, "")
.def("LayoutItems", &BLayout::LayoutItems, "", py::arg("force")=false)
.def("LayoutArea", &BLayout::LayoutArea, "")
.def("LayoutContext", &BLayout::LayoutContext, "")
.def("Archive", &BLayout::Archive, "", py::arg("into"), py::arg("deep")=true)
.def("Perform", &BLayout::Perform, "", py::arg("d"), py::arg("arg"))
;


}
