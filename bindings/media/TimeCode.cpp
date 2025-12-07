#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>
#include <pybind11/numpy.h>

#include <media/TimeCode.h>

namespace py = pybind11;

std::string get_timecode_info_name(const timecode_info& self) {
    return std::string(self.name);
}

void set_timecode_info_name(timecode_info& self, const std::string& name) {
    std::strncpy(self.name, name.c_str(), 32 - 1);
    self.name[32 - 1] = '\0';
}

std::string get_timecode_info_format(const timecode_info& self) {
    return std::string(self.format);
}

void set_timecode_info_format(timecode_info& self, const std::string& format) {
    std::strncpy(self.format, format.c_str(), 32 - 1);
    self.name[32 - 1] = '\0';
}

PYBIND11_MODULE(TimeCode, m)
{
py::enum_<timecode_type>(m, "timecode_type", "")
.value("B_TIMECODE_DEFAULT", timecode_type::B_TIMECODE_DEFAULT, "")
.value("B_TIMECODE_100", timecode_type::B_TIMECODE_100, "")
.value("B_TIMECODE_75", timecode_type::B_TIMECODE_75, "")
.value("B_TIMECODE_30", timecode_type::B_TIMECODE_30, "")
.value("B_TIMECODE_30_DROP_2", timecode_type::B_TIMECODE_30_DROP_2, "")
.value("B_TIMECODE_30_DROP_4", timecode_type::B_TIMECODE_30_DROP_4, "")
.value("B_TIMECODE_25", timecode_type::B_TIMECODE_25, "")
.value("B_TIMECODE_24", timecode_type::B_TIMECODE_24, "")
.value("B_TIMECODE_18", timecode_type::B_TIMECODE_18, "")
.export_values();

py::class_<timecode_info>(m, "timecode_info")
.def_readwrite("type", &timecode_info::type, "")
.def_readwrite("drop_frames", &timecode_info::drop_frames, "")
.def_readwrite("every_nth", &timecode_info::every_nth, "")
.def_readwrite("except_nth", &timecode_info::except_nth, "")
.def_readwrite("fps_div", &timecode_info::fps_div, "")
//.def_readwrite("name", &timecode_info::name, "")
.def_property("name", &get_timecode_info_name,&set_timecode_info_name,"")
//.def_readwrite("format", &timecode_info::format, "")
.def_property("format", &get_timecode_info_format,&set_timecode_info_format,"")
//.def_readwrite("_reserved_", &timecode_info::_reserved_, "")
.def_property(
            "_reserved_",
            [](const timecode_info &info) {
                py::array_t<char> result(64);
                std::memcpy(result.mutable_data(), &info._reserved_, sizeof(info._reserved_));
                return result;
            },
            [](timecode_info &info, py::array_t<char> value) {
                if (value.size() != 64) {
                    throw std::runtime_error("Array must have size 64");
                }
                std::memcpy(&info._reserved_, value.data(), sizeof(info._reserved_));
            },"")
;

py::class_<BTimeCode>(m, "BTimeCode")
.def(py::init(), "")
.def(py::init<bigtime_t, timecode_type>(), "", py::arg("microSeconds"), py::arg("type")=B_TIMECODE_DEFAULT)
.def(py::init<const BTimeCode &>(), "", py::arg("other"))
.def(py::init<int, int, int, int, timecode_type>(), "", py::arg("hours"), py::arg("minutes"), py::arg("seconds"), py::arg("frames"), py::arg("type")=B_TIMECODE_DEFAULT)
.def("SetData", &BTimeCode::SetData, "", py::arg("hours"), py::arg("minutes"), py::arg("seconds"), py::arg("frames"))
.def("SetType", &BTimeCode::SetType, "", py::arg("type"))
.def("SetMicroseconds", &BTimeCode::SetMicroseconds, "", py::arg("microSeconds"))
.def("SetLinearFrames", &BTimeCode::SetLinearFrames, "", py::arg("linearFrames"))
.def("__copy__", &BTimeCode::operator=, "", py::arg("other"))
.def("__eq__", &BTimeCode::operator==, "", py::arg("other"))
.def("__lt__", &BTimeCode::operator<, "", py::arg("other"))
.def("__iadd__", &BTimeCode::operator+=, "", py::arg("other"))
.def("__isub__", &BTimeCode::operator-=, "", py::arg("other"))
.def("__add__", &BTimeCode::operator+, "", py::arg("other"))
.def("operator-", &BTimeCode::operator-, "", py::arg("other"))
.def("Hours", &BTimeCode::Hours, "")
.def("Minutes", &BTimeCode::Minutes, "")
.def("Seconds", &BTimeCode::Seconds, "")
.def("Frames", &BTimeCode::Frames, "")
.def("Type", &BTimeCode::Type, "")
.def("GetData", &BTimeCode::GetData, "", py::arg("_hours"), py::arg("_minutes"), py::arg("_seconds"), py::arg("_frames"), py::arg("_type")=NULL)
.def("Microseconds", &BTimeCode::Microseconds, "")
.def("LinearFrames", &BTimeCode::LinearFrames, "")
.def("GetString", &BTimeCode::GetString, "", py::arg("string"))
;

m.def("us_to_timecode", &us_to_timecode, "", py::arg("micros"), py::arg("hours"), py::arg("minutes"), py::arg("seconds"), py::arg("frames"), py::arg("code")=NULL);

m.def("timecode_to_us", &timecode_to_us, "", py::arg("hours"), py::arg("minutes"), py::arg("seconds"), py::arg("frames"), py::arg("micros"), py::arg("code")=NULL);

m.def("frames_to_timecode", &frames_to_timecode, "", py::arg("l_frames"), py::arg("hours"), py::arg("minutes"), py::arg("seconds"), py::arg("frames"), py::arg("code")=NULL);

m.def("timecode_to_frames", &timecode_to_frames, "", py::arg("hours"), py::arg("minutes"), py::arg("seconds"), py::arg("frames"), py::arg("lFrames"), py::arg("code")=NULL);

m.def("get_timecode_description", &get_timecode_description, "", py::arg("type"), py::arg("_timecode"));

m.def("count_timecodes", &count_timecodes, "");

}
