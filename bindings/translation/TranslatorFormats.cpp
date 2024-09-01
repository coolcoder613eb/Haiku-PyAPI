#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <translation/TranslatorFormats.h>

namespace py = pybind11;

PYBIND11_MODULE(TranslatorFormats,m)
{
py::enum_<TranslatorGroups>(m, "TranslatorGroups", "")
.value("B_TRANSLATOR_BITMAP", TranslatorGroups::B_TRANSLATOR_BITMAP, "")
.value("B_TRANSLATOR_PICTURE", TranslatorGroups::B_TRANSLATOR_PICTURE, "")
.value("B_TRANSLATOR_SOUND", TranslatorGroups::B_TRANSLATOR_SOUND, "")
.value("B_TRANSLATOR_TEXT", TranslatorGroups::B_TRANSLATOR_TEXT, "")
.value("B_TRANSLATOR_MIDI", TranslatorGroups::B_TRANSLATOR_MIDI, "")
.value("B_TRANSLATOR_MEDIA", TranslatorGroups::B_TRANSLATOR_MEDIA, "")
.value("B_TRANSLATOR_NONE", TranslatorGroups::B_TRANSLATOR_NONE, "")
.value("B_TRANSLATOR_ANY_TYPE", TranslatorGroups::B_TRANSLATOR_ANY_TYPE, "")
.export_values();

m.attr("B_GIF_FORMAT") = 'GIF ';//py::cast(B_GIF_FORMAT);
m.attr("B_JPEG_FORMAT") = 'JPEG';//py::cast(B_JPEG_FORMAT);
m.attr("B_PNG_FORMAT") = 'PNG ';//py::cast(B_PNG_FORMAT);
m.attr("B_PPM_FORMAT") = 'PPM ';//py::cast(B_PPM_FORMAT);
m.attr("B_TGA_FORMAT") = 'TGA ';//py::cast(B_TGA_FORMAT);
m.attr("B_BMP_FORMAT") = 'BMP ';//py::cast(B_BMP_FORMAT);
m.attr("B_TIFF_FORMAT") = 'TIFF';//py::cast(B_TIFF_FORMAT);
m.attr("B_WEBP_FORMAT") = 'WebP';//py::cast(B_WEBP_FORMAT);
m.attr("B_DXF_FORMAT") = 'DXF ';//py::cast(B_DXF_FORMAT);
m.attr("B_EPS_FORMAT") = 'EPS ';//py::cast(B_EPS_FORMAT);
m.attr("B_PICT_FORMAT") = 'PICT';//py::cast(B_PICT_FORMAT);
m.attr("B_WAV_FORMAT") = 'WAV ';//py::cast(B_WAV_FORMAT);
m.attr("B_AIFF_FORMAT") = 'AIFF';//py::cast(B_AIFF_FORMAT);
m.attr("B_CD_FORMAT") = 'CD  ';//py::cast(B_CD_FORMAT);
m.attr("B_AU_FORMAT") = 'AU  ';//py::cast(B_AU_FORMAT);
m.attr("B_STYLED_TEXT_FORMAT") = 'STXT';//py::cast(B_STYLED_TEXT_FORMAT);


/* from TranslatorRoster.cpp in translation kit
char B_TRANSLATOR_EXT_HEADER_ONLY[]			= "/headerOnly";
char B_TRANSLATOR_EXT_DATA_ONLY[]			= "/dataOnly";
char B_TRANSLATOR_EXT_COMMENT[]				= "/comment";
char B_TRANSLATOR_EXT_TIME[]				= "/time";
char B_TRANSLATOR_EXT_FRAME[]				= "/frame";
char B_TRANSLATOR_EXT_BITMAP_RECT[]			= "bits/Rect";
char B_TRANSLATOR_EXT_BITMAP_COLOR_SPACE[]	= "bits/space";
char B_TRANSLATOR_EXT_BITMAP_PALETTE[]		= "bits/palette";
char B_TRANSLATOR_EXT_SOUND_CHANNEL[]		= "nois/channel";
char B_TRANSLATOR_EXT_SOUND_MONO[]			= "nois/mono";
char B_TRANSLATOR_EXT_SOUND_MARKER[]		= "nois/marker";
char B_TRANSLATOR_EXT_SOUND_LOOP[]			= "nois/loop";*/

m.attr("B_TRANSLATOR_EXT_HEADER_ONLY") = "/headerOnly";//py::cast(B_TRANSLATOR_EXT_HEADER_ONLY);

m.attr("B_TRANSLATOR_EXT_DATA_ONLY") = "/dataOnly";//py::cast(B_TRANSLATOR_EXT_DATA_ONLY);

m.attr("B_TRANSLATOR_EXT_COMMENT") = "/comment";//py::cast(B_TRANSLATOR_EXT_COMMENT);

m.attr("B_TRANSLATOR_EXT_TIME") = "/time";//py::cast(B_TRANSLATOR_EXT_TIME);

m.attr("B_TRANSLATOR_EXT_FRAME") = "/frame";//py::cast(B_TRANSLATOR_EXT_FRAME);

m.attr("B_TRANSLATOR_EXT_BITMAP_RECT") = "bits/Rect";//py::cast(B_TRANSLATOR_EXT_BITMAP_RECT);

m.attr("B_TRANSLATOR_EXT_BITMAP_COLOR_SPACE") = "bits/space";//py::cast(B_TRANSLATOR_EXT_BITMAP_COLOR_SPACE);

m.attr("B_TRANSLATOR_EXT_BITMAP_PALETTE") = "bits/palette";//py::cast(B_TRANSLATOR_EXT_BITMAP_PALETTE);

m.attr("B_TRANSLATOR_EXT_SOUND_CHANNEL") = "nois/channel";//py::cast(B_TRANSLATOR_EXT_SOUND_CHANNEL);

m.attr("B_TRANSLATOR_EXT_SOUND_MONO") = "nois/mono";//py::cast(B_TRANSLATOR_EXT_SOUND_MONO);

m.attr("B_TRANSLATOR_EXT_SOUND_MARKER") = "nois/marker";//py::cast(B_TRANSLATOR_EXT_SOUND_MARKER);

m.attr("B_TRANSLATOR_EXT_SOUND_LOOP") = "nois/loop";//py::cast(B_TRANSLATOR_EXT_SOUND_LOOP);

py::class_<TranslatorBitmap>(m, "TranslatorBitmap")
.def_readwrite("magic", &TranslatorBitmap::magic, "")
.def_readwrite("bounds", &TranslatorBitmap::bounds, "")
.def_readwrite("rowBytes", &TranslatorBitmap::rowBytes, "")
.def_readwrite("colors", &TranslatorBitmap::colors, "")
.def_readwrite("dataSize", &TranslatorBitmap::dataSize, "")
;

py::class_<TranslatorSound>(m, "TranslatorSound")
.def_readwrite("magic", &TranslatorSound::magic, "")
.def_readwrite("channels", &TranslatorSound::channels, "")
.def_readwrite("sampleFreq", &TranslatorSound::sampleFreq, "")
.def_readwrite("numFrames", &TranslatorSound::numFrames, "")
;

py::class_<TranslatorStyledTextRecordHeader>(m, "TranslatorStyledTextRecordHeader")
.def_readwrite("magic", &TranslatorStyledTextRecordHeader::magic, "")
.def_readwrite("header_size", &TranslatorStyledTextRecordHeader::header_size, "")
.def_readwrite("data_size", &TranslatorStyledTextRecordHeader::data_size, "")
;

py::class_<TranslatorStyledTextStreamHeader>(m, "TranslatorStyledTextStreamHeader")
.def_property_readonly("STREAM_HEADER_MAGIC", []() {
	return 'STXT';
},"")
.def_readwrite("header", &TranslatorStyledTextStreamHeader::header, "")
.def_readwrite("version", &TranslatorStyledTextStreamHeader::version, "")
;

py::class_<TranslatorStyledTextTextHeader>(m, "TranslatorStyledTextTextHeader")
.def_property_readonly("TEXT_HEADER_MAGIC", []() {
	return 'TEXT';
},"")
.def_readwrite("header", &TranslatorStyledTextTextHeader::header, "")
.def_readwrite("charset", &TranslatorStyledTextTextHeader::charset, "")
;

py::class_<TranslatorStyledTextStyleHeader>(m, "TranslatorStyledTextStyleHeader")
.def_property_readonly("STYLE_HEADER_MAGIC", []() {
	return 'STYL';
},"")
.def_readwrite("header", &TranslatorStyledTextStyleHeader::header, "")
.def_readwrite("apply_offset", &TranslatorStyledTextStyleHeader::apply_offset, "")
.def_readwrite("apply_length", &TranslatorStyledTextStyleHeader::apply_length, "")
;


}
