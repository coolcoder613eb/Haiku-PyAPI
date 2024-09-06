#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/LayoutItem.h>
#include <Alignment.h>
#include <Archivable.h>
#include <Rect.h>
#include <Size.h>
#include <View.h>
#include <Layout.h>

namespace py = pybind11;

class PyBLayoutItem : public BLayoutItem{
	public:
        using BLayoutItem::BLayoutItem;
        BSize				MinSize() override {
        	PYBIND11_OVERLOAD_PURE(BSize, BLayoutItem, MinSize);
        }
        BSize				MaxSize() override {
        	PYBIND11_OVERLOAD_PURE(BSize, BLayoutItem, MaxSize);
        }
        BSize				PreferredSize() override {
        	PYBIND11_OVERLOAD_PURE(BSize, BLayoutItem, PreferredSize);
        }
        BAlignment				Alignment() override {
        	PYBIND11_OVERLOAD_PURE(BAlignment, BLayoutItem, Alignment);
        }
        void				SetExplicitMinSize(BSize size) override {
        	PYBIND11_OVERLOAD_PURE(void, BLayoutItem, SetExplicitMinSize, size);
        }
        void				SetExplicitMaxSize(BSize size) override {
        	PYBIND11_OVERLOAD_PURE(void, BLayoutItem, SetExplicitMaxSize, size);
        }
        void				SetExplicitPreferredSize(BSize size) override {
        	PYBIND11_OVERLOAD_PURE(void, BLayoutItem, SetExplicitPreferredSize, size);
        }
        void				SetExplicitAlignment(BAlignment alignment) override {
        	PYBIND11_OVERLOAD_PURE(void, BLayoutItem, SetExplicitAlignment, alignment);
        }
        bool				IsVisible() override {
        	PYBIND11_OVERLOAD_PURE(bool, BLayoutItem, IsVisible);
        }
        void				SetVisible(bool visible) override {
        	PYBIND11_OVERLOAD_PURE(void, BLayoutItem, SetVisible, visible);
        }
        BRect				Frame() override {
        	PYBIND11_OVERLOAD_PURE(BRect, BLayoutItem, Frame);
        }
        void				SetFrame(BRect frame) override {
        	PYBIND11_OVERLOAD_PURE(void, BLayoutItem, SetFrame, frame);
        }
        bool				HasHeightForWidth() override {
        	PYBIND11_OVERLOAD(bool, BLayoutItem, HasHeightForWidth);
        }
        void				GetHeightForWidth(float width, float* min, float* max, float* preferred) override {
        	PYBIND11_OVERLOAD(void, BLayoutItem, GetHeightForWidth, width, min, max, preferred);
        }
        BView*				View() override {
        	PYBIND11_OVERLOAD(BView*, BLayoutItem, View);
        }
        void				InvalidateLayout(bool children = false) override {
        	PYBIND11_OVERLOAD(void, BLayoutItem, InvalidateLayout, children);
        }
        void				Relayout(bool immediate = false) override {
        	PYBIND11_OVERLOAD(void, BLayoutItem, Relayout, immediate);
        }
        status_t			Archive(BMessage* into, bool deep = true) const override {
        	PYBIND11_OVERLOAD(status_t, BLayoutItem, Archive, into, deep);
        }
        status_t			Perform(perform_code d, void* arg) override {
        	PYBIND11_OVERLOAD(status_t, BLayoutItem, Perform, d, arg);
        }
};

PYBIND11_MODULE(LayoutItem,m)
{
py::class_<BLayoutItem,PyBLayoutItem,std::unique_ptr<BLayoutItem, py::nodelete>>(m, "BLayoutItem")
.def(py::init(), "")
.def(py::init<BMessage *>(), "", py::arg("from"))
.def("Layout", &BLayoutItem::Layout, "")
.def("RemoveSelf", &BLayoutItem::RemoveSelf, "")
.def("MinSize", &BLayoutItem::MinSize, "")
.def("MaxSize", &BLayoutItem::MaxSize, "")
.def("PreferredSize", &BLayoutItem::PreferredSize, "")
.def("Alignment", &BLayoutItem::Alignment, "")
.def("SetExplicitMinSize", &BLayoutItem::SetExplicitMinSize, "", py::arg("size"))
.def("SetExplicitMaxSize", &BLayoutItem::SetExplicitMaxSize, "", py::arg("size"))
.def("SetExplicitPreferredSize", &BLayoutItem::SetExplicitPreferredSize, "", py::arg("size"))
.def("SetExplicitSize", &BLayoutItem::SetExplicitSize, "", py::arg("size"))
.def("SetExplicitAlignment", &BLayoutItem::SetExplicitAlignment, "", py::arg("alignment"))
.def("IsVisible", &BLayoutItem::IsVisible, "")
.def("SetVisible", &BLayoutItem::SetVisible, "", py::arg("visible"))
.def("Frame", &BLayoutItem::Frame, "")
.def("SetFrame", &BLayoutItem::SetFrame, "", py::arg("frame"))
.def("HasHeightForWidth", &BLayoutItem::HasHeightForWidth, "")
.def("GetHeightForWidth", &BLayoutItem::GetHeightForWidth, "", py::arg("width"), py::arg("min"), py::arg("max"), py::arg("preferred"))
.def("View", &BLayoutItem::View, "")
.def("InvalidateLayout", &BLayoutItem::InvalidateLayout, "", py::arg("children")=false)
.def("Relayout", &BLayoutItem::Relayout, "", py::arg("immediate")=false)
.def("LayoutData", &BLayoutItem::LayoutData, "")
.def("SetLayoutData", &BLayoutItem::SetLayoutData, "", py::arg("data"))
.def("AlignInFrame", &BLayoutItem::AlignInFrame, "", py::arg("frame"))
.def("Archive", &BLayoutItem::Archive, "", py::arg("into"), py::arg("deep")=true)
.def("Perform", &BLayoutItem::Perform, "", py::arg("d"), py::arg("arg"))
;
}
