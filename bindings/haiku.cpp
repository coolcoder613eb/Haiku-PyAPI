#include <python3.9/pybind11/pybind11.h>
#include <AppKit.h>
#include <InterfaceKit.h>
 
namespace py = pybind11;
 
class PyBWindow : public BWindow{
    public:
        using BWindow::BWindow;
 
        void MessageReceived(BMessage* msg) override {
            py::gil_scoped_release release;
            {
                py::gil_scoped_acquire acquire;
                PYBIND11_OVERLOAD(
                    void,
                    BWindow,
                    MessageReceived,
                    msg
                );
            }
        }
 
        bool QuitRequested() override {
            py::gil_scoped_release release;
            {
                py::gil_scoped_acquire acquire;
                PYBIND11_OVERLOAD(
                    bool,
                    BWindow,
                    QuitRequested,
                );
            }
        }
};
 
PYBIND11_MODULE(haiku,m) {
    py::class_<BApplication>(m, "BApplication")
        .def(py::init<const char*>())
        .def("Run", &BApplication::Run);
 
    py::class_<BMessage>(m, "BMessage")
        .def(py::init<uint32>())
        .def_readwrite("what", &BMessage::what);
 
    py::class_<BRect>(m, "BRect")
        .def(py::init<float, float, float, float>());
 
    py::class_<BView>(m, "BView")
        .def(py::init<BRect, const char*, uint32, uint32>())
        .def("AddChild", (void (BView::*) (BView*, BView*)) &BView::AddChild);
 
    py::class_<BWindow, PyBWindow>(m, "BWindow")
        .def(py::init<BRect, const char*, window_type, int>())
        .def("Show", &BWindow::Show)
        .def("MessageReceived", &BWindow::MessageReceived)
        .def("QuitRequested", &BWindow::QuitRequested)
        .def("Bounds", &BWindow::Bounds)
        .def("AddChild", (void (BWindow::*) (BView*, BView*)) &BWindow::AddChild);
 
    py::enum_<window_type>(m, "window_type")
        .value("B_TITLED_WINDOW", window_type::B_TITLED_WINDOW);

    py::class_<BButton, BView>(m, "BButton")
        .def(py::init<BRect, const char*, const char*, BMessage*>());
}
