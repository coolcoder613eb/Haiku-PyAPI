#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <add-ons/graphics/Accelerant.h>

namespace py = pybind11;

class MyClass {
public:
enum production {
	week,
	year
};
};

PYBIND11_MODULE(Accelerant, m)
{
m.attr("B_INIT_ACCELERANT") = 0;//py::cast(B_INIT_ACCELERANT);
m.attr("B_ACCELERANT_CLONE_INFO_SIZE") = 1;//py::cast(B_ACCELERANT_CLONE_INFO_SIZE);
m.attr("B_GET_ACCELERANT_CLONE_INFO") = 2;//py::cast(B_GET_ACCELERANT_CLONE_INFO);
m.attr("B_CLONE_ACCELERANT") = 3;//py::cast(B_CLONE_ACCELERANT);
m.attr("B_UNINIT_ACCELERANT") = 4;//py::cast(B_UNINIT_ACCELERANT);
m.attr("B_GET_ACCELERANT_DEVICE_INFO") = 5;//py::cast(B_GET_ACCELERANT_DEVICE_INFO);
m.attr("B_ACCELERANT_RETRACE_SEMAPHORE") = 6;//py::cast(B_ACCELERANT_RETRACE_SEMAPHORE);
m.attr("B_ACCELERANT_MODE_COUNT") = 0x100;//py::cast(B_ACCELERANT_MODE_COUNT);
m.attr("B_GET_MODE_LIST") = 0x101;//py::cast(B_GET_MODE_LIST);
m.attr("B_PROPOSE_DISPLAY_MODE") = 0x102;//py::cast(B_PROPOSE_DISPLAY_MODE);
m.attr("B_SET_DISPLAY_MODE") = 0x103;//py::cast(B_SET_DISPLAY_MODE);
m.attr("B_GET_DISPLAY_MODE") = 0x104;//py::cast(B_GET_DISPLAY_MODE);
m.attr("B_GET_FRAME_BUFFER_CONFIG") = 0x105;//py::cast(B_GET_FRAME_BUFFER_CONFIG);
m.attr("B_GET_PIXEL_CLOCK_LIMITS") = 0x106;//py::cast(B_GET_PIXEL_CLOCK_LIMITS);
m.attr("B_GET_TIMING_CONSTRAINTS") = 0x107;//py::cast(B_GET_TIMING_CONSTRAINTS);
m.attr("B_MOVE_DISPLAY") = 0x108;//py::cast(B_MOVE_DISPLAY);
m.attr("B_SET_INDEXED_COLORS") = 0x109;//py::cast(B_SET_INDEXED_COLORS);
m.attr("B_DPMS_CAPABILITIES") = 0x10A;//py::cast(B_DPMS_CAPABILITIES);
m.attr("B_DPMS_MODE") = 0x10B;//py::cast(B_DPMS_MODE);
m.attr("B_SET_DPMS_MODE") = 0x10C;//py::cast(B_SET_DPMS_MODE);
m.attr("B_GET_PREFERRED_DISPLAY_MODE") = 0x10D;//py::cast(B_GET_PREFERRED_DISPLAY_MODE);
m.attr("B_GET_MONITOR_INFO") = 0x10E;//py::cast(B_GET_MONITOR_INFO);
m.attr("B_GET_EDID_INFO") = 0x10F;//py::cast(B_GET_EDID_INFO);
m.attr("B_SET_BRIGHTNESS") = 0x110;//py::cast(B_SET_BRIGHTNESS);
m.attr("B_GET_BRIGHTNESS") = 0x111;//py::cast(B_GET_BRIGHTNESS);
m.attr("B_MOVE_CURSOR") = 0x200;//py::cast(B_MOVE_CURSOR);
m.attr("B_SET_CURSOR_SHAPE") = 0x201;//py::cast(B_SET_CURSOR_SHAPE);
m.attr("B_SHOW_CURSOR") = 0x202;//py::cast(B_SHOW_CURSOR);
m.attr("B_SET_CURSOR_BITMAP") = 0x203;//py::cast(B_SET_CURSOR_BITMAP);
m.attr("B_ACCELERANT_ENGINE_COUNT") = 0x300;//py::cast(B_ACCELERANT_ENGINE_COUNT);
m.attr("B_ACQUIRE_ENGINE") = 0x301;//py::cast(B_ACQUIRE_ENGINE);
m.attr("B_RELEASE_ENGINE") = 0x302;//py::cast(B_RELEASE_ENGINE);
m.attr("B_WAIT_ENGINE_IDLE") = 0x303;//py::cast(B_WAIT_ENGINE_IDLE);
m.attr("B_GET_SYNC_TOKEN") = 0x304;//py::cast(B_GET_SYNC_TOKEN);
m.attr("B_SYNC_TO_TOKEN") = 0x305;//py::cast(B_SYNC_TO_TOKEN);
m.attr("B_SCREEN_TO_SCREEN_BLIT") = 0x400;//py::cast(B_SCREEN_TO_SCREEN_BLIT);
m.attr("B_FILL_RECTANGLE") = 0x401;//py::cast(B_FILL_RECTANGLE);
m.attr("B_INVERT_RECTANGLE") = 0x402;//py::cast(B_INVERT_RECTANGLE);
m.attr("B_FILL_SPAN") = 0x403;//py::cast(B_FILL_SPAN);
m.attr("B_SCREEN_TO_SCREEN_TRANSPARENT_BLIT") = 0x404;//py::cast(B_SCREEN_TO_SCREEN_TRANSPARENT_BLIT);
m.attr("B_SCREEN_TO_SCREEN_SCALED_FILTERED_BLIT") = 0x405;//py::cast(B_SCREEN_TO_SCREEN_SCALED_FILTERED_BLIT);
m.attr("B_ACCELERANT_PRIVATE_START") = (int)0x80000000;//py::cast(B_ACCELERANT_PRIVATE_START);

m.attr("B_SCROLL") = 1 << 0;//py::cast(B_SCROLL);
m.attr("B_8_BIT_DAC") = 1 << 1;//py::cast(B_8_BIT_DAC);
m.attr("B_HARDWARE_CURSOR") = 1 << 2;//py::cast(B_HARDWARE_CURSOR);
m.attr("B_PARALLEL_ACCESS") = 1 << 3;//py::cast(B_PARALLEL_ACCESS);
m.attr("B_DPMS") = 1 << 4;//py::cast(B_DPMS);
m.attr("B_IO_FB_NA") = 1 << 5;//py::cast(B_IO_FB_NA);

m.attr("B_DPMS_ON") = 1 << 0;//py::cast(B_DPMS_ON);
m.attr("B_DPMS_STAND_BY") = 1 << 1;//py::cast(B_DPMS_STAND_BY);
m.attr("B_DPMS_SUSPEND") = 1 << 2;//py::cast(B_DPMS_SUSPEND);
m.attr("B_DPMS_OFF") = 1 << 3;//py::cast(B_DPMS_OFF);

m.attr("B_BLANK_PEDESTAL") = 1 << 27;//py::cast(B_BLANK_PEDESTAL);
m.attr("B_TIMING_INTERLACED") = 1 << 28;//py::cast(B_TIMING_INTERLACED);
m.attr("B_POSITIVE_HSYNC") = 1 << 29;//py::cast(B_POSITIVE_HSYNC);
m.attr("B_POSITIVE_VSYNC") = 1 << 30;//py::cast(B_POSITIVE_VSYNC);
m.attr("B_SYNC_ON_GREEN") = 1 << 31;//py::cast(B_SYNC_ON_GREEN);

m.attr("B_2D_ACCELERATION") = 1 << 0;//py::cast(B_2D_ACCELERATION);
m.attr("B_3D_ACCELERATION") = 1 << 1;//py::cast(B_3D_ACCELERATION);

py::class_<accelerant_device_info>(m, "accelerant_device_info")
.def(py::init(), "")
.def_readwrite("version", &accelerant_device_info::version, "")
//.def_readwrite("name", &accelerant_device_info::name, "")
//.def_readwrite("chipset", &accelerant_device_info::chipset, "")
//.def_readwrite("serial_no", &accelerant_device_info::serial_no, "")
.def_property(
            "name",
            [](const accelerant_device_info &acc_info) {
                return py::cast(acc_info.name);
            },
            [](accelerant_device_info &acc_info, const std::string &value) {
            	if (value.size()<sizeof(acc_info.name)) {
            		std::copy(value.begin(), value.end(), acc_info.name);
            		acc_info.name[value.size()] = '\0';
            	} else { 
            		throw std::invalid_argument("Wrong accelerant_device_info name dimension, it exceeds 32 chars");
            	}
            }
        , "")
.def_property(
            "chipset",
            [](const accelerant_device_info &acc_info) {
                return py::cast(acc_info.chipset);
            },
            [](accelerant_device_info &acc_info, const std::string &value) {
            	if (value.size()<sizeof(acc_info.chipset)) {
            		std::copy(value.begin(), value.end(), acc_info.chipset);
            		acc_info.chipset[value.size()] = '\0';
            	} else { 
            		throw std::invalid_argument("Wrong accelerant_device_info chipset dimension, it exceeds 32 chars");
            	}
            }
        , "")
.def_property(
            "serial_no",
            [](const accelerant_device_info &acc_info) {
                return py::cast(acc_info.serial_no);
            },
            [](accelerant_device_info &acc_info, const std::string &value) {
            	if (value.size()<sizeof(acc_info.serial_no)) {
            		std::copy(value.begin(), value.end(), acc_info.serial_no);
            		acc_info.serial_no[value.size()] = '\0';
            	} else { 
            		throw std::invalid_argument("Wrong accelerant_device_info serial_no dimension, it exceeds 32 chars");
            	}
            }
        , "")
.def_readwrite("memory", &accelerant_device_info::memory, "")
.def_readwrite("dac_speed", &accelerant_device_info::dac_speed, "")
;

py::class_<display_timing>(m, "display_timing")
.def(py::init(), "")
.def_readwrite("pixel_clock", &display_timing::pixel_clock, "")
.def_readwrite("h_display", &display_timing::h_display, "")
.def_readwrite("h_sync_start", &display_timing::h_sync_start, "")
.def_readwrite("h_sync_end", &display_timing::h_sync_end, "")
.def_readwrite("h_total", &display_timing::h_total, "")
.def_readwrite("v_display", &display_timing::v_display, "")
.def_readwrite("v_sync_start", &display_timing::v_sync_start, "")
.def_readwrite("v_sync_end", &display_timing::v_sync_end, "")
.def_readwrite("v_total", &display_timing::v_total, "")
.def_readwrite("flags", &display_timing::flags, "")
;

py::class_<display_mode>(m, "display_mode")
.def(py::init(), "")
.def_readwrite("timing", &display_mode::timing, "")
.def_readwrite("space", &display_mode::space, "")
.def_readwrite("virtual_width", &display_mode::virtual_width, "")
.def_readwrite("virtual_height", &display_mode::virtual_height, "")
.def_readwrite("h_display_start", &display_mode::h_display_start, "")
.def_readwrite("v_display_start", &display_mode::v_display_start, "")
.def_readwrite("flags", &display_mode::flags, "")
;

py::class_<frame_buffer_config>(m, "frame_buffer_config")
.def(py::init(), "")
.def_readwrite("frame_buffer", &frame_buffer_config::frame_buffer, "")
.def_readwrite("frame_buffer_dma", &frame_buffer_config::frame_buffer_dma, "")
.def_readwrite("bytes_per_row", &frame_buffer_config::bytes_per_row, "")
;

py::class_<display_timing_constraints>(m, "display_timing_constraints")
.def(py::init(), "")
.def_readwrite("h_res", &display_timing_constraints::h_res, "")
.def_readwrite("h_sync_min", &display_timing_constraints::h_sync_min, "")
.def_readwrite("h_sync_max", &display_timing_constraints::h_sync_max, "")
.def_readwrite("h_blank_min", &display_timing_constraints::h_blank_min, "")
.def_readwrite("h_blank_max", &display_timing_constraints::h_blank_max, "")
.def_readwrite("v_res", &display_timing_constraints::v_res, "")
.def_readwrite("v_sync_min", &display_timing_constraints::v_sync_min, "")
.def_readwrite("v_sync_max", &display_timing_constraints::v_sync_max, "")
.def_readwrite("v_blank_min", &display_timing_constraints::v_blank_min, "")
.def_readwrite("v_blank_max", &display_timing_constraints::v_blank_max, "")
;

py::enum_<MyClass::production>(m, "production")
.value("week",MyClass::production::week)
.value("year",MyClass::production::year)
.export_values();
//py::class_<produced>(m, "")
//.def_readwrite("week", &::week, "")
//.def_readwrite("year", &::year, "")
//;

py::class_<monitor_info>(m, "monitor_info")
.def(py::init(), "")
.def_readwrite("version", &monitor_info::version, "")
//.def_readwrite("vendor", &monitor_info::vendor, "")
.def_property(
            "vendor",
            [](const monitor_info &info) {
                return py::cast(info.vendor);
            },
            [](monitor_info &info, const std::string &value) {
            	if (value.size()<sizeof(info.vendor)) {
            		std::copy(value.begin(), value.end(), info.vendor);
            		info.vendor[value.size()] = '\0';
            	} else { 
            		throw std::invalid_argument("Wrong monitor_info vendor dimension, it exceeds 128 chars");
            	}
            }
        , "")
//.def_readwrite("name", &monitor_info::name, "")
.def_property(
            "name",
            [](const monitor_info &info) {
                return py::cast(info.name);
            },
            [](monitor_info &info, const std::string &value) {
            	if (value.size()<sizeof(info.name)) {
            		std::copy(value.begin(), value.end(), info.name);
            		info.name[value.size()] = '\0';
            	} else { 
            		throw std::invalid_argument("Wrong monitor_info name dimension, it exceeds 128 chars");
            	}
            }
        , "")
//.def_readwrite("serial_number", &monitor_info::serial_number, "")
.def_property(
            "serial_number",
            [](const monitor_info &info) {
                return py::cast(info.serial_number);
            },
            [](monitor_info &info, const std::string &value) {
            	if (value.size()<sizeof(info.serial_number)) {
            		std::copy(value.begin(), value.end(), info.serial_number);
            		info.serial_number[value.size()] = '\0';
            	} else { 
            		throw std::invalid_argument("Wrong monitor_info serial_number dimension, it exceeds 128 chars");
            	}
            }
        , "")
.def_readwrite("product_id", &monitor_info::product_id, "")
.def_readwrite("produced", &monitor_info::produced, "")
.def_readwrite("width", &monitor_info::width, "")
.def_readwrite("height", &monitor_info::height, "")
.def_readwrite("min_horizontal_frequency", &monitor_info::min_horizontal_frequency, "")
.def_readwrite("max_horizontal_frequency", &monitor_info::max_horizontal_frequency, "")
.def_readwrite("min_vertical_frequency", &monitor_info::min_vertical_frequency, "")
.def_readwrite("max_vertical_frequency", &monitor_info::max_vertical_frequency, "")
.def_readwrite("max_pixel_clock", &monitor_info::max_pixel_clock, "")
;

py::class_<blit_params>(m, "blit_params")
.def(py::init(), "")
.def_readwrite("src_left", &blit_params::src_left, "")
.def_readwrite("src_top", &blit_params::src_top, "")
.def_readwrite("dest_left", &blit_params::dest_left, "")
.def_readwrite("dest_top", &blit_params::dest_top, "")
.def_readwrite("width", &blit_params::width, "")
.def_readwrite("height", &blit_params::height, "")
;

py::class_<scaled_blit_params>(m, "scaled_blit_params")
.def(py::init(), "")
.def_readwrite("src_left", &scaled_blit_params::src_left, "")
.def_readwrite("src_top", &scaled_blit_params::src_top, "")
.def_readwrite("src_width", &scaled_blit_params::src_width, "")
.def_readwrite("src_height", &scaled_blit_params::src_height, "")
.def_readwrite("dest_left", &scaled_blit_params::dest_left, "")
.def_readwrite("dest_top", &scaled_blit_params::dest_top, "")
.def_readwrite("dest_width", &scaled_blit_params::dest_width, "")
.def_readwrite("dest_height", &scaled_blit_params::dest_height, "")
;

py::class_<fill_rect_params>(m, "fill_rect_params")
.def(py::init(), "")
.def_readwrite("left", &fill_rect_params::left, "")
.def_readwrite("top", &fill_rect_params::top, "")
.def_readwrite("right", &fill_rect_params::right, "")
.def_readwrite("bottom", &fill_rect_params::bottom, "")
;

py::class_<engine_token>(m, "engine_token")
.def(py::init(), "")
.def_readwrite("engine_id", &engine_token::engine_id, "")
.def_readwrite("capability_mask", &engine_token::capability_mask, "")
.def_readwrite("opaque", &engine_token::opaque, "")
;

py::class_<sync_token>(m, "sync_token")
.def(py::init(), "")
.def_readwrite("counter", &sync_token::counter, "")
.def_readwrite("engine_id", &sync_token::engine_id, "")
//.def_readwrite("opaque", &sync_token::opaque, "")
.def_property(
            "opaque",
            [](const sync_token &token) {
                return py::cast(token.opaque);
            },
            [](sync_token &token, const std::string &value) {
            	if (value.size()<sizeof(token.opaque)) {
            		std::copy(value.begin(), value.end(), token.opaque);
            		token.opaque[value.size()] = '\0';
            	} else { 
            		throw std::invalid_argument("Wrong sync_token opaque dimension, it exceeds 12 chars");
            	}
            }
        , "")
;

//m.def("get_accelerant_hook", &get_accelerant_hook, "", py::arg("feature"), py::arg("data"));

}
