#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <translation/TranslationDefs.h>

namespace py = pybind11;


void define_TranslationDefs(py::module_& m)
{
m.attr("B_TRANSLATOR_MIME_TYPE") = py::cast(B_TRANSLATOR_MIME_TYPE);

py::class_<translation_format>(m, "translation_format")
.def_readwrite("type", &translation_format::type, "")
.def_readwrite("group", &translation_format::group, "")
.def_readwrite("quality", &translation_format::quality, "")
.def_readwrite("capability", &translation_format::capability, "")
.def_readwrite("MIME", &translation_format::MIME, "")
.def_readwrite("name", &translation_format::name, "")
;

py::class_<translator_info>(m, "translator_info")
.def_readwrite("type", &translator_info::type, "")
.def_readwrite("translator", &translator_info::translator, "")
.def_readwrite("group", &translator_info::group, "")
.def_readwrite("quality", &translator_info::quality, "")
.def_readwrite("capability", &translator_info::capability, "")
.def_readwrite("name", &translator_info::name, "")
.def_readwrite("MIME", &translator_info::MIME, "")
;


}
