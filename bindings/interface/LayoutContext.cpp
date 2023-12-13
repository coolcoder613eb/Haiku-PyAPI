#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/LayoutContext.h>
#include <List.h>

namespace py = pybind11;


class PyBLayoutContextListener : public BLayoutContextListener {
public:
    using BLayoutContextListener::BLayoutContextListener;

    void LayoutContextLeft(BLayoutContext* context) override {
        PYBIND11_OVERRIDE_PURE(void, BLayoutContextListener, LayoutContextLeft, context);
    }
};

PYBIND11_MODULE(LayoutContext,m)
{
py::class_<BLayoutContextListener>(m, "BLayoutContextListener")
//.def(py::init(), "")
//.def("LayoutContextLeft", &BLayoutContextListener::LayoutContextLeft, "", py::arg("context"))
;

py::class_<BLayoutContext>(m, "BLayoutContext")
.def(py::init(), "")
.def("AddListener", &BLayoutContext::AddListener, "", py::arg("listener"))
.def("RemoveListener", &BLayoutContext::RemoveListener, "", py::arg("listener"))
;


}
