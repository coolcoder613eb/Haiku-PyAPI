#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/SplitView.h>
#include <View.h>

namespace py = pybind11;


PYBIND11_MODULE(SplitView,m)
{
py::class_<BSplitView, BView>(m, "BSplitView")
.def(py::init<orientation, float>(), "", py::arg("orientation")=B_HORIZONTAL, py::arg("spacing")=B_USE_DEFAULT_SPACING)
.def(py::init<BMessage *>(), "", py::arg("from"))
.def("SetInsets", py::overload_cast<float, float, float, float>(&BSplitView::SetInsets), "", py::arg("left"), py::arg("top"), py::arg("right"), py::arg("bottom"))
.def("SetInsets", py::overload_cast<float, float>(&BSplitView::SetInsets), "", py::arg("horizontal"), py::arg("vertical"))
.def("SetInsets", py::overload_cast<float>(&BSplitView::SetInsets), "", py::arg("insets"))
.def("GetInsets", &BSplitView::GetInsets, "", py::arg("left"), py::arg("top"), py::arg("right"), py::arg("bottom"))
.def("Spacing", &BSplitView::Spacing, "")
.def("SetSpacing", &BSplitView::SetSpacing, "", py::arg("spacing"))
.def("Orientation", &BSplitView::Orientation, "")
.def("SetOrientation", &BSplitView::SetOrientation, "", py::arg("orientation"))
.def("SplitterSize", &BSplitView::SplitterSize, "")
.def("SetSplitterSize", &BSplitView::SetSplitterSize, "", py::arg("size"))
.def("CountItems", &BSplitView::CountItems, "")
.def("ItemWeight", py::overload_cast<int>(&BSplitView::ItemWeight), "", py::arg("index"))
.def("ItemWeight", py::overload_cast<BLayoutItem *>(&BSplitView::ItemWeight), "", py::arg("item"))
.def("SetItemWeight", py::overload_cast<int, float, bool>(&BSplitView::SetItemWeight), "", py::arg("index"), py::arg("weight"), py::arg("invalidateLayout"))
.def("SetItemWeight", py::overload_cast<BLayoutItem *, float>(&BSplitView::SetItemWeight), "", py::arg("item"), py::arg("weight"))
.def("IsCollapsible", &BSplitView::IsCollapsible, "", py::arg("index"))
.def("SetCollapsible", py::overload_cast<bool>(&BSplitView::SetCollapsible), "", py::arg("collapsible"))
.def("SetCollapsible", py::overload_cast<int, bool>(&BSplitView::SetCollapsible), "", py::arg("index"), py::arg("collapsible"))
.def("SetCollapsible", py::overload_cast<int, int, bool>(&BSplitView::SetCollapsible), "", py::arg("first"), py::arg("last"), py::arg("collapsible"))
.def("IsItemCollapsed", &BSplitView::IsItemCollapsed, "", py::arg("index"))
.def("SetItemCollapsed", &BSplitView::SetItemCollapsed, "", py::arg("index"), py::arg("collapsed"))
.def("AddChild", py::overload_cast<BView *, BView *>(&BSplitView::AddChild), "", py::arg("child"), py::arg("sibling")=NULL)
.def("AddChild", py::overload_cast<BView *, float>(&BSplitView::AddChild), "", py::arg("child"), py::arg("weight"))
.def("AddChild", py::overload_cast<int, BView *, float>(&BSplitView::AddChild), "", py::arg("index"), py::arg("child"), py::arg("weight"))
.def("AddChild", py::overload_cast<BLayoutItem *>(&BSplitView::AddChild), "", py::arg("child"))
.def("AddChild", py::overload_cast<BLayoutItem *, float>(&BSplitView::AddChild), "", py::arg("child"), py::arg("weight"))
.def("AddChild", py::overload_cast<int, BLayoutItem *, float>(&BSplitView::AddChild), "", py::arg("index"), py::arg("child"), py::arg("weight"))
.def("AttachedToWindow", &BSplitView::AttachedToWindow, "")
.def("Draw", &BSplitView::Draw, "", py::arg("updateRect"))
.def("DrawAfterChildren", &BSplitView::DrawAfterChildren, "", py::arg("updateRect"))
.def("MouseDown", &BSplitView::MouseDown, "", py::arg("where"))
.def("MouseUp", &BSplitView::MouseUp, "", py::arg("where"))
.def("MouseMoved", &BSplitView::MouseMoved, "", py::arg("where"), py::arg("transit"), py::arg("message"))
.def("MessageReceived", &BSplitView::MessageReceived, "", py::arg("message"))
.def("SetLayout", &BSplitView::SetLayout, "", py::arg("layout"))
.def("Archive", &BSplitView::Archive, "", py::arg("into"), py::arg("deep")=true)
.def_static("Instantiate", &BSplitView::Instantiate, "", py::arg("from"))
.def("Perform", &BSplitView::Perform, "", py::arg("d"), py::arg("arg"))
;


}
