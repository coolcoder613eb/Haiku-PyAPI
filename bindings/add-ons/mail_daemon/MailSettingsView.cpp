#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <add-ons/mail_daemon/MailSettingsView.h>

namespace py = pybind11;

class PyBMailSettingsView : public BMailSettingsView {
public:
	using BMailSettingsView::BMailSettingsView;
    status_t				SaveInto(BMailAddOnSettings& settings) const override {
        PYBIND11_OVERLOAD_PURE(status_t, BMailSettingsView, SaveInto, settings);
    }
};

PYBIND11_MODULE(MailSettingsView, m)
{
py::class_<BMailSettingsView, PyBMailSettingsView, BView>(m, "BMailSettingsView")
.def(py::init<const char *>(), "", py::arg("name"))
.def("SaveInto", &BMailSettingsView::SaveInto, "", py::arg("settings"))
/*.def("SaveInto", [](BMailSettingsView& self) {
    BMailAddOnSettings  settings;
    status_t r = self.SaveInto(settings);
    return std::make_tuple(r,settings);
}
, "")*/

;


}
