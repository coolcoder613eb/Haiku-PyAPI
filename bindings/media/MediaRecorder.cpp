#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <media/MediaRecorder.h>
#include <media/MediaAddOn.h>

namespace py = pybind11;
using namespace BPrivate;
using namespace BPrivate::media;

PYBIND11_MODULE(MediaRecorder, m)
{
py::enum_<BMediaRecorder::notification>(m, "notification", "")
.value("B_WILL_START", BMediaRecorder::notification::B_WILL_START, "")
.value("B_WILL_STOP", BMediaRecorder::notification::B_WILL_STOP, "")
.value("B_WILL_SEEK", BMediaRecorder::notification::B_WILL_SEEK, "")
.value("B_WILL_TIMEWARP", BMediaRecorder::notification::B_WILL_TIMEWARP, "")
.export_values();

py::class_<BMediaRecorder>(m, "BMediaRecorder")
.def(py::init<const char *, media_type>(), "", py::arg("name"), py::arg("type")=B_MEDIA_UNKNOWN_TYPE)
.def("InitCheck", &BMediaRecorder::InitCheck, "")
.def("SetHooks", &BMediaRecorder::SetHooks, "", py::arg("recordFunc")=NULL, py::arg("notifyFunc")=NULL, py::arg("cookie")=NULL)
.def("SetAcceptedFormat", &BMediaRecorder::SetAcceptedFormat, "", py::arg("format"))
.def("AcceptedFormat", &BMediaRecorder::AcceptedFormat, "")
.def("Start", &BMediaRecorder::Start, "", py::arg("force")=false)
.def("Stop", &BMediaRecorder::Stop, "", py::arg("force")=false)
.def("Connect", py::overload_cast<const media_format &>(&BMediaRecorder::Connect), "", py::arg("format"))
.def("Connect", py::overload_cast<const dormant_node_info &, const media_format &>(&BMediaRecorder::Connect), "", py::arg("dormantInfo"), py::arg("format"))
.def("Connect", py::overload_cast<const media_node &, const media_output *, const media_format *>(&BMediaRecorder::Connect), "", py::arg("node"), py::arg("output")=NULL, py::arg("format")=NULL)
.def("Disconnect", &BMediaRecorder::Disconnect, "")
.def("IsConnected", &BMediaRecorder::IsConnected, "")
.def("IsRunning", &BMediaRecorder::IsRunning, "")
.def("Format", &BMediaRecorder::Format, "")
;


}
