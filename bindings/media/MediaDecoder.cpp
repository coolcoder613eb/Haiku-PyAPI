#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <media/MediaDecoder.h>

namespace py = pybind11;
using namespace BPrivate;
using namespace BPrivate::media;

class PyBMediaDecoder : public BMediaDecoder{
	public:
        using BMediaDecoder::BMediaDecoder;
        status_t GetNextChunk(const void **chunkData, size_t *chunkLen, media_header *mh) override {
        	PYBIND11_OVERRIDE_PURE( status_t, BMediaDecoder, GetNextChunk, chunkData, chunkLen, mh ); 
    } 
};

PYBIND11_MODULE(MediaDecoder, m)
{

//m.attr("Decoder") = py::cast(Decoder);

//m.attr("Decoder") = py::cast(Decoder);

//m.attr("DecoderPlugin") = py::cast(DecoderPlugin);

py::class_<BMediaDecoder,PyBMediaDecoder>(m, "BMediaDecoder")
.def(py::init(), "")
.def(py::init<const media_format *, const void *, size_t>(), "", py::arg("in_format"), py::arg("info")=NULL, py::arg("info_size")=0)
.def(py::init<const media_codec_info *>(), "", py::arg("mci"))
.def("InitCheck", &BMediaDecoder::InitCheck, "")
.def("SetTo", py::overload_cast<const media_format *, const void *, size_t>(&BMediaDecoder::SetTo), "", py::arg("in_format"), py::arg("info")=NULL, py::arg("info_size")=0)
.def("SetTo", py::overload_cast<const media_codec_info *>(&BMediaDecoder::SetTo), "", py::arg("mci"))
.def("SetInputFormat", &BMediaDecoder::SetInputFormat, "", py::arg("in_format"), py::arg("in_info")=NULL, py::arg("in_size")=0) // TODO
.def("SetOutputFormat", &BMediaDecoder::SetOutputFormat, "", py::arg("output_format"))
.def("Decode", &BMediaDecoder::Decode, "", py::arg("out_buffer"), py::arg("out_frameCount"), py::arg("out_mh"), py::arg("info")) // TODO out_buffer
.def("GetDecoderInfo", &BMediaDecoder::GetDecoderInfo, "", py::arg("out_info"))
;

py::class_<BMediaBufferDecoder, BMediaDecoder>(m, "BMediaBufferDecoder")
.def(py::init(), "")
.def(py::init<const media_format *, const void *, size_t>(), "", py::arg("in_format"), py::arg("info")=NULL, py::arg("info_size")=0)
.def(py::init<const media_codec_info *>(), "", py::arg("mci"))
.def("DecodeBuffer", &BMediaBufferDecoder::DecodeBuffer, "", py::arg("input_buffer"), py::arg("input_size"), py::arg("out_buffer"), py::arg("out_frameCount"), py::arg("out_mh"), py::arg("info")=NULL) // TODO handle buffers
;


}
