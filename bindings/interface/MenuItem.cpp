#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/MenuItem.h>
#include <Archivable.h>
#include <InterfaceDefs.h>
#include <Invoker.h>
#include <Menu.h>
#include <SeparatorItem.h>

namespace py = pybind11;
using namespace BPrivate;

PYBIND11_MODULE(MenuItem,m)
{
m.attr("MenuItemPrivate") = MenuItemPrivate;

py::class_<BMenuItem, BArchivable, BInvoker>(m, "BMenuItem")
.def(py::init<const char *, BMessage *, char, unsigned int>(), "", py::arg("label"), py::arg("message"), py::arg("shortcut")=0, py::arg("modifiers")=0)
.def(py::init<BMenu *, BMessage *>(), "", py::arg("menu"), py::arg("message")=NULL)
.def(py::init<BMessage *>(), "", py::arg("data"))
.def_static("Instantiate", &BMenuItem::Instantiate, "", py::arg("archive"))
.def("Archive", &BMenuItem::Archive, "", py::arg("archive"), py::arg("deep")=true)
.def("SetLabel", &BMenuItem::SetLabel, "", py::arg("name"))
.def("SetEnabled", &BMenuItem::SetEnabled, "", py::arg("enable"))
.def("SetMarked", &BMenuItem::SetMarked, "", py::arg("mark"))
.def("SetTrigger", &BMenuItem::SetTrigger, "", py::arg("trigger"))
.def("SetShortcut", &BMenuItem::SetShortcut, "", py::arg("shortcut"), py::arg("modifiers"))
.def("Label", &BMenuItem::Label, "")
.def("IsEnabled", &BMenuItem::IsEnabled, "")
.def("IsMarked", &BMenuItem::IsMarked, "")
.def("Trigger", &BMenuItem::Trigger, "")
.def("Shortcut", &BMenuItem::Shortcut, "", py::arg("_modifiers")=NULL)
.def("Submenu", &BMenuItem::Submenu, "")
.def("Menu", &BMenuItem::Menu, "")
.def("Frame", &BMenuItem::Frame, "")
;


}
