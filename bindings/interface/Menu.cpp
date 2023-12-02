#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/Menu.h>
#include <InterfaceDefs.h>
#include <List.h>
#include <View.h>
#include <MenuItem.h>

namespace py = pybind11;
using namespace BPrivate;

class PyBMenu : public BMenu{
	public:
        using BMenu::BMenu;
        status_t	Archive(BMessage* archive, bool deep = true) const override {
        	PYBIND11_OVERLOAD(status_t, BMenu, Archive, archive, deep);
        }
        void				AttachedToWindow() override {
            PYBIND11_OVERLOAD(void, BMenu, AttachedToWindow);
        }
        void				DetachedFromWindow() override {
            PYBIND11_OVERLOAD(void, BMenu, DetachedFromWindow);
        }
        void				AllAttached() override {
            PYBIND11_OVERLOAD(void, BMenu, AllAttached);
        }
        void				AllDetached() override {
            PYBIND11_OVERLOAD(void, BMenu, AllDetached);
        }
        void 		Draw(BRect updateRect) override {
            PYBIND11_OVERLOAD(void, BMenu, Draw, updateRect);
        }
        void				MessageReceived(BMessage* message) override {
            PYBIND11_OVERLOAD(void, BMenu, MessageReceived, message);
        }
        void				KeyDown(const char* bytes, int32 numBytes) override {
            PYBIND11_OVERLOAD(void, BMenu, KeyDown, bytes, numBytes);
        }
        BSize				MinSize() override {
            PYBIND11_OVERLOAD(BSize, BMenu, MinSize);
        }
        BSize				MaxSize() override {
            PYBIND11_OVERLOAD(BSize, BMenu, MaxSize);
        }
        BSize				PreferredSize() override {
            PYBIND11_OVERLOAD(BSize, BMenu, PreferredSize);
        }
        void				GetPreferredSize(float* _width, float* _height) override {
            PYBIND11_OVERLOAD(void, BMenu, GetPreferredSize, _width, _height);
        }
        void				ResizeToPreferred() override {
            PYBIND11_OVERLOAD(void, BMenu, ResizeToPreferred);
        }
        void				DoLayout() override {
            PYBIND11_OVERLOAD(void, BMenu, DoLayout);
        }
        void				FrameMoved(BPoint where) override {
            PYBIND11_OVERLOAD(void, BMenu, FrameMoved, where);
        }
        void				FrameResized(float width, float height) override {
            PYBIND11_OVERLOAD(void, BMenu, FrameResized, width, height);
        }
        void				MakeFocus(bool focus = true) override {
            PYBIND11_OVERLOAD(void, BMenu, MakeFocus, focus);
        }
        status_t			SetTargetForItems(BHandler* target) override {
            PYBIND11_OVERLOAD(status_t, BMenu, SetTargetForItems, target);
        }
        status_t			SetTargetForItems(BMessenger messenger) override {
            PYBIND11_OVERLOAD(status_t, BMenu, SetTargetForItems, messenger);
        }
        void				SetEnabled(bool enable) override {
            PYBIND11_OVERLOAD(void, BMenu, SetEnabled, enable);
        }
        void				SetRadioMode(bool on) override {
            PYBIND11_OVERLOAD(void, BMenu, SetRadioMode, on);
        }
        void				SetTriggersEnabled(bool enable) override {
            PYBIND11_OVERLOAD(void, BMenu, SetTriggersEnabled, enable);
        }
        void				SetMaxContentWidth(float maxWidth) override {
            PYBIND11_OVERLOAD(void, BMenu, SetMaxContentWidth, maxWidth);
        }
        BHandler*			ResolveSpecifier(BMessage* message, int32 index, BMessage* specifier, int32 what, const char* property) override {
            PYBIND11_OVERLOAD(BHandler*, BMenu, ResolveSpecifier, message, index, specifier, what, property);
        }
        status_t			GetSupportedSuites(BMessage* data) override {
            PYBIND11_OVERLOAD(status_t, BMenu, GetSupportedSuites, data);
        }
        status_t			Perform(perform_code d, void* arg) override {
            PYBIND11_OVERLOAD(status_t, BMenu, Perform, d, arg);
        }
};

