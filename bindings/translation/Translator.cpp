#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <translation/Translator.h>
#include <View.h>

namespace py = pybind11;

class PyBTranslator : public BTranslator {
public:
    using BTranslator::BTranslator;

    const char*			TranslatorName() const override {
        PYBIND11_OVERRIDE_PURE(const char*, BTranslator, TranslatorName);
    }
    const char*			TranslatorInfo() const override {
        PYBIND11_OVERRIDE_PURE(const char*, BTranslator, TranslatorInfo);
    }
    int32			TranslatorVersion() const override {
        PYBIND11_OVERRIDE_PURE(int32, BTranslator, TranslatorVersion);
    }
    const translation_format* InputFormats(int32* _count) const override {
        PYBIND11_OVERRIDE_PURE(translation_format*, BTranslator, InputFormats, _count);
    }
    const translation_format* OutputFormats(int32* _count) const override {
        PYBIND11_OVERRIDE_PURE(translation_format*, BTranslator, OutputFormats, _count);
    }
    status_t			Identify(BPositionIO* source, const translation_format* format, BMessage* extension, translator_info* info, uint32 outType) override {
        PYBIND11_OVERRIDE_PURE(status_t, BTranslator, Identify, source, format, extension, info,outType);
    }
    status_t			Translate(BPositionIO* source, const translator_info* info, BMessage* extension, uint32 outType, BPositionIO* destination) override {
        PYBIND11_OVERRIDE_PURE(status_t, BTranslator, Translate, source, info, extension, outType, destination);
    }
//    status_t			MakeConfigurationView(BMessage* extension, BView** _view, BRect* _extent)
    status_t			GetConfigurationMessage(BMessage* extension) override {
        PYBIND11_OVERLOAD(status_t, BTranslator, GetConfigurationMessage, extension);
    }


};

PYBIND11_MODULE(Translator, m)
{
py::class_<BTranslator, PyBTranslator, BArchivable,std::unique_ptr<BTranslator, py::nodelete>>(m, "BTranslator")
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
//.def("MakeConfigurationView", &BTranslator::MakeConfigurationView, "", py::arg("extension"), py::arg("_view"), py::arg("_extent"))
.def("GetConfigurationMessage", &BTranslator::GetConfigurationMessage, "", py::arg("extension"))
;

//m.def("make_nth_translator", &make_nth_translator, "", py::arg("n"), py::arg("you"), py::arg("flags"));

}
