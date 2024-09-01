#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/BlockCache.h>

namespace py = pybind11;


PYBIND11_MODULE(BlockCache, m)
{
m.attr("B_OBJECT_CACHE") = 0;//py::cast(B_OBJECT_CACHE);
m.attr("B_MALLOC_CACHE") = 1;//py::cast(B_MALLOC_CACHE);

py::class_<BBlockCache>(m, "BBlockCache")
.def(py::init<uint32, size_t, uint32>(), "", py::arg("blockCount"), py::arg("blockSize"), py::arg("allocationType"))
.def("Get", &BBlockCache::Get, "", py::arg("blockSize"))
.def("Save", &BBlockCache::Save, "", py::arg("pointer"), py::arg("blockSize"))
;


}
