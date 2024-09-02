#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <locale/StringFormat.h>

namespace py = pybind11;
using namespace U_ICU_NAMESPACE;

PYBIND11_MODULE(StringFormat, m)
{
//m.attr("MessageFormat") = py::cast(MessageFormat);

//m.attr("UnicodeString") = py::cast(UnicodeString);

py::class_<BStringFormat, BFormat>(m, "BStringFormat")
.def(py::init<const BLanguage &, const BString>(), "", py::arg("language"), py::arg("pattern"))
.def(py::init<const BString>(), "", py::arg("pattern"))
.def("InitCheck", &BStringFormat::InitCheck, "")
.def("Format", [](BStringFormat& self,int64_t arg) {
    BString  buffer;
    status_t r = self.Format(buffer, arg);
    return std::make_tuple(r,buffer);
}
, "", py::arg("arg"))
;


}
