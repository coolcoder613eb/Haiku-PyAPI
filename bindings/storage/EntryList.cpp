#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <EntryList.h>

namespace py = pybind11;


void define_EntryList(py::module_& m)
{
py::class_<BEntryList>(m, "BEntryList")
.def(py::init(), "")
.def("GetNextEntry", &BEntryList::GetNextEntry, "", py::arg("entry"), py::arg("traverse")=false)
.def("GetNextRef", &BEntryList::GetNextRef, "", py::arg("ref"))
.def("GetNextDirents", &BEntryList::GetNextDirents, "", py::arg("direntBuffer"), py::arg("bufferSize"), py::arg("maxEntries")=INT_MAX)
.def("Rewind", &BEntryList::Rewind, "")
.def("CountEntries", &BEntryList::CountEntries, "")
;


}
