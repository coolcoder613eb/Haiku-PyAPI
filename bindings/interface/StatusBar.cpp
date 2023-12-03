#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/StatusBar.h>
#include <String.h>
#include <View.h>

namespace py = pybind11;

class PyBStatusBar : public BStatusBar{
	public:
        using BStatusBar::BStatusBar;
        status_t		Archive(BMessage* archive, bool deep = true) const override {
        	PYBIND11_OVERLOAD(status_t, BStatusBar, Archive, archive, deep);
        }
        void				AttachedToWindow() override {
            PYBIND11_OVERLOAD(void, BStatusBar, AttachedToWindow);
        }
        void				DetachedFromWindow() override {
            PYBIND11_OVERLOAD(void, BStatusBar, DetachedFromWindow);
        }
        void				AllAttached() override {
            PYBIND11_OVERLOAD(void, BStatusBar, AllAttached);
        }
        void				AllDetached() override {
            PYBIND11_OVERLOAD(void, BStatusBar, AllDetached);
        }
        void				WindowActivated(bool state) override {
            PYBIND11_OVERLOAD(void, BStatusBar, WindowActivated, state);
        }
        void				MakeFocus(bool focus = true) override {
            PYBIND11_OVERLOAD(void, BStatusBar, MakeFocus, focus);
        }
        void			GetPreferredSize(float* _width, float* _height) override {
            PYBIND11_OVERLOAD(void, BStatusBar, GetPreferredSize, _width, _height);
        }
        BSize			MinSize() override {
            PYBIND11_OVERLOAD(BSize, BStatusBar, MinSize);
        }
        BSize			MaxSize() override {
            PYBIND11_OVERLOAD(BSize, BStatusBar, MaxSize);
        }
        BSize			PreferredSize() override {
            PYBIND11_OVERLOAD(BSize, BStatusBar, PreferredSize);
        }
        void				ResizeToPreferred() override {
            PYBIND11_OVERLOAD(void, BStatusBar, ResizeToPreferred);
        }
        void				FrameMoved(BPoint newPosition) override {
            PYBIND11_OVERLOAD(void, BStatusBar, FrameMoved, newPosition);
        }
        void				FrameResized(float newWidth, float newHeight) override {
            PYBIND11_OVERLOAD(void, BStatusBar, FrameResized, newWidth, newHeight);
        }
        void				Draw(BRect updateRect) override {
            PYBIND11_OVERLOAD(void, BStatusBar, Draw, updateRect);
        }
        void				MessageReceived(BMessage* message) override {
            PYBIND11_OVERLOAD(void, BStatusBar, MessageReceived, message);
        }
        void				MouseDown(BPoint where) override {
            PYBIND11_OVERLOAD(void, BStatusBar, MouseDown, where);
        }
        void				MouseUp(BPoint where) override {
            PYBIND11_OVERLOAD(void, BStatusBar, MouseUp, where);
        }
        void				MouseMoved(BPoint where, uint32 transit, const BMessage* dragMessage) override {
            PYBIND11_OVERLOAD(void, BStatusBar, MouseMoved, where, transit, dragMessage);
        }
        void				SetBarColor(rgb_color color) override {
            PYBIND11_OVERLOAD(void, BStatusBar, SetBarColor, color);
        }
        void				SetBarHeight(float height) override {
            PYBIND11_OVERLOAD(void, BStatusBar, SetBarHeight, height);
        }
        void				SetText(const char* string) override {
            PYBIND11_OVERLOAD(void, BStatusBar, SetText, string);
        }
        void				SetTrailingText(const char* string) override {
            PYBIND11_OVERLOAD(void, BStatusBar, SetTrailingText, string);
        }
        void				SetMaxValue(float max) override {
            PYBIND11_OVERLOAD(void, BStatusBar, SetMaxValue, max);
        }
        void				Update(float delta, const char* text = NULL, const char* trailingText = NULL) override {
            PYBIND11_OVERLOAD(void, BStatusBar, Update, delta, text, trailingText);
        }
        void				Reset(const char* label = NULL, const char* trailingLabel = NULL) override {
            PYBIND11_OVERLOAD(void, BStatusBar, Reset, label, trailingLabel);
        }
        void				SetTo(float value, const char* text = NULL, const char* trailingText = NULL) override {
            PYBIND11_OVERLOAD(void, BStatusBar, SetTo, value, text, trailingText);
        }
        BHandler*			ResolveSpecifier(BMessage* message, int32 index, BMessage* specifier, int32 what, const char* property) override {
            PYBIND11_OVERLOAD(BHandler*, BStatusBar, ResolveSpecifier, message, index, specifier, what, property);
        }
        status_t			GetSupportedSuites(BMessage* data) override {
            PYBIND11_OVERLOAD(status_t, BStatusBar, GetSupportedSuites, data);
        }
        status_t		Perform(perform_code code, void* data) override {
            PYBIND11_OVERLOAD(status_t, BStatusBar, Perform, code, data);
        }
};

