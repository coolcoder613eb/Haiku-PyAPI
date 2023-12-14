#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <translation/TranslationDefs.h>

namespace py = pybind11;


PYBIND11_MODULE(TranslationDefs, m)
{
m.attr("B_TRANSLATOR_MIME_TYPE") = py::cast(B_TRANSLATOR_MIME_TYPE);
//m.attr("B_TRANSLATOR_MIME_TYPE") = B_TRANSLATOR_MIME_TYPE;

py::class_<translation_format>(m, "translation_format")
.def_readwrite("type", &translation_format::type, "")
.def_readwrite("group", &translation_format::group, "")
.def_readwrite("quality", &translation_format::quality, "")
.def_readwrite("capability", &translation_format::capability, "")
//.def_readwrite("MIME", &translation_format::MIME, "")
//.def_readwrite("name", &translation_format::name, "")
.def_property("MIME",
                      [](const translation_format &t) {
                          return std::string(t.MIME);
                      },
                      [](translation_format &t, const std::string &value) {
                          std::strncpy(t.MIME, value.c_str(), sizeof(t.MIME));
                      })
.def_property("name",
                      [](const translation_format &t) {
                          return std::string(t.name);
                      },
                      [](translation_format &t, const std::string &value) {
                          std::strncpy(t.name, value.c_str(), sizeof(t.name));
                      })
;

py::class_<translator_info>(m, "translator_info")
.def_readwrite("type", &translator_info::type, "")
.def_readwrite("translator", &translator_info::translator, "")
.def_readwrite("group", &translator_info::group, "")
.def_readwrite("quality", &translator_info::quality, "")
.def_readwrite("capability", &translator_info::capability, "")
//.def_readwrite("name", &translator_info::name, "")
//.def_readwrite("MIME", &translator_info::MIME, "")
.def_property("name",
                      [](const translator_info &t) {
                          return std::string(t.name);
                      },
                      [](translator_info &t, const std::string &value) {
                          std::strncpy(t.name, value.c_str(), sizeof(t.name));
                      })
.def_property("MIME",
                      [](const translator_info &t) {
                          return std::string(t.MIME);
                      },
                      [](translator_info &t, const std::string &value) {
                          std::strncpy(t.MIME, value.c_str(), sizeof(t.MIME));
                      })
;


}
