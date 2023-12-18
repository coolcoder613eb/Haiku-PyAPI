#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <translation/TranslatorRoster.h>
#include <Translator.h>
#include <Messenger.h>
#include <View.h>

namespace py = pybind11;


PYBIND11_MODULE(TranslatorRoster, m)
{
py::class_<BTranslatorReleaseDelegate>(m, "BTranslatorReleaseDelegate")
.def(py::init<BTranslator *>(), "", py::arg("translator"))
.def("Release", &BTranslatorReleaseDelegate::Release, "")
;

py::class_<BTranslatorRoster, BArchivable>(m, "BTranslatorRoster")
.def(py::init(), "")
.def(py::init<BMessage *>(), "", py::arg("model"))
.def_static("Default", &BTranslatorRoster::Default, "")
.def("Archive", &BTranslatorRoster::Archive, "", py::arg("into"), py::arg("deep")=true)
.def_static("Instantiate", &BTranslatorRoster::Instantiate, "", py::arg("from"))
.def("AddTranslators", &BTranslatorRoster::AddTranslators, "", py::arg("loadPath")=NULL)
.def("AddTranslator", &BTranslatorRoster::AddTranslator, "", py::arg("translator"))
.def("Identify", &BTranslatorRoster::Identify, "", py::arg("source"), py::arg("ioExtension"), py::arg("_info"), py::arg("hintType")=0, py::arg("hintMIME")=NULL, py::arg("wantType")=0)
//.def("GetTranslators", &BTranslatorRoster::GetTranslators, "", py::arg("source"), py::arg("ioExtension"), py::arg("_info"), py::arg("_numInfo"), py::arg("hintType")=0, py::arg("hintMIME")=NULL, py::arg("wantType")=0)
//.def("GetAllTranslators", &BTranslatorRoster::GetAllTranslators, "", py::arg("_list"), py::arg("_count"))
//.def("GetTranslatorInfo", &BTranslatorRoster::GetTranslatorInfo, "", py::arg("translatorID"), py::arg("_name"), py::arg("_info"), py::arg("_version"))
//.def("GetInputFormats", &BTranslatorRoster::GetInputFormats, "", py::arg("translatorID"), py::arg("_formats"), py::arg("_numFormats"))
//.def("GetOutputFormats", &BTranslatorRoster::GetOutputFormats, "", py::arg("translatorID"), py::arg("_formats"), py::arg("_numFormats"))
.def("Translate", py::overload_cast<BPositionIO *, const translator_info *, BMessage *, BPositionIO *, uint32, uint32, const char *>(&BTranslatorRoster::Translate), "", py::arg("source"), py::arg("info"), py::arg("ioExtension"), py::arg("destination"), py::arg("wantOutType"), py::arg("hintType")=0, py::arg("hintMIME")=NULL)
.def("Translate", py::overload_cast<translator_id, BPositionIO *, BMessage *, BPositionIO *, uint32>(&BTranslatorRoster::Translate), "", py::arg("translatorID"), py::arg("source"), py::arg("ioExtension"), py::arg("destination"), py::arg("wantOutType"))
//.def("MakeConfigurationView", &BTranslatorRoster::MakeConfigurationView, "", py::arg("translatorID"), py::arg("ioExtension"), py::arg("_view"), py::arg("_extent"))
.def("GetConfigurationMessage", &BTranslatorRoster::GetConfigurationMessage, "", py::arg("translatorID"), py::arg("ioExtension"))
.def("AcquireTranslator", &BTranslatorRoster::AcquireTranslator, "", py::arg("translatorID"))
.def("GetRefFor", &BTranslatorRoster::GetRefFor, "", py::arg("translatorID"), py::arg("ref"))
.def("IsTranslator", &BTranslatorRoster::IsTranslator, "", py::arg("ref"))
.def("StartWatching", &BTranslatorRoster::StartWatching, "", py::arg("target"))
.def("StopWatching", &BTranslatorRoster::StopWatching, "", py::arg("target"))
//.def_readwrite("Private", &BTranslatorRoster::Private, "")
;


}
