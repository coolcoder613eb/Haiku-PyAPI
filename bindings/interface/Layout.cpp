#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/Layout.h>
#include <Alignment.h>
#include <Archivable.h>
#include <LayoutItem.h>
#include <List.h>
#include <Size.h>
#include <View.h>
#include <LayoutContext.h>

namespace py = pybind11;


PYBIND11_MODULE(Layout,m)
{
py::class_<BLayout, BLayoutItem>(m, "BLayout");
}
