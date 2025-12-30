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
/* substituted as appTeam is immutable
status_t LaunchWrapper(BRoster& self, const char* mimeType, int argc,
		const std::vector<const char *>& args, team_id* appTeam) {
	return self.Launch(mimeType, argc, args.data(), appTeam);
}*/
/* first version args.data is const char** not char**, look at local wrapper below using py::list
status_t LaunchWrapper(BRoster& self, const char* mimeType, int argc,
		const std::vector<const char *>& args) {
			team_id appTeam = -1;
			status_t status = self.Launch(mimeType, argc, args.data(), &appTeam);
	return py::make_tuple(status,appTeam);
}*/

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
BMessage GetRecentDocumentsPythonicWrapper(BRoster& self, int32 maxCount,
		std::vector<const char*>& fileTypes, int32 fileTypesCount,
		const char* signature) {
	BMessage refList;
	self.GetRecentDocuments(&refList, maxCount,
		fileTypes.data(), fileTypesCount, signature);
	return refList;
}

PYBIND11_MODULE(Roster,m)
{

py::enum_<watching_request_flags>(m, "watching_request_flags", R"doc()doc")
.value("B_REQUEST_LAUNCHED", watching_request_flags::B_REQUEST_LAUNCHED, R"doc()doc")
.value("B_REQUEST_QUIT", watching_request_flags::B_REQUEST_QUIT, R"doc()doc")
.value("B_REQUEST_ACTIVATED", watching_request_flags::B_REQUEST_ACTIVATED, R"doc()doc")
.export_values();

m.attr("B_SOME_APP_LAUNCHED") = py::int_('BRAS');
m.attr("B_SOME_APP_QUIT") = py::int_('BRAQ');
m.attr("B_SOME_APP_ACTIVATED") = py::int_('BRAW');

py::class_<app_info>(m, "app_info")
.def(py::init(), R"doc()doc")
.def_readwrite("thread", &app_info::thread, R"doc()doc")
.def_readwrite("team", &app_info::team, R"doc()doc")
.def_readwrite("port", &app_info::port, R"doc()doc")
.def_readwrite("flags", &app_info::flags, R"doc()doc")
.def_readwrite("ref", &app_info::ref, R"doc()doc")
.def_readonly("signature", &app_info::signature, R"doc()doc")
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
:rtype: int
)doc", py::arg("signature"))
.def("TeamFor", py::overload_cast<entry_ref *>(&BRoster::TeamFor, py::const_), R"doc(
Query whether the application identified by a reference to its 
executable file is running and return its team identifier.

:param ref: The reference to the executable file.
:type ref: entry_ref
:return: The team identifier, or ``B_ERROR``
:rtype: int
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
.def("GetAppList", [](const BRoster& self){
	BList* teamIDList = new BList;
	self.GetAppList(teamIDList);
	return teamIDList;
}, R"doc(
Return a ``BList`` with team identifiers for 
applications in the roster. Each item in the list will be of type 
``team_id``.

:return: The list o team identifiers for applications in the roster.
:rtype: BList
)doc",py::return_value_policy::take_ownership) //take care of BList or there's a memory leak
.def("GetAppList", py::overload_cast<const char *, BList *>(&BRoster::GetAppList, py::const_), R"doc(
Fills in the ``teamIDList`` ``BList`` with team identifiers for 
applications running in the roster under the ``signature`` signature. 
Each item in the list will be of type ``team_id``.

.. note::
   
   This version is kept for C++ compatibility

:param signature: The applications signature.
:type signature: str
:param teamIDList: The list of ``team_id``s (int) to be filled.
:type teamIDList: BList
)doc", py::arg("signature"), py::arg("teamIDList"))
.def("GetAppList", [](const BRoster& self, const char* signature){
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
)doc",py::arg("signature"),py::return_value_policy::take_ownership) //take care of BList or there's a memory leak
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
.def("GetAppInfo", [](const BRoster& self, const char* signature){
	//app_info* info = new app_info;
	//status_t status = self.GetAppInfo(signature,info);
	app_info info;
	status_t status = self.GetAppInfo(signature,&info);
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
.def("GetAppInfo", [](const BRoster& self, entry_ref* ref){
	app_info info;
	status_t status = self.GetAppInfo(ref,&info);
	//app_info* info = new app_info;
	//status_t status = self.GetAppInfo(ref,info);
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
:type team: int
:param info: The parameter to fill with the information reported about the application.
:type info: app_info
:return: ``B_OK`` or an error code:
   
   - ``B_OK`` if able to fill in the app_info variable with meaningful values.
   - ``B_ERROR`` if the application isn't running.
   
:rtype: int
)doc", py::arg("team"), py::arg("info"))
.def("GetRunningAppInfo", [](const BRoster& self, team_id team){
	app_info* info = new app_info;
	status_t status = self.GetRunningAppInfo(team,info);
	return py::make_tuple(status,info);
}, R"doc(
Finds an app that corresponds to the given ``team`` identifier 
and reports information about the application.

:param team: The team identifier of the app.
:type team: int
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
.def("GetActiveAppInfo", [](const BRoster& self){
	//app_info* info = new app_info;
	//status_t status = self.GetActiveAppInfo(info);
	app_info info;
	status_t status = self.GetActiveAppInfo(&info);
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
.def("FindApp", py::overload_cast<const char *, entry_ref *>(&BRoster::FindApp, py::const_), R"doc(
Finds the application associated with the MIME data ``mimeType`` 
and modifies the ``app`` ``entry_ref`` class so that it refers 
to the executable file for that application. If the ``mimeType`` is an 
application signature, this function finds the application that 
has that signature. Otherwise, it finds the preferred 
application for the type.

.. note::

   This version is kept for C++ compatibility.

:param mimeType: The application signature or a file's MIME type
:type mimeType: str
:param app: The ``entry_ref`` class to fill with the reference to the executable file or to the preferred application.
:type app: entry_ref
:return: ``B_OK`` or an error code:

   - ``B_OK`` if it can translate ``mimeType`` into a reference to an application executable.
   - An error code, typically one describing a file system error.
   
:rtype: int
)doc", py::arg("mimeType"), py::arg("app"))
.def("FindApp", [](const BRoster& self, const char * mimeType){
	//entry_ref* app = new entry_ref;
	entry_ref app;
	status_t status = self.FindApp(mimeType,&app);
	return py::make_tuple(status,app);
},R"doc(
Finds the application associated with the MIME data ``mimeType``
and returns the entry_ref that refers to the executable file for 
that application. If the ``mimeType`` is an 
application signature, this function finds the application that 
has that signature. Otherwise, it finds the preferred 
application for the type.

:param mimeType: The application signature or a file's MIME type
:type mimeType: str
:return: A tuple with the status of the function and the reference to the app:
   
   - the status can be one of these:
   
      - ``B_OK`` (int) if it can translate ``mimeType`` into a reference to an application executable.
      - ``B_ERROR`` (int) if the application isn't running.
   
   - the reference (``entry_ref``) to the executable file for that application.
   
:rtype: tuple
)doc", py::arg("mimeType"))
.def("FindApp", py::overload_cast<entry_ref *, entry_ref *>(&BRoster::FindApp, py::const_), R"doc(
Finds the application associated with the specified file, and 
modifies the app entry_ref that refers to the executable file for 
that application. If the file is an application executable, this
method merely copies the file reference to the app argument. 
Otherwise, it finds the preferred application for the filetype.

.. note::

   This version is kept for C++ compatibility.

:param ref: the reference to the file to check.
:type ref: entry_ref
:param app: the reference (``entry_ref``) that will be modified with the executable file for that application/file.
:type app: entry_ref
:return: ``B_OK`` or an error code:

   - ``B_OK`` if it can find the reference to an application executable for ``ref``.
   - An error code, typically one describing a file system error.
   
:rtype: int
)doc", py::arg("ref"), py::arg("app"))
.def("FindApp", [](BRoster& self, entry_ref * ref){
	entry_ref app;
	status_t status = self.FindApp(ref,&app);
	return py::make_tuple(status,app);
}, R"doc(
Finds the application associated with the specified file and 
returns the status of the call and the entry_ref that refers 
to the executable file for that application.

:param ref: the reference to the file to check.
:type ref: entry_ref
:return: A tuple with the status of the function and the reference to the app:
   
   - the status can be one of these:
   
      - ``B_OK`` (int) if it can translate ``mimeType`` into a reference to an application executable.
      - ``B_ERROR`` (int) if the application isn't running.
   
   - the reference (``entry_ref``) to the executable file for that application/file.
   
:rtype: tuple
)doc",py::arg("ref"))
.def("Broadcast", py::overload_cast<BMessage *>(&BRoster::Broadcast, py::const_), R"doc(
Sends the message to every running application, except to 
those applications (``B_ARGV_ONLY``) that don't accept messages. 
The message is sent asynchronously with a timeout of 0. As is 
the case for other message-sending functions, the caller retains 
ownership of the message.

This function returns immediately after setting up the broadcast 
operation. It doesn't wait for the messages to be sent and 
doesn't report any errors encountered when they are.

The replies to this message will be lost.

:param message: The message to broadcast.
:type message: BMessage
:return: a status code:

   -  ``B_OK`` ff successful in getting the operation started
   - An error only if it can't start the broadcast operation.
   
:rtype: int
)doc", py::arg("message"))
.def("Broadcast", py::overload_cast<BMessage *, BMessenger>(&BRoster::Broadcast, py::const_), R"doc(
Sends the message to every running application, except to 
those applications (``B_ARGV_ONLY``) that don't accept messages. 
The message is sent asynchronously with a timeout of 0. As is 
the case for other message-sending functions, the caller retains 
ownership of the message.

This function returns immediately after setting up the broadcast 
operation. It doesn't wait for the messages to be sent and 
doesn't report any errors encountered when they are.

Replies to the broadcasted message will be sent via the 
``replyTo`` ``BMessenger``.

:param message: The message to broadcast.
:type message: BMessage
:param replyTo: The messaenger for the replies.
:type replyTo: BMessenger
:return: a status code:

   -  ``B_OK`` ff successful in getting the operation started
   - An error only if it can't start the broadcast operation.
   
:rtype: int
)doc", py::arg("message"), py::arg("replyTo"))
.def("StartWatching", &BRoster::StartWatching, R"doc(
``StartWatching()`` initiates the application event monitor,
 which is used for keeping track of events such as application 
 launches. 

The caller specifies the events to monitor through the 
``eventMask`` argument; ``target`` is the ``BMessenger`` to 
which the corresponding notification messages are sent. 

**Event Flags and Messages:**

+----------------------------+-----------------------+
| Flag                       | Message               |
+============================+=======================+
| B_REQUEST_LAUNCHED         | B_SOME_APP_LAUNCHED   |
+----------------------------+-----------------------+
| B_REQUEST_QUIT             | B_SOME_APP_QUIT       |
+----------------------------+-----------------------+
| B_REQUEST_ACTIVATED        | B_SOME_APP_ACTIVATED  |
+----------------------------+-----------------------+

**Notification Message Fields:**

The fields in a notification message describe the application 
that was launched, quit, or activated:

+----------+-----------------+---------------------------+
| Field    | Type            | Description               |
+==========+=================+===========================+
| mime_sig | B_STRING_TYPE   | MIME signature            |
+----------+-----------------+---------------------------+
| team     | B_INT32_TYPE    | team_id                   |
+----------+-----------------+---------------------------+
| thread   | B_INT32_TYPE    | thread_id                 |
+----------+-----------------+---------------------------+
| flags    | B_INT32_TYPE    | Application flags         |
+----------+-----------------+---------------------------+
| ref      | B_REF_TYPE      | Executable's ``entry_ref``|
+----------+-----------------+---------------------------+

:param target: the messenger to which the corresponding notification messages are sent.
:type target: BMessenger
:param eventMask: Bitmask of events to monitor.
:type eventMask: int
:return: ``B_OK`` if successful, or an error code.
:rtype: int
)doc", py::arg("target"), py::arg("eventMask")=B_REQUEST_LAUNCHED | B_REQUEST_QUIT)
.def("StopWatching", &BRoster::StopWatching, R"doc(
Terminate the application monitor previously initiated for 
a given ``BMessenger``.

:param target: the used messenger to which the notification messages were sent.
:type target: BMessenger
:return: ``B_OK`` if successful, or an error code.
:rtype: int
)doc", py::arg("target"))
.def("ActivateApp", &BRoster::ActivateApp, R"doc(
Activates the team application (by bringing one of its 
windows to the front and making it the active window). 
This function works only if the target application has 
a window on-screen. The newly activated application is 
notified with a ``B_APP_ACTIVATED`` message.

:param team: The team identifying the application.
:type team: int
:return: ``B_OK`` or an error code.
:rtype: int
)doc", py::arg("team"))
/* commented as the optional ``_appTeam`` parameter is immutable in Python.
.def("Launch", py::overload_cast<const char *, BMessage *, team_id *>(&BRoster::Launch, py::const_), "", py::arg("mimeType"), py::arg("initialMessage")=NULL, py::arg("_appTeam")=NULL)
*/
.def("Launch", [](const BRoster& self, const char * mimeType, BMessage* message){
	team_id _appTeam = -1;
	status_t status = self.Launch(mimeType,message,&_appTeam);
	return py::make_tuple(status,_appTeam);
}, R"doc(
Launches the application associated with the MIME ``mimeType``.
If the MIME type is an application signature, this function 
launches the application with that signature. Otherwise, it 
launches the preferred application for the type.

If a message is specified, it will be sent to the application 
on-launch where it will be received and responded to before 
the application is notified that it's ready to run. 

If the target application is already running, ``Launch()`` won't 
launch it again, unless it permits multiple instances to run 
concurrently (it doesn't wait for the messages to be sent or 
report errors encountered when they are). It fails for 
``B_SINGLE_LAUNCH`` and ``B_EXCLUSIVE_LAUNCH`` applications 
that have already been launched. Nevertheless, it assumes that 
you want the messages to get to the application and so 
delivers them to the currently running instance.

:param mimeType: The MIME associated to an application.
:type mimeType: str
:param initialMessage: The message to be sent to the application.
:type initialMessage: BMessage, optional
:return: a tuple (int,int) containing the status code and the ``team_id`` of the launched app:

   - A status code (int):

      - ``B_OK`` if this method is able to launch the application
      - ``B_BAD_VALUE`` if the ``mimeType`` is not valid or  an attempt is being made to send an on-launch message to an application that doesn't accept messages (a B_ARGV_ONLY app)
      - ``B_ALREADY_RUNNING`` The application is already running and can't be launched again (it's a B_SINGLE_LAUNCH or B_EXCLUSIVE_LAUNCH application).
      - ``B_LAUNCH_FAILED`` The attempt to launch the application failed for some other reason, such as insufficient memory.
      - A file system error: The ``mimeType`` can't be matched to an application.
   
   - The team identifier (int) for the newly launched application, or ``-1``
   
:rtype: tuple
)doc", py::arg("mimeType"), py::arg("initialMessage")=NULL)
/* idem as before
.def("Launch", py::overload_cast<const char *, BList *, team_id *>(&BRoster::Launch, py::const_), R"doc()doc", py::arg("mimeType"), py::arg("messageList"), py::arg("_appTeam")=NULL)
*/
.def("Launch", [](const BRoster& self, const char * mimeType, BList* messageList){
	team_id _appTeam = B_ERROR;//-1;
	status_t status = self.Launch(mimeType,messageList,&_appTeam);
	return py::make_tuple(status,_appTeam);
}, R"doc(
Launches the application associated with the MIME ``mimeType``.
If the MIME type is an application signature, this function 
launches the application with that signature. Otherwise, it 
launches the preferred application for the type.

Each message in the list of messages ``messageList`` will be 
delivered on-launch.

If the target application is already running, ``Launch()`` won't 
launch it again, unless it permits multiple instances to run 
concurrently (it doesn't wait for the messages to be sent or 
report errors encountered when they are). It fails for 
``B_SINGLE_LAUNCH`` and ``B_EXCLUSIVE_LAUNCH`` applications 
that have already been launched. Nevertheless, it assumes that 
you want the messages to get to the application and so 
delivers them to the currently running instance.

.. warning::

   The BList passed to this method must contain only ``BMessage`` objects. 
   The caller is responsible for ensuring the list contains only the correct 
   types. Passing other types of objects will result in undefined behavior 
   (and likely a crash).

:param mimeType: The MIME associated to an application.
:type mimeType: str
:param messageList: The list containing the messages to be sent.
:type messageList: BList
:return: a tuple (int,int) containing the status code and the ``team_id`` of the launched app:

   - A status code (int):

      - ``B_OK`` if this method is able to launch the application
      - ``B_BAD_VALUE`` if the ``mimeType`` is not valid or  an attempt is being made to send an on-launch message to an application that doesn't accept messages (a B_ARGV_ONLY app)
      - ``B_ALREADY_RUNNING`` The application is already running and can't be launched again (it's a B_SINGLE_LAUNCH or B_EXCLUSIVE_LAUNCH application).
      - ``B_LAUNCH_FAILED`` The attempt to launch the application failed for some other reason, such as insufficient memory.
      - A file system error: The ``mimeType`` can't be matched to an application.
   
   - The team identifier (int) for the newly launched application, or ``-1``
   
:rtype: tuple
)doc", py::arg("mimeType"), py::arg("messageList"))
/* nice but conflicts with the next one below
.def("Launch", [](const BRoster& self, const char* mimeType, py::list messages) {
	team_id _appTeam = -1;
	BList list;
	for (auto item : messages) {
		try {
			BMessage* msg = item.cast<BMessage*>();
			list.AddItem(msg);
		} catch (const py::cast_error& e) {
			throw py::type_error("Messages list must contain only BMessage objects");
		}
	}
	status_t status = self.Launch(mimeType, &list, &_appTeam);
	return py::make_tuple(status, _appTeam);
},R"doc(
A convenience method that passes a pythonic list of BMessages 
instead of a BList.
this functions behaves like the Launch(str,BList) one
)doc", py::arg("mimeType"), py::arg("messages"))*/
//.def("Launch", static_cast<status_t (*)(BRoster &, const char *, int, const std::vector<const char *>&, team_id *)>(&LaunchWrapper), "", py::arg("mimeType"), py::arg("argc"), py::arg("args"), py::arg("_appTeam")=NULL)
.def("Launch", [](const BRoster& self, const char* mimeType, py::list args) {
	team_id appTeam = B_ERROR;
	std::vector<std::string> storage;
	storage.reserve(args.size());
	std::vector<char*> argv;
	argv.reserve(args.size() + 1);
	for (auto item : args) {
		storage.push_back(item.cast<std::string>());
		argv.push_back(const_cast<char*>(storage.back().c_str()));
	}
	argv.push_back(nullptr);
	status_t status = self.Launch(mimeType, static_cast<int>(args.size()), argv.data(), &appTeam);
	return py::make_tuple(status, appTeam);
}, R"doc(
Launches the application associated with the MIME ``mimeType``.
If the MIME type is an application signature, this function 
launches the application with that signature. Otherwise, it 
launches the preferred application for the type.

The application will be launched with an array of argument 
strings that will be passed to its main() function. ``args``
is a python list containing the arguments. If the application 
accepts messages, this information will also be packaged in 
a ``B_ARGV_RECEIVED`` message that the application will 
receive on-launch.

If the target application is already running, ``Launch()`` won't 
launch it again, unless it permits multiple instances to run 
concurrently (it doesn't wait for the messages to be sent or 
report errors encountered when they are). It fails for 
``B_SINGLE_LAUNCH`` and ``B_EXCLUSIVE_LAUNCH`` applications 
that have already been launched. Nevertheless, it assumes that 
you want the messages to get to the application and so 
delivers them to the currently running instance.


:param mimeType: The MIME associated to an application.
:type mimeType: str
:param messageList: The list containing the arguments.
:type messageList: list
:return: a tuple (int,int) containing the status code and the ``team_id`` of the launched app:

   - A status code (int):

      - ``B_OK`` if this method is able to launch the application
      - ``B_BAD_VALUE`` if the ``mimeType`` is not valid or  an attempt is being made to send an on-launch message to an application that doesn't accept messages (a B_ARGV_ONLY app)
      - ``B_ALREADY_RUNNING`` The application is already running and can't be launched again (it's a B_SINGLE_LAUNCH or B_EXCLUSIVE_LAUNCH application).
      - ``B_LAUNCH_FAILED`` The attempt to launch the application failed for some other reason, such as insufficient memory.
      - A file system error: The ``mimeType`` can't be matched to an application.
   
   - The team identifier (int) for the newly launched application, or ``-1``
   
:rtype: tuple
)doc", py::arg("mimeType"), py::arg("args"))

//.def("Launch", py::overload_cast<const entry_ref *, const BMessage *, team_id *>(&BRoster::Launch, py::const_), R"doc()doc", py::arg("ref"), py::arg("initialMessage")=NULL, py::arg("_appTeam")=NULL)
.def("Launch", [](const BRoster& self,const entry_ref * ref, const BMessage * initialMessage){
	team_id appTeam = B_ERROR;
	status_t status = self.Launch(ref,initialMessage,&appTeam);
	return py::make_tuple(status,appTeam);
}, R"doc(
Launches the application associated with a particular file
reference (``ref``). If the file is an application executable, 
it launches that application. Otherwise, it launches the 
preferred application for the file type and passes the file 
reference to the application in a ``B_REFS_RECEIVED`` message.

If a message is specified, it will be sent to the application 
on-launch where it will be received and responded to before 
the application is notified that it's ready to run. 

If the target application is already running, ``Launch()`` won't 
launch it again, unless it permits multiple instances to run 
concurrently (it doesn't wait for the messages to be sent or 
report errors encountered when they are). It fails for 
``B_SINGLE_LAUNCH`` and ``B_EXCLUSIVE_LAUNCH`` applications 
that have already been launched. Nevertheless, it assumes that 
you want the messages to get to the application and so 
delivers them to the currently running instance.

:param ref: the reference to the file to check.
:type ref: entry_ref
:param initialMessage: The message to be sent to the application.
:type initialMessage: BMessage, optional
:return: a tuple (int,int) containing the status code and the ``team_id`` of the launched app:

   - A status code (int):

      - ``B_OK`` if this method is able to launch the application
      - ``B_BAD_VALUE`` if the ``mimeType`` is not valid or  an attempt is being made to send an on-launch message to an application that doesn't accept messages (a B_ARGV_ONLY app)
      - ``B_ALREADY_RUNNING`` The application is already running and can't be launched again (it's a B_SINGLE_LAUNCH or B_EXCLUSIVE_LAUNCH application).
      - ``B_LAUNCH_FAILED`` The attempt to launch the application failed for some other reason, such as insufficient memory.
      - A file system error: The ``mimeType`` can't be matched to an application.
   
   - The team identifier (int) for the newly launched application, or ``-1``
   
:rtype: tuple
)doc", py::arg("ref"), py::arg("initialMessage")=NULL)
//.def("Launch", py::overload_cast<const entry_ref *, const BList *, team_id *>(&BRoster::Launch, py::const_), R"doc()doc", py::arg("ref"), py::arg("messageList"), py::arg("_appTeam")=NULL)
.def("Launch", [](BRoster& self,const entry_ref * ref, const BList * messageList){
	team_id appTeam = B_ERROR;
	status_t status = self.Launch(ref,messageList,&appTeam);
	return py::make_tuple(status,appTeam);
}, R"doc(
Launches the application associated with a particular file
reference (``ref``). If the file is an application executable, 
it launches that application. Otherwise, it launches the 
preferred application for the file type and passes the file 
reference to the application in a ``B_REFS_RECEIVED`` message.

Each message in the list of messages ``messageList`` will be 
delivered on-launch.

If the target application is already running, ``Launch()`` won't 
launch it again, unless it permits multiple instances to run 
concurrently (it doesn't wait for the messages to be sent or 
report errors encountered when they are). It fails for 
``B_SINGLE_LAUNCH`` and ``B_EXCLUSIVE_LAUNCH`` applications 
that have already been launched. Nevertheless, it assumes that 
you want the messages to get to the application and so 
delivers them to the currently running instance.

.. warning::

   The BList passed to this method must contain only ``BMessage`` objects. 
   The caller is responsible for ensuring the list contains only the correct 
   types. Passing other types of objects will result in undefined behavior 
   (and likely a crash).
   
:param ref: the reference to the file to check.
:type ref: entry_ref
:param messageList: The list containing the messages to be sent.
:type messageList: BList
:return: a tuple (int,int) containing the status code and the ``team_id`` of the launched app:

   - A status code (int):

      - ``B_OK`` if this method is able to launch the application
      - ``B_BAD_VALUE`` if the ``mimeType`` is not valid or  an attempt is being made to send an on-launch message to an application that doesn't accept messages (a B_ARGV_ONLY app)
      - ``B_ALREADY_RUNNING`` The application is already running and can't be launched again (it's a B_SINGLE_LAUNCH or B_EXCLUSIVE_LAUNCH application).
      - ``B_LAUNCH_FAILED`` The attempt to launch the application failed for some other reason, such as insufficient memory.
      - A file system error: The ``mimeType`` can't be matched to an application.
   
   - The team identifier (int) for the newly launched application, or ``-1``
   
:rtype: tuple
)doc", py::arg("ref"), py::arg("messageList"))
//.def("Launch", static_cast<status_t (*)(BRoster &, const entry_ref *, int, const std::vector<const char *>&, team_id *)>(&LaunchWrapper), R"doc()doc", py::arg("ref"), py::arg("argc"), py::arg("args"), py::arg("_appTeam")=NULL)
.def("Launch", [](BRoster& self,const entry_ref * ref, py::list args) {
	team_id appTeam = B_ERROR;
	std::vector<std::string> storage;
	storage.reserve(args.size());
	std::vector<char*> argv;
	argv.reserve(args.size() + 1);
	for (auto item : args) {
		storage.push_back(item.cast<std::string>());
		argv.push_back(const_cast<char*>(storage.back().c_str()));
	}
	argv.push_back(nullptr);
	status_t status = self.Launch(ref, static_cast<int>(args.size()), argv.data(), &appTeam);
	return py::make_tuple(status, appTeam);
},R"doc(
Launches the application associated with a particular file
reference (``ref``). If the file is an application executable, 
it launches that application. Otherwise, it launches the 
preferred application for the file type and passes the file 
reference to the application in a ``B_REFS_RECEIVED`` message.

The application will be launched with an array of argument 
strings that will be passed to its main() function. ``args``
is a python list containing the arguments. If the application 
accepts messages, this information will also be packaged in 
a ``B_ARGV_RECEIVED`` message that the application will 
receive on-launch.

If the target application is already running, ``Launch()`` won't 
launch it again, unless it permits multiple instances to run 
concurrently (it doesn't wait for the messages to be sent or 
report errors encountered when they are). It fails for 
``B_SINGLE_LAUNCH`` and ``B_EXCLUSIVE_LAUNCH`` applications 
that have already been launched. Nevertheless, it assumes that 
you want the messages to get to the application and so 
delivers them to the currently running instance.

:param ref: the reference to the file to check.
:type ref: entry_ref
:param messageList: The list containing the arguments.
:type messageList: list
:return: a tuple (int,int) containing the status code and the ``team_id`` of the launched app:

   - A status code (int):

      - ``B_OK`` if this method is able to launch the application
      - ``B_BAD_VALUE`` if the ``mimeType`` is not valid or  an attempt is being made to send an on-launch message to an application that doesn't accept messages (a B_ARGV_ONLY app)
      - ``B_ALREADY_RUNNING`` The application is already running and can't be launched again (it's a B_SINGLE_LAUNCH or B_EXCLUSIVE_LAUNCH application).
      - ``B_LAUNCH_FAILED`` The attempt to launch the application failed for some other reason, such as insufficient memory.
      - A file system error: The ``mimeType`` can't be matched to an application.
   
   - The team identifier (int) for the newly launched application, or ``-1``
   
:rtype: tuple
)doc", py::arg("ref"), py::arg("args"))
.def("GetRecentDocuments", py::overload_cast<BMessage *, int32, const char *, const char *>(&BRoster::GetRecentDocuments, py::const_), R"doc(
Retrieve a list of the most recent documents. The ``refList`` 
message will be filled with ``entry_ref`` items (under the 
name "refs") providing information about the most recently 
used documents, up to the limit specified by ``maxCount``. 
If you want to obtain a list of documents of a specific type, 
you can specify a MIME type string in the ``fileType`` 
argument. Likewise, if you're only interested in files that 
want to be opened by a specific application, specify that 
application's signature in ``signature``; if you don't care, 
pass ``None``.

.. note::

   This version is kept for C++ compatibility.

:param refList: The message to be filled out with information.
:type refList: BMessage
:param maxCount: The maximum number of recent documents to retrieve.
:type maxCount: int
:param fileType: Optional MIME type to filter the documents (e.g., "text/plain"). Pass ``None`` for all types.
:type fileType: str
:param signature: Optional application signature to filter for documents associated with a specific app. Pass ``None`` for any application.
:type signature: str
)doc", py::arg("refList"), py::arg("maxCount"), py::arg("fileType")=NULL, py::arg("signature")=NULL)
.def("GetRecentDocuments", [](BRoster& self,int32 maxCount,const char* fileType, const char* signature){
	BMessage refList;
	self.GetRecentDocuments(&refList,maxCount,fileType,signature);
	return refList;
}, R"doc(
Convenient method to return a list of the most recent 
documents through a ``BMessage``. 
The message returned will be filled with ``entry_ref`` items 
(under the name "refs") providing information about the most 
recently used documents, up to the limit specified by ``maxCount``. 
If you want to obtain a list of documents of a specific type, 
you can specify a MIME type string in the ``fileType`` 
argument. Likewise, if you're only interested in files that 
want to be opened by a specific application, specify that 
application's signature in ``signature``; if you don't care, 
pass ``None``.

:param maxCount: The maximum number of recent documents to retrieve.
:type maxCount: int
:param fileType: Optional MIME type to filter the documents (e.g., "text/plain"). Pass ``None`` for all types.
:type fileType: str
:param signature: Optional application signature to filter for documents associated with a specific app. Pass ``None`` for any application.
:type signature: str
:return: A  message filled out with information (``entry_ref``s).
:rtype: BMessage
)doc", py::arg("maxCount"), py::arg("fileType")=NULL, py::arg("signature")=NULL)
.def("GetRecentDocuments", &GetRecentDocumentsWrapper, R"doc(
Retrieve a list of the most recent documents. The ``refList`` 
message will be filled with ``entry_ref`` items (under the 
name "refs") providing information about the most recently 
used documents, up to the limit specified by ``maxCount``. 
In this version you can get a list of files of multiple types
by specifying an array of strings in ``fileTypes`` and the 
number of types in the list in ``fileTypesCount``.


If you're only interested in files that want to be opened 
by a specific application, specify that application's 
signature in ``signature``; if you don't care, pass ``None``.

:param refList: The message to be filled out with information.
:type refList: BMessage
:param maxCount: The maximum number of recent documents to retrieve.
:type maxCount: int
:param fileTypes: Optional list of MIME types to filter the documents. Pass ``None`` for all types/no list.
:type fileType: list
:param fileTypesCount: The number of types in the list
:type fileTypesCount: int
:param signature: Optional application signature to filter for documents associated with a specific app. Pass ``None`` for any application.
:type signature: str
)doc", py::arg("refList"), py::arg("maxCount"), py::arg("fileTypes"), py::arg("fileTypesCount"), py::arg("signature")=NULL)
.def("GetRecentDocuments", &GetRecentDocumentsPythonicWrapper, R"doc(
Convenient method to return a list of the most recent 
documents through a ``BMessage``.
The message returned will be filled with ``entry_ref`` 
items (under the name "refs") providing information about 
the most recently used documents, up to the limit specified 
by ``maxCount``. 
In this version you can get a list of files of multiple types
by specifying an array of strings in ``fileTypes`` and the 
number of types in the list in ``fileTypesCount``.

If you're only interested in files that want to be opened 
by a specific application, specify that application's 
signature in ``signature``; if you don't care, pass ``None``.

:param maxCount: The maximum number of recent documents to retrieve.
:type maxCount: int
:param fileTypes: Optional list of MIME types to filter the documents. Pass ``None`` for all types/no list.
:type fileType: list
:param fileTypesCount: The number of types in the list
:type fileTypesCount: int
:param signature: Optional application signature to filter for documents associated with a specific app. Pass ``None`` for any application.
:type signature: str
:return: A  message filled out with information (``entry_ref``s).
:rtype: BMessage
)doc", py::arg("maxCount"), py::arg("fileTypes"), py::arg("fileTypesCount"), py::arg("signature")=NULL)
.def("GetRecentFolders", &BRoster::GetRecentFolders, R"doc(
Retrieve a list of the most recently-accessed folders. The 
``refList`` message will be filled with ``entry_ref`` items 
(under the name "refs") up to the limit specified by 
``maxCount``. If you're only interested in folders that 
were used by a specific application, specify that application's 
signature in ``signature``; if you don't care, pass ``None``.

.. note::

   This version is kept for C++ compatibility.

:param refList: The message to be filled out with information.
:type refList: BMessage
:param maxCount: The maximum number of recent documents to retrieve.
:type maxCount: int
:param signature: Optional application signature to filter for folders that were used by a specific application. Pass ``None`` for any application.
:type signature: str
)doc", py::arg("refList"), py::arg("maxCount"), py::arg("signature")=NULL)
.def("GetRecentFolders", [](const BRoster& self,int32 maxCount, const char * signature){
	BMessage refList;
	self.GetRecentFolders(&refList, maxCount, signature);
	return refList;
},R"doc(
Convenient method to return a list of the most recently-accessed 
folders through a ``BMessage``.
The message returned will be filled with ``entry_ref`` 
items (under the name "refs") up to the limit specified by 
``maxCount``. If you're only interested in folders that 
were used by a specific application, specify that application's 
signature in ``signature``; if you don't care, pass ``None``.

:param maxCount: The maximum number of recent documents to retrieve.
:type maxCount: int
:param signature: Optional application signature to filter for folders that were used by a specific application. Pass ``None`` for any application.
:type signature: str
:return: A message filled out with information (``entry_ref``s).
:rtype: BMessage
)doc",py::arg("maxCount"), py::arg("signature")=NULL)
.def("GetRecentApps", &BRoster::GetRecentApps, R"doc(
Return a list of the most recently-launched applications. The 
``BMessage`` ``refList`` will be filled out with information 
about the maxCount most recently-launched applications.

The resulting refList will have a field, "refs", containing 
the ``entry_ref``s to the resulting applications.

.. note::

   This version is kept for C++ compatibility.

:param refList: The message to be filled out with information.
:type refList: BMessage
:param maxCount: The maximum number of recent applications.
:type maxCount: int
)doc", py::arg("refList"), py::arg("maxCount"))
.def("GetRecentApps", [](BRoster& self, int32 maxCount){
	BMessage refList;
	self.GetRecentApps(&refList,maxCount);
	return refList;
}, R"doc(
Convenient method to return a list of the most recently-launched 
applications through a ``BMessage``. The message returned will 
be filled with ``entry_ref`` items (under the name "refs") up 
to the limit specified by ``maxCount``.

:param maxCount: The maximum number of recent applications.
:type maxCount: int
:return: A message filled out with information (``entry_ref``s).
:rtype: BMessage
)doc", py::arg("maxCount"))
.def("AddToRecentDocuments", &BRoster::AddToRecentDocuments, R"doc(
Add the document file specified by ``document`` to the list of 
recent documents. If you wish to record that a specific 
application used the document, you can specify the signature 
of that application using the ``signature`` argument; otherwise 
you can specify ``None``.

:param document: The document to add to the list of recent documents.
:type document: entry_ref
:param signature: The app signature that used the document you wish to record, or ``None``.
:type signature: str
)doc", py::arg("document"), py::arg("signature")=NULL)
.def("AddToRecentFolders", &BRoster::AddToRecentFolders, R"doc(
Add the folder specified by ``folder`` to the list of recent 
folders. If you wish to record that a specific application 
used the folder, you can specify the signature of that 
application using the ``signature`` argument; otherwise you 
can use ``None``.

:param folder: The folder to add to the list of recently-accessed folders.
:type folder: entry_ref
:param signature: The app signature that accessed the folder you wish to record, or ``None``.
:type signature: str
)doc", py::arg("folder"), py::arg("signature")=NULL)
;

m.attr("be_roster") = be_roster;


}
