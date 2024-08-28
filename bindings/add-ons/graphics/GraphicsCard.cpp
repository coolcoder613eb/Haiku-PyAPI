#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <add-ons/graphics/GraphicsCard.h>

namespace py = pybind11;

PYBIND11_MODULE(GraphicsCard, m)
{
m.attr("B_OPEN_GRAPHICS_CARD") = py::cast(B_OPEN_GRAPHICS_CARD);
m.attr("B_CLOSE_GRAPHICS_CARD") = py::cast(B_CLOSE_GRAPHICS_CARD);
m.attr("B_GET_GRAPHICS_CARD_INFO") = py::cast(B_GET_GRAPHICS_CARD_INFO);
m.attr("B_GET_GRAPHICS_CARD_HOOKS") = py::cast(B_GET_GRAPHICS_CARD_HOOKS);
m.attr("B_SET_INDEXED_COLOR") = py::cast(B_SET_INDEXED_COLOR);
m.attr("B_GET_SCREEN_SPACES") = py::cast(B_GET_SCREEN_SPACES);
m.attr("B_CONFIG_GRAPHICS_CARD") = py::cast(B_CONFIG_GRAPHICS_CARD);
m.attr("B_GET_REFRESH_RATES") = py::cast(B_GET_REFRESH_RATES);
m.attr("B_SET_SCREEN_GAMMA") = py::cast(B_SET_SCREEN_GAMMA);
m.attr("B_GET_INFO_FOR_CLONE_SIZE") = py::cast(B_GET_INFO_FOR_CLONE_SIZE);
m.attr("B_GET_INFO_FOR_CLONE") = py::cast(B_GET_INFO_FOR_CLONE);
m.attr("B_SET_CLONED_GRAPHICS_CARD") = py::cast(B_SET_CLONED_GRAPHICS_CARD);
m.attr("B_CLOSE_CLONED_GRAPHICS_CARD") = py::cast(B_CLOSE_CLONED_GRAPHICS_CARD);
m.attr("B_PROPOSE_FRAME_BUFFER") = py::cast(B_PROPOSE_FRAME_BUFFER);
m.attr("B_SET_FRAME_BUFFER") = py::cast(B_SET_FRAME_BUFFER);
m.attr("B_SET_DISPLAY_AREA") = py::cast(B_SET_DISPLAY_AREA);
m.attr("B_MOVE_DISPLAY_AREA") = py::cast(B_MOVE_DISPLAY_AREA);

m.attr("B_CRT_CONTROL") = py::cast(B_CRT_CONTROL);
m.attr("B_GAMMA_CONTROL") = py::cast(B_GAMMA_CONTROL);
m.attr("B_FRAME_BUFFER_CONTROL") = py::cast(B_FRAME_BUFFER_CONTROL);
m.attr("B_PARALLEL_BUFFER_ACCESS") = py::cast(B_PARALLEL_BUFFER_ACCESS);
m.attr("B_LAME_ASS_CARD") = py::cast(B_LAME_ASS_CARD);

py::class_<graphics_card_info>(m, "graphics_card_info")
.def_readwrite("version", &graphics_card_info::version, "")
.def_readwrite("id", &graphics_card_info::id, "")
.def_readwrite("frame_buffer", &graphics_card_info::frame_buffer, "")
//.def_readwrite("rgba_order", &graphics_card_info::rgba_order, "")
.def_property(
            "rgba_order",
            [](const graphics_card_info &info) {
                return py::cast(info.rgba_order);
            },
            [](graphics_card_info &info, const std::string &value) {
            	if (value.size()<sizeof(info.rgba_order)) {
            		std::copy(value.begin(), value.end(), info.rgba_order);
            		info.rgba_order[value.size()] = '\0';
            	} else { 
            		throw std::invalid_argument("Wrong rgba_order dimension, it exceeds 4 chars");
            	}
            }
        , "")
.def_readwrite("flags", &graphics_card_info::flags, "")
.def_readwrite("bits_per_pixel", &graphics_card_info::bits_per_pixel, "")
.def_readwrite("bytes_per_row", &graphics_card_info::bytes_per_row, "")
.def_readwrite("width", &graphics_card_info::width, "")
.def_readwrite("height", &graphics_card_info::height, "")
;

py::class_<indexed_color>(m, "indexed_color")
.def_readwrite("index", &indexed_color::index, "")
.def_readwrite("color", &indexed_color::color, "")
;

py::class_<graphics_card_config>(m, "graphics_card_config")
.def_readwrite("space", &graphics_card_config::space, "")
.def_readwrite("refresh_rate", &graphics_card_config::refresh_rate, "")
.def_readwrite("h_position", &graphics_card_config::h_position, "")
.def_readwrite("v_position", &graphics_card_config::v_position, "")
.def_readwrite("h_size", &graphics_card_config::h_size, "")
.def_readwrite("v_size", &graphics_card_config::v_size, "")
;

py::class_<refresh_rate_info>(m, "refresh_rate_info")
.def_readwrite("min", &refresh_rate_info::min, "")
.def_readwrite("max", &refresh_rate_info::max, "")
.def_readwrite("current", &refresh_rate_info::current, "")
;

py::class_<graphics_card_spec>(m, "graphics_card_spec")
.def_readwrite("screen_base", &graphics_card_spec::screen_base, "")
.def_readwrite("io_base", &graphics_card_spec::io_base, "")
.def_readwrite("vendor_id", &graphics_card_spec::vendor_id, "")
.def_readwrite("device_id", &graphics_card_spec::device_id, "")
.def_readwrite("_reserved1_", &graphics_card_spec::_reserved1_, "")
.def_readwrite("_reserved2_", &graphics_card_spec::_reserved2_, "")
;

py::class_<rgb_color_line>(m, "rgb_color_line")
.def_readwrite("x1", &rgb_color_line::x1, "")
.def_readwrite("y1", &rgb_color_line::y1, "")
.def_readwrite("x2", &rgb_color_line::x2, "")
.def_readwrite("y2", &rgb_color_line::y2, "")
.def_readwrite("color", &rgb_color_line::color, "")
;

py::class_<indexed_color_line>(m, "indexed_color_line")
.def_readwrite("x1", &indexed_color_line::x1, "")
.def_readwrite("y1", &indexed_color_line::y1, "")
.def_readwrite("x2", &indexed_color_line::x2, "")
.def_readwrite("y2", &indexed_color_line::y2, "")
.def_readwrite("color", &indexed_color_line::color, "")
;

py::class_<frame_buffer_info>(m, "frame_buffer_info")
.def_readwrite("bits_per_pixel", &frame_buffer_info::bits_per_pixel, "")
.def_readwrite("bytes_per_row", &frame_buffer_info::bytes_per_row, "")
.def_readwrite("width", &frame_buffer_info::width, "")
.def_readwrite("height", &frame_buffer_info::height, "")
.def_readwrite("display_width", &frame_buffer_info::display_width, "")
.def_readwrite("display_height", &frame_buffer_info::display_height, "")
.def_readwrite("display_x", &frame_buffer_info::display_x, "")
.def_readwrite("display_y", &frame_buffer_info::display_y, "")
;

py::class_<screen_gamma>(m, "screen_gamma")
//.def_readwrite("red", &screen_gamma::red, "")
.def_property(
            "red",
            [](const screen_gamma &gamma) {
                return py::cast(gamma.red);
            },
            [](screen_gamma &gamma, const std::string &value) {
            	if (value.size()<sizeof(gamma.red)) {
            		std::copy(value.begin(), value.end(), gamma.red);
            		gamma.red[value.size()] = '\0';
            	} else { 
            		throw std::invalid_argument("Wrong red dimension, it exceeds 256 chars");
            	}
            }
        , "")
//.def_readwrite("green", &screen_gamma::green, "")
.def_property(
            "green",
            [](const screen_gamma &gamma) {
                return py::cast(gamma.green);
            },
            [](screen_gamma &gamma, const std::string &value) {
            	if (value.size()<sizeof(gamma.green)) {
            		std::copy(value.begin(), value.end(), gamma.green);
            		gamma.green[value.size()] = '\0';
            	} else { 
            		throw std::invalid_argument("Wrong green dimension, it exceeds 256 chars");
            	}
            }
        , "")
//.def_readwrite("blue", &screen_gamma::blue, "")
.def_property(
            "blue",
            [](const screen_gamma &gamma) {
                return py::cast(gamma.blue);
            },
            [](screen_gamma &gamma, const std::string &value) {
            	if (value.size()<sizeof(gamma.blue)) {
            		std::copy(value.begin(), value.end(), gamma.blue);
            		gamma.blue[value.size()] = '\0';
            	} else { 
            		throw std::invalid_argument("Wrong blue dimension, it exceeds 256 chars");
            	}
            }
        , "")
;

m.def("control_graphics_card", &control_graphics_card, "", py::arg(""), py::arg(""));

}
