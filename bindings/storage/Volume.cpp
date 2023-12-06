#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>
#include <pybind11/numpy.h>

#include <Volume.h>
#include <Directory.h>
#include <Bitmap.h>

namespace py = pybind11;
/*using namespace BPrivate;
using namespace BPrivate::Storage;
using namespace BPrivate::Storage::Mime;
using namespace BPackageKit;*/

PYBIND11_MODULE(Volume, m)
{
py::class_<BVolume>(m, "BVolume")
.def(py::init(), "")
.def(py::init<dev_t>(), "", py::arg("device"))
.def(py::init<const BVolume &>(), "", py::arg("volume"))
.def("InitCheck", &BVolume::InitCheck, "")
.def("SetTo", &BVolume::SetTo, "", py::arg("device"))
.def("Unset", &BVolume::Unset, "")
.def("Device", &BVolume::Device, "")
.def("GetRootDirectory", &BVolume::GetRootDirectory, "", py::arg("directory"))
.def("Capacity", &BVolume::Capacity, "")
.def("FreeBytes", &BVolume::FreeBytes, "")
.def("BlockSize", &BVolume::BlockSize, "")
.def("GetName", &BVolume::GetName, "", py::arg("name"))
.def("SetName", &BVolume::SetName, "", py::arg("name"))
.def("GetIcon", py::overload_cast<BBitmap *, icon_size>(&BVolume::GetIcon, py::const_), "", py::arg("icon"), py::arg("which"))
//.def("GetIcon", py::overload_cast<unsigned char, size_t *, type_code *>(&BVolume::GetIcon, py::const_), "", py::arg("_data"), py::arg("_size"), py::arg("_type"))
.def("GetIcon", [](BVolume& self, size_t size, type_code type){
    uint8_t* data;
    status_t result = self.GetIcon(&data, &size, &type);
    py::array_t<uint8_t> array = py::array_t<uint8_t>(
            {static_cast<ssize_t>(size)},
            {sizeof(uint8_t)},
            data
    );
    return py::make_tuple(array, result);
}, "", py::arg("size"), py::arg("type"))
.def("IsRemovable", &BVolume::IsRemovable, "")
.def("IsReadOnly", &BVolume::IsReadOnly, "")
.def("IsPersistent", &BVolume::IsPersistent, "")
.def("IsShared", &BVolume::IsShared, "")
.def("KnowsMime", &BVolume::KnowsMime, "")
.def("KnowsAttr", &BVolume::KnowsAttr, "")
.def("KnowsQuery", &BVolume::KnowsQuery, "")
.def("__eq__", &BVolume::operator==, "", py::arg("volume"))
.def("__ne__", &BVolume::operator!=, "", py::arg("volume"))
.def("operator=", &BVolume::operator=, "", py::arg("volume"))
;


}
