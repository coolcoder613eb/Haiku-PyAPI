#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>
#include <app/Roster.h>
#include <Entry.h>
#include <Messenger.h>
#include <OS.h>
#include <List.h>

namespace py = pybind11;

status_t LaunchWrapper(BRoster& self, const char* mimeType, int argc,
		const std::vector<const char *>& args, team_id* appTeam) {
	return self.Launch(mimeType, argc, args.data(), appTeam);
}

status_t LaunchWrapper(BRoster& self, const entry_ref* ref, int argc,
		const std::vector<const char *>& args, team_id* appTeam) {
	return self.Launch(ref, argc, args.data(), appTeam);
}

void GetRecentDocumentsWrapper(BRoster& self, BMessage* refList, int32 maxCount,
		std::vector<const char*>& fileTypes, int32 fileTypesCount,
		const char* signature) {
	self.GetRecentDocuments(refList, maxCount,
		fileTypes.data(), fileTypesCount, signature);
}

PYBIND11_MODULE(Roster,m)
{

py::enum_<watching_request_flags>(m, "watching_request_flags", "")
.value("B_REQUEST_LAUNCHED", watching_request_flags::B_REQUEST_LAUNCHED, "")
.value("B_REQUEST_QUIT", watching_request_flags::B_REQUEST_QUIT, "")
.value("B_REQUEST_ACTIVATED", watching_request_flags::B_REQUEST_ACTIVATED, "")
.export_values();

m.attr("B_SOME_APP_LAUNCHED") = py::int_('BRAS');
m.attr("B_SOME_APP_QUIT") = py::int_('BRAQ');
m.attr("B_SOME_APP_ACTIVATED") = py::int_('BRAW');

py::class_<app_info>(m, "app_info")
.def(py::init(), "")
.def_readwrite("thread", &app_info::thread)
.def_readwrite("team", &app_info::team)
.def_readwrite("port", &app_info::port)
.def_readwrite("flags", &app_info::flags)
.def_readwrite("ref", &app_info::ref)
.def_readonly("signature", &app_info::signature)
;


py::class_<BRoster>(m, "BRoster",R"doc(
The ``BRoster`` object represents a service that keeps a roster of all 
applications currently running. It can provide information about any of 
those applications, activate one of them, add another application to 
the roster by launching it, or get information about an application to 
help you decide whether to launch it.

There's just one roster and it's shared by all applications. When an 
application starts up, a ``BRoster`` object is constructed and assigned to 
a global variable, be_roster. You always access the roster through this 
variable; you never have to instantiate a ``BRoster`` in application code.

The ``BRoster`` identifies applications in three ways:

   - By entry_ref references to the executable files where they reside.

   - By their signatures. The signature is a unique identifier for the 
   application assigned as a file-system attribute or resource at compile 
   time or by the ``BApplication`` constructor at run time.

   - At run time, by their ``team_id``s. A team is a group of threads 
   sharing an address space; every application is a team.

If an application is launched more than once, the roster will include one 
entry for each instance of the application that's running. These instances 
will have the same signature, but different team identifiers.
)doc")
.def(py::init(), R"doc(
Sets up the object's connection to the roster service.

When an application constructs its ``BApplication`` object, the system 
constructs a ``BRoster`` object and assigns it to the be_roster global 
variable. A ``BRoster`` is therefore readily available from the time 
the application is initialized until the time it quits; you don't have 
to construct one. The constructor is public only to give programs that 
don't have BApplication objects access to the roster.
)doc")
.def("IsRunning", py::overload_cast<const char *>(&BRoster::IsRunning, py::const_), R"doc(
Query whether the application, identified by its signature is running.

:param signature: The application signature.
:type signature: str
:return: ``True`` if it is running, ``False`` it isn't.
:rtype: bool
)doc", py::arg("signature"))
.def("IsRunning", py::overload_cast<entry_ref *>(&BRoster::IsRunning, py::const_), R"doc(
Query whether the application, identified by a reference to its 
executable file, is running.

:param ref: The reference to the executable file.
:type ref: entry_ref
:return: ``True`` if it is running, ``False`` it isn't.
:rtype: bool
)doc", py::arg("ref"))
.def("TeamFor", py::overload_cast<const char *>(&BRoster::TeamFor, py::const_), R"doc(
Query whether the application identified by its signature is running 
and return its team identifier.

:param signature: The application signature.
:type signature: str
:return: The team identifier, or ``B_ERROR``
:rtype: team_id
)doc", py::arg("signature"))
.def("TeamFor", py::overload_cast<entry_ref *>(&BRoster::TeamFor, py::const_), R"doc(
Query whether the application identified by a reference to its 
executable file is running and return its team identifier.

:param ref: The reference to the executable file.
:type ref: entry_ref
:return: The team identifier, or ``B_ERROR``
:rtype: team_id
)doc", py::arg("ref"))
.def("GetAppList", py::overload_cast<BList *>(&BRoster::GetAppList, py::const_), R"doc(
Fills in the ``teamIDList`` ``BList`` with team identifiers for 
applications in the roster. Each item in the list will be of type 
``team_id``.

.. note::
   
   This version is kept for C++ compatibility

:param teamIDList: The list of ``team_id``s to be filled.
:type teamIDList: BList
)doc", py::arg("teamIDList"))
.def("GetAppList", [](BRoster& self){
	BList* teamIDList = new BList;
	self.GetAppList(teamIDList);
	return teamIDList;
}, R"doc(
Return a ``BList`` with team identifiers for 
applications in the roster. Each item in the list will be of type 
``team_id``.

:return: The list o team identifiers for applications in the roster.
:rtype: BList
)doc")
.def("GetAppList", py::overload_cast<const char *, BList *>(&BRoster::GetAppList, py::const_), R"doc(
Fills in the ``teamIDList`` ``BList`` with team identifiers for 
applications running in the roster under the ``signature`` signature. 
Each item in the list will be of type ``team_id``.

.. note::
   
   This version is kept for C++ compatibility

:param signature: The applications signature.
:type signature: str
:param teamIDList: The list of ``team_id``s to be filled.
:type teamIDList: BList
)doc", py::arg("signature"), py::arg("teamIDList"))
.def("GetAppList", [](BRoster& self, const char* signature){
	BList* teamIDList = new BList;
	self.GetAppList(signature,teamIDList);
	return teamIDList;
}, R"doc(
Return a ``BList`` with team identifiers for applications in the 
roster under the ``signature`` signature. Each item in the list 
will be of type ``team_id``.

:param signature: The applications signature.
:type signature: str
:return: The list o team identifiers for applications in the roster.
:rtype: BList
)doc")
.def("GetAppInfo", py::overload_cast<const char *, app_info *>(&BRoster::GetAppInfo, py::const_), R"doc(
Finds an app that has the given signature and reports information 
about the application.
If there's more than one such app, the function chooses one at random.

.. note::
   
   This version is kept for C++ compatibility

:param signature: The app signature.
:type signature: str
:param info: The parameter to fill with the information reported about the application.
:type info: app_info
:return: ``B_OK`` or an error code:
   
   - ``B_OK`` if able to fill in the app_info variable with meaningful values.
   - ``B_ERROR`` if the application isn't running.
   
:rtype: int
)doc", py::arg("signature"), py::arg("info"))
.def("GetAppInfo", [](BRoster& self, const char* signature){
	app_info* info = new app_info;
	status_t status = self.GetAppInfo(signature,info);
	return py::make_tuple(status,info);
},R"doc(
Finds an app that has the given signature and reports information 
about the application.
If there's more than one such app, the function chooses one at random.

:param signature: The app signature.
:type signature: str
:return: A tuple with the status of the function and the information about the app:
   
   - the status can be one of these:
   
      - ``B_OK`` (int) if able to fill in the app_info variable with meaningful values.
      - ``B_ERROR`` (int) if the application isn't running.
   
   - the information is an ``app_info`` class containig the values
   
:rtype: tuple
)doc",py::arg("signature"))
.def("GetAppInfo", py::overload_cast<entry_ref *, app_info *>(&BRoster::GetAppInfo, py::const_), R"doc(
Finds an app that was launched from the executable file and reports 
information about the application.
If there's more than one such app, the function chooses one at random.

.. note::
   
   This version is kept for C++ compatibility

:param ref: The reference to the executable file.
:type ref: entry_ref
:param info: The parameter to fill with the information reported about the application.
:type info: app_info
:return: ``B_OK`` or an error code:
   
   - ``B_OK`` if able to fill in the app_info variable with meaningful values.
   - ``B_ERROR`` if the application isn't running.
   
:rtype: int
)doc", py::arg("ref"), py::arg("info"))
.def("GetAppInfo", [](BRoster& self, entry_ref* ref){
	app_info* info = new app_info;
	status_t status = self.GetAppInfo(ref,info);
	return py::make_tuple(status,info);
}, R"doc(
Finds an app that was launched from the executable file and reports 
information about the application.
If there's more than one such app, the function chooses one at random.

:param ref: The reference to the executable file.
:type ref: entry_ref
:return: A tuple with the status of the function and the information about the app:
   
   - the status can be one of these:
   
      - ``B_OK`` (int) if able to fill in the app_info variable with meaningful values.
      - ``B_ERROR`` (int) if the application isn't running.
   
   - the information is an ``app_info`` class containig the values
   
:rtype: tuple
)doc",py::arg("ref"))
.def("GetRunningAppInfo", &BRoster::GetRunningAppInfo, R"doc(
Finds an app that corresponds to the given ``team`` identifier 
and reports information about the application.

.. note::
   
   This version is kept for C++ compatibility
   
:param team: The team identifier of the app.
:type team: team_id
:param info: The parameter to fill with the information reported about the application.
:type info: app_info
:return: ``B_OK`` or an error code:
   
   - ``B_OK`` if able to fill in the app_info variable with meaningful values.
   - ``B_ERROR`` if the application isn't running.
   
:rtype: int
)doc", py::arg("team"), py::arg("info"))
.def("GetRunningAppInfo", [](BRoster& self, team_id team){
	app_info* info = new app_info;
	status_t status = self.GetRunningAppInfo(team,info);
	return py::make_tuple(status,info);
}, R"doc(
Finds an app that corresponds to the given ``team`` identifier 
and reports information about the application.

:param team: The team identifier of the app.
:type team: team_id
:return: A tuple with the status of the function and the information about the app:
   
   - the status can be one of these:
   
      - ``B_OK`` (int) if able to fill in the app_info variable with meaningful values.
      - ``B_ERROR`` (int) if the application isn't running.
   
   - the information is an ``app_info`` class containig the values
   
:rtype: tuple
)doc", py::arg("team"))
.def("GetActiveAppInfo", &BRoster::GetActiveAppInfo, R"doc(
Finds the current active app and reports information about the
application.

.. note::
   
   This version is kept for C++ compatibility

:param info: The parameter to fill with the information reported about the application.
:type info: app_info
:return: ``B_OK`` or an error code:
   
   - ``B_OK`` if able to fill in the app_info variable with meaningful values.
   - ``B_ERROR`` if the application isn't running.
   
:rtype: int
)doc", py::arg("info"))
.def("GetActiveAppInfo", [](BRoster& self){
	app_info* info = new app_info;
	status_t status = self.GetActiveAppInfo(info);
	return py::make_tuple(status,info);
}, R"doc(
Finds the current active app and reports information about the
application.

:return: A tuple with the status of the function and the information about the app:
   
   - the status can be one of these:
   
      - ``B_OK`` (int) if able to fill in the app_info variable with meaningful values.
      - ``B_ERROR`` (int) if the application isn't running.
   
   - the information is an ``app_info`` class containig the values
   
:rtype: tuple
)doc")
.def("FindApp", py::overload_cast<const char *, entry_ref *>(&BRoster::FindApp, py::const_), R"doc()doc", py::arg("mimeType"), py::arg("app"))
.def("FindApp", py::overload_cast<entry_ref *, entry_ref *>(&BRoster::FindApp, py::const_), R"doc()doc", py::arg("ref"), py::arg("app"))
.def("Broadcast", py::overload_cast<BMessage *>(&BRoster::Broadcast, py::const_), R"doc()doc", py::arg("message"))
.def("Broadcast", py::overload_cast<BMessage *, BMessenger>(&BRoster::Broadcast, py::const_), R"doc()doc", py::arg("message"), py::arg("replyTo"))
.def("StartWatching", &BRoster::StartWatching, R"doc()doc", py::arg("target"), py::arg("eventMask")=B_REQUEST_LAUNCHED | B_REQUEST_QUIT)
.def("StopWatching", &BRoster::StopWatching, R"doc()doc", py::arg("target"))
.def("ActivateApp", &BRoster::ActivateApp, R"doc()doc", py::arg("team"))
.def("Launch", py::overload_cast<const char *, BMessage *, team_id *>(&BRoster::Launch, py::const_), "", py::arg("mimeType"), py::arg("initialMessage")=NULL, py::arg("_appTeam")=NULL)
.def("Launch", py::overload_cast<const char *, BList *, team_id *>(&BRoster::Launch, py::const_), "", py::arg("mimeType"), py::arg("messageList"), py::arg("_appTeam")=NULL)
.def("Launch", static_cast<status_t (*)(BRoster &, const char *, int, const std::vector<const char *>&, team_id *)>(&LaunchWrapper), "", py::arg("mimeType"), py::arg("argc"), py::arg("args"), py::arg("_appTeam")=NULL)
.def("Launch", py::overload_cast<const entry_ref *, const BMessage *, team_id *>(&BRoster::Launch, py::const_), "", py::arg("ref"), py::arg("initialMessage")=NULL, py::arg("_appTeam")=NULL)
.def("Launch", py::overload_cast<const entry_ref *, const BList *, team_id *>(&BRoster::Launch, py::const_), "", py::arg("ref"), py::arg("messageList"), py::arg("_appTeam")=NULL)
.def("Launch", static_cast<status_t (*)(BRoster &, const entry_ref *, int, const std::vector<const char *>&, team_id *)>(&LaunchWrapper), "", py::arg("ref"), py::arg("argc"), py::arg("args"), py::arg("_appTeam")=NULL)
.def("GetRecentDocuments", py::overload_cast<BMessage *, int32, const char *, const char *>(&BRoster::GetRecentDocuments, py::const_), "", py::arg("refList"), py::arg("maxCount"), py::arg("fileType")=NULL, py::arg("signature")=NULL)
.def("GetRecentDocuments", &GetRecentDocumentsWrapper, "", py::arg("refList"), py::arg("maxCount"), py::arg("fileTypes"), py::arg("fileTypesCount"), py::arg("signature")=NULL)
.def("GetRecentFolders", &BRoster::GetRecentFolders, "", py::arg("refList"), py::arg("maxCount"), py::arg("signature")=NULL)
.def("GetRecentApps", &BRoster::GetRecentApps, "", py::arg("refList"), py::arg("maxCount"))
.def("AddToRecentDocuments", &BRoster::AddToRecentDocuments, "", py::arg("document"), py::arg("signature")=NULL)
.def("AddToRecentFolders", &BRoster::AddToRecentFolders, "", py::arg("folder"), py::arg("signature")=NULL)
;

m.attr("be_roster") = be_roster;


}