PYBIND11_MODULE(StatusBar,m)
{
py::class_<BStatusBar, PyBStatusBar, BView, std::unique_ptr<BStatusBar, py::nodelete>>(m, "BStatusBar")
.def(py::init<BRect, const char *, const char *, const char *>(), "", py::arg("frame"), py::arg("name"), py::arg("label")=NULL, py::arg("trailingLabel")=NULL)
.def(py::init<const char *, const char *, const char *>(), "", py::arg("name"), py::arg("label")=NULL, py::arg("trailingLabel")=NULL)
.def(py::init<BMessage *>(), "", py::arg("archive"))
.def_static("Instantiate", &BStatusBar::Instantiate, "", py::arg("archive"))
.def("Archive", &BStatusBar::Archive, "", py::arg("archive"), py::arg("deep")=true)
.def("AttachedToWindow", &BStatusBar::AttachedToWindow, "")
.def("DetachedFromWindow", &BStatusBar::DetachedFromWindow, "")
.def("AllAttached", &BStatusBar::AllAttached, "")
.def("AllDetached", &BStatusBar::AllDetached, "")
.def("WindowActivated", &BStatusBar::WindowActivated, "", py::arg("state"))
.def("MakeFocus", &BStatusBar::MakeFocus, "", py::arg("focus")=true)
.def("GetPreferredSize", &BStatusBar::GetPreferredSize, "", py::arg("_width"), py::arg("_height"))
.def("MinSize", &BStatusBar::MinSize, "")
.def("MaxSize", &BStatusBar::MaxSize, "")
.def("PreferredSize", &BStatusBar::PreferredSize, "")
.def("ResizeToPreferred", &BStatusBar::ResizeToPreferred, "")
.def("FrameMoved", &BStatusBar::FrameMoved, "", py::arg("newPosition"))
.def("FrameResized", &BStatusBar::FrameResized, "", py::arg("newWidth"), py::arg("newHeight"))
.def("Draw", &BStatusBar::Draw, "", py::arg("updateRect"))
.def("MessageReceived", &BStatusBar::MessageReceived, "", py::arg("message"))
.def("MouseDown", &BStatusBar::MouseDown, "", py::arg("where"))
.def("MouseUp", &BStatusBar::MouseUp, "", py::arg("where"))
.def("MouseMoved", &BStatusBar::MouseMoved, "", py::arg("where"), py::arg("transit"), py::arg("dragMessage"))
.def("SetBarColor", &BStatusBar::SetBarColor, "", py::arg("color"))
.def("SetBarHeight", &BStatusBar::SetBarHeight, "", py::arg("height"))
.def("SetText", &BStatusBar::SetText, "", py::arg("string"))
.def("SetTrailingText", &BStatusBar::SetTrailingText, "", py::arg("string"))
.def("SetMaxValue", &BStatusBar::SetMaxValue, "", py::arg("max"))
.def("Update", &BStatusBar::Update, "", py::arg("delta"), py::arg("text")=NULL, py::arg("trailingText")=NULL)
.def("Reset", &BStatusBar::Reset, "", py::arg("label")=NULL, py::arg("trailingLabel")=NULL)
.def("SetTo", &BStatusBar::SetTo, "", py::arg("value"), py::arg("text")=NULL, py::arg("trailingText")=NULL)
.def("CurrentValue", &BStatusBar::CurrentValue, "")
.def("MaxValue", &BStatusBar::MaxValue, "")
.def("BarColor", &BStatusBar::BarColor, "")
.def("BarHeight", &BStatusBar::BarHeight, "")
.def("Text", &BStatusBar::Text, "")
.def("TrailingText", &BStatusBar::TrailingText, "")
.def("Label", &BStatusBar::Label, "")
.def("TrailingLabel", &BStatusBar::TrailingLabel, "")
.def("ResolveSpecifier", &BStatusBar::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("what"), py::arg("property"))
.def("GetSupportedSuites", &BStatusBar::GetSupportedSuites, "", py::arg("data"))
.def("Perform", &BStatusBar::Perform, "", py::arg("d"), py::arg("arg"))
;


}
