#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/ByteOrder.h>

namespace py = pybind11;


void define_ByteOrder(py::module_& m)
{
py::enum_<swap_action>(m, "swap_action", "")
.value("B_SWAP_HOST_TO_LENDIAN", swap_action::B_SWAP_HOST_TO_LENDIAN, "")
.value("B_SWAP_HOST_TO_BENDIAN", swap_action::B_SWAP_HOST_TO_BENDIAN, "")
.value("B_SWAP_LENDIAN_TO_HOST", swap_action::B_SWAP_LENDIAN_TO_HOST, "")
.value("B_SWAP_BENDIAN_TO_HOST", swap_action::B_SWAP_BENDIAN_TO_HOST, "")
.value("B_SWAP_ALWAYS", swap_action::B_SWAP_ALWAYS, "")
.export_values();

m.def("swap_data", &swap_data, "", py::arg("type"), py::arg("data"), py::arg("length"), py::arg("action"));

m.def("is_type_swapped", &is_type_swapped, "", py::arg("type"));

m.def("__swap_double", &__swap_double, "", py::arg("arg"));

m.def("__swap_float", &__swap_float, "", py::arg("arg"));

m.def("__swap_int64", &__swap_int64, "", py::arg("arg"));

m.def("__swap_int32", &__swap_int32, "", py::arg("arg"));

m.def("__swap_int16", &__swap_int16, "", py::arg("arg"));

}
