#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>
#include <pybind11/numpy.h>

#include <media/MediaAddOn.h>
#include <media/MediaNode.h>
#include <MimeType.h>


namespace py = pybind11;
using namespace BPrivate;
using namespace BPrivate::media;

std::string get_dormant_node_info_name(const dormant_node_info& self) {
    return std::string(self.name);
}

void set_dormant_node_info_name(dormant_node_info& self, const std::string& name) {
    std::strncpy(self.name, name.c_str(), B_MEDIA_NAME_LENGTH - 1);
    self.name[B_MEDIA_NAME_LENGTH - 1] = '\0';
}

//std::pair<status_t, std::string> InitCheck(BMediaAddOn& self){
//std::pair<status_t, std::vector<char *>> InitCheck_wrapper(BMediaAddOn& self){
py::tuple InitCheck_wrapper(BMediaAddOn& self){
	/*
	const std::vector<char*> _failureText;
	const char** failureText;
	//const char* failureText = nullptr;
	//status_t status = self.InitCheck(failureText);
	status_t status = self.InitCheck(failureText);
	
	//return {status, failureText ? std::string(failureText) : ""};
	//return {status, _failureText};
	return py::make_tuple(status,_failureText);
	*/
	
	
	const char ** failureText;
    std::vector<char*> _failureText;
    status_t status = self.InitCheck(failureText);
    // Assume che la fine dell'array sia segnata da un puntatore nullo
    for (size_t i = 0; failureText[i] != nullptr; ++i) {
        _failureText.push_back(const_cast<char*>(failureText[i]));
    }

    return py::make_tuple(status,_failureText);
}

