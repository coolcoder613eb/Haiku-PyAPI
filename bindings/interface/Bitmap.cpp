#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/Bitmap.h>
#include <Archivable.h>
#include <InterfaceDefs.h>
#include <Rect.h>
#include <View.h>

namespace py = pybind11;
using namespace BPrivate;

PYBIND11_MODULE(Bitmap,m)
{
m.attr("B_BITMAP_CLEAR_TO_WHITE") = 1;
m.attr("B_BITMAP_ACCEPTS_VIEWS") = 2;
m.attr("B_BITMAP_IS_AREA") = 4;
m.attr("B_BITMAP_IS_LOCKED") = "0x00000008 | B_BITMAP_IS_AREA";
m.attr("B_BITMAP_IS_CONTIGUOUS") = "0x00000010 | B_BITMAP_IS_LOCKED";
m.attr("B_BITMAP_IS_OFFSCREEN") = 32;
m.attr("B_BITMAP_WILL_OVERLAY") = "0x00000040 | B_BITMAP_IS_OFFSCREEN";
m.attr("B_BITMAP_RESERVE_OVERLAY_CHANNEL") = 128;
m.attr("B_BITMAP_NO_SERVER_LINK") = 256;

//m.attr("BPrivateScreen") = BPrivateScreen;

py::class_<BBitmap, BArchivable>(m, "BBitmap")
.def(py::init<BRect, unsigned int, color_space, int, screen_id>(), "", py::arg("bounds"), py::arg("flags"), py::arg("colorSpace"), py::arg("bytesPerRow")=B_ANY_BYTES_PER_ROW, py::arg("screenID")=B_MAIN_SCREEN_ID)
.def(py::init<BRect, color_space, bool, bool>(), "", py::arg("bounds"), py::arg("colorSpace"), py::arg("acceptsViews")=false, py::arg("needsContiguous")=false)
.def(py::init<const BBitmap &, unsigned int>(), "", py::arg("source"), py::arg("flags"))
.def(py::init<const BBitmap &>(), "", py::arg("source"))
.def(py::init<const BBitmap *, bool, bool>(), "", py::arg("source"), py::arg("acceptsViews")=false, py::arg("needsContiguous")=false)
.def(py::init<BMessage *>(), "", py::arg("data"))
.def_static("Instantiate", &BBitmap::Instantiate, "", py::arg("data"))
.def("Archive", &BBitmap::Archive, "", py::arg("data"), py::arg("deep")=true)
.def("InitCheck", &BBitmap::InitCheck, "")
.def("IsValid", &BBitmap::IsValid, "")
.def("LockBits", &BBitmap::LockBits, "", py::arg("state")=NULL)
.def("UnlockBits", &BBitmap::UnlockBits, "")
.def("Area", &BBitmap::Area, "")
.def("Bits", &BBitmap::Bits, "")
.def("BitsLength", &BBitmap::BitsLength, "")
.def("BytesPerRow", &BBitmap::BytesPerRow, "")
.def("ColorSpace", &BBitmap::ColorSpace, "")
.def("Bounds", &BBitmap::Bounds, "")
.def("SetDrawingFlags", &BBitmap::SetDrawingFlags, "", py::arg("flags"))
.def("Flags", &BBitmap::Flags, "")
.def("ImportBits", py::overload_cast<const void *, int32, int32, int32, color_space>(&BBitmap::ImportBits), "", py::arg("data"), py::arg("length"), py::arg("bpr"), py::arg("offset"), py::arg("colorSpace"))
.def("ImportBits", py::overload_cast<const void *, int32, int32, color_space, BPoint, BPoint, BSize>(&BBitmap::ImportBits), "", py::arg("data"), py::arg("length"), py::arg("bpr"), py::arg("colorSpace"), py::arg("from"), py::arg("to"), py::arg("size"))
.def("ImportBits", py::overload_cast<const BBitmap *>(&BBitmap::ImportBits), "", py::arg("bitmap"))
.def("ImportBits", py::overload_cast<const BBitmap *, BPoint, BPoint, BSize>(&BBitmap::ImportBits), "", py::arg("bitmap"), py::arg("from"), py::arg("to"), py::arg("size"))
.def("GetOverlayRestrictions", &BBitmap::GetOverlayRestrictions, "", py::arg("restrictions"))
.def("AddChild", &BBitmap::AddChild, "", py::arg("view"))
.def("RemoveChild", &BBitmap::RemoveChild, "", py::arg("view"))
.def("CountChildren", &BBitmap::CountChildren, "")
.def("ChildAt", &BBitmap::ChildAt, "", py::arg("index"))
.def("FindView", py::overload_cast<const char *>(&BBitmap::FindView, py::const_), "", py::arg("viewName"))
.def("FindView", py::overload_cast<BPoint>(&BBitmap::FindView, py::const_), "", py::arg("point"))
.def("Lock", &BBitmap::Lock, "")
.def("Unlock", &BBitmap::Unlock, "")
.def("IsLocked", &BBitmap::IsLocked, "")
.def("operator=", &BBitmap::operator=, "", py::arg("source"))
.def("SetBits", &BBitmap::SetBits, "", py::arg("data"), py::arg("length"), py::arg("offset"), py::arg("colorSpace"))
//.def_readwrite("Private", &BBitmap::Private, "")
;


}
