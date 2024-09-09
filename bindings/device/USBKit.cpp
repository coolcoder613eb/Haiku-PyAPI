#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>
#include <pybind11/numpy.h>

#include <USBKit.h>

namespace py = pybind11;
class PyBUSBRoster : public BUSBRoster{
	public:
        using BUSBRoster::BUSBRoster;
		status_t					DeviceAdded(BUSBDevice *device) override {
			PYBIND11_OVERLOAD_PURE(status_t,BUSBRoster,DeviceAdded,device)
		}
		void						DeviceRemoved(BUSBDevice *device) override {
			PYBIND11_OVERLOAD_PURE(void,BUSBRoster,DeviceRemoved,device)
		}
};

PYBIND11_MODULE(USBKit,m)
{
py::class_<BUSBRoster,PyBUSBRoster>(m, "BUSBRoster")
.def(py::init(), "")
.def("DeviceAdded", &BUSBRoster::DeviceAdded, "", py::arg("device"))
.def("DeviceRemoved", &BUSBRoster::DeviceRemoved, "", py::arg("device"))
.def("Start", &BUSBRoster::Start, "")
.def("Stop", &BUSBRoster::Stop, "")
;

py::class_<BUSBDevice>(m, "BUSBDevice")
.def(py::init<const char *>(), "", py::arg("path")=NULL)
.def("InitCheck", &BUSBDevice::InitCheck, "")
.def("SetTo", &BUSBDevice::SetTo, "", py::arg("path"))
.def("Unset", &BUSBDevice::Unset, "")
.def("Location", &BUSBDevice::Location, "")
.def("IsHub", &BUSBDevice::IsHub, "")
.def("USBVersion", &BUSBDevice::USBVersion, "")
.def("Class", &BUSBDevice::Class, "")
.def("Subclass", &BUSBDevice::Subclass, "")
.def("Protocol", &BUSBDevice::Protocol, "")
.def("MaxEndpoint0PacketSize", &BUSBDevice::MaxEndpoint0PacketSize, "")
.def("VendorID", &BUSBDevice::VendorID, "")
.def("ProductID", &BUSBDevice::ProductID, "")
.def("Version", &BUSBDevice::Version, "")
.def("ManufacturerString", &BUSBDevice::ManufacturerString, "")
.def("ProductString", &BUSBDevice::ProductString, "")
.def("SerialNumberString", &BUSBDevice::SerialNumberString, "")
.def("Descriptor", &BUSBDevice::Descriptor, "")
.def("GetStringDescriptor", &BUSBDevice::GetStringDescriptor, "", py::arg("index"), py::arg("descriptor"), py::arg("length"))
.def("DecodeStringDescriptor", &BUSBDevice::DecodeStringDescriptor, "", py::arg("index"))
//.def("GetDescriptor", &BUSBDevice::GetDescriptor, "", py::arg("type"), py::arg("index"), py::arg("languageID"), py::arg("data"), py::arg("length")) //todo: void *data -> in py::bytes
.def("GetDescriptor", [](const BUSBDevice& self, uint8 type, uint8 index, uint16 languageID, py::bytes data) {
	size_t length = py::len(data);
	std::vector<uint8_t> buffer(length);
	size_t resultLength = self.GetDescriptor(type, index, languageID, buffer.data(), length);
	return py::bytes(reinterpret_cast<const char*>(buffer.data()), resultLength);
},"", py::arg("type"), py::arg("index"), py::arg("languageID"), py::arg("data"))
.def("CountConfigurations", &BUSBDevice::CountConfigurations, "")
.def("ConfigurationAt", &BUSBDevice::ConfigurationAt, "", py::arg("index"))
.def("ActiveConfiguration", &BUSBDevice::ActiveConfiguration, "")
.def("SetConfiguration", &BUSBDevice::SetConfiguration, "", py::arg("configuration"))
.def("ControlTransfer", &BUSBDevice::ControlTransfer, "", py::arg("requestType"), py::arg("request"), py::arg("value"), py::arg("index"), py::arg("length"), py::arg("data"))
;

py::class_<BUSBConfiguration, std::unique_ptr<BUSBConfiguration,py::nodelete>>(m, "BUSBConfiguration")
.def("Index", &BUSBConfiguration::Index, "")
.def("Device", &BUSBConfiguration::Device, "")
.def("ConfigurationString", &BUSBConfiguration::ConfigurationString, "")
.def("Descriptor", &BUSBConfiguration::Descriptor, "")
.def("CountInterfaces", &BUSBConfiguration::CountInterfaces, "")
.def("InterfaceAt", &BUSBConfiguration::InterfaceAt, "", py::arg("index"))
;

py::class_<BUSBInterface, std::unique_ptr<BUSBInterface,py::nodelete>>(m, "BUSBInterface")
.def("Index", &BUSBInterface::Index, "")
.def("AlternateIndex", &BUSBInterface::AlternateIndex, "")
.def("Configuration", &BUSBInterface::Configuration, py::return_value_policy::reference)
.def("Device", &BUSBInterface::Device, py::return_value_policy::reference)
.def("Class", &BUSBInterface::Class, "")
.def("Subclass", &BUSBInterface::Subclass, "")
.def("Protocol", &BUSBInterface::Protocol, "")
.def("InterfaceString", &BUSBInterface::InterfaceString, "")
.def("Descriptor", &BUSBInterface::Descriptor, "")
.def("OtherDescriptorAt", &BUSBInterface::OtherDescriptorAt, "", py::arg("index"), py::arg("descriptor"), py::arg("length"))
.def("CountEndpoints", &BUSBInterface::CountEndpoints, "")
.def("EndpointAt", &BUSBInterface::EndpointAt, "", py::arg("index"))
.def("CountAlternates", &BUSBInterface::CountAlternates, "")
.def("ActiveAlternateIndex", &BUSBInterface::ActiveAlternateIndex, "")
.def("AlternateAt", &BUSBInterface::AlternateAt, "", py::arg("alternateIndex"))
.def("SetAlternate", &BUSBInterface::SetAlternate, "", py::arg("alternateIndex"))
;

py::class_<BUSBEndpoint, std::unique_ptr<BUSBEndpoint,py::nodelete>>(m, "BUSBEndpoint")
.def("Index", &BUSBEndpoint::Index, "")
.def("Interface", &BUSBEndpoint::Interface, "")
.def("Configuration", &BUSBEndpoint::Configuration, "")
.def("Device", &BUSBEndpoint::Device, "")
.def("IsBulk", &BUSBEndpoint::IsBulk, "")
.def("IsInterrupt", &BUSBEndpoint::IsInterrupt, "")
.def("IsIsochronous", &BUSBEndpoint::IsIsochronous, "")
.def("IsControl", &BUSBEndpoint::IsControl, "")
.def("IsInput", &BUSBEndpoint::IsInput, "")
.def("IsOutput", &BUSBEndpoint::IsOutput, "")
.def("MaxPacketSize", &BUSBEndpoint::MaxPacketSize, "")
.def("Interval", &BUSBEndpoint::Interval, "")
.def("Descriptor", &BUSBEndpoint::Descriptor, "")
//.def("ControlTransfer", &BUSBEndpoint::ControlTransfer, "", py::arg("requestType"), py::arg("request"), py::arg("value"), py::arg("index"), py::arg("length"), py::arg("data"))
.def("ControlTransfer", [](const BUSBEndpoint& self, uint8 requestType, uint8 request, uint16 value, uint16 index, uint16 length, py::bytes data) {
	size_t dataLength = py::len(data);
	std::vector<uint8_t> buffer(dataLength);
	ssize_t result = self.ControlTransfer(requestType, request, value, index, length, buffer.data());
	return py::bytes(reinterpret_cast<const char*>(buffer.data()), result);
},"", py::arg("requestType"), py::arg("request"), py::arg("value"), py::arg("index"), py::arg("length"), py::arg("data")) .def("InterruptTransfer", [](const MyDevice& self, py::bytes data) { size_t dataLength = py::len(data); std::vector<uint8_t> buffer(dataLength); ssize_t result = self.InterruptTransfer(buffer.data(), dataLength); return py::bytes(reinterpret_cast<const char*>(buffer.data()), result); }, py::arg("data")) .def("BulkTransfer", [](const MyDevice& self, py::bytes data) { size_t dataLength = py::len(data); std::vector<uint8_t> buffer(dataLength); ssize_t result = self.BulkTransfer(buffer.data(), dataLength); return py::bytes(reinterpret_cast<const char*>(buffer.data()), result); }, py::arg("data")) .def("IsochronousTransfer", [](const MyDevice& self, py::bytes data, py::list packetDescriptors) { size_t dataLength = py::len(data); std::vector<uint8_t> buffer(dataLength); // Converti packetDescriptors da lista Python a un array C++ std::vector<usb_iso_packet_descriptor> descriptors; for (auto item : packetDescriptors) { descriptors.push_back(item.cast<usb_iso_packet_descriptor>()); } ssize_t result = self.IsochronousTransfer(buffer.data(), dataLength, descriptors.data(), descriptors.size()); return py::bytes(reinterpret_cast<const char*>(buffer.data()), result); }, py::arg("data"), py::arg("packetDescriptors"))
//.def("InterruptTransfer", &BUSBEndpoint::InterruptTransfer, "", py::arg("data"), py::arg("length"))
.def("InterruptTransfer", [](const BUSBEndpoint& self, py::bytes data) {
	size_t dataLength = py::len(data);
	std::vector<uint8_t> buffer(dataLength);
	ssize_t result = self.InterruptTransfer(buffer.data(), dataLength);
	return py::bytes(reinterpret_cast<const char*>(buffer.data()), result);
},"", py::arg("data"))
//.def("BulkTransfer", &BUSBEndpoint::BulkTransfer, "", py::arg("data"), py::arg("length"))
.def("BulkTransfer", [](const BUSBEndpoint& self, py::bytes data) {
	size_t dataLength = py::len(data);
	std::vector<uint8_t> buffer(dataLength);
	ssize_t result = self.BulkTransfer(buffer.data(), dataLength);
	return py::bytes(reinterpret_cast<const char*>(buffer.data()), result);
},"", py::arg("data"))
//.def("IsochronousTransfer", &BUSBEndpoint::IsochronousTransfer, "", py::arg("data"), py::arg("length"), py::arg("packetDescriptors"), py::arg("packetCount"))
.def("IsochronousTransfer", [](const BUSBEndpoint& self, py::bytes data, usb_iso_packet_descriptor *packetDescriptors, uint32 packetCount) {
	size_t dataLength = py::len(data);
	std::vector<uint8_t> buffer(dataLength);
	ssize_t result = self.IsochronousTransfer(buffer.data(), dataLength,packetDescriptors,packetCount);
	return py::bytes(reinterpret_cast<const char*>(buffer.data()), result);
},"", py::arg("data"))
.def("IsStalled", &BUSBEndpoint::IsStalled, "")
.def("ClearStall", &BUSBEndpoint::ClearStall, "")
;

}
