#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <locale/DurationFormat.h>
#include <locale/TimeZone.h>

namespace py = pybind11;
using namespace U_ICU_NAMESPACE;

PYBIND11_MODULE(DurationFormat, m)
{
//m.attr("GregorianCalendar") = py::cast(GregorianCalendar); //TODO try to fix this gregocal.h in icu74 d

py::class_<BDurationFormat, BFormat>(m, "BDurationFormat")
.def(py::init<const BLanguage &, const BFormattingConventions &, const BString &, const time_unit_style>(), "", py::arg("language"), py::arg("conventions"), py::arg("separator")=", ", py::arg("style")=B_TIME_UNIT_FULL)
.def(py::init<const BString &, const time_unit_style>(), "", py::arg("separator")=", ", py::arg("style")=B_TIME_UNIT_FULL)
.def(py::init<const BDurationFormat &>(), "", py::arg("other"))
.def("SetSeparator", &BDurationFormat::SetSeparator, "", py::arg("separator"))
.def("SetTimeZone", &BDurationFormat::SetTimeZone, "", py::arg("timeZone"))
.def("Format", [](BDurationFormat& self,const bigtime_t startValue,const bigtime_t stopValue) {
    BString  buffer;
    status_t r = self.Format(buffer, startValue, stopValue);
    return std::make_tuple(r,buffer);
}
, "", py::arg("startValue"), py::arg("stopValue"))
;


}
