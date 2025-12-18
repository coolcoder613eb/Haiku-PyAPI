#include <pybind11/smart_holder.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <app/Looper.h>
#include <BeBuild.h>
#include <Handler.h>
#include <List.h>
#include <OS.h>
#include <MessageFilter.h>
#include <MessageQueue.h>

namespace py = pybind11;
using namespace BPrivate;

class PyBLooper : public BLooper{
	public:
        using BLooper::BLooper;
		~PyBLooper() override {
			try {
				// Call function overriding the destructor, if any. We can't
				// use PYBIND11_OVERLOAD since that attempts to return from the
				// destructor.
				py::gil_scoped_acquire acquire;
				py::function override = py::get_override(this, "__del__");
				if (override) {
					override();
				}
			} catch (py::error_already_set &e) {
				// Return Python exception back to Python. Throwing from a
				// destructor would crash the program, but we just want Python
				// to print an error message.
				e.discard_as_unraisable(__func__);
			}
        }
        status_t	Archive(BMessage* data, bool deep = true) const override {
        	PYBIND11_OVERLOAD(status_t, BLooper, Archive, data, deep);
        }
        void		DispatchMessage(BMessage* message, BHandler* handler) override {
        	PYBIND11_OVERLOAD(void, BLooper, DispatchMessage, message, handler);
        }
        void		MessageReceived(BMessage* message) override {
        	PYBIND11_OVERLOAD(void, BLooper, MessageReceived, message);
        }
		thread_id	Run()  override {
			py::gil_scoped_acquire acquire;

			// Python should not delete the class after run is called
			// FIXME: What if the Python overload never actually calls
			// BLooper::Run? Then the looper isn't actually running and should
			// still be deletable
			do_not_delete = py::cast(this);

			PYBIND11_OVERLOAD(thread_id, BLooper, Run);
		}
		void		Quit() override {
			{
				py::gil_scoped_acquire acquire;

				// Not sure if it's actually necessary to release the reference
				// to ourselves, since we will delete ourselves anyway.
				// FIXME: What if the Python overload never actually calls
				// BLooper::Quit?
				do_not_delete.release();
			}

			PYBIND11_OVERLOAD(void, BLooper, Quit);
		}
        bool		QuitRequested() override {
        	PYBIND11_OVERLOAD(bool, BLooper, QuitRequested);
        }
        BHandler*	ResolveSpecifier(BMessage* message, int32 index, BMessage* specifier, int32 what, const char* property) override {
        	PYBIND11_OVERLOAD(BHandler*, BLooper, ResolveSpecifier, message, index, specifier, what, property);
        }
        status_t	GetSupportedSuites(BMessage* data) override {
        	PYBIND11_OVERLOAD(status_t, BLooper, GetSupportedSuites, data);
        }
        void		AddCommonFilter(BMessageFilter* filter) override {
        	PYBIND11_OVERLOAD(void, BLooper, AddCommonFilter, filter);
        }
        bool		RemoveCommonFilter(BMessageFilter* filter) override {
        	PYBIND11_OVERLOAD(bool, BLooper, RemoveCommonFilter, filter);
        }
        void		SetCommonFilterList(BList* filters) override {
        	PYBIND11_OVERLOAD(void, BLooper, SetCommonFilterList, filters);
        }
        status_t	Perform(perform_code d, void* arg) override {
        	PYBIND11_OVERLOAD(status_t, BLooper, Perform, d, arg);
        }

	private:
		// holds a reference to our object in Python to prevent Python from
		// deleting us when we're not ready
		py::object do_not_delete;
};

void QuitWrapper(BLooper& self) {
	// When quit is called from the BWindow's thread, it never returns. The
	// thread is destroyed inside of this function. That means we need to
	// release the global interpreter lock since this thread will no longer be
	// running Python code.

	py::gil_scoped_release release;
	self.BLooper::Quit();
		// Avoids calling PyBLooper::Quit

	// If the code reaches this point, the global interpreter lock is
	// reacquired, otherwise, it isn't. Exactly the behaviour we want.
}

PYBIND11_SMART_HOLDER_TYPE_CASTERS(BLooper);

