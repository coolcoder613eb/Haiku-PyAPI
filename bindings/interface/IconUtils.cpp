#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/IconUtils.h>
#include <Mime.h>

namespace py = pybind11;


PYBIND11_MODULE(IconUtils,m)
{
py::class_<BIconUtils>(m, "BIconUtils")
.def_static("GetIcon", &BIconUtils::GetIcon, "", py::arg("node"), py::arg("vectorIconAttrName"), py::arg("smallIconAttrName"), py::arg("largeIconAttrName"), py::arg("size"), py::arg("result"))
.def_static("GetVectorIcon", py::overload_cast<BNode *, const char *, BBitmap *>(&BIconUtils::GetVectorIcon), "", py::arg("node"), py::arg("attrName"), py::arg("result"))
.def_static("GetVectorIcon", py::overload_cast<unsigned char, size_t, BBitmap *>(&BIconUtils::GetVectorIcon), "", py::arg("buffer"), py::arg("size"), py::arg("result"))
.def_static("GetCMAP8Icon", &BIconUtils::GetCMAP8Icon, "", py::arg("node"), py::arg("smallIconAttrName"), py::arg("largeIconAttrName"), py::arg("size"), py::arg("icon"))
.def_static("ConvertFromCMAP8", py::overload_cast<BBitmap *, BBitmap *>(&BIconUtils::ConvertFromCMAP8), "", py::arg("source"), py::arg("result"))
.def_static("ConvertToCMAP8", py::overload_cast<BBitmap *, BBitmap *>(&BIconUtils::ConvertToCMAP8), "", py::arg("source"), py::arg("result"))
.def_static("ConvertFromCMAP8", py::overload_cast<unsigned char, unsigned int, unsigned int, unsigned int, BBitmap *>(&BIconUtils::ConvertFromCMAP8), "", py::arg("data"), py::arg("width"), py::arg("height"), py::arg("bytesPerRow"), py::arg("result"))
.def_static("ConvertToCMAP8", py::overload_cast<unsigned char, unsigned int, unsigned int, unsigned int, BBitmap *>(&BIconUtils::ConvertToCMAP8), "", py::arg("data"), py::arg("width"), py::arg("height"), py::arg("bytesPerRow"), py::arg("result"))
;


}
