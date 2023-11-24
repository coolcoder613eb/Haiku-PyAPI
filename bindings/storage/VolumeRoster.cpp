#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <VolumeRoster.h>

namespace py = pybind11;
using namespace BPrivate;
using namespace BPrivate::Storage;
using namespace BPrivate::Storage::Mime;
using namespace BPackageKit;

void define_VolumeRoster(py::module_& m)
{
py::class_<BVolumeRoster>(m, "BVolumeRoster")
.def(py::init(), "")
.def("GetNextVolume", &BVolumeRoster::GetNextVolume, "", py::arg("volume"))
.def("Rewind", &BVolumeRoster::Rewind, "")
.def("GetBootVolume", &BVolumeRoster::GetBootVolume, "", py::arg("volume"))
.def("StartWatching", &BVolumeRoster::StartWatching, "", py::arg("messenger")=be_app_messenger)
.def("StopWatching", &BVolumeRoster::StopWatching, "")
.def("Messenger", &BVolumeRoster::Messenger, "")
;


}
