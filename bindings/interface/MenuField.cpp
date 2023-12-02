#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/MenuField.h>
#include <Menu.h>
#include <LayoutItem.h>
#include <MenuItem.h>
#include <MenuBar.h>

namespace py = pybind11;

class PyBMenuField : public BMenuField{
	public:
        using BMenuField::BMenuField;
        status_t			Archive(BMessage* archive, bool deep = true) const override {
        	PYBIND11_OVERLOAD(status_t, BMenuField, Archive, archive, deep);
        }
        void				Draw(BRect updateRect) override {
            PYBIND11_OVERLOAD(void, BMenuField, Draw, updateRect);
        }
        void				AttachedToWindow() override {
            PYBIND11_OVERLOAD(void, BMenuField, AttachedToWindow);
        }
        void				AllAttached() override {
            PYBIND11_OVERLOAD(void, BMenuField, AllAttached);
        }
        void				MouseDown(BPoint where) override {
            PYBIND11_OVERLOAD(void, BMenuField, MouseDown, where);
        }
        void				KeyDown(const char* bytes, int32 numBytes) override {
            PYBIND11_OVERLOAD(void, BMenuField, KeyDown, bytes, numBytes);
        }
        void				MakeFocus(bool focused) override {
            PYBIND11_OVERLOAD(void, BMenuField, MakeFocus, focused);
        }
        void				MessageReceived(BMessage* message) override {
            PYBIND11_OVERLOAD(void, BMenuField, MessageReceived, message);
        }
        void				WindowActivated(bool active) override {
            PYBIND11_OVERLOAD(void, BMenuField, WindowActivated, active);
        }
        void				MouseUp(BPoint where) override {
            PYBIND11_OVERLOAD(void, BMenuField, MouseUp, where);
        }
        void				MouseMoved(BPoint where, uint32 transit, const BMessage* dragMessage) override {
            PYBIND11_OVERLOAD(void, BMenuField, MouseMoved, where, transit, dragMessage);
        }
        void				DetachedFromWindow() override {
            PYBIND11_OVERLOAD(void, BMenuField, DetachedFromWindow);
        }
        void				AllDetached() override {
            PYBIND11_OVERLOAD(void, BMenuField, AllAttached);
        }
        void				FrameMoved(BPoint where) override {
            PYBIND11_OVERLOAD(void, BMenuField, FrameMoved, where);
        }
        void				FrameResized(float width, float height) override {
            PYBIND11_OVERLOAD(void, BMenuField, FrameResized, width, height);
        }
        void				SetLabel(const char* label) override {
            PYBIND11_OVERLOAD(void, BMenuField, SetLabel, label);
        }
        void				SetEnabled(bool on) override {
            PYBIND11_OVERLOAD(void, BMenuField, SetEnabled, on);
        }
        void				SetAlignment(alignment label) override {
            PYBIND11_OVERLOAD(void, BMenuField, SetAlignment, label);
        }
        void				SetDivider(float position) override {
            PYBIND11_OVERLOAD(void, BMenuField, SetDivider, position);
        }
        BHandler*			ResolveSpecifier(BMessage* message, int32 index, BMessage* specifier, int32 form, const char* property) override {
            PYBIND11_OVERLOAD(BHandler*, BMenuField, ResolveSpecifier, message, index, specifier, form, property);
        }
        status_t			GetSupportedSuites(BMessage* data) override {
            PYBIND11_OVERLOAD(status_t, BMenuField, GetSupportedSuites, data);
        }
        void				ResizeToPreferred() override {
            PYBIND11_OVERLOAD(void, BMenuField, ResizeToPreferred);
        }
        void				GetPreferredSize(float* width, float* height) override {
            PYBIND11_OVERLOAD(void, BMenuField, GetPreferredSize, width, height);
        }
        BSize				MinSize() override {
            PYBIND11_OVERLOAD(BSize, BMenuField, MinSize);
        }
        BSize				MaxSize() override {
            PYBIND11_OVERLOAD(BSize, BMenuField, MaxSize);
        }
        BSize				PreferredSize() override {
            PYBIND11_OVERLOAD(BSize, BMenuField, PreferredSize);
        }
        status_t			Perform(perform_code d, void* arg) override {
            PYBIND11_OVERLOAD(status_t, BMenuField, Perform, d, arg);
        }
};

