#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <media/Sound.h>

namespace py = pybind11;
using namespace BPrivate;

void define_Sound(py::module_& m)
{
m.attr("BTrackReader") = py::cast(BTrackReader);

py::class_<BSound>(m, "BSound")
.def(py::init<void *, size_t, const media_raw_audio_format &, bool>(), "", py::arg("data"), py::arg("size"), py::arg("format"), py::arg("freeWhenDone")=false)
.def(py::init<const entry_ref *, bool>(), "", py::arg("soundFile"), py::arg("loadIntoMemory")=false)
.def("InitCheck", &BSound::InitCheck, "")
.def("AcquireRef", &BSound::AcquireRef, "")
.def("ReleaseRef", &BSound::ReleaseRef, "")
.def("RefCount", &BSound::RefCount, "")
.def("Duration", &BSound::Duration, "")
.def("Format", &BSound::Format, "")
.def("Data", &BSound::Data, "")
.def("Size", &BSound::Size, "")
.def("GetDataAt", &BSound::GetDataAt, "", py::arg("offset"), py::arg("intoBuffer"), py::arg("bufferSize"), py::arg("outUsed"))
.def("BindTo", &BSound::BindTo, "", py::arg("player"), py::arg("format"))
.def("UnbindFrom", &BSound::UnbindFrom, "", py::arg("player"))
;


}
