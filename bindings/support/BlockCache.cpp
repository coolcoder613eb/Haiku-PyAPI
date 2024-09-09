#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/BlockCache.h>

namespace py = pybind11;

/*
py::bytes Get_wrapper(size_t blockSize) { 
	void* data = Get(blockSize);
	py::buffer buffer;
	
	if (data == nullptr) { 
		throw std::runtime_error("Failed to get data");
	}
	return py::bytes(static_cast<const char*>(data), blockSize);
}*/
py::bytes Get_wrapper2(BBlockCache& self, size_t blockSize) {
	void* data = self.Get(blockSize);
	if (data == nullptr) {
		throw std::runtime_error("Failed to get data");
	}
	py::buffer_info buf_info(static_cast<char*>(data), sizeof(char), py::format_descriptor<char>::format(), 1, {blockSize}, {sizeof(char)} );
	//return py::array(buf_info);
	return py::bytes(static_cast<const char*>(buf_info.ptr), buf_info.size * buf_info.itemsize); //convert py::buffer to py::bytes
};

PYBIND11_MODULE(BlockCache, m)
{
m.attr("B_OBJECT_CACHE") = 0;//py::cast(B_OBJECT_CACHE);
m.attr("B_MALLOC_CACHE") = 1;//py::cast(B_MALLOC_CACHE);

py::class_<BBlockCache>(m, "BBlockCache")
.def(py::init<uint32, size_t, uint32>(), "", py::arg("blockCount"), py::arg("blockSize"), py::arg("allocationType"))
//.def("Get", &BBlockCache::Get, "", py::arg("blockSize"))//TODO this returns a void * -- let's return a py::bytes or a py::buffer
.def("Get", &Get_wrapper2, "", py::arg("blockSize"))
.def("Get2", [](BBlockCache& self, size_t blockSize)->py::tuple{
	std::vector<char>buffer(blockSize);
	void* data = self.Get(blockSize);
	if (data != nullptr) {
	std::memcpy(buffer.data(), data, blockSize);
	}
	py::bytes pyBytes(buffer.data(),blockSize);
	return py::make_tuple(pyBytes, blockSize);
},"",py::arg("blockSize"))
//.def("Save", &BBlockCache::Save, "", py::arg("pointer"), py::arg("blockSize"))//TODO: pointer is a void * -> python can't use void *
.def("Save", [](BBlockCache& self, py::bytes data) {//if we pass a py::bytes we already pass the size along with data right?
/*	std::string byt = py::str(data);
	void* pointer = static_cast<void*>(const_cast<char*>(byt.data()));
	self.Save(pointer, byt.size());*/
	char* pointer;
	ssize_t size;
	PYBIND11_BYTES_AS_STRING_AND_SIZE(data.ptr(), &pointer, &size);
	self.Save(static_cast<void*>(pointer), static_cast<size_t>(size));
	},"", py::arg("data"))
.def("Save_from_buffer", [](BBlockCache& self, py::buffer py_buffer){
	py::buffer_info buf_info = py_buffer.request();
	void* pointer = buf_info.ptr;
	//size_t blockSize = buf_info.size * buf_info.itemsize;
	size_t blockSize = buf_info.size;
	self.Save(pointer, blockSize);
},"",py::arg("py_buffer"))
;


}
