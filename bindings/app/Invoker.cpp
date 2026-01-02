#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <app/Invoker.h>
#include <BeBuild.h>
#include <Messenger.h>
#include <Handler.h>
#include <Looper.h>
#include <AppDefs.h>

namespace py = pybind11;

class PyBInvoker : public BInvoker{
	public:
        using BInvoker::BInvoker;
        status_t			SetMessage(BMessage* message) override {
        	PYBIND11_OVERLOAD(status_t, BInvoker, SetMessage, message);
        }
        status_t			SetTarget(const BHandler* handler, const BLooper* looper = NULL) override {
        	PYBIND11_OVERLOAD(status_t, BInvoker, SetTarget, handler, looper);
        }
        status_t			SetTarget(BMessenger messenger) override {
        	PYBIND11_OVERLOAD(status_t, BInvoker, SetTarget, messenger);
        }
        status_t			SetHandlerForReply(BHandler* handler) override {
        	PYBIND11_OVERLOAD(status_t, BInvoker, SetHandlerForReply, handler);
        }
        status_t			Invoke(BMessage* message = NULL) override {
        	PYBIND11_OVERLOAD(status_t, BInvoker, Invoke, message);
        }
};

py::tuple TargetWrapper(BInvoker& self) {
	BHandler* handler;
	BLooper* looper;

	handler = self.Target(&looper);

	return py::make_tuple(handler, looper);
}

namespace {
std::string FourCC(uint32 code){
    char s[5] = {
        char((code >> 24) & 0xff),
        char((code >> 16) & 0xff),
        char((code >> 8) & 0xff),
        char(code & 0xff),
        0
    };

    for (int i = 0; i < 4; i++)
        if (!isprint((unsigned char)s[i]))
            return "";

    return std::string("'") + s + "'";
	}
}

