#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <locale/NumberFormat.h>
#include <locale/Locale.h>

namespace py = pybind11;


PYBIND11_MODULE(NumberFormat, m)
{
py::enum_<BNumberElement>(m, "BNumberElement", "")
.value("B_DECIMAL_SEPARATOR", BNumberElement::B_DECIMAL_SEPARATOR, "")
.value("B_GROUPING_SEPARATOR", BNumberElement::B_GROUPING_SEPARATOR, "")
.export_values();

py::class_<BNumberFormat, BFormat>(m, "BNumberFormat")
.def(py::init(), "")
.def(py::init<const BLocale *>(), "", py::arg("locale"))
.def("Format", py::overload_cast<char *, size_t, const double>(&BNumberFormat::Format), "", py::arg("string"), py::arg("maxSize"), py::arg("value"))
.def("Format", [](BNumberFormat& self,const double value) {
    BString string;
    status_t r = self.Format(string, value);
    return std::make_tuple(r,string);
}
, "", py::arg("value"))
.def("Format", py::overload_cast<char *, size_t, int32>(&BNumberFormat::Format), "", py::arg("string"), py::arg("maxSize"), py::arg("value"))
.def("Format", [](BNumberFormat& self, int32 value) {
    BString string;
    status_t r = self.Format(string, value);
    return std::make_tuple(r,string);
}
, "", py::arg("value"))
.def("FormatMonetary", py::overload_cast<char *, size_t, const double>(&BNumberFormat::FormatMonetary), "", py::arg("string"), py::arg("maxSize"), py::arg("value"))
.def("FormatMonetary", [](BNumberFormat& self,const double value) {
    BString  string;
    status_t r = self.FormatMonetary(string, value);
    return std::make_tuple(r,string);
}
, "", py::arg("value"))
.def("FormatPercent", py::overload_cast<char *, size_t, const double>(&BNumberFormat::FormatPercent), "", py::arg("string"), py::arg("maxSize"), py::arg("value"))
.def("FormatPercent", [](BNumberFormat& self,const double value) {
    BString  string;
    status_t r = self.FormatPercent(string, value);
    return std::make_tuple(r,string);
}
, "", py::arg("value"))
.def("Parse", [](BNumberFormat& self,const BString & string) {
    double  value;
    status_t r = self.Parse(string, value);
    return std::make_tuple(r,value);
}
, "", py::arg("string"))
.def("GetSeparator", &BNumberFormat::GetSeparator, "", py::arg("element"))
;


}
