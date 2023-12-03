#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/SeparatorItem.h>
#include <MenuItem.h>

namespace py = pybind11;

class PyBSeparatorItem : public BSeparatorItem{
	public:
        using BSeparatorItem::BSeparatorItem;
        status_t		Archive(BMessage* data, bool deep = true) const override {
        	PYBIND11_OVERLOAD(status_t, BSeparatorItem, Archive, data, deep);
        }
        void			SetEnabled(bool enable) override {
        	PYBIND11_OVERLOAD(void, BSeparatorItem, SetEnabled, enable);
        }
};

PYBIND11_MODULE(SeparatorItem,m)
{
py::class_<BSeparatorItem, PyBSeparatorItem, BMenuItem, std::unique_ptr<BSeparatorItem, py::nodelete>>(m, "BSeparatorItem")
.def(py::init(), "")
.def(py::init<BMessage *>(), "", py::arg("data"))
.def_static("Instantiate", &BSeparatorItem::Instantiate, "", py::arg("data"))
.def("Archive", &BSeparatorItem::Archive, "", py::arg("data"), py::arg("deep")=true)
.def("SetEnabled", &BSeparatorItem::SetEnabled, "", py::arg("enable"))
;

}
