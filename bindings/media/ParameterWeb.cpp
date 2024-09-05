#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <media/ParameterWeb.h>

namespace py = pybind11;
using namespace BPrivate;
using namespace BPrivate::media;


PYBIND11_MODULE(ParameterWeb, m)
{
py::enum_<media_parameter_flags>(m, "media_parameter_flags", "")
.value("B_HIDDEN_PARAMETER", media_parameter_flags::B_HIDDEN_PARAMETER, "")
.value("B_ADVANCED_PARAMETER", media_parameter_flags::B_ADVANCED_PARAMETER, "")
.export_values();
/*from ParameterWeb.cpp media kit source
const char * const B_GENERIC			 = "";
const char * const B_MASTER_GAIN		 = "Master";
const char * const B_GAIN				 = "Gain";
const char * const B_BALANCE			 = "Balance";
const char * const B_FREQUENCY			 = "Frequency";
const char * const B_LEVEL				 = "Level";
const char * const B_SHUTTLE_SPEED		 = "Speed";
const char * const B_CROSSFADE			 = "XFade";
const char * const B_EQUALIZATION		 = "EQ";
const char * const B_COMPRESSION		 = "Compression";
const char * const B_QUALITY			 = "Quality";
const char * const B_BITRATE			 = "Bitrate";
const char * const B_GOP_SIZE			 = "GOPSize";
const char * const B_MUTE				 = "Mute";
const char * const B_ENABLE				 = "Enable";
const char * const B_INPUT_MUX			 = "Input";
const char * const B_OUTPUT_MUX			 = "Output";
const char * const B_TUNER_CHANNEL		 = "Channel";
const char * const B_TRACK				 = "Track";
const char * const B_RECSTATE			 = "RecState";
const char * const B_SHUTTLE_MODE		 = "Shuttle";
const char * const B_RESOLUTION			 = "Resolution";
const char * const B_COLOR_SPACE		 = "Colorspace";
const char * const B_FRAME_RATE			 = "FrameRate";
const char * const B_VIDEO_FORMAT		 = "VideoFormat";
const char * const B_WEB_PHYSICAL_INPUT	 = "PhysInput";
const char * const B_WEB_PHYSICAL_OUTPUT = "PhysOutput";
const char * const B_WEB_ADC_CONVERTER	 = "ADC";
const char * const B_WEB_DAC_CONVERTER	 = "DAC";
const char * const B_WEB_LOGICAL_INPUT	 = "LogInput";
const char * const B_WEB_LOGICAL_OUTPUT	 = "LogOutput";
const char * const B_WEB_LOGICAL_BUS	 = "LogBus";
const char * const B_WEB_BUFFER_INPUT	 = "DataInput";
const char * const B_WEB_BUFFER_OUTPUT	 = "DataOutput";
const char * const B_SIMPLE_TRANSPORT	 = "SimpleTransport";*/
m.attr("B_GENERIC") = "";//py::cast(B_GENERIC);

m.attr("B_MASTER_GAIN") = "Master";//py::cast(B_MASTER_GAIN);

m.attr("B_GAIN") = "Gain";//py::cast(B_GAIN);

m.attr("B_BALANCE") = "Balance";//py::cast(B_BALANCE);

m.attr("B_FREQUENCY") = "Frequency";//py::cast(B_FREQUENCY);

m.attr("B_LEVEL") = "Level";//py::cast(B_LEVEL);

m.attr("B_SHUTTLE_SPEED") = "Speed";//py::cast(B_SHUTTLE_SPEED);

m.attr("B_CROSSFADE") = "XFade";//py::cast(B_CROSSFADE);

m.attr("B_EQUALIZATION") = "EQ";//py::cast(B_EQUALIZATION);

m.attr("B_COMPRESSION") = "Compression";//py::cast(B_COMPRESSION);

m.attr("B_QUALITY") = "Quality";//py::cast(B_QUALITY);

m.attr("B_BITRATE") = "Bitrate";//py::cast(B_BITRATE);

m.attr("B_GOP_SIZE") = "GOPSize";//py::cast(B_GOP_SIZE);

m.attr("B_MUTE") = "Mute";//py::cast(B_MUTE);

m.attr("B_ENABLE") = "Enable";//py::cast(B_ENABLE);

m.attr("B_INPUT_MUX") = "Input";//py::cast(B_INPUT_MUX);

m.attr("B_OUTPUT_MUX") = "Output";//py::cast(B_OUTPUT_MUX);

m.attr("B_TUNER_CHANNEL") = "Channel";//py::cast(B_TUNER_CHANNEL);

m.attr("B_TRACK") = "Track";//py::cast(B_TRACK);

m.attr("B_RECSTATE") = "RecState";//py::cast(B_RECSTATE);

m.attr("B_SHUTTLE_MODE") = "Shuttle";//py::cast(B_SHUTTLE_MODE);

m.attr("B_RESOLUTION") = "Resolution";//py::cast(B_RESOLUTION);

m.attr("B_COLOR_SPACE") = "Colorspace";//py::cast(B_COLOR_SPACE);

m.attr("B_FRAME_RATE") = "FrameRate";//py::cast(B_FRAME_RATE);

m.attr("B_VIDEO_FORMAT") = "VideoFormat";//py::cast(B_VIDEO_FORMAT);

m.attr("B_WEB_PHYSICAL_INPUT") = "PhysInput";//py::cast(B_WEB_PHYSICAL_INPUT);

m.attr("B_WEB_PHYSICAL_OUTPUT") = "PhysOutput";//py::cast(B_WEB_PHYSICAL_OUTPUT);

m.attr("B_WEB_ADC_CONVERTER") = "ADC";//py::cast(B_WEB_ADC_CONVERTER);

m.attr("B_WEB_DAC_CONVERTER") = "DAC";//py::cast(B_WEB_DAC_CONVERTER);

m.attr("B_WEB_LOGICAL_INPUT") = "LogInput";//py::cast(B_WEB_LOGICAL_INPUT);

m.attr("B_WEB_LOGICAL_OUTPUT") = "LogOutput";//py::cast(B_WEB_LOGICAL_OUTPUT);

m.attr("B_WEB_LOGICAL_BUS") = "LogBus";//py::cast(B_WEB_LOGICAL_BUS);

m.attr("B_WEB_BUFFER_INPUT") = "DataInput";//py::cast(B_WEB_BUFFER_INPUT);

m.attr("B_WEB_BUFFER_OUTPUT") = "DataOutput";//py::cast(B_WEB_BUFFER_OUTPUT);

m.attr("B_SIMPLE_TRANSPORT") = "SimpleTransport";//py::cast(B_SIMPLE_TRANSPORT);

//m.attr("BContinuousParameter") = py::cast(BContinuousParameter);

py::class_<BParameterWeb, BFlattenable, std::unique_ptr<BParameterWeb,py::nodelete>>(m, "BParameterWeb")
.def(py::init(), "")
.def("Node", &BParameterWeb::Node, "")
.def("MakeGroup", &BParameterWeb::MakeGroup, "", py::arg("name"))
.def("CountGroups", &BParameterWeb::CountGroups, "")
.def("GroupAt", &BParameterWeb::GroupAt, "", py::arg("index"))
.def("CountParameters", &BParameterWeb::CountParameters, "")
.def("ParameterAt", &BParameterWeb::ParameterAt, "", py::arg("index"))
.def("IsFixedSize", &BParameterWeb::IsFixedSize, "")
.def("TypeCode", &BParameterWeb::TypeCode, "")
.def("FlattenedSize", &BParameterWeb::FlattenedSize, "")
.def("Flatten", &BParameterWeb::Flatten, "", py::arg("buffer"), py::arg("size"))
.def("AllowsTypeCode", &BParameterWeb::AllowsTypeCode, "", py::arg("code"))
.def("Unflatten", &BParameterWeb::Unflatten, "", py::arg("code"), py::arg("buffer"), py::arg("size"))
;

py::class_<BParameterGroup, BFlattenable, std::unique_ptr<BParameterGroup,py::nodelete>>(m, "BParameterGroup")
.def("Web", &BParameterGroup::Web, "")
.def("Name", &BParameterGroup::Name, "")
.def("SetFlags", &BParameterGroup::SetFlags, "", py::arg("flags"))
.def("Flags", &BParameterGroup::Flags, "")
.def("MakeNullParameter", &BParameterGroup::MakeNullParameter, "", py::arg("id"), py::arg("type"), py::arg("name"), py::arg("kind"))
.def("MakeContinuousParameter", &BParameterGroup::MakeContinuousParameter, "", py::arg("id"), py::arg("type"), py::arg("name"), py::arg("kind"), py::arg("unit"), py::arg("min"), py::arg("max"), py::arg("step"))
.def("MakeDiscreteParameter", &BParameterGroup::MakeDiscreteParameter, "", py::arg("id"), py::arg("type"), py::arg("name"), py::arg("kind"))
.def("MakeTextParameter", &BParameterGroup::MakeTextParameter, "", py::arg("id"), py::arg("type"), py::arg("name"), py::arg("kind"), py::arg("maxBytes"))
.def("MakeGroup", &BParameterGroup::MakeGroup, "", py::arg("name"))
.def("CountParameters", &BParameterGroup::CountParameters, "")
.def("ParameterAt", &BParameterGroup::ParameterAt, "", py::arg("index"))
.def("CountGroups", &BParameterGroup::CountGroups, "")
.def("GroupAt", &BParameterGroup::GroupAt, "", py::arg("index"))
.def("IsFixedSize", &BParameterGroup::IsFixedSize, "")
.def("TypeCode", &BParameterGroup::TypeCode, "")
.def("FlattenedSize", &BParameterGroup::FlattenedSize, "")
.def("Flatten", &BParameterGroup::Flatten, "", py::arg("buffer"), py::arg("size"))
.def("AllowsTypeCode", &BParameterGroup::AllowsTypeCode, "", py::arg("code"))
.def("Unflatten", &BParameterGroup::Unflatten, "", py::arg("code"), py::arg("buffer"), py::arg("size"))
;

py::class_<BParameter, BFlattenable, std::unique_ptr<BParameter,py::nodelete>>(m, "BParameter")
.def("Type", &BParameter::Type, "")
.def("Web", &BParameter::Web, "")
.def("Group", &BParameter::Group, "")
.def("Name", &BParameter::Name, "")
.def("Kind", &BParameter::Kind, "")
.def("Unit", &BParameter::Unit, "")
.def("ID", &BParameter::ID, "")
.def("SetFlags", &BParameter::SetFlags, "", py::arg("flags"))
.def("Flags", &BParameter::Flags, "")
.def("ValueType", &BParameter::ValueType, "")
.def("GetValue", &BParameter::GetValue, "", py::arg("buffer"), py::arg("_size"), py::arg("_when"))
.def("SetValue", &BParameter::SetValue, "", py::arg("buffer"), py::arg("size"), py::arg("when"))
.def("CountChannels", &BParameter::CountChannels, "")
.def("SetChannelCount", &BParameter::SetChannelCount, "", py::arg("count"))
.def("MediaType", &BParameter::MediaType, "")
.def("SetMediaType", &BParameter::SetMediaType, "", py::arg("type"))
.def("CountInputs", &BParameter::CountInputs, "")
.def("InputAt", &BParameter::InputAt, "", py::arg("index"))
.def("AddInput", &BParameter::AddInput, "", py::arg("input"))
.def("CountOutputs", &BParameter::CountOutputs, "")
.def("OutputAt", &BParameter::OutputAt, "", py::arg("index"))
.def("AddOutput", &BParameter::AddOutput, "", py::arg("output"))
.def("IsFixedSize", &BParameter::IsFixedSize, "")
.def("TypeCode", &BParameter::TypeCode, "")
.def("FlattenedSize", &BParameter::FlattenedSize, "")
.def("Flatten", &BParameter::Flatten, "", py::arg("buffer"), py::arg("size"))
.def("AllowsTypeCode", &BParameter::AllowsTypeCode, "", py::arg("code"))
.def("Unflatten", &BParameter::Unflatten, "", py::arg("code"), py::arg("buffer"), py::arg("size"))
;

py::class_<BContinuousParameter, BParameter, std::unique_ptr<BContinuousParameter,py::nodelete>>(m, "BContinuousParameter")
.def("ValueType", &BContinuousParameter::ValueType, "")
.def("MinValue", &BContinuousParameter::MinValue, "")
.def("MaxValue", &BContinuousParameter::MaxValue, "")
.def("ValueStep", &BContinuousParameter::ValueStep, "")
.def("SetResponse", &BContinuousParameter::SetResponse, "", py::arg("response"), py::arg("factor"), py::arg("offset"))
.def("GetResponse", &BContinuousParameter::GetResponse, "", py::arg("_response"), py::arg("factor"), py::arg("offset"))
.def("FlattenedSize", &BContinuousParameter::FlattenedSize, "")
.def("Flatten", &BContinuousParameter::Flatten, "", py::arg("buffer"), py::arg("size"))
.def("Unflatten", &BContinuousParameter::Unflatten, "", py::arg("code"), py::arg("buffer"), py::arg("size"))
;

py::class_<BDiscreteParameter, BParameter, std::unique_ptr<BDiscreteParameter,py::nodelete>>(m, "BDiscreteParameter")
.def("ValueType", &BDiscreteParameter::ValueType, "")
.def("CountItems", &BDiscreteParameter::CountItems, "")
.def("ItemNameAt", &BDiscreteParameter::ItemNameAt, "", py::arg("index"))
.def("ItemValueAt", &BDiscreteParameter::ItemValueAt, "", py::arg("index"))
.def("AddItem", &BDiscreteParameter::AddItem, "", py::arg("value"), py::arg("name"))
.def("MakeItemsFromInputs", &BDiscreteParameter::MakeItemsFromInputs, "")
.def("MakeItemsFromOutputs", &BDiscreteParameter::MakeItemsFromOutputs, "")
.def("MakeEmpty", &BDiscreteParameter::MakeEmpty, "")
.def("FlattenedSize", &BDiscreteParameter::FlattenedSize, "")
.def("Flatten", &BDiscreteParameter::Flatten, "", py::arg("buffer"), py::arg("size"))
.def("Unflatten", &BDiscreteParameter::Unflatten, "", py::arg("code"), py::arg("buffer"), py::arg("size"))
;

py::class_<BTextParameter, BParameter, std::unique_ptr<BTextParameter,py::nodelete>>(m, "BTextParameter")
.def("ValueType", &BTextParameter::ValueType, "")
.def("MaxBytes", &BTextParameter::MaxBytes, "")
.def("FlattenedSize", &BTextParameter::FlattenedSize, "")
.def("Flatten", &BTextParameter::Flatten, "", py::arg("buffer"), py::arg("size"))
.def("Unflatten", &BTextParameter::Unflatten, "", py::arg("code"), py::arg("buffer"), py::arg("size"))
;

py::class_<BNullParameter, BParameter, std::unique_ptr<BNullParameter,py::nodelete>>(m, "BNullParameter")
.def("ValueType", &BNullParameter::ValueType, "")
.def("FlattenedSize", &BNullParameter::FlattenedSize, "")
.def("Flatten", &BNullParameter::Flatten, "", py::arg("buffer"), py::arg("size"))
.def("Unflatten", &BNullParameter::Unflatten, "", py::arg("code"), py::arg("buffer"), py::arg("size"))
;


}
