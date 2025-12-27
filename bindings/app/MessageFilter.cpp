#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <app/MessageFilter.h>
#include <Handler.h>
#include <Looper.h>


namespace py = pybind11;

class PyBMessageFilter : public BMessageFilter {
public:
    using BMessageFilter::BMessageFilter;

    filter_result Filter(BMessage* message, BHandler** target) override {
        py::gil_scoped_acquire gil;

        py::function override = py::get_override(static_cast<const BMessageFilter*>(this), "Filter");

        if (!override) {
            return BMessageFilter::Filter(message, target);
        }

        BHandler* current = target ? *target : nullptr;
        py::object result = override(message, current);

        auto tuple = result.cast<py::tuple>();
        filter_result fr = tuple[0].cast<filter_result>();
        BHandler* newTarget = tuple[1].cast<BHandler*>();

        if (target)
            *target = newTarget;

        return fr;
    }
};

PYBIND11_MODULE(MessageFilter,m)
{
py::enum_<filter_result>(m, "filter_result", R"doc(
Indicates the result of a message filtering operation.
)doc")
.value("B_SKIP_MESSAGE", filter_result::B_SKIP_MESSAGE, R"doc(
The message goes no further–it's immediately thrown away by the caller.
)doc")
.value("B_DISPATCH_MESSAGE", filter_result::B_DISPATCH_MESSAGE, R"doc(
The message and handler are passed (by the caller) to the looper's ``DispatchMessage()`` function.
)doc")
.export_values();

py::enum_<message_delivery>(m, "message_delivery", R"doc(
The delivery criteria for filtering a message.
Specifies how the message must arrive:
)doc")
.value("B_ANY_DELIVERY", message_delivery::B_ANY_DELIVERY, R"doc(
Any (The default one).
)doc")
.value("B_DROPPED_DELIVERY", message_delivery::B_DROPPED_DELIVERY, "Drag'n'drop")
.value("B_PROGRAMMED_DELIVERY", message_delivery::B_PROGRAMMED_DELIVERY, "Programmatically")
.export_values();

py::enum_<message_source>(m, "message_source", R"doc(
The source criteria for filtering a message.
Specifes whether the sender of the message must be:
)doc")
.value("B_ANY_SOURCE", message_source::B_ANY_SOURCE, R"doc(
Any (The default one).
)doc")
.value("B_REMOTE_SOURCE", message_source::B_REMOTE_SOURCE, "Remote")
.value("B_LOCAL_SOURCE", message_source::B_LOCAL_SOURCE, "Local vis-a-vis this app")
.export_values();

py::class_<BMessageFilter,PyBMessageFilter>(m, "BMessageFilter",R"doc(
A ``BMessageFilter`` is a message-screening function that you "attach" to 
a ``BLooper`` or ``BHandler``. The message filter sees messages just before 
they're dispatched (i.e. just before ``BLooper.DispatchMessage()``), and can 
modify or reject the message, change the message's designated handler, or 
whatever else it wants to do—the implementation of the filter function isn't 
restricted.

.. note::

   filter_hook defines the protocol for message-filtering functions.
   In c++:
   
   .. code-block:: c++
   
      filter_result (*filter_hook)(BMessage* message,
                             BHandler** target,
                             BMessageFilter* messageFilter);

   The first two arguments are the message that's being considered, and 
   the proposed ``BHandler`` target. You can alter the contents of the 
   message, and alter or even replace the handler. If you replace the 
   handler, the new handler must belong to the same looper as the 
   original. The new handler is given an opportunity to filter the 
   message before it's dispatched.

   ``messageFilter`` is a pointer to the object on whose behalf this 
   function is being called; you mustn't delete this object. More than 
   one ``BMessageFilter`` can use the same ``filter_hook`` function.
   
   **beware** filter_hook is not Python-usable therefore we ignore it

)doc")
.def(py::init<uint32>(),R"doc(
Creates and returns a new ``BMessageFilter``.

:param what: A command constant, the ``what`` value of the incoming message must match this value.
:type what: int
)doc", py::arg("what"))
// Non funziona con trampoline/alias
//.def(py::init([](message_delivery d, message_source s) {
//        return BMessageFilter(d, s, nullptr);
//}), R"doc(
.def(py::init<message_delivery, message_source>(), R"doc(
Creates and returns a new ``BMessageFilter``.

:param delivery: specify how message must arrive.
:type delivery: message_delivery
:param source: specify how should be the sender.
:type source: message_source
)doc", py::arg("delivery"), py::arg("source"))
// Non funziona con trampoline/alias
// .def(py::init([](message_delivery d, message_source s, uint32 w) {
//         return BMessageFilter(d, s, w, nullptr);
// }),R"doc(
.def(py::init<message_delivery, message_source, unsigned int>(), R"doc(
Creates and returns a new ``BMessageFilter``.

:param delivery: specify how message must arrive.
:type delivery: message_delivery
:param source: specify how should be the sender.
:type source: message_source
:param what: A command constant, the ``what`` value of the incoming message must match this value.
:type what: int
)doc", py::arg("delivery"), py::arg("source"), py::arg("what"))
/*
.def(py::init<unsigned int, filter_hook>(), "", py::arg("what"), py::arg("func")=NULL)
.def(py::init<message_delivery, message_source, filter_hook>(), "", py::arg("delivery"), py::arg("source"), py::arg("func")=NULL)
.def(py::init<message_delivery, message_source, unsigned int, filter_hook>(), "", py::arg("delivery"), py::arg("source"), py::arg("what"), py::arg("func")=NULL)
.def(py::init<const BMessageFilter *>(), "", py::arg("filter"))
.def(py::init<const BMessageFilter &>(), "", py::arg("filter"))
*/
//.def("operator=", &BMessageFilter::operator=, "", py::arg("from"))
.def("Filter", [](BMessageFilter& self, BMessage* message, BHandler* target) {
	BHandler* current = target;
	filter_result result = self.Filter(message, &current);
	return py::make_tuple(result, current);
}, R"doc(
Executes the message filter.

:param message: The message being considered for dispatch.
:type message: BMessage
:param target: The handler that would normally receive the message.
:type target: BHandler
:return: A tuple ``(result, target)``:

   - ``result`` (filter_result): the outcome of the filtering operation.
   - ``target`` (BHandler): The handler that will receive the message. This may differ from the original handler if the filter changed it.
   
:rtype: tuple
)doc", py::arg("message"), py::arg("target"))
.def("MessageDelivery", &BMessageFilter::MessageDelivery, "")
.def("MessageSource", &BMessageFilter::MessageSource, "")
.def("Command", &BMessageFilter::Command, "")
.def("FiltersAnyCommand", &BMessageFilter::FiltersAnyCommand, "")
.def("Looper", &BMessageFilter::Looper, "",py::return_value_policy::reference)
;


}
