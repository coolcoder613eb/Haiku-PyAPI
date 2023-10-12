#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/PopUpMenu.h>
#include <Menu.h>
#include <MenuItem.h>

namespace py = pybind11;


PYBIND11_MODULE(PopUpMenu,m)
{
py::class_<BPopUpMenu, BMenu, std::unique_ptr<BPopUpMenu,py::nodelete>>(m, "BPopUpMenu")
.def(py::init<const char *, bool, bool, menu_layout>(), "", py::arg("name"), py::arg("radioMode")=true, py::arg("labelFromMarked")=true, py::arg("layout")=B_ITEMS_IN_COLUMN)
.def(py::init<BMessage *>(), "", py::arg("data"))
.def("Archive", &BPopUpMenu::Archive, "", py::arg("archive"), py::arg("deep")=true)
.def_static("Instantiate", &BPopUpMenu::Instantiate, "", py::arg("archive"))
.def("Go", py::overload_cast<BPoint, bool, bool, bool>(&BPopUpMenu::Go), "", py::arg("where"), py::arg("autoInvoke")=false, py::arg("keepOpen")=false, py::arg("async")=false)
.def("Go", py::overload_cast<BPoint, bool, bool, BRect, bool>(&BPopUpMenu::Go), "", py::arg("where"), py::arg("autoInvoke"), py::arg("keepOpen"), py::arg("openRect"), py::arg("async")=false)
.def("MessageReceived", &BPopUpMenu::MessageReceived, "", py::arg("message"))
.def("MouseDown", &BPopUpMenu::MouseDown, "", py::arg("where"))
.def("MouseUp", &BPopUpMenu::MouseUp, "", py::arg("where"))
.def("MouseMoved", &BPopUpMenu::MouseMoved, "", py::arg("where"), py::arg("transit"), py::arg("dragMessage"))
.def("AttachedToWindow", &BPopUpMenu::AttachedToWindow, "")
.def("DetachedFromWindow", &BPopUpMenu::DetachedFromWindow, "")
.def("FrameMoved", &BPopUpMenu::FrameMoved, "", py::arg("newPosition"))
.def("FrameResized", &BPopUpMenu::FrameResized, "", py::arg("newWidth"), py::arg("newHeight"))
.def("ResolveSpecifier", &BPopUpMenu::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("form"), py::arg("property"))
.def("GetSupportedSuites", &BPopUpMenu::GetSupportedSuites, "", py::arg("data"))
.def("Perform", &BPopUpMenu::Perform, "", py::arg("code"), py::arg("_data"))
.def("ResizeToPreferred", &BPopUpMenu::ResizeToPreferred, "")
.def("GetPreferredSize", &BPopUpMenu::GetPreferredSize, "", py::arg("_width"), py::arg("_height"))
.def("MakeFocus", &BPopUpMenu::MakeFocus, "", py::arg("state")=true)
.def("AllAttached", &BPopUpMenu::AllAttached, "")
.def("AllDetached", &BPopUpMenu::AllDetached, "")
.def("SetAsyncAutoDestruct", &BPopUpMenu::SetAsyncAutoDestruct, "", py::arg("on"))
.def("AsyncAutoDestruct", &BPopUpMenu::AsyncAutoDestruct, "")
;


}