PYBIND11_MODULE(Looper,m)
{
py::class_<BLooper, PyBLooper, BHandler, py::smart_holder>(m, "BLooper",R"doc(
A ``BLooper`` object creates a *message loop* that receives messages that are sent or posted 
to the ``BLooper``. The message loop runs in a separate thread that's spawned (and told to 
run) when the ``BLooper`` receives a ``Run()`` call. If you're creating your own BLooper, 
you can invoke ``Run()`` from within the constructor.

You tell the loop to stop by sending the ``BLooper`` a ``B_QUIT_REQUESTED`` message, which 
invokes the object's ``Quit()`` function. You can also call ``Quit()`` directly, but you 
have to ``Lock()`` the object first.
)doc")
.def(py::init_alias<const char *, int, int>(), R"doc(
   Construct a new BLooper with a priority and an capacity.

   The default priority should be good enough for most tasks. Also, some derived versions 
   of ``BLooper`` will use a specialized priority. So it is advised to leave this setting at 
   the default, unless you know why you would like another setting.
   The constants for priority are located in the OS module
   
   .. code-block:: python
   
      from Be.OS import B_NORMAL_PRIORITY
   
   Loopers use ports to send and receive messages (see the kernel kit). Ports have a maximum 
   capacity; if there are so many messages queued that the port is full, all other incoming 
   messages are dropped. There are situations where the size of the port should be different 
   from the default. This might be when your looper receives a lot of messages, or if the 
   message handling thread runs at a lower priority than normal, which would decrease the 
   processing speed. Finding a suitable value for these custom scenarios would be done by 
   testing.
   
   The new looper is, by default, not running yet. If you have set up everything properly, 
   you may call ``Run()``.
   
   :param name: The name of the looper.
   :type name: str
   :param priority: The priority of the message thread of this looper. The default is ``B_NORMAL_PRIORITY``
   :type priority: int
   :param portCapacity: The maximum port capacity, the default is ``B_LOOPER_PORT_DEFAULT_CAPACITY``
   :type portCapacity: int
   
)doc", py::arg("name")=NULL, py::arg("priority")=B_NORMAL_PRIORITY, py::arg("portCapacity")=B_LOOPER_PORT_DEFAULT_CAPACITY)
.def(py::init_alias<BMessage *>(), R"doc(
   Construct a looper from an archived message.

   The data message has to be constructed by a BLooper::Archive() call. Note that the 
   data that is restored, is merely the port capacity and the name of the looper/handler. 
   Other data, such as filters, is not archived by the default archiver.
   
   .. note::
      This constructor does no type check whatsoever. Since you can pass any BMessage, 
      you should - if you are not sure about the exact type - use the Instantiate() method, 
      which does check the type.
      
   :param data: The archived message containing the looper.
   :type data: BMessage

)doc", py::arg("data"))
.def_static("Instantiate", &BLooper::Instantiate, R"doc(
   Static method to instantiate a looper from an archived message.
   
   :param data: The archived message containing the looper.
   :type data: BMessage
   :return: the instantiated looper, or None if the data is not a valid archived BLooper object.
   :rtype: BArchivable

)doc", py::arg("data"))
/* todo pythonize this */
.def("Archive", &BLooper::Archive, R"doc(
   Archive a looper to a message.
   
   Currently, only the name and the port capacity are archived. Any other data, such 
   as the filters, is not stored.
   
   :param data: The ``BMessage`` object to archive the object in.
   :type data: BMessage
   :param deep: This parameter is ignored, as ``BLooper`` does not have children.
   :type deep: bool
   :return: one of these:
   
      - ``B_OK`` if success
      - ``B_BAD_VALUE`` if the data parameter is not a valid message.
      
   :rtype: int
   
)doc", py::arg("data"), py::arg("deep")=true)
.def("PostMessage", py::overload_cast<uint32>(&BLooper::PostMessage), R"doc(
   Post a message with the *command* as ``what`` identifier to this looper.
   
   :param command: The what identifier of the message to be sent.
   :type command: int
   :return: one of these:
   
      - ``B_OK	if the operation succeeded, and the message is sent to the port.
      - ``B_ERROR`` if there was a general operation error.
      - ``B_BAD_VALUE`` if this looper is not yet running and therefore cannot receive messages.
      
   :rtype: int
   
)doc", py::arg("command"))
.def("PostMessage", py::overload_cast<BMessage *>(&BLooper::PostMessage), R"doc(
   Post a message to this looper.

   Posting a message puts it in the message queue. The message passes through the 
   default handler chain.
   
   :param message: The message you would like to pass to this method.
   :type message: int
   :return: one of these:
   
      - ``B_OK	if the operation succeeded, and the message is sent to the port.
      - ``B_ERROR`` if there was a general operation error.
      - ``B_BAD_VALUE`` if this looper is not yet running and therefore cannot receive messages.
      
   :rtype: int

)doc", py::arg("message"))
.def("PostMessage", py::overload_cast<uint32, BHandler *, BHandler *>(&BLooper::PostMessage), R"doc(
   Sends a message with *command* ``what`` identifier to the handler associated with 
   this looper. A response may be sent to the *replyTo* handler asynchronously.

   The target handler should be associated with this looper. This method 
   bypasses the default message queue.
   
   :param command: The value you want as the message's what identifier.
   :type command: int
   :param handler: The handler you would like to pass this message to.
   :type handler: BHandler
   :param replyTo: If you would like to request a reply, pass the handler to which this reply should be directed to. If you pass ``None``, you will not receive a reply.
   :type replyTo: BHandler
   :return: one of these:
   
      - ``B_OK	if the operation succeeded, and the message is sent to the port.
      - ``B_ERROR`` if there was a general operation error.
      - ``B_BAD_VALUE`` if this looper is not yet running and therefore cannot receive messages.
      - ``B_MISMATCHED_VALUES`` if the handler is not associated with this looper.
      
   :rtype: int
)doc", py::arg("command"), py::arg("handler"), py::arg("replyTo")=NULL)
.def("PostMessage", py::overload_cast<BMessage *, BHandler *, BHandler *>(&BLooper::PostMessage), R"doc(
   Send a message to the handler associated with this looper. A response may 
   be sent to the *replyTo* handler asynchronously.
   
   The target handler should be associated with this looper. This method 
   bypasses the default message queue.
   
   :param message: The message you want to pass.
   :type message: BMessage
   :param handler: The handler you would like to pass this message to.
   :type handler: BHandler
   :param replyTo: If you would like to request a reply, pass the handler to which this reply should be directed to. If you pass ``None``, you will not receive a reply.
   :type replyTo: BHandler
   :return: one of these:
   
      - ``B_OK	if the operation succeeded, and the message is sent to the port.
      - ``B_ERROR`` if there was a general operation error.
      - ``B_BAD_VALUE`` if this looper is not yet running and therefore cannot receive messages.
      - ``B_MISMATCHED_VALUES`` if the handler is not associated with this looper.
      
   :rtype: int
   
)doc", py::arg("message"), py::arg("handler"), py::arg("replyTo")=NULL)
.def("DispatchMessage", &BLooper::DispatchMessage, R"doc(
   Dispatch a message to a handler. Override if there are messages that 
   you want to catch before they are sent to the handlers.

   This method is called by the message looping thread to dispatch a message 
   to handler. If you implement the ``BLooper`` class and your looper receives 
   messages that absolutely have to be processed by the looper instead of any 
   of the handlers, override this method. For example, the default implementation 
   catches ``B_QUIT_REQUESTED`` messages before they are sent to the handlers, 
   so that the looper will quit at those messages.

   You are discouraged from using this method to filter out any messages you 
   do not want to process. For this, there is a more generic method using the 
   ``BMessageFilter`` class. If you want to skip messages with certain patterns, 
   have a look at the ``AddCommonFilter()`` and ``SetCommonFilterList()`` methods.

   If you do override this method, please remember to call the ``DispatchMessage()`` 
   method of the parent class.
   
   :param message: The message to dispatch.
   :type message: BMessage
   :param handler: The handler that will receive the message.
   :type handler: BHandler

)doc", py::arg("message"), py::arg("handler"))
.def("MessageReceived", &BLooper::MessageReceived, R"doc(
   Process a message received by the internal handler of this looper.

   Derived from ``BHandler.MessageReceived()``
   
   :param message: The received message to be processed.
   :type message: BMessage

)doc", py::arg("message"))
.def("CurrentMessage", &BLooper::CurrentMessage, R"doc(
   Retrieve the current message.
   
   .. note::
      Only call this method from within the thread that processes the messages. It contains 
      a pointer to the message that is currently being handled. Due to the multithreaded 
      nature of the operating system, this method will not safely let you read the message 
      that is being processed by this handler from outside the context of the processing. 
      If you do want to use a message outside of the processing thread, have a look at 
      ``DetachCurrentMessage()`` to safely retrieve a message.
      Haiku Book explains that calling this function from outside the thread that processes 
      the message, could give you a NULL pointer or an invalid pointer.
      
   :return: the message that is currently being processed.
   :rtype: BMessage
   
)doc")
.def("DetachCurrentMessage", &BLooper::DetachCurrentMessage, R"doc(
   Get ownership of the message currently being processed.

   Retrieve the current message and gain ownership of it. This means that 
   the message will not be deleted as soon as the looper is done processing 
   it. You can then use it for different purposes.
   
   .. note::
      Only call this method from within the thread that processes the messages. Due to the 
      multithreaded nature of the operating system, calling it from another thread is very 
      likely to give you an invalid or a NULL pointer.
      
   :return: The message currently being processed.
   :rtype: BMessage

)doc")
.def("DispatchExternalMessage", [](BLooper& self,BMessage * message,BHandler * handler) {
    bool  _detached;
    self.DispatchExternalMessage(message, handler, _detached);
    return _detached;
}
, R"doc(
   Internal method to support single-threaded GUI toolkits.
   
   :param message: message
   :type message: BMessage
   :param handler: handler
   :type handler: BHandler

)doc", py::arg("message"), py::arg("handler"))
.def("MessageQueue", &BLooper::MessageQueue, R"doc(
   Return the internal message queue of this looper.
   You can then manipulate the message queue. Note that the message 
   that is being processed is already detached from this queue.
   
   :return: the internal message queue.
   :rtype: BMessageQueue

)doc")
.def("IsMessageWaiting", &BLooper::IsMessageWaiting, R"doc(
   Check if there is a message waiting.
   
   :return: ``True`` if there are still messages to be processed, ``False`` if there is no message waiting.
   :rtype: bool

)doc")
.def("AddHandler", &BLooper::AddHandler, R"doc(
   Associate a handler to this looper.

   The handler will be associated to this looper. By default, the handler 
   in this looper will be chained to the supplied handler.
   
   :param handler: The handler to associate with this looper. If the handler is already associated to another looper, the operation will fail silently. Check beforehand if you cannot be sure that the handler is unassociated.
   :type handler: BHandler
   
)doc", py::arg("handler"))
.def("RemoveHandler", &BLooper::RemoveHandler, R"doc(
   Disassociate a handler from this looper.

   If the handler is disassociated, it can be reassociated to another looper.
   
   :param handler: the handler to dissociate
   :type handler: BHandler
   :return: ``True`` if the handler has been removed from this looper, ``False`` The handler was invalid or the handler was not associated to this looper.
   :rtype: bool
   
)doc", py::arg("handler"))
.def("CountHandlers", &BLooper::CountHandlers, R"doc(
   Get the number of handlers associated with this looper.
   
   :return: the number of handlers.
   :rtype: int

)doc")
.def("HandlerAt", &BLooper::HandlerAt, R"doc(
   Get the handler at an index of the list of associated handlers.
   
   :param index: the index.
   :type index: int
   :return: the handler at the specific index provided
   :rtype: BHandler

)doc", py::arg("index"))
.def("IndexOf", &BLooper::IndexOf, R"doc(
   Get the index of the handler that is in the associated handler list.
   
   :param handler: The handler whose index you want to retrieve.
   :type handler: BHandler
   :return: The zero-based index of the handler if in the list of handlers, otherwise ``-1``.
   :rtype: int
   
)doc", py::arg("handler"))
.def("PreferredHandler", &BLooper::PreferredHandler, R"doc(
   Get the preferred handler.

   :return: The preferred handler, or ``None`` if none is set.
   :rtype: BHandler

)doc")
.def("SetPreferredHandler", &BLooper::SetPreferredHandler, R"doc(
   Set a preferred handler.

   If messages are posted to this looper using one of the ``PostMessage()`` methods 
   without a specific BHandler argument, the messages will be handled by the looper 
   itself (since a looper is a subclass of BHandler, this is perfectly possible). 
   If you want to override that behavior, you should set a preferred handler. This 
   handler will be called if incoming messages do not ask to be directly passed on 
   to a specific handler.
   
   If you want to unset the preferred handler, pass ``None``. If the supplied handler 
   is not associated with this looper, this call will fail silently and the current 
   preferred handler will be unset.
   
   :param handler: The preferred handler you want undesignated messages to be handled by.
   :type handler: BHandler
   
)doc", py::arg("handler"))
.def("Run", &BLooper::Run, "")
.def("Loop", &BLooper::Loop, "")
.def("Quit", &QuitWrapper, "")
.def("QuitRequested", &BLooper::QuitRequested, "")
.def("Lock", &BLooper::Lock, "")
.def("Unlock", &BLooper::Unlock, "")
.def("IsLocked", &BLooper::IsLocked, "")
.def("LockWithTimeout", &BLooper::LockWithTimeout, "", py::arg("timeout"))
.def("Thread", &BLooper::Thread, "")
.def("Team", &BLooper::Team, "")
.def_static("LooperForThread", &BLooper::LooperForThread, "", py::arg("thread"))
.def("LockingThread", &BLooper::LockingThread, "")
.def("CountLocks", &BLooper::CountLocks, "")
.def("CountLockRequests", &BLooper::CountLockRequests, "")
.def("Sem", &BLooper::Sem, "")
.def("ResolveSpecifier", &BLooper::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("what"), py::arg("property"))
.def("GetSupportedSuites", &BLooper::GetSupportedSuites, "", py::arg("data"))
.def("AddCommonFilter", &BLooper::AddCommonFilter, "", py::arg("filter"))
.def("RemoveCommonFilter", &BLooper::RemoveCommonFilter, "", py::arg("filter"))
.def("SetCommonFilterList", &BLooper::SetCommonFilterList, "", py::arg("filters"))
.def("CommonFilterList", &BLooper::CommonFilterList, "")
.def("Perform", &BLooper::Perform, "", py::arg("d"), py::arg("arg"))
;

m.attr("B_LOOPER_PORT_DEFAULT_CAPACITY") = B_LOOPER_PORT_DEFAULT_CAPACITY;

}
