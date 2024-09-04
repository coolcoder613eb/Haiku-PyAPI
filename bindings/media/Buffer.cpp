#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <media/Buffer.h>

namespace py = pybind11;
using namespace BPrivate;

PYBIND11_MODULE(Buffer, m)
{
//m.attr("BufferCache") = py::cast(BufferCache);

//m.attr("SharedBufferList") = py::cast(SharedBufferList);

py::class_<buffer_clone_info>(m, "buffer_clone_info")
.def(py::init(), "")
.def_readwrite("buffer", &buffer_clone_info::buffer, "")
.def_readwrite("area", &buffer_clone_info::area, "")
.def_readwrite("offset", &buffer_clone_info::offset, "")
.def_readwrite("size", &buffer_clone_info::size, "")
.def_readwrite("flags", &buffer_clone_info::flags, "")
;

py::class_<BBuffer, std::unique_ptr<BBuffer,py::nodelete>>(m, "BBuffer")
.def("Data", &BBuffer::Data, "")
.def("SizeAvailable", &BBuffer::SizeAvailable, "")
.def("SizeUsed", &BBuffer::SizeUsed, "")
.def("SetSizeUsed", &BBuffer::SetSizeUsed, "", py::arg("used"))
.def("Flags", &BBuffer::Flags, "")
.def("Recycle", &BBuffer::Recycle, "")
.def("CloneInfo", &BBuffer::CloneInfo, "")
.def("ID", &BBuffer::ID, "")
.def("Type", &BBuffer::Type, "")
.def("Header", &BBuffer::Header, "")
.def("AudioHeader", &BBuffer::AudioHeader, "")
.def("VideoHeader", &BBuffer::VideoHeader, "")
.def("Size", &BBuffer::Size, "")
;

m.attr("B_F1_BUFFER") = 0x1;

m.attr("B_F2_BUFFER") = 0x2;

m.attr("B_SMALL_BUFFER") = 0x80000000;

py::class_<BSmallBuffer, BBuffer>(m, "BSmallBuffer")
.def(py::init(), "")
.def_static("SmallBufferSizeLimit", &BSmallBuffer::SmallBufferSizeLimit, "")
;


}
