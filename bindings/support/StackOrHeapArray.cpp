#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/StackOrHeapArray.h>

namespace py = pybind11;


void define_StackOrHeapArray(py::module_& m)
{
py::class_<BStackOrHeapArray>(m, "BStackOrHeapArray")
.def(py::init<size_t>(), "", py::arg("count"))
.def("IsValid", &BStackOrHeapArray::IsValid, "")
.def("operatorType*", &BStackOrHeapArray::operatorType*, "")
;


}
