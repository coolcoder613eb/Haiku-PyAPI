#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/OptionPopUp.h>
#include <OptionControl.h>

namespace py = pybind11;


PYBIND11_MODULE(OptionPopUp,m)
{
py::class_<BOptionPopUp, BOptionControl>(m, "BOptionPopUp")
.def(py::init<BRect, const char *, const char *, BMessage *, unsigned int, unsigned int>(), "", py::arg("frame"), py::arg("name"), py::arg("label"), py::arg("message"), py::arg("resizeMask")=B_FOLLOW_LEFT_TOP, py::arg("flags")=B_WILL_DRAW)
.def(py::init<BRect, const char *, const char *, BMessage *, bool, unsigned int, unsigned int>(), "", py::arg("frame"), py::arg("name"), py::arg("label"), py::arg("message"), py::arg("fixed"), py::arg("resizeMask")=B_FOLLOW_LEFT_TOP, py::arg("flags")=B_WILL_DRAW)
.def(py::init<const char *, const char *, BMessage *, unsigned int>(), "", py::arg("name"), py::arg("label"), py::arg("message"), py::arg("flags")=B_WILL_DRAW)
.def("MenuField", &BOptionPopUp::MenuField, "")
.def("GetOptionAt", &BOptionPopUp::GetOptionAt, "", py::arg("index"), py::arg("_name"), py::arg("_value"))
.def("RemoveOptionAt", &BOptionPopUp::RemoveOptionAt, "", py::arg("index"))
.def("CountOptions", &BOptionPopUp::CountOptions, "")
.def("AddOptionAt", &BOptionPopUp::AddOptionAt, "", py::arg("name"), py::arg("value"), py::arg("index"))
.def("AllAttached", &BOptionPopUp::AllAttached, "")
.def("AttachedToWindow", &BOptionPopUp::AttachedToWindow, "")
.def("MessageReceived", &BOptionPopUp::MessageReceived, "", py::arg("message"))
.def("SetLabel", &BOptionPopUp::SetLabel, "", py::arg("text"))
.def("SetValue", &BOptionPopUp::SetValue, "", py::arg("value"))
.def("SetEnabled", &BOptionPopUp::SetEnabled, "", py::arg("enabled"))
.def("GetPreferredSize", &BOptionPopUp::GetPreferredSize, "", py::arg("_width"), py::arg("_height"))
.def("ResizeToPreferred", &BOptionPopUp::ResizeToPreferred, "")
.def("SelectedOption", &BOptionPopUp::SelectedOption, "", py::arg("_name")=0, py::arg("_value")=0)
;


}
