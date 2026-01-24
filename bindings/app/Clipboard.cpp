#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <app/Clipboard.h>
#include <BeBuild.h>
#include <Locker.h>
#include <Messenger.h>

namespace py = pybind11;


PYBIND11_MODULE(Clipboard,m)
{
m.attr("B_CLIPBOARD_CHANGED") = "CLCH";

py::class_<BClipboard>(m, "BClipboard", R"doc(
Used for short-term data storage between documents and applications 
via copy and paste operations.

Clipboards are differentiated by their name. In order for two 
applications to share a clipboard they simply have to create a 
BClipboard object with the same name. However, it is rarely necessary 
to create your own clipboard, instead you can use the `be_clipboard` 
system clipboard object.

.. note::
   To access the system clipboard without a BApplication object, 
   create a BClipboard object with the name "system". You should 
   avoid creating a custom clipboard with the name "system" for 
   your own use.

To access the clipboard data call the Data() method.
)doc")
.def(py::init<const char *, bool>(), R"doc(
Create a BClipboard object with the given name.

If the name parameter is ``None`` then the "system" BClipboard object 
is constructed instead.

:param name: The name of the clipboard.
:type name: str
:param transient: If ``True``, lose data after a reboot (currently unused). Defaults to ``False``
:type transient: bool
)doc", py::arg("name"), py::arg("transient")=false)
.def("Name", &BClipboard::Name, R"doc(
Return the name of the BClipboard object.

:return: The name of the clipboard.
:rtype: str
)doc")
.def("LocalCount", &BClipboard::LocalCount, R"doc(
Return the (locally cached) number of succesful commits to the clipboard.

.. note::
   This method returns a locally cached value, which might already 
   be obsolete. For an up-to-date value use SystemCount().
   
:return: The number of commits to the clipboard.
:rtype: int
)doc")
.def("SystemCount", &BClipboard::SystemCount, R"doc(
Return the number of commits to the clipboard.

.. note::
   This method retrieves the value directly from the system service 
   managing the clipboards, so it is more expensive, but more 
   up-to-date than LocalCount(), which returns a locally cached 
   value.

:return: The number of commits to the clipboard.
:rtype: int
)doc")
.def("StartWatching", &BClipboard::StartWatching, R"doc(
Start watching the BClipboard object for changes.
When some action occurs (e.g. cut or copy), a ``B_CLIPBOARD_CHANGED``
message is sent to the target.

:param target: A BMessenger that will receive the ``B_CLIPBOARD_CHANGED`` message
:type target: BMessenger
:return: ``B_OK`` if success, ``B_BAD_VALUE`` if target is invalid, ``B_ERROR`` an error occured.
:rtype: int
)doc", py::arg("target"))
.def("StopWatching", &BClipboard::StopWatching, R"doc(
Stop watching the BClipboard object for changes.

:param target: The BMessenger that will stop receiving the ``B_CLIPBOARD_CHANGED`` message
:type target: BMessenger
:return: ``B_OK` if success, ``B_BAD_VALUE`` if target is invalid, ``B_ERROR`` an error occured.
:rtype: int
)doc", py::arg("target"))
.def("Lock", &BClipboard::Lock, R"doc(
Acquire the lock on the clipboard, preventing other threads from 
accessing (reading or writing) its content.

:return: ``True`` if the clipboard was locked, ``False`` otherwise.
:rtype: bool
)doc")
.def("Unlock", &BClipboard::Unlock, R"doc(
Unlock the clipboard.
)doc")
.def("IsLocked", &BClipboard::IsLocked, R"doc(
Return whether or not the clipboard is locked.

:return: ``True`` if the clipboard is locked, ``False`` if it is unlocked.
:rtype: bool
)doc")
.def("Clear", &BClipboard::Clear, R"doc(
Clear out all data from the clipboard.
You should call Clear() before adding new data to the BClipboard object.

:return: ``B_OK`` if successful, ``B_NOT_ALLOWED`` if the clipboard is not locked, ``B_NO_MEMORY`` if ran out of memory initializing the data message, ``B_ERROR`` if another error occured
:rtype: int
)doc")
.def("Commit", py::overload_cast<>(&BClipboard::Commit), R"doc(
Commit the clipboard data to the BClipboard object.

:return: ``B_OK`` if successful, ``B_NOT_ALLOWED`` if the clipboard is not locked, ``B_ERROR`` if another error occured
:rtype: int
)doc")
.def("Commit", py::overload_cast<bool>(&BClipboard::Commit), R"doc(
Commit the clipboard data to the BClipboard object with the 
option to fail if there is a change to the clipboard data.

:param failIfChanged: Whether or not to fail to commit the changes if there's a change in the clipboard data.
:type failIfChanged: bool
:return: ``B_OK`` if successful, ``B_NOT_ALLOWED`` if the clipboard isn't locked, ``B_ERROR`` if another error occured
:rtype: int
)doc", py::arg("failIfChanged"))
.def("Revert", &BClipboard::Revert, R"doc(
Revert the clipboard data.

The method should be used in the case that you have made a 
change to the clipboard data message and then decide to revert 
the change instead of committing it.

:return: ``B_OK`` if successful, ``B_NOT_ALLOWED`` if the clipboard isn't locked, ``B_NO_MEMORY`` if ran out of memory initializing the data message, ``B_ERROR`` if another error occured
:rtype: int
)doc")
.def("DataSource", &BClipboard::DataSource, R"doc(
Get a BMessenger object targeting the application that last modified the clipboard.

.. note:: 
   The clipboard object does not need to be locked to call this method.

:return: A BMessenger that targets the application that last modified the clipboard
:rtype: BMessenger
)doc")
.def("Data", &BClipboard::Data, R"doc(
Return the BMessage object that holds the clipboard data.

.. note::
   If the BClipboard object is not locked this method returns ``None``.

:return: The BMessage object that holds the clipboard data or ``None`` if the clipboard is not locked
:rtype: BMessage
)doc")
.def("__repr__", [](const BClipboard& clip) {
    const char* nam = clip.Name();
    if (nam && nam[0] != '\0') {
        return std::string("BClipboard(\"") + nam + "\")";
    }
    return std::string("<BClipboard>");
})
.def_property_readonly_static("be_clipboard", [](py::object /* self */) {
        return be_clipboard;
}, py::return_value_policy::reference)
;

m.def("get_be_clipboard", []() {
    return be_clipboard; 
}, py::return_value_policy::reference);
//m.attr("be_clipboard") = be_clipboard;
//m.attr("be_clipboard") = py::cast(be_clipboard, py::return_value_policy::reference);
}
