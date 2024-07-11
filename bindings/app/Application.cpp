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
        void ArgvReceived(int32 argc, std::vector<char*> argv) {
        	pybind11::gil_scoped_acquire gil;
        	pybind11::function override = pybind11::get_override(static_cast<const BApplication*>(this), "ArgvReceived");
        	if (override) {
				// It exists! Let's call it.
				override(argc, argv);
			} else {
				// Doesn't exist. Let's call our wrapper instead
				ArgvReceivedWrapper(*this, argc, argv);
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

py::class_<BApplication,PyBApplication,BLooper, py::smart_holder>(m, "BApplication")
.def(py::init<const char *>(), "", py::arg("signature"))
.def(py::init<const char *, status_t *>(), "", py::arg("signature"), py::arg("error"))
.def(py::init<BMessage *>(), "", py::arg("data"))
.def_static("Instantiate", &BApplication::Instantiate, "", py::arg("data"))
.def("Archive", &BApplication::Archive, "", py::arg("data"), py::arg("deep")=true)
.def("InitCheck", &BApplication::InitCheck, "")
.def("Run", &RunWrapper, "")
.def("Quit", &QuitWrapper, "")
.def("QuitRequested", &BApplication::QuitRequested, "")
.def("Pulse", &BApplication::Pulse, "")
.def("ReadyToRun", &BApplication::ReadyToRun, "")
.def("MessageReceived", &BApplication::MessageReceived, "", py::arg("message"))
.def("ArgvReceived", &ArgvReceivedWrapper, "", py::arg("argc"), py::arg("argv"))
//.def("ArgvReceivedWrapper", &PyBApplication::ArgvReceivedWrapper, "", py::arg("args"))  // Usare il metodo wrapper qui
.def("AppActivated", &BApplication::AppActivated, "", py::arg("active"))
.def("RefsReceived", &BApplication::RefsReceived, "", py::arg("message"))
.def("AboutRequested", &BApplication::AboutRequested, "")
.def("ResolveSpecifier", &BApplication::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("form"), py::arg("property"))
.def("ShowCursor", &BApplication::ShowCursor, "")
.def("HideCursor", &BApplication::HideCursor, "")
.def("ObscureCursor", &BApplication::ObscureCursor, "")
.def("IsCursorHidden", &BApplication::IsCursorHidden, "")
.def("SetCursor", py::overload_cast<const void *>(&BApplication::SetCursor), "", py::arg("cursor"))
.def("SetCursor", py::overload_cast<const BCursor *, bool>(&BApplication::SetCursor), "", py::arg("cursor"), py::arg("sync")=true)
.def("CountWindows", &BApplication::CountWindows, "")
.def("WindowAt", &BApplication::WindowAt, "", py::arg("index"))
.def("CountLoopers", &BApplication::CountLoopers, "")
.def("LooperAt", &BApplication::LooperAt, "", py::arg("index"))
.def("IsLaunching", &BApplication::IsLaunching, "")
.def("Signature", &BApplication::Signature, "")
.def("GetAppInfo", &BApplication::GetAppInfo, "", py::arg("info"))
.def_static("AppResources", &BApplication::AppResources, "")
.def("DispatchMessage", &BApplication::DispatchMessage, "", py::arg("message"), py::arg("handler"))
.def("SetPulseRate", &BApplication::SetPulseRate, "", py::arg("rate"))
.def("RegisterLooper", &BApplication::RegisterLooper, "", py::arg("looper"))
.def("UnregisterLooper", &BApplication::UnregisterLooper, "", py::arg("looper"))
.def("GetSupportedSuites", &BApplication::GetSupportedSuites, "", py::arg("data"))
.def("Perform", &BApplication::Perform, "", py::arg("d"), py::arg("arg"))
;

m.attr("be_app") = be_app;
m.attr("be_app_messenger") = be_app_messenger;

}
