#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/TextView.h>
#include <stdint.h>
#include <Locker.h>
#include <View.h>
#include <File.h>
#include <Clipboard.h>
#include <Region.h>

namespace py = pybind11;
using namespace BPrivate;

PYBIND11_MODULE(TextView,m)
{
py::enum_<undo_state>(m, "undo_state", "")
.value("B_UNDO_UNAVAILABLE", undo_state::B_UNDO_UNAVAILABLE, "")
.value("B_UNDO_TYPING", undo_state::B_UNDO_TYPING, "")
.value("B_UNDO_CUT", undo_state::B_UNDO_CUT, "")
.value("B_UNDO_PASTE", undo_state::B_UNDO_PASTE, "")
.value("B_UNDO_CLEAR", undo_state::B_UNDO_CLEAR, "")
.value("B_UNDO_DROP", undo_state::B_UNDO_DROP, "")
.export_values();

//m.attr("TextGapBuffer") = TextGapBuffer;

py::class_<text_run>(m, "text_run")
.def_readwrite("offset", &text_run::offset, "")
.def_readwrite("font", &text_run::font, "")
.def_readwrite("color", &text_run::color, "")
;

py::class_<text_run_array>(m, "text_run_array")
.def_readwrite("count", &text_run_array::count, "")
.def_readonly("runs", &text_run_array::runs, "")
;

py::class_<BTextView, BView, std::unique_ptr<BTextView,py::nodelete>>(m, "BTextView")
.def(py::init<BRect, const char *, BRect, uint32, uint32>(), "", py::arg("frame"), py::arg("name"), py::arg("textRect"), py::arg("resizeMask"), py::arg("flags")=B_WILL_DRAW | B_PULSE_NEEDED)
.def(py::init<BRect, const char *, BRect, const BFont *, const rgb_color *, uint32, uint32>(), "", py::arg("frame"), py::arg("name"), py::arg("textRect"), py::arg("initialFont"), py::arg("initialColor"), py::arg("resizeMask"), py::arg("flags"))
.def(py::init<const char *, unsigned int>(), "", py::arg("name"), py::arg("flags")=B_WILL_DRAW | B_PULSE_NEEDED)
.def(py::init<const char *, const BFont *, const rgb_color *, uint32>(), "", py::arg("name"), py::arg("initialFont"), py::arg("initialColor"), py::arg("flags"))
.def(py::init<BMessage *>(), "", py::arg("archive"))
.def_static("Instantiate", &BTextView::Instantiate, "", py::arg("archive"))
.def("Archive", &BTextView::Archive, "", py::arg("archive"), py::arg("deep")=true)
.def("AttachedToWindow", &BTextView::AttachedToWindow, "")
.def("DetachedFromWindow", &BTextView::DetachedFromWindow, "")
.def("Draw", &BTextView::Draw, "", py::arg("updateRect"))
.def("MouseDown", &BTextView::MouseDown, "", py::arg("where"))
.def("MouseUp", &BTextView::MouseUp, "", py::arg("where"))
.def("MouseMoved", &BTextView::MouseMoved, "", py::arg("where"), py::arg("code"), py::arg("dragMessage"))
.def("WindowActivated", &BTextView::WindowActivated, "", py::arg("active"))
.def("KeyDown", &BTextView::KeyDown, "", py::arg("bytes"), py::arg("numBytes"))
.def("Pulse", &BTextView::Pulse, "")
.def("FrameResized", &BTextView::FrameResized, "", py::arg("newWidth"), py::arg("newHeight"))
.def("MakeFocus", &BTextView::MakeFocus, "", py::arg("focus")=true)
.def("MessageReceived", &BTextView::MessageReceived, "", py::arg("message"))
.def("ResolveSpecifier", &BTextView::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("form"), py::arg("property"))
.def("GetSupportedSuites", &BTextView::GetSupportedSuites, "", py::arg("data"))
.def("Perform", &BTextView::Perform, "", py::arg("code"), py::arg("data"))
.def("SetText", py::overload_cast<const char *, const text_run_array *>(&BTextView::SetText), "", py::arg("text"), py::arg("runs")=NULL)
.def("SetText", py::overload_cast<const char *, int32, const text_run_array *>(&BTextView::SetText), "", py::arg("text"), py::arg("length"), py::arg("runs")=NULL)
.def("SetText", py::overload_cast<BFile *, int32, int32, const text_run_array *>(&BTextView::SetText), "", py::arg("file"), py::arg("offset"), py::arg("length"), py::arg("runs")=NULL)
.def("Insert", py::overload_cast<const char *, const text_run_array *>(&BTextView::Insert), "", py::arg("text"), py::arg("runs")=NULL)
.def("Insert", py::overload_cast<const char *, int32, const text_run_array *>(&BTextView::Insert), "", py::arg("text"), py::arg("length"), py::arg("runs")=NULL)
.def("Insert", py::overload_cast<int32, const char *, int32, const text_run_array *>(&BTextView::Insert), "", py::arg("offset"), py::arg("text"), py::arg("length"), py::arg("runs")=NULL)
.def("Delete", py::overload_cast<>(&BTextView::Delete), "")
.def("Delete", py::overload_cast<int32, int32>(&BTextView::Delete), "", py::arg("startOffset"), py::arg("endOffset"))
.def("Text", &BTextView::Text, "")
.def("TextLength", &BTextView::TextLength, "")
.def("GetText", &BTextView::GetText, "", py::arg("offset"), py::arg("length"), py::arg("buffer"))
.def("ByteAt", &BTextView::ByteAt, "", py::arg("offset"))
.def("CountLines", &BTextView::CountLines, "")
.def("CurrentLine", &BTextView::CurrentLine, "")
.def("GoToLine", &BTextView::GoToLine, "", py::arg("lineNumber"))
.def("Cut", &BTextView::Cut, "", py::arg("clipboard"))
.def("Copy", &BTextView::Copy, "", py::arg("clipboard"))
.def("Paste", &BTextView::Paste, "", py::arg("clipboard"))
.def("Clear", &BTextView::Clear, "")
.def("AcceptsPaste", &BTextView::AcceptsPaste, "", py::arg("clipboard"))
.def("AcceptsDrop", &BTextView::AcceptsDrop, "", py::arg("message"))
.def("Select", &BTextView::Select, "", py::arg("startOffset"), py::arg("endOffset"))
.def("SelectAll", &BTextView::SelectAll, "")
.def("GetSelection", &BTextView::GetSelection, "", py::arg("_start"), py::arg("_end"))
.def("SetFontAndColor", static_cast<void (BTextView::*)(const BFont*, uint32, const rgb_color*)>(&BTextView::SetFontAndColor), "", py::arg("font"), py::arg("mode")=B_FONT_ALL, py::arg("color")=NULL)
//.def("SetFontAndColor", py::overload_cast<const BFont *, uint32, const rgb_color *>(&BTextView::SetFontAndColor,py::const_), "", py::arg("font"), py::arg("mode")=B_FONT_ALL, py::arg("color")=NULL)
.def("SetFontAndColor", static_cast<void (BTextView::*)(int32, int32, const BFont *, uint32, const rgb_color *)>(&BTextView::SetFontAndColor), "", py::arg("startOffset"), py::arg("endOffset"), py::arg("font"), py::arg("mode")=B_FONT_ALL, py::arg("color")=NULL)
//.def("SetFontAndColor", py::overload_cast<int32, int32, const BFont *, uint32, const rgb_color *>(&BTextView::SetFontAndColor,py::const_), "", py::arg("startOffset"), py::arg("endOffset"), py::arg("font"), py::arg("mode")=B_FONT_ALL, py::arg("color")=NULL)
.def("GetFontAndColor", py::overload_cast<int32, BFont *, rgb_color *>(&BTextView::GetFontAndColor,py::const_), "", py::arg("offset"), py::arg("_font"), py::arg("_color")=NULL)
.def("GetFontAndColor", py::overload_cast<BFont *, uint32 *, rgb_color *, bool *>(&BTextView::GetFontAndColor,py::const_), "", py::arg("_font"), py::arg("_mode"), py::arg("_color")=NULL, py::arg("_sameColor")=NULL)
.def("SetRunArray", &BTextView::SetRunArray, "", py::arg("startOffset"), py::arg("endOffset"), py::arg("runs"))
.def("RunArray", &BTextView::RunArray, "", py::arg("startOffset"), py::arg("endOffset"), py::arg("_size")=NULL)
.def("LineAt", py::overload_cast<int32>(&BTextView::LineAt,py::const_), "", py::arg("offset"))
.def("LineAt", py::overload_cast<BPoint>(&BTextView::LineAt,py::const_), "", py::arg("point"))
.def("PointAt", &BTextView::PointAt, "", py::arg("offset"), py::arg("_height")=NULL)
.def("OffsetAt", py::overload_cast<BPoint>(&BTextView::OffsetAt,py::const_), "", py::arg("point"))
.def("OffsetAt", py::overload_cast<int32>(&BTextView::OffsetAt,py::const_), "", py::arg("line"))
.def("FindWord", &BTextView::FindWord, "", py::arg("offset"), py::arg("_fromOffset"), py::arg("_toOffset"))
.def("CanEndLine", &BTextView::CanEndLine, "", py::arg("offset"))
.def("LineWidth", &BTextView::LineWidth, "", py::arg("lineNumber")=0)
.def("LineHeight", &BTextView::LineHeight, "", py::arg("lineNumber")=0)
.def("TextHeight", &BTextView::TextHeight, "", py::arg("startLine"), py::arg("endLine"))
.def("GetTextRegion", &BTextView::GetTextRegion, "", py::arg("startOffset"), py::arg("endOffset"), py::arg("outRegion"))
.def("ScrollToOffset", &BTextView::ScrollToOffset, "", py::arg("offset"))
.def("ScrollToSelection", &BTextView::ScrollToSelection, "")
.def("Highlight", &BTextView::Highlight, "", py::arg("startOffset"), py::arg("endOffset"))
.def("SetTextRect", &BTextView::SetTextRect, "", py::arg("rect"))
.def("TextRect", &BTextView::TextRect, "")
.def("SetInsets", &BTextView::SetInsets, "", py::arg("left"), py::arg("top"), py::arg("right"), py::arg("bottom"))
.def("GetInsets", &BTextView::GetInsets, "", py::arg("_left"), py::arg("_top"), py::arg("_right"), py::arg("_bottom"))
.def("SetStylable", &BTextView::SetStylable, "", py::arg("stylable"))
.def("IsStylable", &BTextView::IsStylable, "")
.def("SetTabWidth", &BTextView::SetTabWidth, "", py::arg("width"))
.def("TabWidth", &BTextView::TabWidth, "")
.def("MakeSelectable", &BTextView::MakeSelectable, "", py::arg("selectable")=true)
.def("IsSelectable", &BTextView::IsSelectable, "")
.def("MakeEditable", &BTextView::MakeEditable, "", py::arg("editable")=true)
.def("IsEditable", &BTextView::IsEditable, "")
.def("SetWordWrap", &BTextView::SetWordWrap, "", py::arg("wrap"))
.def("DoesWordWrap", &BTextView::DoesWordWrap, "")
.def("SetMaxBytes", &BTextView::SetMaxBytes, "", py::arg("max"))
.def("MaxBytes", &BTextView::MaxBytes, "")
.def("DisallowChar", &BTextView::DisallowChar, "", py::arg("character"))
.def("AllowChar", &BTextView::AllowChar, "", py::arg("character"))
.def("SetAlignment", &BTextView::SetAlignment, "", py::arg("align"))
.def("Alignment", &BTextView::Alignment, "")
.def("SetAutoindent", &BTextView::SetAutoindent, "", py::arg("state"))
.def("DoesAutoindent", &BTextView::DoesAutoindent, "")
.def("SetColorSpace", &BTextView::SetColorSpace, "", py::arg("colors"))
.def("ColorSpace", &BTextView::ColorSpace, "")
.def("MakeResizable", &BTextView::MakeResizable, "", py::arg("resize"), py::arg("resizeView")=NULL)
.def("IsResizable", &BTextView::IsResizable, "")
.def("SetDoesUndo", &BTextView::SetDoesUndo, "", py::arg("undo"))
.def("DoesUndo", &BTextView::DoesUndo, "")
.def("HideTyping", &BTextView::HideTyping, "", py::arg("enabled"))
.def("IsTypingHidden", &BTextView::IsTypingHidden, "")
.def("ResizeToPreferred", &BTextView::ResizeToPreferred, "")
.def("GetPreferredSize", &BTextView::GetPreferredSize, "", py::arg("_width"), py::arg("_height"))
.def("AllAttached", &BTextView::AllAttached, "")
.def("AllDetached", &BTextView::AllDetached, "")
.def_static("AllocRunArray", &BTextView::AllocRunArray, "", py::arg("entryCount"), py::arg("outSize")=NULL)
.def_static("CopyRunArray", &BTextView::CopyRunArray, "", py::arg("orig"), py::arg("countDelta")=0)
.def_static("FreeRunArray", &BTextView::FreeRunArray, "", py::arg("array"))
.def_static("FlattenRunArray", &BTextView::FlattenRunArray, "", py::arg("runArray"), py::arg("_size")=NULL)
.def_static("UnflattenRunArray", &BTextView::UnflattenRunArray, "", py::arg("data"), py::arg("_size")=NULL)
.def("Undo", &BTextView::Undo, "", py::arg("clipboard"))
.def("UndoState", &BTextView::UndoState, "", py::arg("isRedo"))
.def("MinSize", &BTextView::MinSize, "")
.def("MaxSize", &BTextView::MaxSize, "")
.def("PreferredSize", &BTextView::PreferredSize, "")
.def("HasHeightForWidth", &BTextView::HasHeightForWidth, "")
.def("GetHeightForWidth", &BTextView::GetHeightForWidth, "", py::arg("width"), py::arg("min"), py::arg("max"), py::arg("preferred"))
;


}
