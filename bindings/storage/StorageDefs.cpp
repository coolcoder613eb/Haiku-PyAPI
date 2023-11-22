#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <storage/StorageDefs.h>
#include <fcntl.h>
#include <sys/param.h>
#include <limits.h>

namespace py = pybind11;
//Check the StorageDefs.h as a lot of define values are not here

PYBIND11_MODULE(StorageDefs,m)
{
py::enum_<node_flavor>(m, "node_flavor", "")
.value("B_FILE_NODE", node_flavor::B_FILE_NODE, "")
.value("B_SYMLINK_NODE", node_flavor::B_SYMLINK_NODE, "")
.value("B_DIRECTORY_NODE", node_flavor::B_DIRECTORY_NODE, "")
.value("B_ANY_NODE", node_flavor::B_ANY_NODE, "")
.export_values();
}
