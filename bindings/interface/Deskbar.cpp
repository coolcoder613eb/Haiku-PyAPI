#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/Deskbar.h>
#include <Rect.h>

namespace py = pybind11;


PYBIND11_MODULE(Deskbar,m)
{
py::enum_<deskbar_location>(m, "deskbar_location", "")
.value("B_DESKBAR_TOP", deskbar_location::B_DESKBAR_TOP, "")
.value("B_DESKBAR_BOTTOM", deskbar_location::B_DESKBAR_BOTTOM, "")
.value("B_DESKBAR_LEFT_TOP", deskbar_location::B_DESKBAR_LEFT_TOP, "")
.value("B_DESKBAR_RIGHT_TOP", deskbar_location::B_DESKBAR_RIGHT_TOP, "")
.value("B_DESKBAR_LEFT_BOTTOM", deskbar_location::B_DESKBAR_LEFT_BOTTOM, "")
.value("B_DESKBAR_RIGHT_BOTTOM", deskbar_location::B_DESKBAR_RIGHT_BOTTOM, "")
.export_values();

py::class_<BDeskbar>(m, "BDeskbar")
.def(py::init(), "")
.def("IsRunning", &BDeskbar::IsRunning, "")
.def("Frame", &BDeskbar::Frame, "")
.def("Location", &BDeskbar::Location, "", py::arg("_isExpanded")=NULL)
.def("SetLocation", &BDeskbar::SetLocation, "", py::arg("location"), py::arg("expanded")=false)
.def("IsExpanded", &BDeskbar::IsExpanded, "")
.def("Expand", &BDeskbar::Expand, "", py::arg("expand"))
.def("IsAlwaysOnTop", &BDeskbar::IsAlwaysOnTop, "")
.def("SetAlwaysOnTop", &BDeskbar::SetAlwaysOnTop, "", py::arg("alwaysOnTop"))
.def("IsAutoRaise", &BDeskbar::IsAutoRaise, "")
.def("SetAutoRaise", &BDeskbar::SetAutoRaise, "", py::arg("autoRaise"))
.def("IsAutoHide", &BDeskbar::IsAutoHide, "")
.def("SetAutoHide", &BDeskbar::SetAutoHide, "", py::arg("autoHide"))
.def("GetItemInfo", py::overload_cast<int, const char * *>(&BDeskbar::GetItemInfo), "", py::arg("id"), py::arg("_name"))
.def("GetItemInfo", py::overload_cast<const char *, int>(&BDeskbar::GetItemInfo), "", py::arg("name"), py::arg("_id"))
.def("HasItem", py::overload_cast<int>(&BDeskbar::HasItem), "", py::arg("id"))
.def("HasItem", py::overload_cast<const char *>(&BDeskbar::HasItem), "", py::arg("name"))
.def("CountItems", &BDeskbar::CountItems, "")
.def("MaxItemWidth", &BDeskbar::MaxItemWidth, "")
.def("MaxItemHeight", &BDeskbar::MaxItemHeight, "")
.def("AddItem", py::overload_cast<BView *, int>(&BDeskbar::AddItem), "", py::arg("archivableView"), py::arg("_id")=NULL)
.def("AddItem", py::overload_cast<entry_ref *, int>(&BDeskbar::AddItem), "", py::arg("addOn"), py::arg("_id")=NULL)
.def("RemoveItem", py::overload_cast<int>(&BDeskbar::RemoveItem), "", py::arg("id"))
.def("RemoveItem", py::overload_cast<const char *>(&BDeskbar::RemoveItem), "", py::arg("name"))
;


}
