#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <pybind11/functional.h> // Per std::function
#include <drivers/bus_manager.h>

namespace py = pybind11;
/*
PYBIND11_MODULE(bus_manager, m)
{
py::class_<bus_manager_info>(m, "bus_manager_info")
.def_readwrite("minfo", &bus_manager_info::minfo, "")
.def_readwrite("rescan", &bus_manager_info::rescan, "")
;


}
*/


// Binding con pybind11
PYBIND11_MODULE(bus_manager, m)
{
py::class_<bus_manager_info>(m, "BusManagerInfo")
        .def(py::init<>())
        .def_readwrite("minfo", &bus_manager_info::minfo, "")
        //.def_readwrite("rescan", &bus_manager_info::rescan)
        .def("rescan", [](bus_manager_info& self) {
            if (self.rescan) {
                return self.rescan();
            }
            return static_cast<status_t>(-1); // Errore se rescan non è impostato
        })
;
}
