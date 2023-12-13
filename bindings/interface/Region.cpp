#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/Region.h>
#include <Rect.h>

namespace py = pybind11;
using namespace BPrivate;

PYBIND11_MODULE(Region,m)
{
//m.attr("ServerLink") = ServerLink;

//m.attr("LinkReceiver") = LinkReceiver;

py::class_<clipping_rect>(m, "clipping_rect")
.def_readwrite("left", &clipping_rect::left, "")
.def_readwrite("top", &clipping_rect::top, "")
.def_readwrite("right", &clipping_rect::right, "")
.def_readwrite("bottom", &clipping_rect::bottom, "")
;

py::class_<BRegion>(m, "BRegion")
.def(py::init(), "")
.def(py::init<const BRegion &>(), "", py::arg("other"))
.def(py::init<const BRect>(), "", py::arg("rect"))
.def("operator=", &BRegion::operator=, "", py::arg("other"))
.def("__eq__", &BRegion::operator==, "", py::arg("other"))
.def("Set", py::overload_cast<BRect>(&BRegion::Set), "", py::arg("rect"))
.def("Set", py::overload_cast<clipping_rect>(&BRegion::Set), "", py::arg("clipping"))
.def("Frame", &BRegion::Frame, "")
.def("FrameInt", &BRegion::FrameInt, "")
.def("RectAt", py::overload_cast<int32>(&BRegion::RectAt), "", py::arg("index"))
.def("RectAt", py::overload_cast<int32>(&BRegion::RectAt), "", py::arg("index"))
.def("RectAtInt", py::overload_cast<int32>(&BRegion::RectAtInt), "", py::arg("index"))
.def("RectAtInt", py::overload_cast<int32>(&BRegion::RectAtInt), "", py::arg("index"))
.def("CountRects", py::overload_cast<>(&BRegion::CountRects), "")
.def("CountRects", py::overload_cast<>(&BRegion::CountRects), "")
.def("Intersects", py::overload_cast<BRect>(&BRegion::Intersects, py::const_), "", py::arg("rect"))
.def("Intersects", py::overload_cast<clipping_rect>(&BRegion::Intersects, py::const_), "", py::arg("clipping"))
.def("Contains", py::overload_cast<BPoint>(&BRegion::Contains, py::const_), "", py::arg("point"))
.def("Contains", py::overload_cast<int32, int32>(&BRegion::Contains), "", py::arg("x"), py::arg("y"))
.def("Contains", py::overload_cast<int32, int32>(&BRegion::Contains), "", py::arg("x"), py::arg("y"))
.def("PrintToStream", &BRegion::PrintToStream, "")
.def("OffsetBy", py::overload_cast<const BPoint &>(&BRegion::OffsetBy), "", py::arg("point"))
.def("OffsetBy", py::overload_cast<int32, int32>(&BRegion::OffsetBy), "", py::arg("x"), py::arg("y"))
.def("ScaleBy", py::overload_cast<BSize>(&BRegion::ScaleBy), "", py::arg("scale"))
.def("ScaleBy", py::overload_cast<float, float>(&BRegion::ScaleBy), "", py::arg("x"), py::arg("y"))
.def("MakeEmpty", &BRegion::MakeEmpty, "")
.def("Include", py::overload_cast<BRect>(&BRegion::Include), "", py::arg("rect"))
.def("Include", py::overload_cast<clipping_rect>(&BRegion::Include), "", py::arg("clipping"))
.def("Include", py::overload_cast<const BRegion *>(&BRegion::Include), "", py::arg("region"))
.def("Exclude", py::overload_cast<BRect>(&BRegion::Exclude), "", py::arg("rect"))
.def("Exclude", py::overload_cast<clipping_rect>(&BRegion::Exclude), "", py::arg("clipping"))
.def("Exclude", py::overload_cast<const BRegion *>(&BRegion::Exclude), "", py::arg("region"))
.def("IntersectWith", &BRegion::IntersectWith, "", py::arg("region"))
.def("ExclusiveInclude", &BRegion::ExclusiveInclude, "", py::arg("region"))
;


}
