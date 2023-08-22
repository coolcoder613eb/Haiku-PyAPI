#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/LayoutBuilder.h>
#include <new>
#include <CardLayout.h>
#include <CardView.h>
#include <GridLayout.h>
#include <GridView.h>
#include <GroupLayout.h>
#include <GroupView.h>
#include <Menu.h>
#include <MenuField.h>
#include <MenuItem.h>
#include <SpaceLayoutItem.h>
#include <SplitView.h>
#include <TextControl.h>
#include <Window.h>

namespace py = pybind11;
using namespace BLayoutBuilder;

PYBIND11_MODULE(LayoutBuilder,m)
{
py::class_<Base>(m, "Base")
.def("SetParent", &Base::SetParent, "", py::arg("parent"))
.def("End", &Base::End, "")
;

py::class_<Group, Base<ParentBuilder>>(m, "Group")
.def(py::init<orientation, float>(), "", py::arg("orientation")=B_HORIZONTAL, py::arg("spacing")=B_USE_DEFAULT_SPACING)
.def(py::init<BWindow *, orientation, float>(), "", py::arg("window"), py::arg("orientation")=B_HORIZONTAL, py::arg("spacing")=B_USE_DEFAULT_SPACING)
.def(py::init<BView *, orientation, float>(), "", py::arg("view"), py::arg("orientation")=B_HORIZONTAL, py::arg("spacing")=B_USE_DEFAULT_SPACING)
.def(py::init<BGroupLayout *>(), "", py::arg("layout"))
.def(py::init<BGroupView *>(), "", py::arg("view"))
.def("Layout", &Group::Layout, "")
.def("View", &Group::View, "")
.def("GetLayout", &Group::GetLayout, "", py::arg("_layout"))
.def("GetView", &Group::GetView, "", py::arg("_view"))
.def("Add", py::overload_cast<BView *>(&Group::Add), "", py::arg("view"))
.def("Add", py::overload_cast<BView *, float>(&Group::Add), "", py::arg("view"), py::arg("weight"))
.def("Add", py::overload_cast<BLayoutItem *>(&Group::Add), "", py::arg("item"))
.def("Add", py::overload_cast<BLayoutItem *, float>(&Group::Add), "", py::arg("item"), py::arg("weight"))
.def("AddGroup", py::overload_cast<orientation, float, float>(&Group::AddGroup), "", py::arg("orientation"), py::arg("spacing")=B_USE_DEFAULT_SPACING, py::arg("weight")=1.0 f)
.def("AddGroup", py::overload_cast<BGroupView *, float>(&Group::AddGroup), "", py::arg("groupView"), py::arg("weight")=1.0 f)
.def("AddGroup", py::overload_cast<BGroupLayout *, float>(&Group::AddGroup), "", py::arg("groupLayout"), py::arg("weight")=1.0 f)
.def("AddGrid", py::overload_cast<float, float, float>(&Group::AddGrid), "", py::arg("horizontal")=B_USE_DEFAULT_SPACING, py::arg("vertical")=B_USE_DEFAULT_SPACING, py::arg("weight")=1.0 f)
.def("AddGrid", py::overload_cast<BGridLayout *, float>(&Group::AddGrid), "", py::arg("gridLayout"), py::arg("weight")=1.0 f)
.def("AddGrid", py::overload_cast<BGridView *, float>(&Group::AddGrid), "", py::arg("gridView"), py::arg("weight")=1.0 f)
.def("AddSplit", py::overload_cast<orientation, float, float>(&Group::AddSplit), "", py::arg("orientation"), py::arg("spacing")=B_USE_DEFAULT_SPACING, py::arg("weight")=1.0 f)
.def("AddSplit", py::overload_cast<BSplitView *, float>(&Group::AddSplit), "", py::arg("splitView"), py::arg("weight")=1.0 f)
.def("AddCards", py::overload_cast<float>(&Group::AddCards), "", py::arg("weight")=1.0 f)
.def("AddCards", py::overload_cast<BCardLayout *, float>(&Group::AddCards), "", py::arg("cardLayout"), py::arg("weight")=1.0 f)
.def("AddCards", py::overload_cast<BCardView *, float>(&Group::AddCards), "", py::arg("cardView"), py::arg("weight")=1.0 f)
.def("AddGlue", &Group::AddGlue, "", py::arg("weight")=1.0 f)
.def("AddStrut", &Group::AddStrut, "", py::arg("size"))
.def("SetInsets", py::overload_cast<float, float, float, float>(&Group::SetInsets), "", py::arg("left"), py::arg("top"), py::arg("right"), py::arg("bottom"))
.def("SetInsets", py::overload_cast<float, float>(&Group::SetInsets), "", py::arg("horizontal"), py::arg("vertical"))
.def("SetInsets", py::overload_cast<float>(&Group::SetInsets), "", py::arg("insets"))
.def("SetExplicitMinSize", &Group::SetExplicitMinSize, "", py::arg("size"))
.def("SetExplicitMaxSize", &Group::SetExplicitMaxSize, "", py::arg("size"))
.def("SetExplicitPreferredSize", &Group::SetExplicitPreferredSize, "", py::arg("size"))
.def("SetExplicitAlignment", &Group::SetExplicitAlignment, "", py::arg("alignment"))
.def("operatorBGroupLayout*", &Group::operatorBGroupLayout*, "")
;

py::class_<Grid, Base<ParentBuilder>>(m, "Grid")
.def(py::init<float, float>(), "", py::arg("horizontal")=B_USE_DEFAULT_SPACING, py::arg("vertical")=B_USE_DEFAULT_SPACING)
.def(py::init<BWindow *, float, float>(), "", py::arg("window"), py::arg("horizontal")=B_USE_DEFAULT_SPACING, py::arg("vertical")=B_USE_DEFAULT_SPACING)
.def(py::init<BView *, float, float>(), "", py::arg("view"), py::arg("horizontal")=B_USE_DEFAULT_SPACING, py::arg("vertical")=B_USE_DEFAULT_SPACING)
.def(py::init<BGridLayout *>(), "", py::arg("layout"))
.def(py::init<BGridView *>(), "", py::arg("view"))
.def("Layout", &Grid::Layout, "")
.def("View", &Grid::View, "")
.def("GetLayout", &Grid::GetLayout, "", py::arg("_layout"))
.def("GetView", &Grid::GetView, "", py::arg("_view"))
.def("Add", py::overload_cast<BView *, int, int, int, int>(&Grid::Add), "", py::arg("view"), py::arg("column"), py::arg("row"), py::arg("columnCount")=1, py::arg("rowCount")=1)
.def("Add", py::overload_cast<BLayoutItem *, int, int, int, int>(&Grid::Add), "", py::arg("item"), py::arg("column"), py::arg("row"), py::arg("columnCount")=1, py::arg("rowCount")=1)
.def("AddMenuField", &Grid::AddMenuField, "", py::arg("menuField"), py::arg("column"), py::arg("row"), py::arg("labelAlignment")=B_ALIGN_HORIZONTAL_UNSET, py::arg("labelColumnCount")=1, py::arg("fieldColumnCount")=1, py::arg("rowCount")=1)
.def("AddTextControl", &Grid::AddTextControl, "", py::arg("textControl"), py::arg("column"), py::arg("row"), py::arg("labelAlignment")=B_ALIGN_HORIZONTAL_UNSET, py::arg("labelColumnCount")=1, py::arg("textColumnCount")=1, py::arg("rowCount")=1)
.def("AddGroup", py::overload_cast<orientation, float, int, int, int, int>(&Grid::AddGroup), "", py::arg("orientation"), py::arg("spacing"), py::arg("column"), py::arg("row"), py::arg("columnCount")=1, py::arg("rowCount")=1)
.def("AddGroup", py::overload_cast<BGroupView *, int, int, int, int>(&Grid::AddGroup), "", py::arg("groupView"), py::arg("column"), py::arg("row"), py::arg("columnCount")=1, py::arg("rowCount")=1)
.def("AddGroup", py::overload_cast<BGroupLayout *, int, int, int, int>(&Grid::AddGroup), "", py::arg("groupLayout"), py::arg("column"), py::arg("row"), py::arg("columnCount")=1, py::arg("rowCount")=1)
.def("AddGrid", py::overload_cast<float, float, int, int, int, int>(&Grid::AddGrid), "", py::arg("horizontalSpacing"), py::arg("verticalSpacing"), py::arg("column"), py::arg("row"), py::arg("columnCount")=1, py::arg("rowCount")=1)
.def("AddGrid", py::overload_cast<BGridLayout *, int, int, int, int>(&Grid::AddGrid), "", py::arg("gridLayout"), py::arg("column"), py::arg("row"), py::arg("columnCount")=1, py::arg("rowCount")=1)
.def("AddGrid", py::overload_cast<BGridView *, int, int, int, int>(&Grid::AddGrid), "", py::arg("gridView"), py::arg("column"), py::arg("row"), py::arg("columnCount")=1, py::arg("rowCount")=1)
.def("AddSplit", py::overload_cast<orientation, float, int, int, int, int>(&Grid::AddSplit), "", py::arg("orientation"), py::arg("spacing"), py::arg("column"), py::arg("row"), py::arg("columnCount")=1, py::arg("rowCount")=1)
.def("AddSplit", py::overload_cast<BSplitView *, int, int, int, int>(&Grid::AddSplit), "", py::arg("splitView"), py::arg("column"), py::arg("row"), py::arg("columnCount")=1, py::arg("rowCount")=1)
.def("AddCards", py::overload_cast<int, int, int, int>(&Grid::AddCards), "", py::arg("column"), py::arg("row"), py::arg("columnCount")=1, py::arg("rowCount")=1)
.def("AddCards", py::overload_cast<BCardLayout *, int, int, int, int>(&Grid::AddCards), "", py::arg("cardLayout"), py::arg("column"), py::arg("row"), py::arg("columnCount")=1, py::arg("rowCount")=1)
.def("AddCards", py::overload_cast<BCardView *, int, int, int, int>(&Grid::AddCards), "", py::arg("cardView"), py::arg("column"), py::arg("row"), py::arg("columnCount")=1, py::arg("rowCount")=1)
.def("AddGlue", &Grid::AddGlue, "", py::arg("column"), py::arg("row"), py::arg("columnCount")=1, py::arg("rowCount")=1)
.def("SetHorizontalSpacing", &Grid::SetHorizontalSpacing, "", py::arg("spacing"))
.def("SetVerticalSpacing", &Grid::SetVerticalSpacing, "", py::arg("spacing"))
.def("SetSpacing", &Grid::SetSpacing, "", py::arg("horizontal"), py::arg("vertical"))
.def("SetColumnWeight", &Grid::SetColumnWeight, "", py::arg("column"), py::arg("weight"))
.def("SetRowWeight", &Grid::SetRowWeight, "", py::arg("row"), py::arg("weight"))
.def("SetInsets", py::overload_cast<float, float, float, float>(&Grid::SetInsets), "", py::arg("left"), py::arg("top"), py::arg("right"), py::arg("bottom"))
.def("SetInsets", py::overload_cast<float, float>(&Grid::SetInsets), "", py::arg("horizontal"), py::arg("vertical"))
.def("SetInsets", py::overload_cast<float>(&Grid::SetInsets), "", py::arg("insets"))
.def("SetExplicitMinSize", &Grid::SetExplicitMinSize, "", py::arg("size"))
.def("SetExplicitMaxSize", &Grid::SetExplicitMaxSize, "", py::arg("size"))
.def("SetExplicitPreferredSize", &Grid::SetExplicitPreferredSize, "", py::arg("size"))
.def("SetExplicitAlignment", &Grid::SetExplicitAlignment, "", py::arg("alignment"))
.def("operatorBGridLayout*", &Grid::operatorBGridLayout*, "")
;

py::class_<Split, Base<ParentBuilder>>(m, "Split")
.def(py::init<orientation, float>(), "", py::arg("orientation")=B_HORIZONTAL, py::arg("spacing")=B_USE_DEFAULT_SPACING)
.def(py::init<BSplitView *>(), "", py::arg("view"))
.def("View", &Split::View, "")
.def("GetView", &Split::GetView, "", py::arg("_view"))
.def("GetSplitView", &Split::GetSplitView, "", py::arg("_view"))
.def("Add", py::overload_cast<BView *>(&Split::Add), "", py::arg("view"))
.def("Add", py::overload_cast<BView *, float>(&Split::Add), "", py::arg("view"), py::arg("weight"))
.def("Add", py::overload_cast<BLayoutItem *>(&Split::Add), "", py::arg("item"))
.def("Add", py::overload_cast<BLayoutItem *, float>(&Split::Add), "", py::arg("item"), py::arg("weight"))
.def("AddGroup", py::overload_cast<orientation, float, float>(&Split::AddGroup), "", py::arg("orientation"), py::arg("spacing")=B_USE_DEFAULT_SPACING, py::arg("weight")=1.0 f)
.def("AddGroup", py::overload_cast<BGroupView *, float>(&Split::AddGroup), "", py::arg("groupView"), py::arg("weight")=1.0 f)
.def("AddGroup", py::overload_cast<BGroupLayout *, float>(&Split::AddGroup), "", py::arg("groupLayout"), py::arg("weight")=1.0 f)
.def("AddGrid", py::overload_cast<float, float, float>(&Split::AddGrid), "", py::arg("horizontal")=B_USE_DEFAULT_SPACING, py::arg("vertical")=B_USE_DEFAULT_SPACING, py::arg("weight")=1.0 f)
.def("AddGrid", py::overload_cast<BGridView *, float>(&Split::AddGrid), "", py::arg("gridView"), py::arg("weight")=1.0 f)
.def("AddGrid", py::overload_cast<BGridLayout *, float>(&Split::AddGrid), "", py::arg("gridLayout"), py::arg("weight")=1.0 f)
.def("AddSplit", py::overload_cast<orientation, float, float>(&Split::AddSplit), "", py::arg("orientation"), py::arg("spacing")=B_USE_DEFAULT_SPACING, py::arg("weight")=1.0 f)
.def("AddSplit", py::overload_cast<BSplitView *, float>(&Split::AddSplit), "", py::arg("splitView"), py::arg("weight")=1.0 f)
.def("AddCards", py::overload_cast<float>(&Split::AddCards), "", py::arg("weight")=1.0 f)
.def("AddCards", py::overload_cast<BCardLayout *, float>(&Split::AddCards), "", py::arg("cardLayout"), py::arg("weight")=1.0 f)
.def("AddCards", py::overload_cast<BCardView *, float>(&Split::AddCards), "", py::arg("cardView"), py::arg("weight")=1.0 f)
.def("SetCollapsible", py::overload_cast<bool>(&Split::SetCollapsible), "", py::arg("collapsible"))
.def("SetCollapsible", py::overload_cast<int, bool>(&Split::SetCollapsible), "", py::arg("index"), py::arg("collapsible"))
.def("SetCollapsible", py::overload_cast<int, int, bool>(&Split::SetCollapsible), "", py::arg("first"), py::arg("last"), py::arg("collapsible"))
.def("SetInsets", py::overload_cast<float, float, float, float>(&Split::SetInsets), "", py::arg("left"), py::arg("top"), py::arg("right"), py::arg("bottom"))
.def("SetInsets", py::overload_cast<float, float>(&Split::SetInsets), "", py::arg("horizontal"), py::arg("vertical"))
.def("SetInsets", py::overload_cast<float>(&Split::SetInsets), "", py::arg("insets"))
.def("operatorBSplitView*", &Split::operatorBSplitView*, "")
;

py::class_<Cards, Base<ParentBuilder>>(m, "Cards")
.def(py::init(), "")
.def(py::init<BWindow *>(), "", py::arg("window"))
.def(py::init<BView *>(), "", py::arg("view"))
.def(py::init<BCardLayout *>(), "", py::arg("layout"))
.def(py::init<BCardView *>(), "", py::arg("view"))
.def("Layout", &Cards::Layout, "")
.def("View", &Cards::View, "")
.def("GetLayout", &Cards::GetLayout, "", py::arg("_layout"))
.def("GetView", &Cards::GetView, "", py::arg("_view"))
.def("Add", py::overload_cast<BView *>(&Cards::Add), "", py::arg("view"))
.def("Add", py::overload_cast<BLayoutItem *>(&Cards::Add), "", py::arg("item"))
.def("AddGroup", py::overload_cast<orientation, float>(&Cards::AddGroup), "", py::arg("orientation"), py::arg("spacing")=B_USE_DEFAULT_SPACING)
.def("AddGroup", py::overload_cast<BGroupView *>(&Cards::AddGroup), "", py::arg("groupView"))
.def("AddGroup", py::overload_cast<BGroupLayout *>(&Cards::AddGroup), "", py::arg("groupLayout"))
.def("AddGrid", py::overload_cast<float, float>(&Cards::AddGrid), "", py::arg("horizontal")=B_USE_DEFAULT_SPACING, py::arg("vertical")=B_USE_DEFAULT_SPACING)
.def("AddGrid", py::overload_cast<BGridLayout *>(&Cards::AddGrid), "", py::arg("gridLayout"))
.def("AddGrid", py::overload_cast<BGridView *>(&Cards::AddGrid), "", py::arg("gridView"))
.def("AddSplit", py::overload_cast<orientation, float>(&Cards::AddSplit), "", py::arg("orientation"), py::arg("spacing")=B_USE_DEFAULT_SPACING)
.def("AddSplit", py::overload_cast<BSplitView *>(&Cards::AddSplit), "", py::arg("splitView"))
.def("AddCards", py::overload_cast<>(&Cards::AddCards), "")
.def("AddCards", py::overload_cast<BCardLayout *>(&Cards::AddCards), "", py::arg("cardLayout"))
.def("AddCards", py::overload_cast<BCardView *>(&Cards::AddCards), "", py::arg("cardView"))
.def("SetExplicitMinSize", &Cards::SetExplicitMinSize, "", py::arg("size"))
.def("SetExplicitMaxSize", &Cards::SetExplicitMaxSize, "", py::arg("size"))
.def("SetExplicitPreferredSize", &Cards::SetExplicitPreferredSize, "", py::arg("size"))
.def("SetExplicitAlignment", &Cards::SetExplicitAlignment, "", py::arg("alignment"))
.def("SetVisibleItem", &Cards::SetVisibleItem, "", py::arg("index"))
.def("operatorBCardLayout*", &Cards::operatorBCardLayout*, "")
;

py::class_<Menu, Base<ParentBuilder>>(m, "Menu")
.def(py::init<BMenu *>(), "", py::arg("menu"))
.def("GetMenu", [](Menu& self) {
    BMenu *  _menu;
    inline ThisBuilder & r = self.GetMenu(_menu);
    return std::make_tuple(r,_menu);
}
, "")
.def("AddItem", py::overload_cast<BMenuItem *>(&Menu::AddItem), "", py::arg("item"))
.def("AddItem", py::overload_cast<BMenu *>(&Menu::AddItem), "", py::arg("menu"))
.def("AddItem", py::overload_cast<const char *, BMessage *, char, unsigned int>(&Menu::AddItem), "", py::arg("label"), py::arg("message"), py::arg("shortcut")=0, py::arg("modifiers")=0)
.def("AddItem", py::overload_cast<const char *, unsigned int, char, unsigned int>(&Menu::AddItem), "", py::arg("label"), py::arg("messageWhat"), py::arg("shortcut")=0, py::arg("modifiers")=0)
.def("AddMenu", py::overload_cast<BMenu *>(&Menu::AddMenu), "", py::arg("menu"))
.def("AddMenu", py::overload_cast<const char *, menu_layout>(&Menu::AddMenu), "", py::arg("title"), py::arg("layout")=B_ITEMS_IN_COLUMN)
.def("AddSeparator", &Menu::AddSeparator, "")
;

py::class_<MenuItem, Menu<ParentBuilder>>(m, "MenuItem")
.def(py::init<ParentBuilder *, BMenu *, BMenuItem *>(), "", py::arg("parentBuilder"), py::arg("menu"), py::arg("item"))
.def("GetItem", [](MenuItem& self) {
    BMenuItem *  _item;
    inline ThisBuilder & r = self.GetItem(_item);
    return std::make_tuple(r,_item);
}
, "")
.def("SetEnabled", &MenuItem::SetEnabled, "", py::arg("enabled"))
;

m.def("Base", &Base, "");

m.def("SetParent", &SetParent, "", py::arg("parent"));

m.def("End", &End, "");

m.def("Group", py::overload_cast<orientation, float>(&Group), "", py::arg("orientation"), py::arg("spacing"));

m.def("Group", py::overload_cast<BWindow *, orientation, float>(&Group), "", py::arg("window"), py::arg("orientation"), py::arg("spacing"));

m.def("Group", py::overload_cast<BView *, orientation, float>(&Group), "", py::arg("view"), py::arg("orientation"), py::arg("spacing"));

m.def("Group", py::overload_cast<BGroupLayout *>(&Group), "", py::arg("layout"));

m.def("Group", py::overload_cast<BGroupView *>(&Group), "", py::arg("view"));

m.def("Layout", py::overload_cast<>(&Layout), "");

m.def("View", py::overload_cast<>(&View), "");

m.def("GetLayout", py::overload_cast<BGroupLayout * *>(&GetLayout), "", py::arg("_layout"));

m.def("GetView", py::overload_cast<BView * *>(&GetView), "", py::arg("_view"));

m.def("Add", py::overload_cast<BView *>(&Add), "", py::arg("view"));

m.def("Add", py::overload_cast<BView *, float>(&Add), "", py::arg("view"), py::arg("weight"));

m.def("Add", py::overload_cast<BLayoutItem *>(&Add), "", py::arg("item"));

m.def("Add", py::overload_cast<BLayoutItem *, float>(&Add), "", py::arg("item"), py::arg("weight"));

m.def("AddGroup", py::overload_cast<orientation, float, float>(&AddGroup), "", py::arg("orientation"), py::arg("spacing"), py::arg("weight"));

m.def("AddGroup", py::overload_cast<BGroupView *, float>(&AddGroup), "", py::arg("groupView"), py::arg("weight"));

m.def("AddGroup", py::overload_cast<BGroupLayout *, float>(&AddGroup), "", py::arg("groupLayout"), py::arg("weight"));

m.def("AddGrid", py::overload_cast<float, float, float>(&AddGrid), "", py::arg("horizontalSpacing"), py::arg("verticalSpacing"), py::arg("weight"));

m.def("AddGrid", py::overload_cast<BGridLayout *, float>(&AddGrid), "", py::arg("gridLayout"), py::arg("weight"));

m.def("AddGrid", py::overload_cast<BGridView *, float>(&AddGrid), "", py::arg("gridView"), py::arg("weight"));

m.def("AddSplit", py::overload_cast<orientation, float, float>(&AddSplit), "", py::arg("orientation"), py::arg("spacing"), py::arg("weight"));

m.def("AddSplit", py::overload_cast<BSplitView *, float>(&AddSplit), "", py::arg("splitView"), py::arg("weight"));

m.def("AddCards", py::overload_cast<float>(&AddCards), "", py::arg("weight"));

m.def("AddCards", py::overload_cast<BCardLayout *, float>(&AddCards), "", py::arg("cardLayout"), py::arg("weight"));

m.def("AddCards", py::overload_cast<BCardView *, float>(&AddCards), "", py::arg("cardView"), py::arg("weight"));

m.def("AddGlue", py::overload_cast<float>(&AddGlue), "", py::arg("weight"));

m.def("AddStrut", &AddStrut, "", py::arg("size"));

m.def("SetInsets", py::overload_cast<float, float, float, float>(&SetInsets), "", py::arg("left"), py::arg("top"), py::arg("right"), py::arg("bottom"));

m.def("SetInsets", py::overload_cast<float, float>(&SetInsets), "", py::arg("horizontal"), py::arg("vertical"));

m.def("SetInsets", py::overload_cast<float>(&SetInsets), "", py::arg("insets"));

m.def("SetExplicitMinSize", py::overload_cast<BSize>(&SetExplicitMinSize), "", py::arg("size"));

m.def("SetExplicitMaxSize", py::overload_cast<BSize>(&SetExplicitMaxSize), "", py::arg("size"));

m.def("SetExplicitPreferredSize", py::overload_cast<BSize>(&SetExplicitPreferredSize), "", py::arg("size"));

m.def("SetExplicitAlignment", py::overload_cast<BAlignment>(&SetExplicitAlignment), "", py::arg("alignment"));

m.def("operatorBGroupLayout*", &operatorBGroupLayout*, "");

m.def("Grid", py::overload_cast<float, float>(&Grid), "", py::arg("horizontalSpacing"), py::arg("verticalSpacing"));

m.def("Grid", py::overload_cast<BWindow *, float, float>(&Grid), "", py::arg("window"), py::arg("horizontalSpacing"), py::arg("verticalSpacing"));

m.def("Grid", py::overload_cast<BView *, float, float>(&Grid), "", py::arg("view"), py::arg("horizontalSpacing"), py::arg("verticalSpacing"));

m.def("Grid", py::overload_cast<BGridLayout *>(&Grid), "", py::arg("layout"));

m.def("Grid", py::overload_cast<BGridView *>(&Grid), "", py::arg("view"));

m.def("Layout", py::overload_cast<>(&Layout), "");

m.def("View", py::overload_cast<>(&View), "");

m.def("GetLayout", py::overload_cast<BGridLayout * *>(&GetLayout), "", py::arg("_layout"));

m.def("GetView", py::overload_cast<BView * *>(&GetView), "", py::arg("_view"));

m.def("Add", py::overload_cast<BView *, int, int, int, int>(&Add), "", py::arg("view"), py::arg("column"), py::arg("row"), py::arg("columnCount"), py::arg("rowCount"));

m.def("Add", py::overload_cast<BLayoutItem *, int, int, int, int>(&Add), "", py::arg("item"), py::arg("column"), py::arg("row"), py::arg("columnCount"), py::arg("rowCount"));

m.def("AddMenuField", &AddMenuField, "", py::arg("menuField"), py::arg("column"), py::arg("row"), py::arg("labelAlignment"), py::arg("labelColumnCount"), py::arg("fieldColumnCount"), py::arg("rowCount"));

m.def("AddTextControl", &AddTextControl, "", py::arg("textControl"), py::arg("column"), py::arg("row"), py::arg("labelAlignment"), py::arg("labelColumnCount"), py::arg("textColumnCount"), py::arg("rowCount"));

m.def("AddGroup", py::overload_cast<orientation, float, int, int, int, int>(&AddGroup), "", py::arg("orientation"), py::arg("spacing"), py::arg("column"), py::arg("row"), py::arg("columnCount"), py::arg("rowCount"));

m.def("AddGroup", py::overload_cast<BGroupView *, int, int, int, int>(&AddGroup), "", py::arg("groupView"), py::arg("column"), py::arg("row"), py::arg("columnCount"), py::arg("rowCount"));

m.def("AddGroup", py::overload_cast<BGroupLayout *, int, int, int, int>(&AddGroup), "", py::arg("groupLayout"), py::arg("column"), py::arg("row"), py::arg("columnCount"), py::arg("rowCount"));

m.def("AddGrid", py::overload_cast<float, float, int, int, int, int>(&AddGrid), "", py::arg("horizontalSpacing"), py::arg("verticalSpacing"), py::arg("column"), py::arg("row"), py::arg("columnCount"), py::arg("rowCount"));

m.def("AddGrid", py::overload_cast<BGridView *, int, int, int, int>(&AddGrid), "", py::arg("gridView"), py::arg("column"), py::arg("row"), py::arg("columnCount"), py::arg("rowCount"));

m.def("AddSplit", py::overload_cast<orientation, float, int, int, int, int>(&AddSplit), "", py::arg("orientation"), py::arg("spacing"), py::arg("column"), py::arg("row"), py::arg("columnCount"), py::arg("rowCount"));

m.def("AddSplit", py::overload_cast<BSplitView *, int, int, int, int>(&AddSplit), "", py::arg("splitView"), py::arg("column"), py::arg("row"), py::arg("columnCount"), py::arg("rowCount"));

m.def("AddCards", py::overload_cast<int, int, int, int>(&AddCards), "", py::arg("column"), py::arg("row"), py::arg("columnCount"), py::arg("rowCount"));

m.def("AddCards", py::overload_cast<BCardLayout *, int, int, int, int>(&AddCards), "", py::arg("cardLayout"), py::arg("column"), py::arg("row"), py::arg("columnCount"), py::arg("rowCount"));

m.def("AddCards", py::overload_cast<BCardView *, int, int, int, int>(&AddCards), "", py::arg("cardView"), py::arg("column"), py::arg("row"), py::arg("columnCount"), py::arg("rowCount"));

m.def("AddGlue", py::overload_cast<int, int, int, int>(&AddGlue), "", py::arg("column"), py::arg("row"), py::arg("columnCount"), py::arg("rowCount"));

m.def("SetHorizontalSpacing", &SetHorizontalSpacing, "", py::arg("spacing"));

m.def("SetVerticalSpacing", &SetVerticalSpacing, "", py::arg("spacing"));

m.def("SetSpacing", &SetSpacing, "", py::arg("horizontal"), py::arg("vertical"));

m.def("SetColumnWeight", &SetColumnWeight, "", py::arg("column"), py::arg("weight"));

m.def("SetRowWeight", &SetRowWeight, "", py::arg("row"), py::arg("weight"));

m.def("SetInsets", py::overload_cast<float, float, float, float>(&SetInsets), "", py::arg("left"), py::arg("top"), py::arg("right"), py::arg("bottom"));

m.def("SetInsets", py::overload_cast<float, float>(&SetInsets), "", py::arg("horizontal"), py::arg("vertical"));

m.def("SetInsets", py::overload_cast<float>(&SetInsets), "", py::arg("insets"));

m.def("SetExplicitMinSize", py::overload_cast<BSize>(&SetExplicitMinSize), "", py::arg("size"));

m.def("SetExplicitMaxSize", py::overload_cast<BSize>(&SetExplicitMaxSize), "", py::arg("size"));

m.def("SetExplicitPreferredSize", py::overload_cast<BSize>(&SetExplicitPreferredSize), "", py::arg("size"));

m.def("SetExplicitAlignment", py::overload_cast<BAlignment>(&SetExplicitAlignment), "", py::arg("alignment"));

m.def("operatorBGridLayout*", &operatorBGridLayout*, "");

m.def("Split", py::overload_cast<orientation, float>(&Split), "", py::arg("orientation"), py::arg("spacing"));

m.def("Split", py::overload_cast<BSplitView *>(&Split), "", py::arg("view"));

m.def("View", py::overload_cast<>(&View), "");

m.def("GetView", py::overload_cast<BView * *>(&GetView), "", py::arg("_view"));

m.def("GetSplitView", &GetSplitView, "", py::arg("_view"));

m.def("Add", py::overload_cast<BView *>(&Add), "", py::arg("view"));

m.def("Add", py::overload_cast<BView *, float>(&Add), "", py::arg("view"), py::arg("weight"));

m.def("Add", py::overload_cast<BLayoutItem *>(&Add), "", py::arg("item"));

m.def("Add", py::overload_cast<BLayoutItem *, float>(&Add), "", py::arg("item"), py::arg("weight"));

m.def("AddGroup", py::overload_cast<orientation, float, float>(&AddGroup), "", py::arg("orientation"), py::arg("spacing"), py::arg("weight"));

m.def("AddGroup", py::overload_cast<BGroupView *, float>(&AddGroup), "", py::arg("groupView"), py::arg("weight"));

m.def("AddGroup", py::overload_cast<BGroupLayout *, float>(&AddGroup), "", py::arg("groupLayout"), py::arg("weight"));

m.def("AddGrid", py::overload_cast<float, float, float>(&AddGrid), "", py::arg("horizontalSpacing"), py::arg("verticalSpacing"), py::arg("weight"));

m.def("AddGrid", py::overload_cast<BGridView *, float>(&AddGrid), "", py::arg("gridView"), py::arg("weight"));

m.def("AddGrid", py::overload_cast<BGridLayout *, float>(&AddGrid), "", py::arg("layout"), py::arg("weight"));

m.def("AddSplit", py::overload_cast<orientation, float, float>(&AddSplit), "", py::arg("orientation"), py::arg("spacing"), py::arg("weight"));

m.def("AddCards", py::overload_cast<float>(&AddCards), "", py::arg("weight"));

m.def("AddCards", py::overload_cast<BCardLayout *, float>(&AddCards), "", py::arg("cardLayout"), py::arg("weight"));

m.def("AddCards", py::overload_cast<BCardView *, float>(&AddCards), "", py::arg("cardView"), py::arg("weight"));

m.def("SetCollapsible", py::overload_cast<bool>(&SetCollapsible), "", py::arg("collapsible"));

m.def("SetCollapsible", py::overload_cast<int, bool>(&SetCollapsible), "", py::arg("index"), py::arg("collapsible"));

m.def("SetCollapsible", py::overload_cast<int, int, bool>(&SetCollapsible), "", py::arg("first"), py::arg("last"), py::arg("collapsible"));

m.def("SetInsets", py::overload_cast<float, float, float, float>(&SetInsets), "", py::arg("left"), py::arg("top"), py::arg("right"), py::arg("bottom"));

m.def("SetInsets", py::overload_cast<float, float>(&SetInsets), "", py::arg("horizontal"), py::arg("vertical"));

m.def("SetInsets", py::overload_cast<float>(&SetInsets), "", py::arg("insets"));

m.def("operatorBSplitView*", &operatorBSplitView*, "");

m.def("Cards", py::overload_cast<>(&Cards), "");

m.def("Cards", py::overload_cast<BWindow *>(&Cards), "", py::arg("window"));

m.def("Cards", py::overload_cast<BView *>(&Cards), "", py::arg("view"));

m.def("Cards", py::overload_cast<BCardLayout *>(&Cards), "", py::arg("layout"));

m.def("Cards", py::overload_cast<BCardView *>(&Cards), "", py::arg("view"));

m.def("Layout", py::overload_cast<>(&Layout), "");

m.def("View", py::overload_cast<>(&View), "");

m.def("GetLayout", py::overload_cast<BCardLayout * *>(&GetLayout), "", py::arg("_layout"));

m.def("GetView", py::overload_cast<BView * *>(&GetView), "", py::arg("_view"));

m.def("Add", py::overload_cast<BView *>(&Add), "", py::arg("view"));

m.def("Add", py::overload_cast<BLayoutItem *>(&Add), "", py::arg("item"));

m.def("AddGroup", py::overload_cast<orientation, float>(&AddGroup), "", py::arg("orientation"), py::arg("spacing"));

m.def("AddGroup", py::overload_cast<BGroupView *>(&AddGroup), "", py::arg("groupView"));

m.def("AddGroup", py::overload_cast<BGroupLayout *>(&AddGroup), "", py::arg("groupLayout"));

m.def("AddGrid", py::overload_cast<float, float>(&AddGrid), "", py::arg("horizontal"), py::arg("vertical"));

m.def("AddGrid", py::overload_cast<BGridLayout *>(&AddGrid), "", py::arg("gridLayout"));

m.def("AddGrid", py::overload_cast<BGridView *>(&AddGrid), "", py::arg("gridView"));

m.def("AddSplit", py::overload_cast<orientation, float>(&AddSplit), "", py::arg("orientation"), py::arg("spacing"));

m.def("AddSplit", py::overload_cast<BSplitView *>(&AddSplit), "", py::arg("splitView"));

m.def("AddCards", py::overload_cast<>(&AddCards), "");

m.def("AddCards", py::overload_cast<BCardLayout *>(&AddCards), "", py::arg("cardLayout"));

m.def("AddCards", py::overload_cast<BCardView *>(&AddCards), "", py::arg("cardView"));

m.def("SetExplicitMinSize", py::overload_cast<BSize>(&SetExplicitMinSize), "", py::arg("size"));

m.def("SetExplicitMaxSize", py::overload_cast<BSize>(&SetExplicitMaxSize), "", py::arg("size"));

m.def("SetExplicitPreferredSize", py::overload_cast<BSize>(&SetExplicitPreferredSize), "", py::arg("size"));

m.def("SetExplicitAlignment", py::overload_cast<BAlignment>(&SetExplicitAlignment), "", py::arg("alignment"));

m.def("SetVisibleItem", &SetVisibleItem, "", py::arg("item"));

m.def("operatorBCardLayout*", &operatorBCardLayout*, "");

m.def("Menu", &Menu, "", py::arg("menu"));

m.def("GetMenu", []() {
    BMenu *  _menu;
    typename Menu<ParentBuilder>::ThisBuilder & Menu<ParentBuilder> : : r = GetMenu(_menu);
    return std::make_tuple(r,_menu);
}
, "");

m.def("AddItem", py::overload_cast<BMenuItem *>(&AddItem), "", py::arg("item"));

m.def("AddItem", py::overload_cast<BMenu *>(&AddItem), "", py::arg("menu"));

m.def("AddItem", py::overload_cast<const char *, BMessage *, char, unsigned int>(&AddItem), "", py::arg("label"), py::arg("message"), py::arg("shortcut"), py::arg("modifiers"));

m.def("AddItem", py::overload_cast<const char *, unsigned int, char, unsigned int>(&AddItem), "", py::arg("label"), py::arg("messageWhat"), py::arg("shortcut"), py::arg("modifiers"));

m.def("AddSeparator", &AddSeparator, "");

m.def("AddMenu", py::overload_cast<BMenu *>(&AddMenu), "", py::arg("menu"));

m.def("AddMenu", py::overload_cast<const char *, menu_layout>(&AddMenu), "", py::arg("title"), py::arg("layout"));

m.def("MenuItem", &MenuItem, "", py::arg("parentBuilder"), py::arg("menu"), py::arg("item"));

m.def("GetItem", []() {
    BMenuItem *  _item;
    typename MenuItem<ParentBuilder>::ThisBuilder & MenuItem<ParentBuilder> : : r = GetItem(_item);
    return std::make_tuple(r,_item);
}
, "");

m.def("SetEnabled", &SetEnabled, "", py::arg("enabled"));

}
