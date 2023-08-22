#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/UnicodeBlockObjects.h>
#include <Font.h>

namespace py = pybind11;


PYBIND11_MODULE(UnicodeBlockObjects,m)
{
m.attr("kNumUnicodeBlockRanges") = kNumUnicodeBlockRanges;

m.def("B_BASIC_LATIN_BLOCK", &B_BASIC_LATIN_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_LATIN1_SUPPLEMENT_BLOCK", &B_LATIN1_SUPPLEMENT_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_LATIN_EXTENDED_A_BLOCK", &B_LATIN_EXTENDED_A_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_LATIN_EXTENDED_B_BLOCK", &B_LATIN_EXTENDED_B_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_IPA_EXTENSIONS_BLOCK", &B_IPA_EXTENSIONS_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_SPACING_MODIFIER_LETTERS_BLOCK", &B_SPACING_MODIFIER_LETTERS_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_COMBINING_DIACRITICAL_MARKS_BLOCK", &B_COMBINING_DIACRITICAL_MARKS_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_BASIC_GREEK_BLOCK", &B_BASIC_GREEK_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_GREEK_SYMBOLS_AND_COPTIC_BLOCK", &B_GREEK_SYMBOLS_AND_COPTIC_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_CYRILLIC_BLOCK", &B_CYRILLIC_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_ARMENIAN_BLOCK", &B_ARMENIAN_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_BASIC_HEBREW_BLOCK", &B_BASIC_HEBREW_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_HEBREW_EXTENDED_BLOCK", &B_HEBREW_EXTENDED_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_BASIC_ARABIC_BLOCK", &B_BASIC_ARABIC_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_ARABIC_EXTENDED_BLOCK", &B_ARABIC_EXTENDED_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_DEVANAGARI_BLOCK", &B_DEVANAGARI_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_BENGALI_BLOCK", &B_BENGALI_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_GURMUKHI_BLOCK", &B_GURMUKHI_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_GUJARATI_BLOCK", &B_GUJARATI_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_ORIYA_BLOCK", &B_ORIYA_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_TAMIL_BLOCK", &B_TAMIL_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_TELUGU_BLOCK", &B_TELUGU_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_KANNADA_BLOCK", &B_KANNADA_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_MALAYALAM_BLOCK", &B_MALAYALAM_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_THAI_BLOCK", &B_THAI_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_LAO_BLOCK", &B_LAO_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_BASIC_GEORGIAN_BLOCK", &B_BASIC_GEORGIAN_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_GEORGIAN_EXTENDED_BLOCK", &B_GEORGIAN_EXTENDED_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_HANGUL_JAMO_BLOCK", &B_HANGUL_JAMO_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_LATIN_EXTENDED_ADDITIONAL_BLOCK", &B_LATIN_EXTENDED_ADDITIONAL_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_GREEK_EXTENDED_BLOCK", &B_GREEK_EXTENDED_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_GENERAL_PUNCTUATION_BLOCK", &B_GENERAL_PUNCTUATION_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_SUPERSCRIPTS_AND_SUBSCRIPTS_BLOCK", &B_SUPERSCRIPTS_AND_SUBSCRIPTS_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_CURRENCY_SYMBOLS_BLOCK", &B_CURRENCY_SYMBOLS_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_COMBINING_MARKS_FOR_SYMBOLS_BLOCK", &B_COMBINING_MARKS_FOR_SYMBOLS_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_LETTERLIKE_SYMBOLS_BLOCK", &B_LETTERLIKE_SYMBOLS_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_NUMBER_FORMS_BLOCK", &B_NUMBER_FORMS_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_ARROWS_BLOCK", &B_ARROWS_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_MATHEMATICAL_OPERATORS_BLOCK", &B_MATHEMATICAL_OPERATORS_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_MISCELLANEOUS_TECHNICAL_BLOCK", &B_MISCELLANEOUS_TECHNICAL_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_CONTROL_PICTURES_BLOCK", &B_CONTROL_PICTURES_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_OPTICAL_CHARACTER_RECOGNITION_BLOCK", &B_OPTICAL_CHARACTER_RECOGNITION_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_ENCLOSED_ALPHANUMERICS_BLOCK", &B_ENCLOSED_ALPHANUMERICS_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_BOX_DRAWING_BLOCK", &B_BOX_DRAWING_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_BLOCK_ELEMENTS_BLOCK", &B_BLOCK_ELEMENTS_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_GEOMETRIC_SHAPES_BLOCK", &B_GEOMETRIC_SHAPES_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_MISCELLANEOUS_SYMBOLS_BLOCK", &B_MISCELLANEOUS_SYMBOLS_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_DINGBATS_BLOCK", &B_DINGBATS_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_CJK_SYMBOLS_AND_PUNCTUATION_BLOCK", &B_CJK_SYMBOLS_AND_PUNCTUATION_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_HIRAGANA_BLOCK", &B_HIRAGANA_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_KATAKANA_BLOCK", &B_KATAKANA_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_BOPOMOFO_BLOCK", &B_BOPOMOFO_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_HANGUL_COMPATIBILITY_JAMO_BLOCK", &B_HANGUL_COMPATIBILITY_JAMO_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_CJK_MISCELLANEOUS_BLOCK", &B_CJK_MISCELLANEOUS_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_ENCLOSED_CJK_LETTERS_AND_MONTHS_BLOCK", &B_ENCLOSED_CJK_LETTERS_AND_MONTHS_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_CJK_COMPATIBILITY_BLOCK", &B_CJK_COMPATIBILITY_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_HANGUL_BLOCK", &B_HANGUL_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_HIGH_SURROGATES_BLOCK", &B_HIGH_SURROGATES_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_LOW_SURROGATES_BLOCK", &B_LOW_SURROGATES_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_CJK_UNIFIED_IDEOGRAPHS_BLOCK", &B_CJK_UNIFIED_IDEOGRAPHS_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_PRIVATE_USE_AREA_BLOCK", &B_PRIVATE_USE_AREA_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_CJK_COMPATIBILITY_IDEOGRAPHS_BLOCK", &B_CJK_COMPATIBILITY_IDEOGRAPHS_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_ALPHABETIC_PRESENTATION_FORMS_BLOCK", &B_ALPHABETIC_PRESENTATION_FORMS_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_ARABIC_PRESENTATION_FORMS_A_BLOCK", &B_ARABIC_PRESENTATION_FORMS_A_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_COMBINING_HALF_MARKS_BLOCK", &B_COMBINING_HALF_MARKS_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_CJK_COMPATIBILITY_FORMS_BLOCK", &B_CJK_COMPATIBILITY_FORMS_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_SMALL_FORM_VARIANTS_BLOCK", &B_SMALL_FORM_VARIANTS_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_ARABIC_PRESENTATION_FORMS_B_BLOCK", &B_ARABIC_PRESENTATION_FORMS_B_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_HALFWIDTH_AND_FULLWIDTH_FORMS_BLOCK", &B_HALFWIDTH_AND_FULLWIDTH_FORMS_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_SPECIALS_BLOCK", &B_SPECIALS_BLOCK, "", py::arg("LL"), py::arg("LL"));

m.def("B_TIBETAN_BLOCK", &B_TIBETAN_BLOCK, "", py::arg("LL"), py::arg("LL"));

}
