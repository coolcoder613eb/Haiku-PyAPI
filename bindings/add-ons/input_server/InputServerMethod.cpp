#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <add-ons/input_server/InputServerMethod.h>
#include <add-ons/input_server/InputServerFilter.h>
#include <Menu.h>
#include <Messenger.h>

namespace py = pybind11;
using namespace BPrivate;

class PyBInputServerMethod : public BInputServerMethod {
public:
    using BInputServerMethod::BInputServerMethod;
	status_t			MethodActivated(bool active) override {
		PYBIND11_OVERLOAD(status_t, BInputServerMethod, MethodActivated, active);
	}
};

PYBIND11_MODULE(InputServerMethod, m)
{
py::class_<BInputServerMethod, PyBInputServerMethod, BInputServerFilter>(m, "BInputServerMethod")
.def(py::init<const char *, const uchar *>(), "", py::arg("name"), py::arg("icon"))
.def("MethodActivated", &BInputServerMethod::MethodActivated, "", py::arg("active"))
.def("EnqueueMessage", &BInputServerMethod::EnqueueMessage, "", py::arg("message"))
.def("SetName", &BInputServerMethod::SetName, "", py::arg("name"))
.def("SetIcon", &BInputServerMethod::SetIcon, "", py::arg("icon"))
.def("SetMenu", &BInputServerMethod::SetMenu, "", py::arg("menu"), py::arg("target"))
;


}
