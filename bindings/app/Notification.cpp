#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <app/Notification.h>
#include <Archivable.h>
#include <Entry.h>
#include <List.h>
#include <String.h>
#include <Bitmap.h>

namespace py = pybind11;


PYBIND11_MODULE(Notification,m)
{
py::enum_<notification_type>(m, "notification_type", "A set of constants identifying different kinds of notification.")
.value("B_INFORMATION_NOTIFICATION", notification_type::B_INFORMATION_NOTIFICATION, "General information notification.")
.value("B_IMPORTANT_NOTIFICATION", notification_type::B_IMPORTANT_NOTIFICATION, "Important notification that requires more attention.")
.value("B_ERROR_NOTIFICATION", notification_type::B_ERROR_NOTIFICATION, "Notification concerning an error or failure.")
.value("B_PROGRESS_NOTIFICATION", notification_type::B_PROGRESS_NOTIFICATION, "Notification used to display the progress of an ongoing operation.")
.export_values();

py::class_<BNotification>(m, "BNotification")//, R"doc()doc")
.def(py::init<notification_type>(), R"doc(
Construct an empty message, with the specified ``type``.
The type influences the style of the notification view.

:param type: The type of the notification.
:type type: notification_type
)doc", py::arg("type"))
.def(py::init<BMessage *>(), R"doc(
Construct a notification from an archive.

:param archive: The ``BMessage`` containing the archived notification.
:type archive: BMessage
)doc", py::arg("archive"))
.def("InitCheck", &BNotification::InitCheck, R"doc(
Return the status of the constructor.

:return: ``B_OK`` or an error code.
:rtype: int
)doc")
.def_static("Instantiate", &BNotification::Instantiate, R"doc(
Returns a new ``BNotification`` object from ``archive``.

This class implements the archiving API, and as such, you can 
build a new ``BNotification`` object from a previously created 
``BMessage`` archive. However, if the message doesn't contain 
an archived data for a ``BNotification`` object, this method 
returns ``None``.

:param archive: The archived notification.
:type archive: BMessage
:return: A ``BNotification`` object from archive or ``None`` if it doesn't contain a valid ``BNotification`` object.
:rtype: BNotification
)doc", py::arg("archive"))
.def("Archive", &BNotification::Archive, R"doc(
Archive the ``BNotification`` in the ``archive``.

.. note::
   This method is kept for compatibility with the original C++ API.

:param archive: BMessage object where the notification will be archived.
:type archive: BMessage
:param deep: If ``True``, perform a deep archive of all contained objects.
:type deep: bool
:return: ``B_OK`` if everything went fine, or other errors that describe why archiving has failed.
:rtype: int
)doc", py::arg("archive"), py::arg("deep")=true)
.def("Archive", [](const BNotification& self,bool deep){
	BMessage msg;
	status_t status = self.Archive(&msg,deep);
	return py::make_tuple(status,msg);
}, R"doc(
Convenience method to archive the ``BNotification`` into a ``BMessage``.
this verstion returns a tuple containing both the status of the
call and the message containing the archived notification.

:param deep: If ``True``, perform a deep archive of all contained objects.
:type deep: bool
:return: A tuple (status,data):

   - ``status`` (int): ``B_OK`` on success, or a Haiku error code
   - ``data`` (BMessage): the message where the notification will be archived.
   
:rtype: tuple
)doc", py::arg("deep")=true)
.def("SourceSignature", &BNotification::SourceSignature, R"doc(
Return the signature of the application where the notification originated.

When you build your own notifications, this will contain the signature 
of the current application. If you receive notifications from other 
applications, it will include theirs.

:return: The signature of the application where the notification originated.
:rtype: str
)doc")
.def("SourceName", &BNotification::SourceName, R"doc(
Return the name of the application where the notification originated.

When you build your own notifications, this will contain the name of 
the current application. If you receive notifications from other 
applications, it will include theirs.

:return: The name of the application where the notification originated.
:rtype: str
)doc")
.def("Type", &BNotification::Type, R"doc(
Return the type of the notification.

:return: A value of the notification_type enum that represents notification type.
:rtype: notification_type
)doc")
.def("Group", &BNotification::Group, R"doc(
Return the group of the notification.

:return: The string of the notification's group.
:rtype: str
)doc")
.def("SetGroup", &BNotification::SetGroup, R"doc(
Set a group for the notifcation.

The default behaviour of the notification_server is group the 
visible notifications per running application, and then in order 
in which they have been received. There may be situations where 
you want to override that behavior and group related notifications. 
When you set a group name, the notification_server will create a 
box with the group name as label, and insert all related 
notifications in that box.

:param group: The group for the notification.
:type group: BString
)doc", py::arg("group"))
.def("Title", &BNotification::Title, R"doc(
Return the title of the notification.

:return: The title of the notification as a string.
:rtype: str
)doc")
.def("SetTitle", &BNotification::SetTitle, R"doc(
Set a title for the notification.

:param title: The new title for the notification.
:type title: BString
)doc", py::arg("title"))
.def("Content", &BNotification::Content, R"doc(
Return the message of the notification.

:return: The message of the notification as a string.
:rtype: str
)doc")
.def("SetContent", &BNotification::SetContent, R"doc(
Set a message for the notification.

:param content: The message for the notification.
:type content: BString
)doc", py::arg("content"))
.def("MessageID", &BNotification::MessageID, R"doc(
Return the identifier of the notification.

:return: The identifier of the notification as a string.
:rtype: str
)doc")
.def("SetMessageID", &BNotification::SetMessageID, R"doc(
Sets notification's message identifier.

If you want to update the contents of an existing notification, 
you can set a identifier for this message. When you send a 
new or updated message with the same identifier, the 
``notification_server`` will update the existing message 
with the new content.

In order to effectively use this feature, you will have to 
make sure the identifier is unique within the current 
application.

:param id: The message identifier.
:type id: BString
)doc", py::arg("id"))
.def("Progress", &BNotification::Progress, "")
.def("SetProgress", &BNotification::SetProgress, "", py::arg("progress"))
.def("OnClickApp", &BNotification::OnClickApp, "")
.def("SetOnClickApp", &BNotification::SetOnClickApp, "", py::arg("app"))
.def("OnClickFile", &BNotification::OnClickFile, "")
.def("SetOnClickFile", &BNotification::SetOnClickFile, "", py::arg("file"))
.def("AddOnClickRef", &BNotification::AddOnClickRef, "", py::arg("ref"))
.def("CountOnClickRefs", &BNotification::CountOnClickRefs, "")
.def("OnClickRefAt", &BNotification::OnClickRefAt, "", py::arg("index"))
.def("AddOnClickArg", &BNotification::AddOnClickArg, "", py::arg("arg"))
.def("CountOnClickArgs", &BNotification::CountOnClickArgs, "")
.def("OnClickArgAt", &BNotification::OnClickArgAt, "", py::arg("index"))
.def("Icon", &BNotification::Icon, "")
.def("SetIcon", &BNotification::SetIcon, "", py::arg("icon"))
.def("Send", &BNotification::Send, "", py::arg("timeout")=- 1)
;


}
