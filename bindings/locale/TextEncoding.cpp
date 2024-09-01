#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <locale/TextEncoding.h>

namespace py = pybind11;
using namespace BPrivate;

void define_TextEncoding(py::module_& m)
{
py::class_<BTextEncoding>(m, "BTextEncoding")
.def(py::init<BString>(), "", py::arg("name"))
.def(py::init<const char *, size_t>(), "", py::arg("data"), py::arg("length"))
.def("InitCheck", &BTextEncoding::InitCheck, "")
.def("GetName", &BTextEncoding::GetName, "")
.def("Encode", [](BTextEncoding& self,const char * input,char * output) {
    size_t  inputLength;
size_t  outputLength;
    status_t r = self.Encode(input, inputLength, output, outputLength);
    return std::make_tuple(r,inputLength,outputLength);
}
, "", py::arg("input"), py::arg("output"))
.def("Decode", [](BTextEncoding& self,const char * input,char * output) {
    size_t  inputLength;
size_t  outputLength;
    status_t r = self.Decode(input, inputLength, output, outputLength);
    return std::make_tuple(r,inputLength,outputLength);
}
, "", py::arg("input"), py::arg("output"))
.def("Flush", [](BTextEncoding& self,char * output) {
    size_t  outputLength;
    status_t r = self.Flush(output, outputLength);
    return std::make_tuple(r,outputLength);
}
, "", py::arg("output"))
;


}
