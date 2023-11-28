#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/SupportDefs.h>

namespace py = pybind11;


void define_SupportDefs(py::module_& m)
{
m.attr("B_EMPTY_STRING") = py::cast(B_EMPTY_STRING);

m.def("get_stack_frame", &get_stack_frame, "", py::arg(""));

m.def_static("atomic_set", py::overload_cast<int, int>(&atomic_set), "", py::arg("value"), py::arg("newValue"));

m.def_static("atomic_get_and_set", py::overload_cast<int, int>(&atomic_get_and_set), "", py::arg("value"), py::arg("newValue"));

m.def_static("atomic_test_and_set", py::overload_cast<int, int, int>(&atomic_test_and_set), "", py::arg("value"), py::arg("newValue"), py::arg("testAgainst"));

m.def_static("atomic_add", py::overload_cast<int, int>(&atomic_add), "", py::arg("value"), py::arg("addValue"));

m.def_static("atomic_and", py::overload_cast<int, int>(&atomic_and), "", py::arg("value"), py::arg("andValue"));

m.def_static("atomic_or", py::overload_cast<int, int>(&atomic_or), "", py::arg("value"), py::arg("orValue"));

m.def_static("atomic_get", py::overload_cast<int>(&atomic_get), "", py::arg("value"));

m.def_static("atomic_set64", py::overload_cast<int64_t, int64_t>(&atomic_set64), "", py::arg("value"), py::arg("newValue"));

m.def_static("atomic_get_and_set64", py::overload_cast<int64_t, int64_t>(&atomic_get_and_set64), "", py::arg("value"), py::arg("newValue"));

m.def_static("atomic_test_and_set64", py::overload_cast<int64_t, int64_t, int64_t>(&atomic_test_and_set64), "", py::arg("value"), py::arg("newValue"), py::arg("testAgainst"));

m.def_static("atomic_add64", py::overload_cast<int64_t, int64_t>(&atomic_add64), "", py::arg("value"), py::arg("addValue"));

m.def_static("atomic_and64", py::overload_cast<int64_t, int64_t>(&atomic_and64), "", py::arg("value"), py::arg("andValue"));

m.def_static("atomic_or64", py::overload_cast<int64_t, int64_t>(&atomic_or64), "", py::arg("value"), py::arg("orValue"));

m.def_static("atomic_get64", py::overload_cast<int64_t>(&atomic_get64), "", py::arg("value"));

m.def("atomic_set", py::overload_cast<int, int>(&atomic_set), "", py::arg("value"), py::arg("newValue"));

m.def("atomic_get_and_set", py::overload_cast<int, int>(&atomic_get_and_set), "", py::arg("value"), py::arg("newValue"));

m.def("atomic_test_and_set", py::overload_cast<int, int, int>(&atomic_test_and_set), "", py::arg("value"), py::arg("newValue"), py::arg("testAgainst"));

m.def("atomic_add", py::overload_cast<int, int>(&atomic_add), "", py::arg("value"), py::arg("addValue"));

m.def("atomic_and", py::overload_cast<int, int>(&atomic_and), "", py::arg("value"), py::arg("andValue"));

m.def("atomic_or", py::overload_cast<int, int>(&atomic_or), "", py::arg("value"), py::arg("orValue"));

m.def("atomic_get", py::overload_cast<int>(&atomic_get), "", py::arg("value"));

m.def("atomic_set64", py::overload_cast<int64_t, int64_t>(&atomic_set64), "", py::arg("value"), py::arg("newValue"));

m.def("atomic_get_and_set64", py::overload_cast<int64_t, int64_t>(&atomic_get_and_set64), "", py::arg("value"), py::arg("newValue"));

m.def("atomic_test_and_set64", py::overload_cast<int64_t, int64_t, int64_t>(&atomic_test_and_set64), "", py::arg("value"), py::arg("newValue"), py::arg("testAgainst"));

m.def("atomic_add64", py::overload_cast<int64_t, int64_t>(&atomic_add64), "", py::arg("value"), py::arg("addValue"));

m.def("atomic_and64", py::overload_cast<int64_t, int64_t>(&atomic_and64), "", py::arg("value"), py::arg("andValue"));

m.def("atomic_or64", py::overload_cast<int64_t, int64_t>(&atomic_or64), "", py::arg("value"), py::arg("orValue"));

m.def("atomic_get64", py::overload_cast<int64_t>(&atomic_get64), "", py::arg("value"));

}
