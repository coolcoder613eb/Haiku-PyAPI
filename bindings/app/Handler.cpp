#include <pybind11/smart_holder.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <app/Handler.h>
#include <Archivable.h>
#include <Messenger.h>
#include <Looper.h>
#include <MessageFilter.h>
#include <List.h>

namespace py = pybind11;
using namespace BPrivate;

py::tuple GetSupportedSuitesWrapper(BHandler& self){
	BMessage message;
	status_t status = self.GetSupportedSuites(&message);
	return py::make_tuple(status, message);
}

PYBIND11_SMART_HOLDER_TYPE_CASTERS(BHandler);

class PyBHandler : public BHandler{
	public:
        using BHandler::BHandler;
        status_t			Archive(BMessage* data, bool deep = true) const override {
        	PYBIND11_OVERLOAD(status_t, BHandler, Archive, data, deep);
        }
        void			MessageReceived(BMessage* message) override {
        	PYBIND11_OVERLOAD(void, BHandler, MessageReceived, message);
        }
        void			SetNextHandler(BHandler* handler) override {
        	PYBIND11_OVERLOAD(void, BHandler, SetNextHandler, handler);
        }
        void			AddFilter(BMessageFilter* filter) override {
        	PYBIND11_OVERLOAD(void, BHandler, AddFilter, filter);
        }
        bool			RemoveFilter(BMessageFilter* filter) override {
        	PYBIND11_OVERLOAD(bool, BHandler, RemoveFilter, filter);
        }
        void			SetFilterList(BList* filters) override {
        	PYBIND11_OVERLOAD(void, BHandler, SetFilterList, filters);
        }
        BHandler*		ResolveSpecifier(BMessage* message, int32 index, BMessage* specifier, int32 what, const char* property) override {
        	PYBIND11_OVERLOAD(BHandler*, BHandler, ResolveSpecifier, message, index, specifier, what, property);
        }
        status_t		GetSupportedSuites(BMessage* data) override {
        	PYBIND11_OVERLOAD(status_t, BHandler, GetSupportedSuites, data);
        }
        status_t		Perform(perform_code d, void* arg) override {
        	PYBIND11_OVERLOAD(status_t, BHandler, Perform, d, arg);
        }
        void 			SendNotices(uint32 what, const BMessage* notice = NULL) override {
        	PYBIND11_OVERLOAD(void, BHandler, SendNotices, what, notice);
        }
};

