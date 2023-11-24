#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <kernel/fs_attr.h>
#include <support/String.h>
#include <Node.h>
#include <Statable.h>
#include <Entry.h>
#include <Directory.h>


namespace py = pybind11;
using namespace BPrivate;
using namespace BPrivate::Storage;
using namespace BPrivate::Storage::Mime;


PYBIND11_MODULE(Node,m)
{
py::class_<node_ref>(m, "node_ref")
.def(py::init(), "")
.def(py::init<dev_t, ino_t>(), "", py::arg("device"), py::arg("node"))
.def(py::init<const node_ref &>(), "", py::arg("other"))
.def("__eq__", &node_ref::operator==, "", py::arg("other"))
.def("__ne__", &node_ref::operator!=, "", py::arg("other"))
.def("__lt__", &node_ref::operator<, "", py::arg("other"))
.def("operator=", &node_ref::operator=, "", py::arg("other"))
.def_readwrite("device", &node_ref::device, "")
.def_readwrite("node", &node_ref::node, "")
;

py::class_<BNode>(m, "BNode") //Commented out BStatable verify if needed
.def(py::init(), "")
.def(py::init<const entry_ref *>(), "", py::arg("ref"))
.def(py::init<const BEntry *>(), "", py::arg("entry"))
.def(py::init<const char *>(), "", py::arg("path"))
.def(py::init<const BDirectory *, const char *>(), "", py::arg("dir"), py::arg("path"))
.def(py::init<const BNode &>(), "", py::arg("node"))
.def("InitCheck", &BNode::InitCheck, "")
.def("GetStat", &BNode::GetStat, "", py::arg("st"))
.def("SetTo", py::overload_cast<const entry_ref *>(&BNode::SetTo), "", py::arg("ref"))
.def("SetTo", py::overload_cast<const BEntry *>(&BNode::SetTo), "", py::arg("entry"))
.def("SetTo", py::overload_cast<const char *>(&BNode::SetTo), "", py::arg("path"))
.def("SetTo", py::overload_cast<const BDirectory *, const char *>(&BNode::SetTo), "", py::arg("dir"), py::arg("path"))
.def("Unset", &BNode::Unset, "")
.def("Lock", &BNode::Lock, "")
.def("Unlock", &BNode::Unlock, "")
.def("Sync", &BNode::Sync, "")
.def("WriteAttr", &BNode::WriteAttr, "", py::arg("name"), py::arg("type"), py::arg("offset"), py::arg("buffer"), py::arg("length"))
.def("ReadAttr", &BNode::ReadAttr, "", py::arg("name"), py::arg("type"), py::arg("offset"), py::arg("buffer"), py::arg("length"))
.def("RemoveAttr", &BNode::RemoveAttr, "", py::arg("name"))
.def("RenameAttr", &BNode::RenameAttr, "", py::arg("oldName"), py::arg("newName"))
//.def("GetAttrInfo", &BNode::GetAttrInfo, "", py::arg("name"), py::arg("info"))
.def("GetAttrInfo", py::overload_cast<const char *, struct attr_info *>(&BNode::GetAttrInfo, py::const_), "", py::arg("name"), py::arg("info"))
//.def("GetNextAttrName", &BNode::GetNextAttrName, "",py::arg("buffer"))
//.def("GetNextAttrName", py::overload_cast<char *>(&BNode::GetNextAttrName), "",py::arg("buffer"))
.def("GetNextAttrName", [](BNode& self, char* buffer){
	status_t result = self.GetNextAttrName(buffer);
	if (result == 0) {
		return std::string(buffer);
	} else {
		throw std::runtime_error("Errore durante la chiamata a GetNextAttrName");
	}
}, py::arg("buffer")="")//, py::return_value_policy::reference_internal
.def("RewindAttrs", &BNode::RewindAttrs, "")
.def("WriteAttrString", &BNode::WriteAttrString, "", py::arg("name"), py::arg("data"))
.def("ReadAttrString", &BNode::ReadAttrString, "", py::arg("name"), py::arg("result"))
.def("operator=", &BNode::operator=, "", py::arg("node"))
.def("__eq__", &BNode::operator==, "", py::arg("node"))
.def("__ne__", &BNode::operator!=, "", py::arg("node"))
.def("Dup", &BNode::Dup, "")
;

}
