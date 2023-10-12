#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/AbstractLayout.h>
#include <Alignment.h>
#include <Layout.h>
#include <Size.h>

namespace py = pybind11;


PYBIND11_MODULE(AbstractLayout,m)
{
py::class_<BAbstractLayout, BLayout>(m, "BAbstractLayout");
}
