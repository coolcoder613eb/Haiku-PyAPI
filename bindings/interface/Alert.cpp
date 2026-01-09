#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/Alert.h>
#include <vector>
#include <Window.h>
#include <Button.h>
#include <Invoker.h>
#include <Bitmap.h>
#include <TextView.h>

namespace py = pybind11;

class PyBAlert : public BAlert{
	public:
        using BAlert::BAlert;
        status_t	Archive(BMessage* data, bool deep = true) const override {
            PYBIND11_OVERLOAD(status_t, BAlert, Archive, data, deep);
        }
        void		MessageReceived(BMessage* message) override {
        	PYBIND11_OVERLOAD(void, BAlert, MessageReceived, message);
        }
        void		FrameResized(float newWidth, float newHeight) override {
        	PYBIND11_OVERLOAD(void, BAlert, FrameResized, newWidth, newHeight);
        }
        BHandler*	ResolveSpecifier(BMessage* message, int32 index,
									BMessage* specifier, int32 form,
									const char* property) override {
			PYBIND11_OVERLOAD(BHandler*, BAlert, ResolveSpecifier, message, index, specifier, form, property);
		}
		status_t	GetSupportedSuites(BMessage* data) override {
			PYBIND11_OVERLOAD(status_t, BAlert, GetSupportedSuites, data);
		}
};


PYBIND11_MODULE(Alert,m)
{
py::enum_<alert_type>(m, "alert_type", "")
.value("B_EMPTY_ALERT", alert_type::B_EMPTY_ALERT, "")
.value("B_INFO_ALERT", alert_type::B_INFO_ALERT, "")
.value("B_IDEA_ALERT", alert_type::B_IDEA_ALERT, "")
.value("B_WARNING_ALERT", alert_type::B_WARNING_ALERT, "")
.value("B_STOP_ALERT", alert_type::B_STOP_ALERT, "")
.export_values();

py::enum_<button_spacing>(m, "button_spacing", "")
.value("B_EVEN_SPACING", button_spacing::B_EVEN_SPACING, "")
.value("B_OFFSET_SPACING", button_spacing::B_OFFSET_SPACING, "")
.export_values();

py::class_<BAlert,PyBAlert,std::unique_ptr<BAlert, py::nodelete>>(m, "BAlert",R"doc(
The ``BAlert`` class defines a modal alert dialog which displays a short message and provides a set of labeled buttons that allow the user to respond.

The alert can be configured with a set of one to three buttons. These buttons are assigned indexes ``0``, ``1``, and ``2`` from right-to-left respectively and are automatically positioned by the system. The user can either click on one of the buttons or use a shortcut key to select a button.

The layout of the buttons can be configured by setting the button_width and button_spacing properties in the ``BAlert`` constructor. The icon displayed in the alert can also be configured by setting the alert_type property. The right-most button (index ``0``) is the default button which can be activated by pushing the `Enter` key.

When the user responds by selecting one of the buttons the alert window is removed from the screen. The index of the selected button is returned to the calling application and the ``BAlert`` object is deleted by Haiku.

.. note::
   
   To prevent "double free" errors, the Python wrapper does not automatically destroy the ``BAlert`` object, as Haiku handles its deletion when the alert closes. 
   However, if a ``BAlert`` is instantiated but never displayed (e.g., by calling ``Go()``), the memory will not be reclaimed automatically.
   In such cases, you are responsible for managing the object's lifecycle to avoid memory leaks by calling ``Quit()``.
   
)doc") //previously, BWindow, py::smart_holder instead of std::unique_ptr<BAlert, py::nodelete>
.def(py::init(), "")
.def(py::init<const char *, const char *, const char *, const char *, const char *, button_width, alert_type>(), "", py::arg("title"), py::arg("text"), py::arg("button1"), py::arg("button2")=NULL, py::arg("button3")=NULL, py::arg("width")=B_WIDTH_AS_USUAL, py::arg("type")=B_INFO_ALERT)
.def(py::init<const char *, const char *, const char *, const char *, const char *, button_width, button_spacing, alert_type>(), "", py::arg("title"), py::arg("text"), py::arg("button1"), py::arg("button2"), py::arg("button3"), py::arg("width"), py::arg("spacing"), py::arg("type")=B_INFO_ALERT)
.def(py::init<BMessage *>(), "", py::arg("data"))
.def_static("Instantiate", &BAlert::Instantiate, "", py::arg("data"))
.def("Archive", &BAlert::Archive, "", py::arg("data"), py::arg("deep")=true)
.def("Type", &BAlert::Type, "")
.def("SetType", &BAlert::SetType, "", py::arg("type"))
.def("SetIcon", &BAlert::SetIcon, "", py::arg("bitmap"))
.def("SetText", &BAlert::SetText, "", py::arg("text"))
.def("SetButtonSpacing", &BAlert::SetButtonSpacing, "", py::arg("spacing"))
.def("SetButtonWidth", &BAlert::SetButtonWidth, "", py::arg("width"))
.def("SetShortcut", &BAlert::SetShortcut, "", py::arg("buttonIndex"), py::arg("key"))
.def("Shortcut", &BAlert::Shortcut, "", py::arg("buttonIndex"))
.def("Go", py::overload_cast<>(&BAlert::Go), "")
.def("Go", py::overload_cast<BInvoker *>(&BAlert::Go), "", py::arg("invoker"))
.def("MessageReceived", &BAlert::MessageReceived, "", py::arg("message"))
.def("FrameResized", &BAlert::FrameResized, "", py::arg("newWidth"), py::arg("newHeight"))
.def("AddButton", &BAlert::AddButton, "", py::arg("label"), py::arg("key")=0)
.def("CountButtons", &BAlert::CountButtons, "")
.def("ButtonAt", &BAlert::ButtonAt, "", py::arg("index"))
.def("TextView", &BAlert::TextView, "")
.def("ResolveSpecifier", &BAlert::ResolveSpecifier, "", py::arg("message"), py::arg("index"), py::arg("specifier"), py::arg("form"), py::arg("property"))
.def("GetSupportedSuites", &BAlert::GetSupportedSuites, "", py::arg("data"))
.def("DispatchMessage", &BAlert::DispatchMessage, "", py::arg("message"), py::arg("handler"))
.def("Quit", &BAlert::Quit, "")
.def("QuitRequested", &BAlert::QuitRequested, "")
.def("Perform", &BAlert::Perform, "", py::arg("d"), py::arg("arg"))
.def_static("AlertPosition", &BAlert::AlertPosition, "", py::arg("width"), py::arg("height"))
;


}
