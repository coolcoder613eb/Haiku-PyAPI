#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <media/BufferConsumer.h>
#include <Region.h>

namespace py = pybind11;
using namespace BPrivate;
using namespace BPrivate::media;

PYBIND11_MODULE(BufferConsumer, m)
{
//m.attr("BufferCache") = py::cast(BufferCache);

//m.attr("BMediaRosterEx") = py::cast(BMediaRosterEx);

py::class_<BBufferConsumer, BMediaNode, std::unique_ptr<BBufferConsumer,py::nodelete>>(m, "BBufferConsumer")
.def("ConsumerType", &BBufferConsumer::ConsumerType, "")
.def_static("RegionToClipData", &BBufferConsumer::RegionToClipData, "", py::arg("region"), py::arg("format"), py::arg("size"), py::arg("data"))
;


}
