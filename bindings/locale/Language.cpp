#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <locale/Language.h>
#include <Bitmap.h>

namespace py = pybind11;
using namespace U_ICU_NAMESPACE;

PYBIND11_MODULE(Language, m)
{
py::enum_<script_direction>(m, "script_direction", "")
.value("B_LEFT_TO_RIGHT", script_direction::B_LEFT_TO_RIGHT, "")
.value("B_RIGHT_TO_LEFT", script_direction::B_RIGHT_TO_LEFT, "")
.value("B_TOP_TO_BOTTOM", script_direction::B_TOP_TO_BOTTOM, "")
.export_values();

py::class_<BLanguage>(m, "BLanguage")
.def(py::init(), "")
.def(py::init<const char *>(), "", py::arg("language"))
.def(py::init<const BLanguage &>(), "", py::arg("other"))
.def("SetTo", &BLanguage::SetTo, "", py::arg("language"))
.def("GetNativeName", [](BLanguage& self) {
    BString  name;
    status_t r = self.GetNativeName(name);
    return std::make_tuple(r,name);
}
, "")
.def("GetName", [](BLanguage& self,const BLanguage * displayLanguage=NULL) {
    BString  name;
    status_t r = self.GetName(name, displayLanguage);
    return std::make_tuple(r,name);
}
, "", py::arg("displayLanguage")=NULL)
.def("GetString", &BLanguage::GetString, "", py::arg("id"))
.def("GetIcon", &BLanguage::GetIcon, "", py::arg("result"))
.def("Code", &BLanguage::Code, "")
.def("CountryCode", &BLanguage::CountryCode, "")
.def("ScriptCode", &BLanguage::ScriptCode, "")
.def("Variant", &BLanguage::Variant, "")
.def("ID", &BLanguage::ID, "")
.def("IsCountrySpecific", &BLanguage::IsCountrySpecific, "")
.def("IsVariant", &BLanguage::IsVariant, "")
.def("Direction", &BLanguage::Direction, "")
.def("__copy__", &BLanguage::operator=, "", py::arg("source"))
//.def_readwrite("Private", &BLanguage::Private, "")
;
//m.attr("Locale") = py::cast(Locale);

}
