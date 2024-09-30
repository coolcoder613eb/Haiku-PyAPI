#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <add-ons/network_settings/NetworkSettings.h>

namespace py = pybind11;
using namespace BNetworkKit;

class AltBNetworkSettingsRead : public BNetworkSettings {
public:
    using BNetworkSettings::BNetworkSettings;
	static const uint32 kMsgInterfaceSettingsUpdated() {
        return BNetworkSettings::kMsgInterfaceSettingsUpdated;
    }
    static const uint32 kMsgNetworkSettingsUpdated() {
        return BNetworkSettings::kMsgNetworkSettingsUpdated;
    }
    static const uint32 kMsgServiceSettingsUpdated() {
        return BNetworkSettings::kMsgServiceSettingsUpdated;
    }
};

PYBIND11_MODULE(NetworkSettings, m)
{
py::class_<BNetworkSettings>(m, "BNetworkSettings")
.def(py::init(), "")
.def("GetNextInterface", [](BNetworkSettings& self, uint32 cookie) {
    BMessage  interface;
    status_t r = self.GetNextInterface(cookie, interface);
    return std::make_tuple(r,interface);
}
, "", py::arg("cookie"))
.def("GetInterface", [](BNetworkSettings& self,const char * name) {
    BMessage  interface;
    status_t r = self.GetInterface(name, interface);
    return std::make_tuple(r,interface);
}
, "", py::arg("name"))
.def("AddInterface", &BNetworkSettings::AddInterface, "", py::arg("interface"))
.def("RemoveInterface", &BNetworkSettings::RemoveInterface, "", py::arg("name"))
.def("Interface", py::overload_cast<const char *>(&BNetworkSettings::Interface), "", py::arg("name"))
.def("Interface", py::overload_cast<const char *>(&BNetworkSettings::Interface, py::const_), "", py::arg("name"))
.def("CountNetworks", &BNetworkSettings::CountNetworks, "")
.def("GetNextNetwork", [](BNetworkSettings& self,uint32 cookie) {
    BMessage  network;
    status_t r = self.GetNextNetwork(cookie, network);
    return std::make_tuple(r,network);
}
, "", py::arg("cookie"))
.def("GetNetwork", [](BNetworkSettings& self,const char * name) {
    BMessage  network;
    status_t r = self.GetNetwork(name, network);
    return std::make_tuple(r,network);
}
, "", py::arg("name"))
.def("AddNetwork", &BNetworkSettings::AddNetwork, "", py::arg("network"))
.def("RemoveNetwork", &BNetworkSettings::RemoveNetwork, "", py::arg("name"))
.def("Services", &BNetworkSettings::Services, "")
.def("GetNextService", [](BNetworkSettings& self,uint32 cookie) {
    BMessage  service;
    status_t r = self.GetNextService(cookie, service);
    return std::make_tuple(r,service);
}
, "", py::arg("cookie"))
.def("GetService", [](BNetworkSettings& self,const char * name) {
    BMessage  service;
    status_t r = self.GetService(name, service);
    return std::make_tuple(r,service);
}
, "", py::arg("name"))
.def("AddService", &BNetworkSettings::AddService, "", py::arg("service"))
.def("RemoveService", &BNetworkSettings::RemoveService, "", py::arg("name"))
.def("Service", py::overload_cast<const char *>(&BNetworkSettings::Service), "", py::arg("name"))
.def("Service", py::overload_cast<const char *>(&BNetworkSettings::Service), "", py::arg("name"))
.def("StartMonitoring", &BNetworkSettings::StartMonitoring, "", py::arg("target"))
.def("StopMonitoring", &BNetworkSettings::StopMonitoring, "", py::arg("target"))
.def("Update", &BNetworkSettings::Update, "", py::arg("message"))
//.def_readwrite("kMsgInterfaceSettingsUpdated", &BNetworkSettings::kMsgInterfaceSettingsUpdated, "")
.def_property_readonly_static("kMsgInterfaceSettingsUpdated", []() {
            return AltBNetworkSettingsRead::kMsgInterfaceSettingsUpdated();
        }, "")
//.def_readwrite("kMsgNetworkSettingsUpdated", &BNetworkSettings::kMsgNetworkSettingsUpdated, "")
.def_property_readonly_static("kMsgNetworkSettingsUpdated", []() {
            return AltBNetworkSettingsRead::kMsgNetworkSettingsUpdated();
        }, "")
//.def_readwrite("kMsgServiceSettingsUpdated", &BNetworkSettings::kMsgServiceSettingsUpdated, "")
.def_property_readonly_static("kMsgServiceSettingsUpdated", []() {
            return AltBNetworkSettingsRead::kMsgServiceSettingsUpdated();
        }, "")
;

py::class_<BNetworkInterfaceAddressSettings>(m, "BNetworkInterfaceAddressSettings")
.def(py::init(), "")
.def(py::init<const BMessage &>(), "", py::arg("data"))
.def(py::init<const BNetworkInterfaceAddressSettings &>(), "", py::arg("other"))
.def("Family", &BNetworkInterfaceAddressSettings::Family, "")
.def("SetFamily", &BNetworkInterfaceAddressSettings::SetFamily, "", py::arg("family"))
.def("IsAutoConfigure", &BNetworkInterfaceAddressSettings::IsAutoConfigure, "")
.def("SetAutoConfigure", &BNetworkInterfaceAddressSettings::SetAutoConfigure, "", py::arg("configure"))
.def("Address", py::overload_cast<>(&BNetworkInterfaceAddressSettings::Address), "")
.def("Address", py::overload_cast<>(&BNetworkInterfaceAddressSettings::Address), "")
.def("Mask", py::overload_cast<>(&BNetworkInterfaceAddressSettings::Mask), "")
.def("Mask", py::overload_cast<>(&BNetworkInterfaceAddressSettings::Mask), "")
.def("Peer", py::overload_cast<>(&BNetworkInterfaceAddressSettings::Peer), "")
.def("Peer", py::overload_cast<>(&BNetworkInterfaceAddressSettings::Peer), "")
.def("Broadcast", py::overload_cast<>(&BNetworkInterfaceAddressSettings::Broadcast), "")
.def("Broadcast", py::overload_cast<>(&BNetworkInterfaceAddressSettings::Broadcast), "")
.def("Gateway", py::overload_cast<>(&BNetworkInterfaceAddressSettings::Gateway), "")
.def("Gateway", py::overload_cast<>(&BNetworkInterfaceAddressSettings::Gateway), "")
.def("GetMessage", [](BNetworkInterfaceAddressSettings& self) {
    BMessage  data;
    status_t r = self.GetMessage(data);
    return std::make_tuple(r,data);
}
, "")
.def("operator=", &BNetworkInterfaceAddressSettings::operator=, "", py::arg("other"))
;

py::class_<BNetworkInterfaceSettings>(m, "BNetworkInterfaceSettings")
.def(py::init(), "")
.def(py::init<const BMessage &>(), "", py::arg("message"))
.def("Name", &BNetworkInterfaceSettings::Name, "")
.def("SetName", &BNetworkInterfaceSettings::SetName, "", py::arg("name"))
.def("Flags", &BNetworkInterfaceSettings::Flags, "")
.def("SetFlags", &BNetworkInterfaceSettings::SetFlags, "", py::arg("flags"))
.def("MTU", &BNetworkInterfaceSettings::MTU, "")
.def("SetMTU", &BNetworkInterfaceSettings::SetMTU, "", py::arg("mtu"))
.def("Metric", &BNetworkInterfaceSettings::Metric, "")
.def("SetMetric", &BNetworkInterfaceSettings::SetMetric, "", py::arg("metric"))
.def("CountAddresses", &BNetworkInterfaceSettings::CountAddresses, "")
.def("AddressAt", py::overload_cast<int32>(&BNetworkInterfaceSettings::AddressAt), "", py::arg("index"))
.def("AddressAt", py::overload_cast<int32>(&BNetworkInterfaceSettings::AddressAt), "", py::arg("index"))
.def("FindFirstAddress", &BNetworkInterfaceSettings::FindFirstAddress, "", py::arg("family"))
.def("AddAddress", &BNetworkInterfaceSettings::AddAddress, "", py::arg("address"))
.def("RemoveAddress", &BNetworkInterfaceSettings::RemoveAddress, "", py::arg("index"))
.def("IsAutoConfigure", &BNetworkInterfaceSettings::IsAutoConfigure, "", py::arg("family"))
.def("GetMessage", [](BNetworkInterfaceSettings& self) {
    BMessage  data;
    status_t r = self.GetMessage(data);
    return std::make_tuple(r,data);
}
, "")
;

py::class_<BNetworkServiceAddressSettings>(m, "BNetworkServiceAddressSettings")
.def(py::init(), "")
.def(py::init<const BMessage &, int, int, int, int>(), "", py::arg("data"), py::arg("family")=- 1, py::arg("type")=- 1, py::arg("protocol")=- 1, py::arg("port")=- 1)
.def("Family", &BNetworkServiceAddressSettings::Family, "")
.def("SetFamily", &BNetworkServiceAddressSettings::SetFamily, "", py::arg("family"))
.def("Protocol", &BNetworkServiceAddressSettings::Protocol, "")
.def("SetProtocol", &BNetworkServiceAddressSettings::SetProtocol, "", py::arg("protocol"))
.def("Type", &BNetworkServiceAddressSettings::Type, "")
.def("SetType", &BNetworkServiceAddressSettings::SetType, "", py::arg("type"))
.def("Address", py::overload_cast<>(&BNetworkServiceAddressSettings::Address), "")
.def("Address", py::overload_cast<>(&BNetworkServiceAddressSettings::Address), "")
.def("GetMessage", [](BNetworkServiceAddressSettings& self) {
    BMessage  data;
    status_t r = self.GetMessage(data);
    return std::make_tuple(r,data);
}
, "")
.def("__eq__", &BNetworkServiceAddressSettings::operator==, "", py::arg("other"))
;

py::class_<BNetworkServiceSettings>(m, "BNetworkServiceSettings")
.def(py::init(), "")
.def(py::init<const BMessage &>(), "", py::arg("message"))
.def("InitCheck", &BNetworkServiceSettings::InitCheck, "")
.def("Name", &BNetworkServiceSettings::Name, "")
.def("SetName", &BNetworkServiceSettings::SetName, "", py::arg("name"))
.def("IsStandAlone", &BNetworkServiceSettings::IsStandAlone, "")
.def("SetStandAlone", &BNetworkServiceSettings::SetStandAlone, "", py::arg("alone"))
.def("IsEnabled", &BNetworkServiceSettings::IsEnabled, "")
.def("SetEnabled", &BNetworkServiceSettings::SetEnabled, "", py::arg("enable"))
.def("Family", &BNetworkServiceSettings::Family, "")
.def("SetFamily", &BNetworkServiceSettings::SetFamily, "", py::arg("family"))
.def("Protocol", &BNetworkServiceSettings::Protocol, "")
.def("SetProtocol", &BNetworkServiceSettings::SetProtocol, "", py::arg("protocol"))
.def("Type", &BNetworkServiceSettings::Type, "")
.def("SetType", &BNetworkServiceSettings::SetType, "", py::arg("type"))
.def("Port", &BNetworkServiceSettings::Port, "")
.def("SetPort", &BNetworkServiceSettings::SetPort, "", py::arg("port"))
.def("CountArguments", &BNetworkServiceSettings::CountArguments, "")
.def("ArgumentAt", &BNetworkServiceSettings::ArgumentAt, "", py::arg("index"))
.def("AddArgument", &BNetworkServiceSettings::AddArgument, "", py::arg("argument"))
.def("RemoveArgument", &BNetworkServiceSettings::RemoveArgument, "", py::arg("index"))
.def("CountAddresses", &BNetworkServiceSettings::CountAddresses, "")
.def("AddressAt", &BNetworkServiceSettings::AddressAt, "", py::arg("index"))
.def("AddAddress", &BNetworkServiceSettings::AddAddress, "", py::arg("address"))
.def("RemoveAddress", &BNetworkServiceSettings::RemoveAddress, "", py::arg("index"))
.def("IsRunning", &BNetworkServiceSettings::IsRunning, "")
.def("GetMessage", [](BNetworkServiceSettings& self) {
    BMessage  data;
    status_t r = self.GetMessage(data);
    return std::make_tuple(r,data);
}
, "")
;


}
