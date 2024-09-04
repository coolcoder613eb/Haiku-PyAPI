#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <media/MediaFormats.h>

namespace py = pybind11;
using namespace BPrivate;
using namespace BPrivate::media;

void define_MediaFormats(py::module_& m)
{
py::enum_<media_file_accept_format_flags>(m, "media_file_accept_format_flags", "")
.value("B_MEDIA_REJECT_WILDCARDS", media_file_accept_format_flags::B_MEDIA_REJECT_WILDCARDS, "")
.export_values();

py::enum_<beos_format>(m, "beos_format", "")
.value("B_BEOS_FORMAT_RAW_AUDIO", beos_format::B_BEOS_FORMAT_RAW_AUDIO, "")
.value("B_BEOS_FORMAT_RAW_VIDEO", beos_format::B_BEOS_FORMAT_RAW_VIDEO, "")
.export_values();

py::enum_<mpeg_id>(m, "mpeg_id", "")
.value("B_MPEG_ANY", mpeg_id::B_MPEG_ANY, "")
.value("B_MPEG_1_AUDIO_LAYER_1", mpeg_id::B_MPEG_1_AUDIO_LAYER_1, "")
.value("B_MPEG_1_AUDIO_LAYER_2", mpeg_id::B_MPEG_1_AUDIO_LAYER_2, "")
.value("B_MPEG_1_AUDIO_LAYER_3", mpeg_id::B_MPEG_1_AUDIO_LAYER_3, "")
.value("B_MPEG_1_VIDEO", mpeg_id::B_MPEG_1_VIDEO, "")
.value("B_MPEG_2_AUDIO_LAYER_1", mpeg_id::B_MPEG_2_AUDIO_LAYER_1, "")
.value("B_MPEG_2_AUDIO_LAYER_2", mpeg_id::B_MPEG_2_AUDIO_LAYER_2, "")
.value("B_MPEG_2_AUDIO_LAYER_3", mpeg_id::B_MPEG_2_AUDIO_LAYER_3, "")
.value("B_MPEG_2_VIDEO", mpeg_id::B_MPEG_2_VIDEO, "")
.value("B_MPEG_2_5_AUDIO_LAYER_1", mpeg_id::B_MPEG_2_5_AUDIO_LAYER_1, "")
.value("B_MPEG_2_5_AUDIO_LAYER_2", mpeg_id::B_MPEG_2_5_AUDIO_LAYER_2, "")
.value("B_MPEG_2_5_AUDIO_LAYER_3", mpeg_id::B_MPEG_2_5_AUDIO_LAYER_3, "")
.export_values();

py::class_<media_codec_info>(m, "media_codec_info")
.def_readwrite("pretty_name", &media_codec_info::pretty_name, "")
.def_readwrite("short_name", &media_codec_info::short_name, "")
.def_readwrite("id", &media_codec_info::id, "")
.def_readwrite("sub_id", &media_codec_info::sub_id, "")
.def_readwrite("pad", &media_codec_info::pad, "")
;

py::class_<GUID>(m, "GUID")
.def_readwrite("data", &GUID::data, "")
;

py::class_<media_beos_description>(m, "media_beos_description")
.def_readwrite("format", &media_beos_description::format, "")
;

py::class_<media_quicktime_description>(m, "media_quicktime_description")
.def_readwrite("codec", &media_quicktime_description::codec, "")
.def_readwrite("vendor", &media_quicktime_description::vendor, "")
;

py::class_<media_avi_description>(m, "media_avi_description")
.def_readwrite("codec", &media_avi_description::codec, "")
;

py::class_<media_avr_description>(m, "media_avr_description")
.def_readwrite("id", &media_avr_description::id, "")
;

py::class_<media_asf_description>(m, "media_asf_description")
.def_readwrite("guid", &media_asf_description::guid, "")
;

py::class_<media_mpeg_description>(m, "media_mpeg_description")
.def_readwrite("id", &media_mpeg_description::id, "")
;

py::class_<media_wav_description>(m, "media_wav_description")
.def_readwrite("codec", &media_wav_description::codec, "")
;

py::class_<media_aiff_description>(m, "media_aiff_description")
.def_readwrite("codec", &media_aiff_description::codec, "")
;

py::class_<media_misc_description>(m, "media_misc_description")
.def_readwrite("file_format", &media_misc_description::file_format, "")
.def_readwrite("codec", &media_misc_description::codec, "")
;

py::class_<union >(m, "union ")
.def_readwrite("beos", &union ::beos, "")
.def_readwrite("quicktime", &union ::quicktime, "")
.def_readwrite("avi", &union ::avi, "")
.def_readwrite("asf", &union ::asf, "")
.def_readwrite("mpeg", &union ::mpeg, "")
.def_readwrite("wav", &union ::wav, "")
.def_readwrite("aiff", &union ::aiff, "")
.def_readwrite("misc", &union ::misc, "")
.def_readwrite("avr", &union ::avr, "")
.def_readwrite("_reserved_", &union ::_reserved_, "")
;

py::class_<media_format_description>(m, "media_format_description")
.def(py::init(), "")
.def(py::init<const _media_format_description &>(), "", py::arg("other"))
.def("operator=", &media_format_description::operator=, "", py::arg("other"))
.def_readwrite("family", &media_format_description::family, "")
.def_readwrite("_reserved_", &media_format_description::_reserved_, "")
.def_readwrite("u", &media_format_description::u, "")
;

py::class_<BMediaFormats>(m, "BMediaFormats")
.def(py::init(), "")
.def("InitCheck", &BMediaFormats::InitCheck, "")
.def("MakeFormatFor", py::overload_cast<const media_format_description *, int, media_format *, unsigned int, void *>(&BMediaFormats::MakeFormatFor), "", py::arg("descriptions"), py::arg("descriptionCount"), py::arg("_inOutFormat"), py::arg("flags")=0, py::arg("_reserved")=0)
.def("GetFormatFor", &BMediaFormats::GetFormatFor, "", py::arg("description"), py::arg("_outFormat"))
.def("GetCodeFor", &BMediaFormats::GetCodeFor, "", py::arg("format"), py::arg("family"), py::arg("_outDescription"))
.def("RewindFormats", &BMediaFormats::RewindFormats, "")
.def("GetNextFormat", &BMediaFormats::GetNextFormat, "", py::arg("_outFormat"), py::arg("_outDescription"))
.def("Lock", &BMediaFormats::Lock, "")
.def("Unlock", &BMediaFormats::Unlock, "")
.def_static("GetBeOSFormatFor", &BMediaFormats::GetBeOSFormatFor, "", py::arg("fourcc"), py::arg("_outFormat"), py::arg("type")=B_MEDIA_UNKNOWN_TYPE)
.def_static("GetAVIFormatFor", &BMediaFormats::GetAVIFormatFor, "", py::arg("fourcc"), py::arg("_outFormat"), py::arg("type")=B_MEDIA_UNKNOWN_TYPE)
.def_static("GetQuicktimeFormatFor", &BMediaFormats::GetQuicktimeFormatFor, "", py::arg("vendor"), py::arg("fourcc"), py::arg("_outFormat"), py::arg("type")=B_MEDIA_UNKNOWN_TYPE)
.def("MakeFormatFor", py::overload_cast<const media_format_description &, const media_format &, media_format *>(&BMediaFormats::MakeFormatFor), "", py::arg("description"), py::arg("inFormat"), py::arg("_outFormat"))
;

m.def("get_next_encoder", py::overload_cast<int, const media_file_format *, const media_format *, media_format *, media_codec_info *>(&get_next_encoder), 
        R"ipc_Qu8mg5v7(
        /*!	\brief	Use this to iterate through the available encoders for a given file
format.
\param cookie		A pointer to a preallocated cookie, which you need
to initialize to \c 0 before calling this function
the first time.
\param fileFormat	A pointer to a valid media_file_format structure
as can be obtained through get_next_file_format().
\param inputFormat	This is the type of data given to the encoder.
\param _outputFormat This is the type of data the encoder will output.
\param _codecInfo	Pointer to a preallocated media_codec_info structure,
information about the encoder is placed there.
\return
- \c B_OK: Everything went fine.
- \c B_BAD_INDEX: There are no more encoders.
*/
        )ipc_Qu8mg5v7", py::arg("cookie"), py::arg("fileFormat"), py::arg("inputFormat"), py::arg("_outputFormat"), py::arg("_codecInfo"));

m.def("get_next_encoder", py::overload_cast<int, const media_file_format *, const media_format *, const media_format *, media_codec_info *, media_format *, media_format *>(&get_next_encoder), 
        R"ipc_Qu8mg5v7(
        /*!	\brief	Use this to iterate through the available encoders with
restrictions to the input and output media_format while the
encoders can specialize wildcards in the media_formats.
\param cookie		A pointer to a preallocated cookie, which you need
to initialize to \c 0 before calling this function
the first time.
\param fileFormat	A pointer to a valid media_file_format structure
as can be obtained through get_next_file_format().
You can pass \c NULL if you don't care.
\param inputFormat	This is the type of data given to the encoder,
wildcards are accepted.
\param outputFormat	This is the type of data you want the encoder to
output. Wildcards are accepted.
\param _codecInfo	Pointer to a preallocated media_codec_info structure,
information about the encoder is placed there.
\param _acceptedInputFormat This is the type of data that the encoder will
accept as input. Wildcards in \a inFormat will be
specialized here.
\param _acceptedOutputFormat This is the type of data that the encoder will
output. Wildcards in \a _outFormat will be specialized
here.
\return
- \c B_OK: Everything went fine.
- \c B_BAD_INDEX: There are no more encoders.
*/
        )ipc_Qu8mg5v7", py::arg("cookie"), py::arg("fileFormat"), py::arg("inputFormat"), py::arg("outputFormat"), py::arg("_codecInfo"), py::arg("_acceptedInputFormat"), py::arg("_acceptedOutputFormat"));

m.def("get_next_encoder", py::overload_cast<int, media_codec_info *>(&get_next_encoder), 
        R"ipc_Qu8mg5v7(
        /*!	\brief	Iterate over the all the available encoders without media_format
restrictions.
\param cookie		A pointer to a preallocated cookie, which you need
to initialize to \c 0 before calling this function
the first time.
\param _codecInfo	Pointer to a preallocated media_codec_info structure,
information about the encoder is placed there.
\return
- \c B_OK: Everything went fine.
- \c B_BAD_INDEX: There are no more encoders.
*/
        )ipc_Qu8mg5v7", py::arg("cookie"), py::arg("_codecInfo"));

m.def("does_file_accept_format", &does_file_accept_format, "", py::arg("fileFormat"), py::arg("format"), py::arg("flags")=0);

m.def("__eq__", py::overload_cast<const media_format_description &, const media_format_description &>(&operator==), "", py::arg("a"), py::arg("b"));

m.def("__lt__", py::overload_cast<const media_format_description &, const media_format_description &>(&operator<), "", py::arg("a"), py::arg("b"));

m.def("__eq__", py::overload_cast<const GUID &, const GUID &>(&operator==), "", py::arg("a"), py::arg("b"));

m.def("__lt__", py::overload_cast<const GUID &, const GUID &>(&operator<), "", py::arg("a"), py::arg("b"));

}
