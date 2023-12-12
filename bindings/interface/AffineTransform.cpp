#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/AffineTransform.h>
#include <Flattenable.h>
#include <Point.h>
#include <math.h>

namespace py = pybind11;
/*
class PyBAffineTransform : public BAffineTransform {
public:
    using BAffineTransform::BAffineTransform;
    bool					IsFixedSize() const override{
        PYBIND11_OVERLOAD(bool, BAffineTransform, IsFixedSize);
    }
    type_code				TypeCode() const override{
        PYBIND11_OVERLOAD(type_code, BAffineTransform, TypeCode);
    }
    ssize_t					FlattenedSize() const override{
        PYBIND11_OVERLOAD(ssize_t, BAffineTransform, FlattenedSize);
    }
    status_t				Flatten(void* buffer, ssize_t size) const override{
        PYBIND11_OVERLOAD(status_t, BAffineTransform, Flatten, buffer, size);
    }
    status_t				Unflatten(type_code code, const void* buffer, ssize_t size) override{
        PYBIND11_OVERLOAD(status_t, BAffineTransform, Unflatten, code, buffer, size);
    }
//    static double getKDefaultEpsilon() {
//        return BAffineTransform::kDefaultEpsilon;
//    }
};*/

class AltBAffineTransform : public BAffineTransform {
public:
    using BAffineTransform::BAffineTransform;
	static double getKDefaultEpsilon() {
        return BAffineTransform::kDefaultEpsilon;
    }
};

#if __cplusplus < 201103L
	static	const double			kDefaultEpsilon = 1e-14;
#else
	static	constexpr double		kDefaultEpsilon = 1e-14;
#endif

