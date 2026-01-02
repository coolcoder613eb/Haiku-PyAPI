#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <app/Cursor.h>
#include <Archivable.h>
#include <InterfaceDefs.h>
#include <Bitmap.h>
#include <Point.h>

namespace py = pybind11;


PYBIND11_MODULE(Cursor,m)
{
py::enum_<BCursorID>(m, "BCursorID", R"doc(
IDs for Haiku's standard cursor shapes for a complete set of semantic cursors.
)doc")
.value("B_CURSOR_ID_SYSTEM_DEFAULT", BCursorID::B_CURSOR_ID_SYSTEM_DEFAULT, R"doc(
   System default cursor
   
   for its numerical value look down below

)doc")
.value("B_CURSOR_ID_CONTEXT_MENU", BCursorID::B_CURSOR_ID_CONTEXT_MENU, R"doc(
   Context menu cursor
   
   for its numerical value look down below

)doc")
.value("B_CURSOR_ID_COPY", BCursorID::B_CURSOR_ID_COPY, R"doc(
   Copy cursor
   
   for its numerical value look down below

)doc")
.value("B_CURSOR_ID_CREATE_LINK", BCursorID::B_CURSOR_ID_CREATE_LINK, R"doc(
   Symlink cursor
   
   for its numerical value look down below

)doc")
.value("B_CURSOR_ID_CROSS_HAIR", BCursorID::B_CURSOR_ID_CROSS_HAIR, R"doc(
   Cross hairs cursor
   
   for its numerical value look down below

)doc")
.value("B_CURSOR_ID_FOLLOW_LINK", BCursorID::B_CURSOR_ID_FOLLOW_LINK, R"doc(
   Follow html link cursor
   
   for its numerical value look down below

)doc")
.value("B_CURSOR_ID_GRAB", BCursorID::B_CURSOR_ID_GRAB, R"doc(
   Grab cursor
   
   for its numerical value look down below

)doc")
.value("B_CURSOR_ID_GRABBING", BCursorID::B_CURSOR_ID_GRABBING, R"doc(
   Grabbing cursor (mouse down)
   
   for its numerical value look down below

)doc")
.value("B_CURSOR_ID_HELP", BCursorID::B_CURSOR_ID_HELP, R"doc(
   Help cursor
   
   for its numerical value look down below

)doc")
.value("B_CURSOR_ID_I_BEAM", BCursorID::B_CURSOR_ID_I_BEAM, R"doc(
   I beam cursor for text
   
   for its numerical value look down below

)doc")
.value("B_CURSOR_ID_I_BEAM_HORIZONTAL", BCursorID::B_CURSOR_ID_I_BEAM_HORIZONTAL, R"doc(
   Horizontal I beam cursor
   
   for its numerical value look down below

)doc")
.value("B_CURSOR_ID_MOVE", BCursorID::B_CURSOR_ID_MOVE, R"doc(
   Move cursor
   
   for its numerical value look down below

)doc")
.value("B_CURSOR_ID_NO_CURSOR", BCursorID::B_CURSOR_ID_NO_CURSOR, R"doc(
   No cursor
   
   for its numerical value look down below

)doc")
.value("B_CURSOR_ID_NOT_ALLOWED", BCursorID::B_CURSOR_ID_NOT_ALLOWED, R"doc(
   Not allowed cursor
   
   for its numerical value look down below

)doc")
.value("B_CURSOR_ID_PROGRESS", BCursorID::B_CURSOR_ID_PROGRESS, R"doc(
   Progress cursor
   
   for its numerical value look down below

)doc")
.value("B_CURSOR_ID_RESIZE_NORTH", BCursorID::B_CURSOR_ID_RESIZE_NORTH, R"doc(
   Resize north cursor
   
   for its numerical value look down below

)doc")
.value("B_CURSOR_ID_RESIZE_EAST", BCursorID::B_CURSOR_ID_RESIZE_EAST, R"doc(
   Resize east cursor
   
   for its numerical value look down below

)doc")
.value("B_CURSOR_ID_RESIZE_SOUTH", BCursorID::B_CURSOR_ID_RESIZE_SOUTH, R"doc(
   Resize south cursor
   
   for its numerical value look down below

)doc")
.value("B_CURSOR_ID_RESIZE_WEST", BCursorID::B_CURSOR_ID_RESIZE_WEST, R"doc(
   Resize west cursor
   
   for its numerical value look down below

)doc")
.value("B_CURSOR_ID_RESIZE_NORTH_EAST", BCursorID::B_CURSOR_ID_RESIZE_NORTH_EAST, R"doc(
   Resize north east cursor
   
   for its numerical value look down below

)doc")
.value("B_CURSOR_ID_RESIZE_NORTH_WEST", BCursorID::B_CURSOR_ID_RESIZE_NORTH_WEST, R"doc(
   Resize north west cursor
   
   for its numerical value look down below

)doc")
.value("B_CURSOR_ID_RESIZE_SOUTH_EAST", BCursorID::B_CURSOR_ID_RESIZE_SOUTH_EAST, R"doc(
   Resize south east cursor
   
   for its numerical value look down below

)doc")
.value("B_CURSOR_ID_RESIZE_SOUTH_WEST", BCursorID::B_CURSOR_ID_RESIZE_SOUTH_WEST, R"doc(
   Resize south west cursor
   
   for its numerical value look down below

)doc")
.value("B_CURSOR_ID_RESIZE_NORTH_SOUTH", BCursorID::B_CURSOR_ID_RESIZE_NORTH_SOUTH, R"doc(
   Resize north south cursor
   
   for its numerical value look down below

)doc")
.value("B_CURSOR_ID_RESIZE_EAST_WEST", BCursorID::B_CURSOR_ID_RESIZE_EAST_WEST, R"doc(
   Resize east west cursor
   
   for its numerical value look down below

)doc")
.value("B_CURSOR_ID_RESIZE_NORTH_EAST_SOUTH_WEST", BCursorID::B_CURSOR_ID_RESIZE_NORTH_EAST_SOUTH_WEST, R"doc(
   Resize north east south west cursor
   
   for its numerical value look down below

)doc")
.value("B_CURSOR_ID_RESIZE_NORTH_WEST_SOUTH_EAST", BCursorID::B_CURSOR_ID_RESIZE_NORTH_WEST_SOUTH_EAST, R"doc(
   Resize north west south east cursor
   
   for its numerical value look down below

)doc")
.value("B_CURSOR_ID_ZOOM_IN", BCursorID::B_CURSOR_ID_ZOOM_IN, R"doc(
   Zoom in cursor
   
   for its numerical value look down below

)doc")
.value("B_CURSOR_ID_ZOOM_OUT", BCursorID::B_CURSOR_ID_ZOOM_OUT, R"doc(
   Zoom out cursor
   
   for its numerical value look down below

)doc")
.export_values();

py::class_<BCursor>(m, "BCursor")
/*
.def(py::init<const void *>(), "", py::arg("cursorData"))*/
.def(py::init([](py::buffer cursorData) {
	py::buffer_info info = cursorData.request();
	if (info.ptr == nullptr) {
		throw std::runtime_error("Data buffer is null");
	}
	return new BCursor(info.ptr);
}), R"doc(
Create a cursor from raw cursor data.

The buffer must contain valid Haiku cursor data (typically a
legacy 68-byte cursor buffer).

if the buffer is null (``None``) an exception is raised

:param cursorData: Raw cursor data buffer.
:type cursorData: buffer
:no-index:
)doc",
    py::arg("cursorData")
)
.def(py::init<const BCursor &>(), R"doc(
Initializes a new cursor object from another cursor object.

:param other: Some other cursor object.
:type other: BCursor
)doc", py::arg("other"))
.def(py::init<BCursorID>(), R"doc(
Initializes a new cursor object from a predefined cursor id.

:param id: An ID of BCursorID enum, see above.
:type id: int
:no-index:
)doc", py::arg("id"))
.def(py::init<BMessage *>(), R"doc(
Initializes a new cursor object from a message archive.

:param data: A message containing the archived data.
:type data: BMessage
)doc", py::arg("data"))
.def(py::init<const BBitmap *, const BPoint &>(), R"doc(
Initializes a new cursor object from a bitmap object and a point object.

:param bitmap: The bitmap object to initialize from.
:type bitmap: BBitmap
:param hotspot: The cursor hotspot.
:type hotspot: BPoint
:no-index:
)doc", py::arg("bitmap"), py::arg("hotspot"))
.def("InitCheck", &BCursor::InitCheck, R"doc(
Return the initialization status.

:return: ``B_OK`` if properly initialized or an error code otherwise.
:rtype: int
)doc")
.def("Archive", &BCursor::Archive, R"doc(
Archive the cursor into a message.

.. note::
   Not implemented!
   
:param archive: The message in which we'll archive the cursor.
:type archive: BMessage
:param deep: If ``True``, all children of this object should be archived as well.
:type deep: bool
:return: ``B_OK`` if success, or an error otherwise.
:rtype: int
)doc", py::arg("archive"), py::arg("deep")=true)
.def("Archive", [](const BCursor& self,bool deep){
	BMessage msg;
	status_t status = self.Archive(&msg,deep);
	return py::make_tuple(status,msg);
}, R"doc(
Convenience method to archive the ``BCursor`` into a ``BMessage``.
this verstion returns a tuple containing both the status of the
call and the message containing the archived cursor.

.. note::
   Not implemented!

:param deep: If ``True``, perform a deep archive of all contained objects.
:type deep: bool
:return: A tuple (status,archive):

   - ``status`` (int): ``B_OK`` on success, or a Haiku error code
   - ``archive`` (BMessage): the message where the cursor will be archived.
   
:rtype: tuple
)doc", py::arg("deep")=true)
.def_static("Instantiate", &BCursor::Instantiate, R"doc(
Instantiate a cursor from an archived message. 

.. note::
   Not implemented!

:param archive: The message containing the cursor.
:type archive: BMessage
:return: The BArchivable object from the message.
:rtype: BArchivable
)doc", py::arg("archive"))
//.def("operator=", &BCursor::operator=, "", py::arg("other"))
.def("__eq__", &BCursor::operator==, R"doc(
Compare two cursors for equality.

:param other: The cursor to compare with.
:type other: BCursor
:return: ``True`` if the cursors are equal.
:rtype: bool
)doc", py::arg("other"))
.def("__ne__", &BCursor::operator!=, R"doc(
Compare two cursors for inequality.

:param other: The cursor to compare with.
:type other: BCursor
:return: ``True`` if the cursors are not equal.
:rtype: bool
)doc", py::arg("other"))
.def("__repr__", []() {
    return std::string("<BCursor>");
})
;

}
