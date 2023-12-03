#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/ScrollView.h>
#include <ScrollBar.h>

namespace py = pybind11;

class PyBScrollView : public BScrollView{
	public:
        using BScrollView::BScrollView;
        status_t			Archive(BMessage* archive, bool deep = true) const override {
        	PYBIND11_OVERLOAD(status_t, BScrollView, Archive, archive, deep);
        }
        status_t			AllUnarchived(const BMessage* archive) override {
            PYBIND11_OVERLOAD(status_t, BScrollView, AllUnarchived, archive);
        }
        void				AllAttached() override {
            PYBIND11_OVERLOAD(void, BScrollView, AllAttached);
        }
        void				AllDetached() override {
            PYBIND11_OVERLOAD(void, BScrollView, AllDetached);
        }
        void				AttachedToWindow() override {
            PYBIND11_OVERLOAD(void, BScrollView, AttachedToWindow);
        }
        void				DetachedFromWindow() override {
            PYBIND11_OVERLOAD(void, BScrollView, DetachedFromWindow);
        }
        void				Draw(BRect updateRect) override {
            PYBIND11_OVERLOAD(void, BScrollView, Draw, updateRect);
        }
        void				FrameMoved(BPoint newPosition) override {
            PYBIND11_OVERLOAD(void, BScrollView, FrameMoved, newPosition);
        }
        void				FrameResized(float newWidth, float newHeight) override {
            PYBIND11_OVERLOAD(void, BScrollView, FrameResized, newWidth, newHeight);
        }
        void				MessageReceived(BMessage* message) override {
            PYBIND11_OVERLOAD(void, BScrollView, MessageReceived, message);
        }
        void				MouseDown(BPoint where) override {
            PYBIND11_OVERLOAD(void, BScrollView, MouseDown, where);
        }
        void				MouseMoved(BPoint where, uint32 code, const BMessage* dragMessage) override {
            PYBIND11_OVERLOAD(void, BScrollView, MouseMoved, where, code, dragMessage);
        }
        void				MouseUp(BPoint where) override {
            PYBIND11_OVERLOAD(void, BScrollView, MouseUp, where);
        }
        void				WindowActivated(bool active) override {
            PYBIND11_OVERLOAD(void, BScrollView, WindowActivated, active);
        }
        void				GetPreferredSize(float* _width, float* _height) override {
            PYBIND11_OVERLOAD(void, BScrollView, GetPreferredSize, _width, _height);
        }
        void				ResizeToPreferred() override {
            PYBIND11_OVERLOAD(void, BScrollView, ResizeToPreferred);
        }
        void				MakeFocus(bool focus = true) override {
            PYBIND11_OVERLOAD(void, BScrollView, MakeFocus, focus);
        }
        BSize				MinSize() override {
            PYBIND11_OVERLOAD(BSize, BScrollView, MinSize);
        }
        BSize				MaxSize() override {
            PYBIND11_OVERLOAD(BSize, BScrollView, MaxSize);
        }
        BSize				PreferredSize() override {
            PYBIND11_OVERLOAD(BSize, BScrollView, PreferredSize);
        }
        void				SetBorder(border_style border) override {
            PYBIND11_OVERLOAD(void, BScrollView, SetBorder, border);
        }
        status_t			SetBorderHighlighted(bool highlight) override {
            PYBIND11_OVERLOAD(status_t, BScrollView, SetBorderHighlighted, highlight);
        }
        BHandler*			ResolveSpecifier(BMessage* message, int32 index, BMessage* specifier, int32 what, const char* property) override {
            PYBIND11_OVERLOAD(BHandler*, BScrollView, ResolveSpecifier, message, index, specifier, what, property);
        }
        status_t			GetSupportedSuites(BMessage* message) override {
            PYBIND11_OVERLOAD(status_t, BScrollView, GetSupportedSuites, message);
        }
        status_t			Perform(perform_code d, void* arg) override {
            PYBIND11_OVERLOAD(status_t, BScrollView, Perform, d, arg);
        }
};


PYBIND11_MODULE(ScrollView,m)
{
py::class_<BScrollView, PyBScrollView, BView,std::unique_ptr<BScrollView, py::nodelete>>(m, "BScrollView")
.def(py::init<const char *, BView *, unsigned int, unsigned int, bool, bool, border_style>(), "", py::arg("name"), py::arg("target"), py::arg("resizingMode")=B_FOLLOW_LEFT_TOP, py::arg("flags")=0, py::arg("horizontal")=false, py::arg("vertical")=false, py::arg("border")=B_FANCY_BORDER)
.def(py::init<const char *, BView *, unsigned int, bool, bool, border_style>(), "", py::arg("name"), py::arg("target"), py::arg("flags"), py::arg("horizontal"), py::arg("vertical"), py::arg("border")=B_FANCY_BORDER)
.def(py::init<BMessage *>(), "", py::arg("archive"))
.def_static("Instantiate", &BScrollView::Instantiate, "", py::arg("archive"))
.def("Archive", &BScrollView::Archive, "", py::arg("archive"), py::arg("deep")=true)
.def("AllUnarchived", &BScrollView::AllUnarchived, "", py::arg("archive"))
.def("AllAttached", &BScrollView::AllAttached, "")
.def("AllDetached", &BScrollView::AllDetached, "")
.def("AttachedToWindow", &BScrollView::AttachedToWindow, "")
.def("DetachedFromWindow", &BScrollView::DetachedFromWindow, "")
.def("Draw", &BScrollView::Draw, "", py::arg("updateRect"))
.def("FrameMoved", &BScrollView::FrameMoved, "", py::arg("newPosition"))
.def("FrameResized", &BScrollView::FrameResized, "", py::arg("newWidth"), py::arg("newHeight"))
.def("MessageReceived", &BScrollView::MessageReceived, "", py::arg("message"))
.def("MouseDown", &BScrollView::MouseDown, "", py::arg("where"))
.def("MouseMoved", &BScrollView::MouseMoved, "", py::arg("where"), py::arg("code"), py::arg("dragMessage"))
.def("MouseUp", &BScrollView::MouseUp, "", py::arg("where"))
.def("WindowActivated", &BScrollView::WindowActivated, "", py::arg("active"))
.def("GetPreferredSize", &BScrollView::GetPreferredSize, "", py::arg("_width"), py::arg("_height"))
.def("ResizeToPreferred", &BScrollView::ResizeToPreferred, "")
.def("MakeFocus", &BScrollView::MakeFocus, "", py::arg("focus")=true)
.def("MinSize", &BScrollView::MinSize, "")
.def("MaxSize", &BScrollView::MaxSize, "")
.def("PreferredSize", &BScrollView::PreferredSize, "")
.def("ScrollBar", &BScrollView::ScrollBar, "", py::arg("direction"))
.def("SetBorder", &BScrollView::SetBorder, "", py::arg("border"))
.def("Border", &BScrollView::Border, "")
.def("SetBorders", &BScrollView::SetBorders, "", py::arg("borders"))
.def("Borders", &BScrollView::Borders, "")
.def("SetBorderHighlighted", &BScrollView::SetBorderHighlighted, "", py::arg("highlight"))
.def("IsBorderHighlighted", &BScrollView::IsBorderHighlighted, "")
.def("SetTarget", &BScrollView::SetTarget, "", py::arg("target"))
.def("Target", &BScrollView::Target, "")
.def("ResolveSpecifier", &BScrollView::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("what"), py::arg("property"))
.def("GetSupportedSuites", &BScrollView::GetSupportedSuites, "", py::arg("message"))
.def("Perform", &BScrollView::Perform, "", py::arg("d"), py::arg("arg"))
;


}
