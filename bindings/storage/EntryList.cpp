#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <EntryList.h>
#include <Entry.h>

namespace py = pybind11;

class PyBEntryList : public BEntryList {
public:
    using BEntryList::BEntryList;
    status_t			GetNextEntry(BEntry* entry, bool traverse = false)  override {
        PYBIND11_OVERLOAD_PURE(status_t, BEntryList, GetNextEntry, entry, traverse);
    }
	status_t			GetNextRef(entry_ref* ref) override {
        PYBIND11_OVERLOAD_PURE(status_t, BEntryList, GetNextRef, ref);
    }
	int32				GetNextDirents(struct dirent* direntBuffer, size_t bufferSize, int32 maxEntries = INT_MAX) override {
        PYBIND11_OVERLOAD_PURE(int32, BEntryList, GetNextDirents, direntBuffer, bufferSize, maxEntries);
    }
	status_t			Rewind() override {
        PYBIND11_OVERLOAD_PURE(status_t, BEntryList, Rewind);
    }
	int32				CountEntries() override {
        PYBIND11_OVERLOAD_PURE(int32, BEntryList, CountEntries);
    }
};

PYBIND11_MODULE(EntryList, m)
{
py::class_<BEntryList,PyBEntryList>(m, "BEntryList")
.def(py::init(), "")
.def("GetNextEntry", &BEntryList::GetNextEntry, "", py::arg("entry"), py::arg("traverse")=false)
.def("GetNextRef", &BEntryList::GetNextRef, "", py::arg("ref"))
.def("GetNextDirents", &BEntryList::GetNextDirents, "", py::arg("direntBuffer"), py::arg("bufferSize"), py::arg("maxEntries")=INT_MAX)
.def("Rewind", &BEntryList::Rewind, "")
.def("CountEntries", &BEntryList::CountEntries, "")
;


}
