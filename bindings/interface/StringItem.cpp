#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/StringItem.h>
#include <Font.h>
#include <ListItem.h>
#include <View.h>

namespace py = pybind11;


PYBIND11_MODULE(StringItem,m)
{
py::class_<BStringItem, BListItem>(m, "BStringItem")
.def(py::init<const char *, unsigned int, bool>(), "", py::arg("text"), py::arg("outlineLevel")=0, py::arg("expanded")=true)
.def(py::init<BMessage *>(), "", py::arg("archive"))
.def_static("Instantiate", &BStringItem::Instantiate, "", py::arg("archive"))
.def("Archive", &BStringItem::Archive, "", py::arg("archive"), py::arg("deep")=true)
.def("DrawItem", &BStringItem::DrawItem, "", py::arg("owner"), py::arg("frame"), py::arg("complete")=false)
.def("SetText", &BStringItem::SetText, "", py::arg("text"))
.def("Text", &BStringItem::Text, "")
.def("Update", &BStringItem::Update, "", py::arg("owner"), py::arg("font"))
.def("Perform", &BStringItem::Perform, "", py::arg("code"), py::arg("arg"))
;


}