PYBIND11_MODULE(MenuField,m)
{
py::class_<BMenuField, PyBMenuField, BView, std::unique_ptr<BMenuField,py::nodelete>>(m, "BMenuField")
.def(py::init<BRect, const char *, const char *, BMenu *, uint32, uint32>(), "", py::arg("frame"), py::arg("name"), py::arg("label"), py::arg("menu"), py::arg("resizingMode")=B_FOLLOW_LEFT_TOP, py::arg("flags")=B_WILL_DRAW | B_NAVIGABLE)
.def(py::init<BRect, const char *, const char *, BMenu *, bool, uint32, uint32>(), "", py::arg("frame"), py::arg("name"), py::arg("label"), py::arg("menu"), py::arg("fixed_size"), py::arg("resizingMode")=B_FOLLOW_LEFT_TOP, py::arg("flags")=B_WILL_DRAW | B_NAVIGABLE)
.def(py::init<const char *, const char *, BMenu *, uint32>(), "", py::arg("name"), py::arg("label"), py::arg("menu"), py::arg("flags")=B_WILL_DRAW | B_NAVIGABLE)
.def(py::init<const char *, BMenu *, uint32>(), "", py::arg("label"), py::arg("menu"), py::arg("flags")=B_WILL_DRAW | B_NAVIGABLE)
.def(py::init<BMessage *>(), "", py::arg("data"))
.def_static("Instantiate", &BMenuField::Instantiate, "", py::arg("archive"))
.def("Archive", &BMenuField::Archive, "", py::arg("archive"), py::arg("deep")=true)
.def("Draw", &BMenuField::Draw, "", py::arg("updateRect"))
.def("AttachedToWindow", &BMenuField::AttachedToWindow, "")
.def("AllAttached", &BMenuField::AllAttached, "")
.def("MouseDown", &BMenuField::MouseDown, "", py::arg("where"))
.def("KeyDown", &BMenuField::KeyDown, "", py::arg("bytes"), py::arg("numBytes"))
.def("MakeFocus", &BMenuField::MakeFocus, "", py::arg("focused"))
.def("MessageReceived", &BMenuField::MessageReceived, "", py::arg("message"))
.def("WindowActivated", &BMenuField::WindowActivated, "", py::arg("active"))
.def("MouseUp", &BMenuField::MouseUp, "", py::arg("where"))
.def("MouseMoved", &BMenuField::MouseMoved, "", py::arg("where"), py::arg("transit"), py::arg("dragMessage"))
.def("DetachedFromWindow", &BMenuField::DetachedFromWindow, "")
.def("AllDetached", &BMenuField::AllDetached, "")
.def("FrameMoved", &BMenuField::FrameMoved, "", py::arg("where"))
.def("FrameResized", &BMenuField::FrameResized, "", py::arg("width"), py::arg("height"))
.def("Menu", &BMenuField::Menu)
.def("MenuBar", &BMenuField::MenuBar, "")
.def("MenuItem", &BMenuField::MenuItem, "")
.def("SetLabel", &BMenuField::SetLabel, "", py::arg("label"))
.def("Label", &BMenuField::Label, "")
.def("SetEnabled", &BMenuField::SetEnabled, "", py::arg("on"))
.def("IsEnabled", &BMenuField::IsEnabled, "")
.def("SetAlignment", &BMenuField::SetAlignment, "", py::arg("label"))
.def("Alignment", &BMenuField::Alignment, "")
.def("SetDivider", &BMenuField::SetDivider, "", py::arg("position"))
.def("Divider", &BMenuField::Divider, "")
.def("ShowPopUpMarker", &BMenuField::ShowPopUpMarker, "")
.def("HidePopUpMarker", &BMenuField::HidePopUpMarker, "")
.def("ResolveSpecifier", &BMenuField::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("form"), py::arg("property"))
.def("GetSupportedSuites", &BMenuField::GetSupportedSuites, "", py::arg("data"))
.def("ResizeToPreferred", &BMenuField::ResizeToPreferred, "")
.def("GetPreferredSize", &BMenuField::GetPreferredSize, "", py::arg("width"), py::arg("height"))
.def("MinSize", &BMenuField::MinSize, "")
.def("MaxSize", &BMenuField::MaxSize, "")
.def("PreferredSize", &BMenuField::PreferredSize, "")
.def("CreateLabelLayoutItem", &BMenuField::CreateLabelLayoutItem, "")
.def("CreateMenuBarLayoutItem", &BMenuField::CreateMenuBarLayoutItem, "")
.def("Perform", &BMenuField::Perform, "", py::arg("d"), py::arg("arg"))
;


}
