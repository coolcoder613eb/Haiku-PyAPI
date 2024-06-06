#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/OutlineListView.h>
#include <ListView.h>

namespace py = pybind11;

class PyBOutlineListView : public BOutlineListView{
	public:
        using BOutlineListView::BOutlineListView;
        status_t	Archive(BMessage* archive, bool deep = true) const override {
        	PYBIND11_OVERLOAD(status_t, BOutlineListView, Archive, archive, deep);
        }
        void				MouseDown(BPoint where) override {
            PYBIND11_OVERLOAD(void, BOutlineListView, MouseDown, where);
        }
        void				KeyDown(const char* bytes, int32 numBytes) override {
            PYBIND11_OVERLOAD(void, BOutlineListView, KeyDown, bytes, numBytes);
        }
        void				MouseUp(BPoint where) override {
            PYBIND11_OVERLOAD(void, BOutlineListView, MouseUp, where);
        }
        bool				AddUnder(BListItem* item, BListItem* superItem) override{
        	PYBIND11_OVERLOAD(bool, BOutlineListView, AddUnder, item, superItem);
        }
        bool				AddItem(BListItem* item) override {
        	PYBIND11_OVERLOAD(bool, BOutlineListView, AddItem, item);
        }
		bool				AddItem(BListItem* item, int32 fullListIndex) override {
			PYBIND11_OVERLOAD(bool, BOutlineListView, AddItem, item, fullListIndex);
		}
		bool				AddList(BList* newItems) override {
			PYBIND11_OVERLOAD(bool, BOutlineListView, AddList, newItems);
		}
		bool				AddList(BList* newItems, int32 fullListIndex) override {
			PYBIND11_OVERLOAD(bool, BOutlineListView, AddList, newItems, fullListIndex);
		}
		bool				RemoveItem(BListItem* item) override {
			PYBIND11_OVERLOAD(bool, BOutlineListView, RemoveItem, item);
		}
		BListItem*			RemoveItem(int32 fullListIndex) override {
			PYBIND11_OVERLOAD(BListItem*, BOutlineListView, RemoveItem, fullListIndex);
		}
		bool				RemoveItems(int32 fullListIndex, int32 count) override {
			PYBIND11_OVERLOAD(bool, BOutlineListView, RemoveItems, fullListIndex, count);
		}
		void				FrameMoved(BPoint newPosition) override {
			PYBIND11_OVERLOAD(void, BOutlineListView, FrameMoved, newPosition);
		}
		void				FrameResized(float newWidth, float newHeight) override {
			PYBIND11_OVERLOAD(void, BOutlineListView, FrameResized, newWidth, newHeight);
		}
		void				MakeEmpty() override {
			PYBIND11_OVERLOAD(void, BOutlineListView, MakeEmpty);
		}
		BHandler*			ResolveSpecifier(BMessage* message,
									int32 index, BMessage* specifier,
									int32 what, const char* property) override {
			PYBIND11_OVERLOAD(BHandler*, BOutlineListView, ResolveSpecifier, message, index, specifier, what, property);
		}
		status_t			GetSupportedSuites(BMessage* data) override {
			PYBIND11_OVERLOAD(status_t, BOutlineListView, GetSupportedSuites, data);
		}
		status_t			Perform(perform_code code, void* data) override {
			PYBIND11_OVERLOAD(status_t, BOutlineListView, Perform, code, data);
		}
		void				ResizeToPreferred() override {
			PYBIND11_OVERLOAD(void, BOutlineListView, ResizeToPreferred);
		}
		void				GetPreferredSize(float* _width, float* _height) override {
			PYBIND11_OVERLOAD(void, BOutlineListView, GetPreferredSize, _width, _height);
		}
		void				MakeFocus(bool focus = true) override {
			PYBIND11_OVERLOAD(void, BOutlineListView, MakeFocus, focus);
		}
		void				AllAttached() override {
			PYBIND11_OVERLOAD(void, BOutlineListView, AllAttached);
		}
		void				AllDetached() override {
			PYBIND11_OVERLOAD(void, BOutlineListView, AllDetached);
		}
		void				DetachedFromWindow() override {
			PYBIND11_OVERLOAD(void, BOutlineListView, DetachedFromWindow);
		}
};
	
PYBIND11_MODULE(OutlineListView,m)
{
py::class_<BOutlineListView,PyBOutlineListView, BListView>(m, "BOutlineListView")
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
.def("AddItem", py::overload_cast<BListItem *, int32>(&BOutlineListView::AddItem), "", py::arg("item"), py::arg("fullListIndex"))
.def("AddList", py::overload_cast<BList *>(&BOutlineListView::AddList), "", py::arg("newItems"))
.def("AddList", py::overload_cast<BList *, int32>(&BOutlineListView::AddList), "", py::arg("newItems"), py::arg("fullListIndex"))
.def("RemoveItem", py::overload_cast<BListItem *>(&BOutlineListView::RemoveItem), "", py::arg("item"))
.def("RemoveItem", py::overload_cast<int32>(&BOutlineListView::RemoveItem), "", py::arg("fullListIndex"))
.def("RemoveItems", &BOutlineListView::RemoveItems, "", py::arg("fullListIndex"), py::arg("count"))
.def("FullListItemAt", &BOutlineListView::FullListItemAt, "", py::arg("fullListIndex"))
.def("FullListIndexOf", py::overload_cast<BPoint>(&BOutlineListView::FullListIndexOf, py::const_), "", py::arg("where"))
.def("FullListIndexOf", py::overload_cast<BListItem *>(&BOutlineListView::FullListIndexOf, py::const_), "", py::arg("item"))
.def("FullListFirstItem", &BOutlineListView::FullListFirstItem, "")
.def("FullListLastItem", &BOutlineListView::FullListLastItem, "")
.def("FullListHasItem", &BOutlineListView::FullListHasItem, "", py::arg("item"))
.def("FullListCountItems", &BOutlineListView::FullListCountItems, "")
.def("FullListCurrentSelection", &BOutlineListView::FullListCurrentSelection, "", py::arg("index")=0)
.def("MakeEmpty", &BOutlineListView::MakeEmpty, "")
.def("FullListIsEmpty", &BOutlineListView::FullListIsEmpty, "")
//.def("FullListDoForEach", py::overload_cast<bool(*func)(BListItem*item)>(&BOutlineListView::FullListDoForEach), "", py::arg(""))
//.def("FullListDoForEach", py::overload_cast<bool(*func)(BListItem*item,void*arg), void *>(&BOutlineListView::FullListDoForEach), "", py::arg(""), py::arg("arg"))
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
