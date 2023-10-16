# Haiku-PyAPI

Python bindings for the Haiku API.

This lets you build apps for Haiku using the Haiku API directly from Python.

## Current status

The API is not stable and subject to change. The bindings for the app kit
are mostly complete, but a couple of functions are missing. The interface
kit has the essentials (buttons, text boxes, etc.), but many items are
missing. The other kits have not been ported yet.

## Installing

Installation on Haiku is easy, just run

`pkgman install haiku_pyapi_python310`

or

`pkgman install haiku_pyapi_python39`

## Compiling

To build for python 3.10 using all cpu cores, run

`jam -j$(nproc)`

### Build parameters

The build parameters can be used to change how the build is done. This can be
used to, for example, specify a different verson of python to build for. To
specify a build parameter, add `-sPARAMETER=VALUE` to the build command line.

| Parameter        | Description                                   |
| ---------------- | --------------------------------------------- |
| python_version   | Version of python to build for. Default: 3.10 |
| py               | Alias of `python_version`                     |
| install_location | Where to install build files to. Default: /boot/system/non-packaged/lib/python$(python_version)/site-packages |

## Example projects

This repository contains `test.py`, which is a simple "Hello world" program.
The matching game [BeMatched](https://github.com/coolcoder613eb/BeMatched)
provides another example of the library in use.
