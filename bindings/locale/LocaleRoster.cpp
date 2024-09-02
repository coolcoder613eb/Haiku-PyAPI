#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <locale/LocaleRoster.h>
#include <locale/TimeZone.h>
#include <locale/Language.h>
#include <Message.h>
#include <Bitmap.h>
#include <locale/Catalog.h>
#include <locale/Locale.h>

namespace py = pybind11;
using namespace BPrivate;


PYBIND11_MODULE(LocaleRoster, m)
{
//m.attr("LocaleRosterData") = py::cast(LocaleRosterData);

py::class_<BLocaleRoster>(m, "BLocaleRoster")
.def_static("Default", &BLocaleRoster::Default, "")
.def("GetDefaultTimeZone", &BLocaleRoster::GetDefaultTimeZone, "", py::arg("timezone"))
//.def("GetLanguage", &BLocaleRoster::GetLanguage, "", py::arg("languageCode"), py::arg("_language"))
//.def("GetLanguage", &GetLanguage_wrapper, "", py::arg("languageCode"), py::arg("_language"))
.def("GetLanguage", [](BLocaleRoster& self,const char* languageCode)-> py::tuple {
	std::vector<BLanguage*> _language;
	status_t r = self.GetLanguage(languageCode,_language.data());
	/* if you want to return a py::list uncomment this and try it
	py::list language;
	for (size_t i = 0; i < _language.size(); ++i) {
        language.append(py::cast(*_language[i]);
    }
    for (size_t i = 0; i < _language.size(); ++i) {
        delete _language[i];
    }
    */
	return py::make_tuple(r,_language);
},"",py::arg("languageCode")) // TODO make a test, try this (returning a std::vector or better a py::list??)
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
//.def_readwrite("kCatLangAttr", &BLocaleRoster::kCatLangAttr, "")
//.def_readwrite("kCatSigAttr", &BLocaleRoster::kCatSigAttr, "")
//.def_readwrite("kCatFingerprintAttr", &BLocaleRoster::kCatFingerprintAttr, "")
//.def_readwrite("kEmbeddedCatAttr", &BLocaleRoster::kEmbeddedCatAttr, "")
//.def_readwrite("kEmbeddedCatResId", &BLocaleRoster::kEmbeddedCatResId, "")
;

m.attr("B_LOCALE_CHANGED") = '_LCC';//py::cast(B_LOCALE_CHANGED);
}
