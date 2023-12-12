#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <translation/TranslatorAddOn.h>

namespace py = pybind11;


void define_TranslatorAddOn(py::module_& m)
{
m.attr("translatorName") = py::cast(translatorName);

m.attr("translatorInfo") = py::cast(translatorInfo);

m.attr("translatorVersion") = py::cast(translatorVersion);

m.attr("inputFormats") = py::cast(inputFormats);

m.attr("outputFormats") = py::cast(outputFormats);

m.def("Identify", &Identify, "", py::arg("source"), py::arg("format"), py::arg("extension"), py::arg("info"), py::arg("outType"));

m.def("Translate", &Translate, "", py::arg("source"), py::arg("info"), py::arg("extension"), py::arg("outType"), py::arg("destination"));

m.def("MakeConfig", &MakeConfig, "", py::arg("extension"), py::arg("_view"), py::arg("_frame"));

m.def("GetConfigMessage", &GetConfigMessage, "", py::arg("extension"));

}
