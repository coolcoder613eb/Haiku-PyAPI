#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <locale/Format.h>
#include <locale/Locale.h>

namespace py = pybind11;


PYBIND11_MODULE(Format, m)
{
m.attr("B_CURRENCY_FIELD") = 0;//py::cast(B_CURRENCY_FIELD);
m.attr("B_DECIMAL_SEPARATOR_FIELD") = 1;//py::cast(B_DECIMAL_SEPARATOR_FIELD);
m.attr("B_EXPONENT_FIELD") = 2;//py::cast(B_EXPONENT_FIELD);
m.attr("B_EXPONENT_SIGN_FIELD") = 3;//py::cast(B_EXPONENT_SIGN_FIELD);
m.attr("B_EXPONENT_SYMBOL_FIELD") = 4;//py::cast(B_EXPONENT_SYMBOL_FIELD);
m.attr("B_FRACTION_FIELD") = 5;//py::cast(B_FRACTION_FIELD);
m.attr("B_GROUPING_SEPARATOR_FIELD") = 6;//py::cast(B_GROUPING_SEPARATOR_FIELD);
m.attr("B_INTEGER_FIELD") = 7;//py::cast(B_INTEGER_FIELD);
m.attr("B_PERCENT_FIELD") = 8;//py::cast(B_PERCENT_FIELD);
m.attr("B_PERMILLE_FIELD") = 9;//py::cast(B_PERMILLE_FIELD);
m.attr("B_SIGN_FIELD") = 10;//py::cast(B_SIGN_FIELD);

py::class_<format_field_position>(m, "format_field_position")
.def_readwrite("field_type", &format_field_position::field_type, "")
.def_readwrite("start", &format_field_position::start, "")
.def_readwrite("length", &format_field_position::length, "")
;

py::class_<BFormat,std::unique_ptr<BFormat, py::nodelete>>(m, "BFormat")
.def("InitCheck", &BFormat::InitCheck, "")
;


}
