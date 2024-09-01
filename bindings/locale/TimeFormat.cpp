#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <locale/TimeFormat.h>
#include <locale/TimeZone.h>
#include <locale/FormattingConventions.h>
#include <DateTime.h>
#include <time.h>

namespace py = pybind11;
using namespace BPrivate;

PYBIND11_MODULE(TimeFormat, m)
{
//m.attr("BTime") = py::cast(BTime);
//m.attr("BTime") = py::cast(BPrivate::BTime);

py::class_<BTimeFormat, BFormat>(m, "BTimeFormat")
.def(py::init(), "")
.def(py::init<const BLanguage &, const BFormattingConventions &>(), "", py::arg("language"), py::arg("conventions"))
.def(py::init<const BTimeFormat &>(), "", py::arg("other"))
.def("SetTimeFormat", &BTimeFormat::SetTimeFormat, "", py::arg("style"), py::arg("format"))
.def("Format", py::overload_cast<char *, size_t, time_t, BTimeFormatStyle>(&BTimeFormat::Format, py::const_), "", py::arg("string"), py::arg("maxSize"), py::arg("time"), py::arg("style"))
//.def("Format", py::overload_cast<BString&, const time_t, const BTimeFormatStyle, const BTimeZone*>(&BTimeFormat::Format, py::const_), "", py::arg("string"), py::arg("time"), py::arg("style"), py::arg("timeZone")=NULL)
//.def("Format", py::overload_cast<BString&, int*&, int&, time_t, BTimeFormatStyle>(&BTimeFormat::Format, py::const_), "", py::arg("string"), py::arg("fieldPositions"), py::arg("fieldCount"), py::arg("time"), py::arg("style"))
.def("Format", [](BTimeFormat& self,const time_t time,const BTimeFormatStyle style,const BTimeZone * timeZone=NULL) {
    BString  string;
    status_t r = self.Format(string, time, style, timeZone);
    return std::make_tuple(r,string);
}
, "", py::arg("time"), py::arg("style"), py::arg("timeZone")=NULL)
.def("Format", [](BTimeFormat& self,time_t time,BTimeFormatStyle style) {
    BString  string;
int *  fieldPositions;
int  fieldCount;
    status_t r = self.Format(string, fieldPositions, fieldCount, time, style);
    return std::make_tuple(r,string,fieldPositions,fieldCount);
}
, "", py::arg("time"), py::arg("style"))
.def("GetTimeFields", [](BTimeFormat& self,BTimeFormatStyle style) {
    BDateElement *  fields;
int  fieldCount;
    status_t r = self.GetTimeFields(fields, fieldCount, style);
    return std::make_tuple(r,fields,fieldCount);
}
, "", py::arg("style"))
.def("Parse", [](BTimeFormat& self,BString source,BTimeFormatStyle style) {
    BPrivate::BTime  output;
    status_t r = self.Parse(source, style, output);
    return std::make_tuple(r,output);
}
, "", py::arg("source"), py::arg("style"))
;


}
