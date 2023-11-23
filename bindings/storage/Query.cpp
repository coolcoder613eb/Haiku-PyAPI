#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <Query.h>

namespace py = pybind11;
using namespace BPrivate;
using namespace BPrivate::Storage;
using namespace BPrivate::Storage::Mime;
using namespace BPackageKit;

void define_Query(py::module_& m)
{
py::enum_<query_op>(m, "query_op", "")
.value("B_INVALID_OP", query_op::B_INVALID_OP, "")
.value("B_EQ", query_op::B_EQ, "")
.value("B_GT", query_op::B_GT, "")
.value("B_GE", query_op::B_GE, "")
.value("B_LT", query_op::B_LT, "")
.value("B_LE", query_op::B_LE, "")
.value("B_NE", query_op::B_NE, "")
.value("B_CONTAINS", query_op::B_CONTAINS, "")
.value("B_BEGINS_WITH", query_op::B_BEGINS_WITH, "")
.value("B_ENDS_WITH", query_op::B_ENDS_WITH, "")
.value("B_AND", query_op::B_AND, "")
.value("B_OR", query_op::B_OR, "")
.value("B_NOT", query_op::B_NOT, "")
.value("_B_RESERVED_OP_", query_op::_B_RESERVED_OP_, "")
.export_values();

m.attr("QueryNode") = py::cast(QueryNode);

m.attr("QueryStack") = py::cast(QueryStack);

m.attr("QueryTree") = py::cast(QueryTree);

py::class_<BQuery, BEntryList>(m, "BQuery")
.def(py::init(), "")
.def("Clear", &BQuery::Clear, "")
.def("PushAttr", &BQuery::PushAttr, "", py::arg("attrName"))
.def("PushOp", &BQuery::PushOp, "", py::arg("op"))
.def("PushUInt32", &BQuery::PushUInt32, "", py::arg("value"))
.def("PushInt32", &BQuery::PushInt32, "", py::arg("value"))
.def("PushUInt64", &BQuery::PushUInt64, "", py::arg("value"))
.def("PushInt64", &BQuery::PushInt64, "", py::arg("value"))
.def("PushFloat", &BQuery::PushFloat, "", py::arg("value"))
.def("PushDouble", &BQuery::PushDouble, "", py::arg("value"))
.def("PushString", &BQuery::PushString, "", py::arg("value"), py::arg("caseInsensitive")=false)
.def("PushDate", &BQuery::PushDate, "", py::arg("date"))
.def("SetVolume", &BQuery::SetVolume, "", py::arg("volume"))
.def("SetPredicate", &BQuery::SetPredicate, "", py::arg("expression"))
.def("SetTarget", &BQuery::SetTarget, "", py::arg("messenger"))
.def("IsLive", &BQuery::IsLive, "")
.def("GetPredicate", py::overload_cast<char *, size_t>(&BQuery::GetPredicate), "", py::arg("buffer"), py::arg("length"))
.def("GetPredicate", py::overload_cast<BString *>(&BQuery::GetPredicate), "", py::arg("predicate"))
.def("PredicateLength", &BQuery::PredicateLength, "")
.def("TargetDevice", &BQuery::TargetDevice, "")
.def("Fetch", &BQuery::Fetch, "")
.def("GetNextEntry", &BQuery::GetNextEntry, "", py::arg("entry"), py::arg("traverse")=false)
.def("GetNextRef", &BQuery::GetNextRef, "", py::arg("ref"))
.def("GetNextDirents", &BQuery::GetNextDirents, "", py::arg("buffer"), py::arg("length"), py::arg("count")=INT_MAX)
.def("Rewind", &BQuery::Rewind, "")
.def("CountEntries", &BQuery::CountEntries, "")
;


}
