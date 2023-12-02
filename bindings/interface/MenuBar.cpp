#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/MenuBar.h>
#include <InterfaceDefs.h>
#include <Menu.h>
#include <OS.h>

namespace py = pybind11;
class PyBMenuBar : public BMenuBar{
	public:
        using BMenuBar::BMenuBar;
        status_t	Archive(BMessage* archive, bool deep = true) const override {
        	PYBIND11_OVERLOAD(status_t, BMenuBar, Archive, archive, deep);
        }
        void				AttachedToWindow() override {
            PYBIND11_OVERLOAD(void, BMenuBar, AttachedToWindow);
        }
        void				DetachedFromWindow() override {
            PYBIND11_OVERLOAD(void, BMenuBar, DetachedFromWindow);
        }
        void				AllAttached() override {
            PYBIND11_OVERLOAD(void, BMenuBar, AllAttached);
        }
        void				AllDetached() override {
            PYBIND11_OVERLOAD(void, BMenuBar, AllDetached);
        }
        void				WindowActivated(bool state) override {
            PYBIND11_OVERLOAD(void, BMenuBar, WindowActivated, state);
        }
        void				MakeFocus(bool state = true) override {
            PYBIND11_OVERLOAD(void, BMenuBar, MakeFocus, state);
        }
        void				ResizeToPreferred() override {
            PYBIND11_OVERLOAD(void, BMenuBar, ResizeToPreferred);
        }
        void				GetPreferredSize(float* _width, float* _height) override {
            PYBIND11_OVERLOAD(void, BMenuBar, GetPreferredSize, _width, _height);
        }
        BSize				MinSize() override {
            PYBIND11_OVERLOAD(BSize, BMenuBar, MinSize);
        }
        BSize				MaxSize() override {
            PYBIND11_OVERLOAD(BSize, BMenuBar, MaxSize);
        }
        BSize				PreferredSize() override {
            PYBIND11_OVERLOAD(BSize, BMenuBar, PreferredSize);
        }
        void				FrameMoved(BPoint newPosition) override {
            PYBIND11_OVERLOAD(void, BMenuBar, FrameMoved, newPosition);
        }
        void				FrameResized(float newWidth, float newHeight) override {
            PYBIND11_OVERLOAD(void, BMenuBar, FrameResized, newWidth, newHeight);
        }
        void				Show() override {
            PYBIND11_OVERLOAD(void, BMenuBar, Show);
        }
        void				Hide() override {
            PYBIND11_OVERLOAD(void, BMenuBar, Hide);
        }
        void				Draw(BRect updateRect) override {
            PYBIND11_OVERLOAD(void, BMenuBar, Draw, updateRect);
        }
        void				MessageReceived(BMessage* message) override {
            PYBIND11_OVERLOAD(void, BMenuBar, MessageReceived, message);
        }
        void				MouseDown(BPoint where) override {
            PYBIND11_OVERLOAD(void, BMenuBar, MouseDown, where);
        }
        void				MouseUp(BPoint where) override {
            PYBIND11_OVERLOAD(void, BMenuBar, MouseUp, where);
        }
        BHandler*			ResolveSpecifier(BMessage* message, int32 index, BMessage* specifier, int32 form, const char* property) override {
            PYBIND11_OVERLOAD(BHandler*, BMenuBar, ResolveSpecifier, message, index, specifier, form, property);
        }
        status_t			GetSupportedSuites(BMessage* data) override {
            PYBIND11_OVERLOAD(status_t, BMenuBar, GetSupportedSuites, data);
        }
        void				SetBorder(menu_bar_border border) override {
            PYBIND11_OVERLOAD(void, BMenuBar, SetBorder, border);
        }
        status_t			Perform(perform_code code, void* data) override {
            PYBIND11_OVERLOAD(status_t, BMenuBar, Perform, code, data);
        }
};

PYBIND11_MODULE(MenuBar,m)
{
py::enum_<menu_bar_border>(m, "menu_bar_border", "")
.value("B_BORDER_FRAME", menu_bar_border::B_BORDER_FRAME, "")
.value("B_BORDER_CONTENTS", menu_bar_border::B_BORDER_CONTENTS, "")
.value("B_BORDER_EACH_ITEM", menu_bar_border::B_BORDER_EACH_ITEM, "")
.export_values();

py::class_<BMenuBar, PyBMenuBar, BMenu, std::unique_ptr<BMenuBar, py::nodelete>>(m, "BMenuBar")
.def(py::init<BRect, const char *, unsigned int, menu_layout, bool>(), "", py::arg("frame"), py::arg("name"), py::arg("resizingMode")=B_FOLLOW_LEFT_RIGHT | B_FOLLOW_TOP, py::arg("layout")=B_ITEMS_IN_ROW, py::arg("resizeToFit")=true)
.def(py::init<const char *, menu_layout, unsigned int>(), "", py::arg("name"), py::arg("layout")=B_ITEMS_IN_ROW, py::arg("flags")=B_WILL_DRAW | B_FRAME_EVENTS)
.def(py::init<BMessage *>(), "", py::arg("archive"))
.def_static("Instantiate", &BMenuBar::Instantiate, "", py::arg("archive"))
.def("Archive", &BMenuBar::Archive, "", py::arg("archive"), py::arg("deep")=true)
.def("AttachedToWindow", &BMenuBar::AttachedToWindow, "")
.def("DetachedFromWindow", &BMenuBar::DetachedFromWindow, "")
.def("AllAttached", &BMenuBar::AllAttached, "")
.def("AllDetached", &BMenuBar::AllDetached, "")
.def("WindowActivated", &BMenuBar::WindowActivated, "", py::arg("state"))
.def("MakeFocus", &BMenuBar::MakeFocus, "", py::arg("state")=true)
.def("ResizeToPreferred", &BMenuBar::ResizeToPreferred, "")
.def("GetPreferredSize", &BMenuBar::GetPreferredSize, "", py::arg("_width"), py::arg("_height"))
.def("MinSize", &BMenuBar::MinSize, "")
.def("MaxSize", &BMenuBar::MaxSize, "")
.def("PreferredSize", &BMenuBar::PreferredSize, "")
.def("FrameMoved", &BMenuBar::FrameMoved, "", py::arg("newPosition"))
.def("FrameResized", &BMenuBar::FrameResized, "", py::arg("newWidth"), py::arg("newHeight"))
.def("Show", &BMenuBar::Show, "")
.def("Hide", &BMenuBar::Hide, "")
.def("Draw", &BMenuBar::Draw, "", py::arg("updateRect"))
.def("MessageReceived", &BMenuBar::MessageReceived, "", py::arg("message"))
.def("MouseDown", &BMenuBar::MouseDown, "", py::arg("where"))
.def("MouseUp", &BMenuBar::MouseUp, "", py::arg("where"))
.def("ResolveSpecifier", &BMenuBar::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("form"), py::arg("property"))
.def("GetSupportedSuites", &BMenuBar::GetSupportedSuites, "", py::arg("data"))
.def("SetBorder", &BMenuBar::SetBorder, "", py::arg("border"))
.def("Border", &BMenuBar::Border, "")
.def("SetBorders", &BMenuBar::SetBorders, "", py::arg("borders"))
.def("Borders", &BMenuBar::Borders, "")
.def("Perform", &BMenuBar::Perform, "", py::arg("code"), py::arg("data"))
;


}
