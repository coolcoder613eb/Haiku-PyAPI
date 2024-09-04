#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <media/MediaEventLooper.h>

namespace py = pybind11;
using namespace BPrivate;
using namespace BPrivate::media;

void define_MediaEventLooper(py::module_& m)
{
py::class_<BMediaEventLooper, BMediaNode>(m, "BMediaEventLooper")
;


}
