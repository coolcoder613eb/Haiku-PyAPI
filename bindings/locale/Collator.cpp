#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <locale/Collator.h>

namespace py = pybind11;
using namespace U_ICU_NAMESPACE;

void define_Collator(py::module_& m)
{
py::enum_<collator_strengths>(m, "collator_strengths", "")
.value("B_COLLATE_DEFAULT", collator_strengths::B_COLLATE_DEFAULT, "")
.value("B_COLLATE_PRIMARY", collator_strengths::B_COLLATE_PRIMARY, "")
.value("B_COLLATE_SECONDARY", collator_strengths::B_COLLATE_SECONDARY, "")
.value("B_COLLATE_TERTIARY", collator_strengths::B_COLLATE_TERTIARY, "")
.value("B_COLLATE_QUATERNARY", collator_strengths::B_COLLATE_QUATERNARY, "")
.value("B_COLLATE_IDENTICAL", collator_strengths::B_COLLATE_IDENTICAL, "")
.export_values();

m.attr("Collator") = py::cast(Collator);

py::class_<BCollator, BArchivable>(m, "BCollator")
.def(py::init(), "")
.def(py::init<const char *, signed char, bool>(), "", py::arg("locale"), py::arg("strength")=B_COLLATE_PRIMARY, py::arg("ignorePunctuation")=false)
.def(py::init<BMessage *>(), "", py::arg("archive"))
.def(py::init<const BCollator &>(), "", py::arg("other"))
.def("operator=", &BCollator::operator=, "", py::arg("source"))
.def("SetStrength", &BCollator::SetStrength, "", py::arg("strength"))
.def("SetIgnorePunctuation", &BCollator::SetIgnorePunctuation, "", py::arg("ignore"))
.def("IgnorePunctuation", &BCollator::IgnorePunctuation, "")
.def("SetNumericSorting", &BCollator::SetNumericSorting, "", py::arg("enable"))
.def("GetSortKey", &BCollator::GetSortKey, "", py::arg("string"), py::arg("key"))
.def("Compare", &BCollator::Compare, "", py::arg("s1"), py::arg("s2"))
.def("Equal", &BCollator::Equal, "", py::arg("s1"), py::arg("s2"))
.def("Greater", &BCollator::Greater, "", py::arg("s1"), py::arg("s2"))
.def("GreaterOrEqual", &BCollator::GreaterOrEqual, "", py::arg("s1"), py::arg("s2"))
.def("Archive", &BCollator::Archive, "", py::arg("archive"), py::arg("deep"))
.def_static("Instantiate", &BCollator::Instantiate, "", py::arg("archive"))
;


}
