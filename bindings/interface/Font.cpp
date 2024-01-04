#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>
#include <pybind11/numpy.h>

#include <interface/Font.h>
#include <SupportDefs.h>
#include <InterfaceDefs.h>
#include <Point.h>
#include <Rect.h>
#include <Shape.h>

namespace py = pybind11;


PYBIND11_MODULE(Font,m)
{
m.attr("B_CHAR_SPACING") = 0;
m.attr("B_STRING_SPACING") = 1;
m.attr("B_BITMAP_SPACING") = 2;
m.attr("B_FIXED_SPACING") = 3;

py::enum_<font_direction>(m, "font_direction", "")
.value("B_FONT_LEFT_TO_RIGHT", font_direction::B_FONT_LEFT_TO_RIGHT, "")
.value("B_FONT_RIGHT_TO_LEFT", font_direction::B_FONT_RIGHT_TO_LEFT, "")
.export_values();

m.attr("B_DISABLE_ANTIALIASING") = 1;
m.attr("B_FORCE_ANTIALIASING") = 2;

m.attr("B_NO_TRUNCATION") = "~0U";
m.attr("B_TRUNCATE_END") = 0;
m.attr("B_TRUNCATE_BEGINNING") = 1;
m.attr("B_TRUNCATE_MIDDLE") = 2;
m.attr("B_TRUNCATE_SMART") = 3;

m.attr("B_UNICODE_UTF8") = 0;
m.attr("B_ISO_8859_1") = 1;
m.attr("B_ISO_8859_2") = 2;
m.attr("B_ISO_8859_3") = 3;
m.attr("B_ISO_8859_4") = 4;
m.attr("B_ISO_8859_5") = 5;
m.attr("B_ISO_8859_6") = 6;
m.attr("B_ISO_8859_7") = 7;
m.attr("B_ISO_8859_8") = 8;
m.attr("B_ISO_8859_9") = 9;
m.attr("B_ISO_8859_10") = 10;
m.attr("B_MACINTOSH_ROMAN") = 11;

m.attr("B_HAS_TUNED_FONT") = 1;
m.attr("B_IS_FIXED") = 2;

m.attr("B_ITALIC_FACE") = 1;
m.attr("B_UNDERSCORE_FACE") = 2;
m.attr("B_NEGATIVE_FACE") = 4;
m.attr("B_OUTLINED_FACE") = 8;
m.attr("B_STRIKEOUT_FACE") = 16;
m.attr("B_BOLD_FACE") = 32;
m.attr("B_REGULAR_FACE") = 64;
m.attr("B_CONDENSED_FACE") = 128;
m.attr("B_LIGHT_FACE") = 256;
m.attr("B_HEAVY_FACE") = 512;

py::enum_<font_metric_mode>(m, "font_metric_mode", "")
.value("B_SCREEN_METRIC", font_metric_mode::B_SCREEN_METRIC, "")
.value("B_PRINTING_METRIC", font_metric_mode::B_PRINTING_METRIC, "")
.export_values();

py::enum_<font_file_format>(m, "font_file_format", "")
.value("B_TRUETYPE_WINDOWS", font_file_format::B_TRUETYPE_WINDOWS, "")
.value("B_POSTSCRIPT_TYPE1_WINDOWS", font_file_format::B_POSTSCRIPT_TYPE1_WINDOWS, "")
.export_values();



py::class_<unicode_block>(m, "unicode_block")
.def(py::init(), "")
.def(py::init<uint64_t, uint64_t>(), "", py::arg("block2"), py::arg("block1"))
.def("Includes", &unicode_block::Includes, "", py::arg("block"))
.def("__and__", &unicode_block::operator&, "", py::arg("block"))
.def("__or__", &unicode_block::operator|, "", py::arg("block"))
.def("operator=", &unicode_block::operator=, "", py::arg("block"))
.def("__eq__", &unicode_block::operator==, "", py::arg("block"))
.def("__ne__", &unicode_block::operator!=, "", py::arg("block"))
;

py::class_<unicode_block_range>(m, "unicode_block_range")
.def("Count", &unicode_block_range::Count, "")
.def_readwrite("start", &unicode_block_range::start, "")
.def_readwrite("end", &unicode_block_range::end, "")
//.def_readonly("block", &unicode_block_range::block, "")
;

py::class_<edge_info>(m, "edge_info")
.def(py::init(), "")
.def_readwrite("left", &edge_info::left, "")
.def_readwrite("right", &edge_info::right, "")
;

py::class_<font_height>(m, "font_height")
.def(py::init(), "")
.def_readwrite("ascent", &font_height::ascent, "")
.def_readwrite("descent", &font_height::descent, "")
.def_readwrite("leading", &font_height::leading, "")
;

py::class_<escapement_delta>(m, "escapement_delta")
.def(py::init(), "")
.def_readwrite("nonspace", &escapement_delta::nonspace, "")
.def_readwrite("space", &escapement_delta::space, "")
;

py::class_<font_cache_info>(m, "font_cache_info")
.def(py::init(), "")
.def_readwrite("sheared_font_penalty", &font_cache_info::sheared_font_penalty, "")
.def_readwrite("rotated_font_penalty", &font_cache_info::rotated_font_penalty, "")
.def_readwrite("oversize_threshold", &font_cache_info::oversize_threshold, "")
.def_readwrite("oversize_penalty", &font_cache_info::oversize_penalty, "")
.def_readwrite("cache_size", &font_cache_info::cache_size, "")
.def_readwrite("spacing_size_threshold", &font_cache_info::spacing_size_threshold, "")
;

py::class_<tuned_font_info>(m, "tuned_font_info")
.def(py::init(), "")
.def_readwrite("size", &tuned_font_info::size, "")
.def_readwrite("shear", &tuned_font_info::shear, "")
.def_readwrite("rotation", &tuned_font_info::rotation, "")
.def_readwrite("flags", &tuned_font_info::flags, "")
.def_readwrite("face", &tuned_font_info::face, "")
;

py::class_<BFont>(m, "BFont")
.def(py::init(), "")
.def(py::init<const BFont &>(), "", py::arg("font"))
.def(py::init<const BFont *>(), "", py::arg("font"))
.def("SetFamilyAndStyle", py::overload_cast<const font_family, const font_style>(&BFont::SetFamilyAndStyle), "", py::arg("family"), py::arg("style"))
.def("SetFamilyAndStyle", py::overload_cast<uint32>(&BFont::SetFamilyAndStyle), "", py::arg("code"))
.def("SetFamilyAndFace", &BFont::SetFamilyAndFace, "", py::arg("family"), py::arg("face"))
.def("SetSize", &BFont::SetSize, "", py::arg("size"))
.def("SetShear", &BFont::SetShear, "", py::arg("shear"))
.def("SetRotation", &BFont::SetRotation, "", py::arg("rotation"))
.def("SetFalseBoldWidth", &BFont::SetFalseBoldWidth, "", py::arg("width"))
.def("SetSpacing", &BFont::SetSpacing, "", py::arg("spacing"))
.def("SetEncoding", &BFont::SetEncoding, "", py::arg("encoding"))
.def("SetFace", &BFont::SetFace, "", py::arg("face"))
.def("SetFlags", &BFont::SetFlags, "", py::arg("flags"))
//.def("GetFamilyAndStyle", &BFont::GetFamilyAndStyle, "", py::arg("family"), py::arg("style"))

.def("GetFamilyAndStyle", [](BFont &self) -> py::tuple {
    font_family family;
    font_style style;

    // Chiamata alla funzione GetFamilyAndStyle della classe BFont
    self.GetFamilyAndStyle(&family, &style);

    // Converte i dati in stringhe Python
    //std::string familyStr(family);
    //std::string styleStr(style);

    // Restituisci una tupla di stringhe
    //return std::make_tuple(familyStr, styleStr);
    return py::make_tuple(family, style);
},"")
/*
.def("GetFamilyAndStyle", [](BFont &self, std::string &family, std::string &style) -> py::tuple {
    font_family famil;
    font_style styl;

    self.GetFamilyAndStyle(&famil, &styl);

    family = std::string(famil, strnlen(famil, B_FONT_FAMILY_LENGTH));
    style = std::string(styl, strnlen(styl, B_FONT_STYLE_LENGTH));

    return py::make_tuple(family, style);
}, "", py::arg("family"), py::arg("style"))*/
.def("FamilyAndStyle", &BFont::FamilyAndStyle, "")
.def("Size", &BFont::Size, "")
.def("Shear", &BFont::Shear, "")
.def("Rotation", &BFont::Rotation, "")
.def("FalseBoldWidth", &BFont::FalseBoldWidth, "")
.def("Spacing", &BFont::Spacing, "")
.def("Encoding", &BFont::Encoding, "")
.def("Face", &BFont::Face, "")
.def("Flags", &BFont::Flags, "")
.def("Direction", &BFont::Direction, "")
.def("IsFixed", &BFont::IsFixed, "")
.def("IsFullAndHalfFixed", &BFont::IsFullAndHalfFixed, "")
.def("BoundingBox", &BFont::BoundingBox, "")
.def("Blocks", &BFont::Blocks, "")
.def("IncludesBlock", &BFont::IncludesBlock, "", py::arg("start"), py::arg("end"))
.def("FileFormat", &BFont::FileFormat, "")
.def("CountTuned", &BFont::CountTuned, "")
.def("GetTunedInfo", &BFont::GetTunedInfo, "", py::arg("index"), py::arg("info"))
.def("TruncateString", &BFont::TruncateString, "", py::arg("inOut"), py::arg("mode"), py::arg("width"))
//.def("GetTruncatedStrings", py::overload_cast<const char *, int, unsigned int, float, BString>(&BFont::GetTruncatedStrings, py::const_), "", py::arg("stringArray"), py::arg("numStrings"), py::arg("mode"), py::arg("width"), py::arg("resultArray"))
.def("GetTruncatedStrings", [](BFont& self, std::vector<const char *> stringArray, uint32 mode,float width)->std::vector<BString>{
	//BString resArray[stringArray.size()];
	std::vector<BString> resArray(stringArray.size());
	self.GetTruncatedStrings(stringArray.data(),stringArray.size(),mode,width,resArray.data());
	return resArray;
},"", py::arg("stringArray"),py::arg("mode"), py::arg("width"))
/*This below compiles but don't returns values we should return as function return value like "return resultArray;"
.def("GetTruncatedStrings", [](BFont& self, std::vector<const char *> stringArray, uint32 mode, float width, std::vector<BString>& resultArray) {
    // Chiamata alla funzione GetTruncatedStrings senza creare un array locale
    resultArray.resize(stringArray.size());  // Assicurati che resultArray abbia la dimensione corretta
    self.GetTruncatedStrings(stringArray.data(), stringArray.size(), mode, width, resultArray.data());
}, "", py::arg("stringArray"), py::arg("mode"), py::arg("width"), py::arg("resultArray"))*/
//.def("GetTruncatedStrings", py::overload_cast<const char *, int, unsigned int, float, char *>(&BFont::GetTruncatedStrings, py::const_), "", py::arg("stringArray"), py::arg("numStrings"), py::arg("mode"), py::arg("width"), py::arg("resultArray"))
.def("StringWidth", py::overload_cast<const char *>(&BFont::StringWidth, py::const_), "", py::arg("string"))
.def("StringWidth", py::overload_cast<const char *, int32>(&BFont::StringWidth, py::const_), "", py::arg("string"), py::arg("length"))
//.def("GetStringWidths", &BFont::GetStringWidths, "", py::arg("stringArray"), py::arg("lengthArray"), py::arg("numStrings"), py::arg("widthArray"))
.def("GetStringWidths", [](BFont& self, std::vector<const char *> stringArray, std::vector<int32> lengthArray){
	std::vector<float> widthArray;
	widthArray.resize(stringArray.size());
	self.GetStringWidths(stringArray.data(),lengthArray.data(),stringArray.size(),widthArray.data());
	return widthArray;
},"", py::arg("stringArray"), py::arg("lengthArray"))
//.def("GetEscapements", py::overload_cast<const char, int, float>(&BFont::GetEscapements,py::const_), "", py::arg("charArray"), py::arg("numChars"), py::arg("escapementArray"))
.def("GetEscapements", [](BFont& self, const std::string& charArray, std::vector<float>& escapementArray) {
// TODO: this function does not return the escapement array, or returns it empty, DON'T WORK
    self.GetEscapements(charArray.c_str(), charArray.size(), escapementArray.data());
    //return escapementArray;
}, "", py::arg("charArray"), py::arg("escapementArray"))
/*.def("GetEscapements", py::overload_cast<const char, int, escapement_delta *, float>(&BFont::GetEscapements,py::const_), "", py::arg("charArray"), py::arg("numChars"), py::arg("delta"), py::arg("escapementArray"))
.def("GetEscapements", py::overload_cast<const char, int, escapement_delta *, BPoint>(&BFont::GetEscapements,py::const_), "", py::arg("charArray"), py::arg("numChars"), py::arg("delta"), py::arg("escapementArray"))
.def("GetEscapements", py::overload_cast<const char, int, escapement_delta *, BPoint, BPoint>(&BFont::GetEscapements,py::const_), "", py::arg("charArray"), py::arg("numChars"), py::arg("delta"), py::arg("escapementArray"), py::arg("offsetArray"))
*/
.def("GetEdges", &BFont::GetEdges, "", py::arg("charArray"), py::arg("numBytes"), py::arg("edgeArray"))
.def("GetHeight", &BFont::GetHeight, "", py::arg("height"))
.def("GetBoundingBoxesAsGlyphs", &BFont::GetBoundingBoxesAsGlyphs, "", py::arg("charArray"), py::arg("numChars"), py::arg("mode"), py::arg("boundingBoxArray"))
.def("GetBoundingBoxesAsString", &BFont::GetBoundingBoxesAsString, "", py::arg("charArray"), py::arg("numChars"), py::arg("mode"), py::arg("delta"), py::arg("boundingBoxArray"))
//.def("GetBoundingBoxesForStrings", &BFont::GetBoundingBoxesForStrings, "", py::arg("stringArray"), py::arg("numStrings"), py::arg("mode"), py::arg("deltas"), py::arg("boundingBoxArray"))
// TODO TEST THIS, it returns empty boundingBox array  DON'T WORK
.def("GetBoundingBoxesForStrings", [](const BFont &self, const std::vector<std::string> &stringArray,
                                       int32 numStrings, font_metric_mode mode,
                                       std::vector<escapement_delta> &deltas,
                                       std::vector<BRect> &boundingBoxArray) {
    std::vector<const char*> cStrings;
    for (const auto &str : stringArray) {
        cStrings.push_back(str.c_str());
    }

    std::vector<escapement_delta>& constDeltas = deltas;
    std::vector<BRect>& constBoundingBoxArray = boundingBoxArray;

    self.GetBoundingBoxesForStrings(cStrings.data(), numStrings, mode, constDeltas.data(), constBoundingBoxArray.data());
},"",py::arg("stringArray"),py::arg("numStrings"),py::arg("mode"),py::arg("deltas"),py::arg("boundingBoxArray"))
/*.def("GetBoundingBoxesForStrings", [](const BFont &self, const std::vector<std::string> &stringArray,
                                       int32 numStrings, font_metric_mode mode,
                                       std::vector<escapement_delta> &deltas) {
    std::vector<BRect> boundingBoxArray;
    std::vector<const char*> cStrings;
    for (const auto &str : stringArray) {
        cStrings.push_back(str.c_str());
    }

    std::vector<escapement_delta>& constDeltas = deltas;
//    std::vector<BRect>& constBoundingBoxArray = boundingBoxArray;

    self.GetBoundingBoxesForStrings(cStrings.data(), numStrings, mode, constDeltas.data(), boundingBoxArray.data());
    return boundingBoxArray;
},"",py::arg("stringArray"),py::arg("numStrings"),py::arg("mode"),py::arg("deltas"))*/
//.def("GetGlyphShapes", &BFont::GetGlyphShapes, "", py::arg("charArray"), py::arg("numChars"), py::arg("glyphShapeArray"))
.def("GetGlyphShapes", [](BFont& self, const std::string& charArray){
    py::list glyphShapeList;
    std::vector<BShape*> glyphShapeArray(charArray.size());

    // Since Each BShape object corresponds to the glyph of one character (this is written in Haiku-Book)
    for (size_t i = 0; i < glyphShapeArray.size(); ++i) {
        glyphShapeArray[i] = new BShape();
    }

    self.GetGlyphShapes(charArray.data(), charArray.size(), glyphShapeArray.data());

    for (size_t i = 0; i < glyphShapeArray.size(); ++i) {
        glyphShapeList.append(py::cast(*glyphShapeArray[i]));
    }

    for (size_t i = 0; i < glyphShapeArray.size(); ++i) {
        delete glyphShapeArray[i];
    }

    return glyphShapeList;
},"",py::arg("charArray"))
.def("GetHasGlyphs", &BFont::GetHasGlyphs, "", py::arg("charArray"), py::arg("numChars"), py::arg("hasArray"))
.def("operator=", &BFont::operator=, "", py::arg("font"))
.def("__eq__", &BFont::operator==, "", py::arg("font"))
.def("__ne__", &BFont::operator!=, "", py::arg("font"))
.def("PrintToStream", &BFont::PrintToStream, "")
.def("LoadFont", py::overload_cast<const char *>(&BFont::LoadFont), "", py::arg("path"))
.def("LoadFont", py::overload_cast<const area_id, size_t, size_t>(&BFont::LoadFont), "", py::arg("fontAreaID"), py::arg("size")=0, py::arg("offset")=0)
.def("UnloadFont", &BFont::UnloadFont, "")
;
/*
m.def("count_font_families", &count_font_families, "", py::arg(""));

//m.def("get_font_family", &get_font_family, "", py::arg("index"), py::arg("name"), py::arg("flags")=NULL);

m.def("count_font_styles", &count_font_styles, "", py::arg("name"));

m.def("get_font_style", py::overload_cast<font_family, int, font_style *, unsigned int>(&get_font_style,py::const_), "", py::arg("family"), py::arg("index"), py::arg("name"), py::arg("flags")=NULL);

m.def("get_font_style", py::overload_cast<font_family, int, font_style *, unsigned short int, unsigned int>(&get_font_style), "", py::arg("family"), py::arg("index"), py::arg("name"), py::arg("face"), py::arg("flags")=NULL);

m.def("update_font_families", &update_font_families, "", py::arg("checkOnly"));

m.def("__and__", &operator&, "", py::arg("block"));

m.def("__or__", &operator|, "", py::arg("block"));

m.def("operator=", &operator=, "", py::arg("block"));

m.def("__eq__", &operator==, "", py::arg("block"));

m.def("__ne__", &operator!=, "", py::arg("block"));
*/
m.attr("be_plain_font") = be_plain_font;

m.attr("be_bold_font") = be_bold_font;

m.attr("be_fixed_font") = be_fixed_font;
}
