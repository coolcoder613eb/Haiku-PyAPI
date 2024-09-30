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
#include <View.h>
#include <LayoutContext.h>

namespace py = pybind11;

class PyBLayout : public BLayout{
	public:
        using BLayout::BLayout;
        BView*			View() override {
            PYBIND11_OVERLOAD(BView*, BLayout, View);
        }
        BLayoutItem*			AddView(BView* child) override {
            PYBIND11_OVERLOAD(BLayoutItem*, BLayout, AddView, child);
        }
        BLayoutItem*			AddView(int32 index, BView* child) override {
            PYBIND11_OVERLOAD(BLayoutItem*, BLayout, AddView, index, child);
        }
        bool			AddItem(BLayoutItem* item) override {
            PYBIND11_OVERLOAD(bool, BLayout, AddItem, item);
        }
        bool			AddItem(int32 index, BLayoutItem* item) override {
            PYBIND11_OVERLOAD(bool, BLayout, AddItem, index, item);
        }
        bool			RemoveView(BView* child) override {
            PYBIND11_OVERLOAD(bool, BLayout, RemoveView, child);
        }
        bool			RemoveItem(BLayoutItem* item) override {
            PYBIND11_OVERLOAD(bool, BLayout, RemoveItem, item);
        }
        BLayoutItem*		RemoveItem(int32 index) override {
            PYBIND11_OVERLOAD(BLayoutItem*, BLayout, RemoveItem, index);
        }
        void				InvalidateLayout(bool children = false) override {
            PYBIND11_OVERLOAD(void, BLayout, InvalidateLayout, children);
        }
        void				Relayout(bool immediate = false) override {
            PYBIND11_OVERLOAD(void, BLayout, Relayout, immediate);
        }
        status_t			Archive(BMessage* into, bool deep = true) const override {
            PYBIND11_OVERLOAD(status_t, BLayout, Archive, into, deep);
        }
        status_t			Perform(perform_code d, void* arg) override {
            PYBIND11_OVERLOAD(status_t, BLayout, Perform, d, arg);
        }
        BSize				MinSize() override {
            PYBIND11_OVERLOAD_PURE(BSize, BLayout, MinSize);
        }
        BSize				MaxSize() override {
            PYBIND11_OVERLOAD_PURE(BSize, BLayout, MaxSize);
        }
        BSize				PreferredSize() override {
            PYBIND11_OVERLOAD_PURE(BSize, BLayout, PreferredSize);
        }
        BAlignment			Alignment() override {
            PYBIND11_OVERLOAD_PURE(BAlignment, BLayout, Alignment);
        }
        void				SetExplicitMinSize(BSize size) override {
            PYBIND11_OVERLOAD_PURE(void, BLayout, SetExplicitMinSize, size);
        }
        void				SetExplicitMaxSize(BSize size) override {
            PYBIND11_OVERLOAD_PURE(void, BLayout, SetExplicitMaxSize, size);
        }
        void				SetExplicitPreferredSize(BSize size) override {
            PYBIND11_OVERLOAD_PURE(void, BLayout, SetExplicitPreferredSize, size);
        }
        void				SetExplicitAlignment(BAlignment alignment) override {
            PYBIND11_OVERLOAD_PURE(void, BLayout, SetExplicitAlignment, alignment);
        }
        bool				IsVisible() override {
            PYBIND11_OVERLOAD_PURE(bool, BLayout, IsVisible);
        }
        void				SetVisible(bool visible) override {
            PYBIND11_OVERLOAD_PURE(void, BLayout, SetVisible, visible);
        }
        BRect				Frame() override {
            PYBIND11_OVERLOAD_PURE(BRect, BLayout, Frame);
        }
        void				SetFrame(BRect frame) override {
            PYBIND11_OVERLOAD_PURE(void, BLayout, SetFrame, frame);
        }
        void				DoLayout() override {
            PYBIND11_OVERLOAD_PURE(void, BLayout, DoLayout);
        }
};

PYBIND11_MODULE(Layout,m)
{
py::class_<BLayout,PyBLayout,BLayoutItem>(m, "BLayout")
.def(py::init(), "")
.def(py::init<BMessage *>(), "", py::arg("archive"))
.def("Owner", &BLayout::Owner, "")
.def("TargetView", &BLayout::TargetView, "")
.def("View", &BLayout::View, "")
.def("AddView", py::overload_cast<BView *>(&BLayout::AddView), "", py::arg("child"))
.def("AddView", py::overload_cast<int32, BView *>(&BLayout::AddView), "", py::arg("index"), py::arg("child"))
.def("AddItem", py::overload_cast<BLayoutItem *>(&BLayout::AddItem), "", py::arg("item"))
.def("AddItem", py::overload_cast<int32, BLayoutItem *>(&BLayout::AddItem), "", py::arg("index"), py::arg("item"))
.def("RemoveView", &BLayout::RemoveView, "", py::arg("child"))
.def("RemoveItem", py::overload_cast<BLayoutItem *>(&BLayout::RemoveItem), "", py::arg("item"))
.def("RemoveItem", py::overload_cast<int32>(&BLayout::RemoveItem), "", py::arg("index"))
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
.def("Perform", &BLayout::Perform, "", py::arg("d"), py::arg("arg"));
}
