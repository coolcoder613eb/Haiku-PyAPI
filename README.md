# Haiku-PyAPI

Python bindings for the Haiku API.

This lets you build apps for Haiku using the Haiku API directly from Python.

For the most part, Haiku-PyAPI tries to copy the C++ API. There are some places
where we have had to deviate from the C++ API, however.

## Current status

Virtually everything from Haiku's API is available. It is likely that you will
run into some bugs if you try to make an application. Please report them! Also,
there's a good chance we can give you a workaround to use until it is fixed.

Probably, the biggest bug is memory leaks. Unless memory management for a class
was simple for us to do, it is likely that we opted to never free the memory
so that we could worry about memory management later!

## Installing

### From HaikuPorts

Installation on Haiku is easy, just run

```
pkgman install haiku_pyapi_python310
```

If you need the latest widgets and bugfixes, then you should compile from source, see below.

### From source

First, clone the source code, with submodules:
```
git clone https://github.com/coolcder613eb/Haiku-PyAPI --recursive
```

The basic build command to build using all CPU cores is
```
jam -j$(nproc)
```
Extra build parameters can be specified, as discussed below.

Finally, to install, simply run
```
jam install
```
Haiku-PyAPI should now be installed and ready to use.


## Build parameters

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

This repository contains `example.py`, which is a simple "Hello world" program.
Other examples:
- https://github.com/coolcoder613eb/Bemini
- https://github.com/coolcoder613eb/BeMatched
- https://github.com/tmtfx/HaiQR
- https://github.com/tmtfx/FeedGator
- https://github.com/tmtfx/HTPBZ2
- https://github.com/tmtfx/HaikuPO
- https://github.com/robante15/Haiku-PyAPI_Examples
