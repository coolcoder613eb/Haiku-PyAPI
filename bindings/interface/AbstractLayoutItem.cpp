#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/AbstractLayoutItem.h>
#include <Alignment.h>
#include <LayoutItem.h>
#include <Size.h>

namespace py = pybind11;

class PyBAbstractLayoutItem : public BAbstractLayoutItem{
	public:
        using BAbstractLayoutItem::BAbstractLayoutItem;
        BSize			MinSize() override {
        	PYBIND11_OVERLOAD(BSize, BAbstractLayoutItem, MinSize);
        }
        BSize			MaxSize() override {
        	PYBIND11_OVERLOAD(BSize, BAbstractLayoutItem, MaxSize);
        }
        BSize			PreferredSize() override {
        	PYBIND11_OVERLOAD(BSize, BAbstractLayoutItem, PreferredSize);
        }
        BAlignment		Alignment() override {
        	PYBIND11_OVERLOAD(BAlignment, BAbstractLayoutItem, Alignment);
        }
        void			SetExplicitMinSize(BSize size) override {
        	PYBIND11_OVERLOAD(void, BAbstractLayoutItem, SetExplicitMinSize, size);
        }
        void			SetExplicitMaxSize(BSize size) override {
        	PYBIND11_OVERLOAD(void, BAbstractLayoutItem, SetExplicitMaxSize, size);
        }
        void			SetExplicitPreferredSize(BSize size) override {
        	PYBIND11_OVERLOAD(void, BAbstractLayoutItem, SetExplicitPreferredSize, size);
        }
        void			SetExplicitAlignment(BAlignment alignment) override {
        	PYBIND11_OVERLOAD(void, BAbstractLayoutItem, SetExplicitAlignment, alignment);
        }
        BSize			BaseMinSize() override {
        	PYBIND11_OVERLOAD(BSize, BAbstractLayoutItem, BaseMinSize);
        }
        BSize			BaseMaxSize() override {
        	PYBIND11_OVERLOAD(BSize, BAbstractLayoutItem, BaseMaxSize);
        }
        BSize			BasePreferredSize() override {
        	PYBIND11_OVERLOAD(BSize, BAbstractLayoutItem, BasePreferredSize);
        }
        BAlignment		BaseAlignment() override {
        	PYBIND11_OVERLOAD(BAlignment, BAbstractLayoutItem, BaseAlignment);
        }
        status_t		Archive(BMessage* into, bool deep = true) const override {
        	PYBIND11_OVERLOAD(status_t, BAbstractLayoutItem, Archive, into, deep);
        }
        status_t		Perform(perform_code d, void* arg) override {
        	PYBIND11_OVERLOAD(status_t, BAbstractLayoutItem, Perform, d, arg);
        }
};

PYBIND11_MODULE(AbstractLayoutItem,m)
{
py::class_<BAbstractLayoutItem, PyBAbstractLayoutItem, BLayoutItem>(m, "BAbstractLayoutItem");
}
