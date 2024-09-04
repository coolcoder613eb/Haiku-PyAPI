#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <media/BufferProducer.h>
#include <Region.h>

namespace py = pybind11;
using namespace BPrivate;
using namespace BPrivate::media;

PYBIND11_MODULE(BufferProducer, m)
{
//m.attr("BMediaRosterEx") = py::cast(BMediaRosterEx);

py::class_<BBufferProducer, BMediaNode, std::unique_ptr<BBufferProducer,py::nodelete>>(m, "BBufferProducer")
.def_static("ClipDataToRegion", &BBufferProducer::ClipDataToRegion, "", py::arg("format"), py::arg("size"), py::arg("data"), py::arg("region"))
.def("ProducerType", &BBufferProducer::ProducerType, "")
;


}
