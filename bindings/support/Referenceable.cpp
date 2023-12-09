#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/Referenceable.h>

namespace py = pybind11;


void define_Referenceable(py::module_& m)
{
py::class_<BReferenceable>(m, "BReferenceable")
.def(py::init(), "")
.def("AcquireReference", &BReferenceable::AcquireReference, "")
.def("ReleaseReference", &BReferenceable::ReleaseReference, "")
.def("CountReferences", &BReferenceable::CountReferences, "")
;

py::class_<BReference>(m, "BReference")
.def(py::init(), "")
.def(py::init<Type *, bool>(), "", py::arg("object"), py::arg("alreadyHasReference")=false)
.def(py::init<const BReference<Type> &>(), "", py::arg("other"))
.def(py::init<const BReference<OtherType> &>(), "", py::arg("other"))
.def("SetTo", &BReference::SetTo, "", py::arg("object"), py::arg("alreadyHasReference")=false)
.def("Unset", &BReference::Unset, "")
.def("IsSet", &BReference::IsSet, "")
.def("Get", &BReference::Get, "")
.def("Detach", &BReference::Detach, "")
.def("__mul__", &BReference::operator*, "")
.def("operator->", &BReference::operator->, "")
.def("operatorType*", &BReference::operatorType*, "")
.def("operator=", py::overload_cast<const BReference<Type> &>(&BReference::operator=), "", py::arg("other"))
.def("operator=", py::overload_cast<Type *>(&BReference::operator=), "", py::arg("other"))
.def("operator=", py::overload_cast<const BReference<OtherType> &>(&BReference::operator=), "", py::arg("other"))
.def("__eq__", py::overload_cast<const BReference<Type> &>(&BReference::operator==), "", py::arg("other"))
.def("__eq__", py::overload_cast<const Type *>(&BReference::operator==), "", py::arg("other"))
.def("__ne__", py::overload_cast<const BReference<Type> &>(&BReference::operator!=), "", py::arg("other"))
.def("__ne__", py::overload_cast<const Type *>(&BReference::operator!=), "", py::arg("other"))
;

py::class_<BReference<constType>>(m, "BReference<constType>")
.def(py::init<Type *, bool>(), "", py::arg("object"), py::arg("alreadyHasReference")=false)
.def(py::init<const BReference<const Type> &>(), "", py::arg("other"))
.def(py::init<const BReference<OtherType> &>(), "", py::arg("other"))
.def("SetTo", &BReference<constType>::SetTo, "", py::arg("object"), py::arg("alreadyHasReference")=false)
.def("Unset", &BReference<constType>::Unset, "")
.def("IsSet", &BReference<constType>::IsSet, "")
.def("Get", &BReference<constType>::Get, "")
.def("Detach", &BReference<constType>::Detach, "")
.def("__mul__", &BReference<constType>::operator*, "")
.def("operator->", &BReference<constType>::operator->, "")
.def("operatorconstType*", &BReference<constType>::operatorconstType*, "")
.def("operator=", py::overload_cast<const BReference<const Type> &>(&BReference<constType>::operator=), "", py::arg("other"))
.def("operator=", py::overload_cast<Type *>(&BReference<constType>::operator=), "", py::arg("other"))
.def("operator=", py::overload_cast<const BReference<OtherType> &>(&BReference<constType>::operator=), "", py::arg("other"))
.def("__eq__", py::overload_cast<const BReference<const Type> &>(&BReference<constType>::operator==), "", py::arg("other"))
.def("__eq__", py::overload_cast<const Type *>(&BReference<constType>::operator==), "", py::arg("other"))
.def("__ne__", py::overload_cast<const BReference<const Type> &>(&BReference<constType>::operator!=), "", py::arg("other"))
.def("__ne__", py::overload_cast<const Type *>(&BReference<constType>::operator!=), "", py::arg("other"))
;


}
