#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <media/MediaFile.h>
#include <Url.h>
#include <media/MediaTrack.h>
#include <media/ParameterWeb.h>
#include <View.h>

namespace py = pybind11;
using namespace BPrivate;
//using namespace BPrivate::media;

PYBIND11_MODULE(MediaFile, m)
{
m.attr("B_MEDIA_FILE_REPLACE_MODE") = 0x00000001;//py::cast(B_MEDIA_FILE_REPLACE_MODE);
m.attr("B_MEDIA_FILE_NO_READ_AHEAD") = 0x00000002;//py::cast(B_MEDIA_FILE_NO_READ_AHEAD);
m.attr("B_MEDIA_FILE_UNBUFFERED") = 0x00000006;//py::cast(B_MEDIA_FILE_UNBUFFERED);
m.attr("B_MEDIA_FILE_BIG_BUFFERS") = 0x00000008;//py::cast(B_MEDIA_FILE_BIG_BUFFERS);

//m.attr("MediaExtractor") = py::cast(MediaExtractor);

//m.attr("MediaStreamer") = py::cast(MediaStreamer);

//m.attr("MediaWriter") = py::cast(MediaWriter);

//m.attr("_AddonManager") = py::cast(_AddonManager);
//TODO gestre dati void
py::class_<BMediaFile>(m, "BMediaFile")
.def(py::init<const entry_ref *>(), "", py::arg("ref"))
.def(py::init<BDataIO *>(), "", py::arg("source"))
.def(py::init<const entry_ref *, int>(), "", py::arg("ref"), py::arg("flags"))
.def(py::init<BDataIO *, int>(), "", py::arg("source"), py::arg("flags"))
.def(py::init<const entry_ref *, const media_file_format *, int>(), "", py::arg("ref"), py::arg("mfi"), py::arg("flags")=0)
.def(py::init<BDataIO *, const media_file_format *, int>(), "", py::arg("destination"), py::arg("mfi"), py::arg("flags")=0)
.def(py::init<const media_file_format *, int>(), "", py::arg("mfi"), py::arg("flags")=0)
.def(py::init<const BUrl &>(), "", py::arg("url"))
.def(py::init<const BUrl &, int>(), "", py::arg("url"), py::arg("flags"))
.def(py::init<const BUrl &, const media_file_format *, int>(), "", py::arg("destination"), py::arg("mfi"), py::arg("flags")=0)
.def("SetTo", py::overload_cast<const entry_ref *>(&BMediaFile::SetTo), "", py::arg("ref"))
.def("SetTo", py::overload_cast<BDataIO *>(&BMediaFile::SetTo), "", py::arg("destination"))
.def("SetTo", py::overload_cast<const BUrl &>(&BMediaFile::SetTo), "", py::arg("url"))
.def("InitCheck", &BMediaFile::InitCheck, "")
.def("GetFileFormatInfo", &BMediaFile::GetFileFormatInfo, "", py::arg("mfi"))
.def("GetMetaData", &BMediaFile::GetMetaData, "", py::arg("_data"))
.def("Copyright", &BMediaFile::Copyright, "")
.def("CountTracks", &BMediaFile::CountTracks, "")
.def("TrackAt", &BMediaFile::TrackAt, "", py::arg("index"))
.def("ReleaseTrack", &BMediaFile::ReleaseTrack, "", py::arg("track"))
.def("ReleaseAllTracks", &BMediaFile::ReleaseAllTracks, "")
.def("CreateTrack", py::overload_cast<media_format *, const media_codec_info *, unsigned int>(&BMediaFile::CreateTrack), "", py::arg("mf"), py::arg("mci"), py::arg("flags")=0)
.def("CreateTrack", py::overload_cast<media_format *, unsigned int>(&BMediaFile::CreateTrack), "", py::arg("mf"), py::arg("flags")=0)
.def("AddCopyright", &BMediaFile::AddCopyright, "", py::arg("data"))
.def("AddChunk", &BMediaFile::AddChunk, "", py::arg("type"), py::arg("data"), py::arg("size"))
.def("CommitHeader", &BMediaFile::CommitHeader, "")
.def("CloseFile", &BMediaFile::CloseFile, "")
//.def("GetParameterWeb", &BMediaFile::GetParameterWeb, "", py::arg("outWeb"))
.def("GetParameterWeb", [](BMediaFile &self) {
	BParameterWeb* web = nullptr;
	status_t status = self.GetParameterWeb(&web);
	return std::make_tuple(status, web);
	},"")
.def("GetParameterValue", &BMediaFile::GetParameterValue, "", py::arg("id"), py::arg("value"), py::arg("size"))
.def("SetParameterValue", &BMediaFile::SetParameterValue, "", py::arg("id"), py::arg("value"), py::arg("size"))
.def("GetParameterView", &BMediaFile::GetParameterView, "")
.def("Perform", &BMediaFile::Perform, "", py::arg("selector"), py::arg("data"))
;


}
