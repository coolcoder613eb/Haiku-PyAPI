#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/ControlLook.h>
#include <Alignment.h>
#include <Font.h>
#include <Rect.h>
#include <Slider.h>

namespace py = pybind11;
using namespace BPrivate;

PYBIND11_MODULE(ControlLook,m)
{
m.attr("be_control_look") = be_control_look;

m.attr("BControlLook") = BControlLook;

m.attr("be_control_look") = be_control_look;

py::class_<BControlLook>(m, "BControlLook")
.def(py::init(), "")
.def("DefaultLabelAlignment", &BControlLook::DefaultLabelAlignment, "")
.def("DefaultLabelSpacing", &BControlLook::DefaultLabelSpacing, "")
.def("DefaultItemSpacing", &BControlLook::DefaultItemSpacing, "")
.def_static("ComposeSpacing", &BControlLook::ComposeSpacing, "", py::arg("spacing"))
.def_static("ComposeIconSize", &BControlLook::ComposeIconSize, "", py::arg("size"))
.def("Flags", &BControlLook::Flags, "", py::arg("control"))
.def("DrawButtonFrame", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,const rgb_color & background,unsigned int flags=0,unsigned int borders=B_ALL_BORDERS) {
    BRect  rect;
    self.DrawButtonFrame(view, rect, updateRect, base, background, flags, borders);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("background"), py::arg("flags")=0, py::arg("borders")=B_ALL_BORDERS)
.def("DrawButtonFrame", [](BControlLook& self,BView * view,const BRect & updateRect,float radius,const rgb_color & base,const rgb_color & background,unsigned int flags=0,unsigned int borders=B_ALL_BORDERS) {
    BRect  rect;
    self.DrawButtonFrame(view, rect, updateRect, radius, base, background, flags, borders);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("radius"), py::arg("base"), py::arg("background"), py::arg("flags")=0, py::arg("borders")=B_ALL_BORDERS)
.def("DrawButtonFrame", [](BControlLook& self,BView * view,const BRect & updateRect,float leftTopRadius,float rightTopRadius,float leftBottomRadius,float rightBottomRadius,const rgb_color & base,const rgb_color & background,unsigned int flags=0,unsigned int borders=B_ALL_BORDERS) {
    BRect  rect;
    self.DrawButtonFrame(view, rect, updateRect, leftTopRadius, rightTopRadius, leftBottomRadius, rightBottomRadius, base, background, flags, borders);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("leftTopRadius"), py::arg("rightTopRadius"), py::arg("leftBottomRadius"), py::arg("rightBottomRadius"), py::arg("base"), py::arg("background"), py::arg("flags")=0, py::arg("borders")=B_ALL_BORDERS)
.def("DrawButtonBackground", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,unsigned int flags=0,unsigned int borders=B_ALL_BORDERS,orientation orientation=B_HORIZONTAL) {
    BRect  rect;
    self.DrawButtonBackground(view, rect, updateRect, base, flags, borders, orientation);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags")=0, py::arg("borders")=B_ALL_BORDERS, py::arg("orientation")=B_HORIZONTAL)
.def("DrawButtonBackground", [](BControlLook& self,BView * view,const BRect & updateRect,float radius,const rgb_color & base,unsigned int flags=0,unsigned int borders=B_ALL_BORDERS,orientation orientation=B_HORIZONTAL) {
    BRect  rect;
    self.DrawButtonBackground(view, rect, updateRect, radius, base, flags, borders, orientation);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("radius"), py::arg("base"), py::arg("flags")=0, py::arg("borders")=B_ALL_BORDERS, py::arg("orientation")=B_HORIZONTAL)
.def("DrawButtonBackground", [](BControlLook& self,BView * view,const BRect & updateRect,float leftTopRadius,float rightTopRadius,float leftBottomRadius,float rightBottomRadius,const rgb_color & base,unsigned int flags=0,unsigned int borders=B_ALL_BORDERS,orientation orientation=B_HORIZONTAL) {
    BRect  rect;
    self.DrawButtonBackground(view, rect, updateRect, leftTopRadius, rightTopRadius, leftBottomRadius, rightBottomRadius, base, flags, borders, orientation);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("leftTopRadius"), py::arg("rightTopRadius"), py::arg("leftBottomRadius"), py::arg("rightBottomRadius"), py::arg("base"), py::arg("flags")=0, py::arg("borders")=B_ALL_BORDERS, py::arg("orientation")=B_HORIZONTAL)
.def("DrawMenuBarBackground", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,unsigned int flags=0,unsigned int borders=B_ALL_BORDERS) {
    BRect  rect;
    self.DrawMenuBarBackground(view, rect, updateRect, base, flags, borders);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags")=0, py::arg("borders")=B_ALL_BORDERS)
.def("DrawMenuFieldFrame", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,const rgb_color & background,unsigned int flags=0,unsigned int borders=B_ALL_BORDERS) {
    BRect  rect;
    self.DrawMenuFieldFrame(view, rect, updateRect, base, background, flags, borders);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("background"), py::arg("flags")=0, py::arg("borders")=B_ALL_BORDERS)
.def("DrawMenuFieldFrame", [](BControlLook& self,BView * view,const BRect & updateRect,float radius,const rgb_color & base,const rgb_color & background,unsigned int flags=0,unsigned int borders=B_ALL_BORDERS) {
    BRect  rect;
    self.DrawMenuFieldFrame(view, rect, updateRect, radius, base, background, flags, borders);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("radius"), py::arg("base"), py::arg("background"), py::arg("flags")=0, py::arg("borders")=B_ALL_BORDERS)
.def("DrawMenuFieldFrame", [](BControlLook& self,BView * view,const BRect & updateRect,float leftTopRadius,float rightTopRadius,float leftBottomRadius,float rightBottomRadius,const rgb_color & base,const rgb_color & background,unsigned int flags=0,unsigned int borders=B_ALL_BORDERS) {
    BRect  rect;
    self.DrawMenuFieldFrame(view, rect, updateRect, leftTopRadius, rightTopRadius, leftBottomRadius, rightBottomRadius, base, background, flags, borders);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("leftTopRadius"), py::arg("rightTopRadius"), py::arg("leftBottomRadius"), py::arg("rightBottomRadius"), py::arg("base"), py::arg("background"), py::arg("flags")=0, py::arg("borders")=B_ALL_BORDERS)
.def("DrawMenuFieldBackground", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,bool popupIndicator,unsigned int flags=0) {
    BRect  rect;
    self.DrawMenuFieldBackground(view, rect, updateRect, base, popupIndicator, flags);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("popupIndicator"), py::arg("flags")=0)
.def("DrawMenuFieldBackground", [](BControlLook& self,BView * view,const BRect & updateRect,float radius,const rgb_color & base,bool popupIndicator,unsigned int flags=0) {
    BRect  rect;
    self.DrawMenuFieldBackground(view, rect, updateRect, radius, base, popupIndicator, flags);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("radius"), py::arg("base"), py::arg("popupIndicator"), py::arg("flags")=0)
.def("DrawMenuFieldBackground", [](BControlLook& self,BView * view,const BRect & updateRect,float leftTopRadius,float rightTopRadius,float leftBottomRadius,float rightBottomRadius,const rgb_color & base,bool popupIndicator,unsigned int flags=0) {
    BRect  rect;
    self.DrawMenuFieldBackground(view, rect, updateRect, leftTopRadius, rightTopRadius, leftBottomRadius, rightBottomRadius, base, popupIndicator, flags);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("leftTopRadius"), py::arg("rightTopRadius"), py::arg("leftBottomRadius"), py::arg("rightBottomRadius"), py::arg("base"), py::arg("popupIndicator"), py::arg("flags")=0)
.def("DrawMenuFieldBackground", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,unsigned int flags=0,unsigned int borders=B_ALL_BORDERS) {
    BRect  rect;
    self.DrawMenuFieldBackground(view, rect, updateRect, base, flags, borders);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags")=0, py::arg("borders")=B_ALL_BORDERS)
.def("DrawMenuBackground", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,unsigned int flags=0,unsigned int borders=B_ALL_BORDERS) {
    BRect  rect;
    self.DrawMenuBackground(view, rect, updateRect, base, flags, borders);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags")=0, py::arg("borders")=B_ALL_BORDERS)
.def("DrawMenuItemBackground", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,unsigned int flags=0,unsigned int borders=B_ALL_BORDERS) {
    BRect  rect;
    self.DrawMenuItemBackground(view, rect, updateRect, base, flags, borders);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags")=0, py::arg("borders")=B_ALL_BORDERS)
.def("DrawStatusBar", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,const rgb_color & barColor,float progressPosition) {
    BRect  rect;
    self.DrawStatusBar(view, rect, updateRect, base, barColor, progressPosition);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("barColor"), py::arg("progressPosition"))
.def("DrawCheckBox", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,unsigned int flags=0) {
    BRect  rect;
    self.DrawCheckBox(view, rect, updateRect, base, flags);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags")=0)
.def("DrawRadioButton", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,unsigned int flags=0) {
    BRect  rect;
    self.DrawRadioButton(view, rect, updateRect, base, flags);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags")=0)
.def("DrawScrollBarBackground", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,unsigned int flags,orientation orientation) {
    BRect  rect1;
BRect  rect2;
    self.DrawScrollBarBackground(view, rect1, rect2, updateRect, base, flags, orientation);
    return std::make_tuple(rect1,rect2);
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags"), py::arg("orientation"))
.def("DrawScrollBarBackground", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,unsigned int flags,orientation orientation) {
    BRect  rect;
    self.DrawScrollBarBackground(view, rect, updateRect, base, flags, orientation);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags"), py::arg("orientation"))
.def("DrawScrollViewFrame", [](BControlLook& self,BView * view,const BRect & updateRect,BRect verticalScrollBarFrame,BRect horizontalScrollBarFrame,const rgb_color & base,border_style borderStyle,unsigned int flags=0,unsigned int borders=B_ALL_BORDERS) {
    BRect  rect;
    self.DrawScrollViewFrame(view, rect, updateRect, verticalScrollBarFrame, horizontalScrollBarFrame, base, borderStyle, flags, borders);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("verticalScrollBarFrame"), py::arg("horizontalScrollBarFrame"), py::arg("base"), py::arg("borderStyle"), py::arg("flags")=0, py::arg("borders")=B_ALL_BORDERS)
.def("DrawArrowShape", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,unsigned int direction,unsigned int flags=0,float tint=B_DARKEN_MAX_TINT) {
    BRect  rect;
    self.DrawArrowShape(view, rect, updateRect, base, direction, flags, tint);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("direction"), py::arg("flags")=0, py::arg("tint")=B_DARKEN_MAX_TINT)
.def("SliderBarColor", &BControlLook::SliderBarColor, "", py::arg("base"))
.def("DrawSliderBar", py::overload_cast<BView *, BRect, const BRect &, const rgb_color &, rgb_color, rgb_color, float, unsigned int, orientation>(&BControlLook::DrawSliderBar), "", py::arg("view"), py::arg("rect"), py::arg("updateRect"), py::arg("base"), py::arg("leftFillColor"), py::arg("rightFillColor"), py::arg("sliderScale"), py::arg("flags"), py::arg("orientation"))
.def("DrawSliderBar", py::overload_cast<BView *, BRect, const BRect &, const rgb_color &, rgb_color, unsigned int, orientation>(&BControlLook::DrawSliderBar), "", py::arg("view"), py::arg("rect"), py::arg("updateRect"), py::arg("base"), py::arg("fillColor"), py::arg("flags"), py::arg("orientation"))
.def("DrawSliderThumb", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,unsigned int flags,orientation orientation) {
    BRect  rect;
    self.DrawSliderThumb(view, rect, updateRect, base, flags, orientation);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags"), py::arg("orientation"))
.def("DrawSliderTriangle", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,unsigned int flags,orientation orientation) {
    BRect  rect;
    self.DrawSliderTriangle(view, rect, updateRect, base, flags, orientation);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags"), py::arg("orientation"))
.def("DrawSliderTriangle", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,const rgb_color & fill,unsigned int flags,orientation orientation) {
    BRect  rect;
    self.DrawSliderTriangle(view, rect, updateRect, base, fill, flags, orientation);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("fill"), py::arg("flags"), py::arg("orientation"))
.def("DrawSliderHashMarks", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,int count,hash_mark_location location,unsigned int flags,orientation orientation) {
    BRect  rect;
    self.DrawSliderHashMarks(view, rect, updateRect, base, count, location, flags, orientation);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("count"), py::arg("location"), py::arg("flags"), py::arg("orientation"))
.def("DrawActiveTab", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,unsigned int flags=0,unsigned int borders=B_ALL_BORDERS,unsigned int side=B_TOP_BORDER,int index=0,int selected=- 1,int first=0,int last=0) {
    BRect  rect;
    self.DrawActiveTab(view, rect, updateRect, base, flags, borders, side, index, selected, first, last);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags")=0, py::arg("borders")=B_ALL_BORDERS, py::arg("side")=B_TOP_BORDER, py::arg("index")=0, py::arg("selected")=- 1, py::arg("first")=0, py::arg("last")=0)
.def("DrawInactiveTab", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,unsigned int flags=0,unsigned int borders=B_ALL_BORDERS,unsigned int side=B_TOP_BORDER,int index=0,int selected=- 1,int first=0,int last=0) {
    BRect  rect;
    self.DrawInactiveTab(view, rect, updateRect, base, flags, borders, side, index, selected, first, last);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags")=0, py::arg("borders")=B_ALL_BORDERS, py::arg("side")=B_TOP_BORDER, py::arg("index")=0, py::arg("selected")=- 1, py::arg("first")=0, py::arg("last")=0)
.def("DrawSplitter", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,orientation orientation,unsigned int flags=0,unsigned int borders=B_ALL_BORDERS) {
    BRect  rect;
    self.DrawSplitter(view, rect, updateRect, base, orientation, flags, borders);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("orientation"), py::arg("flags")=0, py::arg("borders")=B_ALL_BORDERS)
.def("DrawBorder", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,border_style borderStyle,unsigned int flags=0,unsigned int borders=B_ALL_BORDERS) {
    BRect  rect;
    self.DrawBorder(view, rect, updateRect, base, borderStyle, flags, borders);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("borderStyle"), py::arg("flags")=0, py::arg("borders")=B_ALL_BORDERS)
.def("DrawRaisedBorder", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,unsigned int flags=0,unsigned int borders=B_ALL_BORDERS) {
    BRect  rect;
    self.DrawRaisedBorder(view, rect, updateRect, base, flags, borders);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags")=0, py::arg("borders")=B_ALL_BORDERS)
.def("DrawGroupFrame", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,unsigned int borders=B_ALL_BORDERS) {
    BRect  rect;
    self.DrawGroupFrame(view, rect, updateRect, base, borders);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("borders")=B_ALL_BORDERS)
.def("DrawTextControlBorder", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,unsigned int flags=0,unsigned int borders=B_ALL_BORDERS) {
    BRect  rect;
    self.DrawTextControlBorder(view, rect, updateRect, base, flags, borders);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags")=0, py::arg("borders")=B_ALL_BORDERS)
.def("DrawLabel", py::overload_cast<BView *, const char *, BRect, const BRect &, const rgb_color &, unsigned int, const rgb_color *>(&BControlLook::DrawLabel), "", py::arg("view"), py::arg("label"), py::arg("rect"), py::arg("updateRect"), py::arg("base"), py::arg("flags"), py::arg("textColor")=NULL)
.def("DrawLabel", py::overload_cast<BView *, const char *, BRect, const BRect &, const rgb_color &, unsigned int, const BAlignment &, const rgb_color *>(&BControlLook::DrawLabel), "", py::arg("view"), py::arg("label"), py::arg("rect"), py::arg("updateRect"), py::arg("base"), py::arg("flags"), py::arg("alignment"), py::arg("textColor")=NULL)
.def("DrawLabel", py::overload_cast<BView *, const char *, const rgb_color &, unsigned int, const BPoint &, const rgb_color *>(&BControlLook::DrawLabel), "", py::arg("view"), py::arg("label"), py::arg("base"), py::arg("flags"), py::arg("where"), py::arg("textColor")=NULL)
.def("DrawLabel", py::overload_cast<BView *, const char *, const BBitmap *, BRect, const BRect &, const rgb_color &, unsigned int, const rgb_color *>(&BControlLook::DrawLabel), "", py::arg("view"), py::arg("label"), py::arg("icon"), py::arg("rect"), py::arg("updateRect"), py::arg("base"), py::arg("flags"), py::arg("textColor")=NULL)
.def("DrawLabel", py::overload_cast<BView *, const char *, const BBitmap *, BRect, const BRect &, const rgb_color &, unsigned int, const BAlignment &, const rgb_color *>(&BControlLook::DrawLabel), "", py::arg("view"), py::arg("label"), py::arg("icon"), py::arg("rect"), py::arg("updateRect"), py::arg("base"), py::arg("flags"), py::arg("alignment"), py::arg("textColor")=NULL)
.def("GetFrameInsets", [](BControlLook& self,frame_type frameType,unsigned int flags) {
    float  _left;
float  _top;
float  _right;
float  _bottom;
    self.GetFrameInsets(frameType, flags, _left, _top, _right, _bottom);
    return std::make_tuple(_left,_top,_right,_bottom);
}
, "", py::arg("frameType"), py::arg("flags"))
.def("GetBackgroundInsets", [](BControlLook& self,background_type backgroundType,unsigned int flags) {
    float  _left;
float  _top;
float  _right;
float  _bottom;
    self.GetBackgroundInsets(backgroundType, flags, _left, _top, _right, _bottom);
    return std::make_tuple(_left,_top,_right,_bottom);
}
, "", py::arg("backgroundType"), py::arg("flags"))
.def("GetInsets", [](BControlLook& self,frame_type frameType,background_type backgroundType,unsigned int flags) {
    float  _left;
float  _top;
float  _right;
float  _bottom;
    self.GetInsets(frameType, backgroundType, flags, _left, _top, _right, _bottom);
    return std::make_tuple(_left,_top,_right,_bottom);
}
, "", py::arg("frameType"), py::arg("backgroundType"), py::arg("flags"))
.def("DrawButtonWithPopUpBackground", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,unsigned int flags=0,unsigned int borders=B_ALL_BORDERS,orientation orientation=B_HORIZONTAL) {
    BRect  rect;
    self.DrawButtonWithPopUpBackground(view, rect, updateRect, base, flags, borders, orientation);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags")=0, py::arg("borders")=B_ALL_BORDERS, py::arg("orientation")=B_HORIZONTAL)
.def("DrawButtonWithPopUpBackground", [](BControlLook& self,BView * view,const BRect & updateRect,float radius,const rgb_color & base,unsigned int flags=0,unsigned int borders=B_ALL_BORDERS,orientation orientation=B_HORIZONTAL) {
    BRect  rect;
    self.DrawButtonWithPopUpBackground(view, rect, updateRect, radius, base, flags, borders, orientation);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("radius"), py::arg("base"), py::arg("flags")=0, py::arg("borders")=B_ALL_BORDERS, py::arg("orientation")=B_HORIZONTAL)
.def("DrawButtonWithPopUpBackground", [](BControlLook& self,BView * view,const BRect & updateRect,float leftTopRadius,float rightTopRadius,float leftBottomRadius,float rightBottomRadius,const rgb_color & base,unsigned int flags=0,unsigned int borders=B_ALL_BORDERS,orientation orientation=B_HORIZONTAL) {
    BRect  rect;
    self.DrawButtonWithPopUpBackground(view, rect, updateRect, leftTopRadius, rightTopRadius, leftBottomRadius, rightBottomRadius, base, flags, borders, orientation);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("leftTopRadius"), py::arg("rightTopRadius"), py::arg("leftBottomRadius"), py::arg("rightBottomRadius"), py::arg("base"), py::arg("flags")=0, py::arg("borders")=B_ALL_BORDERS, py::arg("orientation")=B_HORIZONTAL)
.def("SetBackgroundInfo", &BControlLook::SetBackgroundInfo, "", py::arg("backgroundInfo"))
.def("DrawTabFrame", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,unsigned int flags=0,unsigned int borders=B_ALL_BORDERS,border_style borderStyle=B_FANCY_BORDER,unsigned int side=B_TOP_BORDER) {
    BRect  rect;
    self.DrawTabFrame(view, rect, updateRect, base, flags, borders, borderStyle, side);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags")=0, py::arg("borders")=B_ALL_BORDERS, py::arg("borderStyle")=B_FANCY_BORDER, py::arg("side")=B_TOP_BORDER)
.def("DrawScrollBarButton", &BControlLook::DrawScrollBarButton, "", py::arg("view"), py::arg("rect"), py::arg("updateRect"), py::arg("base"), py::arg("flags"), py::arg("direction"), py::arg("orientation"), py::arg("down")=false)
.def("DrawScrollBarThumb", [](BControlLook& self,BView * view,const BRect & updateRect,const rgb_color & base,unsigned int flags,orientation orientation,unsigned int knobStyle=B_KNOB_NONE) {
    BRect  rect;
    self.DrawScrollBarThumb(view, rect, updateRect, base, flags, orientation, knobStyle);
    return rect;
}
, "", py::arg("view"), py::arg("updateRect"), py::arg("base"), py::arg("flags"), py::arg("orientation"), py::arg("knobStyle")=B_KNOB_NONE)
.def("DrawScrollBarBorder", &BControlLook::DrawScrollBarBorder, "", py::arg("view"), py::arg("rect"), py::arg("updateRect"), py::arg("base"), py::arg("flags"), py::arg("orientation"))
.def("GetScrollBarWidth", &BControlLook::GetScrollBarWidth, "", py::arg("orientation")=B_VERTICAL)
.def_static("ShouldDraw", &BControlLook::ShouldDraw, "", py::arg("view"), py::arg("rect"), py::arg("updateRect"))
;

m.def("instantiate_control_look", &instantiate_control_look, "", py::arg("id"));

}
