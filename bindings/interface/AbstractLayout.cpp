#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/AbstractLayout.h>
#include <Alignment.h>
#include <Layout.h>
#include <Size.h>

namespace py = pybind11;


PYBIND11_MODULE(AbstractLayout,m)
{
py::class_<BAbstractLayout, BLayout>(m, "BAbstractLayout")
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
.def("Perform", &BAbstractLayout::Perform, "", py::arg("d"), py::arg("arg"))
;


}
