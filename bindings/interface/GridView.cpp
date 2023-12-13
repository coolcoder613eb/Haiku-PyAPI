#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/GridView.h>
#include <GridLayout.h>
#include <View.h>

namespace py = pybind11;


class PyBGridView : public BGridView{
	public:
        using BGridView::BGridView;
        void		SetLayout(BLayout* layout) override {
        	PYBIND11_OVERLOAD(void, BGridView, SetLayout, layout);
        }
        status_t	Perform(perform_code d, void* arg) override {
        	PYBIND11_OVERLOAD(status_t, BGridView, Perform, d, arg);
        }
};

PYBIND11_MODULE(GridView,m)
{
py::class_<BGridView, PyBGridView, BView>(m, "BGridView")
//.def(py::init<float, float>(), "", py::arg("horizontal")=B_USE_DEFAULT_SPACING, py::arg("vertical")=B_USE_DEFAULT_SPACING)
.def(py::init<float, float>(), "", py::arg("horizontal")=-1002, py::arg("vertical")=-1002)
//.def(py::init<const char *, float, float>(), "", py::arg("name"), py::arg("horizontal")=B_USE_DEFAULT_SPACING, py::arg("vertical")=B_USE_DEFAULT_SPACING)
.def(py::init<const char *, float, float>(), "", py::arg("name"), py::arg("horizontal")=-1002, py::arg("vertical")=-1002)
.def(py::init<BMessage *>(), "", py::arg("from"))
.def("SetLayout", &BGridView::SetLayout, "", py::arg("layout"))
.def("GridLayout", &BGridView::GridLayout, "")
.def_static("Instantiate", &BGridView::Instantiate, "", py::arg("from"))
.def("Perform", &BGridView::Perform, "", py::arg("d"), py::arg("arg"))
;


}
