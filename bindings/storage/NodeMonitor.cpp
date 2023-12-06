#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <NodeMonitor.h>
#include <StorageDefs.h>
#include <Handler.h>
#include <Looper.h>

namespace py = pybind11;
//using namespace BPrivate;
//using namespace BPrivate::Storage;
//using namespace BPrivate::Storage::Mime;

PYBIND11_MODULE(NodeMonitor, m)
{
m.def("watch_volume", py::overload_cast<dev_t, uint32, BMessenger>(&watch_volume), "", py::arg("volume"), py::arg("flags"), py::arg("target"));

m.def("watch_volume", py::overload_cast<dev_t, uint32, const BHandler *, const BLooper *>(&watch_volume), "", py::arg("volume"), py::arg("flags"), py::arg("handler"), py::arg("looper")=NULL);

m.def("watch_node", py::overload_cast<const node_ref *, uint32, BMessenger>(&watch_node), "", py::arg("node"), py::arg("flags"), py::arg("target"));

m.def("watch_node", py::overload_cast<const node_ref *, uint32, const BHandler *, const BLooper *>(&watch_node), "", py::arg("node"), py::arg("flags"), py::arg("handler"), py::arg("looper")=NULL);

m.def("stop_watching", py::overload_cast<BMessenger>(&stop_watching), "", py::arg("target"));

m.def("stop_watching", py::overload_cast<const BHandler *, const BLooper *>(&stop_watching), "", py::arg("handler"), py::arg("looper")=NULL);

m.attr("B_STOP_WATCHING") = 0x0000; //these have been hardcoded due to fault on loading module
m.attr("B_WATCH_NAME") = 0x0001;
m.attr("B_WATCH_STAT") = 0x0002;
m.attr("B_WATCH_ATTR") = 0x0004;
m.attr("B_WATCH_DIRECTORY") = 0x0008;
m.attr("B_WATCH_ALL") = 0x000f;
m.attr("B_WATCH_MOUNT") = 0x0010;
m.attr("B_WATCH_INTERIM_STAT") = 0x0020;
m.attr("B_WATCH_CHILDREN") = 0x0040;

m.attr("B_STAT_MODE") = 0x0001;
m.attr("B_STAT_UID") = 0x0002;
m.attr("B_STAT_GID") = 0x0004;
m.attr("B_STAT_SIZE") = 0x0008;
m.attr("B_STAT_ACCESS_TIME") = 0x0010;
m.attr("B_STAT_MODIFICATION_TIME") = 0x0020;
m.attr("B_STAT_CREATION_TIME") = 0x0040;
m.attr("B_STAT_CHANGE_TIME") = 0x0080;
m.attr("B_STAT_INTERIM_UPDATE") = 0x1000;
}
