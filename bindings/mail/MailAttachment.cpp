#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <mail/MailAttachment.h>

namespace py = pybind11;


void define_MailAttachment(py::module_& m)
{
py::class_<BMailAttachment, BMailComponent>(m, "BMailAttachment")
.def("SetFileName", &BMailAttachment::SetFileName, "", py::arg("name"))
.def("FileName", &BMailAttachment::FileName, "", py::arg("name"))
.def("SetTo", py::overload_cast<BFile *, bool>(&BMailAttachment::SetTo), "", py::arg("file"), py::arg("deleteFileWhenDone")=false)
.def("SetTo", py::overload_cast<entry_ref *>(&BMailAttachment::SetTo), "", py::arg("ref"))
.def("InitCheck", &BMailAttachment::InitCheck, "")
;

py::class_<BSimpleMailAttachment, BMailAttachment>(m, "BSimpleMailAttachment")
.def(py::init<BPositionIO *, mail_encoding>(), "", py::arg("dataToAttach"), py::arg("encoding")=base64)
.def(py::init<const void *, size_t, mail_encoding>(), "", py::arg("dataToAttach"), py::arg("lengthOfData"), py::arg("encoding")=base64)
.def(py::init<BFile *, bool>(), "", py::arg("file"), py::arg("delete_when_done"))
.def(py::init<entry_ref *>(), "", py::arg("ref"))
.def(py::init(), "")
.def("SetTo", py::overload_cast<BFile *, bool>(&BSimpleMailAttachment::SetTo), "", py::arg("file"), py::arg("delete_file_when_done")=false)
.def("SetTo", py::overload_cast<entry_ref *>(&BSimpleMailAttachment::SetTo), "", py::arg("ref"))
.def("InitCheck", &BSimpleMailAttachment::InitCheck, "")
.def("SetFileName", &BSimpleMailAttachment::SetFileName, "", py::arg("name"))
.def("FileName", &BSimpleMailAttachment::FileName, "", py::arg("name"))
.def("GetDecodedData", py::overload_cast<BPositionIO *>(&BSimpleMailAttachment::GetDecodedData), "", py::arg("data"))
.def("SetDecodedData", py::overload_cast<BPositionIO *>(&BSimpleMailAttachment::SetDecodedData), "", py::arg("data"))
.def("GetDecodedData", py::overload_cast<>(&BSimpleMailAttachment::GetDecodedData), "")
.def("SetDecodedData", py::overload_cast<const void *, size_t>(&BSimpleMailAttachment::SetDecodedData), "", py::arg("data"), py::arg("length"))
.def("SetDecodedDataAndDeleteWhenDone", &BSimpleMailAttachment::SetDecodedDataAndDeleteWhenDone, "", py::arg("data"))
.def("SetEncoding", &BSimpleMailAttachment::SetEncoding, "", py::arg("encoding")=base64)
.def("Encoding", &BSimpleMailAttachment::Encoding, "")
.def("SetToRFC822", &BSimpleMailAttachment::SetToRFC822, "", py::arg("data"), py::arg("length"), py::arg("parse_now")=false)
.def("RenderToRFC822", &BSimpleMailAttachment::RenderToRFC822, "", py::arg("render_to"))
;

py::class_<BAttributedMailAttachment, BMailAttachment>(m, "BAttributedMailAttachment")
.def(py::init<BFile *, bool>(), "", py::arg("file"), py::arg("delete_when_done"))
.def(py::init<entry_ref *>(), "", py::arg("ref"))
.def(py::init(), "")
.def("SetTo", py::overload_cast<BFile *, bool>(&BAttributedMailAttachment::SetTo), "", py::arg("file"), py::arg("delete_file_when_done")=false)
.def("SetTo", py::overload_cast<entry_ref *>(&BAttributedMailAttachment::SetTo), "", py::arg("ref"))
.def("InitCheck", &BAttributedMailAttachment::InitCheck, "")
.def("SaveToDisk", &BAttributedMailAttachment::SaveToDisk, "", py::arg("entry"))
.def("SetEncoding", &BAttributedMailAttachment::SetEncoding, "", py::arg("encoding"))
.def("Encoding", &BAttributedMailAttachment::Encoding, "")
.def("FileName", &BAttributedMailAttachment::FileName, "", py::arg("name"))
.def("SetFileName", &BAttributedMailAttachment::SetFileName, "", py::arg("name"))
.def("GetDecodedData", &BAttributedMailAttachment::GetDecodedData, "", py::arg("data"))
.def("SetDecodedData", &BAttributedMailAttachment::SetDecodedData, "", py::arg("data"))
.def("SetToRFC822", &BAttributedMailAttachment::SetToRFC822, "", py::arg("data"), py::arg("length"), py::arg("parse_now")=false)
.def("RenderToRFC822", &BAttributedMailAttachment::RenderToRFC822, "", py::arg("render_to"))
.def("MIMEType", &BAttributedMailAttachment::MIMEType, "", py::arg("mime"))
;


}
