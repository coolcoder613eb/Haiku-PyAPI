#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <add-ons/input_server/InputServerDevice.h>

namespace py = pybind11;
using namespace BPrivate;

class PyBInputServerDevice : public BInputServerDevice {
public:
    using BInputServerDevice::BInputServerDevice;
    status_t	InitCheck() override {
		PYBIND11_OVERLOAD(status_t, BInputServerDevice, InitCheck);
	}
	status_t	SystemShuttingDown() override {
		PYBIND11_OVERLOAD(status_t, BInputServerDevice, SystemShuttingDown);
	}
	status_t	Start(const char* device, void* cookie) override {
		PYBIND11_OVERLOAD(status_t, BInputServerDevice, Start, device, cookie);
	}
	status_t	Stop(const char* device, void* cookie) override {
		PYBIND11_OVERLOAD(status_t, BInputServerDevice, Stop, device, cookie);
	}
	status_t	Control(const char* device, void* cookie, uint32 code, BMessage* message) override {
		PYBIND11_OVERLOAD(status_t, BInputServerDevice, Control, device, cookie, code, message);
	}
};

PYBIND11_MODULE(InputServerDevice, m)
{

py::class_<input_device_ref>(m, "input_device_ref")
.def(py::init(), "")
.def_readwrite("name", &input_device_ref::name, "")
.def_readwrite("type", &input_device_ref::type, "")
.def_readwrite("cookie", &input_device_ref::cookie, "")
;

py::class_<BInputServerDevice,PyBInputServerDevice>(m, "BInputServerDevice")
.def(py::init(), "")
.def("InitCheck", &BInputServerDevice::InitCheck, "")
.def("SystemShuttingDown", &BInputServerDevice::SystemShuttingDown, "")
.def("Start", &BInputServerDevice::Start, "", py::arg("device"), py::arg("cookie"))
.def("Stop", &BInputServerDevice::Stop, "", py::arg("device"), py::arg("cookie"))
.def("Control", &BInputServerDevice::Control, "", py::arg("device"), py::arg("cookie"), py::arg("code"), py::arg("message"))
//.def("RegisterDevices", &BInputServerDevice::RegisterDevices, "", py::arg("devices"))
.def("RegisterDevices", [](BInputServerDevice &self, py::list &py_devices) {
            std::vector<input_device_ref*> devices;
            for (auto item : py_devices) {
                devices.push_back(item.cast<input_device_ref*>());
            }
            status_t status = self.RegisterDevices(devices.data());
            //for (size_t i = 0; i < devices.size(); ++i) {
            //    py_devices[i] = py::cast(devices[i]);
            //}
            return status;
        }, py::arg("devices"))
//.def("UnregisterDevices", &BInputServerDevice::UnregisterDevices, "", py::arg("devices"))
.def("UnregisterDevices", [](BInputServerDevice &self, py::list &py_devices) {
            std::vector<input_device_ref*> devices;
            for (auto item : py_devices) {
                devices.push_back(item.cast<input_device_ref*>());
            }
            status_t status = self.UnregisterDevices(devices.data());
            //for (size_t i = 0; i < devices.size(); ++i) {
            //    py_devices[i] = py::cast(devices[i]);
            //}
            return status;
        }, py::arg("devices"))
.def("EnqueueMessage", &BInputServerDevice::EnqueueMessage, "", py::arg("message"))
.def("StartMonitoringDevice", &BInputServerDevice::StartMonitoringDevice, "", py::arg("device"))
.def("StopMonitoringDevice", &BInputServerDevice::StopMonitoringDevice, "", py::arg("device"))
.def("AddDevices", &BInputServerDevice::AddDevices, "", py::arg("path"))
;

//m.attr("DeviceAddOn") = py::cast(DeviceAddOn);
m.attr("B_KEY_MAP_CHANGED") = py::cast(B_KEY_MAP_CHANGED);
m.attr("B_KEY_LOCKS_CHANGED") = py::cast(B_KEY_LOCKS_CHANGED);
m.attr("B_KEY_REPEAT_DELAY_CHANGED") = py::cast(B_KEY_REPEAT_DELAY_CHANGED);
m.attr("B_KEY_REPEAT_RATE_CHANGED") = py::cast(B_KEY_REPEAT_RATE_CHANGED);
m.attr("B_MOUSE_TYPE_CHANGED") = py::cast(B_MOUSE_TYPE_CHANGED);
m.attr("B_MOUSE_MAP_CHANGED") = py::cast(B_MOUSE_MAP_CHANGED);
m.attr("B_MOUSE_SPEED_CHANGED") = py::cast(B_MOUSE_SPEED_CHANGED);
m.attr("B_CLICK_SPEED_CHANGED") = py::cast(B_CLICK_SPEED_CHANGED);
m.attr("B_MOUSE_ACCELERATION_CHANGED") = py::cast(B_MOUSE_ACCELERATION_CHANGED);
m.attr("B_SET_TOUCHPAD_SETTINGS") = py::cast(B_SET_TOUCHPAD_SETTINGS);
}
