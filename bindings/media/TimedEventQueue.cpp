#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>
#include <pybind11/numpy.h>

#include <media/TimedEventQueue.h>

namespace py = pybind11;

std::string get_media_timed_event_user_data(const media_timed_event& self) {
    return std::string(self.user_data);
}

void set_media_timed_event_user_data(media_timed_event& self, const std::string& user_data) {
    std::strncpy(self.user_data, user_data.c_str(), 64 - 1);
    self.user_data[64 - 1] = '\0';
}

PYBIND11_MODULE(TimedEventQueue, m)
{
py::class_<media_timed_event>(m, "media_timed_event")
.def(py::init(), "")
.def(py::init<bigtime_t, int32>(), "", py::arg("inTime"), py::arg("inType"))
.def(py::init<bigtime_t, int32, void *, uint32>(), "", py::arg("inTime"), py::arg("inType"), py::arg("inPointer"), py::arg("inCleanup"))
.def(py::init<bigtime_t, int32, void *, uint32, int32, int64, const char *, size_t>(), "", py::arg("inTime"), py::arg("inType"), py::arg("inPointer"), py::arg("inCleanup"), py::arg("inData"), py::arg("inBigdata"), py::arg("inUserData"), py::arg("dataSize")=0)
.def(py::init<const media_timed_event &>(), "", py::arg("other"))
.def("operator=", &media_timed_event::operator=, "", py::arg("other"))
.def_readwrite("event_time", &media_timed_event::event_time, "")
.def_readwrite("type", &media_timed_event::type, "")
.def_readwrite("pointer", &media_timed_event::pointer, "")
.def_readwrite("cleanup", &media_timed_event::cleanup, "")
.def_readwrite("data", &media_timed_event::data, "")
.def_readwrite("bigdata", &media_timed_event::bigdata, "")
//.def_readwrite("user_data", &media_timed_event::user_data, "")
.def_property("user_data", &get_media_timed_event_user_data,&set_media_timed_event_user_data,"")
//.def_readwrite("_reserved_media_timed_event_", &media_timed_event::_reserved_media_timed_event_, "")
/*.def_property(
            "_reserved_media_timed_event_",
            [](const media_timed_event &event) {
                py::array_t<uint32> result(8);
                std::memcpy(result.mutable_data(), &event._reserved_media_timed_event_, sizeof(event._reserved_media_timed_event_));
                return result;
            },
            [](media_timed_event &event, py::array_t<uint32> value) {
                if (value.size() != 8) {
                    throw std::runtime_error("Array must have size 8");
                }
                std::memcpy(&event._reserved_media_timed_event_, value.data(), sizeof(event._reserved_media_timed_event_));
            },"")*/
;

py::enum_<BTimedEventQueue::event_type>(m, "event_type", "")
.value("B_NO_EVENT", BTimedEventQueue::event_type::B_NO_EVENT, "")
.value("B_ANY_EVENT", BTimedEventQueue::event_type::B_ANY_EVENT, "")
.value("B_START", BTimedEventQueue::event_type::B_START, "")
.value("B_STOP", BTimedEventQueue::event_type::B_STOP, "")
.value("B_SEEK", BTimedEventQueue::event_type::B_SEEK, "")
.value("B_WARP", BTimedEventQueue::event_type::B_WARP, "")
.value("B_TIMER", BTimedEventQueue::event_type::B_TIMER, "")
.value("B_HANDLE_BUFFER", BTimedEventQueue::event_type::B_HANDLE_BUFFER, "")
.value("B_DATA_STATUS", BTimedEventQueue::event_type::B_DATA_STATUS, "")
.value("B_HARDWARE", BTimedEventQueue::event_type::B_HARDWARE, "")
.value("B_PARAMETER", BTimedEventQueue::event_type::B_PARAMETER, "")
.value("B_USER_EVENT", BTimedEventQueue::event_type::B_USER_EVENT, "")
.export_values();

py::enum_<BTimedEventQueue::cleanup_flag>(m, "cleanup_flag", "")
.value("B_NO_CLEANUP", BTimedEventQueue::cleanup_flag::B_NO_CLEANUP, "")
.value("B_RECYCLE_BUFFER", BTimedEventQueue::cleanup_flag::B_RECYCLE_BUFFER, "")
.value("B_EXPIRE_TIMER", BTimedEventQueue::cleanup_flag::B_EXPIRE_TIMER, "")
.value("B_USER_CLEANUP", BTimedEventQueue::cleanup_flag::B_USER_CLEANUP, "")
.export_values();

py::enum_<BTimedEventQueue::time_direction>(m, "time_direction", "")
.value("B_ALWAYS", BTimedEventQueue::time_direction::B_ALWAYS, "")
.value("B_BEFORE_TIME", BTimedEventQueue::time_direction::B_BEFORE_TIME, "")
.value("B_AT_TIME", BTimedEventQueue::time_direction::B_AT_TIME, "")
.value("B_AFTER_TIME", BTimedEventQueue::time_direction::B_AFTER_TIME, "")
.export_values();

py::class_<BTimedEventQueue>(m, "BTimedEventQueue")
//.def("operatornew", &BTimedEventQueue::operatornew, "", py::arg("size"))
//.def("operatordelete", &BTimedEventQueue::operatordelete, "", py::arg("ptr"), py::arg("size"))
.def(py::init(), "")
.def("AddEvent", &BTimedEventQueue::AddEvent, "", py::arg("event"))
.def("RemoveEvent", &BTimedEventQueue::RemoveEvent, "", py::arg("event"))
.def("RemoveFirstEvent", &BTimedEventQueue::RemoveFirstEvent, "", py::arg("_event")=NULL)
.def("HasEvents", &BTimedEventQueue::HasEvents, "")
.def("EventCount", &BTimedEventQueue::EventCount, "")
.def("FirstEvent", &BTimedEventQueue::FirstEvent, "")
.def("FirstEventTime", &BTimedEventQueue::FirstEventTime, "")
.def("LastEvent", &BTimedEventQueue::LastEvent, "")
.def("LastEventTime", &BTimedEventQueue::LastEventTime, "")
.def("FindFirstMatch", &BTimedEventQueue::FindFirstMatch, "", py::arg("eventTime"), py::arg("direction"), py::arg("inclusive")=true, py::arg("eventType")=BTimedEventQueue::event_type::B_ANY_EVENT)
.def("DoForEach", &BTimedEventQueue::DoForEach, "", py::arg("hook"), py::arg("context"), py::arg("eventTime")=0, py::arg("direction")=BTimedEventQueue::time_direction::B_ALWAYS, py::arg("inclusive")=true, py::arg("eventType")=BTimedEventQueue::event_type::B_ANY_EVENT)
.def("SetCleanupHook", &BTimedEventQueue::SetCleanupHook, "", py::arg("hook"), py::arg("context"))
.def("FlushEvents", &BTimedEventQueue::FlushEvents, "", py::arg("eventTime"), py::arg("direction"), py::arg("inclusive")=true, py::arg("eventType")=BTimedEventQueue::event_type::B_ANY_EVENT)
;

//m.def("__eq__", &operator==, "", py::arg("a"), py::arg("b"));
m.def("__eq__", py::overload_cast<const media_timed_event &, const media_timed_event &>(&operator==), "", py::arg("a"), py::arg("b"));

//m.def("__ne__", &operator!=, "", py::arg("a"), py::arg("b"));
m.def("__ne__", py::overload_cast<const media_timed_event &, const media_timed_event &>(&operator!=), "", py::arg("a"), py::arg("b"));

//m.def("__lt__", &operator<, "", py::arg("a"), py::arg("b"));
m.def("__lt__", py::overload_cast<const media_timed_event &, const media_timed_event &>(&operator<), "", py::arg("a"), py::arg("b"));

//m.def("__gt__", &operator>, "", py::arg("a"), py::arg("b"));
m.def("__gt__", py::overload_cast<const media_timed_event &, const media_timed_event &>(&operator>), "", py::arg("a"), py::arg("b"));

}
