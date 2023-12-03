#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/Shape.h>
#include <Archivable.h>
#include <Point.h>

namespace py = pybind11;
using namespace BPrivate;

PYBIND11_MODULE(Shape,m)
{
py::class_<BShapeIterator>(m, "BShapeIterator")
.def(py::init(), "")
.def("IterateMoveTo", &BShapeIterator::IterateMoveTo, "", py::arg("point"))
.def("IterateLineTo", &BShapeIterator::IterateLineTo, "", py::arg("lineCount"), py::arg("linePoints"))
.def("IterateBezierTo", &BShapeIterator::IterateBezierTo, "", py::arg("bezierCount"), py::arg("bezierPoints"))
.def("IterateClose", &BShapeIterator::IterateClose, "")
.def("IterateArcTo", [](BShapeIterator& self,bool largeArc,bool counterClockWise) {
    float  rx;
float  ry;
float  angle;
BPoint  point;
    status_t r = self.IterateArcTo(rx, ry, angle, largeArc, counterClockWise, point);
    return std::make_tuple(r,rx,ry,angle,point);
}
, "", py::arg("largeArc"), py::arg("counterClockWise"))
.def("Iterate", &BShapeIterator::Iterate, "", py::arg("shape"))
;

py::class_<BShape, BArchivable>(m, "BShape")
.def(py::init(), "")
.def(py::init<const BShape &>(), "", py::arg("other"))
.def(py::init<BMessage *>(), "", py::arg("archive"))
.def_static("Instantiate", &BShape::Instantiate, "", py::arg("archive"))
.def("Archive", &BShape::Archive, "", py::arg("archive"), py::arg("deep")=true)
.def("operator=", &BShape::operator=, "", py::arg("other"))
.def("__eq__", &BShape::operator==, "", py::arg("other"))
.def("__ne__", &BShape::operator!=, "", py::arg("other"))
.def("Clear", &BShape::Clear, "")
.def("Bounds", &BShape::Bounds, "")
.def("CurrentPosition", &BShape::CurrentPosition, "")
.def("AddShape", &BShape::AddShape, "", py::arg("other"))
.def("MoveTo", &BShape::MoveTo, "", py::arg("point"))
.def("LineTo", &BShape::LineTo, "", py::arg("linePoint"))
.def("BezierTo", py::overload_cast<BPoint[3]>(&BShape::BezierTo), "", py::arg("controlPoints"))
.def("BezierTo", py::overload_cast<const BPoint &, const BPoint &, const BPoint &>(&BShape::BezierTo), "", py::arg("control1"), py::arg("control2"), py::arg("endPoint"))
.def("ArcTo", &BShape::ArcTo, "", py::arg("rx"), py::arg("ry"), py::arg("angle"), py::arg("largeArc"), py::arg("counterClockWise"), py::arg("point"))
.def("Close", &BShape::Close, "")
;

//m.attr("ServerLink") = ServerLink;

//m.attr("PicturePlayer") = PicturePlayer;

}
