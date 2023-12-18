#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/ListItem.h>
#include <Archivable.h>
#include <Rect.h>
#include <StringItem.h>
#include <View.h>
#include <Font.h>
#include <OutlineListView.h>
#include <Message.h>
#include <List.h>

namespace py = pybind11;

class PyBListItem : public BListItem {
public:
    using BListItem::BListItem;
    status_t			Archive(BMessage* archive, bool deep = true) const override {
        	PYBIND11_OVERLOAD(status_t, BListItem, Archive, archive, deep);
        }
    void				SetEnabled(bool enabled) override {
            PYBIND11_OVERLOAD(void, BListItem, SetEnabled, enabled);
        }
    void 				DrawItem(BView* owner, BRect itemRect, bool drawEverything) override {
        PYBIND11_OVERLOAD_PURE(void, BListItem, DrawItem, owner, itemRect, drawEverything);
    }
    void				Update(BView* owner, const BFont* font) override {
            PYBIND11_OVERLOAD(void, BListItem, Update, owner, font);
        }
    status_t			Perform(perform_code code, void* arg) override {
            PYBIND11_OVERLOAD(status_t, BListItem, Perform, code, arg);
        }
    
private:
    BListItem* item_;
};


PYBIND11_MODULE(ListItem,m)
{
//py::class_<BListItem, BArchivable>(m, "BListItem")
py::class_<BListItem, PyBListItem, BArchivable, std::unique_ptr<BListItem, py::nodelete>>(m, "BListItem")
.def(py::init<uint32, bool>(), "", py::arg("outlineLevel")=0, py::arg("expanded")=true)
.def(py::init<BMessage *>(), "", py::arg("archive"))
.def("Archive", &BListItem::Archive, "", py::arg("archive"), py::arg("deep")=true)
.def("Height", &BListItem::Height, "")
.def("Width", &BListItem::Width, "")
.def("IsSelected", &BListItem::IsSelected, "")
.def("Select", &BListItem::Select, "")
.def("Deselect", &BListItem::Deselect, "")
.def("SetEnabled", &BListItem::SetEnabled, "", py::arg("enabled"))
.def("IsEnabled", &BListItem::IsEnabled, "")
.def("SetHeight", &BListItem::SetHeight, "", py::arg("height"))
.def("SetWidth", &BListItem::SetWidth, "", py::arg("width"))
.def("DrawItem", &BListItem::DrawItem, "", py::arg("owner"), py::arg("frame"), py::arg("complete")=false)
//.def("DrawItem", &PyBListItem::DrawItem, "", py::arg("owner"), py::arg("frame"), py::arg("complete")=false)
//.def("DrawItem", &PyBListItemWrapper::DrawItemWrapper, "", py::arg("owner"), py::arg("itemRect"), py::arg("drawEverything") = false)
.def("Update", &BListItem::Update, "", py::arg("owner"), py::arg("font"))
.def("IsExpanded", &BListItem::IsExpanded, "")
.def("SetExpanded", &BListItem::SetExpanded, "", py::arg("expanded"))
.def("OutlineLevel", &BListItem::OutlineLevel, "")
.def("SetOutlineLevel", &BListItem::SetOutlineLevel, "", py::arg("level"))
.def("Perform", &BListItem::Perform, "", py::arg("code"), py::arg("arg"))
;


}
