#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <media/MediaTheme.h>
#include <media/ParameterWeb.h>
#include <View.h>
#include <Control.h>
#include <Bitmap.h>

namespace py = pybind11;
using namespace BPrivate;
//using namespace BPrivate::media;

PYBIND11_MODULE(MediaTheme, m)
{
py::enum_<BMediaTheme::bg_kind>(m, "bg_kind", "")
.value("B_GENERAL_BG", BMediaTheme::bg_kind::B_GENERAL_BG, "")
.value("B_SETTINGS_BG", BMediaTheme::bg_kind::B_SETTINGS_BG, "")
.value("B_PRESENTATION_BG", BMediaTheme::bg_kind::B_PRESENTATION_BG, "")
.value("B_EDIT_BG", BMediaTheme::bg_kind::B_EDIT_BG, "")
.value("B_CONTROL_BG", BMediaTheme::bg_kind::B_CONTROL_BG, "")
.value("B_HILITE_BG", BMediaTheme::bg_kind::B_HILITE_BG, "")
.export_values();
py::enum_<BMediaTheme::fg_kind>(m, "fg_kind", "")
.value("B_GENERAL_FG", BMediaTheme::fg_kind::B_GENERAL_FG, "")
.value("B_SETTINGS_FG", BMediaTheme::fg_kind::B_SETTINGS_FG, "")
.value("B_PRESENTATION_FG", BMediaTheme::fg_kind::B_PRESENTATION_FG, "")
.value("B_EDIT_FG", BMediaTheme::fg_kind::B_EDIT_FG, "")
.value("B_CONTROL_FG", BMediaTheme::fg_kind::B_CONTROL_FG, "")
.value("B_HILITE_FG", BMediaTheme::fg_kind::B_HILITE_FG, "")
.export_values();
py::class_<BMediaTheme>(m, "BMediaTheme")
.def("Name", &BMediaTheme::Name, "")
.def("Info", &BMediaTheme::Info, "")
.def("ID", &BMediaTheme::ID, "")
.def("GetRef", &BMediaTheme::GetRef, "", py::arg("ref"))
.def_static("ViewFor", &BMediaTheme::ViewFor, "", py::arg("web"), py::arg("hintRect")=NULL, py::arg("usingTheme")=NULL)
.def_static("SetPreferredTheme", &BMediaTheme::SetPreferredTheme, "", py::arg("defaultTheme")=NULL)
.def_static("PreferredTheme", &BMediaTheme::PreferredTheme, "")
.def("MakeControlFor", &BMediaTheme::MakeControlFor, "", py::arg("control"))
.def("BackgroundBitmapFor", &BMediaTheme::BackgroundBitmapFor, "", py::arg("bg")=BMediaTheme::bg_kind::B_GENERAL_BG)
.def("BackgroundColorFor", &BMediaTheme::BackgroundColorFor, "", py::arg("bg")=BMediaTheme::bg_kind::B_GENERAL_BG)
.def("ForegroundColorFor", &BMediaTheme::ForegroundColorFor, "", py::arg("fg")=BMediaTheme::fg_kind::B_GENERAL_FG)
;

//m.def("make_theme", &make_theme, "", py::arg("id"), py::arg("you")); //where are these?

//m.def("get_theme_at", &get_theme_at, "", py::arg("index"), py::arg("_name"), py::arg("_info"), py::arg("_id"));

}
