#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/BlockCache.h>

namespace py = pybind11;


void define_BlockCache(py::module_& m)
{
m.attr("B_OBJECT_CACHE") = py::cast(B_OBJECT_CACHE);
m.attr("B_MALLOC_CACHE") = py::cast(B_MALLOC_CACHE);

py::class_<BBlockCache>(m, "BBlockCache")
.def(py::init<unsigned int, size_t, unsigned int>(), "", py::arg("blockCount"), py::arg("blockSize"), py::arg("allocationType"))
.def("Get", &BBlockCache::Get, "", py::arg("blockSize"))
.def("Save", &BBlockCache::Save, "", py::arg("pointer"), py::arg("blockSize"))
;


}
