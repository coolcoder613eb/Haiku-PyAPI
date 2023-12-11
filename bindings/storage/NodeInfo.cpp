#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>
#include <pybind11/numpy.h>

#include <NodeInfo.h>
#include <Bitmap.h>

namespace py = pybind11;
using namespace BPrivate;
using namespace BPrivate::Storage;
using namespace BPrivate::Storage::Mime;

PYBIND11_MODULE(NodeInfo, m)
{
py::class_<BNodeInfo>(m, "BNodeInfo")
.def(py::init(), "")
.def(py::init<BNode *>(), "", py::arg("node"))
.def("SetTo", &BNodeInfo::SetTo, "", py::arg("node"))
.def("InitCheck", &BNodeInfo::InitCheck, "")
.def("GetType", &BNodeInfo::GetType, "", py::arg("type"))
.def("SetType", &BNodeInfo::SetType, "", py::arg("type"))
.def("GetIcon", py::overload_cast<BBitmap *, icon_size>(&BNodeInfo::GetIcon, py::const_), "", py::arg("icon"), py::arg("which")=B_LARGE_ICON)
/*
.def("GetIcon_toBitmap", [](const BNodeInfo& self, icon_size which){
            BBitmap *icon;
            if(which==B_LARGE_ICON){
            	icon = new BBitmap(BRect(0, 0, 31, 31), B_RGBA32);
            } else {
            	icon = new BBitmap(BRect(0, 0, 15, 15), B_RGBA32);
            }
            status_t result = self.GetIcon(icon, which);
            return std::make_tuple(result, icon);
}, "", py::arg("which")=B_LARGE_ICON)*/
.def("SetIcon", py::overload_cast<const BBitmap *, icon_size>(&BNodeInfo::SetIcon), "", py::arg("icon"), py::arg("which")=B_LARGE_ICON)
//.def("GetIcon", py::overload_cast<unsigned char, size_t *, type_code *>(&BNodeInfo::GetIcon, py::const_), "", py::arg("data"), py::arg("size"), py::arg("type"))
.def("GetIcon", [](const BNodeInfo& self, py::list& _data, size_t& _size, type_code& _type) {
            uint8* data = nullptr;
            size_t size = 0;
            type_code type = 0;
            status_t result = self.GetIcon(&data, &size, &type);
            for (size_t i = 0; i < size; ++i) {
                _data.append(data[i]);
            }
            _size = size;
            _type = type;
            delete[] data;
            return result;
},"", py::arg("_data"), py::arg("_size"), py::arg("_type"))
/*.def("GetIcon_toArray", [](const BNodeInfo &self) {
            size_t size;
            type_code type;
            uint8_t *data;
            status_t result = self.GetIcon(&data, &size, &type);
            auto capsule = py::capsule(data, [](void *d) {
                delete[] static_cast<uint8_t *>(d);
            });
            return std::make_tuple(result, py::array_t<uint8_t>({static_cast<ssize_t>(size)}, {sizeof(uint8_t)}, data, capsule), type);
}, "")*/
.def("SetIcon", py::overload_cast<const uint8*, size_t>(&BNodeInfo::SetIcon), "", py::arg("data"), py::arg("size"))
.def("GetPreferredApp", &BNodeInfo::GetPreferredApp, "", py::arg("signature"), py::arg("verb")=B_OPEN)
.def("SetPreferredApp", &BNodeInfo::SetPreferredApp, "", py::arg("signature"), py::arg("verb")=B_OPEN)
.def("GetAppHint", &BNodeInfo::GetAppHint, "", py::arg("ref"))
.def("SetAppHint", &BNodeInfo::SetAppHint, "", py::arg("ref"))
.def("GetTrackerIcon", py::overload_cast<BBitmap *, icon_size>(&BNodeInfo::GetTrackerIcon, py::const_), "", py::arg("icon"), py::arg("which")=B_LARGE_ICON)// TODO
.def_static("GetTrackerIcon_static", py::overload_cast<const entry_ref *, BBitmap *, icon_size>(&BNodeInfo::GetTrackerIcon), "", py::arg("ref"), py::arg("icon"), py::arg("which")=B_LARGE_ICON)
;


}
