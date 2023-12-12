#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <FilePanel.h>
//#include <Directory.h>
//#include <Entry.h>
//#include <Node.h>
#include <Window.h>
#include <Message.h>
#include <Messenger.h>
#include <posix/compat/sys/stat.h>
//#include <sys/stat.h>

namespace py = pybind11;


class PyBRefFilter : public BRefFilter {
public:
    using BRefFilter::BRefFilter;
    bool			Filter(const entry_ref* ref, BNode* node, struct stat_beos* stat, const char* mimeType)  override {
        PYBIND11_OVERLOAD(bool, BRefFilter, Filter, ref, node, stat, mimeType);
    }
};

class PyBFilePanel : public BFilePanel {
public:
    using BFilePanel::BFilePanel;
    void	WasHidden() override {
        PYBIND11_OVERLOAD(void, BFilePanel, WasHidden);
    }
    void	SelectionChanged() override {
        PYBIND11_OVERLOAD(void, BFilePanel, SelectionChanged);
    }
    void	SendMessage(const BMessenger* target, BMessage* message) override {
        PYBIND11_OVERLOAD(void, BFilePanel, SendMessage, target, message);
    }
};

PYBIND11_MODULE(FilePanel, m)
{
py::enum_<file_panel_mode>(m, "file_panel_mode", "")
.value("B_OPEN_PANEL", file_panel_mode::B_OPEN_PANEL, "")
.value("B_SAVE_PANEL", file_panel_mode::B_SAVE_PANEL, "")
.export_values();

py::enum_<file_panel_button>(m, "file_panel_button", "")
.value("B_CANCEL_BUTTON", file_panel_button::B_CANCEL_BUTTON, "")
.value("B_DEFAULT_BUTTON", file_panel_button::B_DEFAULT_BUTTON, "")
.export_values();

py::class_<BRefFilter,PyBRefFilter>(m, "BRefFilter")
//.def(py::init<>(),"")
.def("Filter", &BRefFilter::Filter, "", py::arg("ref"), py::arg("node"), py::arg("stat"), py::arg("mimeType"))
;

py::class_<BFilePanel,PyBFilePanel>(m, "BFilePanel")
.def(py::init<file_panel_mode, BMessenger *, const entry_ref *, uint32, bool, BMessage *, BRefFilter *, bool, bool>(), "", py::arg("mode")=file_panel_mode::B_OPEN_PANEL, py::arg("target")=NULL, py::arg("directory")=NULL, py::arg("nodeFlavors")=0, py::arg("allowMultipleSelection")=true,
	py::arg("message")=NULL, py::arg("refFilter")=NULL, py::arg("modal")=false, py::arg("hideWhenDone")=true)
.def("Show", &BFilePanel::Show, "")
.def("Hide", &BFilePanel::Hide, "")
.def("IsShowing", &BFilePanel::IsShowing, "")
.def("WasHidden", &BFilePanel::WasHidden, "")
.def("SelectionChanged", &BFilePanel::SelectionChanged, "")
.def("SendMessage", &BFilePanel::SendMessage, "", py::arg("target"), py::arg("message"))
.def("Window", &BFilePanel::Window, "")
.def("Messenger", &BFilePanel::Messenger, "")
.def("RefFilter", &BFilePanel::RefFilter, "")
.def("PanelMode", &BFilePanel::PanelMode, "")
.def("SetTarget", &BFilePanel::SetTarget, "", py::arg("target"))
.def("SetMessage", &BFilePanel::SetMessage, "", py::arg("message"))
.def("SetRefFilter", &BFilePanel::SetRefFilter, "", py::arg("filter"))
.def("SetSaveText", &BFilePanel::SetSaveText, "", py::arg("text"))
.def("SetButtonLabel", &BFilePanel::SetButtonLabel, "", py::arg("button"), py::arg("label"))
.def("SetNodeFlavors", &BFilePanel::SetNodeFlavors, "", py::arg("flavors"))
.def("SetPanelDirectory", py::overload_cast<const BEntry *>(&BFilePanel::SetPanelDirectory), "", py::arg("newDirectory"))
.def("SetPanelDirectory", py::overload_cast<const BDirectory *>(&BFilePanel::SetPanelDirectory), "", py::arg("newDirectory"))
.def("SetPanelDirectory", py::overload_cast<const entry_ref *>(&BFilePanel::SetPanelDirectory), "", py::arg("newDirectory"))
.def("SetPanelDirectory", py::overload_cast<const char *>(&BFilePanel::SetPanelDirectory), "", py::arg("newDirectory"))
.def("GetPanelDirectory", &BFilePanel::GetPanelDirectory, "", py::arg("ref"))
.def("SetHideWhenDone", &BFilePanel::SetHideWhenDone, "", py::arg("hideWhenDone"))
.def("HidesWhenDone", &BFilePanel::HidesWhenDone, "")
.def("Refresh", &BFilePanel::Refresh, "")
.def("Rewind", &BFilePanel::Rewind, "")
.def("GetNextSelectedRef", &BFilePanel::GetNextSelectedRef, "", py::arg("ref"))
;


}
