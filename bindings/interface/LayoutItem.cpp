#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/LayoutItem.h>
#include <Alignment.h>
#include <Archivable.h>
#include <Rect.h>
#include <Size.h>
#include <View.h>
#include <Layout.h>

namespace py = pybind11;


PYBIND11_MODULE(LayoutItem,m)
{
py::class_<BLayoutItem,std::unique_ptr<BLayoutItem, py::nodelete>>(m, "BLayoutItem");
}
