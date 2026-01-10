/*
 * Copyright 2023, Fabio Tomat <f.t.public@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <sys/stat.h>

namespace py = pybind11;

void expose_stat(py::module &m) {
	py::class_<struct stat>(m, "stat")
		.def(py::init<>())
		.def_readwrite("st_dev", &stat::st_dev)
		.def_readwrite("st_ino", &stat::st_ino)
		.def_readwrite("st_mode", &stat::st_mode)
		.def_readwrite("st_nlink", &stat::st_nlink)
		.def_readwrite("st_uid", &stat::st_uid)
		.def_readwrite("st_gid", &stat::st_gid)
		.def_readwrite("st_size", &stat::st_size)
		.def_readwrite("st_rdev", &stat::st_rdev)
		.def_readwrite("st_blksize", &stat::st_blksize)
		//.def_readwrite("st_atim", &stat::st_atim)
		//.def_readwrite("st_mtim", &stat::st_mtim)
		//.def_readwrite("st_ctim", &stat::st_ctim)
		//.def_readwrite("st_crtim", &stat::st_crtim)
		.def_readwrite("st_type", &stat::st_type)
		.def_readwrite("st_blocks", &stat::st_blocks)
		.def_property_readonly("st_atim", [](const struct stat &s) {
			return (double)s.st_atim.tv_sec + (double)s.st_atim.tv_nsec / 1e9;
		})
		.def_property_readonly("st_mtim", [](const struct stat &s) {
			return (double)s.st_mtim.tv_sec + (double)s.st_mtim.tv_nsec / 1e9;
		})
		.def_property_readonly("st_ctim", [](const struct stat &s) {
			return (double)s.st_ctim.tv_sec + (double)s.st_ctim.tv_nsec / 1e9;
		})
		.def_property_readonly("st_crtime", [](const struct stat &s) {
			return (double)s.st_crtim.tv_sec + (double)s.st_crtim.tv_nsec / 1e9;
		})
		// Rappresentazione testuale per il debugging in Python
		.def("__repr__", [](const struct stat &s) {
			return "<Be.stat size=" + std::to_string(s.st_size) + ">";
		});
		
	m.def("S_ISDIR", [](int mode) { return S_ISDIR(mode); });
	m.def("S_ISCHR", [](int mode) { return S_ISCHR(mode); });
	m.def("S_ISBLK", [](int mode) { return S_ISBLK(mode); });
	m.def("S_ISREG", [](int mode) { return S_ISREG(mode); });
	m.def("S_ISFIFO", [](int mode) { return S_ISFIFO(mode); });
	m.def("S_ISLNK", [](int mode) { return S_ISLNK(mode); });
	m.def("S_ISSOCK", [](int mode) { return S_ISSOCK(mode); });

	m.attr("S_IFMT")   = py::int_(S_IFMT);
	m.attr("S_IFDIR")  = py::int_(S_IFDIR);
	m.attr("S_IFCHR")  = py::int_(S_IFCHR);
	m.attr("S_IFREG")  = py::int_(S_IFREG);
	m.attr("S_IFLNK")  = py::int_(S_IFLNK);
	
	m.attr("S_IRWXU")  = py::int_(S_IRWXU);
	m.attr("S_IRUSR")  = py::int_(S_IRUSR);
	m.attr("S_IWUSR")  = py::int_(S_IWUSR);
	m.attr("S_IXUSR")  = py::int_(S_IXUSR);
}
PYBIND11_MODULE(stat, m) {
	expose_stat(m);
}
