#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/Shelf.h>
#include <Dragger.h>
#include <Handler.h>
#include <List.h>
#include <Locker.h>

namespace py = pybind11;
using namespace BPrivate;

PYBIND11_MODULE(Shelf,m)
{
m.attr("replicant_data") = replicant_data;

m.attr("ShelfContainerViewFilter") = ShelfContainerViewFilter;

py::class_<BShelf, BHandler>(m, "BShelf")
.def(py::init<BView *, bool, const char *>(), "", py::arg("view"), py::arg("allowDrags")=true, py::arg("shelfType")=NULL)
.def(py::init<const entry_ref *, BView *, bool, const char *>(), "", py::arg("ref"), py::arg("view"), py::arg("allowDrags")=true, py::arg("shelfType")=NULL)
.def(py::init<BDataIO *, BView *, bool, const char *>(), "", py::arg("stream"), py::arg("view"), py::arg("allowDrags")=true, py::arg("shelfType")=NULL)
.def(py::init<BMessage *>(), "", py::arg("archive"))
.def_static("Instantiate", &BShelf::Instantiate, "", py::arg("archive"))
.def("Archive", &BShelf::Archive, "", py::arg("archive"), py::arg("deep")=true)
.def("MessageReceived", &BShelf::MessageReceived, "", py::arg("message"))
.def("Save", &BShelf::Save, "")
.def("SetDirty", &BShelf::SetDirty, "", py::arg("state"))
.def("IsDirty", &BShelf::IsDirty, "")
.def("ResolveSpecifier", &BShelf::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("form"), py::arg("property"))
.def("GetSupportedSuites", &BShelf::GetSupportedSuites, "", py::arg("data"))
.def("Perform", &BShelf::Perform, "", py::arg("code"), py::arg("data"))
.def("AllowsDragging", &BShelf::AllowsDragging, "")
.def("SetAllowsDragging", &BShelf::SetAllowsDragging, "", py::arg("state"))
.def("AllowsZombies", &BShelf::AllowsZombies, "")
.def("SetAllowsZombies", &BShelf::SetAllowsZombies, "", py::arg("state"))
.def("DisplaysZombies", &BShelf::DisplaysZombies, "")
.def("SetDisplaysZombies", &BShelf::SetDisplaysZombies, "", py::arg("state"))
.def("IsTypeEnforced", &BShelf::IsTypeEnforced, "")
.def("SetTypeEnforced", &BShelf::SetTypeEnforced, "", py::arg("state"))
.def("SetSaveLocation", py::overload_cast<BDataIO *>(&BShelf::SetSaveLocation), "", py::arg("stream"))
.def("SetSaveLocation", py::overload_cast<const entry_ref *>(&BShelf::SetSaveLocation), "", py::arg("ref"))
.def("SaveLocation", &BShelf::SaveLocation, "", py::arg("ref"))
.def("AddReplicant", &BShelf::AddReplicant, "", py::arg("archive"), py::arg("location"))
.def("DeleteReplicant", py::overload_cast<BView *>(&BShelf::DeleteReplicant), "", py::arg("replicant"))
.def("DeleteReplicant", py::overload_cast<BMessage *>(&BShelf::DeleteReplicant), "", py::arg("archive"))
.def("DeleteReplicant", py::overload_cast<int>(&BShelf::DeleteReplicant), "", py::arg("index"))
.def("CountReplicants", &BShelf::CountReplicants, "")
.def("ReplicantAt", &BShelf::ReplicantAt, "", py::arg("index"), py::arg("view")=NULL, py::arg("uid")=NULL, py::arg("perr")=NULL)
.def("IndexOf", py::overload_cast<const BView *>(&BShelf::IndexOf), "", py::arg("replicantView"))
.def("IndexOf", py::overload_cast<const BMessage *>(&BShelf::IndexOf), "", py::arg("archive"))
.def("IndexOf", py::overload_cast<unsigned int>(&BShelf::IndexOf), "", py::arg("id"))
;


}
