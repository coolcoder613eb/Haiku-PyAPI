#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <app/MessageQueue.h>
#include <Locker.h>
#include <Message.h>

namespace py = pybind11;


PYBIND11_MODULE(MessageQueue,m)
{
py::class_<BMessageQueue>(m, "BMessageQueue",R"doc(
The ``BMessageQueue`` class completes the implementation of ``BLooper`` 
by providing a first-in/first-out stack in which the looper can place 
in-coming ``BMessages``. In general, the message dispatching mechanism 
of ``BLooper`` should suffice. However, if you ever need to manipulate 
a ``BMessage`` queue directly, you can do so.
)doc")
.def(py::init(), "Create an empty BMessageQueue object.")
.def("AddMessage", &BMessageQueue::AddMessage, R"doc(
Add a message to the far end of the queue.

:param message: The message to be queued.
:type message: BMessage
)doc", py::arg("message"))
.def("RemoveMessage", &BMessageQueue::RemoveMessage, R"doc(
Remove a particular message from the queue and delete it.

:param message: The message to be removed.
:type message: BMessage
)doc", py::arg("message"))
.def("CountMessages", &BMessageQueue::CountMessages, R"doc(
Return the number of messages currently in the queue.

:return: The number of the messages in the queue.
:rtype: int
)doc")
.def("IsEmpty", &BMessageQueue::IsEmpty, R"doc(
Returns a boolean value indicating whether the object doesn't contain 
any messages.

:return: ``True`` if empty, ``False`` otherwise.
:rtype: bool
)doc")
.def("FindMessage", py::overload_cast<int32>(&BMessageQueue::FindMessage, py::const_), R"doc(
Return the ``index``'th ``BMessage`` in the queue, where index ``0`` 
signifies the message that's been in the queue the longest.

.. note::

   The message is not removed from the message queue.
   If the index is out of range, this method returns ``None``.

:param index: The zero-based index of the message to retrieve.
:type index: int
:return: The message retrieved.
:rtype: BMessage
)doc", py::arg("index"))
.def("FindMessage", py::overload_cast<uint32, int32>(&BMessageQueue::FindMessage, py::const_), R"doc(
This version of ``FindMessage`` lets you specify a ``what`` field value; 
in this case, only messages that match the ``what`` argument are counted.

.. note::

   The message is not removed from the message queue.
   If the index is out of range, this method returns ``None``.

:param what: The command to consider for the queued messages.
:type what: int
:param index: The zero-based index of the considered message list to use for message retrival.
:type index: int
:return: The message retrieved.
:rtype: BMessage
)doc", py::arg("what"), py::arg("index")=0)
.def("Lock", &BMessageQueue::Lock, R"doc(
Lock the ``BMessageQueue``, so that another thread won't alter the 
contents of the queue while it's being read. ``Lock()`` doesn't 
return until it has the queue locked; it always returns ``True``.

.. note::

   Calls to this function can be nested.

:return: ``True``
:rtype: bool
)doc")
.def("Unlock", &BMessageQueue::Unlock, R"doc(
Unlock the ``BMessageQueue``, so that another thread won't alter the 
contents of the queue while it's being read. ``Unlock()`` releases 
the lock so that someone else can lock it.

.. note::

   Calls to this function can be nested.

)doc")
.def("IsLocked", static_cast<bool (BMessageQueue::*)() const>(&BMessageQueue::IsLocked), R"doc(
Check if the queue is locked.

:return: Whether the queue is locked. ``True`` is locked, ``False`` otherwise.
:rtype: bool
)doc")
.def("NextMessage", &BMessageQueue::NextMessage, R"doc(
Remove and return the oldest message from the queue. If the queue 
is empty, the function returns ``None``.

:return: The oldest message from the queue or ``None``.
:rtype: BMessage
)doc")
.def("IsNextMessage", &BMessageQueue::IsNextMessage, R"doc(
Checks if the given ``BMessage`` is the one currently at the head of 
the queue (the next one to be dispatched).

:param message: The message object to check.
:type message: BMessage 
:return: ``True`` if the object is the next message in the queue, ``False`` otherwise.
:rtype: bool
)doc", py::arg("message"))
;


}
