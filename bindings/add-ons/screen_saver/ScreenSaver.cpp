#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <add-ons/screen_saver/ScreenSaver.h>

namespace py = pybind11;

class PyBScreenSaver : public BScreenSaver{
	public:
        using BScreenSaver::BScreenSaver;
        status_t			InitCheck() override {
            PYBIND11_OVERLOAD(status_t, BScreenSaver, InitCheck);
        }
        status_t 			StartSaver(BView* view, bool preview) override {
            PYBIND11_OVERLOAD(status_t, BScreenSaver, StartSaver, view, preview);
        }
        void				StopSaver() override {
            PYBIND11_OVERLOAD(void, BScreenSaver, StopSaver);
        }
        void				Draw(BView* view, int32 frame) override {
            PYBIND11_OVERLOAD(void, BScreenSaver, Draw, view, frame);
        }
        void				DirectConnected(direct_buffer_info* info) override {
            PYBIND11_OVERLOAD(void, BScreenSaver, DirectConnected, info);
        }
        void				DirectDraw(int32 frame) override {
            PYBIND11_OVERLOAD(void, BScreenSaver, DirectDraw, frame);
        }
        void				StartConfig(BView* configView) override {
            PYBIND11_OVERLOAD(void, BScreenSaver, StartConfig, configView);
        }
        void				StopConfig() override {
            PYBIND11_OVERLOAD(void, BScreenSaver, StopConfig);
        }
        void				SupplyInfo(BMessage* info) const override {
            PYBIND11_OVERLOAD(void, BScreenSaver, SupplyInfo, info);
        }
        void				ModulesChanged(const BMessage* info) override {
            PYBIND11_OVERLOAD(void, BScreenSaver, ModulesChanged, info);
        }
        status_t			SaveState(BMessage* into) const override {
            PYBIND11_OVERLOAD(status_t, BScreenSaver, SaveState, into);
        }
};

PYBIND11_MODULE(ScreenSaver, m)
{
py::class_<BScreenSaver,PyBScreenSaver>(m, "BScreenSaver")
.def(py::init<BMessage *, image_id>(), "", py::arg("archive"), py::arg("thisImage"))
.def("InitCheck", &BScreenSaver::InitCheck, "")
.def("StartSaver", &BScreenSaver::StartSaver, "", py::arg("view"), py::arg("preview"))
.def("StopSaver", &BScreenSaver::StopSaver, "")
.def("Draw", &BScreenSaver::Draw, "", py::arg("view"), py::arg("frame"))
.def("DirectConnected", &BScreenSaver::DirectConnected, "", py::arg("info"))
.def("DirectDraw", &BScreenSaver::DirectDraw, "", py::arg("frame"))
.def("StartConfig", &BScreenSaver::StartConfig, "", py::arg("configView"))
.def("StopConfig", &BScreenSaver::StopConfig, "")
.def("SupplyInfo", &BScreenSaver::SupplyInfo, "", py::arg("info"))
.def("ModulesChanged", &BScreenSaver::ModulesChanged, "", py::arg("info"))
.def("SaveState", &BScreenSaver::SaveState, "", py::arg("into"))
.def("SetTickSize", &BScreenSaver::SetTickSize, "", py::arg("tickSize"))
.def("TickSize", &BScreenSaver::TickSize, "")
.def("SetLoop", &BScreenSaver::SetLoop, "", py::arg("onCount"), py::arg("offCount"))
.def("LoopOnCount", &BScreenSaver::LoopOnCount, "")
.def("LoopOffCount", &BScreenSaver::LoopOffCount, "")
;

m.def("instantiate_screen_saver", &instantiate_screen_saver, "", py::arg("msg"), py::arg("id"));

}
