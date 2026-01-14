#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <scheduler.h>

namespace py = pybind11;


//void define_scheduler(py::module_& m)
PYBIND11_MODULE(scheduler,m)
{
py::enum_<be_task_flags>(m, "be_task_flags", 
R"ipc_Qu8mg5v7(

To get a good thread priority, call suggest_thread_priority() with the
following information:
\a what is a bit mask describing what you're doing in the thread.
\a period is how many times a second your thread needs to run
(-1 if you're running continuously.)
\a jitter is an estimate (in us) of how much that period can vary,
as long as it stays centered on the average.
\a length is how long (in us) you expect to run for each invocation.
"Invocation" means, typically, receiving a message, dispatching
it, and then returning to reading a message.
MANIPULATION means both filtering and compression/decompression.
PLAYBACK and RECORDING means threads feeding/reading ACTUAL
HARDWARE ONLY.
0 means don't care

)ipc_Qu8mg5v7")
.value("B_DEFAULT_MEDIA_PRIORITY", be_task_flags::B_DEFAULT_MEDIA_PRIORITY, "")
.value("B_OFFLINE_PROCESSING", be_task_flags::B_OFFLINE_PROCESSING, "")
.value("B_STATUS_RENDERING", be_task_flags::B_STATUS_RENDERING, "")
.value("B_USER_INPUT_HANDLING", be_task_flags::B_USER_INPUT_HANDLING, "")
.value("B_LIVE_VIDEO_MANIPULATION", be_task_flags::B_LIVE_VIDEO_MANIPULATION, "")
.value("B_VIDEO_PLAYBACK", be_task_flags::B_VIDEO_PLAYBACK, "")
.value("B_VIDEO_RECORDING", be_task_flags::B_VIDEO_RECORDING, "")
.value("B_LIVE_AUDIO_MANIPULATION", be_task_flags::B_LIVE_AUDIO_MANIPULATION, "")
.value("B_AUDIO_PLAYBACK", be_task_flags::B_AUDIO_PLAYBACK, "")
.value("B_AUDIO_RECORDING", be_task_flags::B_AUDIO_RECORDING, "")
.value("B_LIVE_3D_RENDERING", be_task_flags::B_LIVE_3D_RENDERING, "")
.value("B_NUMBER_CRUNCHING", be_task_flags::B_NUMBER_CRUNCHING, "")
.value("B_MIDI_PROCESSING", be_task_flags::B_MIDI_PROCESSING, "")
.export_values();

py::enum_<scheduler_mode>(m, "scheduler_mode", "")
.value("SCHEDULER_MODE_LOW_LATENCY", scheduler_mode::SCHEDULER_MODE_LOW_LATENCY, "")
.value("SCHEDULER_MODE_POWER_SAVING", scheduler_mode::SCHEDULER_MODE_POWER_SAVING, "")
.export_values();

m.def("suggest_thread_priority", py::overload_cast<uint32, int32, bigtime_t, bigtime_t>(&suggest_thread_priority), "", py::arg("task_flags")=B_DEFAULT_MEDIA_PRIORITY, py::arg("period")=0, py::arg("jitter")=0, py::arg("length")=0);

m.def("estimate_max_scheduling_latency", py::overload_cast<thread_id>(&estimate_max_scheduling_latency), "", py::arg("th")=- 1);

m.def("set_scheduler_mode", py::overload_cast<int32>(&set_scheduler_mode), "", py::arg("mode"));

//m.def("get_scheduler_mode", py::overload_cast<void>(&get_scheduler_mode), "", py::arg(""));
m.def("get_scheduler_mode", &get_scheduler_mode, "");

m.def("suggest_thread_priority", py::overload_cast<uint32, int32, bigtime_t, bigtime_t>(&suggest_thread_priority), "", py::arg("what"), py::arg("period"), py::arg("jitter"), py::arg("length"));

m.def("estimate_max_scheduling_latency", py::overload_cast<thread_id>(&estimate_max_scheduling_latency), "", py::arg("th"));

m.def("set_scheduler_mode", py::overload_cast<int32>(&set_scheduler_mode), "", py::arg("mode"));

//m.def("get_scheduler_mode", py::overload_cast<void>(&get_scheduler_mode), "", py::arg(""));

}
