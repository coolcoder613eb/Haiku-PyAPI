#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/OptionControl.h>
#include <Control.h>

namespace py = pybind11;

class PyBOptionControl : public BOptionControl {
public:
    using BOptionControl::BOptionControl;

    void	MessageReceived(BMessage* message) override {
        	PYBIND11_OVERLOAD(void, BOptionControl, MessageReceived, message);
    }
    bool 	GetOptionAt(int32 index, const char** _name, int32* _value) override {
        PYBIND11_OVERRIDE_PURE(bool, BOptionControl, GetOptionAt, index, _name, _value);
    }
    void	RemoveOptionAt(int32 index) override {
        PYBIND11_OVERRIDE_PURE(void, BOptionControl, RemoveOptionAt, index);
    }
    int32	CountOptions() const override {
        PYBIND11_OVERRIDE_PURE(int32, BOptionControl, CountOptions);
    }
    status_t	AddOptionAt(const char* name, int32 value, int32 index) override {
        PYBIND11_OVERRIDE_PURE(status_t, BOptionControl, AddOptionAt, name, value, index);
    }
    int32	SelectedOption(const char** name = NULL, int32* outValue = NULL) const override {
        PYBIND11_OVERRIDE_PURE(int32, BOptionControl, SelectedOption, name, outValue);
    }
    status_t	SelectOptionFor(int32 value) override {
        	PYBIND11_OVERLOAD(status_t, BOptionControl, SelectOptionFor, value);
    }
    status_t	SelectOptionFor(const char* name) override {
        	PYBIND11_OVERLOAD(status_t, BOptionControl, SelectOptionFor, name);
    }
};

PYBIND11_MODULE(OptionControl,m)
{
m.attr("B_OPTION_CONTROL_VALUE") = "_BMV";

py::class_<BOptionControl,PyBOptionControl, BControl>(m, "BOptionControl")
.def(py::init<BRect, const char *, const char *, BMessage *, unsigned int, unsigned int>(), "", py::arg("frame"), py::arg("name"), py::arg("label"), py::arg("message"), py::arg("resizeMask")=B_FOLLOW_LEFT_TOP, py::arg("flags")=B_WILL_DRAW)
.def(py::init<const char *, const char *, BMessage *, unsigned int>(), "", py::arg("name"), py::arg("label"), py::arg("message"), py::arg("flags")=B_WILL_DRAW)
.def("MessageReceived", &BOptionControl::MessageReceived, "", py::arg("message"))
.def("AddOption", &BOptionControl::AddOption, "", py::arg("name"), py::arg("value"))
//.def("GetOptionAt", &BOptionControl::GetOptionAt, "", py::arg("index"), py::arg("_name"), py::arg("_value"))
//.def("RemoveOptionAt", &BOptionControl::RemoveOptionAt, "", py::arg("index"))
//.def("CountOptions", &BOptionControl::CountOptions, "")
//.def("AddOptionAt", &BOptionControl::AddOptionAt, "", py::arg("name"), py::arg("value"), py::arg("index"))
//.def("SelectedOption", &BOptionControl::SelectedOption, "", py::arg("name")=NULL, py::arg("outValue")=NULL)
.def("SelectOptionFor", py::overload_cast<int32>(&BOptionControl::SelectOptionFor), "", py::arg("value"))
.def("SelectOptionFor", py::overload_cast<const char *>(&BOptionControl::SelectOptionFor), "", py::arg("name"))
;


}
