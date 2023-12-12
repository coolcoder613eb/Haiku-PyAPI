#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <translation/BitmapStream.h>

namespace py = pybind11;


void define_BitmapStream(py::module_& m)
{
py::class_<BBitmapStream, BPositionIO>(m, "BBitmapStream")
.def(py::init<BBitmap *>(), "", py::arg("bitmap")=NULL)
.def("ReadAt", &BBitmapStream::ReadAt, "", py::arg("offset"), py::arg("buffer"), py::arg("size"))
.def("WriteAt", &BBitmapStream::WriteAt, "", py::arg("offset"), py::arg("buffer"), py::arg("size"))
.def("Seek", &BBitmapStream::Seek, "", py::arg("position"), py::arg("seekMode"))
.def("Position", &BBitmapStream::Position, "")
.def("Size", &BBitmapStream::Size, "")
.def("SetSize", &BBitmapStream::SetSize, "", py::arg("size"))
.def("DetachBitmap", &BBitmapStream::DetachBitmap, "", py::arg("_bitmap"))
;


}
