#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <ResourceStrings.h>
#include <String.h>

namespace py = pybind11;
//using namespace BPrivate;
//using namespace BPrivate::Storage;
//using namespace BPrivate::Storage::Mime;
//using namespace BPackageKit;

class PyBResourceStrings : public BResourceStrings{
	public:
        using BResourceStrings::BResourceStrings;
        BString*	NewString(int32 id) override {
            PYBIND11_OVERLOAD(BString*, BResourceStrings, NewString, id);
        }
        const char*	FindString(int32 id) override {
            PYBIND11_OVERLOAD(const char*, BResourceStrings, FindString, id);
        }
        status_t	SetStringFile(const entry_ref* ref) override {
            PYBIND11_OVERLOAD(status_t, BResourceStrings, SetStringFile, ref);
        }
};

PYBIND11_MODULE(ResourceStrings, m)
{
py::class_<BResourceStrings>(m, "BResourceStrings")
.def(py::init(), "")
.def(py::init<const entry_ref &>(), "", py::arg("ref"))
.def("InitCheck", &BResourceStrings::InitCheck, "")
.def("NewString", &BResourceStrings::NewString, "", py::arg("id"))
.def("FindString", &BResourceStrings::FindString, "", py::arg("id"))
.def("SetStringFile", &BResourceStrings::SetStringFile, "", py::arg("ref"))
.def("GetStringFile", &BResourceStrings::GetStringFile, "", py::arg("outRef"))
;
/* it's protected(?)
py::class_<_string_id_hash>(m, "_string_id_hash")
.def(py::init(), "")
.def("assign_string", &_string_id_hash::assign_string, "", py::arg("str"), py::arg("makeCopy"))
.def_readwrite("next", &_string_id_hash::next, "")
.def_readwrite("id", &_string_id_hash::id, "")
.def_readwrite("data", &_string_id_hash::data, "")
.def_readwrite("data_alloced", &_string_id_hash::data_alloced, "")
.def_readwrite("_reserved1", &_string_id_hash::_reserved1, "")
.def_readwrite("_reserved2", &_string_id_hash::_reserved2, "")
;
*/

}
