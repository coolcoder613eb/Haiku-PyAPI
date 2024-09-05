#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <media/MediaRoster.h>
#include <media/MediaNode.h>
#include <String.h>
#include <media/TimeSource.h>
#include <media/MediaAddOn.h>
#include <MimeType.h>
#include <Messenger.h>
#include <media/ParameterWeb.h>

namespace py = pybind11;
using namespace BPrivate;
using namespace BPrivate::media;

PYBIND11_MODULE(MediaRoster, m)
{
py::enum_<bus_type>(m, "bus_type", "//! The BMediaRoster is the main API to the Media Kit.")
.value("B_ISA_BUS", bus_type::B_ISA_BUS, "")
.value("B_PCI_BUS", bus_type::B_PCI_BUS, "")
.value("B_PCMCIA_BUS", bus_type::B_PCMCIA_BUS, "")
.value("B_UNKNOWN_BUS", bus_type::B_UNKNOWN_BUS, "")
.export_values();

//m.attr("DefaultDeleter") = py::cast(DefaultDeleter);

//m.attr("BMediaRosterEx") = py::cast(BMediaRosterEx);

py::class_<BMediaRoster, BLooper>(m, "BMediaRoster")
.def_static("Roster", &BMediaRoster::Roster, "", py::arg("_error")=NULL)
.def_static("CurrentRoster", &BMediaRoster::CurrentRoster, "")
.def_static("IsRunning", &BMediaRoster::IsRunning, "")
.def("GetVideoInput", &BMediaRoster::GetVideoInput, "", py::arg("_node"))
.def("GetAudioInput", &BMediaRoster::GetAudioInput, "", py::arg("_node"))
.def("GetVideoOutput", &BMediaRoster::GetVideoOutput, "", py::arg("_node"))
.def("GetAudioMixer", &BMediaRoster::GetAudioMixer, "", py::arg("_node"))
.def("GetAudioOutput", py::overload_cast<media_node *>(&BMediaRoster::GetAudioOutput), "", py::arg("_node"))
.def("GetAudioOutput", py::overload_cast<media_node *, int32*, BString *>(&BMediaRoster::GetAudioOutput), "", py::arg("_node"), py::arg("_inputId"), py::arg("_inputName"))
.def("GetTimeSource", &BMediaRoster::GetTimeSource, "", py::arg("_node"))
.def("SetVideoInput", py::overload_cast<const media_node &>(&BMediaRoster::SetVideoInput), "", py::arg("producer"))
.def("SetVideoInput", py::overload_cast<const dormant_node_info &>(&BMediaRoster::SetVideoInput), "", py::arg("producer"))
.def("SetAudioInput", py::overload_cast<const media_node &>(&BMediaRoster::SetAudioInput), "", py::arg("producer"))
.def("SetAudioInput", py::overload_cast<const dormant_node_info &>(&BMediaRoster::SetAudioInput), "", py::arg("producer"))
.def("SetVideoOutput", py::overload_cast<const media_node &>(&BMediaRoster::SetVideoOutput), "", py::arg("consumer"))
.def("SetVideoOutput", py::overload_cast<const dormant_node_info &>(&BMediaRoster::SetVideoOutput), "", py::arg("consumer"))
.def("SetAudioOutput", py::overload_cast<const media_node &>(&BMediaRoster::SetAudioOutput), "", py::arg("consumer"))
.def("SetAudioOutput", py::overload_cast<const media_input &>(&BMediaRoster::SetAudioOutput), "", py::arg("inputToOutput"))
.def("SetAudioOutput", py::overload_cast<const dormant_node_info &>(&BMediaRoster::SetAudioOutput), "", py::arg("consumer"))
.def("GetNodeFor", &BMediaRoster::GetNodeFor, "", py::arg("node"), py::arg("clone"))
.def("GetSystemTimeSource", &BMediaRoster::GetSystemTimeSource, "", py::arg("clone"))
.def("ReleaseNode", &BMediaRoster::ReleaseNode, "", py::arg("node"))
.def("MakeTimeSourceFor", &BMediaRoster::MakeTimeSourceFor, "", py::arg("for_node"))
.def("Connect", py::overload_cast<const media_source &, const media_destination &, media_format *, media_output *, media_input *>(&BMediaRoster::Connect), "", py::arg("from"), py::arg("to"), py::arg("_inOutFormat"), py::arg("_output"), py::arg("_input"))
.def("Connect", py::overload_cast<const media_source &, const media_destination &, media_format *, media_output *, media_input *, uint32, void *>(&BMediaRoster::Connect), "", py::arg("from"), py::arg("to"), py::arg("_inOutFormat"), py::arg("_output"), py::arg("_input"), py::arg("flags"), py::arg("_reserved")=NULL)
.def("Disconnect", py::overload_cast<media_node_id, const media_source &, media_node_id, const media_destination &>(&BMediaRoster::Disconnect), "", py::arg("sourceNode"), py::arg("source"), py::arg("destinationNode"), py::arg("destination"))
.def("Disconnect", py::overload_cast<const media_output &, const media_input &>(&BMediaRoster::Disconnect), "", py::arg("output"), py::arg("input"))
.def("StartNode", &BMediaRoster::StartNode, "", py::arg("node"), py::arg("atPerformanceTime"))
.def("StopNode", &BMediaRoster::StopNode, "", py::arg("node"), py::arg("atPerformanceTime"), py::arg("immediate")=false)
.def("SeekNode", &BMediaRoster::SeekNode, "", py::arg("node"), py::arg("toMediaTime"), py::arg("atPerformanceTime")=0)
.def("StartTimeSource", &BMediaRoster::StartTimeSource, "", py::arg("node"), py::arg("atRealTime"))
.def("StopTimeSource", &BMediaRoster::StopTimeSource, "", py::arg("node"), py::arg("atRealTime"), py::arg("immediate")=false)
.def("SeekTimeSource", &BMediaRoster::SeekTimeSource, "", py::arg("node"), py::arg("toPerformanceTime"), py::arg("atRealTime"))
.def("SyncToNode", &BMediaRoster::SyncToNode, "", py::arg("node"), py::arg("atTime"), py::arg("timeout")=B_INFINITE_TIMEOUT)
.def("SetRunModeNode", &BMediaRoster::SetRunModeNode, "", py::arg("node"), py::arg("mode"))
.def("PrerollNode", &BMediaRoster::PrerollNode, "", py::arg("node"))
.def("RollNode", &BMediaRoster::RollNode, "", py::arg("node"), py::arg("startPerformance"), py::arg("stopPerformance"), py::arg("atMediaTime")=- B_INFINITE_TIMEOUT)
.def("SetProducerRunModeDelay", &BMediaRoster::SetProducerRunModeDelay, "", py::arg("node"), py::arg("delay"), py::arg("mode")=BMediaNode::run_mode::B_RECORDING)
.def("SetProducerRate", &BMediaRoster::SetProducerRate, "", py::arg("producer"), py::arg("numer"), py::arg("denom"))
.def("GetLiveNodeInfo", &BMediaRoster::GetLiveNodeInfo, "", py::arg("node"), py::arg("_liveInfo"))
.def("GetLiveNodes", &BMediaRoster::GetLiveNodes, "", py::arg("_liveNodes"), py::arg("inOutTotalCount"), py::arg("hasInput")=NULL, py::arg("hasOutput")=NULL, py::arg("name")=NULL, py::arg("nodeKinds")=0)
.def("GetFreeInputsFor", &BMediaRoster::GetFreeInputsFor, "", py::arg("node"), py::arg("_freeInputsBuffer"), py::arg("bufferCapacity"), py::arg("_foundCount"), py::arg("filterType")=B_MEDIA_UNKNOWN_TYPE)
.def("GetConnectedInputsFor", &BMediaRoster::GetConnectedInputsFor, "", py::arg("node"), py::arg("_activeInputsBuffer"), py::arg("bufferCapacity"), py::arg("_foundCount"))
.def("GetAllInputsFor", &BMediaRoster::GetAllInputsFor, "", py::arg("node"), py::arg("_inputsBuffer"), py::arg("bufferCapacity"), py::arg("_foundCount"))
.def("GetFreeOutputsFor", &BMediaRoster::GetFreeOutputsFor, "", py::arg("node"), py::arg("_freeOutputsBuffer"), py::arg("bufferCapacity"), py::arg("_foundCount"), py::arg("filterType")=B_MEDIA_UNKNOWN_TYPE)
.def("GetConnectedOutputsFor", &BMediaRoster::GetConnectedOutputsFor, "", py::arg("node"), py::arg("_activeOutputsBuffer"), py::arg("bufferCapacity"), py::arg("_foundCount"))
.def("GetAllOutputsFor", &BMediaRoster::GetAllOutputsFor, "", py::arg("node"), py::arg("_outputsBuffer"), py::arg("bufferCapacity"), py::arg("_foundCount"))
.def("StartWatching", py::overload_cast<const BMessenger &>(&BMediaRoster::StartWatching), "", py::arg("target"))
.def("StartWatching", py::overload_cast<const BMessenger &, int32>(&BMediaRoster::StartWatching), "", py::arg("target"), py::arg("notificationType"))
.def("StartWatching", py::overload_cast<const BMessenger &, const media_node &, int32>(&BMediaRoster::StartWatching), "", py::arg("target"), py::arg("node"), py::arg("notificationType"))
.def("StopWatching", py::overload_cast<const BMessenger &>(&BMediaRoster::StopWatching), "", py::arg("target"))
.def("StopWatching", py::overload_cast<const BMessenger &, int32>(&BMediaRoster::StopWatching), "", py::arg("target"), py::arg("notificationType"))
.def("StopWatching", py::overload_cast<const BMessenger &, const media_node &, int32>(&BMediaRoster::StopWatching), "", py::arg("target"), py::arg("node"), py::arg("notificationType"))
.def("RegisterNode", &BMediaRoster::RegisterNode, "", py::arg("node"))
.def("UnregisterNode", &BMediaRoster::UnregisterNode, "", py::arg("node"))
.def("SetTimeSourceFor", &BMediaRoster::SetTimeSourceFor, "", py::arg("node"), py::arg("timeSource"))
//.def("GetParameterWebFor", &BMediaRoster::GetParameterWebFor, "", py::arg("node"), py::arg("_web"))
.def("GetParameterWebFor",[](BMediaRoster& self, const media_node& node) {
	BParameterWeb* web = nullptr;
	status_t status =self.GetParameterWebFor(node, &web);
	return std::make_tuple(status, web);
}, "", py::arg("node"))
.def("StartControlPanel", &BMediaRoster::StartControlPanel, "", py::arg("node"), py::arg("_messenger")=NULL)
.def("GetDormantNodes", &BMediaRoster::GetDormantNodes, "", py::arg("_info"), py::arg("_inOutCount"), py::arg("_hasInput")=NULL, py::arg("_hasOutput")=NULL, py::arg("name")=NULL, py::arg("requireKinds")=0, py::arg("denyKinds")=0)
.def("InstantiateDormantNode", py::overload_cast<const dormant_node_info &, media_node *, uint32>(&BMediaRoster::InstantiateDormantNode), "", py::arg("info"), py::arg("_node"), py::arg("flags"))
.def("InstantiateDormantNode", py::overload_cast<const dormant_node_info &, media_node *>(&BMediaRoster::InstantiateDormantNode), "", py::arg("info"), py::arg("_node"))
.def("GetDormantNodeFor", &BMediaRoster::GetDormantNodeFor, "", py::arg("node"), py::arg("_info"))
.def("GetDormantFlavorInfoFor", &BMediaRoster::GetDormantFlavorInfoFor, "", py::arg("info"), py::arg("_flavor"))
.def("GetLatencyFor", &BMediaRoster::GetLatencyFor, "", py::arg("producer"), py::arg("_latency"))
.def("GetInitialLatencyFor", &BMediaRoster::GetInitialLatencyFor, "", py::arg("producer"), py::arg("_latency"), py::arg("_flags")=NULL)
.def("GetStartLatencyFor", &BMediaRoster::GetStartLatencyFor, "", py::arg("timeSource"), py::arg("_latency"))
.def("GetFileFormatsFor", &BMediaRoster::GetFileFormatsFor, "", py::arg("fileInterface"), py::arg("_formatsBuffer"), py::arg("_inOutNumInfos"))
.def("SetRefFor", &BMediaRoster::SetRefFor, "", py::arg("fileInterface"), py::arg("file"), py::arg("createAndTruncate"), py::arg("_length"))
.def("GetRefFor", &BMediaRoster::GetRefFor, "", py::arg("node"), py::arg("_ref"), py::arg("mimeType")=NULL)
.def("SniffRefFor", &BMediaRoster::SniffRefFor, "", py::arg("fileInterface"), py::arg("ref"), py::arg("_mimeType"), py::arg("_capability"))
.def("SniffRef", &BMediaRoster::SniffRef, "", py::arg("ref"), py::arg("requireNodeKinds"), py::arg("_node"), py::arg("_mimeType")=NULL)
.def("GetDormantNodeForType", &BMediaRoster::GetDormantNodeForType, "", py::arg("type"), py::arg("requireNodeKinds"), py::arg("_info"))
.def("GetReadFileFormatsFor", &BMediaRoster::GetReadFileFormatsFor, "", py::arg("node"), py::arg("_readFormatsBuffer"), py::arg("bufferCapacity"), py::arg("_foundCount"))
.def("GetWriteFileFormatsFor", &BMediaRoster::GetWriteFileFormatsFor, "", py::arg("node"), py::arg("_writeFormatsBuffer"), py::arg("bufferCapacity"), py::arg("_foundCount"))
.def("GetFormatFor", py::overload_cast<const media_output &, media_format *, uint32>(&BMediaRoster::GetFormatFor), "", py::arg("output"), py::arg("_inOutFormat"), py::arg("flags")=0)
.def("GetFormatFor", py::overload_cast<const media_input &, media_format *, uint32>(&BMediaRoster::GetFormatFor), "", py::arg("input"), py::arg("_inOutFormat"), py::arg("flags")=0)
.def("GetFormatFor", py::overload_cast<const media_node &, media_format *, float>(&BMediaRoster::GetFormatFor), "", py::arg("node"), py::arg("_inOutFormat"), py::arg("quality")=B_MEDIA_ANY_QUALITY)
.def("GetNodeAttributesFor", &BMediaRoster::GetNodeAttributesFor, "", py::arg("node"), py::arg("outArray"), py::arg("inMaxCount"))
.def("NodeIDFor", &BMediaRoster::NodeIDFor, "", py::arg("sourceOrDestinationPort"))
.def("GetInstancesFor", &BMediaRoster::GetInstancesFor, "", py::arg("addon"), py::arg("flavor"), py::arg("_id"), py::arg("_inOutCount")=NULL)
.def("AudioBufferSizeFor", &BMediaRoster::AudioBufferSizeFor, "", py::arg("channelCount"), py::arg("sampleFormat"), py::arg("frameRate"), py::arg("busType")=B_UNKNOWN_BUS)
.def_static("MediaFlags", &BMediaRoster::MediaFlags, "", py::arg("cap"), py::arg("buffer"), py::arg("maxSize"))
.def("MessageReceived", &BMediaRoster::MessageReceived, "", py::arg("message"))
.def("QuitRequested", &BMediaRoster::QuitRequested, "")
.def("ResolveSpecifier", &BMediaRoster::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("form"), py::arg("property"))
.def("GetSupportedSuites", &BMediaRoster::GetSupportedSuites, "", py::arg("data"))
;


}
