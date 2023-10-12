#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/TwoDimensionalLayout.h>
#include <AbstractLayout.h>

namespace py = pybind11;


PYBIND11_MODULE(TwoDimensionalLayout,m)
{
py::class_<BTwoDimensionalLayout, BAbstractLayout>(m, "BTwoDimensionalLayout");
}
