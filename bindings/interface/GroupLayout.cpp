#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/GroupLayout.h>
#include <TwoDimensionalLayout.h>
#include <View.h>

namespace py = pybind11;

class PyBGroupLayout : public BGroupLayout{
	public:
        using BGroupLayout::BGroupLayout;
        BLayoutItem*		AddView(BView* child) override {
        	PYBIND11_OVERLOAD(BLayoutItem*, BGroupLayout, AddView, child);
        }
        BLayoutItem*		AddView(int32 index, BView* child) override {
        	PYBIND11_OVERLOAD(BLayoutItem*, BGroupLayout, AddView, index, child);
        }
        BLayoutItem*		AddView(BView* child, float weight) override {
        	PYBIND11_OVERLOAD(BLayoutItem*, BGroupLayout, AddView, child, weight);
        }
        BLayoutItem*		AddView(int32 index, BView* child, float weight) override {
        	PYBIND11_OVERLOAD(BLayoutItem*, BGroupLayout, AddView, index, child, weight);
        }
        bool				AddItem(BLayoutItem* item) override {
        	PYBIND11_OVERLOAD(bool, BGroupLayout, AddItem, item);
        }
        bool				AddItem(int32 index, BLayoutItem* item) override {
        	PYBIND11_OVERLOAD(bool, BGroupLayout, AddItem, index, item);
        }
        bool				AddItem(BLayoutItem* item, float weight) override {
        	PYBIND11_OVERLOAD(bool, BGroupLayout, AddItem, item, weight);
        }
        bool				AddItem(int32 index, BLayoutItem* item, float weight) override {
        	PYBIND11_OVERLOAD(bool, BGroupLayout, AddItem, index, item, weight);
        }
        status_t			Archive(BMessage* into, bool deep = true) const override {
        	PYBIND11_OVERLOAD(status_t, BGroupLayout, Archive, into, deep);
        }
        status_t			Perform(perform_code d, void* arg) override {
        	PYBIND11_OVERLOAD(status_t, BGroupLayout, Perform, d, arg);
        }
};

PYBIND11_MODULE(GroupLayout,m)
{
py::class_<BGroupLayout, PyBGroupLayout, BTwoDimensionalLayout>(m, "BGroupLayout")
//.def(py::init<orientation, float>(), "", py::arg("orientation"), py::arg("spacing")=B_USE_DEFAULT_SPACING)
.def(py::init<orientation, float>(), "", py::arg("orientation"), py::arg("spacing")=-1002)
.def(py::init<BMessage *>(), "", py::arg("from"))
.def("Spacing", &BGroupLayout::Spacing, "")
.def("SetSpacing", &BGroupLayout::SetSpacing, "", py::arg("spacing"))
.def("Orientation", &BGroupLayout::Orientation, "")
.def("SetOrientation", &BGroupLayout::SetOrientation, "", py::arg("orientation"))
.def("ItemWeight", &BGroupLayout::ItemWeight, "", py::arg("index"))
.def("SetItemWeight", &BGroupLayout::SetItemWeight, "", py::arg("index"), py::arg("weight"))
.def("AddView", py::overload_cast<BView *>(&BGroupLayout::AddView), "", py::arg("child"))
.def("AddView", py::overload_cast<int32, BView *>(&BGroupLayout::AddView), "", py::arg("index"), py::arg("child"))
.def("AddView", py::overload_cast<BView *, float>(&BGroupLayout::AddView), "", py::arg("child"), py::arg("weight"))
.def("AddView", py::overload_cast<int32, BView *, float>(&BGroupLayout::AddView), "", py::arg("index"), py::arg("child"), py::arg("weight"))
.def("AddItem", py::overload_cast<BLayoutItem *>(&BGroupLayout::AddItem), "", py::arg("item"))
.def("AddItem", py::overload_cast<int32, BLayoutItem *>(&BGroupLayout::AddItem), "", py::arg("index"), py::arg("item"))
.def("AddItem", py::overload_cast<BLayoutItem *, float>(&BGroupLayout::AddItem), "", py::arg("item"), py::arg("weight"))
.def("AddItem", py::overload_cast<int32, BLayoutItem *, float>(&BGroupLayout::AddItem), "", py::arg("index"), py::arg("item"), py::arg("weight"))
.def("Archive", &BGroupLayout::Archive, "", py::arg("into"), py::arg("deep")=true)
.def_static("Instantiate", &BGroupLayout::Instantiate, "", py::arg("from"))
.def("Perform", &BGroupLayout::Perform, "", py::arg("d"), py::arg("arg"))
;


}
