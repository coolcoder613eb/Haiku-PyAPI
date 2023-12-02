#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/GridLayout.h>
#include <TwoDimensionalLayout.h>
#include <View.h>
#include <InterfaceDefs.h>


namespace py = pybind11;

class PyBGridLayout : public BGridLayout{
	public:
        using BGridLayout::BGridLayout;
        BLayoutItem*		AddView(BView* child) override {
            PYBIND11_OVERLOAD(BLayoutItem*, BGridLayout, AddView, child);
        }
        BLayoutItem*		AddView(int32 index, BView* child) override {
            PYBIND11_OVERLOAD(BLayoutItem*, BGridLayout, AddView, index, child);
        }
        BLayoutItem*		AddView(BView* child, int32 column, int32 row, int32 columnCount = 1, int32 rowCount = 1) override {
            PYBIND11_OVERLOAD(BLayoutItem*, BGridLayout, AddView, child, column, row, columnCount, rowCount);
        }
        bool				AddItem(BLayoutItem* item) override {
            PYBIND11_OVERLOAD(bool, BGridLayout, AddItem, item);
        }
        bool				AddItem(int32 index, BLayoutItem* item) override {
            PYBIND11_OVERLOAD(bool, BGridLayout, AddItem, index, item);
        }
        bool				AddItem(BLayoutItem* item, int32 column, int32 row, int32 columnCount = 1, int32 rowCount = 1) override {
            PYBIND11_OVERLOAD(bool, BGridLayout, AddItem, item, column, row, columnCount, rowCount);
        }
        status_t			Archive(BMessage* into, bool deep = true) const override {
        	PYBIND11_OVERLOAD(status_t, BGridLayout, Archive, into, deep);
        }
        status_t			Perform(perform_code d, void* arg) override {
            PYBIND11_OVERLOAD(status_t, BGridLayout, Perform, d, arg);
        }
};

PYBIND11_MODULE(GridLayout,m)
{
py::class_<BGridLayout, PyBGridLayout, BTwoDimensionalLayout, std::unique_ptr<BGridLayout,py::nodelete>>(m, "BGridLayout")
// ImportError: arg(): could not convert default argument 'horizontal: ._anon_253' in method '<class 'Be.GridLayout.BGridLayout'>.__init__' into a Python object (type not registered yet?)
.def(py::init<float, float>(), "", py::arg("horizontal")=py::int_(-1002), py::arg("vertical")=py::int_(-1002))
.def(py::init<BMessage *>(), "", py::arg("from"))
.def("CountColumns", &BGridLayout::CountColumns, "")
.def("CountRows", &BGridLayout::CountRows, "")
.def("HorizontalSpacing", &BGridLayout::HorizontalSpacing, "")
.def("VerticalSpacing", &BGridLayout::VerticalSpacing, "")
.def("SetHorizontalSpacing", &BGridLayout::SetHorizontalSpacing, "", py::arg("spacing"))
.def("SetVerticalSpacing", &BGridLayout::SetVerticalSpacing, "", py::arg("spacing"))
.def("SetSpacing", &BGridLayout::SetSpacing, "", py::arg("horizontal"), py::arg("vertical"))
.def("ColumnWeight", &BGridLayout::ColumnWeight, "", py::arg("column"))
.def("SetColumnWeight", &BGridLayout::SetColumnWeight, "", py::arg("column"), py::arg("weight"))
.def("MinColumnWidth", &BGridLayout::MinColumnWidth, "", py::arg("column"))
.def("SetMinColumnWidth", &BGridLayout::SetMinColumnWidth, "", py::arg("column"), py::arg("width"))
.def("MaxColumnWidth", &BGridLayout::MaxColumnWidth, "", py::arg("column"))
.def("SetMaxColumnWidth", &BGridLayout::SetMaxColumnWidth, "", py::arg("column"), py::arg("width"))
.def("RowWeight", &BGridLayout::RowWeight, "", py::arg("row"))
.def("SetRowWeight", &BGridLayout::SetRowWeight, "", py::arg("row"), py::arg("weight"))
.def("MinRowHeight", &BGridLayout::MinRowHeight, "", py::arg("row"))
.def("SetMinRowHeight", &BGridLayout::SetMinRowHeight, "", py::arg("row"), py::arg("height"))
.def("MaxRowHeight", &BGridLayout::MaxRowHeight, "", py::arg("row"))
.def("SetMaxRowHeight", &BGridLayout::SetMaxRowHeight, "", py::arg("row"), py::arg("height"))
.def("ItemAt", &BGridLayout::ItemAt, "", py::arg("column"), py::arg("row"))
.def("AddView", py::overload_cast<BView *>(&BGridLayout::AddView), "", py::arg("child"))
.def("AddView", py::overload_cast<int32, BView *>(&BGridLayout::AddView), "", py::arg("index"), py::arg("child"))
.def("AddView", py::overload_cast<BView *, int32, int32, int32, int32>(&BGridLayout::AddView), "", py::arg("child"), py::arg("column"), py::arg("row"), py::arg("columnCount")=1, py::arg("rowCount")=1)
.def("AddItem", py::overload_cast<BLayoutItem *>(&BGridLayout::AddItem), "", py::arg("item"))
.def("AddItem", py::overload_cast<int32, BLayoutItem *>(&BGridLayout::AddItem), "", py::arg("index"), py::arg("item"))
.def("AddItem", py::overload_cast<BLayoutItem *, int32, int32, int32, int32>(&BGridLayout::AddItem), "", py::arg("item"), py::arg("column"), py::arg("row"), py::arg("columnCount")=1, py::arg("rowCount")=1)
.def("Archive", &BGridLayout::Archive, "", py::arg("into"), py::arg("deep")=true)
.def_static("Instantiate", &BGridLayout::Instantiate, "", py::arg("from"))
.def("Perform", &BGridLayout::Perform, "", py::arg("d"), py::arg("arg"))
;


}
