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

class PyBCursor : public BCursor{
	public:
        using BCursor::BCursor;
        status_t			Archive(BMessage* archive, bool deep = true) const override {
        	PYBIND11_OVERLOAD(status_t, BCursor, Archive, archive, deep);
        }
};

PYBIND11_MODULE(Cursor,m)
{
py::enum_<BCursorID>(m, "BCursorID", "")
.value("B_CURSOR_ID_SYSTEM_DEFAULT", BCursorID::B_CURSOR_ID_SYSTEM_DEFAULT, "")
.value("B_CURSOR_ID_CONTEXT_MENU", BCursorID::B_CURSOR_ID_CONTEXT_MENU, "")
.value("B_CURSOR_ID_COPY", BCursorID::B_CURSOR_ID_COPY, "")
.value("B_CURSOR_ID_CREATE_LINK", BCursorID::B_CURSOR_ID_CREATE_LINK, "")
.value("B_CURSOR_ID_CROSS_HAIR", BCursorID::B_CURSOR_ID_CROSS_HAIR, "")
.value("B_CURSOR_ID_FOLLOW_LINK", BCursorID::B_CURSOR_ID_FOLLOW_LINK, "")
.value("B_CURSOR_ID_GRAB", BCursorID::B_CURSOR_ID_GRAB, "")
.value("B_CURSOR_ID_GRABBING", BCursorID::B_CURSOR_ID_GRABBING, "")
.value("B_CURSOR_ID_HELP", BCursorID::B_CURSOR_ID_HELP, "")
.value("B_CURSOR_ID_I_BEAM", BCursorID::B_CURSOR_ID_I_BEAM, "")
.value("B_CURSOR_ID_I_BEAM_HORIZONTAL", BCursorID::B_CURSOR_ID_I_BEAM_HORIZONTAL, "")
.value("B_CURSOR_ID_MOVE", BCursorID::B_CURSOR_ID_MOVE, "")
.value("B_CURSOR_ID_NO_CURSOR", BCursorID::B_CURSOR_ID_NO_CURSOR, "")
.value("B_CURSOR_ID_NOT_ALLOWED", BCursorID::B_CURSOR_ID_NOT_ALLOWED, "")
.value("B_CURSOR_ID_PROGRESS", BCursorID::B_CURSOR_ID_PROGRESS, "")
.value("B_CURSOR_ID_RESIZE_NORTH", BCursorID::B_CURSOR_ID_RESIZE_NORTH, "")
.value("B_CURSOR_ID_RESIZE_EAST", BCursorID::B_CURSOR_ID_RESIZE_EAST, "")
.value("B_CURSOR_ID_RESIZE_SOUTH", BCursorID::B_CURSOR_ID_RESIZE_SOUTH, "")
.value("B_CURSOR_ID_RESIZE_WEST", BCursorID::B_CURSOR_ID_RESIZE_WEST, "")
.value("B_CURSOR_ID_RESIZE_NORTH_EAST", BCursorID::B_CURSOR_ID_RESIZE_NORTH_EAST, "")
.value("B_CURSOR_ID_RESIZE_NORTH_WEST", BCursorID::B_CURSOR_ID_RESIZE_NORTH_WEST, "")
.value("B_CURSOR_ID_RESIZE_SOUTH_EAST", BCursorID::B_CURSOR_ID_RESIZE_SOUTH_EAST, "")
.value("B_CURSOR_ID_RESIZE_SOUTH_WEST", BCursorID::B_CURSOR_ID_RESIZE_SOUTH_WEST, "")
.value("B_CURSOR_ID_RESIZE_NORTH_SOUTH", BCursorID::B_CURSOR_ID_RESIZE_NORTH_SOUTH, "")
.value("B_CURSOR_ID_RESIZE_EAST_WEST", BCursorID::B_CURSOR_ID_RESIZE_EAST_WEST, "")
.value("B_CURSOR_ID_RESIZE_NORTH_EAST_SOUTH_WEST", BCursorID::B_CURSOR_ID_RESIZE_NORTH_EAST_SOUTH_WEST, "")
.value("B_CURSOR_ID_RESIZE_NORTH_WEST_SOUTH_EAST", BCursorID::B_CURSOR_ID_RESIZE_NORTH_WEST_SOUTH_EAST, "")
.value("B_CURSOR_ID_ZOOM_IN", BCursorID::B_CURSOR_ID_ZOOM_IN, "")
.value("B_CURSOR_ID_ZOOM_OUT", BCursorID::B_CURSOR_ID_ZOOM_OUT, "")
.export_values();

py::class_<BCursor, PyBCursor>(m, "BCursor")
.def(py::init<const void *>(), "", py::arg("cursorData"))
.def(py::init<const BCursor &>(), "", py::arg("other"))
.def(py::init<BCursorID>(), "", py::arg("id"))
.def(py::init<BMessage *>(), "", py::arg("data"))
.def(py::init<const BBitmap *, const BPoint &>(), "", py::arg("bitmap"), py::arg("hotspot"))
.def("InitCheck", &BCursor::InitCheck, "")
.def("Archive", &BCursor::Archive, "", py::arg("archive"), py::arg("deep")=true)
.def_static("Instantiate", &BCursor::Instantiate, "", py::arg("archive"))
.def("operator=", &BCursor::operator=, "", py::arg("other"))
.def("__eq__", &BCursor::operator==, "", py::arg("other"))
.def("__ne__", &BCursor::operator!=, "", py::arg("other"))
;


}
