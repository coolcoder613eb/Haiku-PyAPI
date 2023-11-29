#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/BufferedDataIO.h>

namespace py = pybind11;


void define_BufferedDataIO(py::module_& m)
{
py::class_<BBufferedDataIO, BDataIO>(m, "BBufferedDataIO")
.def(py::init<size_t, bool, bool>(), "", py::arg("bufferSize")=65536 L, py::arg("ownsStream")=true, py::arg("partialReads")=false)
.def("InitCheck", &BBufferedDataIO::InitCheck, "")
.def("Stream", &BBufferedDataIO::Stream, "")
.def("BufferSize", &BBufferedDataIO::BufferSize, "")
.def("OwnsStream", &BBufferedDataIO::OwnsStream, "")
.def("SetOwnsStream", &BBufferedDataIO::SetOwnsStream, "", py::arg("ownsStream"))
.def("Flush", &BBufferedDataIO::Flush, "")
.def("Read", &BBufferedDataIO::Read, "", py::arg("buffer"), py::arg("size"))
.def("Write", &BBufferedDataIO::Write, "", py::arg("buffer"), py::arg("size"))
;


}
