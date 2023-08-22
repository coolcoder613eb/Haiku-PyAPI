#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/AbstractLayoutItem.h>
#include <Alignment.h>
#include <LayoutItem.h>
#include <Size.h>

namespace py = pybind11;


PYBIND11_MODULE(AbstractLayoutItem,m)
{
py::class_<BAbstractLayoutItem, BLayoutItem>(m, "BAbstractLayoutItem")
.def(py::init(), "")
.def(py::init<BMessage *>(), "", py::arg("from"))
.def("MinSize", &BAbstractLayoutItem::MinSize, "")
.def("MaxSize", &BAbstractLayoutItem::MaxSize, "")
.def("PreferredSize", &BAbstractLayoutItem::PreferredSize, "")
.def("Alignment", &BAbstractLayoutItem::Alignment, "")
.def("SetExplicitMinSize", &BAbstractLayoutItem::SetExplicitMinSize, "", py::arg("size"))
.def("SetExplicitMaxSize", &BAbstractLayoutItem::SetExplicitMaxSize, "", py::arg("size"))
.def("SetExplicitPreferredSize", &BAbstractLayoutItem::SetExplicitPreferredSize, "", py::arg("size"))
.def("SetExplicitAlignment", &BAbstractLayoutItem::SetExplicitAlignment, "", py::arg("alignment"))
.def("BaseMinSize", &BAbstractLayoutItem::BaseMinSize, "")
.def("BaseMaxSize", &BAbstractLayoutItem::BaseMaxSize, "")
.def("BasePreferredSize", &BAbstractLayoutItem::BasePreferredSize, "")
.def("BaseAlignment", &BAbstractLayoutItem::BaseAlignment, "")
.def("Archive", &BAbstractLayoutItem::Archive, "", py::arg("into"), py::arg("deep")=true)
.def("Perform", &BAbstractLayoutItem::Perform, "", py::arg("d"), py::arg("arg"))
;


}
