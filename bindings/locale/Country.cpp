#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <locale/Country.h>
#include <locale/DateFormat.h>
#include <locale/Locale.h>
#include <Bitmap.h>

namespace py = pybind11;
using namespace U_ICU_NAMESPACE;

PYBIND11_MODULE(Country, m)
{


py::class_<BCountry>(m, "BCountry")
.def(py::init<const char *>(), "", py::arg("countryCode")=NULL)
.def(py::init<const BCountry &>(), "", py::arg("other"))
.def("operator=", &BCountry::operator=, "", py::arg("other"))
.def("SetTo", &BCountry::SetTo, "", py::arg("countryCode"))
.def("InitCheck", &BCountry::InitCheck, "")
.def("GetNativeName", [](BCountry& self) {
    BString  name;
    status_t r = self.GetNativeName(name);
    return std::make_tuple(r,name);
}
, "")
.def("GetName", [](BCountry& self,const BLanguage * displayLanguage=NULL) {
    BString  name;
    status_t r = self.GetName(name, displayLanguage);
    return std::make_tuple(r,name);
}
, "", py::arg("displayLanguage")=NULL)
.def("GetPreferredLanguage", &BCountry::GetPreferredLanguage, "", py::arg("&"))
.def("Code", &BCountry::Code, "")
.def("GetIcon", &BCountry::GetIcon, "", py::arg("result"))
.def("GetAvailableTimeZones", &BCountry::GetAvailableTimeZones, "", py::arg("timeZones"))
//.def_readwrite("Private", &BCountry::Private, "")
;

//m.attr("DateFormat") = py::cast(DateFormat);

//m.attr("Locale") = py::cast(Locale);
}
