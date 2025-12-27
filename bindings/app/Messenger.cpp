#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <app/Messenger.h>
#include <OS.h>
#include <ByteOrder.h>
#include <Message.h>
#include <Looper.h>
#include <Handler.h>

namespace py = pybind11;

/* wrong
BHandler* TargetWrapper(BMessenger& self, std::vector<BLooper*> looper) {
	return self.Target(looper.data());
}*/

PYBIND11_MODULE(Messenger,m)
{
py::class_<BMessenger>(m, "BMessenger",R"doc(
A ``BMessenger`` can send messages to local and remote targets. If the 
target belongs to the same team as the ``BMessenger`` it is a local target, 
otherwise if the target lives in a separate address space it is a remote 
target.

The most significant (set of) method(s) in the class is ``SendMessage()``, 
which sends its message to the target. For a local target ``SendMessage()`` 
is roughly equivalent in terms of efficiency to posting a message directly 
to the messenger's target (i.e. ``BLooper.PostMessage()``).

If you supply a target ``BMessenger`` or ``BHandler`` to ``SendMessage()`` 
the method will return immediately after delivery and the response will be 
handled asynchronously, otherwise the method will return once the reply has 
been delivered or after a set timeout.
)doc")
.def(py::init(), "Create an uninitialized BMessenger.")
// ACT TODO: modificare init perché non possiamo passare un parametro status_t visto che python lo rende immutabile
//.def(py::init<const char *, team_id, status_t *>(), R"doc(
/*.def(py::init([](const char * signature, team_id team){
	status_t status;
	BMessenger* msngr = new BMessenger(signature,team,status);
	return py::make_tuple(msngr,status);
}, */
/*
Note: the original constructor is:
.def(py::init<const char *, team_id, status_t *>()
with status_t * called py::arg("result")=NULL

as python int are immutable we cannot use the result parameter.
py::init cannot return tuples so, in this case we can provide a 
static_def (e.g.) "Create" which returns both the new BMessenger and the status_t
*/
.def(py::init<const char *, team_id>(),R"doc(
Creates a BMessenger and initializes it to target the already running 
application identified by its signature and/or team ID.

When only a signature is given, and multiple instances of the application 
are running it is indeterminate which one is chosen as the target. In case 
only a team ID is passed, the target application is identified uniquely. 
If both are supplied, the application identified by the team ID must have 
a matching signature, otherwise the initialization fails.

:param signature: The target application's signature. May be ``None``.
:type signature: str
:param team: The target application's team ID. May be < ``0``.
:type team: team_id
)doc", py::arg("signature"), py::arg("team")=- 1)
//.def(py::init<const BHandler *, const BLooper *, status_t *>(), "", py::arg("handler"), py::arg("looper")=NULL, py::arg("result")=NULL)
.def(py::init<const BHandler *, const BLooper *>(), R"doc(
Creates a ``BMessenger`` and initializes it to target the local ``BHandler`` 
and/or ``BLooper``.

When a ``None`` handler is supplied, the preferred handler in the looper 
is targeted. If no looper is supplied the looper that handler belongs to 
is used instead – that means in particular, that the handler must already 
belong to a looper. If both are supplied the handler must belong to the looper.

:param handler: The target handler. May be ``None``.
:type handler: BHandler
:param looper: The target looper. May be ``None``.
:type looper: BLooper
)doc", py::arg("handler"), py::arg("looper")=NULL)
.def(py::init<const BMessenger &>(), R"doc(
Creates a ``BMessenger`` and initializes it to have the same target as 
the supplied messenger.

:param other: 
:type other: BMessenger
)doc", py::arg("other"))
.def_static("Create",[](const char* signature, team_id team) {
	status_t status;
	BMessenger messenger(signature, team, &status);
	return py::make_tuple(messenger, status);
}, R"doc(
Convenience static method to create a ``BMessenger`` by providing a 
signature and/or a team ID. It will return both the messenger and 
its initialization status through a tuple.

:param signature: The target application's signature. May be ``None``.
:type signature: str
:param team: The target application's team ID. May be < ``0``.
:type team: team_id
:return: A tuple containing the messenger and its initialization status
:rtype: tuple
)doc", py::arg("signature"), py::arg("team"))
.def_static("Create",[](const BHandler * handler, const BLooper * looper) {
	status_t status;
	BMessenger messenger(handler, looper, &status);
	return py::make_tuple(messenger, status);
}, R"doc(
Convenience static method to create a ``BMessenger`` by providing a handler
and/or a looper. It will return both the messenger and its initialization 
status through a tuple.

:param handler: The target handler. May be ``None``.
:type handler: BHandler
:param looper: The target looper. May be ``None``.
:type looper: BLooper
:return: A tuple containing the messenger and its initialization status
:rtype: tuple
)doc", py::arg("handler"), py::arg("looper")=NULL)
.def("IsTargetLocal", &BMessenger::IsTargetLocal, R"doc(
Return whether the messenger and target belong to the same team.

:return: ``True`` if the messenger is properly initialized and its target belong ot the same team, ``False`` if they reside in separate address spaces.
:rtype: bool
)doc")
/* 
this is actually not like the c++ original one, as it returns a tuple and the passed looper is not "filled"
so there's no need or reasons to expose this version!

.def("Target", [](const BMessenger& self, BLooper* looper) {
	BLooper* current = looper;
	BHandler* handler = self.Target(&current);
	return py::make_tuple(handler, current);
}, "", py::arg("looper")) */
.def("Target",[](const BMessenger& self) {
	BLooper* looper = nullptr;
	BHandler* handler = self.Target(&looper);
	return py::make_tuple(handler, looper);
},R"doc(
Returns the handler and looper targeted by the messenger (if the target 
is local).

Both are returned through a tuple. If both are ``None``, the object is 
either not properly initialized, the target objects have been deleted 
or the target is remote. If only the returned handler is ``None``, either 
the looper's preferred handler is targeted 
or the handler has been deleted.

:return: A tuple ``(handler, looper)``.
:rtype: tuple
)doc")
.def("LockTarget", &BMessenger::LockTarget, R"doc(
Lock the ``BLooper`` targeted by the messenger (if the target is local).

This method is a shorthand for retrieving the targeted looper via 
``Target()`` and calling ``BLooper.Lock()`` on the looper afterwards.

:return: a boolean value:
   
   - ``True`` if the looper was locked successfully
   - ``False`` if the messenger was not properly initialized, the target was remote, or the targeted looper was invalid.
   
:rtype: bool
)doc")
.def("LockTargetWithTimeout", &BMessenger::LockTargetWithTimeout, R"doc(
Lock the ``BLooper`` targeted by the messenger with a timeout (if 
the target is local).

This method is a shorthand for retrieving the targeted looper via 
``Target()`` and calling ``BLooper.LockWithTimeout()`` on the 
looper afterwards.

:return: A status code. If not success, one of the error codes returned by BLooper.LockWithTimeout().
   
   - ``B_OK`` if the looper was locked successfully.
   - ``B_BAD_VALUE`` if the messenger was not properly initialized, the target was remote, or the targeted looper was invalid.
   
:rtype: int 
)doc", py::arg("timeout"))
.def("SendMessage", py::overload_cast<uint32, BHandler *>(&BMessenger::SendMessage, py::const_), "", py::arg("command"), py::arg("replyTo")=NULL)
.def("SendMessage", py::overload_cast<BMessage *, BHandler *, bigtime_t>(&BMessenger::SendMessage, py::const_), "", py::arg("message"), py::arg("replyTo")=NULL, py::arg("timeout")=B_INFINITE_TIMEOUT)
.def("SendMessage", py::overload_cast<BMessage *, BMessenger, bigtime_t>(&BMessenger::SendMessage, py::const_), "", py::arg("message"), py::arg("replyTo"), py::arg("timeout")=B_INFINITE_TIMEOUT)
.def("SendMessage", py::overload_cast<uint32, BMessage *>(&BMessenger::SendMessage, py::const_), "", py::arg("command"), py::arg("reply"))
.def("SendMessage", py::overload_cast<BMessage *, BMessage *, bigtime_t, bigtime_t>(&BMessenger::SendMessage, py::const_), "", py::arg("message"), py::arg("reply"), py::arg("deliveryTimeout")=B_INFINITE_TIMEOUT, py::arg("replyTimeout")=B_INFINITE_TIMEOUT)
.def("SetTo", py::overload_cast<const char *, team_id>(&BMessenger::SetTo), "", py::arg("signature"), py::arg("team")=- 1)
.def("SetTo", py::overload_cast<const BHandler *, const BLooper *>(&BMessenger::SetTo), "", py::arg("handler"), py::arg("looper")=NULL)
//.def("operator=", &BMessenger::operator=, "", py::arg("other"))
.def("__eq__", &BMessenger::operator==, "", py::arg("other"))
.def("IsValid", &BMessenger::IsValid, "")
.def("Team", &BMessenger::Team, "")
.def("HashValue", &BMessenger::HashValue, "")
;

m.def("__lt__", py::overload_cast<const BMessenger &, const BMessenger &>(&operator<), "", py::arg("a"), py::arg("b"));

m.def("__ne__", &operator!=, "", py::arg("a"), py::arg("b"));

}
