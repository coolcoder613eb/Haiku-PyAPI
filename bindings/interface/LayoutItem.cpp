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


PYBIND11_MODULE(LayoutItem,m)
{
py::class_<BLayoutItem, BArchivable>(m, "BLayoutItem")
//.def(py::init(), "")
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
