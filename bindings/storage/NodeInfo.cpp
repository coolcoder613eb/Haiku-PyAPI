#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <NodeInfo.h>

namespace py = pybind11;
using namespace BPrivate;
using namespace BPrivate::Storage;
using namespace BPrivate::Storage::Mime;

void define_NodeInfo(py::module_& m)
{
py::class_<BNodeInfo>(m, "BNodeInfo")
.def(py::init(), "")
.def(py::init<BNode *>(), "", py::arg("node"))
.def("SetTo", &BNodeInfo::SetTo, "", py::arg("node"))
.def("InitCheck", &BNodeInfo::InitCheck, "")
.def("GetType", &BNodeInfo::GetType, "", py::arg("type"))
.def("SetType", &BNodeInfo::SetType, "", py::arg("type"))
.def("GetIcon", py::overload_cast<BBitmap *, icon_size>(&BNodeInfo::GetIcon), "", py::arg("icon"), py::arg("which")=B_LARGE_ICON)
.def("SetIcon", py::overload_cast<const BBitmap *, icon_size>(&BNodeInfo::SetIcon), "", py::arg("icon"), py::arg("which")=B_LARGE_ICON)
.def("GetIcon", py::overload_cast<unsigned char, size_t *, type_code *>(&BNodeInfo::GetIcon), "", py::arg("data"), py::arg("size"), py::arg("type"))
.def("SetIcon", py::overload_cast<unsigned char, size_t>(&BNodeInfo::SetIcon), "", py::arg("data"), py::arg("size"))
.def("GetPreferredApp", &BNodeInfo::GetPreferredApp, "", py::arg("signature"), py::arg("verb")=B_OPEN)
.def("SetPreferredApp", &BNodeInfo::SetPreferredApp, "", py::arg("signature"), py::arg("verb")=B_OPEN)
.def("GetAppHint", &BNodeInfo::GetAppHint, "", py::arg("ref"))
.def("SetAppHint", &BNodeInfo::SetAppHint, "", py::arg("ref"))
.def("GetTrackerIcon", py::overload_cast<BBitmap *, icon_size>(&BNodeInfo::GetTrackerIcon), "", py::arg("icon"), py::arg("which")=B_LARGE_ICON)
.def_static("GetTrackerIcon", py::overload_cast<const entry_ref *, BBitmap *, icon_size>(&BNodeInfo::GetTrackerIcon), "", py::arg("ref"), py::arg("icon"), py::arg("which")=B_LARGE_ICON)
;


}
