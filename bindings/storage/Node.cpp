#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>
#include <pybind11/chrono.h>

#include <kernel/fs_attr.h>
#include <support/String.h>
#include <support/TypeConstants.h>
#include <Node.h>
#include <Statable.h>
#include <Entry.h>
#include <Directory.h>


namespace py = pybind11;


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
//.def("ReadAttr", py::overload_cast<const char*, type_code, off_t, void*, size_t>(&ReadAttrWrapper), "", py::arg("name"), py::arg("type"), py::arg("offset"), py::arg("buffer"), py::arg("length"))
//.def("ReadAttr", &BNode::ReadAttr, "", py::arg("name"), py::arg("type"), py::arg("offset"), py::arg("buffer"), py::arg("length"))
.def("ReadAttr", [](BNode& self, const char* name, type_code type, off_t offset, void* buffer, size_t length)->py::object{
		void* tmp = malloc(length);
		if (tmp == nullptr){
			throw std::runtime_error("Error allocating memory");
		}
		ssize_t result = self.ReadAttr(name, type, offset, tmp, length);
		if (result < 0) {
			free(tmp);
			throw std::runtime_error("Error calling ReadAttr");
		}
		py::object ret;
		switch (type) {
			//test Int64 for reinterpretation in int32*
			case B_INT64_TYPE:
			case B_INT32_TYPE:
			case B_INT16_TYPE:
			case B_INT8_TYPE:
				ret = py::int_(*reinterpret_cast<int32*>(PyLong_AsVoidPtr(PyLong_FromVoidPtr(tmp))));
				break;
			case B_STRING_TYPE:
			case B_MIME_STRING_TYPE:
			case B_ASCII_TYPE:
				ret = py::str(static_cast<const char*>(tmp));
				//ret = PyUnicode_FromString(static_cast<const char*>(tmp));
				break;
			case B_BOOL_TYPE:
				/*int32* inttmpPtr = reinterpret_cast<int32*>(PyLong_AsVoidPtr(PyLong_FromVoidPtr(tmp)));
				if (inttmpPtr == nullptr) {
					free(tmp);
					throw std::runtime_error("Error converting PyLong object to int32*");
				}
				ret = py::bool_(*inttmpPtr != 0);
				break;*/
				ret = py::bool_(PyBool_FromLong(*reinterpret_cast<int32*>(PyLong_AsVoidPtr(PyLong_FromVoidPtr(tmp)))));
				break;
			case B_FLOAT_TYPE:
				ret = py::float_(*reinterpret_cast<float*>(tmp));
				break;
			case B_DOUBLE_TYPE:
				ret = py::float_(*reinterpret_cast<double*>(tmp));
				break;
			case B_TIME_TYPE:{
				bigtime_t timeValue = *reinterpret_cast<bigtime_t*>(tmp);
				std::chrono::system_clock::time_point timePoint =
				std::chrono::system_clock::time_point(std::chrono::seconds(timeValue));
				// Calcola il tempo trascorso dalla mezzanotte del 1 gennaio 1970 in secondi
				auto seconds_since_epoch = std::chrono::duration_cast<std::chrono::seconds>(timePoint.time_since_epoch()).count();
				ret = py::module::import("datetime").attr("datetime").attr("fromtimestamp")(seconds_since_epoch);
    			break;
				/*
				bigtime_t timeValue=*reinterpret_cast<bigtime_t*>(tmp);
				std::chrono::system_clock::time_point timePoint = std::chrono::system_clock::from_time_t(timeValue / 1000000);
				ret = py::module::import("datetime").attr("datetime").attr("fromtimestamp")(std::chrono::system_clock::to_time_t(timePoint));
				break;*/
			}
			default:
				ret = py::none();
				break;
		}
		free(tmp);
		return ret;
		//return py::reinterpret_steal<py::object>(ret);
}, "", py::arg("name"), py::arg("type"), py::arg("offset"), py::arg("buffer")=NULL, py::arg("length"))		
/*
.def("ReadAttr", [](BNode& self, const char* name, type_code type, off_t offset, void* buffer, size_t length)->py::object{
		void* tmp = malloc(length);
		self.ReadAttr(name, type, offset, tmp, length);
		PyObject* ret;
		long intVal;
		char* strPtr = strdup("");
		bool boolPtr;
		switch (type){
				case B_INT32_TYPE:
					ret = PyLong_FromVoidPtr(tmp);
					if (ret == nullptr) {
						free(tmp);
						throw std::runtime_error("Errore durante la chiamata a ReadAttr");
					}
					// Converte l'oggetto PyObject* in un puntatore a int*
					int32* intPtr;
					intPtr = reinterpret_cast<int32*>(PyLong_AsVoidPtr(ret));
					intVal = py::int_(*intPtr);
					free(intPtr);
					//intVal = PyLong_AsLong(ret);
					Py_DECREF(ret); // Decrementa il riferimento all'oggetto PyObject* (non più necessario)
			        // Restituisci il puntatore a intPtr invece dell'oggetto PyObject*
					break;
				case B_STRING_TYPE:
					ret = PyUnicode_FromString(static_cast<const char*>(tmp));
					free(tmp); // Libera la memoria allocata con malloc
					if (ret == nullptr) {
						throw std::runtime_error("Errore durante la chiamata a ReadAttr");
					}
					// Converte l'oggetto PyObject* in un puntatore a char*
					strPtr = strdup(PyUnicode_AsUTF8(ret));
					if (strPtr == nullptr) {
						Py_DECREF(ret);
						throw std::runtime_error("Errore durante la conversione dell'oggetto PyUnicode a char*");
					}
					Py_DECREF(ret); // Decrementa il riferimento all'oggetto PyObject*
					break;
				case B_BOOL_TYPE:
					ret = PyLong_FromVoidPtr(tmp);
					int32* intPtr;
					intPtr = reinterpret_cast<int32*>(PyLong_AsVoidPtr(ret));
					boolPtr = PyBool_FromLong(*intPtr);
					
				default:
					//ret = PyLong_FromSsize_t(result);//*reinterpret_cast<int32_t*>(result));
					//intPtr = 0;
					free(tmp);
					break;
		}
		if (type == B_STRING_TYPE){
			return py::str(strPtr);
		} else if (type == B_INT32_TYPE){
			return py::int_(intVal);
		} else if (type == B_BOOL_TYPE){
			return py::bool_(boolPtr);
		}
		return py::none();
		
}, "", py::arg("name"), py::arg("type"), py::arg("offset"), py::arg("buffer")=NULL, py::arg("length"))*/

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
