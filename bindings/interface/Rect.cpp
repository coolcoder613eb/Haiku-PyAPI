#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/Rect.h>
#include <math.h>
#include <Point.h>
#include <Size.h>

namespace py = pybind11;


PYBIND11_MODULE(Rect,m)
{
py::class_<BRect>(m, "BRect")
.def(py::init(), "")
.def(py::init<const BRect &>(), "", py::arg("other"))
.def(py::init<float, float, float, float>(), "", py::arg("left"), py::arg("top"), py::arg("right"), py::arg("bottom"))
.def(py::init<BPoint, BPoint>(), "", py::arg("leftTop"), py::arg("rightBottom"))
.def(py::init<BPoint, BSize>(), "", py::arg("leftTop"), py::arg("size"))
.def(py::init<float>(), "", py::arg("side"))
.def("operator=", &BRect::operator=, "", py::arg("other"))
.def("Set", &BRect::Set, "", py::arg("left"), py::arg("top"), py::arg("right"), py::arg("bottom"))
.def("PrintToStream", &BRect::PrintToStream, "")
.def("LeftTop", &BRect::LeftTop, "")
.def("RightBottom", &BRect::RightBottom, "")
.def("LeftBottom", &BRect::LeftBottom, "")
.def("RightTop", &BRect::RightTop, "")
.def("SetLeftTop", &BRect::SetLeftTop, "", py::arg("point"))
.def("SetRightBottom", &BRect::SetRightBottom, "", py::arg("point"))
.def("SetLeftBottom", &BRect::SetLeftBottom, "", py::arg("point"))
.def("SetRightTop", &BRect::SetRightTop, "", py::arg("point"))
.def("InsetBy", py::overload_cast<BPoint>(&BRect::InsetBy), "", py::arg("inset"))
.def("InsetBy", py::overload_cast<float, float>(&BRect::InsetBy), "", py::arg("dx"), py::arg("dy"))
.def("OffsetBy", py::overload_cast<BPoint>(&BRect::OffsetBy), "", py::arg("delta"))
.def("OffsetBy", py::overload_cast<float, float>(&BRect::OffsetBy), "", py::arg("dx"), py::arg("dy"))
.def("OffsetTo", py::overload_cast<BPoint>(&BRect::OffsetTo), "", py::arg("offset"))
.def("OffsetTo", py::overload_cast<float, float>(&BRect::OffsetTo), "", py::arg("x"), py::arg("y"))
.def("InsetBySelf", py::overload_cast<BPoint>(&BRect::InsetBySelf), "", py::arg("inset"))
.def("InsetBySelf", py::overload_cast<float, float>(&BRect::InsetBySelf), "", py::arg("dx"), py::arg("dy"))
.def("InsetByCopy", py::overload_cast<BPoint>(&BRect::InsetByCopy, py::const_), "", py::arg("inset"))
.def("InsetByCopy", py::overload_cast<float, float>(&BRect::InsetByCopy, py::const_), "", py::arg("dx"), py::arg("dy"))
.def("OffsetBySelf", py::overload_cast<BPoint>(&BRect::OffsetBySelf), "", py::arg("offset"))
.def("OffsetBySelf", py::overload_cast<float, float>(&BRect::OffsetBySelf), "", py::arg("dx"), py::arg("dy"))
.def("OffsetByCopy", py::overload_cast<BPoint>(&BRect::OffsetByCopy, py::const_), "", py::arg("offset"))
.def("OffsetByCopy", py::overload_cast<float, float>(&BRect::OffsetByCopy, py::const_), "", py::arg("dx"), py::arg("dy"))
.def("OffsetToSelf", py::overload_cast<BPoint>(&BRect::OffsetToSelf), "", py::arg("offset"))
.def("OffsetToSelf", py::overload_cast<float, float>(&BRect::OffsetToSelf), "", py::arg("x"), py::arg("y"))
.def("OffsetToCopy", py::overload_cast<BPoint>(&BRect::OffsetToCopy, py::const_), "", py::arg("offset"))
.def("OffsetToCopy", py::overload_cast<float, float>(&BRect::OffsetToCopy, py::const_), "", py::arg("x"), py::arg("y"))
.def("__eq__", &BRect::operator==, "", py::arg("other"))
.def("__ne__", &BRect::operator!=, "", py::arg("other"))
.def("__and__", &BRect::operator&, "", py::arg("other"))
.def("__or__", &BRect::operator|, "", py::arg("other"))
// added by TmTFx 
.def("__repr__", [](const BRect& r) {
    return "BRect(" +
        std::to_string(r.left) + ", " +
        std::to_string(r.top) + ", " +
        std::to_string(r.right) + ", " +
        std::to_string(r.bottom) + ")";
})
.def("IsValid", &BRect::IsValid, "")
.def("Width", &BRect::Width, "")
.def("IntegerWidth", &BRect::IntegerWidth, "")
.def("Height", &BRect::Height, "")
.def("IntegerHeight", &BRect::IntegerHeight, "")
.def("Size", &BRect::Size, "")
.def("Intersects", &BRect::Intersects, "", py::arg("rect"))
.def("Contains", py::overload_cast<BPoint>(&BRect::Contains, py::const_), "", py::arg("point"))
.def("Contains", py::overload_cast<BRect>(&BRect::Contains, py::const_), "", py::arg("rect"))
.def_readwrite("left", &BRect::left, "")
.def_readwrite("top", &BRect::top, "")
.def_readwrite("right", &BRect::right, "")
.def_readwrite("bottom", &BRect::bottom, "")
;

//m.def("operator=", &operator=, "", py::arg("other"));

}
