#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <app/MessageFilter.h>
#include <Handler.h>
#include <Looper.h>


namespace py = pybind11;


PYBIND11_MODULE(MessageFilter,m)
{
py::enum_<filter_result>(m, "filter_result", "")
.value("B_SKIP_MESSAGE", filter_result::B_SKIP_MESSAGE, "")
.value("B_DISPATCH_MESSAGE", filter_result::B_DISPATCH_MESSAGE, "")
.export_values();

py::enum_<message_delivery>(m, "message_delivery", "")
.value("B_ANY_DELIVERY", message_delivery::B_ANY_DELIVERY, "")
.value("B_DROPPED_DELIVERY", message_delivery::B_DROPPED_DELIVERY, "")
.value("B_PROGRAMMED_DELIVERY", message_delivery::B_PROGRAMMED_DELIVERY, "")
.export_values();

py::enum_<message_source>(m, "message_source", "")
.value("B_ANY_SOURCE", message_source::B_ANY_SOURCE, "")
.value("B_REMOTE_SOURCE", message_source::B_REMOTE_SOURCE, "")
.value("B_LOCAL_SOURCE", message_source::B_LOCAL_SOURCE, "")
.export_values();

py::class_<BMessageFilter>(m, "BMessageFilter")
.def(py::init<unsigned int, filter_hook>(), "", py::arg("what"), py::arg("func")=NULL)
.def(py::init<message_delivery, message_source, filter_hook>(), "", py::arg("delivery"), py::arg("source"), py::arg("func")=NULL)
.def(py::init<message_delivery, message_source, unsigned int, filter_hook>(), "", py::arg("delivery"), py::arg("source"), py::arg("what"), py::arg("func")=NULL)
.def(py::init<const BMessageFilter &>(), "", py::arg("filter"))
.def(py::init<const BMessageFilter *>(), "", py::arg("filter"))
.def("operator=", &BMessageFilter::operator=, "", py::arg("from"))
//.def("Filter", &BMessageFilter::Filter, "", py::arg("message"), py::arg("_target"))
.def("MessageDelivery", &BMessageFilter::MessageDelivery, "")
.def("MessageSource", &BMessageFilter::MessageSource, "")
.def("Command", &BMessageFilter::Command, "")
.def("FiltersAnyCommand", &BMessageFilter::FiltersAnyCommand, "")
.def("Looper", &BMessageFilter::Looper, "")
;


}
