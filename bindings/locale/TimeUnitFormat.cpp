#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <locale/TimeUnitFormat.h>

namespace py = pybind11;
using namespace U_ICU_NAMESPACE;

PYBIND11_MODULE(TimeUnitFormat, m)
{
py::enum_<time_unit_style>(m, "time_unit_style", "")
.value("B_TIME_UNIT_ABBREVIATED", time_unit_style::B_TIME_UNIT_ABBREVIATED, "")
.value("B_TIME_UNIT_FULL", time_unit_style::B_TIME_UNIT_FULL, "")
.export_values();

py::enum_<time_unit_element>(m, "time_unit_element", "")
.value("B_TIME_UNIT_YEAR", time_unit_element::B_TIME_UNIT_YEAR, "")
.value("B_TIME_UNIT_MONTH", time_unit_element::B_TIME_UNIT_MONTH, "")
.value("B_TIME_UNIT_WEEK", time_unit_element::B_TIME_UNIT_WEEK, "")
.value("B_TIME_UNIT_DAY", time_unit_element::B_TIME_UNIT_DAY, "")
.value("B_TIME_UNIT_HOUR", time_unit_element::B_TIME_UNIT_HOUR, "")
.value("B_TIME_UNIT_MINUTE", time_unit_element::B_TIME_UNIT_MINUTE, "")
.value("B_TIME_UNIT_SECOND", time_unit_element::B_TIME_UNIT_SECOND, "")
.value("B_TIME_UNIT_LAST", time_unit_element::B_TIME_UNIT_LAST, "")
.export_values();

//m.attr("TimeUnitFormat") = py::cast(TimeUnitFormat); TODO try to fix this, it's in ICU

py::class_<BTimeUnitFormat, BFormat>(m, "BTimeUnitFormat")
.def(py::init<const time_unit_style>(), "", py::arg("style")=B_TIME_UNIT_FULL)
.def(py::init<const BLanguage &, const BFormattingConventions &, const time_unit_style>(), "", py::arg("language"), py::arg("conventions"), py::arg("style")=B_TIME_UNIT_FULL)
.def(py::init<const BTimeUnitFormat &>(), "", py::arg("other"))
.def("Format", [](BTimeUnitFormat& self,int value,const time_unit_element unit) {
    BString  buffer;
    status_t r = self.Format(buffer, value, unit);
    return std::make_tuple(r,buffer);
}
, "", py::arg("value"), py::arg("unit"))
;


}
