#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/Size.h>
#include <limits.h>
#include <SupportDefs.h>

namespace py = pybind11;


PYBIND11_MODULE(Size,m)
{
m.attr("B_SIZE_UNSET") = "- 2";
m.attr("B_SIZE_UNLIMITED") = "1024 * 1024 * 1024";

py::class_<BSize>(m, "BSize")
.def(py::init(), "")
.def(py::init<const BSize &>(), "", py::arg("other"))
.def(py::init<float, float>(), "", py::arg("width"), py::arg("height"))
.def("Width", &BSize::Width, "")
.def("Height", &BSize::Height, "")
.def("Set", &BSize::Set, "", py::arg("width"), py::arg("height"))
.def("SetWidth", &BSize::SetWidth, "", py::arg("width"))
.def("SetHeight", &BSize::SetHeight, "", py::arg("height"))
.def("IntegerWidth", &BSize::IntegerWidth, "")
.def("IntegerHeight", &BSize::IntegerHeight, "")
.def("IsWidthSet", &BSize::IsWidthSet, "")
.def("IsHeightSet", &BSize::IsHeightSet, "")
.def("__eq__", &BSize::operator==, "", py::arg("other"))
.def("__ne__", &BSize::operator!=, "", py::arg("other"))
.def("__copy__", &BSize::operator=, "", py::arg("other"))
.def_readwrite("width", &BSize::width, "")
.def_readwrite("height", &BSize::height, "")
;

//m.def("__eq__", &operator==, "", py::arg("other"));

//m.def("__ne__", &operator!=, "", py::arg("other"));

//m.def("operator=", &operator=, "", py::arg("other"));

}
