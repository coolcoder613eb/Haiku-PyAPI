#include <pybind11/smart_holder.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <app/Application.h>
#include <AppDefs.h>
#include <InterfaceDefs.h>
#include <Looper.h>
#include <Messenger.h>
#include <Point.h>
#include <Rect.h>
#include <Cursor.h>
#include <Window.h>
#include <Resources.h>
#include <Roster.h>

namespace py = pybind11;
using namespace BPrivate;

void RunWrapper(BApplication& self) {
	// Why release the gil (global interpreter lock) here? Because its a long-
	// running function (it usually runs for the lifetime of the application).
	// See https://pybind11.readthedocs.io/en/stable/advanced/misc.html#global-interpreter-lock-gil
	// for more details.
	py::gil_scoped_release release;
	self.Run();
}

void QuitWrapper(BApplication& self) {
	// For an explanation, see QuitWrapper in Looper.cpp
	py::gil_scoped_release release;
	self.Quit();
}

void ArgvReceivedWrapper(BApplication& self, int32 argc, std::vector<char*> argv) {
	self.ArgvReceived(argc, argv.data());
}
py::tuple GetSupportedSuitesWrapper(BApplication& self){
	BMessage message;
	status_t status = self.GetSupportedSuites(&message);
	return py::make_tuple(status, message);
}
py::tuple GetAppInfoWrapper(BApplication& self){
	app_info info;
	status_t status = self.GetAppInfo(&info);
	return py::make_tuple(status, info);
}
class PyBApplication : public BApplication{
	public:
        using BApplication::BApplication;
        void ReadyToRun() override {
            PYBIND11_OVERLOAD(void, BApplication, ReadyToRun);
        }
        bool QuitRequested() override {
            PYBIND11_OVERLOAD(bool, BApplication, QuitRequested);
        }
        status_t			Archive(BMessage* data, bool deep = true) const override {
            PYBIND11_OVERLOAD(status_t, BApplication, Archive, data, deep);
        }
        thread_id			Run() override {
            // There is no need to release the GIL here like RunWrapper. Here,
            // the GIL starts off unacquired, whereas in RunWrapper, the GIL
            // starts off acquired. Here, only if pybind sees that there
            // is a Python function overriding Run that needs to be run will
            // it acquire the GIL. Otherwise, it stays unacquired.
            PYBIND11_OVERLOAD(thread_id, BApplication, Run);
        }
        void				Quit() override {
            PYBIND11_OVERLOAD(void, BApplication, Quit);
        }
        void				Pulse() override {
            PYBIND11_OVERLOAD(void, BApplication, Pulse);
        }
        void				MessageReceived(BMessage* message) override {
            PYBIND11_OVERLOAD(void, BApplication, MessageReceived, message);
        }
        void ArgvReceived(int32 argc, char** argv) override {
            pybind11::gil_scoped_acquire gil;
            pybind11::function override = pybind11::get_override(static_cast<const BApplication*>(this), "ArgvReceived");
            if (override) {
		        // It exists! Let's call it.
	            std::vector<char*> args;
			    for (int32 i = 0; i < argc; ++i) {
                    args.push_back(argv[i]);
                }

                override(argc, args);
            } else {
                // Doesn't exist. Let's call the default ArgvReceived instead
                BApplication::ArgvReceived(argc, argv);
            }
        }

        void				AppActivated(bool active) override {
            PYBIND11_OVERLOAD(void, BApplication, AppActivated, active);
        }
        void				RefsReceived(BMessage* message) override {
            PYBIND11_OVERLOAD(void, BApplication, RefsReceived, message);
        }
        void				AboutRequested() override {
            PYBIND11_OVERLOAD(void, BApplication, AboutRequested);
        }
        BHandler*			ResolveSpecifier(BMessage* message, int32 index, BMessage* specifier, int32 form, const char* property) override {
            PYBIND11_OVERLOAD(BHandler*, BApplication, ResolveSpecifier, message, index, specifier, form, property);
        }
        void				DispatchMessage(BMessage* message, BHandler* handler) override {
            PYBIND11_OVERLOAD(void, BApplication, DispatchMessage, message, handler);
        }
        status_t			GetSupportedSuites(BMessage* data) override {
            PYBIND11_OVERLOAD(status_t, BApplication, GetSupportedSuites, data);
        }
        status_t			Perform(perform_code d, void* arg) override {
            PYBIND11_OVERLOAD(status_t, BApplication, Perform, d, arg);
        }
};


