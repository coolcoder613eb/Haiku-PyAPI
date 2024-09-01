#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <locale/LocaleRoster.h>

namespace py = pybind11;
using namespace BPrivate;

void define_LocaleRoster(py::module_& m)
{
m.attr("B_LOCALE_CHANGED") = py::cast(B_LOCALE_CHANGED);

m.attr("LocaleRosterData") = py::cast(LocaleRosterData);

py::class_<BLocaleRoster>(m, "BLocaleRoster")
.def_static("Default", &BLocaleRoster::Default, "")
.def("GetDefaultTimeZone", &BLocaleRoster::GetDefaultTimeZone, "", py::arg("timezone"))
.def("GetLanguage", &BLocaleRoster::GetLanguage, "", py::arg("languageCode"), py::arg("_language"))
.def("GetPreferredLanguages", &BLocaleRoster::GetPreferredLanguages, "", py::arg("message"))
.def("GetAvailableLanguages", &BLocaleRoster::GetAvailableLanguages, "", py::arg("message"))
.def("GetAvailableCountries", &BLocaleRoster::GetAvailableCountries, "", py::arg("timeZones"))
.def("GetAvailableTimeZones", &BLocaleRoster::GetAvailableTimeZones, "", py::arg("timeZones"))
.def("GetAvailableTimeZonesWithRegionInfo", &BLocaleRoster::GetAvailableTimeZonesWithRegionInfo, "", py::arg("timeZonesWithRegonInfo"))
.def("GetAvailableTimeZonesForCountry", &BLocaleRoster::GetAvailableTimeZonesForCountry, "", py::arg("message"), py::arg("countryCode"))
.def("GetFlagIconForCountry", &BLocaleRoster::GetFlagIconForCountry, "", py::arg("flagIcon"), py::arg("countryCode"))
.def("GetFlagIconForLanguage", &BLocaleRoster::GetFlagIconForLanguage, "", py::arg("flagIcon"), py::arg("languageCode"))
.def("GetAvailableCatalogs", &BLocaleRoster::GetAvailableCatalogs, "", py::arg("message"), py::arg("sigPattern")=NULL, py::arg("langPattern")=NULL, py::arg("fingerprint")=0)
.def("Refresh", &BLocaleRoster::Refresh, "")
.def("GetCatalog", &BLocaleRoster::GetCatalog, "")
.def("GetDefaultLocale", &BLocaleRoster::GetDefaultLocale, "")
.def("IsFilesystemTranslationPreferred", &BLocaleRoster::IsFilesystemTranslationPreferred, "")
.def("GetLocalizedFileName", [](BLocaleRoster& self,const entry_ref & ref,bool traverse=false) {
    BString  localizedFileName;
    status_t r = self.GetLocalizedFileName(localizedFileName, ref, traverse);
    return std::make_tuple(r,localizedFileName);
}
, "", py::arg("ref"), py::arg("traverse")=false)
.def_readwrite("kCatLangAttr", &BLocaleRoster::kCatLangAttr, "")
.def_readwrite("kCatSigAttr", &BLocaleRoster::kCatSigAttr, "")
.def_readwrite("kCatFingerprintAttr", &BLocaleRoster::kCatFingerprintAttr, "")
.def_readwrite("kEmbeddedCatAttr", &BLocaleRoster::kEmbeddedCatAttr, "")
.def_readwrite("kEmbeddedCatResId", &BLocaleRoster::kEmbeddedCatResId, "")
;


}
