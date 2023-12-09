#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/UTF8.h>

namespace py = pybind11;


void define_UTF8(py::module_& m)
{
m.attr("B_ISO1_CONVERSION") = py::cast(B_ISO1_CONVERSION);
m.attr("B_ISO2_CONVERSION") = py::cast(B_ISO2_CONVERSION);
m.attr("B_ISO3_CONVERSION") = py::cast(B_ISO3_CONVERSION);
m.attr("B_ISO4_CONVERSION") = py::cast(B_ISO4_CONVERSION);
m.attr("B_ISO5_CONVERSION") = py::cast(B_ISO5_CONVERSION);
m.attr("B_ISO6_CONVERSION") = py::cast(B_ISO6_CONVERSION);
m.attr("B_ISO7_CONVERSION") = py::cast(B_ISO7_CONVERSION);
m.attr("B_ISO8_CONVERSION") = py::cast(B_ISO8_CONVERSION);
m.attr("B_ISO9_CONVERSION") = py::cast(B_ISO9_CONVERSION);
m.attr("B_ISO10_CONVERSION") = py::cast(B_ISO10_CONVERSION);
m.attr("B_MAC_ROMAN_CONVERSION") = py::cast(B_MAC_ROMAN_CONVERSION);
m.attr("B_SJIS_CONVERSION") = py::cast(B_SJIS_CONVERSION);
m.attr("B_EUC_CONVERSION") = py::cast(B_EUC_CONVERSION);
m.attr("B_JIS_CONVERSION") = py::cast(B_JIS_CONVERSION);
m.attr("B_MS_WINDOWS_CONVERSION") = py::cast(B_MS_WINDOWS_CONVERSION);
m.attr("B_UNICODE_CONVERSION") = py::cast(B_UNICODE_CONVERSION);
m.attr("B_KOI8R_CONVERSION") = py::cast(B_KOI8R_CONVERSION);
m.attr("B_MS_WINDOWS_1251_CONVERSION") = py::cast(B_MS_WINDOWS_1251_CONVERSION);
m.attr("B_MS_DOS_866_CONVERSION") = py::cast(B_MS_DOS_866_CONVERSION);
m.attr("B_MS_DOS_CONVERSION") = py::cast(B_MS_DOS_CONVERSION);
m.attr("B_EUC_KR_CONVERSION") = py::cast(B_EUC_KR_CONVERSION);
m.attr("B_ISO13_CONVERSION") = py::cast(B_ISO13_CONVERSION);
m.attr("B_ISO14_CONVERSION") = py::cast(B_ISO14_CONVERSION);
m.attr("B_ISO15_CONVERSION") = py::cast(B_ISO15_CONVERSION);
m.attr("B_BIG5_CONVERSION") = py::cast(B_BIG5_CONVERSION);
m.attr("B_GBK_CONVERSION") = py::cast(B_GBK_CONVERSION);
m.attr("B_UTF16_CONVERSION") = py::cast(B_UTF16_CONVERSION);
m.attr("B_MS_WINDOWS_1250_CONVERSION") = py::cast(B_MS_WINDOWS_1250_CONVERSION);

m.def("convert_to_utf8", &convert_to_utf8, "", py::arg("sourceEncoding"), py::arg("source"), py::arg("sourceLength"), py::arg("dest"), py::arg("destLength"), py::arg("state"), py::arg("substitute")=B_SUBSTITUTE);

m.def("convert_from_utf8", &convert_from_utf8, "", py::arg("destEncoding"), py::arg("source"), py::arg("sourceLength"), py::arg("dest"), py::arg("destLength"), py::arg("state"), py::arg("substitute")=B_SUBSTITUTE);

}
