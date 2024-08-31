#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <mail/MailContainer.h>

namespace py = pybind11;

class PyBMailContainer : public BMailContainer{
	public:
        using BMailContainer::BMailContainer;
        status_t AddComponent(BMailComponent *component) override {
            PYBIND11_OVERLOAD_PURE(status_t, BMailContainer, AddComponent, component);
        }
        status_t RemoveComponent(BMailComponent *component) override {
            PYBIND11_OVERLOAD_PURE(status_t, BMailContainer, RemoveComponent, component);
        }
        status_t RemoveComponent(int32 index) override {
            PYBIND11_OVERLOAD_PURE(status_t, BMailContainer, RemoveComponent, index);
        }
        BMailComponent *GetComponent(int32 index, bool parse_now = false) override {
            PYBIND11_OVERLOAD_PURE(BMailComponent*, BMailContainer, GetComponent, index, parse_now);
        }
        int32 CountComponents() const override {
            PYBIND11_OVERLOAD_PURE(int32, BMailContainer, CountComponents);
        }
};

PYBIND11_MODULE(MailContainer, m)
{
py::class_<BMailContainer, PyBMailContainer, BMailComponent>(m, "BMailContainer")
.def(py::init<unsigned int>(), "", py::arg("defaultCharSet")=B_MAIL_NULL_CONVERSION)
.def("AddComponent", &BMailContainer::AddComponent, "", py::arg("component"))
.def("RemoveComponent", py::overload_cast<BMailComponent *>(&BMailContainer::RemoveComponent), "", py::arg("component"))
.def("RemoveComponent", py::overload_cast<int>(&BMailContainer::RemoveComponent), "", py::arg("index"))
.def("GetComponent", &BMailContainer::GetComponent, "", py::arg("index"), py::arg("parse_now")=false)
.def("CountComponents", &BMailContainer::CountComponents, "")
;

py::class_<BMIMEMultipartMailContainer, BMailContainer>(m, "BMIMEMultipartMailContainer")
.def(py::init<const char *, const char *, unsigned int>(), "", py::arg("boundary")=NULL, py::arg("this_is_an_MIME_message_text")=NULL, py::arg("defaultCharSet")=B_MAIL_NULL_CONVERSION)
.def(py::init(), "")
.def("SetBoundary", &BMIMEMultipartMailContainer::SetBoundary, "", py::arg("boundary"))
.def("SetThisIsAnMIMEMessageText", &BMIMEMultipartMailContainer::SetThisIsAnMIMEMessageText, "", py::arg("text"))
.def("AddComponent", &BMIMEMultipartMailContainer::AddComponent, "", py::arg("component"))
.def("RemoveComponent", py::overload_cast<BMailComponent *>(&BMIMEMultipartMailContainer::RemoveComponent), "", py::arg("component"))
.def("RemoveComponent", py::overload_cast<int>(&BMIMEMultipartMailContainer::RemoveComponent), "", py::arg("index"))
.def("GetComponent", &BMIMEMultipartMailContainer::GetComponent, "", py::arg("index"), py::arg("parse_now")=false)
.def("CountComponents", &BMIMEMultipartMailContainer::CountComponents, "")
.def("GetDecodedData", &BMIMEMultipartMailContainer::GetDecodedData, "", py::arg("data"))
.def("SetDecodedData", &BMIMEMultipartMailContainer::SetDecodedData, "", py::arg("data"))
.def("SetToRFC822", &BMIMEMultipartMailContainer::SetToRFC822, "", py::arg("data"), py::arg("length"), py::arg("parse_now")=false)
.def("RenderToRFC822", &BMIMEMultipartMailContainer::RenderToRFC822, "", py::arg("render_to"))
;


}
