#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/BufferedDataIO.h>
#include <support/DataIO.h>

namespace py = pybind11;

class PyBBufferedDataIO : public BBufferedDataIO{
	public:
        using BBufferedDataIO::BBufferedDataIO;
        ssize_t	Read(void* buffer, size_t size) override {
            PYBIND11_OVERLOAD(ssize_t, BBufferedDataIO, Read, buffer, size);
        }
        ssize_t				Write(const void* buffer, size_t size) override {
            PYBIND11_OVERLOAD(ssize_t, BBufferedDataIO, Write, buffer, size);
        }
};

ssize_t ReadWrapper(BBufferedDataIO& self, py::buffer buffer) {
    py::buffer_info info = buffer.request();
    
    if (info.ndim != 1) {
        throw std::runtime_error("Buffer should be one-dimensional");
    }

    if (info.itemsize != 1) {
        throw std::runtime_error("Buffer elements should be of size 1 byte");
    }

    return self.Read(info.ptr, info.size);
};

ssize_t WriteWrapper(BBufferedDataIO& self, py::buffer buffer) {
    py::buffer_info info = buffer.request();

    if (info.ndim != 1) {
        throw std::runtime_error("Buffer should be one-dimensional");
    }

    if (info.itemsize != 1) {
        throw std::runtime_error("Buffer elements should be of size 1 byte");
    }

    return self.Write(info.ptr, info.size);
};

PYBIND11_MODULE(BufferedDataIO, m)
{
py::class_<BBufferedDataIO, PyBBufferedDataIO, BDataIO>(m, "BBufferedDataIO")
.def(py::init<BDataIO&, size_t, bool, bool>(), "", py::arg("stream") ,py::arg("bufferSize")=65536L, py::arg("ownsStream")=true, py::arg("partialReads")=false)
.def("InitCheck", &BBufferedDataIO::InitCheck, "")
.def("Stream", &BBufferedDataIO::Stream, "")
.def("BufferSize", &BBufferedDataIO::BufferSize, "")
.def("OwnsStream", &BBufferedDataIO::OwnsStream, "")
.def("SetOwnsStream", &BBufferedDataIO::SetOwnsStream, "", py::arg("ownsStream"))
.def("Flush", &BBufferedDataIO::Flush, "")
//.def("Read", &BBufferedDataIO::Read, "", py::arg("buffer"), py::arg("size")) // change to correctly handle void* buffer
.def("Read", &ReadWrapper, "", py::arg("buffer")) //TODO test this
/* in python:
buffered_io = mymodule.BBufferedDataIO()
buffer = bytearray(1024)
read_bytes = buffered_io.Read(buffer)*/
//.def("Write", &BBufferedDataIO::Write, "", py::arg("buffer"), py::arg("size")) // change to correctly handle void* buffer
.def("Write", &WriteWrapper, "", py::arg("buffer")) //TODO test this
/*in python:
buffered_io = mymodule.BBufferedDataIO()
data = bytearray(b"Hello, world!")
written_bytes = buffered_io.Write(data)*/
;


}
