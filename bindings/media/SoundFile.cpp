#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <media/SoundFile.h>

namespace py = pybind11;
using namespace BPrivate;

void define_SoundFile(py::module_& m)
{
m.attr("B_UNKNOWN_FILE") = py::cast(B_UNKNOWN_FILE);
m.attr("B_AIFF_FILE") = py::cast(B_AIFF_FILE);
m.attr("B_WAVE_FILE") = py::cast(B_WAVE_FILE);
m.attr("B_UNIX_FILE") = py::cast(B_UNIX_FILE);

py::class_<BSoundFile>(m, "BSoundFile")
.def(py::init(), "")
.def(py::init<const entry_ref *, unsigned int>(), "", py::arg("ref"), py::arg("openMode"))
.def("InitCheck", &BSoundFile::InitCheck, "")
.def("SetTo", &BSoundFile::SetTo, "", py::arg("ref"), py::arg("openMode"))
.def("FileFormat", &BSoundFile::FileFormat, "")
.def("SamplingRate", &BSoundFile::SamplingRate, "")
.def("CountChannels", &BSoundFile::CountChannels, "")
.def("SampleSize", &BSoundFile::SampleSize, "")
.def("ByteOrder", &BSoundFile::ByteOrder, "")
.def("SampleFormat", &BSoundFile::SampleFormat, "")
.def("FrameSize", &BSoundFile::FrameSize, "")
.def("CountFrames", &BSoundFile::CountFrames, "")
.def("IsCompressed", &BSoundFile::IsCompressed, "")
.def("CompressionType", &BSoundFile::CompressionType, "")
.def("CompressionName", &BSoundFile::CompressionName, "")
.def("SetFileFormat", &BSoundFile::SetFileFormat, "", py::arg("format"))
.def("SetSamplingRate", &BSoundFile::SetSamplingRate, "", py::arg("fps"))
.def("SetChannelCount", &BSoundFile::SetChannelCount, "", py::arg("samplesPerFrame"))
.def("SetSampleSize", &BSoundFile::SetSampleSize, "", py::arg("bytesPerSample"))
.def("SetByteOrder", &BSoundFile::SetByteOrder, "", py::arg("byteOrder"))
.def("SetSampleFormat", &BSoundFile::SetSampleFormat, "", py::arg("format"))
.def("SetCompressionType", &BSoundFile::SetCompressionType, "", py::arg("type"))
.def("SetCompressionName", &BSoundFile::SetCompressionName, "", py::arg("name"))
.def("SetIsCompressed", &BSoundFile::SetIsCompressed, "", py::arg("compressed"))
.def("SetDataLocation", &BSoundFile::SetDataLocation, "", py::arg("offset"))
.def("SetFrameCount", &BSoundFile::SetFrameCount, "", py::arg("count"))
.def("ReadFrames", &BSoundFile::ReadFrames, "", py::arg("buffer"), py::arg("count"))
.def("WriteFrames", &BSoundFile::WriteFrames, "", py::arg("buffer"), py::arg("count"))
.def("SeekToFrame", &BSoundFile::SeekToFrame, "", py::arg("index"))
.def("FrameIndex", &BSoundFile::FrameIndex, "")
.def("FramesRemaining", &BSoundFile::FramesRemaining, "")
.def_readwrite("fSoundFile", &BSoundFile::fSoundFile, "")
;


}
