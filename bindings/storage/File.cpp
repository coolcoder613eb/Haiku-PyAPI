#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <File.h>
#include <DataIO.h>
#include <Node.h>
#include <StorageDefs.h>
#include <Entry.h>
#include <Directory.h>

namespace py = pybind11;

class PyBFile : public BFile {
public:
    using BFile::BFile;
    ssize_t Read(void *buffer, size_t size)  override {
        PYBIND11_OVERLOAD(ssize_t, BFile, Read, buffer, size);
    }
    ssize_t ReadAt(off_t location, void *buffer, size_t size)  override {
        PYBIND11_OVERLOAD(ssize_t, BFile, ReadAt, location, buffer, size);
    }
    ssize_t Write(const void *buffer, size_t size)  override {
        PYBIND11_OVERLOAD(ssize_t, BFile, Write, buffer, size);
    }
    ssize_t WriteAt(off_t location, const void *buffer, size_t size)  override {
        PYBIND11_OVERLOAD(ssize_t, BFile, WriteAt, location, buffer, size);
    }
    off_t Seek(off_t offset, uint32 seekMode)  override {
        PYBIND11_OVERLOAD(off_t, BFile, Seek, offset, seekMode);
    }
    off_t Position() const  override {
        PYBIND11_OVERLOAD(off_t, BFile, Position);
    }
    status_t SetSize(off_t size)  override {
        PYBIND11_OVERLOAD(status_t, BFile, SetSize, size);
    }
    status_t GetSize(off_t* size) const  override {
        PYBIND11_OVERLOAD(status_t, BFile, GetSize, size);
    }
};

PYBIND11_MODULE(File, m)
{
py::class_<BFile, BNode, BPositionIO>(m, "BFile")
.def(py::init(), "")
.def(py::init<const BFile &>(), "", py::arg("file"))
.def(py::init<const entry_ref *, unsigned int32>(), "", py::arg("ref"), py::arg("openMode"))
.def(py::init<const BEntry *, unsigned int32>(), "", py::arg("entry"), py::arg("openMode"))
.def(py::init<const char *, unsigned int32>(), "", py::arg("path"), py::arg("openMode"))
.def(py::init<const BDirectory *, const char *, unsigned int32>(), "", py::arg("dir"), py::arg("path"), py::arg("openMode"))
.def("SetTo", py::overload_cast<const entry_ref *, unsigned int32>(&BFile::SetTo), "", py::arg("ref"), py::arg("openMode"))
.def("SetTo", py::overload_cast<const BEntry *, unsigned int32>(&BFile::SetTo), "", py::arg("entry"), py::arg("openMode"))
.def("SetTo", py::overload_cast<const char *, unsigned int32>(&BFile::SetTo), "", py::arg("path"), py::arg("openMode"))
.def("SetTo", py::overload_cast<const BDirectory *, const char *, unsigned int32>(&BFile::SetTo), "", py::arg("dir"), py::arg("path"), py::arg("openMode"))
.def("IsReadable", &BFile::IsReadable, "")
.def("IsWritable", &BFile::IsWritable, "")
.def("Read", &BFile::Read, "", py::arg("buffer"), py::arg("size"))
.def("ReadAt", &BFile::ReadAt, "", py::arg("location"), py::arg("buffer"), py::arg("size"))
.def("Write", &BFile::Write, "", py::arg("buffer"), py::arg("size"))
.def("WriteAt", &BFile::WriteAt, "", py::arg("location"), py::arg("buffer"), py::arg("size"))
.def("Seek", &BFile::Seek, "", py::arg("offset"), py::arg("seekMode"))
.def("Position", &BFile::Position, "")
.def("SetSize", &BFile::SetSize, "", py::arg("size"))
.def("GetSize", &BFile::GetSize, "", py::arg("size"))
.def("operator=", &BFile::operator=, "", py::arg("file"))
;


}
