#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <locale/FormattingConventions.h>
#include <locale/Locale.h>

namespace py = pybind11;
using namespace U_ICU_NAMESPACE;

PYBIND11_MODULE(FormattingConventions, m)
{
py::enum_<BMeasurementKind>(m, "BMeasurementKind", "")
.value("B_METRIC", BMeasurementKind::B_METRIC, "")
.value("B_US", BMeasurementKind::B_US, "")
.export_values();

py::enum_<BDateFormatStyle>(m, "BDateFormatStyle", "")
.value("B_FULL_DATE_FORMAT", BDateFormatStyle::B_FULL_DATE_FORMAT, "")
.value("B_LONG_DATE_FORMAT", BDateFormatStyle::B_LONG_DATE_FORMAT, "")
.value("B_MEDIUM_DATE_FORMAT", BDateFormatStyle::B_MEDIUM_DATE_FORMAT, "")
.value("B_SHORT_DATE_FORMAT", BDateFormatStyle::B_SHORT_DATE_FORMAT, "")
.value("B_DATE_FORMAT_STYLE_COUNT", BDateFormatStyle::B_DATE_FORMAT_STYLE_COUNT, "")
.export_values();

py::enum_<BTimeFormatStyle>(m, "BTimeFormatStyle", "")
.value("B_FULL_TIME_FORMAT", BTimeFormatStyle::B_FULL_TIME_FORMAT, "")
.value("B_LONG_TIME_FORMAT", BTimeFormatStyle::B_LONG_TIME_FORMAT, "")
.value("B_MEDIUM_TIME_FORMAT", BTimeFormatStyle::B_MEDIUM_TIME_FORMAT, "")
.value("B_SHORT_TIME_FORMAT", BTimeFormatStyle::B_SHORT_TIME_FORMAT, "")
.value("B_TIME_FORMAT_STYLE_COUNT", BTimeFormatStyle::B_TIME_FORMAT_STYLE_COUNT, "")
.export_values();

//m.attr("DateFormat") = py::cast(DateFormat);

//m.attr("Locale") = py::cast(Locale);

py::class_<BFormattingConventions, BArchivable>(m, "BFormattingConventions")
.def(py::init<const char *>(), "", py::arg("id")=NULL)
.def(py::init<const BFormattingConventions &>(), "", py::arg("other"))
.def(py::init<const BMessage *>(), "", py::arg("archive"))
.def("__copy__", &BFormattingConventions::operator=, "", py::arg("other"))
.def("__eq__", &BFormattingConventions::operator==, "", py::arg("other"))
.def("__ne__", &BFormattingConventions::operator!=, "", py::arg("other"))
.def("ID", &BFormattingConventions::ID, "")
.def("LanguageCode", &BFormattingConventions::LanguageCode, "")
.def("CountryCode", &BFormattingConventions::CountryCode, "")
.def("AreCountrySpecific", &BFormattingConventions::AreCountrySpecific, "")
.def("GetNativeName", [](BFormattingConventions& self) {
    BString  name;
    status_t r = self.GetNativeName(name);
    return std::make_tuple(r,name);
}
, "")
.def("GetName", [](BFormattingConventions& self,const BLanguage * displayLanguage=NULL) {
    BString  name;
    status_t r = self.GetName(name, displayLanguage);
    return std::make_tuple(r,name);
}
, "", py::arg("displayLanguage")=NULL)
//.def("GetString", &BFormattingConventions::GetString, "", py::arg("id"))
.def("GetDateFormat", [](BFormattingConventions& self,BDateFormatStyle style) {
    BString  outFormat;
    status_t r = self.GetDateFormat(style, outFormat);
    return std::make_tuple(r,outFormat);
}
, "", py::arg("style"))
.def("GetTimeFormat", [](BFormattingConventions& self,BTimeFormatStyle style) {
    BString  outFormat;
    status_t r = self.GetTimeFormat(style, outFormat);
    return std::make_tuple(r,outFormat);
}
, "", py::arg("style"))
.def("GetDateTimeFormat", [](BFormattingConventions& self,BDateFormatStyle dateStyle,BTimeFormatStyle timeStyle) {
    BString  outFormat;
    status_t r = self.GetDateTimeFormat(dateStyle, timeStyle, outFormat);
    return std::make_tuple(r,outFormat);
}
, "", py::arg("dateStyle"), py::arg("timeStyle"))
.def("GetNumericFormat", [](BFormattingConventions& self) {
    BString  outFormat;
    status_t r = self.GetNumericFormat(outFormat);
    return std::make_tuple(r,outFormat);
}
, "")
.def("GetMonetaryFormat", [](BFormattingConventions& self) {
    BString  outFormat;
    status_t r = self.GetMonetaryFormat(outFormat);
    return std::make_tuple(r,outFormat);
}
, "")
.def("SetExplicitDateFormat", &BFormattingConventions::SetExplicitDateFormat, "", py::arg("style"), py::arg("format"))
.def("SetExplicitTimeFormat", &BFormattingConventions::SetExplicitTimeFormat, "", py::arg("style"), py::arg("format"))
.def("SetExplicitDateTimeFormat", &BFormattingConventions::SetExplicitDateTimeFormat, "", py::arg("dateStyle"), py::arg("timeStyle"), py::arg("format"))
.def("SetExplicitNumericFormat", &BFormattingConventions::SetExplicitNumericFormat, "", py::arg("format"))
.def("SetExplicitMonetaryFormat", &BFormattingConventions::SetExplicitMonetaryFormat, "", py::arg("format"))
.def("MeasurementKind", &BFormattingConventions::MeasurementKind, "")
.def("UseStringsFromPreferredLanguage", &BFormattingConventions::UseStringsFromPreferredLanguage, "")
.def("SetUseStringsFromPreferredLanguage", &BFormattingConventions::SetUseStringsFromPreferredLanguage, "", py::arg("value"))
.def("Use24HourClock", &BFormattingConventions::Use24HourClock, "")
.def("SetExplicitUse24HourClock", &BFormattingConventions::SetExplicitUse24HourClock, "", py::arg("value"))
.def("UnsetExplicitUse24HourClock", &BFormattingConventions::UnsetExplicitUse24HourClock, "")
.def("Archive", &BFormattingConventions::Archive, "", py::arg("archive"), py::arg("deep")=true)
//.def_readwrite("Private", &BFormattingConventions::Private, "")
;


}
