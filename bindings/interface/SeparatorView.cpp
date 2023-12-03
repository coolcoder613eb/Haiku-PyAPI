#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/SeparatorView.h>
#include <Alignment.h>
#include <String.h>
#include <View.h>

namespace py = pybind11;

class PyBSeparatorView : public BSeparatorView{
	public:
        using BSeparatorView::BSeparatorView;
        status_t		Archive(BMessage* into, bool deep = true) const override {
        	PYBIND11_OVERLOAD(status_t, BSeparatorView, Archive, into, deep);
        }
        void				Draw(BRect updateRect) override {
            PYBIND11_OVERLOAD(void, BSeparatorView, Draw, updateRect);
        }
        void			GetPreferredSize(float* width, float* height) override {
            PYBIND11_OVERLOAD(void, BSeparatorView, GetPreferredSize, width, height);
        }
        BSize			MinSize() override {
            PYBIND11_OVERLOAD(BSize, BSeparatorView, MinSize);
        }
        BSize			PreferredSize() override {
            PYBIND11_OVERLOAD(BSize, BSeparatorView, PreferredSize);
        }
        BSize			MaxSize() override {
            PYBIND11_OVERLOAD(BSize, BSeparatorView, MaxSize);
        }
        status_t		Perform(perform_code code, void* data) override {
            PYBIND11_OVERLOAD(status_t, BSeparatorView, Perform, code, data);
        }
};

PYBIND11_MODULE(SeparatorView,m)
{
py::class_<BSeparatorView, PyBSeparatorView, BView>(m, "BSeparatorView")
.def(py::init<orientation, border_style>(), "", py::arg("orientation"), py::arg("border")=B_PLAIN_BORDER)
.def(py::init<const char *, const char *, orientation, border_style, const BAlignment &>(), "", py::arg("name"), py::arg("label"), py::arg("orientation")=B_HORIZONTAL, py::arg("border")=B_FANCY_BORDER, py::arg("alignment")=BAlignment(B_ALIGN_HORIZONTAL_CENTER,B_ALIGN_VERTICAL_CENTER))
.def(py::init<const char *, BView *, orientation, border_style, const BAlignment &>(), "", py::arg("name"), py::arg("labelView"), py::arg("orientation")=B_HORIZONTAL, py::arg("border")=B_FANCY_BORDER, py::arg("alignment")=BAlignment(B_ALIGN_HORIZONTAL_CENTER,B_ALIGN_VERTICAL_CENTER))
.def(py::init<const char *, orientation, border_style, const BAlignment &>(), "", py::arg("label")=NULL, py::arg("orientation")=B_HORIZONTAL, py::arg("border")=B_FANCY_BORDER, py::arg("alignment")=BAlignment(B_ALIGN_HORIZONTAL_CENTER,B_ALIGN_VERTICAL_CENTER))
.def(py::init<BView *, orientation, border_style, const BAlignment &>(), "", py::arg("labelView"), py::arg("orientation")=B_HORIZONTAL, py::arg("border")=B_FANCY_BORDER, py::arg("alignment")=BAlignment(B_ALIGN_HORIZONTAL_CENTER,B_ALIGN_VERTICAL_CENTER))
.def(py::init<BMessage *>(), "", py::arg("archive"))
.def_static("Instantiate", &BSeparatorView::Instantiate, "", py::arg("archive"))
.def("Archive", &BSeparatorView::Archive, "", py::arg("into"), py::arg("deep")=true)
.def("Draw", &BSeparatorView::Draw, "", py::arg("updateRect"))
.def("GetPreferredSize", &BSeparatorView::GetPreferredSize, "", py::arg("width"), py::arg("height"))
.def("MinSize", &BSeparatorView::MinSize, "")
.def("MaxSize", &BSeparatorView::MaxSize, "")
.def("PreferredSize", &BSeparatorView::PreferredSize, "")
.def("SetOrientation", &BSeparatorView::SetOrientation, "", py::arg("orientation"))
.def("SetAlignment", &BSeparatorView::SetAlignment, "", py::arg("aligment"))
.def("SetBorderStyle", &BSeparatorView::SetBorderStyle, "", py::arg("border"))
.def("SetLabel", py::overload_cast<const char *>(&BSeparatorView::SetLabel), "", py::arg("label"))
.def("SetLabel", py::overload_cast<BView *, bool>(&BSeparatorView::SetLabel), "", py::arg("view"), py::arg("deletePrevious"))
.def("Perform", &BSeparatorView::Perform, "", py::arg("code"), py::arg("data"))
;


}
