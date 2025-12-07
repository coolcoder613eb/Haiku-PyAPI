#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/Polygon.h>
#include <InterfaceDefs.h>
#include <Rect.h>

namespace py = pybind11;


PYBIND11_MODULE(Polygon,m)
{
py::class_<BPolygon>(m, "BPolygon")
.def(py::init<const BPoint *, int>(), "", py::arg("points"), py::arg("count"))
.def(py::init<const BPolygon &>(), "", py::arg("other"))
.def(py::init<const BPolygon *>(), "", py::arg("other"))
.def(py::init(), "")
.def("__copy__", &BPolygon::operator=, "", py::arg("other"))
.def("Frame", &BPolygon::Frame, "")
.def("AddPoints", &BPolygon::AddPoints, "", py::arg("points"), py::arg("count"))
.def("CountPoints", &BPolygon::CountPoints, "")
.def("MapTo", &BPolygon::MapTo, "", py::arg("source"), py::arg("destination"))
.def("PrintToStream", &BPolygon::PrintToStream, "")
;


}
