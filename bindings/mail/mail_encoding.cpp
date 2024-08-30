#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <mail/mail_encoding.h>

namespace py = pybind11;


void define_mail_encoding(py::module_& m)
{
py::enum_<mail_encoding>(m, "mail_encoding", "")
.value("base64", mail_encoding::base64, "")
.value("quoted_printable", mail_encoding::quoted_printable, "")
.value("seven_bit", mail_encoding::seven_bit, "")
.value("eight_bit", mail_encoding::eight_bit, "")
.value("uuencode", mail_encoding::uuencode, "")
.value("null_encoding", mail_encoding::null_encoding, "")
.value("no_encoding", mail_encoding::no_encoding, "")
.export_values();

m.def("encode", &encode, "", py::arg("encoding"), py::arg("out"), py::arg("in"), py::arg("length"), py::arg("headerMode"));

m.def("decode", &decode, "", py::arg("encoding"), py::arg("out"), py::arg("in"), py::arg("length"), py::arg("underscore_is_space"));

m.def("max_encoded_length", &max_encoded_length, "", py::arg("encoding"), py::arg("cur_length"));

m.def("encoding_for_cte", &encoding_for_cte, "", py::arg("content_transfer_encoding"));

m.def("encode_base64", &encode_base64, "", py::arg("out"), py::arg("in"), py::arg("length"), py::arg("headerMode"));

m.def("decode_base64", &decode_base64, "", py::arg("out"), py::arg("in"), py::arg("length"));

m.def("encode_qp", &encode_qp, "", py::arg("out"), py::arg("in"), py::arg("length"), py::arg("headerMode"));

m.def("decode_qp", &decode_qp, "", py::arg("out"), py::arg("in"), py::arg("length"), py::arg("underscore_is_space"));

m.def("uu_decode", &uu_decode, "", py::arg("out"), py::arg("in"), py::arg("length"));

}
