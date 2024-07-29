# Haiku-PyAPI

Python bindings for the Haiku API.

This lets you build apps for Haiku using the Haiku API directly from Python.

For the most part, Haiku-PyAPI tries to copy the C++ API. There are some places
where we have had to deviate from the C++ API, however.

## Current status

Currently, Haiku-PyAPI is best suited to scripts and small, simple
applications.

Almost everything in the app and interface kits have been ported. The storage
kit has mostly been ported. The support kit has only partially been ported.
The other kits haven't been ported yet.

Of the kits that have been ported, many of the functions haven't been tested
yet. You should, therefore, expect to encounter problems occasionally. Besides
this, you can expect memory leaks, as little work has been done on getting
memory freed correctly once it is no longer needed.

## Installing

Installation on Haiku is easy, just run

`pkgman install haiku_pyapi_python310`

or

`pkgman install haiku_pyapi_python39`

If you need the latest widgets and bugfixes, then you should compile from source, see below.

## Compiling

First, install the appropriate version of pybind11 for your CPU architecture and version of Python. For example, to install pybind11 for x86 and python3.10, run

`pkgman install pybind11_x86_python310`

The basic build command to build using all CPU cores is

`jam -j$(nproc)`

Extra build parameters can be specified, as discussed below.

### Build parameters

The build parameters can be used to change how the build is done. This can be
used to, for example, specify a different verson of python to build for. To
specify a build parameter, add `-sPARAMETER=VALUE` to the build command line.

| Parameter        | Description                                   |
| ---------------- | --------------------------------------------- |
| python_version   | Version of python to build for. Default: 3.10 |
| py               | Alias of `python_version`                     |
| type             | Debug or release build. Default: release      |
| build_location   | Location to put build files. Default: build/python$(python_version)_$(type) |
| install_location | Where to install build files to. Default: /boot/system/non-packaged/lib/python$(python_version)/site-packages |

## Example projects

This repository contains `test.py`, which is a simple "Hello world" program.
The matching game [BeMatched](https://github.com/coolcoder613eb/BeMatched)
provides another example of the library in use.
