#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/ColorControl.h>
#include <interface/Layout.h>
#include <interface/Bitmap.h>
#include <Control.h>

namespace py = pybind11;

class PyBColorControl : public BColorControl{
	public:
        using BColorControl::BColorControl;
        status_t	Archive(BMessage* data, bool deep = true) const override {
        	PYBIND11_OVERLOAD(status_t, BColorControl, Archive, data, deep);
        }
        void				SetLayout(BLayout* layout) override {
            PYBIND11_OVERLOAD(void, BColorControl, SetLayout, layout);
        }
        void				SetValue(int32 color_value) override {
            PYBIND11_OVERLOAD(void, BColorControl, SetValue, color_value);
        }
        void				SetEnabled(bool state) override {
            PYBIND11_OVERLOAD(void, BColorControl, SetEnabled, state);
        }
        void				AttachedToWindow() override {
            PYBIND11_OVERLOAD(void, BColorControl, AttachedToWindow);
        }
        void				MessageReceived(BMessage* message) override {
            PYBIND11_OVERLOAD(void, BColorControl, MessageReceived, message);
        }
        void				Draw(BRect updateRect) override {
            PYBIND11_OVERLOAD(void, BColorControl, Draw, updateRect);
        }
        void				MouseDown(BPoint where) override {
            PYBIND11_OVERLOAD(void, BColorControl, MouseDown, where);
        }
        void				KeyDown(const char* bytes, int32 numBytes) override {
            PYBIND11_OVERLOAD(void, BColorControl, KeyDown, bytes, numBytes);
        }
        void				SetCellSize(float size) override {
            PYBIND11_OVERLOAD(void, BColorControl, SetCellSize, size);
        }
        void				SetLayout(color_control_layout layout) override {
            PYBIND11_OVERLOAD(void, BColorControl, SetLayout, layout);
        }
        void				WindowActivated(bool state) override {
            PYBIND11_OVERLOAD(void, BColorControl, WindowActivated, state);
        }
        void				MouseUp(BPoint point) override {
            PYBIND11_OVERLOAD(void, BColorControl, MouseUp, point);
        }
        void				MouseMoved(BPoint point, uint32 code, const BMessage* dragMessage) override {
        	PYBIND11_OVERLOAD(void, BColorControl, MouseMoved, point, code, dragMessage);
        }
        void				DetachedFromWindow() override {
            PYBIND11_OVERLOAD(void, BColorControl, DetachedFromWindow);
        }
        void				GetPreferredSize(float* _width, float* _height) override {
            PYBIND11_OVERLOAD(void, BColorControl, GetPreferredSize, _width, _height);
        }
        void				ResizeToPreferred() override {
            PYBIND11_OVERLOAD(void, BColorControl, ResizeToPreferred);
        }
        status_t			Invoke(BMessage* message = NULL) override {
            PYBIND11_OVERLOAD(status_t, BColorControl, Invoke, message);
        }
        void				FrameMoved(BPoint newPosition) override {
            PYBIND11_OVERLOAD(void, BColorControl, FrameMoved, newPosition);
        }
        void				FrameResized(float newWidth, float newHeight) override {
            PYBIND11_OVERLOAD(void, BColorControl, FrameResized, newWidth, newHeight);
        }
        BHandler*			ResolveSpecifier(BMessage* message, int32 index, BMessage* specifier, int32 what, const char* property) override {
            PYBIND11_OVERLOAD(BHandler*, BColorControl, ResolveSpecifier, message, index, specifier, what, property);
        }
        status_t			GetSupportedSuites(BMessage* data) override {
            PYBIND11_OVERLOAD(status_t, BColorControl, GetSupportedSuites, data);
        }
        void				MakeFocus(bool focused = true) override {
            PYBIND11_OVERLOAD(void, BColorControl, MakeFocus, focused);
        }
        void				AllAttached() override {
            PYBIND11_OVERLOAD(void, BColorControl, AllAttached);
        }
        void				AllDetached() override {
            PYBIND11_OVERLOAD(void, BColorControl, AllDetached);
        }
        status_t			SetIcon(const BBitmap* icon, uint32 flags = 0) override {
            PYBIND11_OVERLOAD(status_t, BColorControl, SetIcon, icon, flags);
        }
};

