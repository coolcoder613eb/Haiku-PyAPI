#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <add-ons/input_server/InputServerFilter.h>
#include <List.h>
#include <Region.h>

namespace py = pybind11;
using namespace BPrivate;

class PyBInputServerFilter : public BInputServerFilter {
public:
    using BInputServerFilter::BInputServerFilter;
    status_t			InitCheck() override {
    	PYBIND11_OVERLOAD(status_t, BInputServerFilter, InitCheck);
    }
	filter_result		Filter(BMessage* message, BList* _list) override {
		PYBIND11_OVERLOAD(filter_result, BInputServerFilter, Filter, message, _list);
	}
};

PYBIND11_MODULE(InputServerFilter, m)
{
py::class_<BInputServerFilter,PyBInputServerFilter>(m, "BInputServerFilter")
.def(py::init(), "")
.def("InitCheck", &BInputServerFilter::InitCheck, "")
.def("Filter", &BInputServerFilter::Filter, "", py::arg("message"), py::arg("_list"))
.def("GetScreenRegion", &BInputServerFilter::GetScreenRegion, "", py::arg("region"))
;


}
