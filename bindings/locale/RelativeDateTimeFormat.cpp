#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <locale/RelativeDateTimeFormat.h>

namespace py = pybind11;
using namespace U_ICU_NAMESPACE;

void define_RelativeDateTimeFormat(py::module_& m)
{
m.attr("GregorianCalendar") = py::cast(GregorianCalendar);

m.attr("RelativeDateTimeFormatter") = py::cast(RelativeDateTimeFormatter);

py::class_<BRelativeDateTimeFormat, BFormat>(m, "BRelativeDateTimeFormat")
.def(py::init(), "")
.def(py::init<const BLanguage &, const BFormattingConventions &>(), "", py::arg("language"), py::arg("conventions"))
.def(py::init<const BRelativeDateTimeFormat &>(), "", py::arg("other"))
.def("Format", [](BRelativeDateTimeFormat& self,const time_t timeValue) {
    BString  string;
    status_t r = self.Format(string, timeValue);
    return std::make_tuple(r,string);
}
, "", py::arg("timeValue"))
;


}