PYBIND11_MODULE(ColorControl,m)
{
py::enum_<color_control_layout>(m, "color_control_layout", "")
.value("B_CELLS_4x64", color_control_layout::B_CELLS_4x64, "")
.value("B_CELLS_8x32", color_control_layout::B_CELLS_8x32, "")
.value("B_CELLS_16x16", color_control_layout::B_CELLS_16x16, "")
.value("B_CELLS_32x8", color_control_layout::B_CELLS_32x8, "")
.value("B_CELLS_64x4", color_control_layout::B_CELLS_64x4, "")
.export_values();

py::class_<BColorControl, PyBColorControl, BControl,std::unique_ptr<BColorControl, py::nodelete>>(m, "BColorControl")
.def(py::init<BPoint, color_control_layout, float, const char *, BMessage *, bool>(), "", py::arg("start"), py::arg("layout"), py::arg("cellSize"), py::arg("name"), py::arg("message")=NULL, py::arg("useOffscreen")=false)
.def(py::init<BMessage *>(), "", py::arg("data"))
.def_static("Instantiate", &BColorControl::Instantiate, "", py::arg("data"))
.def("Archive", &BColorControl::Archive, "", py::arg("data"), py::arg("deep")=true)
.def("SetLayout", py::overload_cast<BLayout *>(&BColorControl::SetLayout), "", py::arg("layout"))
.def("SetValue", py::overload_cast<int32>(&BColorControl::SetValue), "", py::arg("color_value"))
.def("SetValue", py::overload_cast<rgb_color>(&BColorControl::SetValue), "", py::arg("color"))
.def("ValueAsColor", &BColorControl::ValueAsColor, "")
.def("SetEnabled", &BColorControl::SetEnabled, "", py::arg("state"))
.def("AttachedToWindow", &BColorControl::AttachedToWindow, "")
.def("MessageReceived", &BColorControl::MessageReceived, "", py::arg("message"))
.def("Draw", &BColorControl::Draw, "", py::arg("updateRect"))
.def("MouseDown", &BColorControl::MouseDown, "", py::arg("where"))
.def("KeyDown", &BColorControl::KeyDown, "", py::arg("bytes"), py::arg("numBytes"))
.def("SetCellSize", &BColorControl::SetCellSize, "", py::arg("size"))
.def("CellSize", &BColorControl::CellSize, "")
.def("SetLayout", py::overload_cast<color_control_layout>(&BColorControl::SetLayout), "", py::arg("layout"))
.def("Layout", &BColorControl::Layout, "")
.def("WindowActivated", &BColorControl::WindowActivated, "", py::arg("state"))
.def("MouseUp", &BColorControl::MouseUp, "", py::arg("point"))
.def("MouseMoved", &BColorControl::MouseMoved, "", py::arg("point"), py::arg("code"), py::arg("dragMessage"))
.def("DetachedFromWindow", &BColorControl::DetachedFromWindow, "")
.def("GetPreferredSize", &BColorControl::GetPreferredSize, "", py::arg("_width"), py::arg("_height"))
.def("ResizeToPreferred", &BColorControl::ResizeToPreferred, "")
.def("Invoke", &BColorControl::Invoke, "", py::arg("message")=NULL)
.def("FrameMoved", &BColorControl::FrameMoved, "", py::arg("newPosition"))
.def("FrameResized", &BColorControl::FrameResized, "", py::arg("newWidth"), py::arg("newHeight"))
.def("ResolveSpecifier", &BColorControl::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("what"), py::arg("property"))
.def("GetSupportedSuites", &BColorControl::GetSupportedSuites, "", py::arg("data"))
.def("MakeFocus", &BColorControl::MakeFocus, "", py::arg("focused")=true)
.def("AllAttached", &BColorControl::AllAttached, "")
.def("AllDetached", &BColorControl::AllDetached, "")
.def("SetIcon", &BColorControl::SetIcon, "", py::arg("icon"), py::arg("flags")=0)
;


}
