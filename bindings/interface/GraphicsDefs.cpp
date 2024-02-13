#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/GraphicsDefs.h>
#include <SupportDefs.h>

namespace py = pybind11;

PYBIND11_MODULE(GraphicsDefs,m)
{
py::enum_<color_space>(m, "color_space", "")
.value("B_NO_COLOR_SPACE", color_space::B_NO_COLOR_SPACE, "")
.value("B_RGBA64", color_space::B_RGBA64, "")
.value("B_RGB48", color_space::B_RGB48, "")
.value("B_RGB32", color_space::B_RGB32, "")
.value("B_RGBA32", color_space::B_RGBA32, "")
.value("B_RGB24", color_space::B_RGB24, "")
.value("B_RGB16", color_space::B_RGB16, "")
.value("B_RGB15", color_space::B_RGB15, "")
.value("B_RGBA15", color_space::B_RGBA15, "")
.value("B_CMAP8", color_space::B_CMAP8, "")
.value("B_GRAY8", color_space::B_GRAY8, "")
.value("B_GRAY1", color_space::B_GRAY1, "")
.value("B_RGBA64_BIG", color_space::B_RGBA64_BIG, "")
.value("B_RGB48_BIG", color_space::B_RGB48_BIG, "")
.value("B_RGB32_BIG", color_space::B_RGB32_BIG, "")
.value("B_RGBA32_BIG", color_space::B_RGBA32_BIG, "")
.value("B_RGB24_BIG", color_space::B_RGB24_BIG, "")
.value("B_RGB16_BIG", color_space::B_RGB16_BIG, "")
.value("B_RGB15_BIG", color_space::B_RGB15_BIG, "")
.value("B_RGBA15_BIG", color_space::B_RGBA15_BIG, "")
.value("B_RGBA64_LITTLE", color_space::B_RGBA64_LITTLE, "")
.value("B_RGB48_LITTLE", color_space::B_RGB48_LITTLE, "")
.value("B_RGB32_LITTLE", color_space::B_RGB32_LITTLE, "")
.value("B_RGBA32_LITTLE", color_space::B_RGBA32_LITTLE, "")
.value("B_RGB24_LITTLE", color_space::B_RGB24_LITTLE, "")
.value("B_RGB16_LITTLE", color_space::B_RGB16_LITTLE, "")
.value("B_RGB15_LITTLE", color_space::B_RGB15_LITTLE, "")
.value("B_RGBA15_LITTLE", color_space::B_RGBA15_LITTLE, "")
.value("B_YCbCr422", color_space::B_YCbCr422, "")
.value("B_YCbCr411", color_space::B_YCbCr411, "")
.value("B_YCbCr444", color_space::B_YCbCr444, "")
.value("B_YCbCr420", color_space::B_YCbCr420, "")
.value("B_YUV422", color_space::B_YUV422, "")
.value("B_YUV411", color_space::B_YUV411, "")
.value("B_YUV444", color_space::B_YUV444, "")
.value("B_YUV420", color_space::B_YUV420, "")
.value("B_YUV9", color_space::B_YUV9, "")
.value("B_YUV12", color_space::B_YUV12, "")
.value("B_UVL24", color_space::B_UVL24, "")
.value("B_UVL32", color_space::B_UVL32, "")
.value("B_UVLA32", color_space::B_UVLA32, "")
.value("B_LAB24", color_space::B_LAB24, "")
.value("B_LAB32", color_space::B_LAB32, "")
.value("B_LABA32", color_space::B_LABA32, "")
.value("B_HSI24", color_space::B_HSI24, "")
.value("B_HSI32", color_space::B_HSI32, "")
.value("B_HSIA32", color_space::B_HSIA32, "")
.value("B_HSV24", color_space::B_HSV24, "")
.value("B_HSV32", color_space::B_HSV32, "")
.value("B_HSVA32", color_space::B_HSVA32, "")
.value("B_HLS24", color_space::B_HLS24, "")
.value("B_HLS32", color_space::B_HLS32, "")
.value("B_HLSA32", color_space::B_HLSA32, "")
.value("B_CMY24", color_space::B_CMY24, "")
.value("B_CMY32", color_space::B_CMY32, "")
.value("B_CMYA32", color_space::B_CMYA32, "")
.value("B_CMYK32", color_space::B_CMYK32, "")
.value("B_MONOCHROME_1_BIT", color_space::B_MONOCHROME_1_BIT, "")
.value("B_GRAYSCALE_8_BIT", color_space::B_GRAYSCALE_8_BIT, "")
.value("B_COLOR_8_BIT", color_space::B_COLOR_8_BIT, "")
.value("B_RGB_32_BIT", color_space::B_RGB_32_BIT, "")
.value("B_RGB_16_BIT", color_space::B_RGB_16_BIT, "")
.value("B_BIG_RGB_32_BIT", color_space::B_BIG_RGB_32_BIT, "")
.value("B_BIG_RGB_16_BIT", color_space::B_BIG_RGB_16_BIT, "")
.export_values();


py::enum_<buffer_orientation>(m, "buffer_orientation", "")
.value("B_BUFFER_TOP_TO_BOTTOM", buffer_orientation::B_BUFFER_TOP_TO_BOTTOM, "")
.value("B_BUFFER_BOTTOM_TO_TOP", buffer_orientation::B_BUFFER_BOTTOM_TO_TOP, "")
.export_values();

py::enum_<buffer_layout>(m, "buffer_layout", "")
.value("B_BUFFER_NONINTERLEAVED", buffer_layout::B_BUFFER_NONINTERLEAVED, "")
.export_values();

py::enum_<drawing_mode>(m, "drawing_mode", "")
.value("B_OP_COPY", drawing_mode::B_OP_COPY, "")
.value("B_OP_OVER", drawing_mode::B_OP_OVER, "")
.value("B_OP_ERASE", drawing_mode::B_OP_ERASE, "")
.value("B_OP_INVERT", drawing_mode::B_OP_INVERT, "")
.value("B_OP_ADD", drawing_mode::B_OP_ADD, "")
.value("B_OP_SUBTRACT", drawing_mode::B_OP_SUBTRACT, "")
.value("B_OP_BLEND", drawing_mode::B_OP_BLEND, "")
.value("B_OP_MIN", drawing_mode::B_OP_MIN, "")
.value("B_OP_MAX", drawing_mode::B_OP_MAX, "")
.value("B_OP_SELECT", drawing_mode::B_OP_SELECT, "")
.value("B_OP_ALPHA", drawing_mode::B_OP_ALPHA, "")
.export_values();

py::enum_<source_alpha>(m, "source_alpha", "")
.value("B_PIXEL_ALPHA", source_alpha::B_PIXEL_ALPHA, "")
.value("B_CONSTANT_ALPHA", source_alpha::B_CONSTANT_ALPHA, "")
.export_values();

py::enum_<alpha_function>(m, "alpha_function", "")
.value("B_ALPHA_OVERLAY", alpha_function::B_ALPHA_OVERLAY, "")
.value("B_ALPHA_COMPOSITE", alpha_function::B_ALPHA_COMPOSITE, "")
.value("B_ALPHA_COMPOSITE_SOURCE_OVER", alpha_function::B_ALPHA_COMPOSITE_SOURCE_OVER, "")
.value("B_ALPHA_COMPOSITE_SOURCE_IN", alpha_function::B_ALPHA_COMPOSITE_SOURCE_IN, "")
.value("B_ALPHA_COMPOSITE_SOURCE_OUT", alpha_function::B_ALPHA_COMPOSITE_SOURCE_OUT, "")
.value("B_ALPHA_COMPOSITE_SOURCE_ATOP", alpha_function::B_ALPHA_COMPOSITE_SOURCE_ATOP, "")
.value("B_ALPHA_COMPOSITE_DESTINATION_OVER", alpha_function::B_ALPHA_COMPOSITE_DESTINATION_OVER, "")
.value("B_ALPHA_COMPOSITE_DESTINATION_IN", alpha_function::B_ALPHA_COMPOSITE_DESTINATION_IN, "")
.value("B_ALPHA_COMPOSITE_DESTINATION_OUT", alpha_function::B_ALPHA_COMPOSITE_DESTINATION_OUT, "")
.value("B_ALPHA_COMPOSITE_DESTINATION_ATOP", alpha_function::B_ALPHA_COMPOSITE_DESTINATION_ATOP, "")
.value("B_ALPHA_COMPOSITE_XOR", alpha_function::B_ALPHA_COMPOSITE_XOR, "")
.value("B_ALPHA_COMPOSITE_CLEAR", alpha_function::B_ALPHA_COMPOSITE_CLEAR, "")
.value("B_ALPHA_COMPOSITE_DIFFERENCE", alpha_function::B_ALPHA_COMPOSITE_DIFFERENCE, "")
.value("B_ALPHA_COMPOSITE_LIGHTEN", alpha_function::B_ALPHA_COMPOSITE_LIGHTEN, "")
.value("B_ALPHA_COMPOSITE_DARKEN", alpha_function::B_ALPHA_COMPOSITE_DARKEN, "")
.export_values();

m.attr("B_8_BIT_640x480") = 1;
m.attr("B_8_BIT_800x600") = 2;
m.attr("B_8_BIT_1024x768") = 4;
m.attr("B_8_BIT_1280x1024") = 8;
m.attr("B_8_BIT_1600x1200") = 16;
m.attr("B_16_BIT_640x480") = 32;
m.attr("B_16_BIT_800x600") = 64;
m.attr("B_16_BIT_1024x768") = 128;
m.attr("B_16_BIT_1280x1024") = 256;
m.attr("B_16_BIT_1600x1200") = 512;
m.attr("B_32_BIT_640x480") = 1024;
m.attr("B_32_BIT_800x600") = 2048;
m.attr("B_32_BIT_1024x768") = 4096;
m.attr("B_32_BIT_1280x1024") = 8192;
m.attr("B_32_BIT_1600x1200") = 16384;
m.attr("B_8_BIT_1152x900") = 32768;
m.attr("B_16_BIT_1152x900") = 65536;
m.attr("B_32_BIT_1152x900") = 131072;
m.attr("B_15_BIT_640x480") = 262144;
m.attr("B_15_BIT_800x600") = 524288;
m.attr("B_15_BIT_1024x768") = 1048576;
m.attr("B_15_BIT_1280x1024") = 2097152;
m.attr("B_15_BIT_1600x1200") = 4194304;
m.attr("B_15_BIT_1152x900") = 8388608;
m.attr("B_8_BIT_640x400") = 2147483648;

m.attr("B_TRANSPARENT_MAGIC_CMAP8") = B_TRANSPARENT_MAGIC_CMAP8;
m.attr("B_TRANSPARENT_MAGIC_RGBA15") = B_TRANSPARENT_MAGIC_RGBA15;
m.attr("B_TRANSPARENT_MAGIC_RGBA15_BIG") = B_TRANSPARENT_MAGIC_RGBA15_BIG;
m.attr("B_TRANSPARENT_MAGIC_RGBA32") = B_TRANSPARENT_MAGIC_RGBA32;
m.attr("B_TRANSPARENT_MAGIC_RGBA32_BIG") = B_TRANSPARENT_MAGIC_RGBA32_BIG;
m.attr("B_TRANSPARENT_8_BIT") = B_TRANSPARENT_8_BIT;

py::class_<pattern>(m, "pattern")
//.def_readwrite("data", &pattern::data, "")
.def_readonly("data", &pattern::data, "")
;

py::class_<rgb_color>(m, "rgb_color")
.def(py::init<>(), "")
.def("set_to", &rgb_color::set_to, "", py::arg("r"), py::arg("g"), py::arg("b"), py::arg("a")=255)
.def("Brightness", &rgb_color::Brightness, "")
.def("__eq__", &rgb_color::operator==, "", py::arg("other"))
.def("__ne__", &rgb_color::operator!=, "", py::arg("other"))
.def("operator=", &rgb_color::operator=, "", py::arg("other"))
.def_readwrite("red", &rgb_color::red, "")
.def_readwrite("green", &rgb_color::green, "")
.def_readwrite("blue", &rgb_color::blue, "")
.def_readwrite("alpha", &rgb_color::alpha, "")
;

py::class_<color_map>(m, "color_map")//TODO: color_list,inversion_map,index_map are writable
.def_readwrite("id", &color_map::id, "")
//.def_readwrite("color_list", &color_map::color_list, "")
.def_readonly("color_list", &color_map::color_list, "")
//.def_readwrite("inversion_map", &color_map::inversion_map, "")
.def_readonly("inversion_map", &color_map::inversion_map, "")
//.def_readwrite("index_map", &color_map::index_map, "")
.def_readonly("index_map", &color_map::index_map, "")
;

py::class_<overlay_rect_limits>(m, "overlay_rect_limits")
.def_readwrite("horizontal_alignment", &overlay_rect_limits::horizontal_alignment, "")
.def_readwrite("vertical_alignment", &overlay_rect_limits::vertical_alignment, "")
.def_readwrite("width_alignment", &overlay_rect_limits::width_alignment, "")
.def_readwrite("height_alignment", &overlay_rect_limits::height_alignment, "")
.def_readwrite("min_width", &overlay_rect_limits::min_width, "")
.def_readwrite("max_width", &overlay_rect_limits::max_width, "")
.def_readwrite("min_height", &overlay_rect_limits::min_height, "")
.def_readwrite("max_height", &overlay_rect_limits::max_height, "")
//.def_readwrite("reserved", &overlay_rect_limits::reserved, "")
;

py::class_<overlay_restrictions>(m, "overlay_restrictions")
.def_readwrite("source", &overlay_restrictions::source, "")
.def_readwrite("destination", &overlay_restrictions::destination, "")
.def_readwrite("min_width_scale", &overlay_restrictions::min_width_scale, "")
.def_readwrite("max_width_scale", &overlay_restrictions::max_width_scale, "")
.def_readwrite("min_height_scale", &overlay_restrictions::min_height_scale, "")
.def_readwrite("max_height_scale", &overlay_restrictions::max_height_scale, "")
//.def_readwrite("reserved", &overlay_restrictions::reserved, "")
;

py::class_<screen_id>(m, "screen_id")
.def_readwrite("id", &screen_id::id, "")
;

m.def("__eq__", &operator==, "", py::arg("a"), py::arg("b"));

m.def("__ne__", &operator!=, "", py::arg("a"), py::arg("b"));

m.def("make_color", &make_color, "", py::arg("red"), py::arg("green"), py::arg("blue"), py::arg("alpha")=255);

m.def("mix_color", &mix_color, "", py::arg("color1"), py::arg("color2"), py::arg("amount"));

m.def("blend_color", &blend_color, "", py::arg("color1"), py::arg("color2"), py::arg("amount"));

m.def("disable_color", &disable_color, "", py::arg("color"), py::arg("background"));

m.def("bitmaps_support_space", &bitmaps_support_space, "", py::arg("space"), py::arg("_supportFlags"));

m.def("get_pixel_size_for", &get_pixel_size_for, "", py::arg("space"), py::arg("_pixelChunk"), py::arg("_rowAlignment"), py::arg("_pixelsPerChunk"));

m.attr("B_SOLID_LOW") = B_SOLID_LOW;
m.attr("B_MIXED_COLORS") = B_MIXED_COLORS;
m.attr("B_SOLID_HIGH") = B_SOLID_HIGH;

m.attr("B_VIEWS_SUPPORT_DRAW_BITMAP") = 1;
m.attr("B_BITMAPS_SUPPORT_ATTACHED_VIEWS") = 2;
m.attr("B_BITMAPS_SUPPORT_OVERLAY") = 4;
m.attr("B_TRANSPARENT_COLOR") = B_TRANSPARENT_COLOR;
m.attr("B_TRANSPARENT_32_BIT") = B_TRANSPARENT_32_BIT;
m.attr("B_MAIN_SCREEN_ID") = B_MAIN_SCREEN_ID;
}
