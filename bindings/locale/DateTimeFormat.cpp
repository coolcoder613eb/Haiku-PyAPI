#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <locale/DateTimeFormat.h>
#include <locale/Locale.h>
#include <locale/TimeZone.h>

namespace py = pybind11;

PYBIND11_MODULE(DateTimeFormat, m)
{
py::enum_<BDateElement>(m, "BDateElement", "")
.value("B_DATE_ELEMENT_INVALID", BDateElement::B_DATE_ELEMENT_INVALID, "")
.value("B_DATE_ELEMENT_YEAR", BDateElement::B_DATE_ELEMENT_YEAR, "")
.value("B_DATE_ELEMENT_MONTH", BDateElement::B_DATE_ELEMENT_MONTH, "")
.value("B_DATE_ELEMENT_WEEKDAY", BDateElement::B_DATE_ELEMENT_WEEKDAY, "")
.value("B_DATE_ELEMENT_DAY", BDateElement::B_DATE_ELEMENT_DAY, "")
.value("B_DATE_ELEMENT_AM_PM", BDateElement::B_DATE_ELEMENT_AM_PM, "")
.value("B_DATE_ELEMENT_HOUR", BDateElement::B_DATE_ELEMENT_HOUR, "")
.value("B_DATE_ELEMENT_MINUTE", BDateElement::B_DATE_ELEMENT_MINUTE, "")
.value("B_DATE_ELEMENT_SECOND", BDateElement::B_DATE_ELEMENT_SECOND, "")
.value("B_DATE_ELEMENT_TIMEZONE", BDateElement::B_DATE_ELEMENT_TIMEZONE, "")
.export_values();

py::class_<BDateTimeFormat, BFormat>(m, "BDateTimeFormat")
.def(py::init<const BLocale *>(), "", py::arg("locale")=NULL)
.def(py::init<const BLanguage &, const BFormattingConventions &>(), "", py::arg("language"), py::arg("conventions"))
.def(py::init<const BDateTimeFormat &>(), "", py::arg("other"))
.def("SetDateTimeFormat", &BDateTimeFormat::SetDateTimeFormat, "", py::arg("dateStyle"), py::arg("timeStyle"), py::arg("elements"))
.def("Format", py::overload_cast<char *, const size_t, const time_t, BDateFormatStyle, BTimeFormatStyle>(&BDateTimeFormat::Format, py::const_), "", py::arg("target"), py::arg("maxSize"), py::arg("time"), py::arg("dateStyle"), py::arg("timeStyle"))
.def("Format", [](BDateTimeFormat& self,const time_t time,BDateFormatStyle dateStyle,BTimeFormatStyle timeStyle,const BTimeZone * timeZone=NULL) {
    BString  buffer;
    status_t r = self.Format(buffer, time, dateStyle, timeStyle, timeZone);
    return std::make_tuple(r,buffer);
}
, "", py::arg("time"), py::arg("dateStyle"), py::arg("timeStyle"), py::arg("timeZone")=NULL)
;


}
