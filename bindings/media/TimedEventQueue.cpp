#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <media/TimedEventQueue.h>

namespace py = pybind11;


void define_TimedEventQueue(py::module_& m)
{
py::class_<media_timed_event>(m, "media_timed_event")
.def(py::init(), "")
.def(py::init<bigtime_t, int>(), "", py::arg("inTime"), py::arg("inType"))
.def(py::init<bigtime_t, int, void *, unsigned int>(), "", py::arg("inTime"), py::arg("inType"), py::arg("inPointer"), py::arg("inCleanup"))
.def(py::init<bigtime_t, int, void *, unsigned int, int, int64_t, const char *, size_t>(), "", py::arg("inTime"), py::arg("inType"), py::arg("inPointer"), py::arg("inCleanup"), py::arg("inData"), py::arg("inBigdata"), py::arg("inUserData"), py::arg("dataSize")=0)
.def(py::init<const media_timed_event &>(), "", py::arg("other"))
.def("operator=", &media_timed_event::operator=, "", py::arg("other"))
.def_readwrite("event_time", &media_timed_event::event_time, "")
.def_readwrite("type", &media_timed_event::type, "")
.def_readwrite("pointer", &media_timed_event::pointer, "")
.def_readwrite("cleanup", &media_timed_event::cleanup, "")
.def_readwrite("data", &media_timed_event::data, "")
.def_readwrite("bigdata", &media_timed_event::bigdata, "")
.def_readwrite("user_data", &media_timed_event::user_data, "")
.def_readwrite("_reserved_media_timed_event_", &media_timed_event::_reserved_media_timed_event_, "")
;

py::class_<BTimedEventQueue>(m, "BTimedEventQueue")
.def("operatornew", &BTimedEventQueue::operatornew, "", py::arg("size"))
.def("operatordelete", &BTimedEventQueue::operatordelete, "", py::arg("ptr"), py::arg("size"))
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
.def("FindFirstMatch", &BTimedEventQueue::FindFirstMatch, "", py::arg("eventTime"), py::arg("direction"), py::arg("inclusive")=true, py::arg("eventType")=B_ANY_EVENT)
.def("DoForEach", &BTimedEventQueue::DoForEach, "", py::arg("hook"), py::arg("context"), py::arg("eventTime")=0, py::arg("direction")=B_ALWAYS, py::arg("inclusive")=true, py::arg("eventType")=B_ANY_EVENT)
.def("SetCleanupHook", &BTimedEventQueue::SetCleanupHook, "", py::arg("hook"), py::arg("context"))
.def("FlushEvents", &BTimedEventQueue::FlushEvents, "", py::arg("eventTime"), py::arg("direction"), py::arg("inclusive")=true, py::arg("eventType")=B_ANY_EVENT)
;

m.def("__eq__", &operator==, "", py::arg("a"), py::arg("b"));

m.def("__ne__", &operator!=, "", py::arg("a"), py::arg("b"));

m.def("__lt__", &operator<, "", py::arg("a"), py::arg("b"));

m.def("__gt__", &operator>, "", py::arg("a"), py::arg("b"));

}
