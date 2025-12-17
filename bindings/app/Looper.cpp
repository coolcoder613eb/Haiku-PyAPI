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
.def(py::init_alias<BMessage *>(), "", py::arg("data"))
.def_static("Instantiate", &BLooper::Instantiate, "", py::arg("data"))
.def("Archive", &BLooper::Archive, "", py::arg("data"), py::arg("deep")=true)
.def("PostMessage", py::overload_cast<uint32>(&BLooper::PostMessage), "", py::arg("command"))
.def("PostMessage", py::overload_cast<BMessage *>(&BLooper::PostMessage), "", py::arg("message"))
.def("PostMessage", py::overload_cast<uint32, BHandler *, BHandler *>(&BLooper::PostMessage), "", py::arg("command"), py::arg("handler"), py::arg("replyTo")=NULL)
.def("PostMessage", py::overload_cast<BMessage *, BHandler *, BHandler *>(&BLooper::PostMessage), "", py::arg("message"), py::arg("handler"), py::arg("replyTo")=NULL)
.def("DispatchMessage", &BLooper::DispatchMessage, "", py::arg("message"), py::arg("handler"))
.def("MessageReceived", &BLooper::MessageReceived, "", py::arg("message"))
.def("CurrentMessage", &BLooper::CurrentMessage, "")
.def("DetachCurrentMessage", &BLooper::DetachCurrentMessage, "")
.def("DispatchExternalMessage", [](BLooper& self,BMessage * message,BHandler * handler) {
    bool  _detached;
    self.DispatchExternalMessage(message, handler, _detached);
    return _detached;
}
, "", py::arg("message"), py::arg("handler"))
.def("MessageQueue", &BLooper::MessageQueue, "")
.def("IsMessageWaiting", &BLooper::IsMessageWaiting, "")
.def("AddHandler", &BLooper::AddHandler, "", py::arg("handler"))
.def("RemoveHandler", &BLooper::RemoveHandler, "", py::arg("handler"))
.def("CountHandlers", &BLooper::CountHandlers, "")
.def("HandlerAt", &BLooper::HandlerAt, "", py::arg("index"))
.def("IndexOf", &BLooper::IndexOf, "", py::arg("handler"))
.def("PreferredHandler", &BLooper::PreferredHandler, "")
.def("SetPreferredHandler", &BLooper::SetPreferredHandler, "", py::arg("handler"))
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
