#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/Input.h>
#include <Messenger.h>
#include <List.h>

namespace py = pybind11;


PYBIND11_MODULE(Input,m)
{
py::enum_<input_method_op>(m, "input_method_op", "")
.value("B_INPUT_METHOD_STARTED", input_method_op::B_INPUT_METHOD_STARTED, "")
.value("B_INPUT_METHOD_STOPPED", input_method_op::B_INPUT_METHOD_STOPPED, "")
.value("B_INPUT_METHOD_CHANGED", input_method_op::B_INPUT_METHOD_CHANGED, "")
.value("B_INPUT_METHOD_LOCATION_REQUEST", input_method_op::B_INPUT_METHOD_LOCATION_REQUEST, "")
.export_values();

py::enum_<input_device_type>(m, "input_device_type", "")
.value("B_POINTING_DEVICE", input_device_type::B_POINTING_DEVICE, "")
.value("B_KEYBOARD_DEVICE", input_device_type::B_KEYBOARD_DEVICE, "")
.value("B_UNDEFINED_DEVICE", input_device_type::B_UNDEFINED_DEVICE, "")
.export_values();

py::enum_<input_device_notification>(m, "input_device_notification", "")
.value("B_INPUT_DEVICE_ADDED", input_device_notification::B_INPUT_DEVICE_ADDED, "")
.value("B_INPUT_DEVICE_STARTED", input_device_notification::B_INPUT_DEVICE_STARTED, "")
.value("B_INPUT_DEVICE_STOPPED", input_device_notification::B_INPUT_DEVICE_STOPPED, "")
.value("B_INPUT_DEVICE_REMOVED", input_device_notification::B_INPUT_DEVICE_REMOVED, "")
.export_values();

py::class_<BInputDevice>(m, "BInputDevice")
.def("Name", &BInputDevice::Name, "")
.def("Type", &BInputDevice::Type, "")
.def("IsRunning", &BInputDevice::IsRunning, "")
.def("Start", py::overload_cast<>(&BInputDevice::Start), "")
.def("Stop", py::overload_cast<>(&BInputDevice::Stop), "")
.def("Control", py::overload_cast<uint32, BMessage *>(&BInputDevice::Control), "", py::arg("code"), py::arg("message"))
.def_static("Start_static", py::overload_cast<input_device_type>(&BInputDevice::Start), "", py::arg("type"))
.def_static("Stop_static", py::overload_cast<input_device_type>(&BInputDevice::Stop), "", py::arg("type"))
.def_static("Control_static", py::overload_cast<input_device_type, uint32, BMessage *>(&BInputDevice::Control), "", py::arg("type"), py::arg("code"), py::arg("message"))
;

m.def("find_input_device", &find_input_device, "", py::arg("name"));

m.def("get_input_devices", &get_input_devices, "", py::arg("list"));

m.def("watch_input_devices", &watch_input_devices, "", py::arg("target"), py::arg("start"));

}
