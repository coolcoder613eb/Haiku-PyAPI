#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <kernel/fs_attr.h>
#include <OS.h>
#include <dirent.h>

namespace py = pybind11;


PYBIND11_MODULE(fs_attr,m)
{
py::class_<attr_info>(m, "attr_info")
.def(py::init(), "")
.def_readwrite("type", &attr_info::type, "")
.def_readwrite("size", &attr_info::size, "")
//.export_values();
;


m.def("fs_read_attr", &fs_read_attr, "", py::arg("fd"), py::arg("attribute"), py::arg("type"), py::arg("pos"), py::arg("buffer"), py::arg("readBytes"));
m.def("fs_write_attr", &fs_write_attr, "", py::arg("fd"), py::arg("attribute"), py::arg("type"), py::arg("pos"), py::arg("buffer"), py::arg("readBytes"));
m.def("fs_remove_attr", &fs_remove_attr, "", py::arg("fd"), py::arg("attribute"));
m.def("fs_stat_attr", &fs_stat_attr, "", py::arg("fd"), py::arg("attribute"), py::arg("attrInfo"));
m.def("fs_open_attr", &fs_open_attr, "", py::arg("path"), py::arg("attribute"), py::arg("type"), py::arg("openMode"));
m.def("fs_fopen_attr", &fs_fopen_attr, "", py::arg("fd"), py::arg("attribute"), py::arg("type"), py::arg("openMode"));
m.def("fs_close_attr", &fs_close_attr, "", py::arg("fd"));
/*
m.def("fs_open_attr_dir", &fs_open_attr_dir, "", py::arg("path"));
m.def("fs_lopen_attr_dir", &fs_lopen_attr_dir, "", py::arg("path"));
m.def("fs_fopen_attr_dir", &fs_fopen_attr_dir, "", py::arg("fd"));
m.def("fs_close_attr_dir", &fs_close_attr_dir, "", py::arg("dir"));
m.def("fs_read_attr_dir", &fs_read_attr_dir, "", py::arg("dir"));
m.def("fs_rewind_attr_dir", &fs_rewind_attr_dir, "", py::arg("dir"));
*/

}
