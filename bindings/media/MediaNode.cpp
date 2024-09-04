#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>
#include <pybind11/numpy.h>

#include <media/MediaNode.h>
#include <media/TimeSource.h>
#include <media/MediaAddOn.h>

namespace py = pybind11;
using namespace BPrivate;
using namespace BPrivate::media;

std::string get_live_node_info_name(const live_node_info& self) {
    return std::string(self.name);
}

void set_live_node_info_name(live_node_info& self, const std::string& name) {
    std::strncpy(self.name, name.c_str(), B_MEDIA_NAME_LENGTH - 1);
    self.name[B_MEDIA_NAME_LENGTH - 1] = '\0';
}

std::string get_media_output_name(const media_output& self) {
    return std::string(self.name);
}

void set_media_output_name(media_output& self, const std::string& name) {
    std::strncpy(self.name, name.c_str(), B_MEDIA_NAME_LENGTH - 1);
    self.name[B_MEDIA_NAME_LENGTH - 1] = '\0';
}

std::string get_media_input_name(const media_input& self) {
    return std::string(self.name);
}

void set_media_input_name(media_input& self, const std::string& name) {
    std::strncpy(self.name, name.c_str(), B_MEDIA_NAME_LENGTH - 1);
    self.name[B_MEDIA_NAME_LENGTH - 1] = '\0';
}

PYBIND11_MODULE(MediaNode, m)
{
//m.attr("TimeSourceObject") = py::cast(TimeSourceObject);

//m.attr("SystemTimeSourceObject") = py::cast(SystemTimeSourceObject);

//m.attr("BMediaRosterEx") = py::cast(BMediaRosterEx);

py::class_<media_node>(m, "media_node")
.def(py::init(), "")
.def_readwrite("node", &media_node::node, "")
.def_readwrite("port", &media_node::port, "")
.def_readwrite("kind", &media_node::kind, "")
//.def_readwrite("null", &media_node::null, "")
;

py::class_<media_input>(m, "media_input")
.def(py::init(), "")
.def_readwrite("node", &media_input::node, "")
.def_readwrite("source", &media_input::source, "")
.def_readwrite("destination", &media_input::destination, "")
.def_readwrite("format", &media_input::format, "")
//.def_readwrite("name", &media_input::name, "")
.def_property("name", &get_media_input_name, &set_media_input_name, "")
;

py::class_<media_output>(m, "media_output")
.def(py::init(), "")
.def_readwrite("node", &media_output::node, "")
.def_readwrite("source", &media_output::source, "")
.def_readwrite("destination", &media_output::destination, "")
.def_readwrite("format", &media_output::format, "")
//.def_readwrite("name", &media_output::name, "")
.def_property("name", &get_media_output_name, &set_media_output_name, "")
;

py::class_<live_node_info>(m, "live_node_info")
.def(py::init(), "")
.def_readwrite("node", &live_node_info::node, "")
.def_readwrite("hint_point", &live_node_info::hint_point, "")
//.def_readwrite("name", &live_node_info::name, "")
.def_property("name", &get_live_node_info_name, &set_live_node_info_name, "")
;

py::class_<media_request_info>(m, "media_request_info")
.def_readwrite("what", &media_request_info::what, "")
.def_readwrite("change_tag", &media_request_info::change_tag, "")
.def_readwrite("status", &media_request_info::status, "")
.def_readwrite("cookie", &media_request_info::cookie, "")
.def_readwrite("user_data", &media_request_info::user_data, "")
.def_readwrite("source", &media_request_info::source, "")
.def_readwrite("destination", &media_request_info::destination, "")
.def_readwrite("format", &media_request_info::format, "")
//.def_readwrite("_reserved_", &media_request_info::_reserved_, "")
.def_property(
            "_reserved_",
            [](const media_request_info &info) {
                py::array_t<uint32> result(32);
                std::memcpy(result.mutable_data(), &info._reserved_, sizeof(info._reserved_));
                return result;
            },
            [](media_request_info &info, py::array_t<uint32> value) {
                if (value.size() != 32) {
                    throw std::runtime_error("Array must have size 32");
                }
                std::memcpy(&info._reserved_, value.data(), sizeof(info._reserved_));
            },"")
;

py::class_<media_node_attribute>(m, "media_node_attribute")
.def_readwrite("what", &media_node_attribute::what, "")
.def_readwrite("flags", &media_node_attribute::flags, "")
.def_readwrite("data", &media_node_attribute::data, "")
;

py::class_<BMediaNode, std::unique_ptr<BMediaNode,py::nodelete>>(m, "BMediaNode")
.def("Acquire", &BMediaNode::Acquire, "")
.def("Release", &BMediaNode::Release, "")
.def("Name", &BMediaNode::Name, "")
.def("ID", &BMediaNode::ID, "")
.def("Kinds", &BMediaNode::Kinds, "")
.def("Node", &BMediaNode::Node, "")
.def("RunMode", &BMediaNode::RunMode, "")
.def("TimeSource", &BMediaNode::TimeSource, "")
.def("ControlPort", &BMediaNode::ControlPort, "")
.def("AddOn", &BMediaNode::AddOn, "", py::arg("internalID"))
.def("HandleMessage", &BMediaNode::HandleMessage, "", py::arg("message"), py::arg("data"), py::arg("size"))
.def("HandleBadMessage", &BMediaNode::HandleBadMessage, "", py::arg("code"), py::arg("buffer"), py::arg("size"))
.def("AddNodeKind", &BMediaNode::AddNodeKind, "", py::arg("kind"))
//.def("operatornew", py::overload_cast<size_t>(&BMediaNode::operatornew), "", py::arg("size"))
//.def("operatornew", py::overload_cast<size_t, const std::nothrow_t>(&BMediaNode::operatornew), "", py::arg("size"), py::arg("&"))
//.def("operatordelete", py::overload_cast<void *>(&BMediaNode::operatordelete), "", py::arg("ptr"))
//.def("operatordelete", py::overload_cast<void *, const std::nothrow_t>(&BMediaNode::operatordelete), "", py::arg("ptr"), py::arg("&"))
.def("GetNodeAttributes", &BMediaNode::GetNodeAttributes, "", py::arg("_attributes"), py::arg("inMaxCount"))
.def("AddTimer", &BMediaNode::AddTimer, "", py::arg("atPerformanceTime"), py::arg("cookie"))
;


}
