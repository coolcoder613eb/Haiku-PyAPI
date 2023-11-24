#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <File.h>

namespace py = pybind11;


void define_File(py::module_& m)
{
py::class_<BFile, BNode, BPositionIO>(m, "BFile")
.def(py::init(), "")
.def(py::init<const BFile &>(), "", py::arg("file"))
.def(py::init<const entry_ref *, unsigned int>(), "", py::arg("ref"), py::arg("openMode"))
.def(py::init<const BEntry *, unsigned int>(), "", py::arg("entry"), py::arg("openMode"))
.def(py::init<const char *, unsigned int>(), "", py::arg("path"), py::arg("openMode"))
.def(py::init<const BDirectory *, const char *, unsigned int>(), "", py::arg("dir"), py::arg("path"), py::arg("openMode"))
.def("SetTo", py::overload_cast<const entry_ref *, unsigned int>(&BFile::SetTo), "", py::arg("ref"), py::arg("openMode"))
.def("SetTo", py::overload_cast<const BEntry *, unsigned int>(&BFile::SetTo), "", py::arg("entry"), py::arg("openMode"))
.def("SetTo", py::overload_cast<const char *, unsigned int>(&BFile::SetTo), "", py::arg("path"), py::arg("openMode"))
.def("SetTo", py::overload_cast<const BDirectory *, const char *, unsigned int>(&BFile::SetTo), "", py::arg("dir"), py::arg("path"), py::arg("openMode"))
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
