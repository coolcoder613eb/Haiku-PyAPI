#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <media/MediaFiles.h>

namespace py = pybind11;
using namespace BPrivate;
//using namespace BPrivate::media;

PYBIND11_MODULE(MediaFiles, m)
{
py::class_<BMediaFiles>(m, "BMediaFiles")
.def(py::init(), "")
.def("RewindTypes", &BMediaFiles::RewindTypes, "")
.def("GetNextType", &BMediaFiles::GetNextType, "", py::arg("_type"))
.def("RewindRefs", &BMediaFiles::RewindRefs, "", py::arg("type"))
.def("GetNextRef", &BMediaFiles::GetNextRef, "", py::arg("_type"), py::arg("_ref")=NULL)
.def("GetRefFor", &BMediaFiles::GetRefFor, "", py::arg("type"), py::arg("item"), py::arg("_ref"))
.def("SetRefFor", &BMediaFiles::SetRefFor, "", py::arg("type"), py::arg("item"), py::arg("ref"))
.def("GetAudioGainFor", &BMediaFiles::GetAudioGainFor, "", py::arg("type"), py::arg("item"), py::arg("_gain"))
.def("SetAudioGainFor", &BMediaFiles::SetAudioGainFor, "", py::arg("type"), py::arg("item"), py::arg("gain"))
.def("RemoveRefFor", &BMediaFiles::RemoveRefFor, "", py::arg("type"), py::arg("item"), py::arg("ref"))
.def("RemoveItem", &BMediaFiles::RemoveItem, "", py::arg("type"), py::arg("item"))
//.def_readwrite("B_SOUNDS", &BMediaFiles::B_SOUNDS, "") //from media kit source const char BMediaFiles::B_SOUNDS[] = "Sounds";
.def_static("B_SOUNDS", [](){return "Sounds";},"")
;


}
