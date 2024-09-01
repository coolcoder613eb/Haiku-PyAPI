#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <locale/TimeZone.h>

namespace py = pybind11;
using namespace U_ICU_NAMESPACE;

void define_TimeZone(py::module_& m)
{
m.attr("Locale") = py::cast(Locale);

m.attr("TimeZone") = py::cast(TimeZone);

py::class_<BTimeZone>(m, "BTimeZone")
.def(py::init<const char *, const BLanguage *>(), "", py::arg("zoneID")=NULL, py::arg("language")=NULL)
.def(py::init<const BTimeZone &>(), "", py::arg("other"))
.def("operator=", &BTimeZone::operator=, "", py::arg("source"))
.def("ID", &BTimeZone::ID, "")
.def("Name", &BTimeZone::Name, "")
.def("DaylightSavingName", &BTimeZone::DaylightSavingName, "")
.def("ShortName", &BTimeZone::ShortName, "")
.def("ShortDaylightSavingName", &BTimeZone::ShortDaylightSavingName, "")
.def("OffsetFromGMT", &BTimeZone::OffsetFromGMT, "")
.def("SupportsDaylightSaving", &BTimeZone::SupportsDaylightSaving, "")
.def("InitCheck", &BTimeZone::InitCheck, "")
.def("SetTo", &BTimeZone::SetTo, "", py::arg("zoneID"), py::arg("language")=NULL)
.def("SetLanguage", &BTimeZone::SetLanguage, "", py::arg("language"))
.def_readwrite("kNameOfGmtZone", &BTimeZone::kNameOfGmtZone, "")
.def_readwrite("Private", &BTimeZone::Private, "")
;


}
