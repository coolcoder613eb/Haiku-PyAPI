#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>
#include <BeBuild.h>

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
.def(py::init<const entry_ref *, uint32>(), "", py::arg("ref"), py::arg("openMode"))
.def(py::init<const BEntry *, uint32>(), "", py::arg("entry"), py::arg("openMode"))
.def(py::init<const char *, uint32>(), "", py::arg("path"), py::arg("openMode"))
.def(py::init<const BDirectory *, const char *, uint32>(), "", py::arg("dir"), py::arg("path"), py::arg("openMode"))
.def("SetTo", py::overload_cast<const entry_ref *, uint32>(&BFile::SetTo), "", py::arg("ref"), py::arg("openMode"))
.def("SetTo", py::overload_cast<const BEntry *, uint32>(&BFile::SetTo), "", py::arg("entry"), py::arg("openMode"))
.def("SetTo", py::overload_cast<const char *, uint32>(&BFile::SetTo), "", py::arg("path"), py::arg("openMode"))
.def("SetTo", py::overload_cast<const BDirectory *, const char *, uint32>(&BFile::SetTo), "", py::arg("dir"), py::arg("path"), py::arg("openMode"))
.def("IsReadable", &BFile::IsReadable, "")
.def("IsWritable", &BFile::IsWritable, "")
//.def("Read", &BFile::Read, "", py::arg("buffer"), py::arg("size"))
.def("Read",[](BFile& self, size_t size)->py::tuple{
	std::vector<char>buffer(size);
	ssize_t bytesRead = self.Read(buffer.data(), size);
	py::bytes pyBytes(buffer.data(),bytesRead);
	return py::make_tuple(pyBytes, bytesRead);
},"", py::arg("size"))
//.def("ReadAt", &BFile::ReadAt, "", py::arg("location"), py::arg("buffer"), py::arg("size"))
.def("ReadAt", [](BFile& self, off_t location, size_t size)->py::tuple{
	std::vector<char>buffer(size);
	ssize_t bytesRead = self.ReadAt(location, buffer.data(), size);
	py::bytes pyBytes(buffer.data(),bytesRead);
	return py::make_tuple(pyBytes, bytesRead);
},"", py::arg("location"),py::arg("size"))
//.def("Write", &BFile::Write, "", py::arg("buffer"), py::arg("size"))
.def("Write", [](BFile& self, py::buffer buffer){
	py::buffer_info info = buffer.request();
	const void* data = info.ptr;
	size_t length = info.size;
	return self.Write(data,length);
}, "",py::arg("buffer"))
//.def("WriteAt", &BFile::WriteAt, "", py::arg("location"), py::arg("buffer"), py::arg("size"))
.def("WriteAt", [](BFile& self, off_t location, py::buffer buffer){
	py::buffer_info info = buffer.request();
	const void* data = info.ptr;
	size_t length = info.size;
	return self.WriteAt(location,data,length);
}, "",py::arg("location"),py::arg("buffer"))
.def("Seek", &BFile::Seek, "", py::arg("offset"), py::arg("seekMode"))
.def("Position", &BFile::Position, "")
.def("SetSize", &BFile::SetSize, "", py::arg("size"))
//.def("GetSize", &BFile::GetSize, "", py::arg("size"))
.def("GetSize", [](BFile& self)->py::tuple{
	off_t size;
	status_t ret = self.GetSize(&size);
	return py::make_tuple(ret,size);
}, "")
.def("__copy__", &BFile::operator=, "", py::arg("file"))
;


}
