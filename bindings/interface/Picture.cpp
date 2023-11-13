#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/Picture.h>
#include <InterfaceDefs.h>
#include <Rect.h>
#include <Archivable.h>

namespace py = pybind11;

int PlayWrapper(BPicture& picture, BMessage* callBackTable, int32 tableEntries, void* userData) {
    // Chiamare la funzione Play originale
    void* callBackTableVoidPtr = static_cast<void*>(callBackTable);
    return picture.Play(&callBackTableVoidPtr, tableEntries, userData);
}

PYBIND11_MODULE(Picture,m)
{
py::class_<BPicture, BArchivable>(m, "BPicture")
.def(py::init(), "")
.def(py::init<const BPicture &>(), "", py::arg("other"))
.def(py::init<BMessage *>(), "", py::arg("data"))
.def_static("Instantiate", &BPicture::Instantiate, "", py::arg("data"))
.def("Archive", &BPicture::Archive, "", py::arg("data"), py::arg("deep")=true)
.def("Perform", &BPicture::Perform, "", py::arg("code"), py::arg("arg"))
//.def("Play", &BPicture::Play, "", py::arg("callBackTable"), py::arg("tableEntries"), py::arg("userData"))
.def("Play", &PlayWrapper, "", py::arg("callBackTable"), py::arg("tableEntries"), py::arg("userData"))
.def("Flatten", &BPicture::Flatten, "", py::arg("stream"))
.def("Unflatten", &BPicture::Unflatten, "", py::arg("stream"))
//.def_readwrite("Private", &BPicture::Private, "")
;


}
