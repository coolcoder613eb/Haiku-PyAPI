#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/View.h>
#include <AffineTransform.h>
#include <Alignment.h>
#include <Font.h>
#include <Handler.h>
#include <InterfaceDefs.h>
#include <Rect.h>
#include <Gradient.h>
#include <Bitmap.h>
#include <ScrollView.h>
#include <Window.h>
#include <LayoutItem.h>
#include <Layout.h>
#include <Polygon.h>
#include <Picture.h>
#include <Cursor.h>
#include <Shape.h>
#include <LayoutContext.h>
#include <Region.h>

namespace py = pybind11;
using namespace BPrivate;

PYBIND11_MODULE(View,m)
{
m.attr("B_PRIMARY_MOUSE_BUTTON") = "B_MOUSE_BUTTON ( 1 )";
m.attr("B_SECONDARY_MOUSE_BUTTON") = "B_MOUSE_BUTTON ( 2 )";
m.attr("B_TERTIARY_MOUSE_BUTTON") = "B_MOUSE_BUTTON ( 3 )";

m.attr("B_ENTERED_VIEW") = 0;
m.attr("B_INSIDE_VIEW") = 1;
m.attr("B_EXITED_VIEW") = 2;
m.attr("B_OUTSIDE_VIEW") = 3;

m.attr("B_POINTER_EVENTS") = 1;
m.attr("B_KEYBOARD_EVENTS") = 2;

m.attr("B_LOCK_WINDOW_FOCUS") = 1;
m.attr("B_SUSPEND_VIEW_FOCUS") = 2;
m.attr("B_NO_POINTER_HISTORY") = 4;
m.attr("B_FULL_POINTER_HISTORY") = 8;

m.attr("B_TRACK_WHOLE_RECT") = 0;
m.attr("B_TRACK_RECT_CORNER") = 1;

m.attr("B_FONT_FAMILY_AND_STYLE") = 1;
m.attr("B_FONT_SIZE") = 2;
m.attr("B_FONT_SHEAR") = 4;
m.attr("B_FONT_ROTATION") = 8;
m.attr("B_FONT_SPACING") = 16;
m.attr("B_FONT_ENCODING") = 32;
m.attr("B_FONT_FACE") = 64;
m.attr("B_FONT_FLAGS") = 128;
m.attr("B_FONT_FALSE_BOLD_WIDTH") = 256;
m.attr("B_FONT_ALL") = 511;

py::enum_<coordinate_space>(m, "coordinate_space", "")
.value("B_CURRENT_STATE_COORDINATES", coordinate_space::B_CURRENT_STATE_COORDINATES, "")
.value("B_PREVIOUS_STATE_COORDINATES", coordinate_space::B_PREVIOUS_STATE_COORDINATES, "")
.value("B_VIEW_COORDINATES", coordinate_space::B_VIEW_COORDINATES, "")
.value("B_PARENT_VIEW_DRAW_COORDINATES", coordinate_space::B_PARENT_VIEW_DRAW_COORDINATES, "")
.value("B_PARENT_VIEW_COORDINATES", coordinate_space::B_PARENT_VIEW_COORDINATES, "")
.value("B_WINDOW_COORDINATES", coordinate_space::B_WINDOW_COORDINATES, "")
.value("B_SCREEN_COORDINATES", coordinate_space::B_SCREEN_COORDINATES, "")
.export_values();

m.attr("B_FULL_UPDATE_ON_RESIZE") = B_FULL_UPDATE_ON_RESIZE;

m.attr("_B_RESERVED1_") = _B_RESERVED1_;

m.attr("B_WILL_DRAW") = B_WILL_DRAW;

m.attr("B_PULSE_NEEDED") = B_PULSE_NEEDED;

m.attr("B_NAVIGABLE_JUMP") = B_NAVIGABLE_JUMP;

m.attr("B_FRAME_EVENTS") = B_FRAME_EVENTS;

m.attr("B_NAVIGABLE") = B_NAVIGABLE;

m.attr("B_SUBPIXEL_PRECISE") = B_SUBPIXEL_PRECISE;

m.attr("B_DRAW_ON_CHILDREN") = B_DRAW_ON_CHILDREN;

m.attr("B_INPUT_METHOD_AWARE") = B_INPUT_METHOD_AWARE;

m.attr("B_SCROLL_VIEW_AWARE") = B_SCROLL_VIEW_AWARE;

m.attr("B_SUPPORTS_LAYOUT") = B_SUPPORTS_LAYOUT;

m.attr("B_INVALIDATE_AFTER_LAYOUT") = B_INVALIDATE_AFTER_LAYOUT;

m.attr("B_TRANSPARENT_BACKGROUND") = B_TRANSPARENT_BACKGROUND;

m.attr("_VIEW_TOP_") = _VIEW_TOP_;

m.attr("_VIEW_LEFT_") = _VIEW_LEFT_;

m.attr("_VIEW_BOTTOM_") = _VIEW_BOTTOM_;

m.attr("_VIEW_RIGHT_") = _VIEW_RIGHT_;

m.attr("_VIEW_CENTER_") = _VIEW_CENTER_;

//m.attr("ViewState") = ViewState;

py::class_<BView,std::unique_ptr<BView, py::nodelete>>(m, "BView")
.def(py::init<const char *, unsigned int, BLayout *>(), "", py::arg("name"), py::arg("flags"), py::arg("layout")=NULL)
.def(py::init<BRect, const char *, unsigned int, unsigned int>(), "", py::arg("frame"), py::arg("name"), py::arg("resizingMode"), py::arg("flags"))
.def(py::init<BMessage *>(), "", py::arg("archive"))
.def_static("Instantiate", &BView::Instantiate, "", py::arg("archive"))
.def("Archive", &BView::Archive, "", py::arg("archive"), py::arg("deep")=true)
.def("AllUnarchived", &BView::AllUnarchived, "", py::arg("archive"))
.def("AllArchived", &BView::AllArchived, "", py::arg("archive"))
.def("AttachedToWindow", &BView::AttachedToWindow, "")
.def("AllAttached", &BView::AllAttached, "")
.def("DetachedFromWindow", &BView::DetachedFromWindow, "")
.def("AllDetached", &BView::AllDetached, "")
.def("MessageReceived", &BView::MessageReceived, "", py::arg("message"))
.def("AddChild", py::overload_cast<BView *, BView *>(&BView::AddChild), "", py::arg("child"), py::arg("before")=NULL)
.def("AddChild", py::overload_cast<BLayoutItem *>(&BView::AddChild), "", py::arg("child"))
.def("RemoveChild", &BView::RemoveChild, "", py::arg("child"))
.def("CountChildren", &BView::CountChildren, "")
.def("ChildAt", &BView::ChildAt, "", py::arg("index"))
.def("NextSibling", &BView::NextSibling, "")
.def("PreviousSibling", &BView::PreviousSibling, "")
.def("RemoveSelf", &BView::RemoveSelf, "")
.def("Window", &BView::Window, "")
.def("Draw", &BView::Draw, "", py::arg("updateRect"))
.def("MouseDown", &BView::MouseDown, "", py::arg("where"))
.def("MouseUp", &BView::MouseUp, "", py::arg("where"))
.def("MouseMoved", &BView::MouseMoved, "", py::arg("where"), py::arg("code"), py::arg("dragMessage"))
.def("WindowActivated", &BView::WindowActivated, "", py::arg("active"))
.def("KeyDown", &BView::KeyDown, "", py::arg("bytes"), py::arg("numBytes"))
.def("KeyUp", &BView::KeyUp, "", py::arg("bytes"), py::arg("numBytes"))
.def("Pulse", &BView::Pulse, "")
.def("FrameMoved", &BView::FrameMoved, "", py::arg("newPosition"))
.def("FrameResized", &BView::FrameResized, "", py::arg("newWidth"), py::arg("newHeight"))
.def("TargetedByScrollView", &BView::TargetedByScrollView, "", py::arg("scrollView"))
//.def("BeginRectTracking", &BView::BeginRectTracking, "", py::arg("startRect"), py::arg("style")=B_TRACK_WHOLE_RECT)
.def("EndRectTracking", &BView::EndRectTracking, "")
.def("GetMouse", &BView::GetMouse, "", py::arg("location"), py::arg("buttons"), py::arg("checkMessageQueue")=true)
.def("DragMessage", py::overload_cast<BMessage *, BRect, BHandler *>(&BView::DragMessage), "", py::arg("message"), py::arg("dragRect"), py::arg("replyTo")=NULL)
.def("DragMessage", py::overload_cast<BMessage *, BBitmap *, BPoint, BHandler *>(&BView::DragMessage), "", py::arg("message"), py::arg("bitmap"), py::arg("offset"), py::arg("replyTo")=NULL)
.def("DragMessage", py::overload_cast<BMessage *, BBitmap *, drawing_mode, BPoint, BHandler *>(&BView::DragMessage), "", py::arg("message"), py::arg("bitmap"), py::arg("dragMode"), py::arg("offset"), py::arg("replyTo")=NULL)
.def("FindView", &BView::FindView, "", py::arg("name"))
.def("Parent", &BView::Parent, "")
.def("Bounds", &BView::Bounds, "")
.def("Frame", &BView::Frame, "")
.def("ConvertToScreen", py::overload_cast<BPoint *>(&BView::ConvertToScreen, py::const_), "", py::arg("point"))
.def("ConvertToScreen", py::overload_cast<BPoint>(&BView::ConvertToScreen, py::const_), "", py::arg("point"))
.def("ConvertFromScreen", py::overload_cast<BPoint *>(&BView::ConvertFromScreen, py::const_), "", py::arg("point"))
.def("ConvertFromScreen", py::overload_cast<BPoint>(&BView::ConvertFromScreen, py::const_), "", py::arg("point"))
.def("ConvertToScreen", py::overload_cast<BRect *>(&BView::ConvertToScreen, py::const_), "", py::arg("rect"))
.def("ConvertToScreen", py::overload_cast<BRect>(&BView::ConvertToScreen, py::const_), "", py::arg("rect"))
.def("ConvertFromScreen", py::overload_cast<BRect *>(&BView::ConvertFromScreen, py::const_), "", py::arg("rect"))
.def("ConvertFromScreen", py::overload_cast<BRect>(&BView::ConvertFromScreen, py::const_), "", py::arg("rect"))
.def("ConvertToParent", py::overload_cast<BPoint *>(&BView::ConvertToParent, py::const_), "", py::arg("point"))
.def("ConvertToParent", py::overload_cast<BPoint>(&BView::ConvertToParent, py::const_), "", py::arg("point"))
.def("ConvertFromParent", py::overload_cast<BPoint *>(&BView::ConvertFromParent, py::const_), "", py::arg("point"))
.def("ConvertFromParent", py::overload_cast<BPoint>(&BView::ConvertFromParent, py::const_), "", py::arg("point"))
.def("ConvertToParent", py::overload_cast<BRect *>(&BView::ConvertToParent, py::const_), "", py::arg("rect"))
.def("ConvertToParent", py::overload_cast<BRect>(&BView::ConvertToParent, py::const_), "", py::arg("rect"))
.def("ConvertFromParent", py::overload_cast<BRect *>(&BView::ConvertFromParent, py::const_), "", py::arg("rect"))
.def("ConvertFromParent", py::overload_cast<BRect>(&BView::ConvertFromParent, py::const_), "", py::arg("rect"))
.def("LeftTop", &BView::LeftTop, "")
.def("GetClippingRegion", &BView::GetClippingRegion, "", py::arg("region"))
.def("ConstrainClippingRegion", &BView::ConstrainClippingRegion, "", py::arg("region"))
//.def("ClipToPicture", &BView::ClipToPicture, "", py::arg("picture"), py::arg("where")=B_ORIGIN, py::arg("sync")=true)
//.def("ClipToInversePicture", &BView::ClipToInversePicture, "", py::arg("picture"), py::arg("where")=B_ORIGIN, py::arg("sync")=true)
.def("ClipToRect", &BView::ClipToRect, "", py::arg("rect"))
.def("ClipToInverseRect", &BView::ClipToInverseRect, "", py::arg("rect"))
.def("ClipToShape", &BView::ClipToShape, "", py::arg("shape"))
.def("ClipToInverseShape", &BView::ClipToInverseShape, "", py::arg("shape"))
.def("SetDrawingMode", &BView::SetDrawingMode, "", py::arg("mode"))
.def("DrawingMode", &BView::DrawingMode, "")
.def("SetBlendingMode", &BView::SetBlendingMode, "", py::arg("srcAlpha"), py::arg("alphaFunc"))
.def("GetBlendingMode", &BView::GetBlendingMode, "", py::arg("srcAlpha"), py::arg("alphaFunc"))
.def("SetPenSize", &BView::SetPenSize, "", py::arg("size"))
.def("PenSize", &BView::PenSize, "")
.def("SetViewCursor", &BView::SetViewCursor, "", py::arg("cursor"), py::arg("sync")=true)
.def("HasDefaultColors", &BView::HasDefaultColors, "")
.def("HasSystemColors", &BView::HasSystemColors, "")
.def("AdoptParentColors", &BView::AdoptParentColors, "")
.def("AdoptSystemColors", &BView::AdoptSystemColors, "")
.def("AdoptViewColors", &BView::AdoptViewColors, "", py::arg("view"))
.def("SetViewColor", py::overload_cast<rgb_color>(&BView::SetViewColor), "", py::arg("color"))
.def("SetViewColor", py::overload_cast<uchar, uchar, uchar, uchar>(&BView::SetViewColor), "", py::arg("red"), py::arg("green"), py::arg("blue"), py::arg("alpha")=255)
.def("ViewColor", &BView::ViewColor, "")
.def("SetViewUIColor", &BView::SetViewUIColor, "", py::arg("which"), py::arg("tint")=B_NO_TINT)
.def("ViewUIColor", &BView::ViewUIColor, "", py::arg("tint")=NULL)
//.def("SetViewBitmap", py::overload_cast<const BBitmap *, BRect, BRect, unsigned int, unsigned int>(&BView::SetViewBitmap), "", py::arg("bitmap"), py::arg("srcRect"), py::arg("dstRect"), py::arg("followFlags")=B_FOLLOW_LEFT_TOP, py::arg("options")=B_TILE_BITMAP)
//.def("SetViewBitmap", py::overload_cast<const BBitmap *, unsigned int, unsigned int>(&BView::SetViewBitmap), "", py::arg("bitmap"), py::arg("followFlags")=B_FOLLOW_LEFT_TOP, py::arg("options")=B_TILE_BITMAP)
.def("ClearViewBitmap", &BView::ClearViewBitmap, "")
.def("SetViewOverlay", py::overload_cast<const BBitmap *, BRect, BRect, rgb_color *, unsigned int, unsigned int>(&BView::SetViewOverlay), "", py::arg("overlay"), py::arg("srcRect"), py::arg("dstRect"), py::arg("colorKey"), py::arg("followFlags")=B_FOLLOW_LEFT_TOP, py::arg("options")=0)
.def("SetViewOverlay", py::overload_cast<const BBitmap *, rgb_color *, unsigned int, unsigned int>(&BView::SetViewOverlay), "", py::arg("overlay"), py::arg("colorKey"), py::arg("followFlags")=B_FOLLOW_LEFT_TOP, py::arg("options")=0)
.def("ClearViewOverlay", &BView::ClearViewOverlay, "")
.def("SetHighColor", py::overload_cast<rgb_color>(&BView::SetHighColor), "", py::arg("color"))
.def("SetHighColor", py::overload_cast<uchar, uchar, uchar, uchar>(&BView::SetHighColor), "", py::arg("red"), py::arg("green"), py::arg("blue"), py::arg("alpha")=255)
.def("HighColor", &BView::HighColor, "")
.def("SetHighUIColor", &BView::SetHighUIColor, "", py::arg("which"), py::arg("tint")=B_NO_TINT)
.def("HighUIColor", &BView::HighUIColor, "", py::arg("tint")=NULL)
.def("SetLowColor", py::overload_cast<rgb_color>(&BView::SetLowColor), "", py::arg("color"))
.def("SetLowColor", py::overload_cast<uchar, uchar, uchar, uchar>(&BView::SetLowColor), "", py::arg("red"), py::arg("green"), py::arg("blue"), py::arg("alpha")=255)
.def("LowColor", &BView::LowColor, "")
.def("SetLowUIColor", &BView::SetLowUIColor, "", py::arg("which"), py::arg("tint")=B_NO_TINT)
.def("LowUIColor", &BView::LowUIColor, "", py::arg("tint")=NULL)
.def("SetLineMode", &BView::SetLineMode, "", py::arg("lineCap"), py::arg("lineJoin"), py::arg("miterLimit")=B_DEFAULT_MITER_LIMIT)
.def("LineJoinMode", &BView::LineJoinMode, "")
.def("LineCapMode", &BView::LineCapMode, "")
.def("LineMiterLimit", &BView::LineMiterLimit, "")
.def("SetFillRule", &BView::SetFillRule, "", py::arg("rule"))
.def("FillRule", &BView::FillRule, "")
.def("SetOrigin", py::overload_cast<BPoint>(&BView::SetOrigin), "", py::arg("where"))
.def("SetOrigin", py::overload_cast<float, float>(&BView::SetOrigin), "", py::arg("x"), py::arg("y"))
.def("Origin", &BView::Origin, "")
.def("SetTransform", &BView::SetTransform, "", py::arg("transform"))
.def("Transform", &BView::Transform, "")
.def("TranslateBy", &BView::TranslateBy, "", py::arg("x"), py::arg("y"))
.def("ScaleBy", &BView::ScaleBy, "", py::arg("x"), py::arg("y"))
.def("RotateBy", &BView::RotateBy, "", py::arg("angleRadians"))
.def("TransformTo", &BView::TransformTo, "", py::arg("basis"))
.def("PushState", &BView::PushState, "")
.def("PopState", &BView::PopState, "")
.def("MovePenTo", py::overload_cast<BPoint>(&BView::MovePenTo), "", py::arg("pt"))
.def("MovePenTo", py::overload_cast<float, float>(&BView::MovePenTo), "", py::arg("x"), py::arg("y"))
.def("MovePenBy", &BView::MovePenBy, "", py::arg("x"), py::arg("y"))
.def("PenLocation", &BView::PenLocation, "")
//.def("StrokeLine", py::overload_cast<BPoint, ::pattern>(&BView::StrokeLine), "", py::arg("toPoint"), py::arg("pattern")=B_SOLID_HIGH)
//.def("StrokeLine", py::overload_cast<BPoint, BPoint, ::pattern>(&BView::StrokeLine), "", py::arg("start"), py::arg("end"), py::arg("pattern")=B_SOLID_HIGH)
.def("BeginLineArray", &BView::BeginLineArray, "", py::arg("count"))
.def("AddLine", &BView::AddLine, "", py::arg("start"), py::arg("end"), py::arg("color"))
.def("EndLineArray", &BView::EndLineArray, "")
/*
.def("StrokePolygon", py::overload_cast<const BPolygon *, bool, ::pattern>(&BView::StrokePolygon), "", py::arg("polygon"), py::arg("closed")=true, py::arg("pattern")=B_SOLID_HIGH)
.def("StrokePolygon", py::overload_cast<const BPoint *, int, bool, ::pattern>(&BView::StrokePolygon), "", py::arg("pointArray"), py::arg("numPoints"), py::arg("closed")=true, py::arg("pattern")=B_SOLID_HIGH)
.def("StrokePolygon", py::overload_cast<const BPoint *, int, BRect, bool, ::pattern>(&BView::StrokePolygon), "", py::arg("pointArray"), py::arg("numPoints"), py::arg("bounds"), py::arg("closed")=true, py::arg("pattern")=B_SOLID_HIGH)
.def("FillPolygon", py::overload_cast<const BPolygon *, ::pattern>(&BView::FillPolygon), "", py::arg("polygon"), py::arg("pattern")=B_SOLID_HIGH)
.def("FillPolygon", py::overload_cast<const BPoint *, int, ::pattern>(&BView::FillPolygon), "", py::arg("pointArray"), py::arg("numPoints"), py::arg("pattern")=B_SOLID_HIGH)
.def("FillPolygon", py::overload_cast<const BPoint *, int, BRect, ::pattern>(&BView::FillPolygon), "", py::arg("pointArray"), py::arg("numPoints"), py::arg("bounds"), py::arg("pattern")=B_SOLID_HIGH)
.def("FillPolygon", py::overload_cast<const BPolygon *, const BGradient &>(&BView::FillPolygon), "", py::arg("polygon"), py::arg("gradient"))
.def("FillPolygon", py::overload_cast<const BPoint *, int, const BGradient &>(&BView::FillPolygon), "", py::arg("pointArray"), py::arg("numPoints"), py::arg("gradient"))
.def("FillPolygon", py::overload_cast<const BPoint *, int, BRect, const BGradient &>(&BView::FillPolygon), "", py::arg("pointArray"), py::arg("numPoints"), py::arg("bounds"), py::arg("gradient"))
.def("StrokeTriangle", py::overload_cast<BPoint, BPoint, BPoint, BRect, ::pattern>(&BView::StrokeTriangle), "", py::arg("point1"), py::arg("point2"), py::arg("point3"), py::arg("bounds"), py::arg("pattern")=B_SOLID_HIGH)
.def("StrokeTriangle", py::overload_cast<BPoint, BPoint, BPoint, ::pattern>(&BView::StrokeTriangle), "", py::arg("point1"), py::arg("point2"), py::arg("point3"), py::arg("pattern")=B_SOLID_HIGH)
.def("FillTriangle", py::overload_cast<BPoint, BPoint, BPoint, ::pattern>(&BView::FillTriangle), "", py::arg("point1"), py::arg("point2"), py::arg("point3"), py::arg("pattern")=B_SOLID_HIGH)
.def("FillTriangle", py::overload_cast<BPoint, BPoint, BPoint, BRect, ::pattern>(&BView::FillTriangle), "", py::arg("point1"), py::arg("point2"), py::arg("point3"), py::arg("bounds"), py::arg("pattern")=B_SOLID_HIGH)
.def("FillTriangle", py::overload_cast<BPoint, BPoint, BPoint, const BGradient &>(&BView::FillTriangle), "", py::arg("point1"), py::arg("point2"), py::arg("point3"), py::arg("gradient"))
.def("FillTriangle", py::overload_cast<BPoint, BPoint, BPoint, BRect, const BGradient &>(&BView::FillTriangle), "", py::arg("point1"), py::arg("point2"), py::arg("point3"), py::arg("bounds"), py::arg("gradient"))
.def("StrokeRect", &BView::StrokeRect, "", py::arg("rect"), py::arg("pattern")=B_SOLID_HIGH)
.def("FillRect", py::overload_cast<BRect, ::pattern>(&BView::FillRect), "", py::arg("rect"), py::arg("pattern")=B_SOLID_HIGH)
.def("FillRect", py::overload_cast<BRect, const BGradient &>(&BView::FillRect), "", py::arg("rect"), py::arg("gradient"))
.def("FillRegion", py::overload_cast<BRegion *, ::pattern>(&BView::FillRegion), "", py::arg("rectegion"), py::arg("pattern")=B_SOLID_HIGH)
.def("FillRegion", py::overload_cast<BRegion *, const BGradient &>(&BView::FillRegion), "", py::arg("rectegion"), py::arg("gradient"))
.def("InvertRect", &BView::InvertRect, "", py::arg("rect"))
.def("StrokeRoundRect", &BView::StrokeRoundRect, "", py::arg("rect"), py::arg("xRadius"), py::arg("yRadius"), py::arg("pattern")=B_SOLID_HIGH)
.def("FillRoundRect", py::overload_cast<BRect, float, float, ::pattern>(&BView::FillRoundRect), "", py::arg("rect"), py::arg("xRadius"), py::arg("yRadius"), py::arg("pattern")=B_SOLID_HIGH)
.def("FillRoundRect", py::overload_cast<BRect, float, float, const BGradient &>(&BView::FillRoundRect), "", py::arg("rect"), py::arg("xRadius"), py::arg("yRadius"), py::arg("gradient"))
.def("StrokeEllipse", py::overload_cast<BPoint, float, float, ::pattern>(&BView::StrokeEllipse), "", py::arg("center"), py::arg("xRadius"), py::arg("yRadius"), py::arg("pattern")=B_SOLID_HIGH)
.def("StrokeEllipse", py::overload_cast<BRect, ::pattern>(&BView::StrokeEllipse), "", py::arg("rect"), py::arg("pattern")=B_SOLID_HIGH)
.def("FillEllipse", py::overload_cast<BPoint, float, float, ::pattern>(&BView::FillEllipse), "", py::arg("center"), py::arg("xRadius"), py::arg("yRadius"), py::arg("pattern")=B_SOLID_HIGH)
.def("FillEllipse", py::overload_cast<BRect, ::pattern>(&BView::FillEllipse), "", py::arg("rect"), py::arg("pattern")=B_SOLID_HIGH)
.def("FillEllipse", py::overload_cast<BPoint, float, float, const BGradient &>(&BView::FillEllipse), "", py::arg("center"), py::arg("xRadius"), py::arg("yRadius"), py::arg("gradient"))
.def("FillEllipse", py::overload_cast<BRect, const BGradient &>(&BView::FillEllipse), "", py::arg("rect"), py::arg("gradient"))
.def("StrokeArc", py::overload_cast<BPoint, float, float, float, float, ::pattern>(&BView::StrokeArc), "", py::arg("center"), py::arg("xRadius"), py::arg("yRadius"), py::arg("startAngle"), py::arg("arcAngle"), py::arg("pattern")=B_SOLID_HIGH)
.def("StrokeArc", py::overload_cast<BRect, float, float, ::pattern>(&BView::StrokeArc), "", py::arg("rect"), py::arg("startAngle"), py::arg("arcAngle"), py::arg("pattern")=B_SOLID_HIGH)
.def("FillArc", py::overload_cast<BPoint, float, float, float, float, ::pattern>(&BView::FillArc), "", py::arg("center"), py::arg("xRadius"), py::arg("yRadius"), py::arg("startAngle"), py::arg("arcAngle"), py::arg("pattern")=B_SOLID_HIGH)
.def("FillArc", py::overload_cast<BRect, float, float, ::pattern>(&BView::FillArc), "", py::arg("rect"), py::arg("startAngle"), py::arg("arcAngle"), py::arg("pattern")=B_SOLID_HIGH)
.def("FillArc", py::overload_cast<BPoint, float, float, float, float, const BGradient &>(&BView::FillArc), "", py::arg("center"), py::arg("xRadius"), py::arg("yRadius"), py::arg("startAngle"), py::arg("arcAngle"), py::arg("gradient"))
.def("FillArc", py::overload_cast<BRect, float, float, const BGradient &>(&BView::FillArc), "", py::arg("rect"), py::arg("startAngle"), py::arg("arcAngle"), py::arg("gradient"))
.def("StrokeBezier", &BView::StrokeBezier, "", py::arg("controlPoints"), py::arg("pattern")=B_SOLID_HIGH)
.def("FillBezier", py::overload_cast<BPoint *, ::pattern>(&BView::FillBezier), "", py::arg("controlPoints"), py::arg("pattern")=B_SOLID_HIGH)
.def("FillBezier", py::overload_cast<BPoint *, const BGradient &>(&BView::FillBezier), "", py::arg("controlPoints"), py::arg("gradient"))
.def("StrokeShape", &BView::StrokeShape, "", py::arg("shape"), py::arg("pattern")=B_SOLID_HIGH)
.def("FillShape", py::overload_cast<BShape *, ::pattern>(&BView::FillShape), "", py::arg("shape"), py::arg("pattern")=B_SOLID_HIGH)
.def("FillShape", py::overload_cast<BShape *, const BGradient &>(&BView::FillShape), "", py::arg("shape"), py::arg("gradient"))
*/
.def("CopyBits", &BView::CopyBits, "", py::arg("src"), py::arg("dst"))
/*
.def("DrawBitmapAsync", py::overload_cast<const BBitmap *, BRect, BRect, unsigned int>(&BView::DrawBitmapAsync), "", py::arg("aBitmap"), py::arg("bitmapRect"), py::arg("viewRect"), py::arg("options"))
.def("DrawBitmapAsync", py::overload_cast<const BBitmap *, BRect, BRect>(&BView::DrawBitmapAsync), "", py::arg("aBitmap"), py::arg("bitmapRect"), py::arg("viewRect"))
.def("DrawBitmapAsync", py::overload_cast<const BBitmap *, BRect>(&BView::DrawBitmapAsync), "", py::arg("aBitmap"), py::arg("viewRect"))
.def("DrawBitmapAsync", py::overload_cast<const BBitmap *, BPoint>(&BView::DrawBitmapAsync), "", py::arg("aBitmap"), py::arg("where"))
.def("DrawBitmapAsync", py::overload_cast<const BBitmap *>(&BView::DrawBitmapAsync), "", py::arg("aBitmap"))
.def("DrawBitmap", py::overload_cast<const BBitmap *, BRect, BRect, unsigned int>(&BView::DrawBitmap), "", py::arg("aBitmap"), py::arg("bitmapRect"), py::arg("viewRect"), py::arg("options"))
.def("DrawBitmap", py::overload_cast<const BBitmap *, BRect, BRect>(&BView::DrawBitmap), "", py::arg("aBitmap"), py::arg("bitmapRect"), py::arg("viewRect"))
.def("DrawBitmap", py::overload_cast<const BBitmap *, BRect>(&BView::DrawBitmap), "", py::arg("aBitmap"), py::arg("viewRect"))
.def("DrawBitmap", py::overload_cast<const BBitmap *, BPoint>(&BView::DrawBitmap), "", py::arg("aBitmap"), py::arg("where"))
.def("DrawBitmap", py::overload_cast<const BBitmap *>(&BView::DrawBitmap), "", py::arg("aBitmap"))
.def("DrawTiledBitmapAsync", &BView::DrawTiledBitmapAsync, "", py::arg("aBitmap"), py::arg("viewRect"), py::arg("phase")=B_ORIGIN)
.def("DrawTiledBitmap", &BView::DrawTiledBitmap, "", py::arg("aBitmap"), py::arg("viewRect"), py::arg("phase")=B_ORIGIN)
.def("DrawChar", py::overload_cast<char>(&BView::DrawChar), "", py::arg("aChar"))
.def("DrawChar", py::overload_cast<char, BPoint>(&BView::DrawChar), "", py::arg("aChar"), py::arg("location"))
.def("DrawString", py::overload_cast<const char *, escapement_delta *>(&BView::DrawString), "", py::arg("string"), py::arg("delta")=NULL)
.def("DrawString", py::overload_cast<const char *, BPoint, escapement_delta *>(&BView::DrawString), "", py::arg("string"), py::arg("location"), py::arg("delta")=NULL)
.def("DrawString", py::overload_cast<const char *, int, escapement_delta *>(&BView::DrawString), "", py::arg("string"), py::arg("length"), py::arg("delta")=NULL)
.def("DrawString", py::overload_cast<const char *, int, BPoint, escapement_delta *>(&BView::DrawString), "", py::arg("string"), py::arg("length"), py::arg("location"), py::arg("delta")=0)
.def("DrawString", py::overload_cast<const char *, const BPoint *, int>(&BView::DrawString), "", py::arg("string"), py::arg("locations"), py::arg("locationCount"))
.def("DrawString", py::overload_cast<const char *, int, const BPoint *, int>(&BView::DrawString), "", py::arg("string"), py::arg("length"), py::arg("locations"), py::arg("locationCount"))
.def("SetFont", &BView::SetFont, "", py::arg("font"), py::arg("mask")=B_FONT_ALL)
.def("GetFont", &BView::GetFont, "", py::arg("font"))
*/
.def("TruncateString", &BView::TruncateString, "", py::arg("in_out"), py::arg("mode"), py::arg("width"))
.def("StringWidth", py::overload_cast<const char *>(&BView::StringWidth, py::const_), "", py::arg("string"))
.def("StringWidth", py::overload_cast<const char *, int>(&BView::StringWidth, py::const_), "", py::arg("string"), py::arg("length"))
//.def("GetStringWidths", &BView::GetStringWidths, "", py::arg("stringArray"), py::arg("lengthArray"), py::arg("numStrings"), py::arg("widthArray"))
.def("SetFontSize", &BView::SetFontSize, "", py::arg("size"))
.def("ForceFontAliasing", &BView::ForceFontAliasing, "", py::arg("enable"))
.def("GetFontHeight", &BView::GetFontHeight, "", py::arg("height"))
.def("Invalidate", py::overload_cast<BRect>(&BView::Invalidate), "", py::arg("invalRect"))
.def("Invalidate", py::overload_cast<const BRegion *>(&BView::Invalidate), "", py::arg("invalRegion"))
.def("Invalidate", py::overload_cast<>(&BView::Invalidate), "")
.def("DelayedInvalidate", py::overload_cast<bigtime_t>(&BView::DelayedInvalidate), "", py::arg("delay"))
.def("DelayedInvalidate", py::overload_cast<bigtime_t, BRect>(&BView::DelayedInvalidate), "", py::arg("delay"), py::arg("invalRect"))
.def("SetDiskMode", &BView::SetDiskMode, "", py::arg("filename"), py::arg("offset"))
.def("BeginPicture", &BView::BeginPicture, "", py::arg("a_picture"))
.def("AppendToPicture", &BView::AppendToPicture, "", py::arg("a_picture"))
.def("EndPicture", &BView::EndPicture, "")
.def("DrawPicture", py::overload_cast<const BPicture *>(&BView::DrawPicture), "", py::arg("a_picture"))
.def("DrawPicture", py::overload_cast<const BPicture *, BPoint>(&BView::DrawPicture), "", py::arg("a_picture"), py::arg("where"))
.def("DrawPicture", py::overload_cast<const char *, long, BPoint>(&BView::DrawPicture), "", py::arg("filename"), py::arg("offset"), py::arg("where"))
.def("DrawPictureAsync", py::overload_cast<const BPicture *>(&BView::DrawPictureAsync), "", py::arg("a_picture"))
.def("DrawPictureAsync", py::overload_cast<const BPicture *, BPoint>(&BView::DrawPictureAsync), "", py::arg("a_picture"), py::arg("where"))
.def("DrawPictureAsync", py::overload_cast<const char *, long, BPoint>(&BView::DrawPictureAsync), "", py::arg("filename"), py::arg("offset"), py::arg("where"))
.def("BeginLayer", &BView::BeginLayer, "", py::arg("opacity"))
.def("EndLayer", &BView::EndLayer, "")
.def("SetEventMask", &BView::SetEventMask, "", py::arg("mask"), py::arg("options")=0)
.def("EventMask", &BView::EventMask, "")
.def("SetMouseEventMask", &BView::SetMouseEventMask, "", py::arg("mask"), py::arg("options")=0)
.def("SetFlags", &BView::SetFlags, "", py::arg("flags"))
.def("Flags", &BView::Flags, "")
.def("SetResizingMode", &BView::SetResizingMode, "", py::arg("mode"))
.def("ResizingMode", &BView::ResizingMode, "")
.def("MoveBy", &BView::MoveBy, "", py::arg("dh"), py::arg("dv"))
.def("MoveTo", py::overload_cast<BPoint>(&BView::MoveTo), "", py::arg("where"))
.def("MoveTo", py::overload_cast<float, float>(&BView::MoveTo), "", py::arg("x"), py::arg("y"))
.def("ResizeBy", &BView::ResizeBy, "", py::arg("dh"), py::arg("dv"))
.def("ResizeTo", py::overload_cast<float, float>(&BView::ResizeTo), "", py::arg("width"), py::arg("height"))
.def("ResizeTo", py::overload_cast<BSize>(&BView::ResizeTo), "", py::arg("size"))
.def("ScrollBy", &BView::ScrollBy, "", py::arg("dh"), py::arg("dv"))
.def("ScrollTo", py::overload_cast<float, float>(&BView::ScrollTo), "", py::arg("x"), py::arg("y"))
.def("ScrollTo", py::overload_cast<BPoint>(&BView::ScrollTo), "", py::arg("where"))
.def("MakeFocus", &BView::MakeFocus, "", py::arg("focus")=true)
.def("IsFocus", &BView::IsFocus, "")
.def("Show", &BView::Show, "")
.def("Hide", &BView::Hide, "")
.def("IsHidden", py::overload_cast<>(&BView::IsHidden, py::const_), "")
.def("IsHidden", py::overload_cast<const BView *>(&BView::IsHidden, py::const_), "", py::arg("looking_from"))
.def("Flush", &BView::Flush, "")
.def("Sync", &BView::Sync, "")
.def("GetPreferredSize", &BView::GetPreferredSize, "", py::arg("_width"), py::arg("_height"))
.def("ResizeToPreferred", &BView::ResizeToPreferred, "")
.def("ScrollBar", &BView::ScrollBar, "", py::arg("direction"))
.def("ResolveSpecifier", &BView::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("form"), py::arg("property"))
.def("GetSupportedSuites", &BView::GetSupportedSuites, "", py::arg("data"))
.def("IsPrinting", &BView::IsPrinting, "")
.def("SetScale", &BView::SetScale, "", py::arg("scale"))
.def("Scale", &BView::Scale, "")
.def("Perform", &BView::Perform, "", py::arg("code"), py::arg("data"))
.def("DrawAfterChildren", &BView::DrawAfterChildren, "", py::arg("updateRect"))
.def("MinSize", &BView::MinSize, "")
.def("MaxSize", &BView::MaxSize, "")
.def("PreferredSize", &BView::PreferredSize, "")
.def("LayoutAlignment", &BView::LayoutAlignment, "")
.def("SetExplicitMinSize", &BView::SetExplicitMinSize, "", py::arg("size"))
.def("SetExplicitMaxSize", &BView::SetExplicitMaxSize, "", py::arg("size"))
.def("SetExplicitPreferredSize", &BView::SetExplicitPreferredSize, "", py::arg("size"))
.def("SetExplicitSize", &BView::SetExplicitSize, "", py::arg("size"))
.def("SetExplicitAlignment", &BView::SetExplicitAlignment, "", py::arg("alignment"))
.def("ExplicitMinSize", &BView::ExplicitMinSize, "")
.def("ExplicitMaxSize", &BView::ExplicitMaxSize, "")
.def("ExplicitPreferredSize", &BView::ExplicitPreferredSize, "")
.def("ExplicitAlignment", &BView::ExplicitAlignment, "")
.def("HasHeightForWidth", &BView::HasHeightForWidth, "")
.def("GetHeightForWidth", &BView::GetHeightForWidth, "", py::arg("width"), py::arg("min"), py::arg("max"), py::arg("preferred"))
.def("InvalidateLayout", &BView::InvalidateLayout, "", py::arg("descendants")=false)
.def("SetLayout", &BView::SetLayout, "", py::arg("layout"))
.def("GetLayout", &BView::GetLayout, "")
.def("EnableLayoutInvalidation", &BView::EnableLayoutInvalidation, "")
.def("DisableLayoutInvalidation", &BView::DisableLayoutInvalidation, "")
.def("IsLayoutInvalidationDisabled", &BView::IsLayoutInvalidationDisabled, "")
.def("IsLayoutValid", &BView::IsLayoutValid, "")
.def("ResetLayoutInvalidation", &BView::ResetLayoutInvalidation, "")
.def("LayoutContext", &BView::LayoutContext, "")
.def("Layout", &BView::Layout, "", py::arg("force"))
.def("Relayout", &BView::Relayout, "")
/* Where and what is BToolTip?
.def("SetToolTip", py::overload_cast<const char *>(&BView::SetToolTip), "", py::arg("text"))
.def("SetToolTip", py::overload_cast<BToolTip *>(&BView::SetToolTip), "", py::arg("tip"))
.def("ToolTip", &BView::ToolTip, "")
.def("ShowToolTip", &BView::ShowToolTip, "", py::arg("tip")=NULL)
.def("HideToolTip", &BView::HideToolTip, "")
*/
//.def_readwrite("Private", &BView::Private, "")
;

//m.def("_rule_", &_rule_, "", py::arg("r1"), py::arg("r2"), py::arg("r3"), py::arg("r4")); 

}
