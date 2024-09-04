#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <media/FileInterface.h>

namespace py = pybind11;
using namespace BPrivate;
using namespace BPrivate::media;

void define_FileInterface(py::module_& m)
{
py::class_<BFileInterface, BMediaNode>(m, "BFileInterface")
;


}
