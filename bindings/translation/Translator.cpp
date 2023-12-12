#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <translation/Translator.h>

namespace py = pybind11;


void define_Translator(py::module_& m)
{
py::class_<BTranslator, BArchivable>(m, "BTranslator")
.def(py::init(), "")
.def("Acquire", &BTranslator::Acquire, "")
.def("Release", &BTranslator::Release, "")
.def("ReferenceCount", &BTranslator::ReferenceCount, "")
.def("TranslatorName", &BTranslator::TranslatorName, "")
.def("TranslatorInfo", &BTranslator::TranslatorInfo, "")
.def("TranslatorVersion", &BTranslator::TranslatorVersion, "")
.def("InputFormats", &BTranslator::InputFormats, "", py::arg("_count"))
.def("OutputFormats", &BTranslator::OutputFormats, "", py::arg("_count"))
.def("Identify", &BTranslator::Identify, "", py::arg("source"), py::arg("format"), py::arg("extension"), py::arg("info"), py::arg("outType"))
.def("Translate", &BTranslator::Translate, "", py::arg("source"), py::arg("info"), py::arg("extension"), py::arg("outType"), py::arg("destination"))
.def("MakeConfigurationView", &BTranslator::MakeConfigurationView, "", py::arg("extension"), py::arg("_view"), py::arg("_extent"))
.def("GetConfigurationMessage", &BTranslator::GetConfigurationMessage, "", py::arg("extension"))
;

m.def("make_nth_translator", &make_nth_translator, "", py::arg("n"), py::arg("you"), py::arg("flags"));

}
