#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/Dragger.h>
#include <Locker.h>
#include <List.h>
#include <View.h>
#include <PopUpMenu.h>
#include <Bitmap.h>

namespace py = pybind11;
using namespace BPrivate;

class PyBDragger : public BDragger {
public:
    using BDragger::BDragger;

    status_t			Archive(BMessage* data, bool deep = true) const override {
        PYBIND11_OVERRIDE_PURE(status_t, BDragger, Archive, data, deep);
    }
    void				AttachedToWindow() override {
        PYBIND11_OVERRIDE_PURE(void, BDragger, AttachedToWindow);
    }
    void				DetachedFromWindow() override {
        PYBIND11_OVERRIDE_PURE(void, BDragger, DetachedFromWindow);
    }
    void				Draw(BRect updateRect) override {
        PYBIND11_OVERRIDE_PURE(void, BDragger, Draw, updateRect);
    }
    void				MouseDown(BPoint where) override {
        PYBIND11_OVERRIDE_PURE(void, BDragger, MouseDown, where);
    }
    void				MouseUp(BPoint where) override {
        PYBIND11_OVERRIDE_PURE(void, BDragger, MouseUp, where);
    }
    void				MouseMoved(BPoint where, uint32 transit, const BMessage* dragMessage) override {
        PYBIND11_OVERRIDE_PURE(void, BDragger, MouseMoved, where, transit, dragMessage);
    }
    void				MessageReceived(BMessage* message) override {
        PYBIND11_OVERRIDE_PURE(void, BDragger, MessageReceived, message);
    }
    void				FrameMoved(BPoint newPosition) override {
        PYBIND11_OVERRIDE_PURE(void, BDragger, FrameMoved, newPosition);
    }
    void				FrameResized(float newWidth, float newHeight) override {
        PYBIND11_OVERRIDE_PURE(void, BDragger, FrameResized, newWidth, newHeight);
    }
    BHandler*			ResolveSpecifier(BMessage* message, int32 index, BMessage* specifier, int32 form, const char* property) override {
        PYBIND11_OVERRIDE_PURE(BHandler*, BDragger, ResolveSpecifier, message, index, specifier, form, property);
    }
    status_t			GetSupportedSuites(BMessage* data) override {
        PYBIND11_OVERRIDE_PURE(status_t, BDragger, GetSupportedSuites, data);
    }
    status_t			Perform(perform_code code, void* data) override {
        PYBIND11_OVERRIDE_PURE(status_t, BDragger, Perform, code, data);
    }
    void				ResizeToPreferred() override {
        PYBIND11_OVERRIDE_PURE(void, BDragger, ResizeToPreferred);
    }
    void				GetPreferredSize(float* _width, float* _height) override {
        PYBIND11_OVERRIDE_PURE(void, BDragger, GetPreferredSize, _width, _height);
    }
    void				MakeFocus(bool focus = true) override {
        PYBIND11_OVERRIDE_PURE(void, BDragger, MakeFocus, focus);
    }
    void				AllAttached() override {
        PYBIND11_OVERRIDE_PURE(void, BDragger, AllAttached);
    }
    void				AllDetached() override {
        PYBIND11_OVERRIDE_PURE(void, BDragger, AllDetached);
    }
    BBitmap*			DragBitmap(BPoint* offset, drawing_mode* mode) override {
        PYBIND11_OVERRIDE_PURE(BBitmap*, BDragger, DragBitmap, offset, mode);
    }
};

PYBIND11_MODULE(Dragger,m)
{
//m.attr("replicant_data") = replicant_data;

//m.attr("ShelfContainerViewFilter") = ShelfContainerViewFilter;

py::class_<BDragger, BView>(m, "BDragger")
.def(py::init<BRect, BView *, unsigned int, unsigned int>(), "", py::arg("frame"), py::arg("target"), py::arg("resizingMode")=B_FOLLOW_NONE, py::arg("flags")=B_WILL_DRAW)
.def(py::init<BView *, unsigned int>(), "", py::arg("target"), py::arg("flags")=B_WILL_DRAW)
.def(py::init<BMessage *>(), "", py::arg("data"))
.def_static("Instantiate", &BDragger::Instantiate, "", py::arg("data"))
.def("Archive", &BDragger::Archive, "", py::arg("data"), py::arg("deep")=true)
.def("AttachedToWindow", &BDragger::AttachedToWindow, "")
.def("DetachedFromWindow", &BDragger::DetachedFromWindow, "")
.def("Draw", &BDragger::Draw, "", py::arg("updateRect"))
.def("MouseDown", &BDragger::MouseDown, "", py::arg("where"))
.def("MouseUp", &BDragger::MouseUp, "", py::arg("where"))
.def("MouseMoved", &BDragger::MouseMoved, "", py::arg("where"), py::arg("transit"), py::arg("dragMessage"))
.def("MessageReceived", &BDragger::MessageReceived, "", py::arg("message"))
.def("FrameMoved", &BDragger::FrameMoved, "", py::arg("newPosition"))
.def("FrameResized", &BDragger::FrameResized, "", py::arg("newWidth"), py::arg("newHeight"))
.def_static("ShowAllDraggers", &BDragger::ShowAllDraggers, "")
.def_static("HideAllDraggers", &BDragger::HideAllDraggers, "")
.def_static("AreDraggersDrawn", &BDragger::AreDraggersDrawn, "")
.def("ResolveSpecifier", &BDragger::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("form"), py::arg("property"))
.def("GetSupportedSuites", &BDragger::GetSupportedSuites, "", py::arg("data"))
.def("Perform", &BDragger::Perform, "", py::arg("code"), py::arg("data"))
.def("ResizeToPreferred", &BDragger::ResizeToPreferred, "")
.def("GetPreferredSize", &BDragger::GetPreferredSize, "", py::arg("_width"), py::arg("_height"))
.def("MakeFocus", &BDragger::MakeFocus, "", py::arg("focus")=true)
.def("AllAttached", &BDragger::AllAttached, "")
.def("AllDetached", &BDragger::AllDetached, "")
.def("SetPopUp", &BDragger::SetPopUp, "", py::arg("contextMenu"))
.def("PopUp", &BDragger::PopUp, "")
.def("InShelf", &BDragger::InShelf, "")
.def("Target", &BDragger::Target, "")
.def("DragBitmap", &BDragger::DragBitmap, "", py::arg("offset"), py::arg("mode"))
//.def_readwrite("Private", &BDragger::Private, "")
;


}