PYBIND11_MODULE(MediaAddOn, m)
{
m.attr("B_FLAVOR_IS_GLOBAL") = 0x100000L;//py::cast(B_FLAVOR_IS_GLOBAL);
m.attr("B_FLAVOR_IS_LOCAL") = 0x200000L;//py::cast(B_FLAVOR_IS_LOCAL);

//m.attr("DormantNodeManager") = py::cast(DormantNodeManager);

py::class_<dormant_node_info>(m, "dormant_node_info")
.def(py::init(), "")
.def_readwrite("addon", &dormant_node_info::addon, "")
.def_readwrite("flavor_id", &dormant_node_info::flavor_id, "")
//.def_readwrite("name", &dormant_node_info::name, "")
.def_property("name", &get_dormant_node_info_name,&set_dormant_node_info_name,"")
;

py::class_<flavor_info>(m, "flavor_info")
.def_readwrite("name", &flavor_info::name, "")
.def_readwrite("info", &flavor_info::info, "")
.def_readwrite("kinds", &flavor_info::kinds, "")
.def_readwrite("flavor_flags", &flavor_info::flavor_flags, "")
.def_readwrite("internal_id", &flavor_info::internal_id, "")
.def_readwrite("possible_count", &flavor_info::possible_count, "")
.def_readwrite("in_format_count", &flavor_info::in_format_count, "")
.def_readwrite("in_format_flags", &flavor_info::in_format_flags, "")
.def_readwrite("in_formats", &flavor_info::in_formats, "")
.def_readwrite("out_format_count", &flavor_info::out_format_count, "")
.def_readwrite("out_format_flags", &flavor_info::out_format_flags, "")
.def_readwrite("out_formats", &flavor_info::out_formats, "")
//.def_readwrite("_reserved_", &flavor_info::_reserved_, "")
.def_property(
            "_reserved_",
            [](const flavor_info &info) {
                py::array_t<uint32> result(16);
                std::memcpy(result.mutable_data(), &info._reserved_, sizeof(info._reserved_));
                return result;
            },
            [](flavor_info &info, py::array_t<uint32> value) {
                if (value.size() != 16) {
                    throw std::runtime_error("Array must have size 16");
                }
                std::memcpy(&info._reserved_, value.data(), sizeof(info._reserved_));
            },"")
;

py::class_<dormant_flavor_info, flavor_info, BFlattenable>(m, "dormant_flavor_info")
.def(py::init(), "")
.def(py::init<const dormant_flavor_info &>(), "", py::arg("other"))
.def("operator=", py::overload_cast<const dormant_flavor_info &>(&dormant_flavor_info::operator=), "", py::arg("other"))
.def("operator=", py::overload_cast<const flavor_info &>(&dormant_flavor_info::operator=), "", py::arg("other"))
.def("set_name", &dormant_flavor_info::set_name, "", py::arg("name"))
.def("set_info", &dormant_flavor_info::set_info, "", py::arg("info"))
.def("add_in_format", &dormant_flavor_info::add_in_format, "", py::arg("format"))
.def("add_out_format", &dormant_flavor_info::add_out_format, "", py::arg("format"))
.def("IsFixedSize", &dormant_flavor_info::IsFixedSize, "")
.def("TypeCode", &dormant_flavor_info::TypeCode, "")
.def("FlattenedSize", &dormant_flavor_info::FlattenedSize, "")
.def("Flatten", &dormant_flavor_info::Flatten, "", py::arg("buffer"), py::arg("size")) //TODO: handle buffer
.def("Unflatten", &dormant_flavor_info::Unflatten, "", py::arg("type"), py::arg("buffer"), py::arg("size")) //TODO: handle buffer
.def_readwrite("node_info", &dormant_flavor_info::node_info, "")
;

py::class_<BMediaAddOn>(m, "BMediaAddOn")
.def(py::init<image_id>(), "", py::arg("image"))
//.def("InitCheck", &BMediaAddOn::InitCheck, "", py::arg("_failureText"))
.def("InitCheck",&InitCheck_wrapper, "")
.def("CountFlavors", &BMediaAddOn::CountFlavors, "")
//.def("GetFlavorAt", &BMediaAddOn::GetFlavorAt, "", py::arg("index"), py::arg("_info"))
.def("GetFlavorAt", [](BMediaAddOn& self, int32 index) {
	const flavor_info* _info = nullptr;
	status_t result = self.GetFlavorAt(index,&_info);
	if (result == B_OK && _info != nullptr) {
		return py::make_tuple(result, py::cast(_info, py::return_value_policy::reference)); 
	} else {
		return py::make_tuple(result, py::none()); 
	}
},"")
.def("InstantiateNodeFor", &BMediaAddOn::InstantiateNodeFor, "", py::arg("info"), py::arg("config"), py::arg("_error"))
.def("GetConfigurationFor", &BMediaAddOn::GetConfigurationFor, "", py::arg("yourNode"), py::arg("intoMessage"))
.def("WantsAutoStart", &BMediaAddOn::WantsAutoStart, "")
//.def("AutoStart", &BMediaAddOn::AutoStart, "", py::arg("index"), py::arg("_node"), py::arg("_internalID"), py::arg("_hasMore"))
.def("AutoStart", [](BMediaAddOn& self, int index) { 
	BMediaNode* node = nullptr;
	int32 internalID = 0;
	bool hasMore = false;
	status_t result = self.AutoStart(index, &node, &internalID, &hasMore);
	return std::make_tuple(result, node, internalID, hasMore);
},"")
.def("SniffRef", &BMediaAddOn::SniffRef, "", py::arg("file"), py::arg("ioMimeType"), py::arg("_quality"), py::arg("_internalID"))
.def("SniffType", &BMediaAddOn::SniffType, "", py::arg("type"), py::arg("_quality"), py::arg("_internalID"))
.def("GetFileFormatList", &BMediaAddOn::GetFileFormatList, "", py::arg("forNodeFlavorID"), py::arg("_writableFormats"), py::arg("writableFormatsCount"), py::arg("_writableFormatsTotalCount"), py::arg("_readableFormats"), py::arg("readableFormatsCount"), py::arg("_readableFormatsTotalCount"), py::arg("_reserved"))
.def("SniffTypeKind", &BMediaAddOn::SniffTypeKind, "", py::arg("type"), py::arg("kinds"), py::arg("_quality"), py::arg("_internalID"), py::arg("_reserved"))
.def("ImageID", &BMediaAddOn::ImageID, "")
.def("AddonID", &BMediaAddOn::AddonID, "")
;

//m.def("make_media_addon", &make_media_addon, "", py::arg("yourImage")); //TODO: where is this? cannot find it normally it calls return new MediaAddOn(imageid); that returns a BMediaAddOn*

}
