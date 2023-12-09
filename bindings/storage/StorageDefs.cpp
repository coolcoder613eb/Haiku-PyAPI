#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <StorageDefs.h>
#include <fcntl.h>
#include <sys/param.h>
#include <limits.h>

namespace py = pybind11;
//using namespace BPrivate;
//using namespace BPrivate::Storage;
//using namespace BPrivate::Storage::Mime;
//using namespace BPackageKit;


PYBIND11_MODULE(StorageDefs,m)
{
py::enum_<node_flavor>(m, "node_flavor", "")
.value("B_FILE_NODE", node_flavor::B_FILE_NODE, "")
.value("B_SYMLINK_NODE", node_flavor::B_SYMLINK_NODE, "")
.value("B_DIRECTORY_NODE", node_flavor::B_DIRECTORY_NODE, "")
.value("B_ANY_NODE", node_flavor::B_ANY_NODE, "")
.export_values();

}