PYBIND11_MODULE(Handler,m)
{
m.attr("B_OBSERVER_OBSERVE_ALL") = B_OBSERVER_OBSERVE_ALL;
m.attr("B_OBSERVE_WHAT_CHANGE") = B_OBSERVE_WHAT_CHANGE;
m.attr("B_OBSERVE_ORIGINAL_WHAT") = B_OBSERVE_ORIGINAL_WHAT;

py::class_<BHandler, PyBHandler, py::smart_holder>(m, "BHandler",R"doc(
This class handles messages that are passed on by a BLooper.
The BHandler class implements two important pieces of functionality: 
- the foundations for handling messages 
- keeping track of the current state of thing for sending out notifications.
)doc")
.def(py::init<const char *>(), R"doc(
Construct a new handler with a name.

The newly constructed handler is not associated with a looper until you 
explicitly request this to happen. 

:param name: name of the handler.
:type name: str
)doc", py::arg("name")=NULL)
.def(py::init<BMessage *>(), R"doc(
Construct a handler from an archived message.

.. warning::
   This data has to be created using the BHandler::Archive() method. Note that only the name is stored. The filters, the associated looper and the observers are not stored, and should be manually added when you are using this object.

:param data: The message containing the archived data.
:type data: BMessage
)doc", py::arg("data"))
.def_static("Instantiate", &BHandler::Instantiate, R"doc(
Static method to instantiate a handler from an archived message.

:param data: the message containing the archived handler.
:type data: BMessage
:return: the instantiated handler, or ``None`` if the data is not a valid archived BHandler object.
:rtype: BArchivable
)doc", py::arg("data"))
.def("Archive", &BHandler::Archive, R"doc(
Archive a handler to a message.

Currently, only the name is archived. The filters, the associated 
looper and the observers are not stored.

:param data: The message to archive the object in.
:type data: BMessage
:param deep: This parameter is ignored, as BHandler does not have children.
:type deep: bool
:return: ``B_OK`` if success, ``B_BAD_VALUE`` if data parameter is not a valid message.
:rtype: int
)doc", py::arg("data"), py::arg("deep")=true)
.def("Archive", [](const BHandler& self,bool deep){
	BMessage msg;
	status_t status = self.Archive(&msg,deep);
	return py::make_tuple(status,msg);
}, R"doc(
Convenience method to archive the ``BHandler`` into a ``BMessage``.
this verstion returns a tuple containing both the status of the
call and the message containing the archived handler.

:param deep: This parameter is ignored, as BHandler does not have children.
:type deep: bool
:return: A tuple (status,data):

   - ``status`` (int): ``B_OK`` on success, or a Haiku error code
   - ``data`` (BMessage): the message where the handler will be archived.
   
:rtype: tuple
)doc", py::arg("deep")=true)
.def("MessageReceived", &BHandler::MessageReceived, R"doc(
Handle the message that has been received by the associated looper.
This method is reimplemented by subclasses.

:param message: The message that needs to be handled.
:type message: BMessage
)doc", py::arg("message"))
.def("Looper", &BHandler::Looper, R"doc(
Return the looper that this handler is associated with.
If the handler is not yet associated with a looper, it will return ``None``.

:return: the looper that this handler is associated with, or ``None``.
:rtype: BLooper
)doc")
.def("SetName", &BHandler::SetName, R"doc(
Set or change the name of this handler.

:param name: The new name.
:type name: str
)doc", py::arg("name"))
.def("Name", &BHandler::Name, R"doc(
Return the name of this handler.

:return: The name of this handler.
:rtype: str
)doc")
.def("SetNextHandler", &BHandler::SetNextHandler, R"doc(
Set the next handler in the chain that the message is passed on to 
if this handler cannot process it.
But you need 3 conditions:
- This handler should belong to a looper.
- The looper needs to be locked.
- The handler that you pass must be associated with the same looper.

:param handler: The next handler you are going to set.
:type handler: BHandler
)doc", py::arg("handler"))
.def("NextHandler", &BHandler::NextHandler, R"doc(
Return the next hander in the chain to which the message is passed on.

:return: The next handler in the chain.
:rtype: BHandler
)doc")
.def("AddFilter", &BHandler::AddFilter, R"doc(
Add filter as a prerequisite to this handler.

If the handler is associated with a looper, this looper needs to be 
locked in order for this operation to succeed.

:param filter: The filter to add
:type filter: BMessageFilter
)doc", py::arg("filter"))
.def("RemoveFilter", &BHandler::RemoveFilter, R"doc(
Remove filter from the filter list.

If the handler is associated with a looper, this looper needs to be 
locked in order for this operation to succeed.

:param filter: The filter to remove.
:type filter: BMessageFilter
:return: ``True`` if the filter was in the filter list and is removed, ``False`` if the filter was in the filter list and is removed.
:rtype: bool
)doc", py::arg("filter"))
.def("SetFilterList", &BHandler::SetFilterList, R"doc(
Set the internal list of filters to the provided list of filters.

If the handler is associated with a looper, this looper needs to be 
locked in order for this operation to succeed.

The internal list will be replaced with the new list of filters. All 
the existing filters will be deleted.

:param filters: List of filters to use as internal list of filters.
:type filters: BList
)doc", py::arg("filters"))
// TODO test this one below
.def("FilterList", &BHandler::FilterList, R"doc(
Return to the list of filters.

)doc")
.def("LockLooper", &BHandler::LockLooper, R"doc(
Conveninent version of Looper.Lock(), but smarter as it avoids race 
conditions, due to its ability to retrieve the handler's looper and 
lock it in a pseudo-atomic operation.

.. warning::
   Avoid using:
   
   .. code-block:: python
   
      myhandler.Looper().Lock()
      {some code}
      myhandler.Looper().Unlock()
   
   use this function instead and its sibiling for Unlock()
   
:return: ``True`` if the looper is locked, ``False`` if an error acquiring the lock.
:rtype: bool
)doc")
.def("LockLooperWithTimeout", &BHandler::LockLooperWithTimeout, R"doc(
Similar to LockLooper: lock the looper associated with this handler, 
with a time out value. Conveninent and smarter version of 
Blooper.LockWithTimeout(). It avoids race conditions.
See :py:meth:`BHandler.LockLooper`

:param timeout: The time to wait for acquiring the lock in microseconds. You may also use ``B_INFINITE_TIMEOUT``, in which this method will wait as long as it takes to acquire the lock.
:type timeout: int
:return: ``B_OK`` if locking succeeded, ``B_BAD_VALUE`` if this handler is not associated with a looper (anymore), ``B_TIMED_OUT`` if the time specified has passed without locking the looper.
:rtype: int
)doc", py::arg("timeout"))
.def("UnlockLooper", &BHandler::UnlockLooper, R"doc(
Conveninent version of Looper.Unlock(), but smarter as it avoids race 
conditions, due to its ability to retrieve the handler's looper and 
unlock it in a pseudo-atomic operation.

.. warning::
   Avoid using:
   
   .. code-block:: python
   
      myhandler.Looper().Lock()
      {some code}
      myhandler.Looper().Unlock()
   
   use this function instead and its sibiling for Lock()

)doc")
.def("ResolveSpecifier", &BHandler::ResolveSpecifier, R"doc(
Determine the proper handler for a scripting message.
The message is targeted to the BHandler, but the specifiers may indicate 
that it should be assigned to another object; it's the job of ResolveSpecifier() 
to examine the current specifier (or more, if necessary) and return the 
object that should either handle the message or look at the next specifier.
This function is called before the message is dispatched and before any 
filtering functions are called.

:param message: The scripting message to determine the handler.
:type message: BMessage
:param index: The index of the specifier.
:type index: int
:param specifier: The message which contains the specifier.
:type specifier: BMessage
:param what: The 'what' field of the specifier message.
:type what: int
:param property: The name of the target property.
:type property: str
:return: the proper BHandler for the given scripting message.
:rtype: BHandler
)doc", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("what"), py::arg("property"))
.def("GetSupportedSuites", &BHandler::GetSupportedSuites, R"doc(
Report the suites of messages and specifiers that derived classes understand.

:param data: A message containing the data for the operation.
:type data: BMessage
:return: ``B_OK`` or a Haiku's error code
:rtype: int
)doc", py::arg("data"))
.def("GetSupportedSuites", &GetSupportedSuitesWrapper, R"doc(
Convenience method that reports the suites of messages and specifiers 
that derived classes understand.
This version returns a tuple containing both the status of the call 
and the ``BMessage`` containing the supported suites.

:return: A tuple with (status,data):

   - ``status`` (int): ``B_OK`` or a Haiku's error code
   - ``data`` (BMessage): The supported suites
   
:rtype: tuple
)doc")
.def("StartWatching", py::overload_cast<BMessenger, uint32>(&BHandler::StartWatching), R"doc(
Subscribe this handler to watch a specific state change of a target.

Use this method to subscribe messengers to watch state changes in 
this handler, this also means that observers from other teams can 
be subscribed.

:param target: The messenger from which the notifications would be received.
:type target: BMessenger
:param what: The state that needs to be watched.
:type what: int
:return: During the call of this method, a notification will be transmitted using the target. If this works, then this method will return ``B_OK``.
:rtype: int
)doc", py::arg("target"), py::arg("what"))
.def("StartWatchingAll", py::overload_cast<BMessenger>(&BHandler::StartWatchingAll), R"doc(
Subscribe this handler to watch all the state changes of the specified target.

:param target: The messenger from which the notifications would be received.
:type target: BMessenger
:return: During the call of this method, a notification will be transmitted using the target. If this works, then this method will return ``B_OK``.
:rtype: int
)doc", py::arg("target"))
.def("StopWatching", py::overload_cast<BMessenger, uint32>(&BHandler::StopWatching), R"doc(
Unsubscribe this handler from watching a specific state.

This method will unsubscribe this handler from watching a specific event in a target.

:param target: The messenger identifying the previously registered watching target.
:type target: BMessenger
:param what: The state that was being watched.
:type what: int
:return: ``B_OK`` if no error, ``B_BAD_HANDLER`` if the specified BHandler isn't valid.
:rtype: int
)doc", py::arg("target"), py::arg("what"))
.def("StopWatchingAll", py::overload_cast<BMessenger>(&BHandler::StopWatchingAll), R"doc(
Unsubscribe this handler from watching all the state changes of the specified target.

:param target: The messenger identifying the previously registered watching target.
:type target: BMessenger
:return: ``B_OK`` if no error, ``B_BAD_HANDLER`` if the specified BHandler isn't valid.
:rtype: int
)doc", py::arg("target"))
.def("StartWatching", py::overload_cast<BHandler *, uint32>(&BHandler::StartWatching), R"doc(
Subscribe an observer for a specific state change of this handler.
State changes of this handler that match the what argument, will be sent.

:param observer: The observer for this handler.
:type observer: BHandler
:param what: The state that needs to be watched.
:type what: int
:return: During the call of this method, a notification will be transmitted using the observer. If this works, then this method will return ``B_OK``.
:rtype: int
)doc", py::arg("observer"), py::arg("what"))
.def("StartWatchingAll", py::overload_cast<BHandler *>(&BHandler::StartWatchingAll), R"doc(
Subscribe an observer for a all state changes.

:param target: The observer for this handler.
:type target: BHandler
:return: During the call of this method, a notification will be transmitted using the target. If this works, then this method will return ``B_OK``.
:rtype: int
)doc", py::arg("observer"))
.def("StopWatching", py::overload_cast<BHandler *, uint32>(&BHandler::StopWatching), R"doc(
Unsubscribe an observer from watching a specific state.
This method will unsubscribe the specified handler from watching a specific event.

:param observer: The handler that was previously registered as the watching target.
:type observer: BHandler
:param what: The state that was being watched.
:type what: int
:return: ``B_OK`` if no error, ``B_BAD_HANDLER`` if the specified BHandler isn't valid.
:rtype: int
)doc", py::arg("observer"), py::arg("what"))
.def("StopWatchingAll", py::overload_cast<BHandler *>(&BHandler::StopWatchingAll), R"doc(
Unsubscribe an observer from watching all states.
This method will unsubscribe the specified handler from watching all state changes.

:param observer: The handler that was previously registered as the watching target.
:type observer: BHandler
:return: ``B_OK`` if no error, ``B_BAD_HANDLER`` if the specified BHandler isn't valid.
:rtype: int
)doc", py::arg("observer"))
//.def("Perform", &BHandler::Perform, "", py::arg("d"), py::arg("arg"))
.def("Perform", [](BHandler& self, perform_code d, py::object arg = py::none()) {
	void* buffer = nullptr;
	if (!arg.is_none()) {
		py::buffer pybuf = arg.cast<py::buffer>();
		py::buffer_info info = pybuf.request();
		buffer = info.ptr;
	}
	return self.Perform(d, buffer);
},R"doc(
Perform some action. Actually an internal method defined for binary 
compatibility purposes.

.. note::
   Only advanced users should call this. Passing arbitrary data may
   result in undefined behavior.

:param d: code of the action
:type d: int
:param arg: data of the action
:type arg: py::buffer (e.g. bytes, bytearray, numpy.ndarray)
:return: ``B_OK`` on success, or a Haiku error code
:rtype: int
)doc", py::arg("d"), py::arg("arg"))
.def("SendNotices", &BHandler::SendNotices, R"doc(
Emit a state change to the observers.

:param what: The identifier of the state.
:type what: int
:param notice: Any data associated with the state change. Defaults to ``None``
:type notice: BMessage
)doc", py::arg("what"), py::arg("notice")=NULL)
.def("IsWatched", &BHandler::IsWatched, R"doc(
Check if there are any observers watching this handler.

:return: A boolean value ``True`` or ``False`` accordingly.
:rtype: bool
)doc")
.def("__repr__", [](const BHandler& handler) {
    const char* nam = handler.Name();
    if (nam && nam[0] != '\0') {
        return std::string("BHandler(\"") + nam + "\")";
    }
    return std::string("<BHandler>");
})
;


}
