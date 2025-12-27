#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <app/MessageRunner.h>
#include <Messenger.h>

namespace py = pybind11;


PYBIND11_MODULE(MessageRunner,m)
{
py::class_<BMessageRunner>(m, "BMessageRunner",R"doc(
The ``BMessageRunner`` class provides a handy mechanism for automatically 
sending an arbitrary message to a ``BMessenger`` at specified intervals. 
The application that creates the ``BMessageRunner`` can specify the message, 
the ``BMessenger`` to send the message to, how often to send the message, 
and how many times it should be sent.
)doc")
.def(py::init<BMessenger, const BMessage *, bigtime_t, int>(), R"doc(
Creates a new ``BMessageRunner``.

:param target: The message recipient.
:type target: BMessenger
:param message: The message to be sent.
:type message: BMessage
:param interval: Time interval between messages (in microseconds).
:type interval: int
:param count: Number of times the message is sent (-1 for infinite).
:type count: int

.. note::

   In C++, there is also a version that accepts a reference (`BMessage &`). 
   In Python, objects are always passed by reference, so the behavior is identical. 
   This pointer-based overload is kept only for compatibility with the original C++ API.

)doc", py::arg("target"), py::arg("message"), py::arg("interval"), py::arg("count")=- 1)
.def(py::init<BMessenger, const BMessage &, bigtime_t, int>(), R"doc(
Creates a new ``BMessageRunner``.

:param target: The message recipient.
:type target: BMessenger
:param message: The message to be sent.
:type message: BMessage
:param interval: Time interval between messages (in microseconds).
:type interval: int
:param count: Number of times the message is sent (-1 for infinite).
:type count: int
)doc", py::arg("target"), py::arg("message"), py::arg("interval"), py::arg("count")=- 1)
.def(py::init<BMessenger, const BMessage *, bigtime_t, int, BMessenger>(), R"doc(
Creates a new BMessageRunner with a reply target.

:param target: The message recipient.
:type target: BMessenger
:param message: The message to be sent.
:type message: BMessage
:param interval: Time interval between messages (in microseconds).
:type interval: int
:param count: Number of times the message is sent (-1 for infinite).
:type count: int
:param replyTo: Messenger to receive replies.
:type replyTo: BMessenger

.. note::

   In C++, there is also a version that accepts a reference (`BMessage &`). 
   In Python, objects are always passed by reference, so the behavior is identical.
   This pointer-based overload is kept only for compatibility with the original C++ API.

)doc", py::arg("target"), py::arg("message"), py::arg("interval"), py::arg("count"), py::arg("replyTo"))
.def(py::init<BMessenger, const BMessage &, bigtime_t, int, BMessenger>(), R"doc(
Creates a new BMessageRunner with a reply target.

:param target: The message recipient.
:type target: BMessenger
:param message: The message to be sent.
:type message: BMessage
:param interval: Time interval between messages (in microseconds).
:type interval: int
:param count: Number of times the message is sent (-1 for infinite).
:type count: int
:param replyTo: Messenger to receive replies.
:type replyTo: BMessenger
)doc", py::arg("target"), py::arg("message"), py::arg("interval"), py::arg("count"), py::arg("replyTo"))
.def("InitCheck", &BMessageRunner::InitCheck, R"doc(
Return a result code indicating ``B_OK`` if the ``BMessageRunner`` constructor executed 
sucessfully, or some other value if an error occurred setting up the object. 
You should call this immediately after creating a ``BMessageRunner``, and shouldn't 
use the object if this function returns anything but ``B_OK``.

.. note::

   As soon as the last message is sent, the message runner becomes unusable. 
   ``InitCheck()`` will still return ``B_OK``, but ``SetInterval()``, ``SetCount()`` 
   and ``GetInfo()`` will all fail.

:return: ``B_OK`` if successful, a Haiku error otherwise.
:rtype: int
 )doc")
.def("SetInterval", &BMessageRunner::SetInterval, R"doc(
Set the number of microseconds that will pass between messages being sent.

:param interval: The new interval in microseconds.
:type interval: int
:return: A status code:
   
   - ``B_OK`` if everything went fine.
   - ``B_NO_INIT`` if the message runner was not properly initialized.
   - ``B_BAD_VALUE`` if interval was ``0`` or negative, or the message runner had already sent all messages and became unusable.
   
:rtype: int
)doc", py::arg("interval"))
.def("SetCount", &BMessageRunner::SetCount, R"doc(
Set the number of times the ``BMessageRunner`` will send the message. 
If you want the message to be sent forever (until the object is deleted or 
``SetCount()`` is called again), specify ``-1``.

:param count: Specifies how many times the message shall be sent. A negative value indicates that the message will be sent forever, or until the BMessageRunner is reconfigured or deleted.
:type count: int
:return: A status code:

   - ``B_OK`` if everything went fine.
   - ``B_NO_INIT`` if the message runner was not properly initialized.
   - ``B_BAD_VALUE`` interval was ``0`` or negative, or the message runner had already sent all messages and became unusable.
   
:rtype: int
)doc", py::arg("count"))
//.def("GetInfo", &BMessageRunner::GetInfo, R"doc()doc", py::arg("interval"), py::arg("count"))
.def("GetInfo", [](const BMessageRunner& self){
	bigtime_t	interval;
	int32		count;
	status_t ret = self.GetInfo(&interval,&count);
	return py::make_tuple(ret,interval,count);
}, R"doc(
Return in interval the time in microseconds that will pass between messages 
being sent, the number of times the message will be sent along with the 
status code of the call.

.. note::
   Both output values (the interval and the count) may be ``None``.
   
:return: A tuple containing:

   - The status code of the call which can be:
      
      - ``B_OK`` if everything went fine.
      - ``B_BAD_VALUE`` if the interval was ``0`` or negative, or the message runner had already sent all messages and became unusable.
      
   - The time interval, may be ``None``.
   - The number of times the message has still to be sent. May be ``None``.
   
:rtype: tuple
)doc")
.def_static("StartSending", py::overload_cast<BMessenger, const BMessage *, bigtime_t, int32>(&BMessageRunner::StartSending), R"doc(
A static call to create and initialize a detached ``BMessageRunner`` that 
instructs the system roster to send the specified message to the target 
count times every interval microseconds, reply messages are sent to 
``be_app_messenger``.

.. note::
   You cannot alter the runner after the creation, and it will be deleted 
   automatically the last message is sent.

:param target: Target of the message(s).
:type target: BMessenger
:param message: The message to be sent to the target.
:type message: BMessage
:param interval: Period of time before the first message is sent and between messages (if more than one shall be sent) in microseconds.
:type interval: int
:param count: How many times the message shall be sent. A negative value indicates that the message will be sent forever, or until the BMessageRunner is reconfigured or deleted.
:type count: int
)doc", py::arg("target"), py::arg("message"), py::arg("interval"), py::arg("count"))
.def_static("StartSending", py::overload_cast<BMessenger, const BMessage *, bigtime_t, int32, BMessenger>(&BMessageRunner::StartSending), R"doc(
A static call to create and initialize a detached ``BMessageRunner`` that 
instructs the system roster to send the specified message to the target 
count times every interval microseconds.

.. note::
   You cannot alter the runner after the creation, and it will be deleted 
   automatically the last message is sent.

:param target: Target of the message(s).
:type target: BMessenger
:param message: The message to be sent to the target.
:type message: BMessage
:param interval: Period of time before the first message is sent and between messages (if more than one shall be sent) in microseconds.
:type interval: int
:param count: How many times the message shall be sent. A negative value indicates that the message will be sent forever, or until the BMessageRunner is reconfigured or deleted.
:type count: int
:param replyTo: Target replies to the delivered message(s) shall be sent to.
:type replyTo: BMessenger
)doc", py::arg("target"), py::arg("message"), py::arg("interval"), py::arg("count"), py::arg("replyTo"))
;


}
