#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/ListView.h>
#include <Invoker.h>
#include <List.h>
#include <ListItem.h>
#include <View.h>
#include <ScrollView.h>
#include <Font.h>

namespace py = pybind11;
//py::list convertBListItemsToPythonList(BListItem** items);
//py::list convertBListItemsToPythonList(const BListItem* const* items);
py::list convertBListItemsToPythonList(const BListItem* const* items, long count) {
    py::list result;

    for (long i = 0; i < count; ++i) {
        // Aggiungi ogni elemento della lista alla lista Python
        result.append(items[i]);
    }

    return result;
}

bool CallPythonFunction(BListItem* item, py::function& func) {
    // Chiamare la funzione Python passando l'elemento
    // Questo richiede la conversione tra tipi C++ e Python
    // Includere eventuali conversioni necessarie qui

    // Esempio di chiamata della funzione Python
    py::object result = func(item);

    // Convertire il risultato della funzione Python in un booleano
    return py::cast<bool>(result);
}

PYBIND11_MODULE(ListView,m)
{
py::enum_<list_view_type>(m, "list_view_type", "")
.value("B_SINGLE_SELECTION_LIST", list_view_type::B_SINGLE_SELECTION_LIST, "")
.value("B_MULTIPLE_SELECTION_LIST", list_view_type::B_MULTIPLE_SELECTION_LIST, "")
.export_values();

py::class_<BListView, BView, BInvoker,std::unique_ptr<BListView, py::nodelete>>(m, "BListView")
.def(py::init<BRect, const char *, list_view_type, unsigned int, unsigned int>(), "", py::arg("frame"), py::arg("name"), py::arg("type")=B_SINGLE_SELECTION_LIST, py::arg("resizeMask")=B_FOLLOW_LEFT_TOP, py::arg("flags")=B_WILL_DRAW | B_FRAME_EVENTS | B_NAVIGABLE)
.def(py::init<const char *, list_view_type, unsigned int>(), "", py::arg("name"), py::arg("type")=B_SINGLE_SELECTION_LIST, py::arg("flags")=B_WILL_DRAW | B_FRAME_EVENTS | B_NAVIGABLE)
.def(py::init<list_view_type>(), "", py::arg("type")=B_SINGLE_SELECTION_LIST)
.def(py::init<BMessage *>(), "", py::arg("data"))
.def_static("Instantiate", &BListView::Instantiate, "", py::arg("data"))
.def("Archive", &BListView::Archive, "", py::arg("data"), py::arg("deep")=true)
.def("Draw", &BListView::Draw, "", py::arg("updateRect"))
.def("AttachedToWindow", &BListView::AttachedToWindow, "")
.def("DetachedFromWindow", &BListView::DetachedFromWindow, "")
.def("AllAttached", &BListView::AllAttached, "")
.def("AllDetached", &BListView::AllDetached, "")
.def("FrameResized", &BListView::FrameResized, "", py::arg("newWidth"), py::arg("newHeight"))
.def("FrameMoved", &BListView::FrameMoved, "", py::arg("newPosition"))
.def("TargetedByScrollView", &BListView::TargetedByScrollView, "", py::arg("view"))
.def("WindowActivated", &BListView::WindowActivated, "", py::arg("active"))
.def("MessageReceived", &BListView::MessageReceived, "", py::arg("message"))
.def("KeyDown", &BListView::KeyDown, "", py::arg("bytes"), py::arg("numBytes"))
.def("MouseDown", &BListView::MouseDown, "", py::arg("where"))
.def("MouseUp", &BListView::MouseUp, "", py::arg("where"))
.def("MouseMoved", &BListView::MouseMoved, "", py::arg("where"), py::arg("code"), py::arg("dragMessage"))
.def("ResizeToPreferred", &BListView::ResizeToPreferred, "")
.def("GetPreferredSize", &BListView::GetPreferredSize, "", py::arg("_width"), py::arg("_height"))
.def("MinSize", &BListView::MinSize, "")
.def("MaxSize", &BListView::MaxSize, "")
.def("PreferredSize", &BListView::PreferredSize, "")
.def("MakeFocus", &BListView::MakeFocus, "", py::arg("state")=true)
.def("SetFont", &BListView::SetFont, "", py::arg("font"), py::arg("mask")=511)
//B_FONT_ALL) Hardcoded 511 if not on import it gives ImportError: arg(): could not convert default argument 'mask: set_font_mask'
.def("ScrollTo", py::overload_cast<BPoint>(&BListView::ScrollTo), "", py::arg("where"))
.def("ScrollTo", py::overload_cast<float, float>(&BListView::ScrollTo), "", py::arg("x"), py::arg("y"))
.def("AddItem", py::overload_cast<BListItem *>(&BListView::AddItem), "", py::arg("item"))
.def("AddItem", py::overload_cast<BListItem *, int32>(&BListView::AddItem), "", py::arg("item"), py::arg("atIndex"))
.def("AddList", py::overload_cast<BList *>(&BListView::AddList), "", py::arg("newItems"))
.def("AddList", py::overload_cast<BList *, int32>(&BListView::AddList), "", py::arg("newItems"), py::arg("atIndex"))
.def("RemoveItem", py::overload_cast<BListItem *>(&BListView::RemoveItem), "", py::arg("item"))
.def("RemoveItem", py::overload_cast<int32>(&BListView::RemoveItem), "", py::arg("index"))
.def("RemoveItems", &BListView::RemoveItems, "", py::arg("index"), py::arg("count"))
.def("SetSelectionMessage", &BListView::SetSelectionMessage, "", py::arg("message"))
.def("SetInvocationMessage", &BListView::SetInvocationMessage, "", py::arg("message"))
.def("SelectionMessage", &BListView::SelectionMessage, "")
.def("SelectionCommand", &BListView::SelectionCommand, "")
.def("InvocationMessage", &BListView::InvocationMessage, "")
.def("InvocationCommand", &BListView::InvocationCommand, "")
.def("SetListType", &BListView::SetListType, "", py::arg("type"))
.def("ListType", &BListView::ListType, "")
.def("ItemAt", &BListView::ItemAt, "", py::arg("index"))
//.def("IndexOf", py::overload_cast<BPoint>(&BListView::IndexOf), "", py::arg("point"))
.def("IndexOf", static_cast<int32 (BListView::*)(BPoint) const>(&BListView::IndexOf), "", py::arg("point"))
//.def("IndexOf", py::overload_cast<BListItem *>(&BListView::IndexOf), "", py::arg("item"))
.def("IndexOf",static_cast<int32 (BListView::*)(BListItem*) const>(&BListView::IndexOf), "", py::arg("item"))
.def("FirstItem", &BListView::FirstItem, "")
.def("LastItem", &BListView::LastItem, "")
.def("HasItem", &BListView::HasItem, "", py::arg("item"))
.def("CountItems", &BListView::CountItems, "")
.def("MakeEmpty", &BListView::MakeEmpty, "")
.def("IsEmpty", &BListView::IsEmpty, "")
//.def("DoForEach", py::overload_cast<bool(*func)(BListItem*item)>(&BListView::DoForEach), "", py::arg(""))

.def("DoForEach", [](BListView& self, py::function& func) -> void {
            // Utilizzare una lambda expression per chiamare la funzione Python per ogni elemento
            self.DoForEach(static_cast<bool (*)(BListItem*, void*)>(+[](BListItem* item, void* userData) -> bool {
                return CallPythonFunction(item, *static_cast<py::function*>(userData));
            }), &func);
        }, "", py::arg("func"))

//.def("DoForEach", py::overload_cast<bool(*func)(BListItem*item,void*arg), void *>(&BListView::DoForEach), "", py::arg(""), py::arg("arg"))

.def("DoForEach", [](BListView& self, py::function& func, void* arg) -> void {
            // Utilizzare una lambda expression per chiamare la funzione Python per ogni elemento
            self.DoForEach(static_cast<bool (*)(BListItem*, void*)>(+[](BListItem* item, void* userData) -> bool {
                return CallPythonFunction(item, *static_cast<py::function*>(userData));
            }), arg);
        }, "", py::arg("func"), py::arg("arg"))

//.def("Items", &BListView::Items, "")
.def("Items", [](BListView& self) {
            const BListItem** items = self.Items();
            long count = self.CountItems();
            return convertBListItemsToPythonList(items, count);
        }, "")
.def("InvalidateItem", &BListView::InvalidateItem, "", py::arg("index"))
.def("ScrollToSelection", &BListView::ScrollToSelection, "")
.def("Select", py::overload_cast<int32, bool>(&BListView::Select), "", py::arg("index"), py::arg("extend")=false)
.def("Select", py::overload_cast<int32, int32, bool>(&BListView::Select), "", py::arg("from"), py::arg("to"), py::arg("extend")=false)
.def("IsItemSelected", &BListView::IsItemSelected, "", py::arg("index"))
.def("CurrentSelection", &BListView::CurrentSelection, "", py::arg("index")=0)
.def("Invoke", &BListView::Invoke, "", py::arg("message")=NULL)
.def("DeselectAll", &BListView::DeselectAll, "")
.def("DeselectExcept", &BListView::DeselectExcept, "", py::arg("exceptFrom"), py::arg("exceptTo"))
.def("Deselect", &BListView::Deselect, "", py::arg("index"))
.def("SelectionChanged", &BListView::SelectionChanged, "")
.def("InitiateDrag", &BListView::InitiateDrag, "", py::arg("where"), py::arg("index"), py::arg("wasSelected"))
.def("SortItems", &BListView::SortItems, "", py::arg(""))
.def("SwapItems", &BListView::SwapItems, "", py::arg("a"), py::arg("b"))
.def("MoveItem", &BListView::MoveItem, "", py::arg("from"), py::arg("to"))
.def("ReplaceItem", &BListView::ReplaceItem, "", py::arg("index"), py::arg("item"))
.def("ItemFrame", &BListView::ItemFrame, "", py::arg("index"))
.def("ResolveSpecifier", &BListView::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("what"), py::arg("property"))
.def("GetSupportedSuites", &BListView::GetSupportedSuites, "", py::arg("data"))
.def("Perform", &BListView::Perform, "", py::arg("code"), py::arg("arg"))
;
/*
py::class_<union MiscData>(m, "union MiscData")
.def_readwrite("replace", &union MiscData::replace, "")
.def_readwrite("move", &union MiscData::move, "")
.def_readwrite("swap", &union MiscData::swap, "")
;

py::class_<Spare>(m, "Spare")
.def_readwrite("data", &Spare::data, "")
;

py::class_<Replace>(m, "Replace")
.def_readwrite("index", &Replace::index, "")
.def_readwrite("item", &Replace::item, "")
;

py::class_<Move>(m, "Move")
.def_readwrite("from", &Move::from, "")
.def_readwrite("to", &Move::to, "")
;

py::class_<Swap>(m, "Swap")
.def_readwrite("a", &Swap::a, "")
.def_readwrite("b", &Swap::b, "")
;

*/
}