PYBIND11_MODULE(Menu,m)
{
py::enum_<menu_layout>(m, "menu_layout", "")
.value("B_ITEMS_IN_ROW", menu_layout::B_ITEMS_IN_ROW, "")
.value("B_ITEMS_IN_COLUMN", menu_layout::B_ITEMS_IN_COLUMN, "")
.value("B_ITEMS_IN_MATRIX", menu_layout::B_ITEMS_IN_MATRIX, "")
.export_values();

//m.attr("BMenuWindow") = BMenuWindow;

//m.attr("ExtraMenuData") = ExtraMenuData;

//m.attr("TriggerList") = TriggerList;

//m.attr("MenuPrivate") = MenuPrivate;

py::class_<menu_info>(m, "menu_info")
.def_readwrite("font_size", &menu_info::font_size, "")
.def_readonly("f_family", &menu_info::f_family, "")
.def_readonly("f_style", &menu_info::f_style, "")
.def_readwrite("background_color", &menu_info::background_color, "")
.def_readwrite("separator", &menu_info::separator, "")
.def_readwrite("click_to_open", &menu_info::click_to_open, "")
.def_readwrite("triggers_always_shown", &menu_info::triggers_always_shown, "")
;

py::class_<BMenu, PyBMenu, BView, std::unique_ptr<BMenu, py::nodelete>>(m, "BMenu")
.def(py::init<const char *, menu_layout>(), "", py::arg("name"), py::arg("layout")=B_ITEMS_IN_COLUMN)
.def(py::init<const char *, float, float>(), "", py::arg("name"), py::arg("width"), py::arg("height"))
.def(py::init<BMessage *>(), "", py::arg("archive"))
.def_static("Instantiate", &BMenu::Instantiate, "", py::arg("archive"))
.def("Archive", &BMenu::Archive, "", py::arg("archive"), py::arg("deep")=true)
.def("AttachedToWindow", &BMenu::AttachedToWindow, "")
.def("DetachedFromWindow", &BMenu::DetachedFromWindow, "")
.def("AllAttached", &BMenu::AllAttached, "")
.def("AllDetached", &BMenu::AllDetached, "")
.def("Draw", &BMenu::Draw, "", py::arg("updateRect"))
.def("MessageReceived", &BMenu::MessageReceived, "", py::arg("message"))
.def("KeyDown", &BMenu::KeyDown, "", py::arg("bytes"), py::arg("numBytes"))
.def("MinSize", &BMenu::MinSize, "")
.def("MaxSize", &BMenu::MaxSize, "")
.def("PreferredSize", &BMenu::PreferredSize, "")
.def("GetPreferredSize", &BMenu::GetPreferredSize, "", py::arg("_width"), py::arg("_height"))
.def("ResizeToPreferred", &BMenu::ResizeToPreferred, "")
.def("DoLayout", &BMenu::DoLayout, "")
.def("FrameMoved", &BMenu::FrameMoved, "", py::arg("where"))
.def("FrameResized", &BMenu::FrameResized, "", py::arg("width"), py::arg("height"))
.def("InvalidateLayout", &BMenu::InvalidateLayout, "")
.def("MakeFocus", &BMenu::MakeFocus, "", py::arg("focus")=true)
.def("AddItem", py::overload_cast<BMenuItem *>(&BMenu::AddItem), "", py::arg("item"))
.def("AddItem", py::overload_cast<BMenuItem *, int32>(&BMenu::AddItem), "", py::arg("item"), py::arg("index"))
.def("AddItem", py::overload_cast<BMenuItem *, BRect>(&BMenu::AddItem), "", py::arg("item"), py::arg("frame"))
.def("AddItem", py::overload_cast<BMenu *>(&BMenu::AddItem), "", py::arg("menu"))
.def("AddItem", py::overload_cast<BMenu *, int32>(&BMenu::AddItem), "", py::arg("menu"), py::arg("index"))
.def("AddItem", py::overload_cast<BMenu *, BRect>(&BMenu::AddItem), "", py::arg("menu"), py::arg("frame"))
.def("AddList", &BMenu::AddList, "", py::arg("list"), py::arg("index"))
.def("AddSeparatorItem", &BMenu::AddSeparatorItem, "")
.def("RemoveItem", py::overload_cast<BMenuItem *>(&BMenu::RemoveItem), "", py::arg("item"))
.def("RemoveItem", py::overload_cast<int32>(&BMenu::RemoveItem), "", py::arg("index"))
.def("RemoveItems", &BMenu::RemoveItems, "", py::arg("index"), py::arg("count"), py::arg("deleteItems")=false)
.def("RemoveItem", py::overload_cast<BMenu *>(&BMenu::RemoveItem), "", py::arg("menu"))
.def("ItemAt", &BMenu::ItemAt, "", py::arg("index"))
.def("SubmenuAt", &BMenu::SubmenuAt, "", py::arg("index"))
.def("CountItems", &BMenu::CountItems, "")
.def("IndexOf", py::overload_cast<BMenuItem *>(&BMenu::IndexOf, py::const_), "", py::arg("item"))
.def("IndexOf", py::overload_cast<BMenu *>(&BMenu::IndexOf, py::const_), "", py::arg("menu"))
.def("FindItem", py::overload_cast<uint32>(&BMenu::FindItem, py::const_), "", py::arg("command"))
.def("FindItem", py::overload_cast<const char *>(&BMenu::FindItem, py::const_), "", py::arg("name"))
.def("SetTargetForItems", py::overload_cast<BHandler *>(&BMenu::SetTargetForItems), "", py::arg("target"))
.def("SetTargetForItems", py::overload_cast<BMessenger>(&BMenu::SetTargetForItems), "", py::arg("messenger"))
.def("SetEnabled", &BMenu::SetEnabled, "", py::arg("enable"))
.def("SetRadioMode", &BMenu::SetRadioMode, "", py::arg("on"))
.def("SetTriggersEnabled", &BMenu::SetTriggersEnabled, "", py::arg("enable"))
.def("SetMaxContentWidth", &BMenu::SetMaxContentWidth, "", py::arg("maxWidth"))
.def("SetLabelFromMarked", &BMenu::SetLabelFromMarked, "", py::arg("on"))
.def("IsLabelFromMarked", &BMenu::IsLabelFromMarked, "")
.def("IsEnabled", &BMenu::IsEnabled, "")
.def("IsRadioMode", &BMenu::IsRadioMode, "")
.def("AreTriggersEnabled", &BMenu::AreTriggersEnabled, "")
.def("IsRedrawAfterSticky", &BMenu::IsRedrawAfterSticky, "")
.def("MaxContentWidth", &BMenu::MaxContentWidth, "")
.def("FindMarked", &BMenu::FindMarked, "")
.def("FindMarkedIndex", &BMenu::FindMarkedIndex, "")
.def("Supermenu", &BMenu::Supermenu, "")
.def("Superitem", &BMenu::Superitem, "")
.def("ResolveSpecifier", &BMenu::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("form"), py::arg("property"))
.def("GetSupportedSuites", &BMenu::GetSupportedSuites, "", py::arg("data"))
.def("Perform", &BMenu::Perform, "", py::arg("d"), py::arg("arg"))
.def("AddDynamicItem", &BMenu::AddDynamicItem, "", py::arg("state"))
.def("DrawBackground", &BMenu::DrawBackground, "", py::arg("updateRect"))
.def("SetTrackingHook", &BMenu::SetTrackingHook, "", py::arg("hook"), py::arg("state"))
.def("SortItems", &BMenu::SortItems, "", py::arg(""))
.def("SwapItems", &BMenu::SwapItems, "", py::arg("indexA"), py::arg("indexB"))
.def("MoveItem", &BMenu::MoveItem, "", py::arg("indexFrom"), py::arg("indexTo"))
;

m.def("get_menu_info", &get_menu_info, "", py::arg("info"));

m.def("set_menu_info", &set_menu_info, "", py::arg("info"));

}