PYBIND11_MODULE(AffineTransform,m)
{
//m.attr("B_AFFINE_IDENTITY_TRANSFORM") = B_AFFINE_IDENTITY_TRANSFORM;
//m.attr("kDefaultEpsilon") = 1e-14;
py::class_<BAffineTransform, BFlattenable>(m, "BAffineTransform")
.def(py::init(), "")
.def(py::init<double, double, double, double, double, double>(), "", py::arg("sx"), py::arg("shy"), py::arg("shx"), py::arg("sy"), py::arg("tx"), py::arg("ty"))
.def(py::init<const BAffineTransform &>(), "", py::arg("copyFrom"))
//.def_static("kDefaultEpsilon", &BAffineTransform::kDefaultEpsilon,"")
.def("IsFixedSize", &BAffineTransform::IsFixedSize, "")
.def("TypeCode", &BAffineTransform::TypeCode, "")
.def("FlattenedSize", &BAffineTransform::FlattenedSize, "")
.def("Flatten", &BAffineTransform::Flatten, "", py::arg("buffer"), py::arg("size"))
.def("Unflatten", &BAffineTransform::Unflatten, "", py::arg("code"), py::arg("buffer"), py::arg("size"))
.def_static("AffineTranslation", &BAffineTransform::AffineTranslation, "", py::arg("x"), py::arg("y"))
.def_static("AffineRotation", &BAffineTransform::AffineRotation, "", py::arg("angle"))
.def_static("AffineScaling", py::overload_cast<double, double>(&BAffineTransform::AffineScaling), "", py::arg("x"), py::arg("y"))
.def_static("AffineScaling", py::overload_cast<double>(&BAffineTransform::AffineScaling), "", py::arg("scale"))
.def_static("AffineShearing", &BAffineTransform::AffineShearing, "", py::arg("x"), py::arg("y"))
.def("Apply", py::overload_cast<double *, double *>(&BAffineTransform::Apply, py::const_), "", py::arg("x"), py::arg("y"))
.def("ApplyInverse", py::overload_cast<double *, double *>(&BAffineTransform::ApplyInverse, py::const_), "", py::arg("x"), py::arg("y"))
.def("Apply", py::overload_cast<const BPoint &>(&BAffineTransform::Apply, py::const_), "", py::arg("point"))
.def("ApplyInverse", py::overload_cast<const BPoint &>(&BAffineTransform::ApplyInverse, py::const_), "", py::arg("point"))
.def("Apply", py::overload_cast<BPoint *>(&BAffineTransform::Apply, py::const_), "", py::arg("point"))
.def("ApplyInverse", py::overload_cast<BPoint *>(&BAffineTransform::ApplyInverse, py::const_), "", py::arg("point"))
.def("Apply", py::overload_cast<BPoint *, unsigned int>(&BAffineTransform::Apply, py::const_), "", py::arg("points"), py::arg("count"))
.def("ApplyInverse", py::overload_cast<BPoint *, unsigned int>(&BAffineTransform::ApplyInverse, py::const_), "", py::arg("points"), py::arg("count"))
.def("TranslateBy", py::overload_cast<double, double>(&BAffineTransform::TranslateBy), "", py::arg("x"), py::arg("y"))
.def("TranslateBy", py::overload_cast<const BPoint &>(&BAffineTransform::TranslateBy), "", py::arg("delta"))
.def("PreTranslateBy", &BAffineTransform::PreTranslateBy, "", py::arg("x"), py::arg("y"))
.def("TranslateByCopy", py::overload_cast<double, double>(&BAffineTransform::TranslateByCopy, py::const_), "", py::arg("x"), py::arg("y"))
.def("TranslateByCopy", py::overload_cast<const BPoint &>(&BAffineTransform::TranslateByCopy, py::const_), "", py::arg("delta"))
.def("RotateBy", py::overload_cast<double>(&BAffineTransform::RotateBy), "", py::arg("angle"))
.def("RotateBy", py::overload_cast<const BPoint &, double>(&BAffineTransform::RotateBy), "", py::arg("center"), py::arg("angle"))
.def("PreRotateBy", &BAffineTransform::PreRotateBy, "", py::arg("angleRadians"))
.def("RotateByCopy", py::overload_cast<double>(&BAffineTransform::RotateByCopy, py::const_), "", py::arg("angle"))
.def("RotateByCopy", py::overload_cast<const BPoint &, double>(&BAffineTransform::RotateByCopy, py::const_), "", py::arg("center"), py::arg("angle"))
.def("ScaleBy", py::overload_cast<double>(&BAffineTransform::ScaleBy), "", py::arg("scale"))
.def("ScaleBy", py::overload_cast<const BPoint &, double>(&BAffineTransform::ScaleBy), "", py::arg("center"), py::arg("scale"))
.def("ScaleBy", py::overload_cast<double, double>(&BAffineTransform::ScaleBy), "", py::arg("x"), py::arg("y"))
.def("ScaleBy", py::overload_cast<const BPoint &, double, double>(&BAffineTransform::ScaleBy), "", py::arg("center"), py::arg("x"), py::arg("y"))
.def("ScaleBy", py::overload_cast<const BPoint &>(&BAffineTransform::ScaleBy), "", py::arg("scale"))
.def("ScaleBy", py::overload_cast<const BPoint &, const BPoint &>(&BAffineTransform::ScaleBy), "", py::arg("center"), py::arg("scale"))
.def("PreScaleBy", &BAffineTransform::PreScaleBy, "", py::arg("x"), py::arg("y"))
.def("ScaleByCopy", py::overload_cast<double>(&BAffineTransform::ScaleByCopy, py::const_), "", py::arg("scale"))
.def("ScaleByCopy", py::overload_cast<const BPoint &, double>(&BAffineTransform::ScaleByCopy, py::const_), "", py::arg("center"), py::arg("scale"))
.def("ScaleByCopy", py::overload_cast<double, double>(&BAffineTransform::ScaleByCopy, py::const_), "", py::arg("x"), py::arg("y"))
.def("ScaleByCopy", py::overload_cast<const BPoint &, double, double>(&BAffineTransform::ScaleByCopy, py::const_), "", py::arg("center"), py::arg("x"), py::arg("y"))
.def("ScaleByCopy", py::overload_cast<const BPoint &>(&BAffineTransform::ScaleByCopy, py::const_), "", py::arg("scale"))
.def("ScaleByCopy", py::overload_cast<const BPoint &, const BPoint &>(&BAffineTransform::ScaleByCopy, py::const_), "", py::arg("center"), py::arg("scale"))
.def("SetScale", py::overload_cast<double>(&BAffineTransform::SetScale), "", py::arg("scale"))
.def("SetScale", py::overload_cast<double, double>(&BAffineTransform::SetScale), "", py::arg("x"), py::arg("y"))
.def("ShearBy", py::overload_cast<double, double>(&BAffineTransform::ShearBy), "", py::arg("x"), py::arg("y"))
.def("ShearBy", py::overload_cast<const BPoint &, double, double>(&BAffineTransform::ShearBy), "", py::arg("center"), py::arg("x"), py::arg("y"))
.def("ShearBy", py::overload_cast<const BPoint &>(&BAffineTransform::ShearBy), "", py::arg("shear"))
.def("ShearBy", py::overload_cast<const BPoint &, const BPoint &>(&BAffineTransform::ShearBy), "", py::arg("center"), py::arg("shear"))
.def("ShearByCopy", py::overload_cast<double, double>(&BAffineTransform::ShearByCopy, py::const_), "", py::arg("x"), py::arg("y"))
.def("ShearByCopy", py::overload_cast<const BPoint &, double, double>(&BAffineTransform::ShearByCopy, py::const_), "", py::arg("center"), py::arg("x"), py::arg("y"))
.def("ShearByCopy", py::overload_cast<const BPoint &>(&BAffineTransform::ShearByCopy, py::const_), "", py::arg("shear"))
.def("ShearByCopy", py::overload_cast<const BPoint &, const BPoint &>(&BAffineTransform::ShearByCopy, py::const_), "", py::arg("center"), py::arg("shear"))
.def("Multiply", &BAffineTransform::Multiply, "", py::arg("other"))
.def("PreMultiply", &BAffineTransform::PreMultiply, "", py::arg("other"))
.def("MultiplyInverse", &BAffineTransform::MultiplyInverse, "", py::arg("other"))
.def("PreMultiplyInverse", &BAffineTransform::PreMultiplyInverse, "", py::arg("other"))
.def("operator=", &BAffineTransform::operator=, "", py::arg("copyFrom"))
.def("__eq__", &BAffineTransform::operator==, "", py::arg("other"))
.def("__ne__", &BAffineTransform::operator!=, "", py::arg("other"))
.def("__imul__", &BAffineTransform::operator*=, "", py::arg("other"))
.def("__idiv__", &BAffineTransform::operator/=, "", py::arg("other"))
.def("__mul__", &BAffineTransform::operator*, "", py::arg("other"))
.def("__truediv__", &BAffineTransform::operator/, "", py::arg("other"))
.def("__invert__", &BAffineTransform::operator~, "")
.def("IsValid", &BAffineTransform::IsValid, "", py::arg("epsilon")=kDefaultEpsilon)
.def("IsIdentity", &BAffineTransform::IsIdentity, "", py::arg("epsilon")=kDefaultEpsilon)
.def("IsDilation", &BAffineTransform::IsDilation, "", py::arg("epsilon")=kDefaultEpsilon)
.def("IsEqual", &BAffineTransform::IsEqual, "", py::arg("other"), py::arg("epsilon")=kDefaultEpsilon)
.def("Invert", &BAffineTransform::Invert, "")
.def("FlipX", &BAffineTransform::FlipX, "")
.def("FlipY", &BAffineTransform::FlipY, "")
.def("Reset", &BAffineTransform::Reset, "")
.def("Determinant", &BAffineTransform::Determinant, "")
.def("InverseDeterminant", &BAffineTransform::InverseDeterminant, "")
.def("GetTranslation", &BAffineTransform::GetTranslation, "", py::arg("tx"), py::arg("ty"))
.def("Rotation", &BAffineTransform::Rotation, "")
.def("Scale", &BAffineTransform::Scale, "")
.def("GetScale", &BAffineTransform::GetScale, "", py::arg("sx"), py::arg("sy"))
.def("GetScaleAbs", &BAffineTransform::GetScaleAbs, "", py::arg("sx"), py::arg("sy"))
.def("GetAffineParameters", &BAffineTransform::GetAffineParameters, "", py::arg("translationX"), py::arg("translationY"), py::arg("rotation"), py::arg("scaleX"), py::arg("scaleY"), py::arg("shearX"), py::arg("shearY"))
.def_property_readonly_static("kDefaultEpsilon", []() {
            return AltBAffineTransform::getKDefaultEpsilon();
        }, "")
//.def_readwrite("kDefaultEpsilon", &BAffineTransform::kDefaultEpsilon, "")
//.def_readwrite("kDefaultEpsilon", &BAffineTransform::kDefaultEpsilon, "")
.def_readwrite("sx", &BAffineTransform::sx, "")
.def_readwrite("shy", &BAffineTransform::shy, "")
.def_readwrite("shx", &BAffineTransform::shx, "")
.def_readwrite("sy", &BAffineTransform::sy, "")
.def_readwrite("tx", &BAffineTransform::tx, "")
.def_readwrite("ty", &BAffineTransform::ty, "")
;
/*
m.def("operator=", &operator=, "", py::arg("other"));

m.def("__eq__", &operator==, "", py::arg("other"));

m.def("__ne__", &operator!=, "", py::arg("other"));

m.def("__imul__", &operator*=, "", py::arg("other"));

m.def("__idiv__", &operator/=, "", py::arg("other"));

m.def("__mul__", &operator*, "", py::arg("other"));

m.def("__truediv__", &operator/, "", py::arg("other"));

m.def("__invert__", &operator~, "");*/

}
