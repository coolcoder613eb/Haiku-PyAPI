#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/BufferIO.h>

namespace py = pybind11;


void define_BufferIO(py::module_& m)
{
py::class_<BBufferIO, BPositionIO>(m, "BBufferIO")
.def(py::init<BPositionIO *, size_t, bool>(), "", py::arg("stream"), py::arg("bufferSize")=65536 L, py::arg("ownsStream")=true)
.def("ReadAt", &BBufferIO::ReadAt, "", py::arg("pos"), py::arg("buffer"), py::arg("size"))
.def("WriteAt", &BBufferIO::WriteAt, "", py::arg("pos"), py::arg("buffer"), py::arg("size"))
.def("Seek", &BBufferIO::Seek, "", py::arg("position"), py::arg("seekMode"))
.def("Position", &BBufferIO::Position, "")
.def("SetSize", &BBufferIO::SetSize, "", py::arg("size"))
.def("Flush", &BBufferIO::Flush, "")
.def("Stream", &BBufferIO::Stream, "")
.def("BufferSize", &BBufferIO::BufferSize, "")
.def("OwnsStream", &BBufferIO::OwnsStream, "")
.def("SetOwnsStream", &BBufferIO::SetOwnsStream, "", py::arg("ownsStream"))
.def("PrintToStream", &BBufferIO::PrintToStream, "")
;


}
