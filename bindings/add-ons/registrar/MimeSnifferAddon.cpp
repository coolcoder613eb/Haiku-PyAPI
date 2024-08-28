#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <add-ons/registrar/MimeSnifferAddon.h>
//#include <SupportDefs.h>
#include <MimeType.h>
namespace py = pybind11;

class PyBMimeSnifferAddon : public BMimeSnifferAddon{
	public:
        using BMimeSnifferAddon::BMimeSnifferAddon;
        size_t				MinimalBufferSize() override {
            PYBIND11_OVERLOAD(size_t, BMimeSnifferAddon, MinimalBufferSize);
        }
        float				GuessMimeType(const char* fileName, BMimeType* type) override {
            PYBIND11_OVERLOAD(float, BMimeSnifferAddon, GuessMimeType, fileName, type);
        }
        float				GuessMimeType(BFile* file, const void* buffer, int32 length, BMimeType* type) override {
            PYBIND11_OVERLOAD(float, BMimeSnifferAddon, GuessMimeType, file, buffer, length, type);
        }
};

PYBIND11_MODULE(MimeSnifferAddon, m)
{
py::class_<BMimeSnifferAddon,PyBMimeSnifferAddon>(m, "BMimeSnifferAddon")
.def(py::init(), "")
.def("MinimalBufferSize", &BMimeSnifferAddon::MinimalBufferSize, "")
.def("GuessMimeType", py::overload_cast<const char *, BMimeType *>(&BMimeSnifferAddon::GuessMimeType), "", py::arg("fileName"), py::arg("type"))
.def("GuessMimeType", py::overload_cast<BFile *, const void *, int32, BMimeType *>(&BMimeSnifferAddon::GuessMimeType), "", py::arg("file"), py::arg("buffer"), py::arg("length"), py::arg("type"))
;


}
