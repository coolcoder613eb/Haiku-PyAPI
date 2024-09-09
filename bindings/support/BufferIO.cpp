#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/BufferIO.h>

namespace py = pybind11;

class PyBBufferIO : public BBufferIO{
	public:
        using BBufferIO::BBufferIO;
        ssize_t				ReadAt(off_t pos, void* buffer, size_t size) override {
            PYBIND11_OVERLOAD(ssize_t, BBufferIO, ReadAt, pos, buffer, size);
        }
        ssize_t				WriteAt(off_t pos, const void* buffer, size_t size) override {
            PYBIND11_OVERLOAD(ssize_t, BBufferIO, WriteAt, pos, buffer, size);
        }
        off_t				Seek(off_t position, uint32 seekMode) override {
            PYBIND11_OVERLOAD(off_t, BBufferIO, Seek, position, seekMode);
        }
        off_t				Position() const override {
            PYBIND11_OVERLOAD(off_t, BBufferIO, Position);
        }
        status_t			SetSize(off_t size) override {
            PYBIND11_OVERLOAD(status_t, BBufferIO, SetSize, size);
        }
        status_t			Flush() override {
            PYBIND11_OVERLOAD(status_t, BBufferIO, Flush);
        }
};


ssize_t ReadAtWrapper(BBufferIO& self, off_t pos, py::buffer buffer) {
    py::buffer_info info = buffer.request();
    
    if (info.ndim != 1) {
        throw std::runtime_error("Buffer should be one-dimensional");
    }

    if (info.itemsize != 1) {
        throw std::runtime_error("Buffer elements should be of size 1 byte");
    }

    return self.ReadAt(pos, info.ptr, info.size);
};

ssize_t WriteAtWrapper(BBufferIO& self, off_t pos, py::buffer buffer) {
    py::buffer_info info = buffer.request();

    if (info.ndim != 1) {
        throw std::runtime_error("Buffer should be one-dimensional");
    }

    if (info.itemsize != 1) {
        throw std::runtime_error("Buffer elements should be of size 1 byte");
    }

    return self.WriteAt(pos, info.ptr, info.size);
};

PYBIND11_MODULE(BufferIO, m)
{
py::class_<BBufferIO, PyBBufferIO, BPositionIO>(m, "BBufferIO")
.def(py::init<BPositionIO *, size_t, bool>(), "", py::arg("stream"), py::arg("bufferSize")=65536L, py::arg("ownsStream")=true)
//.def("ReadAt", &BBufferIO::ReadAt, "", py::arg("pos"), py::arg("buffer"), py::arg("size"))
.def("ReadAt", &ReadAtWrapper, "", py::arg("pos"), py::arg("buffer"))
//.def("WriteAt", &BBufferIO::WriteAt, "", py::arg("pos"), py::arg("buffer"), py::arg("size"))
.def("WriteAt", &WriteAtWrapper, "", py::arg("pos"), py::arg("buffer"))
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
