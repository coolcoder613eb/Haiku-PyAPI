#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <locale/DateFormat.h>
#include <locale/TimeZone.h>
#include <locale/Locale.h>

namespace py = pybind11;
using namespace U_ICU_NAMESPACE;

PYBIND11_MODULE(DateFormat, m)
{
py::enum_<BWeekday>(m, "BWeekday", "")
.value("B_WEEKDAY_MONDAY", BWeekday::B_WEEKDAY_MONDAY, "")
.value("B_WEEKDAY_TUESDAY", BWeekday::B_WEEKDAY_TUESDAY, "")
.value("B_WEEKDAY_WEDNESDAY", BWeekday::B_WEEKDAY_WEDNESDAY, "")
.value("B_WEEKDAY_THURSDAY", BWeekday::B_WEEKDAY_THURSDAY, "")
.value("B_WEEKDAY_FRIDAY", BWeekday::B_WEEKDAY_FRIDAY, "")
.value("B_WEEKDAY_SATURDAY", BWeekday::B_WEEKDAY_SATURDAY, "")
.value("B_WEEKDAY_SUNDAY", BWeekday::B_WEEKDAY_SUNDAY, "")
.export_values();

//m.attr("DateFormat") = py::cast(DateFormat);

py::class_<BDateFormat, BFormat>(m, "BDateFormat")
.def(py::init<const BLocale *>(), "", py::arg("locale")=NULL)
.def(py::init<const BLanguage &, const BFormattingConventions &>(), "", py::arg("language"), py::arg("format"))
.def(py::init<const BDateFormat &>(), "", py::arg("other"))
.def("GetDateFormat", [](BDateFormat& self,BDateFormatStyle style) {
    BString  outFormat;
    status_t r = self.GetDateFormat(style, outFormat);
    return std::make_tuple(r,outFormat);
}
, "", py::arg("style"))
.def("SetDateFormat", &BDateFormat::SetDateFormat, "", py::arg("style"), py::arg("format"))
.def("Format", py::overload_cast<char *, const size_t, const time_t, const BDateFormatStyle>(&BDateFormat::Format, py::const_), "", py::arg("string"), py::arg("maxSize"), py::arg("time"), py::arg("style"))
.def("Format", [](BDateFormat& self,const time_t time,const BDateFormatStyle style,const BTimeZone * timeZone=NULL) {
    BString  string;
    status_t r = self.Format(string, time, style, timeZone);
    return std::make_tuple(r,string);
}
, "", py::arg("time"), py::arg("style"), py::arg("timeZone")=NULL)
.def("Format", [](BDateFormat& self,const BDate & time,const BDateFormatStyle style,const BTimeZone * timeZone=NULL) {
    BString  string;
    status_t r = self.Format(string, time, style, timeZone);
    return std::make_tuple(r,string);
}
, "", py::arg("time"), py::arg("style"), py::arg("timeZone")=NULL)
.def("Format", [](BDateFormat& self,const time_t time,const BDateFormatStyle style) {
    BString  string;
int *  fieldPositions;
int  fieldCount;
    status_t r = self.Format(string, fieldPositions, fieldCount, time, style);
    return std::make_tuple(r,string,fieldPositions,fieldCount);
}
, "", py::arg("time"), py::arg("style"))
.def("GetFields", [](BDateFormat& self,BDateFormatStyle style) {
    BDateElement *  fields;
int  fieldCount;
    status_t r = self.GetFields(fields, fieldCount, style);
    return std::make_tuple(r,fields,fieldCount);
}
, "", py::arg("style"))
.def("GetStartOfWeek", &BDateFormat::GetStartOfWeek, "", py::arg("weekday"))
.def("GetMonthName", [](BDateFormat& self,int month,const BDateFormatStyle style=B_FULL_DATE_FORMAT) {
    BString  outName;
    status_t r = self.GetMonthName(month, outName, style);
    return std::make_tuple(r,outName);
}
, "", py::arg("month"), py::arg("style")=B_FULL_DATE_FORMAT)
.def("GetDayName", [](BDateFormat& self,int day,const BDateFormatStyle style=B_FULL_DATE_FORMAT) {
    BString  outName;
    status_t r = self.GetDayName(day, outName, style);
    return std::make_tuple(r,outName);
}
, "", py::arg("day"), py::arg("style")=B_FULL_DATE_FORMAT)
.def("Parse", [](BDateFormat& self,BString source,BDateFormatStyle style) {
    BDate  output;
    status_t r = self.Parse(source, style, output);
    return std::make_tuple(r,output);
}
, "", py::arg("source"), py::arg("style"))
;


}
