#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/DataIO.h>

namespace py = pybind11;

class PyBDataIO : public BDataIO {
public:
    ssize_t				Read(void* buffer, size_t size) override {
        PYBIND11_OVERLOAD(ssize_t, BDataIO, Read, buffer, size);
    }
	ssize_t				Write(const void* buffer, size_t size) override {
        PYBIND11_OVERLOAD(ssize_t, BDataIO, Write, buffer, size);
    }
    status_t			Flush() override {
    	PYBIND11_OVERLOAD(status_t, BDataIO, Flush);
    }
};


class PyBPositionIO : public BPositionIO {
public:
	using BPositionIO::Seek;
    using BPositionIO::Position;
    using BPositionIO::BPositionIO;
    ssize_t				Read(void* buffer, size_t size) override {
        PYBIND11_OVERLOAD(ssize_t, BPositionIO, Read, buffer, size);
    }
	ssize_t				Write(const void* buffer, size_t size) override {
        PYBIND11_OVERLOAD(ssize_t, BPositionIO, Write, buffer, size);
    }
    ssize_t ReadAt(off_t position, void* buffer, size_t size) override {
        PYBIND11_OVERLOAD_PURE(ssize_t, BPositionIO, ReadAt, position, buffer, size);
    }
    ssize_t WriteAt(off_t position, const void* buffer, size_t size) override {
        PYBIND11_OVERLOAD_PURE(ssize_t, BPositionIO, WriteAt, position, buffer, size);
    }
    off_t Seek(off_t position, uint32 seekMode) override {
        PYBIND11_OVERLOAD_PURE(off_t, BPositionIO, Seek, position, seekMode);
    }
    off_t Position() const override {
        PYBIND11_OVERLOAD_PURE(off_t, BPositionIO, Position);
    }
    status_t SetSize(off_t size) override {
        PYBIND11_OVERLOAD(status_t, BPositionIO, SetSize, size);
    }
    status_t			GetSize(off_t* size) const override {
        PYBIND11_OVERLOAD(status_t, BPositionIO, GetSize, size);
    }
};

class PyBMemoryIO : public BMemoryIO {
public:
    ssize_t				ReadAt(off_t position, void* buffer, size_t size) override {
        PYBIND11_OVERLOAD(ssize_t, BMemoryIO, ReadAt, position, buffer, size);
    }
	ssize_t				WriteAt(off_t position, const void* buffer, size_t size) override {
        PYBIND11_OVERLOAD(ssize_t, BMemoryIO, WriteAt, position, buffer, size);
    }
    off_t				Seek(off_t position, uint32 seekMode) override {
    	PYBIND11_OVERLOAD(off_t, BMemoryIO, Seek, position, seekMode);
    }
    off_t				Position() const override {
    	PYBIND11_OVERLOAD(off_t, BMemoryIO, Position);
    }
    status_t			SetSize(off_t size) override {
    	PYBIND11_OVERLOAD(status_t, BMemoryIO, SetSize, size);
    }
};

class PyBMallocIO : public BMallocIO {
public:
    ssize_t				ReadAt(off_t position, void* buffer, size_t size) override {
        PYBIND11_OVERLOAD(ssize_t, BMallocIO, ReadAt, position, buffer, size);
    }
	ssize_t				WriteAt(off_t position, const void* buffer, size_t size) override {
        PYBIND11_OVERLOAD(ssize_t, BMallocIO, WriteAt, position, buffer, size);
    }
    off_t				Seek(off_t position, uint32 seekMode) override {
    	PYBIND11_OVERLOAD(off_t, BMallocIO, Seek, position, seekMode);
    }
    off_t				Position() const override {
    	PYBIND11_OVERLOAD(off_t, BMallocIO, Position);
    }
    status_t			SetSize(off_t size) override {
    	PYBIND11_OVERLOAD(status_t, BMallocIO, SetSize, size);
    }
};


PYBIND11_MODULE(DataIO, m)
{
py::class_<BDataIO, PyBDataIO>(m, "BDataIO")
.def(py::init(), "")
.def("Read", &BDataIO::Read, "", py::arg("buffer"), py::arg("size"))
.def("Write", &BDataIO::Write, "", py::arg("buffer"), py::arg("size"))
.def("Flush", &BDataIO::Flush, "")
.def("ReadExactly", &BDataIO::ReadExactly, "", py::arg("buffer"), py::arg("size"), py::arg("_bytesRead")=NULL)
.def("WriteExactly", &BDataIO::WriteExactly, "", py::arg("buffer"), py::arg("size"), py::arg("_bytesWritten")=NULL)
;

/*
py::class_<BPositionIO, PyBPositionIO, BDataIO>(m, "BPositionIO");
py::class_<BMemoryIO,PyBMemoryIO, BPositionIO>(m, "BMemoryIO");
py::class_<BMallocIO,PyBMallocIO, BPositionIO>(m, "BMallocIO");
*/
py::class_<BPositionIO, PyBPositionIO, BDataIO>(m, "BPositionIO")
//py::class_<PyBPositionIO, std::shared_ptr<PyBPositionIO>>(m, "BPositionIO")
.def(py::init(), "")
.def("Read", &BPositionIO::Read, "", py::arg("buffer"), py::arg("size"))
.def("Write", &BPositionIO::Write, "", py::arg("buffer"), py::arg("size"))
//.def("ReadAt", &BPositionIO::ReadAt, "", py::arg("position"), py::arg("buffer"), py::arg("size"))
//.def("WriteAt", &BPositionIO::WriteAt, "", py::arg("position"), py::arg("buffer"), py::arg("size"))
.def("ReadAtExactly", &BPositionIO::ReadAtExactly, "", py::arg("position"), py::arg("buffer"), py::arg("size"), py::arg("_bytesRead")=NULL)
.def("WriteAtExactly", &BPositionIO::WriteAtExactly, "", py::arg("position"), py::arg("buffer"), py::arg("size"), py::arg("_bytesWritten")=NULL)
.def("Seek", &BPositionIO::Seek, "", py::arg("position"), py::arg("seekMode"))
.def("Position", &BPositionIO::Position, "")
.def("SetSize", &BPositionIO::SetSize, "", py::arg("size"))
.def("GetSize", &BPositionIO::GetSize, "", py::arg("size"))
;

py::class_<BMemoryIO, PyBMemoryIO, BPositionIO>(m, "BMemoryIO")
//py::class_<PyBMemoryIO, std::shared_ptr<PyBMemoryIO>>(m, "BMemoryIO")
//.def(py::init<void *, size_t>(), "", py::arg("data"), py::arg("length"))
//.def(py::init<const void *, size_t>(), "", py::arg("data"), py::arg("length"))
.def("ReadAt", &BMemoryIO::ReadAt, "", py::arg("position"), py::arg("buffer"), py::arg("size"))
.def("WriteAt", &BMemoryIO::WriteAt, "", py::arg("position"), py::arg("buffer"), py::arg("size"))
.def("Seek", &BMemoryIO::Seek, "", py::arg("position"), py::arg("seekMode"))
.def("Position", &BMemoryIO::Position, "")
.def("SetSize", &BMemoryIO::SetSize, "", py::arg("size"))
;

py::class_<BMallocIO,PyBMallocIO, BPositionIO>(m, "BMallocIO")
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
