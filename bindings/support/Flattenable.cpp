#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/Flattenable.h>

namespace py = pybind11;


PYBIND11_MODULE(Flattenable, m)
{
py::class_<BFlattenable>(m, "BFlattenable")
.def("IsFixedSize", &BFlattenable::IsFixedSize, "")
.def("TypeCode", &BFlattenable::TypeCode, "")
.def("FlattenedSize", &BFlattenable::FlattenedSize, "")
//.def("Flatten", &BFlattenable::Flatten, "", py::arg("buffer"), py::arg("size"))
.def("Flatten", [](const BFlattenable& self) {
	ssize_t size = self.FlattenedSize();
	std::vector<char> buffer(size); 
	status_t status = self.Flatten(buffer.data(), size);
	//if (status != B_OK) { throw std::runtime_error("Flatten failed with status: " + std::to_string(status)); }
	return std::make_tuple(status,py::bytes(buffer.data(), size));
},"")
.def("AllowsTypeCode", &BFlattenable::AllowsTypeCode, "", py::arg("code"))
//.def("Unflatten", &BFlattenable::Unflatten, "", py::arg("code"), py::arg("buffer"), py::arg("size"))
.def("Unflatten", [](BFlattenable& self, type_code code, py::bytes data) {
	 // Convert py::bytes to a void* buffer 
	 std::string buffer = data; // py::bytes can be directly assigned to std::string 
	 ssize_t size = buffer.size();
	 status_t status = self.Unflatten(code, buffer.data(), size);
	 //if (status != B_OK) { throw std::runtime_error("Unflatten failed with status: " + std::to_string(status)); }
	 return status; },"",py::arg("code"),py::arg("data"))
;


}
