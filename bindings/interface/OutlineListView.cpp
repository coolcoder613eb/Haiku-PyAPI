#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/OutlineListView.h>
#include <ListView.h>

namespace py = pybind11;


PYBIND11_MODULE(OutlineListView,m)
{
py::class_<BOutlineListView, BListView>(m, "BOutlineListView")
.def(py::init<BRect, const char *, list_view_type, unsigned int, unsigned int>(), "", py::arg("frame"), py::arg("name"), py::arg("type")=B_SINGLE_SELECTION_LIST, py::arg("resizingMode")=B_FOLLOW_LEFT_TOP, py::arg("flags")=B_WILL_DRAW | B_FRAME_EVENTS | B_NAVIGABLE)
.def(py::init<const char *, list_view_type, unsigned int>(), "", py::arg("name"), py::arg("type")=B_SINGLE_SELECTION_LIST, py::arg("flags")=B_WILL_DRAW | B_FRAME_EVENTS | B_NAVIGABLE)
.def(py::init<BMessage *>(), "", py::arg("archive"))
.def_static("Instantiate", &BOutlineListView::Instantiate, "", py::arg("archive"))
.def("Archive", &BOutlineListView::Archive, "", py::arg("archive"), py::arg("deep")=true)
.def("MouseDown", &BOutlineListView::MouseDown, "", py::arg("where"))
.def("KeyDown", &BOutlineListView::KeyDown, "", py::arg("bytes"), py::arg("numBytes"))
.def("FrameMoved", &BOutlineListView::FrameMoved, "", py::arg("newPosition"))
.def("FrameResized", &BOutlineListView::FrameResized, "", py::arg("newWidth"), py::arg("newHeight"))
.def("MouseUp", &BOutlineListView::MouseUp, "", py::arg("where"))
.def("AddUnder", &BOutlineListView::AddUnder, "", py::arg("item"), py::arg("superItem"))
.def("AddItem", py::overload_cast<BListItem *>(&BOutlineListView::AddItem), "", py::arg("item"))
.def("AddItem", py::overload_cast<BListItem *, int>(&BOutlineListView::AddItem), "", py::arg("item"), py::arg("fullListIndex"))
.def("AddList", py::overload_cast<BList *>(&BOutlineListView::AddList), "", py::arg("newItems"))
.def("AddList", py::overload_cast<BList *, int>(&BOutlineListView::AddList), "", py::arg("newItems"), py::arg("fullListIndex"))
.def("RemoveItem", py::overload_cast<BListItem *>(&BOutlineListView::RemoveItem), "", py::arg("item"))
.def("RemoveItem", py::overload_cast<int>(&BOutlineListView::RemoveItem), "", py::arg("fullListIndex"))
.def("RemoveItems", &BOutlineListView::RemoveItems, "", py::arg("fullListIndex"), py::arg("count"))
.def("FullListItemAt", &BOutlineListView::FullListItemAt, "", py::arg("fullListIndex"))
.def("FullListIndexOf", py::overload_cast<BPoint>(&BOutlineListView::FullListIndexOf), "", py::arg("where"))
.def("FullListIndexOf", py::overload_cast<BListItem *>(&BOutlineListView::FullListIndexOf), "", py::arg("item"))
.def("FullListFirstItem", &BOutlineListView::FullListFirstItem, "")
.def("FullListLastItem", &BOutlineListView::FullListLastItem, "")
.def("FullListHasItem", &BOutlineListView::FullListHasItem, "", py::arg("item"))
.def("FullListCountItems", &BOutlineListView::FullListCountItems, "")
.def("FullListCurrentSelection", &BOutlineListView::FullListCurrentSelection, "", py::arg("index")=0)
.def("MakeEmpty", &BOutlineListView::MakeEmpty, "")
.def("FullListIsEmpty", &BOutlineListView::FullListIsEmpty, "")
.def("FullListDoForEach", py::overload_cast<bool(*func)(BListItem*item)>(&BOutlineListView::FullListDoForEach), "", py::arg(""))
.def("FullListDoForEach", py::overload_cast<bool(*func)(BListItem*item,void*arg), void *>(&BOutlineListView::FullListDoForEach), "", py::arg(""), py::arg("arg"))
.def("Superitem", &BOutlineListView::Superitem, "", py::arg("item"))
.def("Expand", &BOutlineListView::Expand, "", py::arg("item"))
.def("Collapse", &BOutlineListView::Collapse, "", py::arg("item"))
.def("IsExpanded", &BOutlineListView::IsExpanded, "", py::arg("fullListIndex"))
.def("ResolveSpecifier", &BOutlineListView::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("what"), py::arg("property"))
.def("GetSupportedSuites", &BOutlineListView::GetSupportedSuites, "", py::arg("data"))
.def("Perform", &BOutlineListView::Perform, "", py::arg("code"), py::arg("data"))
.def("ResizeToPreferred", &BOutlineListView::ResizeToPreferred, "")
.def("GetPreferredSize", &BOutlineListView::GetPreferredSize, "", py::arg("_width"), py::arg("_height"))
.def("MakeFocus", &BOutlineListView::MakeFocus, "", py::arg("focus")=true)
.def("AllAttached", &BOutlineListView::AllAttached, "")
.def("AllDetached", &BOutlineListView::AllDetached, "")
.def("DetachedFromWindow", &BOutlineListView::DetachedFromWindow, "")
.def("FullListSortItems", &BOutlineListView::FullListSortItems, "", py::arg(""))
.def("SortItemsUnder", &BOutlineListView::SortItemsUnder, "", py::arg("superItem"), py::arg("oneLevelOnly"), py::arg(""))
.def("CountItemsUnder", &BOutlineListView::CountItemsUnder, "", py::arg("superItem"), py::arg("oneLevelOnly"))
.def("EachItemUnder", &BOutlineListView::EachItemUnder, "", py::arg("superItem"), py::arg("oneLevelOnly"), py::arg("*(*eachFunc)(BListItem*item,void*arg)"), py::arg("arg"))
.def("ItemUnderAt", &BOutlineListView::ItemUnderAt, "", py::arg("superItem"), py::arg("oneLevelOnly"), py::arg("index"))
;


}