PYBIND11_SMART_HOLDER_TYPE_CASTERS(BApplication);

PYBIND11_MODULE(Application,m)
{
py::module_::import("Be.Messenger");
py::class_<BApplication,PyBApplication,BLooper, py::smart_holder>(m, "BApplication",R"doc(
BApplication represents a Haiku application. It manages the application’s
message loop, windows, event handling, and overall lifecycle. Applications
should subclass BApplication to implement behavior for messages, events, 
and scripting interfaces.
)doc")
.def(py::init<const char *>(), R"doc(
Create a new application with the given application signature.
:param signature: A MIME type string that must have the supertype "application".
:type signature: str
)doc", py::arg("signature"))
// ############### TODO ACT this one won't work as status_t is an int and it's immutable ############
.def(py::init<const char *, status_t *>(), R"doc(
Create a new application and return an error code if initialization fails.

:param signature: A MIME type string that must have the supertype "application".
:type signature: str
:param error: Pointer to a status_t variable that receives the initialization status.
:type error: int
)doc", py::arg("signature"), py::arg("error"))
// ###############################################################################
.def(py::init<BMessage *>(), R"doc(
Reconstruct an application from archived data stored in a BMessage.

:param data: BMessage containing archived application state.
:type data: BMessage
)doc", py::arg("data"))
.def_static("Instantiate", &BApplication::Instantiate, R"doc(
Return a new instance of the application based on archived data.

:param data: The archived data
:type data: BMessage
:return: Returns a BArchivable, regardless the actual class in which it's implemented
:rtype: BArchivable
)doc", py::arg("data"))
.def("Archive", &BApplication::Archive, R"doc(
Archive the BApplication object into a BMessage.

:param data: BMessage object where the application will be archived.
:type data: BMessage
:param deep: If ``True``, perform a deep archive of all contained objects.
:type deep: bool
:return: ``B_OK`` on success, or a Haiku error code
:rtype: int
)doc", py::arg("data"), py::arg("deep")=true)
.def("InitCheck", &BApplication::InitCheck, R"doc(
Return the status of the constructor.

:return: ``B_OK`` on success, or a Haiku error code
:rtype: int
)doc")
.def("Run", &RunWrapper, R"doc(
Start the application's message loop. This call blocks until the application quits.

:return: The thread ID of the application's message loop.
:rtype: int
)doc")
.def("Quit", &QuitWrapper, R"doc(
Request the application to quit. Will call QuitRequested() on each window.
)doc")
.def("QuitRequested", &BApplication::QuitRequested, R"doc(
Called before quitting; return ``True`` to allow the application to quit.

:return: ``True`` if quitting is allowed, ``False`` to cancel.
:rtype: bool
)doc")
.def("Pulse", &BApplication::Pulse, R"doc(
Called periodically if a pulse rate has been set via SetPulseRate().
)doc")
.def("ReadyToRun", &BApplication::ReadyToRun, R"doc(
Called once before Run() begins processing messages, when the application is ready.
)doc")
.def("MessageReceived", &BApplication::MessageReceived, R"doc(
Handle messages sent to the application.

:param message: The BMessage to process.
:type message: BMessage
)doc", py::arg("message"))
.def("ArgvReceived", &ArgvReceivedWrapper, R"doc(
Called when the application receives command-line arguments.

:param argc: Number of arguments.
:type argc: int
:param argv: List of argument strings.
:type argv: list
)doc", py::arg("argc"), py::arg("argv"))
//.def("ArgvReceivedWrapper", &PyBApplication::ArgvReceivedWrapper, "", py::arg("args"))  // Usare il metodo wrapper qui
.def("AppActivated", &BApplication::AppActivated,R"doc(
Hook method that gets invoked when the application receives ``B_APP_ACTIVATED`` message.
The message is sent when the application gains or loses active application status.

:param active: ``True`` means your application is now active, otherwise ``False``.
:type active: bool
)doc", py::arg("active"))
.def("RefsReceived", &BApplication::RefsReceived, R"doc(
Hook function that's called when the application receives a ``B_REFS_RECEIVED`` message. 
The message is sent when the user drops a file (or files) on your app's icon, or 
double clicks a file that's handled by your app. 
The message can arrive either at launch time, or while your application is already 
running use IsLaunching() to tell which.

:param message: The message containing a single field named ``be:refs`` that contains one or more ``entry_ref``
:type message: BMessage
)doc", py::arg("message"))
.def("AboutRequested", &BApplication::AboutRequested, R"doc(
Hook function that's invoked when the BApplication receives a ``B_ABOUT_REQUESTED`` message.
)doc")
.def("ResolveSpecifier", &BApplication::ResolveSpecifier, R"doc(
ResolveSpecifier(message: BMessage, index: int, specifier: BMessage, form: int, property: BMessage)
Determine the proper handler for a scripting message.

:param message: The scripting message.
:type message: BMessage
:param index: The index in the specifier array of message.
:type index: int
:param specifier: The specifier.
:type specifier: BMessage
:param form: The "what" data member of specifier.
:type form: int
:param property: The name of the targeted property.
:type property: str
:return: the next BHandler that should look at the message.
:rtype: BHandler
)doc", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("form"), py::arg("property"))
.def("ShowCursor", &BApplication::ShowCursor, R"doc(
Restore the mouse cursor.
)doc")
.def("HideCursor", &BApplication::HideCursor, R"doc(
Hide the mouse cursor.
)doc")
.def("ObscureCursor", &BApplication::ObscureCursor, R"doc(
Temporarily hide or obscure the cursor.
)doc")
.def("IsCursorHidden", &BApplication::IsCursorHidden, R"doc(
Check whether the cursor is currently hidden.

:return: ``True`` if the cursor is hidden, ``False`` otherwise.
:rtype: bool
)doc")
//.def("SetCursor", py::overload_cast<const void *>(&BApplication::SetCursor), "", py::arg("cursor"))
.def("SetCursor", [](BApplication& self, py::buffer cursor){
	py::buffer_info info = cursor.request();
	const void* buffer = info.ptr;
	self.SetCursor(buffer);
},R"doc(
Set the current cursor to the given raw cursor data.

:param cursor: The cursor data.
:type cursor: py::buffer (e.g. bytes, bytearray, numpy.ndarray)
)doc", py::arg("cursor"))
.def("SetCursor", py::overload_cast<const BCursor *, bool>(&BApplication::SetCursor), R"doc(
Set the current cursor to the given BCursor object.

:param cursor: BCursor object to use.
:type cursor: BCursor
:param sync: If ``True``, update cursor immediately.
:type sync: bool
)doc", py::arg("cursor"), py::arg("sync")=true)
.def("CountWindows", &BApplication::CountWindows, R"doc(
Return the number of windows managed by the application.

:return: Number of windows.
:rtype: int
)doc")
.def("WindowAt", &BApplication::WindowAt, R"doc(
Return the window at the specified index.

:param index: Window index.
:type index: int
:return: The window at the given index.
:rtype: BWindow
)doc", py::arg("index"))
.def("CountLoopers", &BApplication::CountLoopers, R"doc(
Return the number of registered BLoopers.

:return: Number of loopers.
:rtype: int
)doc")
.def("LooperAt", &BApplication::LooperAt, R"doc(
Return the looper at the specified index.

:param index: Looper index.
:type index: int
:return: The BLooper at the given index.
:rtype: BLooper
)doc", py::arg("index"))
.def("IsLaunching", &BApplication::IsLaunching, R"doc(
Returns ``True`` if the application is still launching. An application
is in its launching phase until ReadyToRun() returns.
:return: ``True`` if in launching phase, otherwise ``False``.
:rtype: bool
)doc")
.def("Signature", &BApplication::Signature, R"doc(
Returns the signature of the Application.

:return: The signature.
:rtype: str
)doc")
.def("GetAppInfo", &BApplication::GetAppInfo, R"doc(
Fills out the info parameter (app_info class, look Roster) with information about the application.

:param info: the parameter to be filled with app information
:type info: app_info
:return: ``B_OK`` if success, otherwise a Haiku error code
:rtype: int
)doc", py::arg("info"))
.def("GetAppInfo", &GetAppInfoWrapper, R"doc(
Convenience method that returns a tuple with the status of
the native call and the actual information.

:return: A tuple ``(status, info)``:
         - ``status`` (int): ``B_OK`` on success, or a Haiku error code
         - ``info`` (app_info): app information  
:rtype: tuple
)doc")
.def_static("AppResources", &BApplication::AppResources, R"doc(
Return the BResources object associated with the application.
You may read the data in the BResources object, but you're not 
allowed to write it.

:return: The resources from the executable file of you application 
:rtype: BResources
)doc")
.def("DispatchMessage", &BApplication::DispatchMessage, R"doc(
Dispatch a message to the specified handler.

This method is called by the message looping thread to dispatch a
message to handler. It is rarely called directly by
applications, but can be overridden to customize how messages are
dispatched.

:param message: The message to be dispatched.
:type message: BMessage
:param handler: The target handler that should receive the message.
:type handler: BHandler
)doc", py::arg("message"), py::arg("handler"))
.def("SetPulseRate", &BApplication::SetPulseRate, R"doc(
Sets the interval that the ``B_PULSE`` messages are sent.

If the rate is set to 0 then the ``B_PULSE`` messages are not sent. 
The pulse rate can be no faster than once per 100,000 microseconds or so.

:param rate: The interval
:type rate: int
)doc", py::arg("rate"))
.def("RegisterLooper", &BApplication::RegisterLooper, R"doc(
Register a looper to quit when the application quits.

:param looper: the looper to register with the application
:type looper: BLooper
:return: ``B_OK`` on success, or a Haiku error code
:rtype: int
)doc", py::arg("looper"))
.def("UnregisterLooper", &BApplication::UnregisterLooper, R"doc(
Remove a previously registered Looper from the quit-list.

:param looper: the looper to remove from the quit-list
:type looper: BLooper
:return: ``B_OK`` on success, or a Haiku error code
:rtype: int
)doc", py::arg("looper"))
.def("GetSupportedSuites", &BApplication::GetSupportedSuites, R"doc(
Reports the suites of messages and specifiers that derived classes understand.

:param data: The message that will be populated with supported suites.
:type data: BMessage
:return: ``B_OK`` on success, or a Haiku error code
:rtype: int
)doc", py::arg("data"))
.def("GetSupportedSuites", &GetSupportedSuitesWrapper, R"doc(
A convenience method to get a tuple containing the status of 
the call and the resulting populated BMessage with the supported suites.

:return: A tuple ``(status, data)``:
         - ``status`` (int): ``B_OK`` on success, or a Haiku error code
         - ``data`` (BMessage): the message with the supported suites
:rtype: tuple
)doc")
// #### TODO wrappare non posso passare void * #######
//.def("Perform", &BApplication::Perform, "" , py::arg("d"), py::arg("arg"))
/* first version
.def("Perform", [](BApplication& self, perform_code d,py::buffer arg){
	py::buffer_info info = arg.request();
	const void* buffer = info.ptr;
	return self.Perform(d,buffer);
}*/
.def("Perform", [](BApplication& self, perform_code d, py::object arg = py::none()) {
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
// ########################################
.def("__repr__", [](const BApplication& app) {
    const char* sig = app.Signature();
    if (sig && sig[0] != '\0') {
        return std::string("BApplication(\"") + sig + "\")";
    }
    return std::string("<BApplication>");
})
;

m.attr("be_app") = be_app;
m.attr("be_app_messenger") = be_app_messenger;

}
