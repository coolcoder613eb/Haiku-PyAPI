#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>
#include <pybind11/numpy.h>

#include <media/MediaDefs.h>
#include <MediaNode.h>

namespace py = pybind11;
using namespace BPrivate;
//using namespace BPrivate::media;

PYBIND11_MODULE(MediaDefs, m)
{
/*
m.attr("B_MEDIA_WILDCARD") = py::cast(B_MEDIA_WILDCARD);
m.attr("B_MEDIA_NODE_CREATED") = py::cast(B_MEDIA_NODE_CREATED);
m.attr("B_MEDIA_NODE_DELETED") = py::cast(B_MEDIA_NODE_DELETED);
m.attr("B_MEDIA_CONNECTION_MADE") = py::cast(B_MEDIA_CONNECTION_MADE);
m.attr("B_MEDIA_CONNECTION_BROKEN") = py::cast(B_MEDIA_CONNECTION_BROKEN);
m.attr("B_MEDIA_BUFFER_CREATED") = py::cast(B_MEDIA_BUFFER_CREATED);
m.attr("B_MEDIA_BUFFER_DELETED") = py::cast(B_MEDIA_BUFFER_DELETED);
m.attr("B_MEDIA_TRANSPORT_STATE") = py::cast(B_MEDIA_TRANSPORT_STATE);
m.attr("B_MEDIA_PARAMETER_CHANGED") = py::cast(B_MEDIA_PARAMETER_CHANGED);
m.attr("B_MEDIA_FORMAT_CHANGED") = py::cast(B_MEDIA_FORMAT_CHANGED);
m.attr("B_MEDIA_WEB_CHANGED") = py::cast(B_MEDIA_WEB_CHANGED);
m.attr("B_MEDIA_DEFAULT_CHANGED") = py::cast(B_MEDIA_DEFAULT_CHANGED);
m.attr("B_MEDIA_NEW_PARAMETER_VALUE") = py::cast(B_MEDIA_NEW_PARAMETER_VALUE);
m.attr("B_MEDIA_NODE_STOPPED") = py::cast(B_MEDIA_NODE_STOPPED);
m.attr("B_MEDIA_FLAVORS_CHANGED") = py::cast(B_MEDIA_FLAVORS_CHANGED);
m.attr("B_MEDIA_SERVER_STARTED") = py::cast(B_MEDIA_SERVER_STARTED);
m.attr("B_MEDIA_SERVER_QUIT") = py::cast(B_MEDIA_SERVER_QUIT);
*/

m.attr("B_MEDIA_WILDCARD") = 'TRWC';
m.attr("B_MEDIA_NODE_CREATED") = 'TRIA';
m.attr("B_MEDIA_NODE_DELETED") = 'TRIB';
m.attr("B_MEDIA_CONNECTION_MADE") = 'TRIC';
m.attr("B_MEDIA_CONNECTION_BROKEN") = 'TRID';
m.attr("B_MEDIA_BUFFER_CREATED") = 'TRIE';
m.attr("B_MEDIA_BUFFER_DELETED") = 'TRIF';
m.attr("B_MEDIA_TRANSPORT_STATE") = 'TRIG';
m.attr("B_MEDIA_PARAMETER_CHANGED") = 'TRIH';
m.attr("B_MEDIA_FORMAT_CHANGED") = 'TRII';
m.attr("B_MEDIA_WEB_CHANGED") = 'TRIJ';
m.attr("B_MEDIA_DEFAULT_CHANGED") = 'TRIK';
m.attr("B_MEDIA_NEW_PARAMETER_VALUE") = 'TRIL';
m.attr("B_MEDIA_NODE_STOPPED") = 'TRIM';
m.attr("B_MEDIA_FLAVORS_CHANGED") = 'TRIN';
m.attr("B_MEDIA_SERVER_STARTED") = 'TRIO';
m.attr("B_MEDIA_SERVER_QUIT") = 'TRIP';

/*
B_MEDIA_WILDCARD = 'TRWC', // 0x54525743 = 1415073475 
B_MEDIA_NODE_CREATED = 'TRIA', // 0x54524941 = 1415073441 
B_MEDIA_NODE_DELETED = 'TRIA' + 1, // 1415073442 
B_MEDIA_CONNECTION_MADE = 'TRIA' + 2, // 1415073443 
B_MEDIA_CONNECTION_BROKEN = 'TRIA' + 3, // 1415073444 
B_MEDIA_BUFFER_CREATED = 'TRIA' + 4, // 1415073445 
B_MEDIA_BUFFER_DELETED = 'TRIA' + 5, // 1415073446 
B_MEDIA_TRANSPORT_STATE = 'TRIA' + 6, // 1415073447 
B_MEDIA_PARAMETER_CHANGED = 'TRIA' + 7, // 1415073448 
B_MEDIA_FORMAT_CHANGED = 'TRIA' + 8, // 1415073449 
B_MEDIA_WEB_CHANGED = 'TRIA' + 9, // 1415073450 
B_MEDIA_DEFAULT_CHANGED = 'TRIA' + 10, // 1415073451 
B_MEDIA_NEW_PARAMETER_VALUE = 'TRIA' + 11, // 1415073452 
B_MEDIA_NODE_STOPPED = 'TRIA' + 12, // 1415073453 
B_MEDIA_FLAVORS_CHANGED = 'TRIA' + 13, // 1415073454 
B_MEDIA_SERVER_STARTED = 'TRIA' + 14, // 1415073455 
B_MEDIA_SERVER_QUIT = 'TRIA' + 15, // 1415073456 
*/

py::enum_<media_type>(m, "media_type", "")
.value("B_MEDIA_NO_TYPE", media_type::B_MEDIA_NO_TYPE, "")
.value("B_MEDIA_UNKNOWN_TYPE", media_type::B_MEDIA_UNKNOWN_TYPE, "")
.value("B_MEDIA_RAW_AUDIO", media_type::B_MEDIA_RAW_AUDIO, "")
.value("B_MEDIA_RAW_VIDEO", media_type::B_MEDIA_RAW_VIDEO, "")
.value("B_MEDIA_VBL", media_type::B_MEDIA_VBL, "")
.value("B_MEDIA_TIMECODE", media_type::B_MEDIA_TIMECODE, "")
.value("B_MEDIA_MIDI", media_type::B_MEDIA_MIDI, "")
.value("B_MEDIA_TEXT", media_type::B_MEDIA_TEXT, "")
.value("B_MEDIA_HTML", media_type::B_MEDIA_HTML, "")
.value("B_MEDIA_MULTISTREAM", media_type::B_MEDIA_MULTISTREAM, "")
.value("B_MEDIA_PARAMETERS", media_type::B_MEDIA_PARAMETERS, "")
.value("B_MEDIA_ENCODED_AUDIO", media_type::B_MEDIA_ENCODED_AUDIO, "")
.value("B_MEDIA_ENCODED_VIDEO", media_type::B_MEDIA_ENCODED_VIDEO, "")
.value("B_MEDIA_PRIVATE", media_type::B_MEDIA_PRIVATE, "")
.value("B_MEDIA_FIRST_USER_TYPE", media_type::B_MEDIA_FIRST_USER_TYPE, "")
.export_values();

py::enum_<node_kind>(m, "node_kind", "")
.value("B_BUFFER_PRODUCER", node_kind::B_BUFFER_PRODUCER, "")
.value("B_BUFFER_CONSUMER", node_kind::B_BUFFER_CONSUMER, "")
.value("B_TIME_SOURCE", node_kind::B_TIME_SOURCE, "")
.value("B_CONTROLLABLE", node_kind::B_CONTROLLABLE, "")
.value("B_FILE_INTERFACE", node_kind::B_FILE_INTERFACE, "")
.value("B_ENTITY_INTERFACE", node_kind::B_ENTITY_INTERFACE, "")
.value("B_PHYSICAL_INPUT", node_kind::B_PHYSICAL_INPUT, "")
.value("B_PHYSICAL_OUTPUT", node_kind::B_PHYSICAL_OUTPUT, "")
.value("B_SYSTEM_MIXER", node_kind::B_SYSTEM_MIXER, "")
.export_values();

py::enum_<video_orientation>(m, "video_orientation", "")
.value("B_VIDEO_TOP_LEFT_RIGHT", video_orientation::B_VIDEO_TOP_LEFT_RIGHT, "")
.value("B_VIDEO_BOTTOM_LEFT_RIGHT", video_orientation::B_VIDEO_BOTTOM_LEFT_RIGHT, "")
.export_values();

py::enum_<media_flags>(m, "media_flags", "")
.value("B_MEDIA_FLAGS_VERSION", media_flags::B_MEDIA_FLAGS_VERSION, "")
.value("B_MEDIA_FLAGS_PRIVATE", media_flags::B_MEDIA_FLAGS_PRIVATE, "")
.export_values();

py::enum_<media_producer_status>(m, "media_producer_status", "")
.value("B_DATA_NOT_AVAILABLE", media_producer_status::B_DATA_NOT_AVAILABLE, "")
.value("B_DATA_AVAILABLE", media_producer_status::B_DATA_AVAILABLE, "")
.value("B_PRODUCER_STOPPED", media_producer_status::B_PRODUCER_STOPPED, "")
.export_values();

py::enum_<media_realtime_flags>(m, "media_realtime_flags", "")
.value("B_MEDIA_REALTIME_ALLOCATOR", media_realtime_flags::B_MEDIA_REALTIME_ALLOCATOR, "")
.value("B_MEDIA_REALTIME_AUDIO", media_realtime_flags::B_MEDIA_REALTIME_AUDIO, "")
.value("B_MEDIA_REALTIME_VIDEO", media_realtime_flags::B_MEDIA_REALTIME_VIDEO, "")
.value("B_MEDIA_REALTIME_ANYKIND", media_realtime_flags::B_MEDIA_REALTIME_ANYKIND, "")
.export_values();

py::enum_<media_frame_flags>(m, "media_frame_flags", "")
.value("B_MEDIA_KEY_FRAME", media_frame_flags::B_MEDIA_KEY_FRAME, "")
.export_values();

py::enum_<media_multi_channels>(m, "media_multi_channels", "")
.value("B_CHANNEL_LEFT", media_multi_channels::B_CHANNEL_LEFT, "")
.value("B_CHANNEL_RIGHT", media_multi_channels::B_CHANNEL_RIGHT, "")
.value("B_CHANNEL_CENTER", media_multi_channels::B_CHANNEL_CENTER, "")
.value("B_CHANNEL_SUB", media_multi_channels::B_CHANNEL_SUB, "")
.value("B_CHANNEL_REARLEFT", media_multi_channels::B_CHANNEL_REARLEFT, "")
.value("B_CHANNEL_REARRIGHT", media_multi_channels::B_CHANNEL_REARRIGHT, "")
.value("B_CHANNEL_FRONT_LEFT_CENTER", media_multi_channels::B_CHANNEL_FRONT_LEFT_CENTER, "")
.value("B_CHANNEL_FRONT_RIGHT_CENTER", media_multi_channels::B_CHANNEL_FRONT_RIGHT_CENTER, "")
.value("B_CHANNEL_BACK_CENTER", media_multi_channels::B_CHANNEL_BACK_CENTER, "")
.value("B_CHANNEL_SIDE_LEFT", media_multi_channels::B_CHANNEL_SIDE_LEFT, "")
.value("B_CHANNEL_SIDE_RIGHT", media_multi_channels::B_CHANNEL_SIDE_RIGHT, "")
.value("B_CHANNEL_TOP_CENTER", media_multi_channels::B_CHANNEL_TOP_CENTER, "")
.value("B_CHANNEL_TOP_FRONT_LEFT", media_multi_channels::B_CHANNEL_TOP_FRONT_LEFT, "")
.value("B_CHANNEL_TOP_FRONT_CENTER", media_multi_channels::B_CHANNEL_TOP_FRONT_CENTER, "")
.value("B_CHANNEL_TOP_FRONT_RIGHT", media_multi_channels::B_CHANNEL_TOP_FRONT_RIGHT, "")
.value("B_CHANNEL_TOP_BACK_LEFT", media_multi_channels::B_CHANNEL_TOP_BACK_LEFT, "")
.value("B_CHANNEL_TOP_BACK_CENTER", media_multi_channels::B_CHANNEL_TOP_BACK_CENTER, "")
.value("B_CHANNEL_TOP_BACK_RIGHT", media_multi_channels::B_CHANNEL_TOP_BACK_RIGHT, "")
.export_values();

py::enum_<media_multi_matrix>(m, "media_multi_matrix", "")
.value("B_MATRIX_PROLOGIC_LR", media_multi_matrix::B_MATRIX_PROLOGIC_LR, "")
.value("B_MATRIX_AMBISONIC_WXYZ", media_multi_matrix::B_MATRIX_AMBISONIC_WXYZ, "")
.export_values();

py::enum_<media_display_flags>(m, "media_display_flags", "")
.value("B_F1_DOMINANT", media_display_flags::B_F1_DOMINANT, "")
.value("B_F2_DOMINANT", media_display_flags::B_F2_DOMINANT, "")
.value("B_TOP_SCANLINE_F1", media_display_flags::B_TOP_SCANLINE_F1, "")
.value("B_TOP_SCANLINE_F2", media_display_flags::B_TOP_SCANLINE_F2, "")
.export_values();

py::enum_<media_format_flags>(m, "media_format_flags", "")
.value("B_MEDIA_RETAINED_DATA", media_format_flags::B_MEDIA_RETAINED_DATA, "")
.value("B_MEDIA_MULTIPLE_BUFFERS", media_format_flags::B_MEDIA_MULTIPLE_BUFFERS, "")
.value("B_MEDIA_CONTIGUOUS_BUFFER", media_format_flags::B_MEDIA_CONTIGUOUS_BUFFER, "")
.value("B_MEDIA_LINEAR_UPDATES", media_format_flags::B_MEDIA_LINEAR_UPDATES, "")
.value("B_MEDIA_MAUI_UNDEFINED_FLAGS", media_format_flags::B_MEDIA_MAUI_UNDEFINED_FLAGS, "")
.export_values();

py::enum_<media_format_family>(m, "media_format_family", "")
.value("B_ANY_FORMAT_FAMILY", media_format_family::B_ANY_FORMAT_FAMILY, "")
.value("B_BEOS_FORMAT_FAMILY", media_format_family::B_BEOS_FORMAT_FAMILY, "")
.value("B_QUICKTIME_FORMAT_FAMILY", media_format_family::B_QUICKTIME_FORMAT_FAMILY, "")
.value("B_AVI_FORMAT_FAMILY", media_format_family::B_AVI_FORMAT_FAMILY, "")
.value("B_ASF_FORMAT_FAMILY", media_format_family::B_ASF_FORMAT_FAMILY, "")
.value("B_MPEG_FORMAT_FAMILY", media_format_family::B_MPEG_FORMAT_FAMILY, "")
.value("B_WAV_FORMAT_FAMILY", media_format_family::B_WAV_FORMAT_FAMILY, "")
.value("B_AIFF_FORMAT_FAMILY", media_format_family::B_AIFF_FORMAT_FAMILY, "")
.value("B_AVR_FORMAT_FAMILY", media_format_family::B_AVR_FORMAT_FAMILY, "")
.value("B_MISC_FORMAT_FAMILY", media_format_family::B_MISC_FORMAT_FAMILY, "")
.export_values();

m.attr("B_BIG_ENDIAN") = 0;//py::cast(B_BIG_ENDIAN);
m.attr("B_LITTLE_ENDIAN") = 1;//py::cast(B_LITTLE_ENDIAN);

m.attr("B_UNDEFINED_SAMPLES") = 0;//py::cast(B_UNDEFINED_SAMPLES);
m.attr("B_LINEAR_SAMPLES") = 1;//py::cast(B_LINEAR_SAMPLES);
m.attr("B_FLOAT_SAMPLES") = 2;//py::cast(B_FLOAT_SAMPLES);
m.attr("B_MULAW_SAMPLES") = 3;//py::cast(B_MULAW_SAMPLES);

m.attr("B_CODEC_TYPE_INFO") = 0x040807b2;//py::cast(B_CODEC_TYPE_INFO); from haiku source kits/media/MediaDefs.cpp

m.attr("B_MEDIA_MESSAGE_SIZE") = 16384;//py::cast(B_MEDIA_MESSAGE_SIZE);

m.attr("B_MEDIA_SERVER_SIGNATURE") = "application/x-vnd.Be.media-server";//py::cast(B_MEDIA_SERVER_SIGNATURE);

py::class_<media_destination>(m, "media_destination")
.def(py::init(), "")
.def(py::init<port_id, int32>(), "", py::arg(""), py::arg(""))
.def(py::init<const media_destination &>(), "", py::arg("other"))
.def("__copy__", &media_destination::operator=, "", py::arg("other"))
.def_readwrite("port", &media_destination::port, "")
.def_readwrite("id", &media_destination::id, "")
//.def_readwrite("null", &media_destination::null, "")
;

py::class_<media_source>(m, "media_source")
.def(py::init(), "")
.def(py::init<port_id, int>(), "", py::arg(""), py::arg(""))
.def(py::init<const media_source &>(), "", py::arg("other"))
.def("__copy__", &media_source::operator=, "", py::arg("other"))
.def_readwrite("port", &media_source::port, "")
.def_readwrite("id", &media_source::id, "")
//.def_readwrite("null", &media_source::null, "")
;

py::class_<media_raw_audio_format>(m, "media_raw_audio_format")
.def_readwrite("frame_rate", &media_raw_audio_format::frame_rate, "")
.def_readwrite("channel_count", &media_raw_audio_format::channel_count, "")
.def_readwrite("format", &media_raw_audio_format::format, "")
.def_readwrite("byte_order", &media_raw_audio_format::byte_order, "")
.def_readwrite("buffer_size", &media_raw_audio_format::buffer_size, "")
//.def_readwrite("wildcard", &media_raw_audio_format::wildcard, "")
.def_static("wildcard", []() { return media_raw_audio_format::wildcard; })
;

py::class_<media_audio_header>(m, "media_audio_header")
//.def_readwrite("_reserved_", &media_audio_header::_reserved_, "")
.def_property(
            "_reserved_",
            [](const media_audio_header &header) {
                py::array_t<int32> result(14);
                std::memcpy(result.mutable_data(), &header._reserved_, sizeof(header._reserved_));
                return result;
            },
            [](media_audio_header &header, py::array_t<int32> value) {
                if (value.size() != 14) {
                    throw std::runtime_error("Array must have size 14");
                }
                std::memcpy(&header._reserved_, value.data(), sizeof(header._reserved_));
            },"")
.def_readwrite("frame_rate", &media_audio_header::frame_rate, "")
.def_readwrite("channel_count", &media_audio_header::channel_count, "")
;

py::class_<media_multi_audio_info>(m, "media_multi_audio_info")
.def_readwrite("channel_mask", &media_multi_audio_info::channel_mask, "")
.def_readwrite("valid_bits", &media_multi_audio_info::valid_bits, "")
.def_readwrite("matrix_mask", &media_multi_audio_info::matrix_mask, "")
//.def_readwrite("_reserved_b", &media_multi_audio_info::_reserved_b, "")
.def_property(
            "_reserved_b",
            [](const media_multi_audio_info &info) {
                py::array_t<uint32> result(3);
                std::memcpy(result.mutable_data(), &info._reserved_b, sizeof(info._reserved_b));
                return result;
            },
            [](media_multi_audio_info &info, py::array_t<uint32> value) {
                if (value.size() != 3) {
                    throw std::runtime_error("Array must have size 3");
                }
                std::memcpy(&info._reserved_b, value.data(), sizeof(info._reserved_b));
            },"")
;

py::class_<media_multi_audio_format, media_raw_audio_format, media_multi_audio_info>(m, "media_multi_audio_format")
//.def_readwrite("wildcard", &media_multi_audio_format::wildcard, "")
.def_static("wildcard", []() { return media_multi_audio_format::wildcard; })
;

py::class_<media_encoded_audio_format>(m, "media_encoded_audio_format")
.def_readwrite("output", &media_encoded_audio_format::output, "")
.def_readwrite("encoding", &media_encoded_audio_format::encoding, "")
.def_readwrite("bit_rate", &media_encoded_audio_format::bit_rate, "")
.def_readwrite("frame_size", &media_encoded_audio_format::frame_size, "")
.def_readwrite("multi_info", &media_encoded_audio_format::multi_info, "")
//.def_readwrite("_reserved_", &media_encoded_audio_format::_reserved_, "")
.def_property(
            "_reserved_",
            [](const media_encoded_audio_format &format) {
                py::array_t<uint32> result(3);
                std::memcpy(result.mutable_data(), &format._reserved_, sizeof(format._reserved_));
                return result;
            },
            [](media_encoded_audio_format &format, py::array_t<uint32> value) {
                if (value.size() != 3) {
                    throw std::runtime_error("Array must have size 3");
                }
                std::memcpy(&format._reserved_, value.data(), sizeof(format._reserved_));
            },"")
//.def_readwrite("wildcard", &media_encoded_audio_format::wildcard, "")
.def_static("wildcard", []() { return media_encoded_audio_format::wildcard; })
;

py::class_<media_encoded_audio_header>(m, "media_encoded_audio_header")
//.def_readwrite("_reserved_0", &media_encoded_audio_header::_reserved_0, "")
.def_property(
            "_reserved_0",
            [](const media_encoded_audio_header &header) {
                py::array_t<int32> result(14);
                std::memcpy(result.mutable_data(), &header._reserved_0, sizeof(header._reserved_0));
                return result;
            },
            [](media_encoded_audio_header &header, py::array_t<int32> value) {
                if (value.size() != 14) {
                    throw std::runtime_error("Array must have size 14");
                }
                std::memcpy(&header._reserved_0, value.data(), sizeof(header._reserved_0));
            },"")
.def_readwrite("buffer_flags", &media_encoded_audio_header::buffer_flags, "")
.def_readwrite("unused_mask", &media_encoded_audio_header::unused_mask, "")
//.def_readwrite("_reserved_2", &media_encoded_audio_header::_reserved_2, "")
.def_property(
            "_reserved_2",
            [](const media_encoded_audio_header &header) {
                py::array_t<uchar> result(2);
                std::memcpy(result.mutable_data(), &header._reserved_2, sizeof(header._reserved_2));
                return result;
            },
            [](media_encoded_audio_header &header, py::array_t<uchar> value) {
                if (value.size() != 2) {
                    throw std::runtime_error("Array must have size 2");
                }
                std::memcpy(&header._reserved_2, value.data(), sizeof(header._reserved_2));
            },"")
;

py::class_<media_video_display_info>(m, "media_video_display_info")
.def_readwrite("format", &media_video_display_info::format, "")
.def_readwrite("line_width", &media_video_display_info::line_width, "")
.def_readwrite("line_count", &media_video_display_info::line_count, "")
.def_readwrite("bytes_per_row", &media_video_display_info::bytes_per_row, "")
.def_readwrite("pixel_offset", &media_video_display_info::pixel_offset, "")
.def_readwrite("line_offset", &media_video_display_info::line_offset, "")
.def_readwrite("flags", &media_video_display_info::flags, "")
//.def_readwrite("_reserved_", &media_video_display_info::_reserved_, "")
.def_property(
            "_reserved_",
            [](const media_video_display_info &info) {
                py::array_t<uint32> result(3);
                std::memcpy(result.mutable_data(), &info._reserved_, sizeof(info._reserved_));
                return result;
            },
            [](media_video_display_info &info, py::array_t<uint32> value) {
                if (value.size() != 3) {
                    throw std::runtime_error("Array must have size 3");
                }
                std::memcpy(&info._reserved_, value.data(), sizeof(info._reserved_));
            },"")
//.def_readwrite("wildcard", &media_video_display_info::wildcard, "")
.def_static("wildcard", []() { return media_video_display_info::wildcard; })
;

py::class_<media_raw_video_format>(m, "media_raw_video_format")
.def_readwrite("field_rate", &media_raw_video_format::field_rate, "")
.def_readwrite("interlace", &media_raw_video_format::interlace, "")
.def_readwrite("first_active", &media_raw_video_format::first_active, "")
.def_readwrite("last_active", &media_raw_video_format::last_active, "")
.def_readwrite("orientation", &media_raw_video_format::orientation, "")
.def_readwrite("pixel_width_aspect", &media_raw_video_format::pixel_width_aspect, "")
.def_readwrite("pixel_height_aspect", &media_raw_video_format::pixel_height_aspect, "")
.def_readwrite("display", &media_raw_video_format::display, "")
//.def_readwrite("wildcard", &media_raw_video_format::wildcard, "")
.def_static("wildcard", []() { return media_raw_video_format::wildcard; })
;

py::class_<media_video_header>(m, "media_video_header")
//.def_readwrite("_reserved_", &media_video_header::_reserved_, "")
.def_property(
            "_reserved_",
            [](const media_video_header &header) {
                py::array_t<uint32> result(8);
                std::memcpy(result.mutable_data(), &header._reserved_, sizeof(header._reserved_));
                return result;
            },
            [](media_video_header &header, py::array_t<uint32> value) {
                if (value.size() != 8) {
                    throw std::runtime_error("Array must have size 8");
                }
                std::memcpy(&header._reserved_, value.data(), sizeof(header._reserved_));
            },"")
.def_readwrite("display_line_width", &media_video_header::display_line_width, "")
.def_readwrite("display_line_count", &media_video_header::display_line_count, "")
.def_readwrite("bytes_per_row", &media_video_header::bytes_per_row, "")
.def_readwrite("pixel_width_aspect", &media_video_header::pixel_width_aspect, "")
.def_readwrite("pixel_height_aspect", &media_video_header::pixel_height_aspect, "")
.def_readwrite("field_gamma", &media_video_header::field_gamma, "")
.def_readwrite("field_sequence", &media_video_header::field_sequence, "")
.def_readwrite("field_number", &media_video_header::field_number, "")
.def_readwrite("pulldown_number", &media_video_header::pulldown_number, "")
.def_readwrite("first_active_line", &media_video_header::first_active_line, "")
.def_readwrite("line_count", &media_video_header::line_count, "")
;

py::class_<media_encoded_video_format>(m, "media_encoded_video_format")
.def_readwrite("output", &media_encoded_video_format::output, "")
.def_readwrite("avg_bit_rate", &media_encoded_video_format::avg_bit_rate, "")
.def_readwrite("max_bit_rate", &media_encoded_video_format::max_bit_rate, "")
.def_readwrite("encoding", &media_encoded_video_format::encoding, "")
.def_readwrite("frame_size", &media_encoded_video_format::frame_size, "")
.def_readwrite("forward_history", &media_encoded_video_format::forward_history, "")
.def_readwrite("backward_history", &media_encoded_video_format::backward_history, "")
//.def_readwrite("_reserved_", &media_encoded_video_format::_reserved_, "")
.def_property(
            "_reserved_",
            [](const media_encoded_video_format &format) {
                py::array_t<uint32> result(3);
                std::memcpy(result.mutable_data(), &format._reserved_, sizeof(format._reserved_));
                return result;
            },
            [](media_encoded_video_format &format, py::array_t<uint32> value) {
                if (value.size() != 3) {
                    throw std::runtime_error("Array must have size 3");
                }
                std::memcpy(&format._reserved_, value.data(), sizeof(format._reserved_));
            },"")
//.def_readwrite("wildcard", &media_encoded_video_format::wildcard, "")
.def_static("wildcard", []() { return media_encoded_video_format::wildcard; })
;

py::class_<media_encoded_video_header>(m, "media_encoded_video_header")
//.def_readwrite("_reserved_1", &media_encoded_video_header::_reserved_1, "")
.def_property(
            "_reserved_1",
            [](const media_encoded_video_header &header) {
                py::array_t<int32> result(9);
                std::memcpy(result.mutable_data(), &header._reserved_1, sizeof(header._reserved_1));
                return result;
            },
            [](media_encoded_video_header &header, py::array_t<int32> value) {
                if (value.size() != 9) {
                    throw std::runtime_error("Array must have size 9");
                }
                std::memcpy(&header._reserved_1, value.data(), sizeof(header._reserved_1));
            },"")
.def_readwrite("field_flags", &media_encoded_video_header::field_flags, "")
.def_readwrite("forward_history", &media_encoded_video_header::forward_history, "")
.def_readwrite("backward_history", &media_encoded_video_header::backward_history, "")
.def_readwrite("unused_mask", &media_encoded_video_header::unused_mask, "")
//.def_readwrite("_reserved_2", &media_encoded_video_header::_reserved_2, "")
.def_property(
            "_reserved_2",
            [](const media_encoded_video_header &header) {
                py::array_t<uchar> result(3);
                std::memcpy(result.mutable_data(), &header._reserved_2, sizeof(header._reserved_2));
                return result;
            },
            [](media_encoded_video_header &header, py::array_t<uchar> value) {
                if (value.size() != 3) {
                    throw std::runtime_error("Array must have size 3");
                }
                std::memcpy(&header._reserved_2, value.data(), sizeof(header._reserved_2));
            },"")
.def_readwrite("field_gamma", &media_encoded_video_header::field_gamma, "")
.def_readwrite("field_sequence", &media_encoded_video_header::field_sequence, "")
.def_readwrite("field_number", &media_encoded_video_header::field_number, "")
.def_readwrite("pulldown_number", &media_encoded_video_header::pulldown_number, "")
.def_readwrite("first_active_line", &media_encoded_video_header::first_active_line, "")
.def_readwrite("line_count", &media_encoded_video_header::line_count, "")
;

py::class_<media_multistream_format>(m, "media_multistream_format")
.def_readwrite("avg_bit_rate", &media_multistream_format::avg_bit_rate, "")
.def_readwrite("max_bit_rate", &media_multistream_format::max_bit_rate, "")
.def_readwrite("avg_chunk_size", &media_multistream_format::avg_chunk_size, "")
.def_readwrite("max_chunk_size", &media_multistream_format::max_chunk_size, "")
.def_readwrite("flags", &media_multistream_format::flags, "")
.def_readwrite("format", &media_multistream_format::format, "")
//.def_readwrite("_reserved_", &media_multistream_format::_reserved_, "")
.def_property(
            "_reserved_",
            [](const media_multistream_format &format) {
                py::array_t<uint32> result(2);
                std::memcpy(result.mutable_data(), &format._reserved_, sizeof(format._reserved_));
                return result;
            },
            [](media_multistream_format &format, py::array_t<uint32> value) {
                if (value.size() != 2) {
                    throw std::runtime_error("Array must have size 2");
                }
                std::memcpy(&format._reserved_, value.data(), sizeof(format._reserved_));
            },"")
.def_readwrite("u", &media_multistream_format::u, "")
//.def_readwrite("wildcard", &media_multistream_format::wildcard, "")
.def_static("wildcard", []() { return media_multistream_format::wildcard; })
;

py::class_<media_multistream_format::vid_info>(m, "vid_info")
.def_readwrite("frame_rate", &media_multistream_format::vid_info::frame_rate, "")
.def_readwrite("width", &media_multistream_format::vid_info::width, "")
.def_readwrite("height", &media_multistream_format::vid_info::height, "")
.def_readwrite("space", &media_multistream_format::vid_info::space, "")
.def_readwrite("sampling_rate", &media_multistream_format::vid_info::sampling_rate, "")
.def_readwrite("sample_format", &media_multistream_format::vid_info::sample_format, "")
.def_readwrite("byte_order", &media_multistream_format::vid_info::byte_order, "")
.def_readwrite("channel_count", &media_multistream_format::vid_info::channel_count, "")
;

py::class_<media_multistream_format::avi_info>(m, "avi_info")
.def_readwrite("us_per_frame", &media_multistream_format::avi_info::us_per_frame, "")
.def_readwrite("width", &media_multistream_format::avi_info::width, "")
.def_readwrite("height", &media_multistream_format::avi_info::height, "")
.def_readwrite("_reserved_", &media_multistream_format::avi_info::_reserved_, "")
.def_readwrite("type_count", &media_multistream_format::avi_info::type_count, "")
//.def_readwrite("types", &media_multistream_format::avi_info::types, "")
.def_property(
            "types",
            [](const media_multistream_format::avi_info &format) {
                py::array_t<media_type> result(5);
                std::memcpy(result.mutable_data(), &format.types, sizeof(format.types));
                return result;
            },
            [](media_multistream_format::avi_info &format, py::array_t<media_type> value) {
                if (value.size() != 5) {
                    throw std::runtime_error("Array must have size 5");
                }
                std::memcpy(&format.types, value.data(), sizeof(format.types));
            },"")
;

/*py::class_<union >(m, "union ")
.def_readwrite("vid", &union ::vid, "")
.def_readwrite("avi", &union ::avi, "")
;*/

py::class_<media_multistream_header>(m, "media_multistream_header")
//.def_readwrite("_reserved_", &media_multistream_header::_reserved_, "")
.def_property(
            "_reserved_",
            [](const media_multistream_header &header) {
                py::array_t<uint32> result(14);
                std::memcpy(result.mutable_data(), &header._reserved_, sizeof(header._reserved_));
                return result;
            },
            [](media_multistream_header &header, py::array_t<uint32> value) {
                if (value.size() != 14) {
                    throw std::runtime_error("Array must have size 14");
                }
                std::memcpy(&header._reserved_, value.data(), sizeof(header._reserved_));
            },"")
.def_readwrite("unused_mask", &media_multistream_header::unused_mask, "")
//.def_readwrite("_reserved_2", &media_multistream_header::_reserved_2, "")
.def_property(
            "_reserved_2",
            [](const media_multistream_header &header) {
                py::array_t<uchar> result(3);
                std::memcpy(result.mutable_data(), &header._reserved_2, sizeof(header._reserved_2));
                return result;
            },
            [](media_multistream_header &header, py::array_t<uchar> value) {
                if (value.size() != 3) {
                    throw std::runtime_error("Array must have size 3");
                }
                std::memcpy(&header._reserved_2, value.data(), sizeof(header._reserved_2));
            },"")
.def_readwrite("flags", &media_multistream_header::flags, "")
;

py::class_<media_format>(m, "media_format")
.def("IsVideo", &media_format::IsVideo, "")
.def("Width", py::overload_cast<>(&media_format::Width), "")
.def("Height", py::overload_cast<>(&media_format::Height), "")
.def("ColorSpace", py::overload_cast<>(&media_format::ColorSpace), "")
.def("Width", py::overload_cast<>(&media_format::Width), "")
.def("Height", py::overload_cast<>(&media_format::Height), "")
.def("ColorSpace", py::overload_cast<>(&media_format::ColorSpace), "")
.def("IsAudio", &media_format::IsAudio, "")
.def("AudioFormat", py::overload_cast<>(&media_format::AudioFormat), "")
.def("AudioFormat", py::overload_cast<>(&media_format::AudioFormat), "")
.def("AudioFrameSize", &media_format::AudioFrameSize, "")
.def("Encoding", &media_format::Encoding, "")
.def("Matches", &media_format::Matches, "", py::arg("other"))
.def("SpecializeTo", &media_format::SpecializeTo, "", py::arg("other"))
.def("SetMetaData", &media_format::SetMetaData, "", py::arg("data"), py::arg("size"))
.def("MetaData", &media_format::MetaData, "")
.def("MetaDataSize", &media_format::MetaDataSize, "")
.def("Unflatten", &media_format::Unflatten, "", py::arg("flatBuffer"))
.def("Clear", &media_format::Clear, "")
.def(py::init(), "")
.def(py::init<const media_format &>(), "", py::arg("other"))
.def("__copy__", &media_format::operator=, "", py::arg("other"))
.def_readwrite("type", &media_format::type, "")
.def_readwrite("user_data_type", &media_format::user_data_type, "")
//.def_readwrite("user_data", &media_format::user_data, "")
.def_property(
            "user_data",
            [](const media_format &format) {
                py::array_t<uchar> result(48);
                std::memcpy(result.mutable_data(), &format.user_data, sizeof(format.user_data));
                return result;
            },
            [](media_format &format, py::array_t<uchar> value) {
                if (value.size() != 48) {
                    throw std::runtime_error("Array must have size 48");
                }
                std::memcpy(&format.user_data, value.data(), sizeof(format.user_data));
            },"")
//.def_readwrite("_reserved_", &media_format::_reserved_, "")
.def_property(
            "_reserved_",
            [](const media_format &format) {
                py::array_t<uint32> result(3);
                std::memcpy(result.mutable_data(), &format._reserved_, sizeof(format._reserved_));
                return result;
            },
            [](media_format &format, py::array_t<uint32> value) {
                if (value.size() != 3) {
                    throw std::runtime_error("Array must have size 3");
                }
                std::memcpy(&format._reserved_, value.data(), sizeof(format._reserved_));
            },"")
.def_readwrite("require_flags", &media_format::require_flags, "")
.def_readwrite("deny_flags", &media_format::deny_flags, "")
.def_readwrite("u", &media_format::u, "")
;
/*
py::class_<union >(m, "union ")
.def_readwrite("raw_audio", &union ::raw_audio, "")
.def_readwrite("raw_video", &union ::raw_video, "")
.def_readwrite("multistream", &union ::multistream, "")
.def_readwrite("encoded_audio", &union ::encoded_audio, "")
.def_readwrite("encoded_video", &union ::encoded_video, "")
.def_readwrite("_reserved_", &union ::_reserved_, "")
;*/

py::class_<media_seek_tag>(m, "media_seek_tag")
//.def_readwrite("data", &media_seek_tag::data, "")
.def_property(
            "data",
            [](const media_seek_tag &tag) {
                py::array_t<char> result(16);
                std::memcpy(result.mutable_data(), &tag.data, sizeof(tag.data));
                return result;
            },
            [](media_seek_tag &tag, py::array_t<char> value) {
                if (value.size() != 16) {
                    throw std::runtime_error("Array must have size 16");
                }
                std::memcpy(&tag.data, value.data(), sizeof(tag.data));
            },"")
;

py::class_<media_header_time_code>(m, "media_header_time_code")
.def_readwrite("type", &media_header_time_code::type, "")
.def_readwrite("_reserved", &media_header_time_code::_reserved, "")
.def_readwrite("hours", &media_header_time_code::hours, "")
.def_readwrite("minutes", &media_header_time_code::minutes, "")
.def_readwrite("seconds", &media_header_time_code::seconds, "")
.def_readwrite("frames", &media_header_time_code::frames, "")
.def_readwrite("subframes", &media_header_time_code::subframes, "")
;

py::class_<media_header>(m, "media_header")
.def_readwrite("type", &media_header::type, "")
.def_readwrite("buffer", &media_header::buffer, "")
.def_readwrite("destination", &media_header::destination, "")
.def_readwrite("time_source", &media_header::time_source, "")
.def_readwrite("_deprecated_", &media_header::_deprecated_, "")
.def_readwrite("size_used", &media_header::size_used, "")
.def_readwrite("start_time", &media_header::start_time, "")
.def_readwrite("owner", &media_header::owner, "")
.def_readwrite("user_data_type", &media_header::user_data_type, "")
//.def_readwrite("user_data", &media_header::user_data, "")
.def_property(
            "user_data",
            [](const media_header &header) {
                py::array_t<uchar> result(64);
                std::memcpy(result.mutable_data(), &header.user_data, sizeof(header.user_data));
                return result;
            },
            [](media_header &header, py::array_t<uchar> value) {
                if (value.size() != 64) {
                    throw std::runtime_error("Array must have size 64");
                }
                std::memcpy(&header.user_data, value.data(), sizeof(header.user_data));
            },"")
.def_readwrite("source", &media_header::source, "")
.def_readwrite("source_port", &media_header::source_port, "")
.def_readwrite("file_pos", &media_header::file_pos, "")
.def_readwrite("orig_size", &media_header::orig_size, "")
.def_readwrite("data_offset", &media_header::data_offset, "")
.def_readwrite("u", &media_header::u, "")
;
/*
py::class_<union >(m, "union ")
.def_readwrite("raw_audio", &union ::raw_audio, "")
.def_readwrite("raw_video", &union ::raw_video, "")
.def_readwrite("multistream", &union ::multistream, "")
.def_readwrite("encoded_audio", &union ::encoded_audio, "")
.def_readwrite("encoded_video", &union ::encoded_video, "")
.def_readwrite("_reserved_", &union ::_reserved_, "")
;*/

py::class_<media_file_format_id>(m, "media_file_format_id")
.def_readwrite("node", &media_file_format_id::node, "")
.def_readwrite("device", &media_file_format_id::device, "")
.def_readwrite("internal_id", &media_file_format_id::internal_id, "")
;

py::class_<media_file_format>(m, "media_file_format")
/*
		B_READABLE				= 0x1,
		B_WRITABLE				= 0x2,
		B_PERFECTLY_SEEKABLE	= 0x4,
		B_IMPERFECTLY_SEEKABLE	= 0x8,
		B_KNOWS_RAW_VIDEO		= 0x10,
		B_KNOWS_RAW_AUDIO		= 0x20,
		B_KNOWS_MIDI			= 0x40,
		B_KNOWS_ENCODED_VIDEO	= 0x80,
		B_KNOWS_ENCODED_AUDIO	= 0x100,
		B_KNOWS_OTHER			= 0x1000000, // For example sub-title streams
		B_KNOWS_ANYTHING		= 0x2000000
		*/
.def_readwrite("capabilities", &media_file_format::capabilities, "")
.def_readwrite("id", &media_file_format::id, "")
.def_readwrite("family", &media_file_format::family, "")
.def_readwrite("version", &media_file_format::version, "")
//.def_readwrite("_reserved_", &media_file_format::_reserved_, "")
.def_property(
            "_reserved_",
            [](const media_file_format &format) {
                py::array_t<uint32> result(25);
                std::memcpy(result.mutable_data(), &format._reserved_, sizeof(format._reserved_));
                return result;
            },
            [](media_file_format &format, py::array_t<uint32> value) {
                if (value.size() != 25) {
                    throw std::runtime_error("Array must have size 25");
                }
                std::memcpy(&format._reserved_, value.data(), sizeof(format._reserved_));
            },"")
//.def_readwrite("mime_type", &media_file_format::mime_type, "")
.def_property(
            "mime_type",
            [](const media_file_format &format) {
                py::array_t<char> result(64);
                std::memcpy(result.mutable_data(), &format.mime_type, sizeof(format.mime_type));
                return result;
            },
            [](media_file_format &format, py::array_t<char> value) {
                if (value.size() != 64) {
                    throw std::runtime_error("Array must have size 64");
                }
                std::memcpy(&format.mime_type, value.data(), sizeof(format.mime_type));
            },"")
//.def_readwrite("pretty_name", &media_file_format::pretty_name, "")
.def_property(
            "pretty_name",
            [](const media_file_format &format) {
                py::array_t<char> result(64);
                std::memcpy(result.mutable_data(), &format.pretty_name, sizeof(format.pretty_name));
                return result;
            },
            [](media_file_format &format, py::array_t<char> value) {
                if (value.size() != 64) {
                    throw std::runtime_error("Array must have size 64");
                }
                std::memcpy(&format.pretty_name, value.data(), sizeof(format.pretty_name));
            },"")
//.def_readwrite("short_name", &media_file_format::short_name, "")
.def_property(
            "short_name",
            [](const media_file_format &format) {
                py::array_t<char> result(32);
                std::memcpy(result.mutable_data(), &format.short_name, sizeof(format.short_name));
                return result;
            },
            [](media_file_format &format, py::array_t<char> value) {
                if (value.size() != 32) {
                    throw std::runtime_error("Array must have size 32");
                }
                std::memcpy(&format.short_name, value.data(), sizeof(format.short_name));
            },"")
//.def_readwrite("file_extension", &media_file_format::file_extension, "")
.def_property(
            "file_extension",
            [](const media_file_format &format) {
                py::array_t<char> result(8);
                std::memcpy(result.mutable_data(), &format.file_extension, sizeof(format.file_extension));
                return result;
            },
            [](media_file_format &format, py::array_t<char> value) {
                if (value.size() != 8) {
                    throw std::runtime_error("Array must have size 8");
                }
                std::memcpy(&format.file_extension, value.data(), sizeof(format.file_extension));
            },"")
//.def_readwrite("reserved", &media_file_format::reserved, "")
.def_property(
            "reserved",
            [](const media_file_format &format) {
                py::array_t<char> result(88);
                std::memcpy(result.mutable_data(), &format.reserved, sizeof(format.reserved));
                return result;
            },
            [](media_file_format &format, py::array_t<char> value) {
                if (value.size() != 88) {
                    throw std::runtime_error("Array must have size 88");
                }
                std::memcpy(&format.reserved, value.data(), sizeof(format.reserved));
            },"")
;

py::class_<media_encode_info>(m, "media_encode_info")
.def(py::init(), "")
.def_readwrite("flags", &media_encode_info::flags, "")
.def_readwrite("used_data_size", &media_encode_info::used_data_size, "")
.def_readwrite("start_time", &media_encode_info::start_time, "")
.def_readwrite("time_to_encode", &media_encode_info::time_to_encode, "")
//.def_readwrite("_pad", &media_encode_info::_pad, "")
.def_property(
            "_pad",
            [](const media_encode_info &info) {
                py::array_t<int32> result(22);
                std::memcpy(result.mutable_data(), &info._pad, sizeof(info._pad));
                return result;
            },
            [](media_encode_info &info, py::array_t<int32> value) {
                if (value.size() != 22) {
                    throw std::runtime_error("Array must have size 22");
                }
                std::memcpy(&info._pad, value.data(), sizeof(info._pad));
            },"")
.def_readwrite("file_format_data", &media_encode_info::file_format_data, "")
.def_readwrite("file_format_data_size", &media_encode_info::file_format_data_size, "")
.def_readwrite("codec_data", &media_encode_info::codec_data, "")
.def_readwrite("codec_data_size", &media_encode_info::codec_data_size, "")
;

py::class_<encode_parameters>(m, "encode_parameters")
.def_readwrite("quality", &encode_parameters::quality, "")
.def_readwrite("avg_field_size", &encode_parameters::avg_field_size, "")
.def_readwrite("max_field_size", &encode_parameters::max_field_size, "")
//.def_readwrite("_pad", &encode_parameters::_pad, "")
.def_property(
            "_pad",
            [](const encode_parameters &parameters) {
                py::array_t<int32> result(27);
                std::memcpy(result.mutable_data(), &parameters._pad, sizeof(parameters._pad));
                return result;
            },
            [](encode_parameters &parameters, py::array_t<int32> value) {
                if (value.size() != 27) {
                    throw std::runtime_error("Array must have size 27");
                }
                std::memcpy(&parameters._pad, value.data(), sizeof(parameters._pad));
            },"")
.def_readwrite("user_data", &encode_parameters::user_data, "")
.def_readwrite("user_data_size", &encode_parameters::user_data_size, "")
;

py::class_<media_decode_info>(m, "media_decode_info")
.def(py::init(), "")
.def_readwrite("time_to_decode", &media_decode_info::time_to_decode, "")
//.def_readwrite("_pad", &media_decode_info::_pad, "")
.def_property(
            "_pad",
            [](const media_decode_info &info) {
                py::array_t<int32> result(26);
                std::memcpy(result.mutable_data(), &info._pad, sizeof(info._pad));
                return result;
            },
            [](media_decode_info &info, py::array_t<int32> value) {
                if (value.size() != 26) {
                    throw std::runtime_error("Array must have size 26");
                }
                std::memcpy(&info._pad, value.data(), sizeof(info._pad));
            },"")
.def_readwrite("file_format_data", &media_decode_info::file_format_data, "")
.def_readwrite("file_format_data_size", &media_decode_info::file_format_data_size, "")
.def_readwrite("codec_data", &media_decode_info::codec_data, "")
.def_readwrite("codec_data_size", &media_decode_info::codec_data_size, "")
;

m.def("__eq__", py::overload_cast<const media_destination &, const media_destination &>(&operator==), "", py::arg("a"), py::arg("b"));

m.def("__ne__", py::overload_cast<const media_destination &, const media_destination &>(&operator!=), "", py::arg("a"), py::arg("b"));

m.def("__lt__", py::overload_cast<const media_destination &, const media_destination &>(&operator<), "", py::arg("a"), py::arg("b"));

m.def("__eq__", py::overload_cast<const media_source &, const media_source &>(&operator==), "", py::arg("a"), py::arg("b"));

m.def("__ne__", py::overload_cast<const media_source &, const media_source &>(&operator!=), "", py::arg("a"), py::arg("b"));

m.def("__lt__", py::overload_cast<const media_source &, const media_source &>(&operator<), "", py::arg("a"), py::arg("b"));

m.def("__eq__", py::overload_cast<const media_node &, const media_node &>(&operator==), "", py::arg("a"), py::arg("b"));

m.def("__ne__", py::overload_cast<const media_node &, const media_node &>(&operator!=), "", py::arg("a"), py::arg("b"));

m.def("__lt__", py::overload_cast<const media_node &, const media_node &>(&operator<), "", py::arg("a"), py::arg("b"));

m.def("__eq__", py::overload_cast<const media_raw_audio_format &, const media_raw_audio_format &>(&operator==), "", py::arg("a"), py::arg("b"));

m.def("__eq__", py::overload_cast<const media_multi_audio_info &, const media_multi_audio_info &>(&operator==), "", py::arg("a"), py::arg("b"));

m.def("__eq__", py::overload_cast<const media_multi_audio_format &, const media_multi_audio_format &>(&operator==), "", py::arg("a"), py::arg("b"));

m.def("__eq__", py::overload_cast<const media_encoded_audio_format &, const media_encoded_audio_format &>(&operator==), "", py::arg("a"), py::arg("b"));

m.def("__eq__", py::overload_cast<const media_video_display_info &, const media_video_display_info &>(&operator==), "", py::arg("a"), py::arg("b"));

m.def("__eq__", py::overload_cast<const media_raw_video_format &, const media_raw_video_format &>(&operator==), "", py::arg("a"), py::arg("b"));

m.def("__eq__", py::overload_cast<const media_encoded_video_format &, const media_encoded_video_format &>(&operator==), "", py::arg("a"), py::arg("b"));

m.def("__eq__", py::overload_cast<const media_multistream_format::vid_info &, const media_multistream_format::vid_info &>(&operator==), "", py::arg("a"), py::arg("b"));

m.def("__eq__", py::overload_cast<const media_multistream_format::avi_info &, const media_multistream_format::avi_info &>(&operator==), "", py::arg("a"), py::arg("b"));

m.def("__eq__", py::overload_cast<const media_multistream_format &, const media_multistream_format &>(&operator==), "", py::arg("a"), py::arg("b"));

m.def("__eq__", py::overload_cast<const media_format &, const media_format &>(&operator==), "", py::arg("a"), py::arg("b"));

m.def("format_is_compatible", &format_is_compatible, "", py::arg("a"), py::arg("b"));

m.def("string_for_format", &string_for_format, "", py::arg("f"), py::arg("buf"), py::arg("size"));

m.def("__eq__", py::overload_cast<const media_file_format_id &, const media_file_format_id &>(&operator==), "", py::arg("a"), py::arg("b"));

m.def("__lt__", py::overload_cast<const media_file_format_id &, const media_file_format_id &>(&operator<), "", py::arg("a"), py::arg("b"));

m.def("get_next_file_format", &get_next_file_format, "", py::arg("cookie"), py::arg("mfi"));

m.def("launch_media_server", &launch_media_server, "", py::arg("timeout")=B_INFINITE_TIMEOUT, py::arg("bool(*progress)(intstage,constchar*message,void*cookie)")=NULL, py::arg("cookie")=NULL, py::arg("flags")=0);

m.def("shutdown_media_server", &shutdown_media_server, "", py::arg("timeout")=B_INFINITE_TIMEOUT, py::arg("bool(*progress)(intstage,constchar*message,void*cookie)")=NULL, py::arg("cookie")=NULL);

}
