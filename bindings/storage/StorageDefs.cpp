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
m.attr("B_DEV_NAME_LENGTH") = B_DEV_NAME_LENGTH; //128
m.attr("B_FILE_NAME_LENGTH") = B_FILE_NAME_LENGTH; //NAME_MAX
m.attr("B_PATH_NAME_LENGTH") = B_PATH_NAME_LENGTH; //MAXPATHLEN
m.attr("B_ATTR_NAME_LENGTH") = B_ATTR_NAME_LENGTH; //(B_FILE_NAME_LENGTH - 1)
m.attr("B_MIME_TYPE_LENGTH") = B_MIME_TYPE_LENGTH; //(B_ATTR_NAME_LENGTH - 15)
m.attr("B_MAX_SYMLINKS") = B_MAX_SYMLINKS; //SYMLOOP_MAX


py::enum_<node_flavor>(m, "node_flavor", "")
.value("B_FILE_NODE", node_flavor::B_FILE_NODE, "")
.value("B_SYMLINK_NODE", node_flavor::B_SYMLINK_NODE, "")
.value("B_DIRECTORY_NODE", node_flavor::B_DIRECTORY_NODE, "")
.value("B_ANY_NODE", node_flavor::B_ANY_NODE, "")
.export_values();
m.attr("B_READ_ONLY") = 0;
m.attr("B_WRITE_ONLY") = 1;
m.attr("B_READ_WRITE") = 2;
m.attr("B_FAIL_IF_EXISTS") = 4;
m.attr("B_CREATE_FILE") = 8;
m.attr("B_ERASE_FILE") = 64;
m.attr("B_OPEN_AT_END") = 128;
//m.attr("B_CLONE_KIND") = 1048576;
}

