#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/DataIO.h>

namespace py = pybind11;


void define_DataIO(py::module_& m)
{
py::class_<BDataIO>(m, "BDataIO")
.def(py::init(), "")
.def("Read", &BDataIO::Read, "", py::arg("buffer"), py::arg("size"))
.def("Write", &BDataIO::Write, "", py::arg("buffer"), py::arg("size"))
.def("Flush", &BDataIO::Flush, "")
.def("ReadExactly", &BDataIO::ReadExactly, "", py::arg("buffer"), py::arg("size"), py::arg("_bytesRead")=NULL)
.def("WriteExactly", &BDataIO::WriteExactly, "", py::arg("buffer"), py::arg("size"), py::arg("_bytesWritten")=NULL)
;

py::class_<BPositionIO, BDataIO>(m, "BPositionIO")
.def(py::init(), "")
.def("Read", &BPositionIO::Read, "", py::arg("buffer"), py::arg("size"))
.def("Write", &BPositionIO::Write, "", py::arg("buffer"), py::arg("size"))
.def("ReadAt", &BPositionIO::ReadAt, "", py::arg("position"), py::arg("buffer"), py::arg("size"))
.def("WriteAt", &BPositionIO::WriteAt, "", py::arg("position"), py::arg("buffer"), py::arg("size"))
.def("ReadAtExactly", &BPositionIO::ReadAtExactly, "", py::arg("position"), py::arg("buffer"), py::arg("size"), py::arg("_bytesRead")=NULL)
.def("WriteAtExactly", &BPositionIO::WriteAtExactly, "", py::arg("position"), py::arg("buffer"), py::arg("size"), py::arg("_bytesWritten")=NULL)
.def("Seek", &BPositionIO::Seek, "", py::arg("position"), py::arg("seekMode"))
.def("Position", &BPositionIO::Position, "")
.def("SetSize", &BPositionIO::SetSize, "", py::arg("size"))
.def("GetSize", &BPositionIO::GetSize, "", py::arg("size"))
;

py::class_<BMemoryIO, BPositionIO>(m, "BMemoryIO")
.def(py::init<void *, size_t>(), "", py::arg("data"), py::arg("length"))
.def(py::init<const void *, size_t>(), "", py::arg("data"), py::arg("length"))
.def("ReadAt", &BMemoryIO::ReadAt, "", py::arg("position"), py::arg("buffer"), py::arg("size"))
.def("WriteAt", &BMemoryIO::WriteAt, "", py::arg("position"), py::arg("buffer"), py::arg("size"))
.def("Seek", &BMemoryIO::Seek, "", py::arg("position"), py::arg("seekMode"))
.def("Position", &BMemoryIO::Position, "")
.def("SetSize", &BMemoryIO::SetSize, "", py::arg("size"))
;

py::class_<BMallocIO, BPositionIO>(m, "BMallocIO")
.def(py::init(), "")
.def("ReadAt", &BMallocIO::ReadAt, "", py::arg("position"), py::arg("buffer"), py::arg("size"))
.def("WriteAt", &BMallocIO::WriteAt, "", py::arg("position"), py::arg("buffer"), py::arg("size"))
.def("Seek", &BMallocIO::Seek, "", py::arg("position"), py::arg("seekMode"))
.def("Position", &BMallocIO::Position, "")
.def("SetSize", &BMallocIO::SetSize, "", py::arg("size"))
.def("SetBlockSize", &BMallocIO::SetBlockSize, "", py::arg("blockSize"))
.def("Buffer", &BMallocIO::Buffer, "")
.def("BufferLength", &BMallocIO::BufferLength, "")
;


}
