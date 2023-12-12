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
};

PYBIND11_MODULE(AbstractLayout,m)
{
py::class_<BAbstractLayout,PyBAbstractLayout, BLayout>(m, "BAbstractLayout");
}
