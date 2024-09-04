#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <media/MediaEncoder.h>

namespace py = pybind11;
using namespace BPrivate;
using namespace BPrivate::media;

void define_MediaEncoder(py::module_& m)
{
m.attr("Encoder") = py::cast(Encoder);

m.attr("EncoderPlugin") = py::cast(EncoderPlugin);

py::class_<BMediaEncoder>(m, "BMediaEncoder")
.def(py::init(), "")
.def(py::init<const media_format *>(), "", py::arg("outputFormat"))
.def(py::init<const media_codec_info *>(), "", py::arg("info"))
.def("InitCheck", &BMediaEncoder::InitCheck, "")
.def("SetTo", py::overload_cast<const media_format *>(&BMediaEncoder::SetTo), "", py::arg("outputFormat"))
.def("SetTo", py::overload_cast<const media_codec_info *>(&BMediaEncoder::SetTo), "", py::arg("info"))
.def("SetFormat", &BMediaEncoder::SetFormat, "", py::arg("inputFormat"), py::arg("outputFormat"), py::arg("fileFormat")=NULL)
.def("Encode", &BMediaEncoder::Encode, "", py::arg("buffer"), py::arg("frameCount"), py::arg("info"))
.def("GetEncodeParameters", &BMediaEncoder::GetEncodeParameters, "", py::arg("parameters"))
.def("SetEncodeParameters", &BMediaEncoder::SetEncodeParameters, "", py::arg("parameters"))
;

py::class_<BMediaBufferEncoder, BMediaEncoder>(m, "BMediaBufferEncoder")
.def(py::init(), "")
.def(py::init<const media_format *>(), "", py::arg("outputFormat"))
.def(py::init<const media_codec_info *>(), "", py::arg("info"))
.def("EncodeToBuffer", &BMediaBufferEncoder::EncodeToBuffer, "", py::arg("outputBuffer"), py::arg("_size"), py::arg("inputBuffer"), py::arg("frameCount"), py::arg("info"))
;


}
