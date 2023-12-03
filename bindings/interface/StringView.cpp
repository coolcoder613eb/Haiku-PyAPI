#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/StringView.h>
#include <View.h>

namespace py = pybind11;

class PyBStringView : public BStringView{
	public:
        using BStringView::BStringView;

        status_t			Archive(BMessage* archive, bool deep = true) const override {
        	PYBIND11_OVERLOAD(status_t, BStringView, Archive, archive, deep);
        }
        void				AttachedToWindow() override {
        	PYBIND11_OVERLOAD(void, BStringView, AttachedToWindow);
        }
        void				DetachedFromWindow() override {
        	PYBIND11_OVERLOAD(void, BStringView, DetachedFromWindow);
        }
        void				AllAttached() override {
        	PYBIND11_OVERLOAD(void, BStringView, AllAttached);
        }
        void				AllDetached() override {
        	PYBIND11_OVERLOAD(void, BStringView, AllDetached);
        }
        void				MakeFocus(bool focus = true) override {
        	PYBIND11_OVERLOAD(void, BStringView, MakeFocus, focus);
        }
        void				GetPreferredSize(float* _width, float* _height) override {
        	PYBIND11_OVERLOAD(void, BStringView, GetPreferredSize, _width, _height);
        }
        BSize				MinSize() override {
        	PYBIND11_OVERLOAD(BSize, BStringView, MinSize);
        }
        BSize				MaxSize() override {
        	PYBIND11_OVERLOAD(BSize, BStringView, MaxSize);
        }
        BSize				PreferredSize() override {
        	PYBIND11_OVERLOAD(BSize, BStringView, PreferredSize);
        }
        void				ResizeToPreferred() override {
        	PYBIND11_OVERLOAD(void, BStringView, ResizeToPreferred);
        }
        BAlignment			LayoutAlignment() override {
        	PYBIND11_OVERLOAD(BAlignment, BStringView, LayoutAlignment);
        }
        void				FrameMoved(BPoint newPosition) override {
        	PYBIND11_OVERLOAD(void, BStringView, FrameMoved, newPosition);
        }
        void				FrameResized(float newWidth, float newHeight) override {
        	PYBIND11_OVERLOAD(void, BStringView, FrameResized, newWidth, newHeight);
        }
        void				Draw(BRect bounds) override {
        	PYBIND11_OVERLOAD(void, BStringView, Draw, bounds);
        }
        void				MessageReceived(BMessage* message) override {
        	PYBIND11_OVERLOAD(void, BStringView, MessageReceived, message);
        }
        void				MouseDown(BPoint point) override {
        	PYBIND11_OVERLOAD(void, BStringView, MouseDown, point);
        }
        void				MouseUp(BPoint point) override {
        	PYBIND11_OVERLOAD(void, BStringView, MouseUp, point);
        }
        void				MouseMoved(BPoint point, uint32 transit, const BMessage* dragMessage) override {
        	PYBIND11_OVERLOAD(void, BStringView, MouseMoved, point, transit, dragMessage);
        }
        BHandler*			ResolveSpecifier(BMessage* message, int32 index, BMessage* specifier, int32 form, const char* property) override {
        	PYBIND11_OVERLOAD(BHandler*, BStringView, ResolveSpecifier, message, index, specifier, form, property);
        }
        status_t			GetSupportedSuites(BMessage* data) override {
        	PYBIND11_OVERLOAD(status_t, BStringView, GetSupportedSuites, data);
        }
        void				SetFont(const BFont* font, uint32 mask = B_FONT_ALL) override {
        	PYBIND11_OVERLOAD(void, BStringView, SetFont, font, mask);
        }
};

PYBIND11_MODULE(StringView,m)
{
py::class_<BStringView, PyBStringView, BView, std::unique_ptr<BStringView, py::nodelete>>(m, "BStringView")
.def(py::init<BRect, const char *, const char *, unsigned int, unsigned int>(), "", py::arg("frame"), py::arg("name"), py::arg("text"), py::arg("resizingMode")=B_FOLLOW_LEFT_TOP, py::arg("flags")=B_WILL_DRAW)
.def(py::init<const char *, const char *, unsigned int>(), "", py::arg("name"), py::arg("text"), py::arg("flags")=B_WILL_DRAW)
.def(py::init<BMessage *>(), "", py::arg("archive"))
.def_static("Instantiate", &BStringView::Instantiate, "", py::arg("archive"))
.def("Archive", &BStringView::Archive, "", py::arg("archive"), py::arg("deep")=true)
.def("SetText", &BStringView::SetText, "", py::arg("text"))
.def("Text", &BStringView::Text, "")
.def("SetAlignment", &BStringView::SetAlignment, "", py::arg("flag"))
.def("Alignment", &BStringView::Alignment, "")
.def("SetTruncation", &BStringView::SetTruncation, "", py::arg("truncationMode"))
.def("Truncation", &BStringView::Truncation, "")
.def("AttachedToWindow", &BStringView::AttachedToWindow, "")
.def("DetachedFromWindow", &BStringView::DetachedFromWindow, "")
.def("AllAttached", &BStringView::AllAttached, "")
.def("AllDetached", &BStringView::AllDetached, "")
.def("MakeFocus", &BStringView::MakeFocus, "", py::arg("focus")=true)
.def("GetPreferredSize", &BStringView::GetPreferredSize, "", py::arg("_width"), py::arg("_height"))
.def("MinSize", &BStringView::MinSize, "")
.def("MaxSize", &BStringView::MaxSize, "")
.def("PreferredSize", &BStringView::PreferredSize, "")
.def("ResizeToPreferred", &BStringView::ResizeToPreferred, "")
.def("LayoutAlignment", &BStringView::LayoutAlignment, "")
.def("FrameMoved", &BStringView::FrameMoved, "", py::arg("newPosition"))
.def("FrameResized", &BStringView::FrameResized, "", py::arg("newWidth"), py::arg("newHeight"))
.def("Draw", &BStringView::Draw, "", py::arg("bounds"))
.def("MessageReceived", &BStringView::MessageReceived, "", py::arg("message"))
.def("MouseDown", &BStringView::MouseDown, "", py::arg("point"))
.def("MouseUp", &BStringView::MouseUp, "", py::arg("point"))
.def("MouseMoved", &BStringView::MouseMoved, "", py::arg("point"), py::arg("transit"), py::arg("dragMessage"))
.def("ResolveSpecifier", &BStringView::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("form"), py::arg("property"))
.def("GetSupportedSuites", &BStringView::GetSupportedSuites, "", py::arg("data"))
.def("SetFont", &BStringView::SetFont, "", py::arg("font"), py::arg("mask")=py::int_(0x000001FF))
;


}
