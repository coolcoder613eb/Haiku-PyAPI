#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/Gradient.h>
#include <Archivable.h>
#include <GraphicsDefs.h>
#include <List.h>

namespace py = pybind11;


PYBIND11_MODULE(Gradient,m)
{
py::class_<BGradient, BArchivable>(m, "BGradient")
.def(py::init(), "")
.def(py::init<const BGradient &>(), "", py::arg("other"))
.def(py::init<BMessage *>(), "", py::arg("archive"))
.def("Archive", &BGradient::Archive, "", py::arg("into"), py::arg("deep")=true)
.def("__copy__", &BGradient::operator=, "", py::arg("other"))
.def("__eq__", &BGradient::operator==, "", py::arg("other"))
.def("__ne__", &BGradient::operator!=, "", py::arg("other"))
.def("ColorStopsAreEqual", &BGradient::ColorStopsAreEqual, "", py::arg("other"))
.def("SetColorStops", &BGradient::SetColorStops, "", py::arg("other"))
.def("AddColor", &BGradient::AddColor, "", py::arg("color"), py::arg("offset"))
.def("AddColorStop", &BGradient::AddColorStop, "", py::arg("colorStop"), py::arg("index"))
.def("RemoveColor", &BGradient::RemoveColor, "", py::arg("index"))
.def("SetColorStop", &BGradient::SetColorStop, "", py::arg("index"), py::arg("colorStop"))
.def("SetColor", &BGradient::SetColor, "", py::arg("index"), py::arg("color"))
.def("SetOffset", &BGradient::SetOffset, "", py::arg("index"), py::arg("offset"))
.def("CountColorStops", &BGradient::CountColorStops, "")
.def("ColorStopAt", &BGradient::ColorStopAt, "", py::arg("index"))
.def("ColorStopAtFast", &BGradient::ColorStopAtFast, "", py::arg("index"))
.def("ColorStops", &BGradient::ColorStops, "")
.def("SortColorStopsByOffset", &BGradient::SortColorStopsByOffset, "")
.def("GetType", &BGradient::GetType, "")
.def("MakeEmpty", &BGradient::MakeEmpty, "")
.def("Flatten", &BGradient::Flatten, "", py::arg("stream"))
/*.def_static("Unflatten", [](BGradient& self,BDataIO * stream) {    // TODO
    BGradient *  output;
    static status_t r = self.Unflatten(output, stream);
    return std::make_tuple(r,output);
}
, "", py::arg("stream"))*/

/*.def_static("Unflatten", [](BGradient& self, BGradient*& output, BDataIO * stream) {
    static status_t r = self.Unflatten(output, stream);
    return r;
}
, "", py::arg("output"), py::arg("stream"))*/
;

py::enum_<BGradient::Type>(m, "Type")
.value("TYPE_LINEAR", BGradient::Type::TYPE_LINEAR, "")
.value("TYPE_RADIAL", BGradient::Type::TYPE_RADIAL, "")
.value("TYPE_RADIAL_FOCUS", BGradient::Type::TYPE_RADIAL_FOCUS, "")
.value("TYPE_DIAMOND", BGradient::Type::TYPE_DIAMOND, "")
.value("TYPE_CONIC", BGradient::Type::TYPE_CONIC, "")
.value("TYPE_NONE", BGradient::Type::TYPE_NONE, "")
.export_values();

py::class_<BGradient::ColorStop>(m, "ColorStop")
.def(py::init<const rgb_color, float>(), "", py::arg("c"), py::arg("o"))
.def(py::init<unsigned char, unsigned char, unsigned char, unsigned char, float>(), "", py::arg("r"), py::arg("g"), py::arg("b"), py::arg("a"), py::arg("o"))
.def(py::init<const BGradient::ColorStop &>(), "", py::arg("other"))
.def(py::init(), "")
.def("__ne__", &BGradient::ColorStop::operator!=, "", py::arg("other"))
.def_readwrite("color", &BGradient::ColorStop::color, "")
.def_readwrite("offset", &BGradient::ColorStop::offset, "")
;
/*
py::class_<union >(m, "union ")
.def_readwrite("linear", &union ::linear, "")
.def_readwrite("radial", &union ::radial, "")
.def_readwrite("radial_focus", &union ::radial_focus, "")
.def_readwrite("diamond", &union ::diamond, "")
.def_readwrite("conic", &union ::conic, "")
;

py::class_<>(m, "")
.def_readwrite("cx", &::cx, "")
.def_readwrite("cy", &::cy, "")
.def_readwrite("angle", &::angle, "")
;

*/
}
