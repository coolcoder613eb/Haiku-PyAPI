#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/OptionControl.h>
#include <Control.h>

namespace py = pybind11;


PYBIND11_MODULE(OptionControl,m)
{
m.attr("B_OPTION_CONTROL_VALUE") = "_BMV";

py::class_<BOptionControl, BControl>(m, "BOptionControl")
.def(py::init<BRect, const char *, const char *, BMessage *, unsigned int, unsigned int>(), "", py::arg("frame"), py::arg("name"), py::arg("label"), py::arg("message"), py::arg("resizeMask")=B_FOLLOW_LEFT_TOP, py::arg("flags")=B_WILL_DRAW)
.def(py::init<const char *, const char *, BMessage *, unsigned int>(), "", py::arg("name"), py::arg("label"), py::arg("message"), py::arg("flags")=B_WILL_DRAW)
.def("MessageReceived", &BOptionControl::MessageReceived, "", py::arg("message"))
.def("AddOption", &BOptionControl::AddOption, "", py::arg("name"), py::arg("value"))
.def("GetOptionAt", &BOptionControl::GetOptionAt, "", py::arg("index"), py::arg("_name"), py::arg("_value"))
.def("RemoveOptionAt", &BOptionControl::RemoveOptionAt, "", py::arg("index"))
.def("CountOptions", &BOptionControl::CountOptions, "")
.def("AddOptionAt", &BOptionControl::AddOptionAt, "", py::arg("name"), py::arg("value"), py::arg("index"))
.def("SelectedOption", &BOptionControl::SelectedOption, "", py::arg("name")=NULL, py::arg("outValue")=NULL)
.def("SelectOptionFor", py::overload_cast<int>(&BOptionControl::SelectOptionFor), "", py::arg("value"))
.def("SelectOptionFor", py::overload_cast<const char *>(&BOptionControl::SelectOptionFor), "", py::arg("name"))
;


}
