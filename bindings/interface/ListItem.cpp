#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/ListItem.h>
#include <Archivable.h>
#include <Rect.h>
#include <StringItem.h>

namespace py = pybind11;


PYBIND11_MODULE(ListItem,m)
{
py::class_<BListItem, BArchivable>(m, "BListItem")
.def(py::init<unsigned int, bool>(), "", py::arg("outlineLevel")=0, py::arg("expanded")=true)
.def(py::init<BMessage *>(), "", py::arg("archive"))
.def("Archive", &BListItem::Archive, "", py::arg("archive"), py::arg("deep")=true)
.def("Height", &BListItem::Height, "")
.def("Width", &BListItem::Width, "")
.def("IsSelected", &BListItem::IsSelected, "")
.def("Select", &BListItem::Select, "")
.def("Deselect", &BListItem::Deselect, "")
.def("SetEnabled", &BListItem::SetEnabled, "", py::arg("enabled"))
.def("IsEnabled", &BListItem::IsEnabled, "")
.def("SetHeight", &BListItem::SetHeight, "", py::arg("height"))
.def("SetWidth", &BListItem::SetWidth, "", py::arg("width"))
.def("DrawItem", &BListItem::DrawItem, "", py::arg("owner"), py::arg("frame"), py::arg("complete")=false)
.def("Update", &BListItem::Update, "", py::arg("owner"), py::arg("font"))
.def("IsExpanded", &BListItem::IsExpanded, "")
.def("SetExpanded", &BListItem::SetExpanded, "", py::arg("expanded"))
.def("OutlineLevel", &BListItem::OutlineLevel, "")
.def("SetOutlineLevel", &BListItem::SetOutlineLevel, "", py::arg("level"))
.def("Perform", &BListItem::Perform, "", py::arg("code"), py::arg("arg"))
;


}
