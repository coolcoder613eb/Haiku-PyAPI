#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <media/MediaTheme.h>

namespace py = pybind11;
using namespace BPrivate;
using namespace BPrivate::media;

void define_MediaTheme(py::module_& m)
{
py::class_<BMediaTheme>(m, "BMediaTheme")
.def("Name", &BMediaTheme::Name, "")
.def("Info", &BMediaTheme::Info, "")
.def("ID", &BMediaTheme::ID, "")
.def("GetRef", &BMediaTheme::GetRef, "", py::arg("ref"))
.def_static("ViewFor", &BMediaTheme::ViewFor, "", py::arg("web"), py::arg("hintRect")=NULL, py::arg("usingTheme")=NULL)
.def_static("SetPreferredTheme", &BMediaTheme::SetPreferredTheme, "", py::arg("defaultTheme")=NULL)
.def_static("PreferredTheme", &BMediaTheme::PreferredTheme, "")
.def("MakeControlFor", &BMediaTheme::MakeControlFor, "", py::arg("control"))
.def("BackgroundBitmapFor", &BMediaTheme::BackgroundBitmapFor, "", py::arg("bg")=B_GENERAL_BG)
.def("BackgroundColorFor", &BMediaTheme::BackgroundColorFor, "", py::arg("bg")=B_GENERAL_BG)
.def("ForegroundColorFor", &BMediaTheme::ForegroundColorFor, "", py::arg("fg")=B_GENERAL_FG)
;

m.def("make_theme", &make_theme, "", py::arg("id"), py::arg("you"));

m.def("get_theme_at", &get_theme_at, "", py::arg("index"), py::arg("_name"), py::arg("_info"), py::arg("_id"));

}
