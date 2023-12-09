#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/PopUpMenu.h>
#include <Menu.h>
#include <MenuItem.h>

namespace py = pybind11;

class PyBPopUpMenu : public BPopUpMenu{
	public:
        using BPopUpMenu::BPopUpMenu;
        status_t			Archive(BMessage* archive, bool deep = true) const override {
        	PYBIND11_OVERLOAD(status_t, BPopUpMenu, Archive, archive, deep);
        }
        void				MessageReceived(BMessage* message) override {
            PYBIND11_OVERLOAD(void, BPopUpMenu, MessageReceived, message);
        }
        void				MouseDown(BPoint where) override {
            PYBIND11_OVERLOAD(void, BPopUpMenu, MouseDown, where);
        }
        void				MouseUp(BPoint where) override {
            PYBIND11_OVERLOAD(void, BPopUpMenu, MouseUp, where);
        }
        void				MouseMoved(BPoint where, uint32 transit, const BMessage* dragMessage) override {
        	PYBIND11_OVERLOAD(void, BPopUpMenu, MouseMoved, where, transit, dragMessage);
        }
        void				AttachedToWindow() override {
            PYBIND11_OVERLOAD(void, BPopUpMenu, AttachedToWindow);
        }
        void				DetachedFromWindow() override {
            PYBIND11_OVERLOAD(void, BPopUpMenu, DetachedFromWindow);
        }
        void				FrameMoved(BPoint newPosition) override {
            PYBIND11_OVERLOAD(void, BPopUpMenu, FrameMoved, newPosition);
        }
        void				FrameResized(float newWidth, float newHeight) override {
            PYBIND11_OVERLOAD(void, BPopUpMenu, FrameResized, newWidth, newHeight);
        }
        BHandler*			ResolveSpecifier(BMessage* message, int32 index, BMessage* specifier, int32 form, const char* property) override {
            PYBIND11_OVERLOAD(BHandler*, BPopUpMenu, ResolveSpecifier, message, index, specifier, form, property);
        }
        status_t			GetSupportedSuites(BMessage* data) override {
            PYBIND11_OVERLOAD(status_t, BPopUpMenu, GetSupportedSuites, data);
        }
        status_t			Perform(perform_code code, void* _data) override {
            PYBIND11_OVERLOAD(status_t, BPopUpMenu, Perform, code, _data);
        }
        void				ResizeToPreferred() override {
            PYBIND11_OVERLOAD(void, BPopUpMenu, ResizeToPreferred);
        }
        void				GetPreferredSize(float* _width, float* _height) override {
            PYBIND11_OVERLOAD(void, BPopUpMenu, GetPreferredSize, _width, _height);
        }
        void				MakeFocus(bool state = true) override {
            PYBIND11_OVERLOAD(void, BPopUpMenu, MakeFocus, state);
        }
        void				AllAttached() override {
            PYBIND11_OVERLOAD(void, BPopUpMenu, AllAttached);
        }
        void				AllDetached() override {
            PYBIND11_OVERLOAD(void, BPopUpMenu, AllDetached);
        }
};

PYBIND11_MODULE(PopUpMenu,m)
{
py::class_<BPopUpMenu, PyBPopUpMenu, BMenu, std::unique_ptr<BPopUpMenu,py::nodelete>>(m, "BPopUpMenu")
.def(py::init<const char *, bool, bool, menu_layout>(), "", py::arg("name"), py::arg("radioMode")=true, py::arg("labelFromMarked")=true, py::arg("layout")=B_ITEMS_IN_COLUMN)
.def(py::init<BMessage *>(), "", py::arg("data"))
.def("Archive", &BPopUpMenu::Archive, "", py::arg("archive"), py::arg("deep")=true)
.def_static("Instantiate", &BPopUpMenu::Instantiate, "", py::arg("archive"))
.def("Go", py::overload_cast<BPoint, bool, bool, bool>(&BPopUpMenu::Go), "", py::arg("where"), py::arg("autoInvoke")=false, py::arg("keepOpen")=false, py::arg("async")=false)
.def("Go", py::overload_cast<BPoint, bool, bool, BRect, bool>(&BPopUpMenu::Go), "", py::arg("where"), py::arg("autoInvoke"), py::arg("keepOpen"), py::arg("openRect"), py::arg("async")=false)
.def("MessageReceived", &BPopUpMenu::MessageReceived, "", py::arg("message"))
.def("MouseDown", &BPopUpMenu::MouseDown, "", py::arg("where"))
.def("MouseUp", &BPopUpMenu::MouseUp, "", py::arg("where"))
.def("MouseMoved", &BPopUpMenu::MouseMoved, "", py::arg("where"), py::arg("transit"), py::arg("dragMessage"))
.def("AttachedToWindow", &BPopUpMenu::AttachedToWindow, "")
.def("DetachedFromWindow", &BPopUpMenu::DetachedFromWindow, "")
.def("FrameMoved", &BPopUpMenu::FrameMoved, "", py::arg("newPosition"))
.def("FrameResized", &BPopUpMenu::FrameResized, "", py::arg("newWidth"), py::arg("newHeight"))
.def("ResolveSpecifier", &BPopUpMenu::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("form"), py::arg("property"))
.def("GetSupportedSuites", &BPopUpMenu::GetSupportedSuites, "", py::arg("data"))
.def("Perform", &BPopUpMenu::Perform, "", py::arg("code"), py::arg("_data"))
.def("ResizeToPreferred", &BPopUpMenu::ResizeToPreferred, "")
.def("GetPreferredSize", &BPopUpMenu::GetPreferredSize, "", py::arg("_width"), py::arg("_height"))
.def("MakeFocus", &BPopUpMenu::MakeFocus, "", py::arg("state")=true)
.def("AllAttached", &BPopUpMenu::AllAttached, "")
.def("AllDetached", &BPopUpMenu::AllDetached, "")
.def("SetAsyncAutoDestruct", &BPopUpMenu::SetAsyncAutoDestruct, "", py::arg("on"))
.def("AsyncAutoDestruct", &BPopUpMenu::AsyncAutoDestruct, "")
;


}
