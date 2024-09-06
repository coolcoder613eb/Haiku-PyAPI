#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/GroupLayoutBuilder.h>
#include <GroupLayout.h>
#include <GroupView.h>
#include <List.h>

namespace py = pybind11;


PYBIND11_MODULE(GroupLayoutBuilder,m)
{
py::class_<BGroupLayoutBuilder>(m, "BGroupLayoutBuilder")
.def(py::init<orientation, float>(), "", py::arg("orientation")=B_HORIZONTAL, py::arg("spacing")=B_USE_DEFAULT_SPACING)
//.def(py::init<orientation, float>(), "", py::arg("orientation")=B_HORIZONTAL, py::arg("spacing")=-1002)
.def(py::init<BGroupLayout *>(), "", py::arg("layout"))
.def(py::init<BGroupView *>(), "", py::arg("view"))
.def("RootLayout", &BGroupLayoutBuilder::RootLayout, "")
.def("TopLayout", &BGroupLayoutBuilder::TopLayout, "")
//.def("GetTopLayout", &BGroupLayoutBuilder::GetTopLayout, "", py::arg("_layout")) //TODO
.def("GetTopLayout", [](BGroupLayoutBuilder &self){
	BGroupLayout* layout = nullptr;
	self.GetTopLayout(&layout);
	return std::make_tuple(std::ref(self), layout);
},"")
.def("TopView", &BGroupLayoutBuilder::TopView, "")
//.def("GetTopView", &BGroupLayoutBuilder::GetTopView, "", py::arg("_view")) //TODO
.def("GetTopView", [](BGroupLayoutBuilder &self) {
	BView* view = nullptr;
	self.GetTopView(&view);
	return std::make_tuple(std::ref(self), view);
	},"")
.def("Add", py::overload_cast<BView *>(&BGroupLayoutBuilder::Add), "", py::arg("view"))
.def("Add", py::overload_cast<BView *, float>(&BGroupLayoutBuilder::Add), "", py::arg("view"), py::arg("weight"))
.def("Add", py::overload_cast<BLayoutItem *>(&BGroupLayoutBuilder::Add), "", py::arg("item"))
.def("Add", py::overload_cast<BLayoutItem *, float>(&BGroupLayoutBuilder::Add), "", py::arg("item"), py::arg("weight"))
.def("AddGroup", &BGroupLayoutBuilder::AddGroup, "", py::arg("orientation"), py::arg("spacing")=B_USE_DEFAULT_SPACING, py::arg("weight")=1.0f)
//.def("AddGroup", &BGroupLayoutBuilder::AddGroup, "", py::arg("orientation"), py::arg("spacing")=-1002, py::arg("weight")=1.0f)
.def("End", &BGroupLayoutBuilder::End, "")
.def("AddGlue", &BGroupLayoutBuilder::AddGlue, "", py::arg("weight")=1.0f)
.def("AddStrut", &BGroupLayoutBuilder::AddStrut, "", py::arg("size"))
.def("SetInsets", &BGroupLayoutBuilder::SetInsets, "", py::arg("left"), py::arg("top"), py::arg("right"), py::arg("bottom"))
//.def("operatorBGroupLayout*", &BGroupLayoutBuilder::operatorBGroupLayout*, "")
.def("__call__", &BGroupLayoutBuilder::operator BGroupLayout *, "")
;


}
