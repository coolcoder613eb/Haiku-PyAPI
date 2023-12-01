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
        void Draw(BRect updateRect) override {
            PYBIND11_OVERLOAD(void, BBox, Draw, updateRect);
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
