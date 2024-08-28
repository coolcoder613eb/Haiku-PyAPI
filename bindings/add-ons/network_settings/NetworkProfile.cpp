#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <add-ons/network_settings/NetworkProfile.h>

namespace py = pybind11;
using namespace BNetworkKit;

PYBIND11_MODULE(NetworkProfile, m)
{
py::class_<BNetworkProfile>(m, "BNetworkProfile")
.def(py::init(), "")
.def(py::init<const char *>(), "", py::arg("path"))
.def(py::init<const entry_ref &>(), "", py::arg("ref"))
.def(py::init<const BEntry &>(), "", py::arg("entry"))
.def("SetTo", py::overload_cast<const char *>(&BNetworkProfile::SetTo), "", py::arg("path"))
.def("SetTo", py::overload_cast<const entry_ref &>(&BNetworkProfile::SetTo), "", py::arg("ref"))
.def("SetTo", py::overload_cast<const BEntry &>(&BNetworkProfile::SetTo), "", py::arg("entry"))
.def("Exists", &BNetworkProfile::Exists, "")
.def("Name", &BNetworkProfile::Name, "")
.def("SetName", &BNetworkProfile::SetName, "", py::arg("name"))
.def("IsDefault", &BNetworkProfile::IsDefault, "")
.def("IsCurrent", &BNetworkProfile::IsCurrent, "")
.def("MakeCurrent", &BNetworkProfile::MakeCurrent, "")
.def("Delete", &BNetworkProfile::Delete, "")
.def_static("Default", &BNetworkProfile::Default, "")
.def_static("Current", &BNetworkProfile::Current, "")
;


}
