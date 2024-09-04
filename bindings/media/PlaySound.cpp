#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <media/PlaySound.h>

namespace py = pybind11;
using namespace BPrivate;
using namespace BPrivate::media;

void define_PlaySound(py::module_& m)
{
m.def("play_sound", &play_sound, "", py::arg("soundRef"), py::arg("mix"), py::arg("queue"), py::arg("background"));

m.def("stop_sound", &stop_sound, "", py::arg("handle"));

m.def("wait_for_sound", &wait_for_sound, "", py::arg("handle"));

}
