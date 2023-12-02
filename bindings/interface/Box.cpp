#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/Box.h>
#include <View.h>

namespace py = pybind11;

class PyBBox : public BBox{
	public:
        using BBox::BBox;
        status_t	Archive(BMessage* archive, bool deep = true) const override {
        	PYBIND11_OVERLOAD(status_t, BBox, Archive, archive, deep);
        }
        void		SetBorder(border_style border) override {
        	PYBIND11_OVERLOAD(void, BBox, SetBorder, border);
        }
        void Draw(BRect updateRect) override {
            PYBIND11_OVERLOAD(void, BBox, Draw, updateRect);
        }
        void		AttachedToWindow() override {
        	PYBIND11_OVERLOAD(void, BBox, AttachedToWindow);
        }
        void		DetachedFromWindow() override {
        	PYBIND11_OVERLOAD(void, BBox, DetachedFromWindow);
        }
        void		AllAttached() override {
        	PYBIND11_OVERLOAD(void, BBox, AllAttached);
        }
        void		AllDetached() override {
        	PYBIND11_OVERLOAD(void, BBox, AllDetached);
        }
        void		FrameResized(float width, float height) override {
        	PYBIND11_OVERLOAD(void, BBox, FrameResized, width, height);
        }
        void		MessageReceived(BMessage* message) override {
        	PYBIND11_OVERLOAD(void, BBox, MessageReceived, message);
        }
        void		MouseDown(BPoint point) override {
        	PYBIND11_OVERLOAD(void, BBox, MouseDown, point);
        }
        void		MouseUp(BPoint point) override {
        	PYBIND11_OVERLOAD(void, BBox, MouseUp, point);
        }
        void		WindowActivated(bool active) override {
        	PYBIND11_OVERLOAD(void, BBox, WindowActivated, active);
        }
        void		MouseMoved(BPoint point, uint32 transit, const BMessage* dragMessage) override {
        	PYBIND11_OVERLOAD(void, BBox, MouseMoved, point, transit, dragMessage);
        }
        void		FrameMoved(BPoint newLocation) override {
        	PYBIND11_OVERLOAD(void, BBox, FrameMoved, newLocation);
        }
        BHandler*	ResolveSpecifier(BMessage* message, int32 index, BMessage* specifier, int32 what, const char* property) override {
        	PYBIND11_OVERLOAD(BHandler*, BBox, ResolveSpecifier, message, index, specifier, what, property);
        }
        void		ResizeToPreferred() override {
        	PYBIND11_OVERLOAD(void, BBox, ResizeToPreferred);
        }
        void		GetPreferredSize(float* _width, float* _height) override {
        	PYBIND11_OVERLOAD(void, BBox, GetPreferredSize, _width, _height);
        }
        void		MakeFocus(bool focused = true) override {
        	PYBIND11_OVERLOAD(void, BBox, MakeFocus, focused);
        }
        status_t	GetSupportedSuites(BMessage* message) override {
        	PYBIND11_OVERLOAD(status_t, BBox, GetSupportedSuites, message);
        }
        status_t	Perform(perform_code d, void* arg) override {
        	PYBIND11_OVERLOAD(status_t, BBox, Perform, d, arg);
        }
        BSize		MinSize() override {
        	PYBIND11_OVERLOAD(BSize, BBox, MinSize);
        }
        BSize		MaxSize() override {
        	PYBIND11_OVERLOAD(BSize, BBox, MaxSize);
        }
        BSize		PreferredSize() override {
        	PYBIND11_OVERLOAD(BSize, BBox, PreferredSize);
        }
        BAlignment	LayoutAlignment() override {
        	PYBIND11_OVERLOAD(BAlignment, BBox, LayoutAlignment);
        }
};


PYBIND11_MODULE(Box,m)
{
py::class_<BBox,PyBBox, BView, std::unique_ptr<BBox, py::nodelete>>(m, "BBox")
.def(py::init<BRect, const char *, unsigned int, unsigned int, border_style>(), "", py::arg("frame"), py::arg("name")=NULL, py::arg("resizingMode")=B_FOLLOW_LEFT_TOP, py::arg("flags")=B_WILL_DRAW | B_FRAME_EVENTS | B_NAVIGABLE_JUMP, py::arg("border")=B_FANCY_BORDER)
.def(py::init<const char *, unsigned int, border_style, BView *>(), "", py::arg("name"), py::arg("flags")=B_WILL_DRAW | B_FRAME_EVENTS | B_NAVIGABLE_JUMP, py::arg("border")=B_FANCY_BORDER, py::arg("child")=NULL)
.def(py::init<border_style, BView *>(), "", py::arg("border"), py::arg("child"))
.def(py::init<BMessage *>(), "", py::arg("archive"))
.def_static("Instantiate", &BBox::Instantiate, "", py::arg("archive"))
.def("Archive", &BBox::Archive, "", py::arg("archive"), py::arg("deep")=true)
.def("SetBorder", &BBox::SetBorder, "", py::arg("border"))
.def("Border", &BBox::Border, "")
.def("TopBorderOffset", &BBox::TopBorderOffset, "")
.def("InnerFrame", &BBox::InnerFrame, "")
.def("SetLabel", py::overload_cast<const char *>(&BBox::SetLabel), "", py::arg("string"))
.def("SetLabel", py::overload_cast<BView *>(&BBox::SetLabel), "", py::arg("viewLabel"))
.def("Label", &BBox::Label, "")
.def("LabelView", &BBox::LabelView, "")
.def("Draw", &BBox::Draw, "", py::arg("updateRect"))
.def("AttachedToWindow", &BBox::AttachedToWindow, "")
.def("DetachedFromWindow", &BBox::DetachedFromWindow, "")
.def("AllAttached", &BBox::AllAttached, "")
.def("AllDetached", &BBox::AllDetached, "")
.def("FrameResized", &BBox::FrameResized, "", py::arg("width"), py::arg("height"))
.def("MessageReceived", &BBox::MessageReceived, "", py::arg("message"))
.def("MouseDown", &BBox::MouseDown, "", py::arg("point"))
.def("MouseUp", &BBox::MouseUp, "", py::arg("point"))
.def("WindowActivated", &BBox::WindowActivated, "", py::arg("active"))
.def("MouseMoved", &BBox::MouseMoved, "", py::arg("point"), py::arg("transit"), py::arg("dragMessage"))
.def("FrameMoved", &BBox::FrameMoved, "", py::arg("newLocation"))
.def("ResolveSpecifier", &BBox::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("what"), py::arg("property"))
.def("ResizeToPreferred", &BBox::ResizeToPreferred, "")
.def("GetPreferredSize", &BBox::GetPreferredSize, "", py::arg("_width"), py::arg("_height"))
.def("MakeFocus", &BBox::MakeFocus, "", py::arg("focused")=true)
.def("GetSupportedSuites", &BBox::GetSupportedSuites, "", py::arg("message"))
.def("Perform", &BBox::Perform, "", py::arg("d"), py::arg("arg"))
.def("MinSize", &BBox::MinSize, "")
.def("MaxSize", &BBox::MaxSize, "")
.def("PreferredSize", &BBox::PreferredSize, "")
.def("LayoutAlignment", &BBox::LayoutAlignment, "")
;


}