PYBIND11_MODULE(Invoker,m)
{
py::class_<BInvoker, PyBInvoker>(m, "BInvoker",R"doc(
BInvoker is a convenience class that bundles up everything you 
need to create a handy message-sending package.

The BInvoker contains:
- a BMessage
- a BMessenger (that identifies a target handler)
- an optional BHandler that handles replies. (be_app by default)
)doc")
.def(py::init(), R"doc(
Initializes a BInvoker without a message or target.
)doc")
.def(py::init<BMessage *, const BHandler *, const BLooper *>(), R"doc(
Initializes the BInvoker with message and sets the target to 
either a local handler or as the preferred handler of a local 
looper where the message is sent when ``Invoke()`` is called.

.. note::
   It is not necessary to specify both the handler and the 
   looper, the unused parameter should be passed in as ``None``.
   
:param message: The message to send.
:type message: BMessage
:param handler: The local handler to receive the message, or ``None``.
:type handler: BHandler
:param looper: The local looper to receive the message, or ``None``, defaults to ``None``.
:type looper: BLooper
)doc", py::arg("message"), py::arg("handler"), py::arg("looper")=NULL)
.def(py::init<BMessage *, BMessenger>(), R"doc(
Initializes the BInvoker with message and sets the target 
messenger where the message is sent when ``Invoke()`` is called.
A BMessenger can target either local or remote objects.

:param message: The message to send.
:type message: BMessage
:param target: The messenger where the message is sent when ``Invoke()`` is called.
:type target: BMessenger
)doc", py::arg("message"), py::arg("target"))
.def("SetMessage", &BInvoker::SetMessage, R"doc(
Assigns message to the invoker, deleting any previously 
assigned message.
If you pass ``None`` as parameter you'll delete the current 
message without replacing it.

:param message: The new message or ``None``
:type message: BMessage
:return: ``B_OK``
:rtype: int
)doc", py::arg("message"))
.def("Message", &BInvoker::Message, R"doc(
Return the invoker's message object.

.. note::
   If a message has not been assigned to the invoker 
   this method returns ``None`` instead.

:return: The message assigned to the invoker.
:rtype: BMessage
)doc")
.def("Command", &BInvoker::Command, R"doc(
Return the message's what data member.

.. note::
   If a message has not been assigned to the invoker this 
   method returns ``0`` instead.
   
:return: The command (what) code of the message.
:rtype: int
)doc")
.def("SetTarget", py::overload_cast<const BHandler *, const BLooper *>(&BInvoker::SetTarget), R"doc(
Sets the target to either a local handler or as the 
preferred handler of a local looper.

.. note::
   It is not necessary to specify both the handler and the looper, the unused 
   parameter should be passed in as ``None``.

.. note::
   ``SetTarget()`` doesn't detect invalid BLoopers and BMessengers.

If given only a handler, it must already be attached to a BLooper.
If given only a looper, the message will be sent to its preferred handler.

:param handler: The local handler that will receive now on the messages invoked.
:type handler: BHandler
:param looper: The local looper that will be set as target of the messages invoked.
:type looper: BLooper
:return: ``B_OK`` if the target was successfully set.
         ``B_BAD_VALUE`` if the proposed handler doesn't belong to a BLooper.
         ``B_MISMATCHED_VALUES`` if ``handler`` doesn't belong to ``looper``.
:rtype: int
)doc", py::arg("handler"), py::arg("looper")=NULL)
.def("SetTarget", py::overload_cast<BMessenger>(&BInvoker::SetTarget), R"doc(
Sets the invoker's target to messenger.

.. note::
   A BMessenger target can be used to designate a remote handler (living in another team).

.. note::
   ``SetTarget()`` doesn't detect invalid BLoopers and BMessengers.
   
:param messenger: The messenger to be targeted by the Invoker.
:type messenger: BMessenger
:return: ``B_OK``
:rtype: int
)doc", py::arg("messenger"))
.def("IsTargetLocal", &BInvoker::IsTargetLocal, R"doc(
Return whether or not the invoker and its target belong to the same team.

:return: ``True`` if in the same team, ``False`` otherwise.
:rtype: bool
)doc")
.def("Target", &TargetWrapper, R"doc(
Return a tuple containing the handler and looper the Invoker is pointing to.

:return: A tuple ``(handler,looper)``:
         - ``handler`` (BHandler): the handler the Invoker is pointing to.
         - ``looper`` (BLooper): the looper the Invoker is pointing to.
)doc")
.def("Messenger", &BInvoker::Messenger, R"doc(
Return the BMessenger object that the invoker uses to send its messages.

:return: the messenger used to send messages.
:rtype: BMessenger
)doc")
.def("SetHandlerForReply", &BInvoker::SetHandlerForReply, R"doc(
Set the BHandler object responsible for handling reply messages.

:param handler: The handler responsible for handling reply messages.
:type handler: BHandler
:return: ``B_OK``
:rtype: int
)doc", py::arg("handler"))
.def("HandlerForReply", &BInvoker::HandlerForReply, R"doc(
Return the previously set reply handler or ``None`` if not set.

:return: The reply handler.
:rtype: BHandler or ``None``
)doc")
.def("Invoke", &BInvoker::Invoke, R"doc(
Sends the message to the invoker's target.
If message is ``None`` the default message is sent instead.

.. note::
   This method also sends a ``B_CONTROL_INVOKED`` notification to handlers which registered themselves using StartWatching
   
:param message: The message to send, or the default value ``None``.
:type message: BMessage
:return: ``B_OK`` if the message was sent, ``B_BAD_VALUE`` for no default message, and no message argument, other error forwarded from BMessenger::SendMessage().
:rtype: int
)doc", py::arg("message")=NULL)
.def("InvokeNotify", &BInvoker::InvokeNotify, R"doc(
Send the message to its target, using the notification code specified by kind.
If message is ``None``, no message is sent to the target, but any watchers of the 
invoker's handler will receive their expected notifications.

:param message: The message to send.
:type message: BMessage
:param kind: The notification command code, default ``B_CONTROL_INVOKED``.
:type kind: int
:return: ``B_OK`` if the message was sent, ``B_BAD_VALUE`` for no default message, and no message argument, other error forwarded from BMessenger::SendMessage().
:rtype: int
)doc", py::arg("message"), py::arg("kind")=py::int_('CIVK'))
.def("SetTimeout", &BInvoker::SetTimeout, R"doc(
Set the timeout to use when sending the message to the target.

:param timeout: The time for the timeout, default is ``B_INFINITE_TIMEOUT``
:type timeout: int
:return: ``B_OK``
:rtype: int
)doc", py::arg("timeout"))
.def("Timeout", &BInvoker::Timeout, R"doc(
Return the current timeout value.

:return: The timeout value
:rtype: int
)doc")
.def("__repr__",[](const BInvoker& self){
	int32 what=self.Command();
	std::string repr = "<BInvoker";
	if (what!=0){
		repr += " what=" + std::to_string(what);
		std::string fourcc = FourCC(what);
		if (!fourcc.empty()) {
			repr += " " + fourcc;
		}
	};
	BHandler* handler;
	BLooper* looper = nullptr;
	handler = self.Target(&looper);
	if (handler != nullptr){
		const char* nam = handler->Name();
		if (nam && nam[0] != '\0') {
			repr += " handler=\"";
			repr += nam;
			repr += "\"";
		}
	}
	repr += ">";
	return repr;
})
;


}
