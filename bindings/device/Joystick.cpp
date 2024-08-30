#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <device/Joystick.h>
#include <String.h>
#include <Entry.h>

namespace py = pybind11;


PYBIND11_MODULE(Joystick,m)
{
py::class_<BJoystick>(m, "BJoystick")
.def(py::init(), "")
.def("Open", py::overload_cast<const char *>(&BJoystick::Open), "", py::arg("portName"))
.def("Open", py::overload_cast<const char *, bool>(&BJoystick::Open), "", py::arg("portName"), py::arg("enhanced"))
.def("Close", &BJoystick::Close, "")
.def("Update", &BJoystick::Update, "")
.def("SetMaxLatency", &BJoystick::SetMaxLatency, "", py::arg("maxLatency"))
.def("CountDevices", &BJoystick::CountDevices, "")
.def("GetDeviceName", &BJoystick::GetDeviceName, "", py::arg("index"), py::arg("name"), py::arg("bufSize")=B_OS_NAME_LENGTH)
.def("RescanDevices", &BJoystick::RescanDevices, "")
.def("EnterEnhancedMode", &BJoystick::EnterEnhancedMode, "", py::arg("ref")=NULL)
.def("CountSticks", &BJoystick::CountSticks, "")
.def("CountAxes", &BJoystick::CountAxes, "")
.def("GetAxisValues", &BJoystick::GetAxisValues, "", py::arg("outValues"), py::arg("forStick")=0)
.def("GetAxisNameAt", &BJoystick::GetAxisNameAt, "", py::arg("index"), py::arg("outName"))
.def("CountHats", &BJoystick::CountHats, "")
.def("GetHatValues", &BJoystick::GetHatValues, "", py::arg("outHats"), py::arg("forStick")=0)
.def("GetHatNameAt", &BJoystick::GetHatNameAt, "", py::arg("index"), py::arg("outName"))
.def("CountButtons", &BJoystick::CountButtons, "")
.def("ButtonValues", &BJoystick::ButtonValues, "", py::arg("forStick")=0)
.def("GetButtonValues", &BJoystick::GetButtonValues, "", py::arg("outButtons"), py::arg("forStick")=0)
.def("GetButtonNameAt", &BJoystick::GetButtonNameAt, "", py::arg("index"), py::arg("outName"))
.def("GetControllerModule", &BJoystick::GetControllerModule, "", py::arg("outName"))
.def("GetControllerName", &BJoystick::GetControllerName, "", py::arg("outName"))
.def("IsCalibrationEnabled", &BJoystick::IsCalibrationEnabled, "")
.def("EnableCalibration", &BJoystick::EnableCalibration, "", py::arg("calibrates")=true)
.def_readwrite("timestamp", &BJoystick::timestamp, "")
.def_readwrite("horizontal", &BJoystick::horizontal, "")
.def_readwrite("vertical", &BJoystick::vertical, "")
.def_readwrite("button1", &BJoystick::button1, "")
.def_readwrite("button2", &BJoystick::button2, "")
;


}
