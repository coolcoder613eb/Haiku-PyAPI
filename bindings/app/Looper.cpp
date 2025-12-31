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
   :param portCapacity: The maximum port capacity, the default is ``B_LOOPER_PORT_DEFAULT_CAPACITY`` (200)
   :type portCapacity: int
   
)doc", py::arg("name")=NULL, py::arg("priority")=B_NORMAL_PRIORITY, py::arg("portCapacity")=B_LOOPER_PORT_DEFAULT_CAPACITY)
.def(py::init_alias<BMessage *>(), R"doc(
   Construct a looper from an archived message.

   The data message has to be constructed by a BLooper::Archive() call. Note that the 
   data that is restored, is merely the port capacity and the name of the looper/handler. 
   Other data, such as filters, is not archived by the default archiver.
   
   .. warning::
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
   :return: The instantiated looper, or None if the data is not a valid archived BLooper object.
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
:return: One of these:
   
      - ``B_OK`` if success
      - ``B_BAD_VALUE`` if the data parameter is not a valid message.
      
:rtype: int
   
)doc", py::arg("data"), py::arg("deep")=true)
.def("Archive", [](const BLooper& self,bool deep){
	BMessage msg;
	status_t status = self.Archive(&msg,deep);
	return py::make_tuple(status,msg);
}, R"doc(
   Convenience method to archive the ``BLooper`` into a ``BMessage``.
   this verstion returns a tuple containing both the status of the
   call and the message containing the archived looper.

   Currently, only the name and the port capacity are archived. Any other data, such 
   as the filters, is not stored.

:param deep: If ``True``, perform a deep archive of all contained objects.
:type deep: bool
:return: A tuple (status,data):

   - ``status`` (int): ``B_OK`` on success, or a Haiku error code
   - ``data`` (BMessage): the message where the looper will be archived.
   
:rtype: tuple
)doc", py::arg("deep")=true)
.def("PostMessage", py::overload_cast<uint32>(&BLooper::PostMessage), R"doc(
   Post a message with the *command* as ``what`` identifier to this looper.
   
:param command: The what identifier of the message to be sent.
:type command: int
:return: One of these:
   
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
:return: One of these:
   
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
:return: One of these:
   
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
:return: One of these:
   
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
   
   .. warning::
      Only call this method from within the thread that processes the messages. It contains 
      a pointer to the message that is currently being handled. Due to the multithreaded 
      nature of the operating system, this method will not safely let you read the message 
      that is being processed by this handler from outside the context of the processing. 
      If you do want to use a message outside of the processing thread, have a look at 
      ``DetachCurrentMessage()`` to safely retrieve a message.
      Haiku Book explains that calling this function from outside the thread that processes 
      the message, could give you a NULL pointer or an invalid pointer.
      
   :return: The message that is currently being processed.
   :rtype: BMessage
   
)doc")
.def("DetachCurrentMessage", &BLooper::DetachCurrentMessage, R"doc(
   Get ownership of the message currently being processed.

   Retrieve the current message and gain ownership of it. This means that 
   the message will not be deleted as soon as the looper is done processing 
   it. You can then use it for different purposes.
   
   .. warning::
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
   
   :return: The internal message queue.
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
   
   :param handler: The handler to dissociate
   :type handler: BHandler
   :return: ``True`` if the handler has been removed from this looper, ``False`` The handler was invalid or the handler was not associated to this looper.
   :rtype: bool
   
)doc", py::arg("handler"))
.def("CountHandlers", &BLooper::CountHandlers, R"doc(
   Get the number of handlers associated with this looper.
   
   :return: The number of handlers.
   :rtype: int

)doc")
.def("HandlerAt", &BLooper::HandlerAt, R"doc(
   Get the handler at an index of the list of associated handlers.
   
   :param index: The index.
   :type index: int
   :return: The handler at the specific index provided
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
.def("Run", &BLooper::Run, R"doc(
   Start the event loop.
   After the looper has been constructed, it needs to be started using this method. 
   A thread will be spawned, which will receive messages.
   Make sure the looper is not yet running before you call this method.
   
   :return: A (positive) thread id if spawning the thread succeeded, or an error code.
   :rtype: int

)doc")
.def("Loop", &BLooper::Loop, R"doc(
   Run the event loop in the current thread.
   This method runs the event loop in an already existing thread. It blocks until the 
   looper stops looping. This can be used to turn an existing thread into a BLooper.
   Make sure the looper is not yet running before you call this method.
   
   :return: The thread ID of the thread that was running the loop.
   :rtype: thread_id
   
)doc")
.def("Quit", &QuitWrapper, R"doc(
   Hook method that is called after a ``B_QUIT_REQUESTED`` message.
   If you want to quit and delete the looper, you should post a ``B_QUIT_REQUESTED`` 
   message. This will first call the hook method ``QuitRequested()``, which can be overridden 
   in child classes in case there are conditions that would prevent the looper to be quit. 
   If you really know what you are doing, and you definitely want to quit this looper, 
   you may call this method, but only after performing a ``Lock()`` operation.
   
   Override this method if your subclass needs to perform specific clean-up tasks. Remember 
   to call the base class implementation when you're done.

   .. note::
   
      You will not have to delete the looper object, if a looper quits it will delete itself.
      
)doc")
.def("QuitRequested", &BLooper::QuitRequested, R"doc(
   Hook method that is called during a ``B_QUIT_REQUESTED`` message.
   This hook function is called by the looper thread when a ``B_QUIT_REQUESTED`` is received. 
   The default implementation always accepts the message, but if your subclass needs a 
   special condition to be met before actually accepting a quit message, you can test for 
   that condition in this hook method. A good example is a window (which is a derivative of 
   ``BLooper``), which contains a modified document. The condition may be that a modal dialog 
   requesting a path of action is closed.
   
   :return: A boolean value:
      
      ``True`` if the looper can be quit and destroyed 
      ``False`` if this method does not accept the quit message and continue processing messages.
      
   :rtype: bool
   
)doc")
.def("Lock", &BLooper::Lock, R"doc(
   Lock the looper.
   For most operations involving the internal data of the looper, you need to hold the lock. 
   Each looper implements a global lock, which you can use to perform operations on internal 
   data in a thread-safe manner.
   Do not forget to pair each ``Lock()`` request with an ``Unlock()`` request. ``Lock()`` requests 
   can be stacked, which means that recursively locking a looper from a thread that actually holds 
   the lock, will not cause a deadlock. See ``BLocker`` for more information on locking internals.

   :return: A boolean value:
   
      ``True`` if the locking request succeeded
      ``False`` if the locking request could not be completed. There are a variety of reasons for this to happen, for example when the looper is destroyed.
      
   :rtype: bool
   
)doc")
.def("Unlock", &BLooper::Unlock, R"doc(
   Unlock a locked looper.
   Use this method paired with ``Lock()`` calls, to release a lock. Make sure that this method is only 
   called on a locked looper.
   
)doc")
.def("IsLocked", &BLooper::IsLocked, R"doc(
   Check if a looper is locked.

   :return: A boolean value:
   
      ``True`` if the looper is locked
      ``False`` if the looper is not locked, or the looper has been deleted
      
   :rtype: bool
   
)doc")
.def("LockWithTimeout", &BLooper::LockWithTimeout, R"doc(
   Lock a looper with a timeout.
   This method locks the looper like ``Lock()``, but if the locking request does not succeed 
   within the provided timeout, the method will return.
   
   :param timeout: The maximum time to wait for the lock request to succeed.
   :type timeout: int
   :return: One of these values:
   
      - ``B_OK`` The lock is acquired
      - ``B_BAD_VALUE`` The looper has been destroyed
      - other errors: There was an error acquiring the lock
      
   :rtype: int
   
)doc", py::arg("timeout"))
.def("Thread", &BLooper::Thread, R"doc(
   Return the thread id of the internal message looper thread.
   If the looper is not yet running, this method will return ``0``.
   
   :return: The thread id of the internal message looper thread, or ``0``
   :rtype: thread_id

)doc")
.def("Team", &BLooper::Team, R"doc(
   Return the team id in which this looper exists.

   :return: The team id in which this looper exists.
   :rtype: int
   
)doc")
.def_static("LooperForThread", &BLooper::LooperForThread, R"doc(
   Static method to retrieve a BLooper for a specified thread.

   :param thread: The ID of the thread for which you want to find the looper.
   :type thread: thread_id
   :return: The looper for the specified thread.
   :rtype: BLooper

)doc", py::arg("thread"))
/*    debugging funcs     */
.def("LockingThread", &BLooper::LockingThread, R"doc(
   Return the thread id of the thread that currently holds the lock.

   .. warning::
   
      This methods may aid you in debugging problems when they occur, but do not use it 
      in actual production code. This method is unreliable because it isn't thread-safe, 
      and as such are only useful in specific debugging situations. 
      Handle with care.

:return: the thread id of the thread that currently holds the lock.
:rtype: thread_id
)doc")
.def("CountLocks", &BLooper::CountLocks, R"doc(
   Return the number of recursive locks that are currently being held 
   on this looper.
   
   .. warning::
   
      This methods may aid you in debugging problems when they occur, but do not use it 
      in actual production code. This method is unreliable because it isn't thread-safe, 
      and as such are only useful in specific debugging situations. 
      Handle with care.
      
   :return: the number of recursive locks held on by this looper.
   :rtype: int
   
)doc")
.def("CountLockRequests", &BLooper::CountLockRequests, R"doc(
   Return the number of pending locks.

   .. warning::
   
      This methods may aid you in debugging problems when they occur, but do not use it 
      in actual production code. This method is unreliable because it isn't thread-safe, 
      and as such are only useful in specific debugging situations. 
      Handle with care.
      
   :return: the number of pending locks.
   :rtype: int

)doc")
.def("Sem", &BLooper::Sem, R"doc(
   Return the id of the semaphore that is used to lock this looper.

   .. warning::
   
      This methods may aid you in debugging problems when they occur, but do not use it 
      in actual production code. This method is unreliable because it isn't thread-safe, 
      and as such are only useful in specific debugging situations. 
      Handle with care.
      
   :return: the semaphore used to lock this looper.
   :rtype: sem_id
   
)doc")
/////////////////////////////////////
.def("ResolveSpecifier", &BLooper::ResolveSpecifier, R"doc(
   Determine the proper handler for a scripting message.
   
   :param message: The scripting message to determine the handler.
   :type message: BMessage
    param index: The index of the specifier.
   :type index: int
   :param specifier: The message which contains the specifier.
   :type specifier: BMessage
    param what: The ``what`` field of the specifier message.
   :type what: int
   :param property: The name of the target property.
   :type property: str

)doc", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("what"), py::arg("property"))
/* non pythonic version */
.def("GetSupportedSuites", &BLooper::GetSupportedSuites, R"doc(
   Report the suites of messages and specifiers that derived classes understand.
   This method fills a passed ``BMessage``.
   
:param data: The message that will be filled with the supported suites.
:type data: BMessage
:return: the status retuned by the call. ``B_OK`` success or a Haiku's error code
:rtype: int
   
)doc", py::arg("data"))
/* pythonic version */
.def("GetSupportedSuites", [](BLooper& self) {
    BMessage msg;
    status_t status = self.GetSupportedSuites(&msg);
    return py::make_tuple(status, msg); 
}, R"doc(
   This is a convenience methond that reports the suites of messages 
   and specifiers that derived classes understand.
   This versions return a tuple containing the status of the call and
   the ``BMessage`` containing the supported suites.
   
:return: A tuple containing ``(status, data)``:
   
      - ``status`` (int): the returned status of the call
      - ``data`` (BMessage): the message containing the supported suites
      
:rtype: tuple
   
)doc")
.def("AddCommonFilter", &BLooper::AddCommonFilter, R"doc(
   Add a common filter to the list of filters that are applied to all incoming messages.

   Filters can only be applied once, so they cannot be shared between loopers, a handler 
   and a looper or between two handlers.
   
   :param filter: common filter to apply to all incoming messages.
   :type filter: BMessageFilter

)doc", py::arg("filter"))
.def("RemoveCommonFilter", &BLooper::RemoveCommonFilter, R"doc(
   Remove a filter from the common message filter list.
   
   :param filter: The filter to remove.
   :type filter: BMessageFilter
   :return: ``True`` if successful, or ``False`` if it can't find the specified filter.
   :rtype: bool

)doc", py::arg("filter"))
.def("SetCommonFilterList", &BLooper::SetCommonFilterList, R"doc(
   Set a new list of filters that need to be applied to all incoming messages.
   You are responsible for validating that all the items in the list of filters are 
   actual filters. The old list is discarded.
   
   .. note::
   
      filters can only be applied to one looper or handler. If any of the filters is already associated with another one, this call will fail.
      
   :param filters: The new list of filters.
   :type filters: BList
   
)doc", py::arg("filters"))
.def("CommonFilterList", &BLooper::CommonFilterList, R"doc(
   Return a list of filters applied to all incoming messages.
   
   .. warning::
   
      You should use the internal list management functions to manipulate the internal filter list, in order to maintain internal consistency.
   
   :return: the internal filter list, or ``None`` if such a list has not yet been created.
   :rtype: BList

)doc")
//.def("Perform", &BLooper::Perform, "", py::arg("d"), py::arg("arg"))
.def("Perform", [](BLooper& self, perform_code d, py::object arg = py::none()) {
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
)doc",py::arg("d"), py::arg("arg"))
;

m.attr("B_LOOPER_PORT_DEFAULT_CAPACITY") = B_LOOPER_PORT_DEFAULT_CAPACITY;

}
