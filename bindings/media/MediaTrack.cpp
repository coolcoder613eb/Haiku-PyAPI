#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <media/MediaTrack.h>

namespace py = pybind11;
using namespace BPrivate;
using namespace BPrivate::media;

void define_MediaTrack(py::module_& m)
{
py::enum_<media_seek_type>(m, "media_seek_type", "")
.value("B_MEDIA_SEEK_CLOSEST_FORWARD", media_seek_type::B_MEDIA_SEEK_CLOSEST_FORWARD, "")
.value("B_MEDIA_SEEK_CLOSEST_BACKWARD", media_seek_type::B_MEDIA_SEEK_CLOSEST_BACKWARD, "")
.value("B_MEDIA_SEEK_DIRECTION_MASK", media_seek_type::B_MEDIA_SEEK_DIRECTION_MASK, "")
.export_values();

m.attr("Decoder") = py::cast(Decoder);

m.attr("Encoder") = py::cast(Encoder);

m.attr("MediaExtractor") = py::cast(MediaExtractor);

m.attr("MediaWriter") = py::cast(MediaWriter);

py::class_<BMediaTrack>(m, "BMediaTrack")
.def("InitCheck", &BMediaTrack::InitCheck, "")
.def("GetCodecInfo", &BMediaTrack::GetCodecInfo, "", py::arg("_codecInfo"))
.def("EncodedFormat", &BMediaTrack::EncodedFormat, "", py::arg("_format"))
.def("DecodedFormat", &BMediaTrack::DecodedFormat, "", py::arg("_format"), py::arg("flags")=0)
.def("CountFrames", &BMediaTrack::CountFrames, "")
.def("Duration", &BMediaTrack::Duration, "")
.def("GetMetaData", &BMediaTrack::GetMetaData, "", py::arg("_data"))
.def("CurrentFrame", &BMediaTrack::CurrentFrame, "")
.def("CurrentTime", &BMediaTrack::CurrentTime, "")
.def("ReadFrames", py::overload_cast<void *, int64_t, media_header *>(&BMediaTrack::ReadFrames), "", py::arg("buffer"), py::arg("_frameCount"), py::arg("header")=NULL)
.def("ReadFrames", py::overload_cast<void *, int64_t, media_header *, media_decode_info *>(&BMediaTrack::ReadFrames), "", py::arg("buffer"), py::arg("_frameCount"), py::arg("header"), py::arg("info"))
.def("ReplaceFrames", &BMediaTrack::ReplaceFrames, "", py::arg("buffer"), py::arg("_frameCount"), py::arg("header"))
.def("SeekToTime", &BMediaTrack::SeekToTime, "", py::arg("_time"), py::arg("flags")=0)
.def("SeekToFrame", &BMediaTrack::SeekToFrame, "", py::arg("_frame"), py::arg("flags")=0)
.def("FindKeyFrameForTime", &BMediaTrack::FindKeyFrameForTime, "", py::arg("_time"), py::arg("flags")=0)
.def("FindKeyFrameForFrame", &BMediaTrack::FindKeyFrameForFrame, "", py::arg("_frame"), py::arg("flags")=0)
.def("ReadChunk", &BMediaTrack::ReadChunk, "", py::arg("_buffer"), py::arg("_size"), py::arg("_header")=NULL)
.def("AddCopyright", &BMediaTrack::AddCopyright, "", py::arg("copyright"))
.def("AddTrackInfo", &BMediaTrack::AddTrackInfo, "", py::arg("code"), py::arg("data"), py::arg("size"), py::arg("flags")=0)
.def("WriteFrames", py::overload_cast<const void *, int, int>(&BMediaTrack::WriteFrames), "", py::arg("data"), py::arg("frameCount"), py::arg("flags")=0)
.def("WriteFrames", py::overload_cast<const void *, int64_t, media_encode_info *>(&BMediaTrack::WriteFrames), "", py::arg("data"), py::arg("frameCount"), py::arg("info"))
.def("WriteChunk", py::overload_cast<const void *, size_t, unsigned int>(&BMediaTrack::WriteChunk), "", py::arg("data"), py::arg("size"), py::arg("flags")=0)
.def("WriteChunk", py::overload_cast<const void *, size_t, media_encode_info *>(&BMediaTrack::WriteChunk), "", py::arg("data"), py::arg("size"), py::arg("info"))
.def("Flush", &BMediaTrack::Flush, "")
.def("GetParameterWeb", &BMediaTrack::GetParameterWeb, "", py::arg("_web"))
.def("GetParameterValue", &BMediaTrack::GetParameterValue, "", py::arg("id"), py::arg("value"), py::arg("size"))
.def("SetParameterValue", &BMediaTrack::SetParameterValue, "", py::arg("id"), py::arg("value"), py::arg("size"))
.def("GetParameterView", &BMediaTrack::GetParameterView, "")
.def("GetQuality", &BMediaTrack::GetQuality, "", py::arg("_quality"))
.def("SetQuality", &BMediaTrack::SetQuality, "", py::arg("quality"))
.def("GetEncodeParameters", &BMediaTrack::GetEncodeParameters, "", py::arg("parameters"))
.def("SetEncodeParameters", &BMediaTrack::SetEncodeParameters, "", py::arg("parameters"))
.def("Perform", &BMediaTrack::Perform, "", py::arg("code"), py::arg("data"))
;


}
