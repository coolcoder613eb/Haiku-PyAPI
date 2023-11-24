#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <NodeMonitor.h>

namespace py = pybind11;
using namespace BPrivate;
using namespace BPrivate::Storage;
using namespace BPrivate::Storage::Mime;

void define_NodeMonitor(py::module_& m)
{
m.attr("B_STOP_WATCHING") = py::cast(B_STOP_WATCHING);
m.attr("B_WATCH_NAME") = py::cast(B_WATCH_NAME);
m.attr("B_WATCH_STAT") = py::cast(B_WATCH_STAT);
m.attr("B_WATCH_ATTR") = py::cast(B_WATCH_ATTR);
m.attr("B_WATCH_DIRECTORY") = py::cast(B_WATCH_DIRECTORY);
m.attr("B_WATCH_ALL") = py::cast(B_WATCH_ALL);
m.attr("B_WATCH_MOUNT") = py::cast(B_WATCH_MOUNT);
m.attr("B_WATCH_INTERIM_STAT") = py::cast(B_WATCH_INTERIM_STAT);
m.attr("B_WATCH_CHILDREN") = py::cast(B_WATCH_CHILDREN);

m.attr("B_STAT_MODE") = py::cast(B_STAT_MODE);
m.attr("B_STAT_UID") = py::cast(B_STAT_UID);
m.attr("B_STAT_GID") = py::cast(B_STAT_GID);
m.attr("B_STAT_SIZE") = py::cast(B_STAT_SIZE);
m.attr("B_STAT_ACCESS_TIME") = py::cast(B_STAT_ACCESS_TIME);
m.attr("B_STAT_MODIFICATION_TIME") = py::cast(B_STAT_MODIFICATION_TIME);
m.attr("B_STAT_CREATION_TIME") = py::cast(B_STAT_CREATION_TIME);
m.attr("B_STAT_CHANGE_TIME") = py::cast(B_STAT_CHANGE_TIME);
m.attr("B_STAT_INTERIM_UPDATE") = py::cast(B_STAT_INTERIM_UPDATE);

m.def("watch_volume", py::overload_cast<dev_t, unsigned int, BMessenger>(&watch_volume), "", py::arg("volume"), py::arg("flags"), py::arg("target"));

m.def("watch_volume", py::overload_cast<dev_t, unsigned int, const BHandler *, const BLooper *>(&watch_volume), "", py::arg("volume"), py::arg("flags"), py::arg("handler"), py::arg("looper")=NULL);

m.def("watch_node", py::overload_cast<const node_ref *, unsigned int, BMessenger>(&watch_node), "", py::arg("node"), py::arg("flags"), py::arg("target"));

m.def("watch_node", py::overload_cast<const node_ref *, unsigned int, const BHandler *, const BLooper *>(&watch_node), "", py::arg("node"), py::arg("flags"), py::arg("handler"), py::arg("looper")=NULL);

m.def("stop_watching", py::overload_cast<BMessenger>(&stop_watching), "", py::arg("target"));

m.def("stop_watching", py::overload_cast<const BHandler *, const BLooper *>(&stop_watching), "", py::arg("handler"), py::arg("looper")=NULL);

}
