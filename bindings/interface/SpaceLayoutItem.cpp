#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/SpaceLayoutItem.h>
#include <LayoutItem.h>

namespace py = pybind11;


PYBIND11_MODULE(SpaceLayoutItem,m)
{
py::class_<BSpaceLayoutItem, BLayoutItem>(m, "BSpaceLayoutItem")
.def(py::init<BSize, BSize, BSize, BAlignment>(), "", py::arg("minSize"), py::arg("maxSize"), py::arg("preferredSize"), py::arg("alignment"))
.def(py::init<BMessage *>(), "", py::arg("archive"))
.def_static("CreateGlue", &BSpaceLayoutItem::CreateGlue, "")
.def_static("CreateHorizontalStrut", &BSpaceLayoutItem::CreateHorizontalStrut, "", py::arg("width"))
.def_static("CreateVerticalStrut", &BSpaceLayoutItem::CreateVerticalStrut, "", py::arg("height"))
.def("MinSize", &BSpaceLayoutItem::MinSize, "")
.def("MaxSize", &BSpaceLayoutItem::MaxSize, "")
.def("PreferredSize", &BSpaceLayoutItem::PreferredSize, "")
.def("Alignment", &BSpaceLayoutItem::Alignment, "")
.def("SetExplicitMinSize", &BSpaceLayoutItem::SetExplicitMinSize, "", py::arg("size"))
.def("SetExplicitMaxSize", &BSpaceLayoutItem::SetExplicitMaxSize, "", py::arg("size"))
.def("SetExplicitPreferredSize", &BSpaceLayoutItem::SetExplicitPreferredSize, "", py::arg("size"))
.def("SetExplicitAlignment", &BSpaceLayoutItem::SetExplicitAlignment, "", py::arg("alignment"))
.def("IsVisible", &BSpaceLayoutItem::IsVisible, "")
.def("SetVisible", &BSpaceLayoutItem::SetVisible, "", py::arg("visible"))
.def("Frame", &BSpaceLayoutItem::Frame, "")
.def("SetFrame", &BSpaceLayoutItem::SetFrame, "", py::arg("frame"))
.def("Archive", &BSpaceLayoutItem::Archive, "", py::arg("into"), py::arg("deep")=true)
.def_static("Instantiate", &BSpaceLayoutItem::Instantiate, "", py::arg("from"))
;


}
