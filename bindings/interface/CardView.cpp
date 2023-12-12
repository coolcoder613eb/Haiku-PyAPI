#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/CardView.h>
#include <Layout.h>
#include <CardLayout.h>
#include <View.h>

namespace py = pybind11;


PYBIND11_MODULE(CardView,m)
{
py::class_<BCardView, BView>(m, "BCardView")
.def(py::init(), "")
.def(py::init<const char *>(), "", py::arg("name"))
.def(py::init<BMessage *>(), "", py::arg("from"))
.def("SetLayout", &BCardView::SetLayout, "", py::arg("layout"))
.def("CardLayout", &BCardView::CardLayout, "")
.def_static("Instantiate", &BCardView::Instantiate, "", py::arg("from"))
.def("Perform", &BCardView::Perform, "", py::arg("d"), py::arg("arg"))
;


}
