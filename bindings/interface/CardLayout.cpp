#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/CardLayout.h>
#include <AbstractLayout.h>

namespace py = pybind11;


PYBIND11_MODULE(CardLayout,m)
{
py::class_<BCardLayout, BAbstractLayout>(m, "BCardLayout")
.def(py::init(), "")
.def(py::init<BMessage *>(), "", py::arg("from"))
.def("VisibleItem", &BCardLayout::VisibleItem, "")
.def("VisibleIndex", &BCardLayout::VisibleIndex, "")
.def("SetVisibleItem", py::overload_cast<int>(&BCardLayout::SetVisibleItem), "", py::arg("index"))
.def("SetVisibleItem", py::overload_cast<BLayoutItem *>(&BCardLayout::SetVisibleItem), "", py::arg("item"))
.def("BaseMinSize", &BCardLayout::BaseMinSize, "")
.def("BaseMaxSize", &BCardLayout::BaseMaxSize, "")
.def("BasePreferredSize", &BCardLayout::BasePreferredSize, "")
.def("BaseAlignment", &BCardLayout::BaseAlignment, "")
.def("HasHeightForWidth", &BCardLayout::HasHeightForWidth, "")
.def("GetHeightForWidth", &BCardLayout::GetHeightForWidth, "", py::arg("width"), py::arg("min"), py::arg("max"), py::arg("preferred"))
.def("Archive", &BCardLayout::Archive, "", py::arg("into"), py::arg("deep")=true)
.def_static("Instantiate", &BCardLayout::Instantiate, "", py::arg("from"))
.def("Perform", &BCardLayout::Perform, "", py::arg("d"), py::arg("arg"))
;


}
