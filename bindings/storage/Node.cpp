#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <kernel/fs_attr.h>
#include <support/String.h>
#include <support/TypeConstants.h>
#include <Node.h>
#include <Statable.h>
#include <Entry.h>
#include <Directory.h>


namespace py = pybind11;
//using namespace BPrivate;
//using namespace BPrivate::Storage;
//using namespace BPrivate::Storage::Mime;

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
//PyBytes_FromObject
//.def("ReadAttr", &BNode::ReadAttr, "", py::arg("name"), py::arg("type"), py::arg("offset"), py::arg("buffer"), py::arg("length"))
.def("ReadAttr", [](BNode& self, const char* name, type_code type, off_t offset, void* buffer, size_t length)->PyObject*{ //void* buffer
		void* tmp = malloc(length);;
		ssize_t result = self.ReadAttr(name, type, offset, tmp, length);
		if (result > 0) {
			PyObject* ret;
			switch (type){
				case B_INT32_TYPE:
					ret = PyLong_FromVoidPtr(tmp);//*reinterpret_cast<int32_t*>(
					break;
				default:
					ret = PyLong_FromSsize_t(result);//*reinterpret_cast<int32_t*>(result));
					break;
			}
			return ret;
		} else {
			free(tmp);
			throw std::runtime_error("Errore durante la chiamata a ReadAttr");
		}
}, "", py::arg("name"), py::arg("type"), py::arg("offset"), py::arg("buffer"), py::arg("length"))
/*.def("ReadAttr", [](BNode& self, const char* name, type_code type, off_t offset, void* buffer, size_t length)-> std::pair<ssize_t, void*>{
	if (buffer == NULL){
		void* tmp = malloc(length);;
		ssize_t result = self.ReadAttr(name, type, offset, tmp, length);
		if (result > 0) {
			return {result,tmp};//std::string(buffer);
		} else {
			free(tmp);
			throw std::runtime_error("Errore durante la chiamata a ReadAttr");
		}
	} else {
		ssize_t result = self.ReadAttr(name, type, offset, buffer, length);
		if (result > 0) {
			return {result,buffer};
		} else {
			throw std::runtime_error("Errore durante la chiamata a ReadAttr");
		}
	}
}, "", py::arg("name"), py::arg("type"), py::arg("offset"), py::arg("buffer"), py::arg("length"))
*/
/*.def("ReadAttr", [](BNode& self, const char* name, type_code type, off_t offset, void* buffer, size_t length){
//as buffer being an output variable we use instead the return value of the function diverging from Haiku-Book references
		void* tmp = malloc(length);
		ssize_t result = self.ReadAttr(name, type, offset, tmp, length);
		if (result > 0) {
			PyObject* ret;
			switch (type){
				case B_INT32_TYPE: {
					//ret = PyLong_FromLong(*reinterpret_cast<int32_t*>(tmp));
					free(tmp);
					
					break;
				}
				/*default: {
					ret = PyLong_FromLong(*reinterpret_cast<int32_t*>(0));
					break;
				}*/
				/* ############################################
				return ret;
			}
			//std::string(buffer);
		} else {
			free(tmp);
			throw std::runtime_error("Errore durante la chiamata a ReadAttr");
		}
}, "", py::arg("name"), py::arg("type"), py::arg("offset"), py::arg("buffer"), py::arg("length"))*/
/*
.def("ReadAttr", [](BNode& self, const char* name, type_code type, off_t offset, PyObject* data, size_t length){
	if (data == NULL){
		void* tmp = malloc(length);;
		ssize_t result = self.ReadAttr(name, type, offset, tmp, length);
		if (result > 0) {
			PyObject* ret;
			switch (type){
				case B_INT32_TYPE: {
					// Turn the void* into an int* and put it into the PyObject
					ret = PyLong_FromLong(*reinterpret_cast<int32_t*>(tmp));
                    free(tmp);
                    break;
        		// and so on for each type_code...
    			}
    		return ret;
			}
			
			//return result;//tmp;//std::string(buffer);
		} else {
			free(tmp);
			return Py_None;
			throw std::runtime_error("Errore durante la chiamata a ReadAttr");
		}
	} else {
		ssize_t result = self.ReadAttr(name, type, offset, data, length);
		if (result > 0) {
			switch (type){
				case B_INT32_TYPE: {
					PyObject* pyInt = PyLong_FromLong(*reinterpret_cast<int32_t*>(data));
					Py_XINCREF(pyInt);  // Incrementa il riferimento all'oggetto Python
					data = pyInt;  // Assegna direttamente il risultato di PyLong_FromLong a data
					// Turn the void* into an int* and put it into the PyObject
					// *data = PyLong_FromLong(*reinterpret_cast<int32_t*>(data));//*(int32*)tmp;
					// free(tmp);
             		break;
				}
        		// and so on for each type_code...
    		}
			//return PyLong_FromLong(result); //tmp;//std::string(buffer);
		} else {
			
			throw std::runtime_error("Errore durante la chiamata a ReadAttr");

		}
		return PyLong_FromLong(result);
	}
}, "", py::arg("name"), py::arg("type"), py::arg("offset"), py::arg("buffer"), py::arg("length"))
*/
.def("RemoveAttr", &BNode::RemoveAttr, "", py::arg("name"))
.def("RenameAttr", &BNode::RenameAttr, "", py::arg("oldName"), py::arg("newName"))
//.def("GetAttrInfo", &BNode::GetAttrInfo, "", py::arg("name"), py::arg("info"))
//.def("GetAttrInfo", py::overload_cast<const char *, struct attr_info *>(&BNode::GetAttrInfo, py::const_), "", py::arg("name"), py::arg("info"))
/*.def("GetAttrInfo", [](BNode& self, const char* attr) -> std::pair<status_t, attr_info> {
    attr_info info;
    status_t result = self.GetAttrInfo(attr, &info);
    return {result, info};
}, "", py::arg("name"))
*/
.def("GetAttrInfo", [](BNode& self, const char* attr, struct attr_info* info){
	status_t result = self.GetAttrInfo(attr, info);
	if (result == 0) {
		return *info;
	} else {
		throw std::runtime_error("Errore durante la chiamata a GetAttrInfo");
	}
}, py::arg("attr"), py::arg("info")=attr_info())
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
