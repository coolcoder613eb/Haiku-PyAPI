#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/AbstractLayout.h>
#include <Alignment.h>
#include <Layout.h>
#include <Size.h>

namespace py = pybind11;

class PyBAbstractLayout : public BAbstractLayout{
	public:
        using BAbstractLayout::BAbstractLayout;
        BSize			MinSize() override {
        	PYBIND11_OVERLOAD(BSize, BAbstractLayout, MinSize);
        }
        BSize			MaxSize() override {
        	PYBIND11_OVERLOAD(BSize, BAbstractLayout, MaxSize);
        }
        BSize			PreferredSize() override {
        	PYBIND11_OVERLOAD(BSize, BAbstractLayout, PreferredSize);
        }
        BAlignment		Alignment() override {
        	PYBIND11_OVERLOAD(BAlignment, BAbstractLayout, Alignment);
        }
        void			SetExplicitMinSize(BSize size) override {
        	PYBIND11_OVERLOAD(void, BAbstractLayout, SetExplicitMinSize, size);
        }
        void			SetExplicitMaxSize(BSize size) override {
        	PYBIND11_OVERLOAD(void, BAbstractLayout, SetExplicitMaxSize, size);
        }
        void			SetExplicitPreferredSize(BSize size) override {
        	PYBIND11_OVERLOAD(void, BAbstractLayout, SetExplicitPreferredSize, size);
        }
        void			SetExplicitAlignment(BAlignment alignment) override {
        	PYBIND11_OVERLOAD(void, BAbstractLayout, SetExplicitAlignment, alignment);
        }
        BSize			BaseMinSize() override {
        	PYBIND11_OVERLOAD(BSize, BAbstractLayout, BaseMinSize);
        }
        BSize			BaseMaxSize() override {
        	PYBIND11_OVERLOAD(BSize, BAbstractLayout, BaseMaxSize);
        }
        BSize			BasePreferredSize() override {
        	PYBIND11_OVERLOAD(BSize, BAbstractLayout, BasePreferredSize);
        }
        BAlignment		BaseAlignment() override {
        	PYBIND11_OVERLOAD(BAlignment, BAbstractLayout, BaseAlignment);
        }
        BRect			Frame() override {
        	PYBIND11_OVERLOAD(BRect, BAbstractLayout, Frame);
        }
        void			SetFrame(BRect frame) override {
        	PYBIND11_OVERLOAD(void, BAbstractLayout, SetFrame, frame);
        }
        bool			IsVisible() override {
        	PYBIND11_OVERLOAD(bool, BAbstractLayout, IsVisible);
        }
        void			SetVisible(bool visible) override {
        	PYBIND11_OVERLOAD(void, BAbstractLayout, SetVisible, visible);
        }
        status_t		Archive(BMessage* into, bool deep = true) const override {
        	PYBIND11_OVERLOAD(status_t, BAbstractLayout, Archive, into, deep);
        }
        status_t		Perform(perform_code d, void* arg) override {
        	PYBIND11_OVERLOAD(status_t, BAbstractLayout, Perform, d, arg);
        }
        void            DoLayout() override {
        	PYBIND11_OVERLOAD_PURE(void, BAbstractLayout, DoLayout);
        }
};

PYBIND11_MODULE(AbstractLayout,m)
{
py::class_<BAbstractLayout,PyBAbstractLayout, BLayout>(m, "BAbstractLayout")
.def(py::init(), "")
.def(py::init<BMessage *>(), "", py::arg("from"))
.def("MinSize", &BAbstractLayout::MinSize, "")
.def("MaxSize", &BAbstractLayout::MaxSize, "")
.def("PreferredSize", &BAbstractLayout::PreferredSize, "")
.def("Alignment", &BAbstractLayout::Alignment, "")
.def("SetExplicitMinSize", &BAbstractLayout::SetExplicitMinSize, "", py::arg("size"))
.def("SetExplicitMaxSize", &BAbstractLayout::SetExplicitMaxSize, "", py::arg("size"))
.def("SetExplicitPreferredSize", &BAbstractLayout::SetExplicitPreferredSize, "", py::arg("size"))
.def("SetExplicitAlignment", &BAbstractLayout::SetExplicitAlignment, "", py::arg("alignment"))
.def("BaseMinSize", &BAbstractLayout::BaseMinSize, "")
.def("BaseMaxSize", &BAbstractLayout::BaseMaxSize, "")
.def("BasePreferredSize", &BAbstractLayout::BasePreferredSize, "")
.def("BaseAlignment", &BAbstractLayout::BaseAlignment, "")
.def("Frame", &BAbstractLayout::Frame, "")
.def("SetFrame", &BAbstractLayout::SetFrame, "", py::arg("frame"))
.def("IsVisible", &BAbstractLayout::IsVisible, "")
.def("SetVisible", &BAbstractLayout::SetVisible, "", py::arg("visible"))
.def("Archive", &BAbstractLayout::Archive, "", py::arg("into"), py::arg("deep")=true)
.def("Perform", &BAbstractLayout::Perform, "", py::arg("d"), py::arg("arg"));
}
