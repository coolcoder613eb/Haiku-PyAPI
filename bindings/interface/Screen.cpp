#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/Screen.h>
#include <Accelerant.h>
#include <GraphicsDefs.h>
#include <Rect.h>
#include <OS.h>

namespace py = pybind11;
using namespace BPrivate;

PYBIND11_MODULE(Screen,m)
{
m.attr("BPrivateScreen") = BPrivateScreen;

py::class_<BScreen>(m, "BScreen")
.def(py::init<screen_id>(), "", py::arg("id")=B_MAIN_SCREEN_ID)
.def(py::init<BWindow *>(), "", py::arg("window"))
.def("IsValid", &BScreen::IsValid, "")
.def("SetToNext", &BScreen::SetToNext, "")
.def("ColorSpace", &BScreen::ColorSpace, "")
.def("Frame", &BScreen::Frame, "")
.def("ID", &BScreen::ID, "")
.def("WaitForRetrace", py::overload_cast<>(&BScreen::WaitForRetrace), "")
.def("WaitForRetrace", py::overload_cast<bigtime_t>(&BScreen::WaitForRetrace), "", py::arg("timeout"))
.def("IndexForColor", py::overload_cast<rgb_color>(&BScreen::IndexForColor), "", py::arg("color"))
.def("IndexForColor", py::overload_cast<unsigned char, unsigned char, unsigned char, unsigned char>(&BScreen::IndexForColor), "", py::arg("red"), py::arg("green"), py::arg("blue"), py::arg("alpha")=255)
.def("ColorForIndex", &BScreen::ColorForIndex, "", py::arg("index"))
.def("InvertIndex", &BScreen::InvertIndex, "", py::arg("index"))
.def("ColorMap", &BScreen::ColorMap, "")
.def("GetBitmap", &BScreen::GetBitmap, "", py::arg("_bitmap"), py::arg("drawCursor")=true, py::arg("frame")=NULL)
.def("ReadBitmap", &BScreen::ReadBitmap, "", py::arg("bitmap"), py::arg("drawCursor")=true, py::arg("frame")=NULL)
.def("DesktopColor", py::overload_cast<>(&BScreen::DesktopColor), "")
.def("DesktopColor", py::overload_cast<unsigned int>(&BScreen::DesktopColor), "", py::arg("workspace"))
.def("SetDesktopColor", py::overload_cast<rgb_color, bool>(&BScreen::SetDesktopColor), "", py::arg("color"), py::arg("stick")=true)
.def("SetDesktopColor", py::overload_cast<rgb_color, unsigned int, bool>(&BScreen::SetDesktopColor), "", py::arg("color"), py::arg("workspace"), py::arg("stick")=true)
.def("ProposeMode", &BScreen::ProposeMode, "", py::arg("target"), py::arg("low"), py::arg("high"))
.def("GetModeList", &BScreen::GetModeList, "", py::arg("_modeList"), py::arg("_count"))
.def("GetMode", py::overload_cast<display_mode *>(&BScreen::GetMode), "", py::arg("mode"))
.def("GetMode", py::overload_cast<unsigned int, display_mode *>(&BScreen::GetMode), "", py::arg("workspace"), py::arg("mode"))
.def("SetMode", py::overload_cast<display_mode *, bool>(&BScreen::SetMode), "", py::arg("mode"), py::arg("makeDefault")=false)
.def("SetMode", py::overload_cast<unsigned int, display_mode *, bool>(&BScreen::SetMode), "", py::arg("workspace"), py::arg("mode"), py::arg("makeDefault")=false)
.def("GetDeviceInfo", &BScreen::GetDeviceInfo, "", py::arg("info"))
.def("GetMonitorInfo", &BScreen::GetMonitorInfo, "", py::arg("info"))
.def("GetPixelClockLimits", &BScreen::GetPixelClockLimits, "", py::arg("mode"), py::arg("_low"), py::arg("_high"))
.def("GetTimingConstraints", &BScreen::GetTimingConstraints, "", py::arg("timingConstraints"))
.def("SetDPMS", &BScreen::SetDPMS, "", py::arg("state"))
.def("DPMSState", &BScreen::DPMSState, "")
.def("DPMSCapabilites", &BScreen::DPMSCapabilites, "")
.def("GetBrightness", &BScreen::GetBrightness, "", py::arg("brightness"))
.def("SetBrightness", &BScreen::SetBrightness, "", py::arg("brightness"))
;


}
