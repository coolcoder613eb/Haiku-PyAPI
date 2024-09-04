#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <media/TimeSource.h>

namespace py = pybind11;
using namespace BPrivate;
using namespace BPrivate::media;

PYBIND11_MODULE(TimeSource, m)
{
//m.attr("BMediaRosterEx") = py::cast(BMediaRosterEx);

//m.attr("TimeSourceObject") = py::cast(TimeSourceObject);

//m.attr("SystemTimeSourceObject") = py::cast(SystemTimeSourceObject);

//m.attr("SlaveNodes") = py::cast(SlaveNodes);

//m.attr("TimeSourceTransmit") = py::cast(TimeSourceTransmit);

py::class_<BTimeSource, BMediaNode, std::unique_ptr<BTimeSource,py::nodelete>>(m, "BTimeSource")
.def("SnoozeUntil", &BTimeSource::SnoozeUntil, "", py::arg("performanceTime"), py::arg("withLatency")=0, py::arg("retrySignals")=false)
.def("Now", &BTimeSource::Now, "")
.def("PerformanceTimeFor", &BTimeSource::PerformanceTimeFor, "", py::arg("realTime"))
.def("RealTimeFor", &BTimeSource::RealTimeFor, "", py::arg("performanceTime"), py::arg("withLatency"))
.def("IsRunning", &BTimeSource::IsRunning, "")
.def("GetTime", &BTimeSource::GetTime, "", py::arg("_performanceTime"), py::arg("_realTime"), py::arg("_drift"))
.def("GetStartLatency", &BTimeSource::GetStartLatency, "", py::arg("_latency"))
.def_static("RealTime", &BTimeSource::RealTime, "")
;
/*
py::class_<time_source_op_info>(m, "time_source_op_info")
.def_readwrite("op", &time_source_op_info::op, "")
.def_readwrite("_reserved1", &time_source_op_info::_reserved1, "")
.def_readwrite("real_time", &time_source_op_info::real_time, "")
.def_readwrite("performance_time", &time_source_op_info::performance_time, "")
//.def_readwrite("_reserved2", &time_source_op_info::_reserved2, "")
.def_property(
            "_reserved2",
            [](const time_source_op_info &info) {
                py::array_t<int32> result(6);
                std::memcpy(result.mutable_data(), &info._reserved_, sizeof(info._reserved_));
                return result;
            },
            [](time_source_op_info &info, py::array_t<int32> value) {
                if (value.size() != 6) {
                    throw std::runtime_error("Array must have size 6");
                }
                std::memcpy(&info._reserved_, value.data(), sizeof(info._reserved_));
            }, "")
;*/


}
