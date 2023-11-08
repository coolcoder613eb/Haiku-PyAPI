#include <pybind11/pybind11.h>
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

class PyBApplication : public BApplication{
	public:
        using BApplication::BApplication;
        void ReadyToRun() override {
        	py::gil_scoped_release release;
            {
                py::gil_scoped_acquire acquire;
                PYBIND11_OVERLOAD(void, BApplication, ReadyToRun);
            }
        }
        bool QuitRequested() override {
            py::gil_scoped_release release;
            {
                py::gil_scoped_acquire acquire;
                PYBIND11_OVERLOAD(
                    bool,
                    BApplication,
                    QuitRequested,
                );
            }
        }
};

void ArgvReceivedWrapper(BApplication& self, int32 argc, std::vector<char*> argv) {
	self.ArgvReceived(argc, argv.data());
}

PYBIND11_MODULE(Application,m)
{
py::class_<BApplication,PyBApplication,BLooper>(m, "BApplication")
.def(py::init<const char *>(), "", py::arg("signature"))
.def(py::init<const char *, status_t *>(), "", py::arg("signature"), py::arg("error"))
.def(py::init<BMessage *>(), "", py::arg("data"))
.def_static("Instantiate", &BApplication::Instantiate, "", py::arg("data"))
.def("Archive", &BApplication::Archive, "", py::arg("data"), py::arg("deep")=true)
.def("InitCheck", &BApplication::InitCheck, "")
.def("Run", &BApplication::Run, "")
.def("Quit", &BApplication::Quit, "")
.def("QuitRequested", &BApplication::QuitRequested, "")
.def("Pulse", &BApplication::Pulse, "")
.def("ReadyToRun", &BApplication::ReadyToRun, "")
.def("MessageReceived", &BApplication::MessageReceived, "", py::arg("message"))
.def("ArgvReceived", &ArgvReceivedWrapper, "", py::arg("argc"), py::arg("argv"))
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
