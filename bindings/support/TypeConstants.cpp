#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/TypeConstants.h>

namespace py = pybind11;


void define_TypeConstants(py::module_& m)
{
m.attr("B_AFFINE_TRANSFORM_TYPE") = py::cast(B_AFFINE_TRANSFORM_TYPE);
m.attr("B_ALIGNMENT_TYPE") = py::cast(B_ALIGNMENT_TYPE);
m.attr("B_ANY_TYPE") = py::cast(B_ANY_TYPE);
m.attr("B_ATOM_TYPE") = py::cast(B_ATOM_TYPE);
m.attr("B_ATOMREF_TYPE") = py::cast(B_ATOMREF_TYPE);
m.attr("B_BOOL_TYPE") = py::cast(B_BOOL_TYPE);
m.attr("B_CHAR_TYPE") = py::cast(B_CHAR_TYPE);
m.attr("B_COLOR_8_BIT_TYPE") = py::cast(B_COLOR_8_BIT_TYPE);
m.attr("B_DOUBLE_TYPE") = py::cast(B_DOUBLE_TYPE);
m.attr("B_FLOAT_TYPE") = py::cast(B_FLOAT_TYPE);
m.attr("B_GRAYSCALE_8_BIT_TYPE") = py::cast(B_GRAYSCALE_8_BIT_TYPE);
m.attr("B_INT16_TYPE") = py::cast(B_INT16_TYPE);
m.attr("B_INT32_TYPE") = py::cast(B_INT32_TYPE);
m.attr("B_INT64_TYPE") = py::cast(B_INT64_TYPE);
m.attr("B_INT8_TYPE") = py::cast(B_INT8_TYPE);
m.attr("B_LARGE_ICON_TYPE") = py::cast(B_LARGE_ICON_TYPE);
m.attr("B_MEDIA_PARAMETER_GROUP_TYPE") = py::cast(B_MEDIA_PARAMETER_GROUP_TYPE);
m.attr("B_MEDIA_PARAMETER_TYPE") = py::cast(B_MEDIA_PARAMETER_TYPE);
m.attr("B_MEDIA_PARAMETER_WEB_TYPE") = py::cast(B_MEDIA_PARAMETER_WEB_TYPE);
m.attr("B_MESSAGE_TYPE") = py::cast(B_MESSAGE_TYPE);
m.attr("B_MESSENGER_TYPE") = py::cast(B_MESSENGER_TYPE);
m.attr("B_MIME_TYPE") = py::cast(B_MIME_TYPE);
m.attr("B_MINI_ICON_TYPE") = py::cast(B_MINI_ICON_TYPE);
m.attr("B_MONOCHROME_1_BIT_TYPE") = py::cast(B_MONOCHROME_1_BIT_TYPE);
m.attr("B_OBJECT_TYPE") = py::cast(B_OBJECT_TYPE);
m.attr("B_OFF_T_TYPE") = py::cast(B_OFF_T_TYPE);
m.attr("B_PATTERN_TYPE") = py::cast(B_PATTERN_TYPE);
m.attr("B_POINTER_TYPE") = py::cast(B_POINTER_TYPE);
m.attr("B_POINT_TYPE") = py::cast(B_POINT_TYPE);
m.attr("B_PROPERTY_INFO_TYPE") = py::cast(B_PROPERTY_INFO_TYPE);
m.attr("B_RAW_TYPE") = py::cast(B_RAW_TYPE);
m.attr("B_RECT_TYPE") = py::cast(B_RECT_TYPE);
m.attr("B_REF_TYPE") = py::cast(B_REF_TYPE);
m.attr("B_NODE_REF_TYPE") = py::cast(B_NODE_REF_TYPE);
m.attr("B_RGB_32_BIT_TYPE") = py::cast(B_RGB_32_BIT_TYPE);
m.attr("B_RGB_COLOR_TYPE") = py::cast(B_RGB_COLOR_TYPE);
m.attr("B_SIZE_TYPE") = py::cast(B_SIZE_TYPE);
m.attr("B_SIZE_T_TYPE") = py::cast(B_SIZE_T_TYPE);
m.attr("B_SSIZE_T_TYPE") = py::cast(B_SSIZE_T_TYPE);
m.attr("B_STRING_TYPE") = py::cast(B_STRING_TYPE);
m.attr("B_STRING_LIST_TYPE") = py::cast(B_STRING_LIST_TYPE);
m.attr("B_TIME_TYPE") = py::cast(B_TIME_TYPE);
m.attr("B_UINT16_TYPE") = py::cast(B_UINT16_TYPE);
m.attr("B_UINT32_TYPE") = py::cast(B_UINT32_TYPE);
m.attr("B_UINT64_TYPE") = py::cast(B_UINT64_TYPE);
m.attr("B_UINT8_TYPE") = py::cast(B_UINT8_TYPE);
m.attr("B_VECTOR_ICON_TYPE") = py::cast(B_VECTOR_ICON_TYPE);
m.attr("B_XATTR_TYPE") = py::cast(B_XATTR_TYPE);
m.attr("B_NETWORK_ADDRESS_TYPE") = py::cast(B_NETWORK_ADDRESS_TYPE);
m.attr("B_MIME_STRING_TYPE") = py::cast(B_MIME_STRING_TYPE);
m.attr("B_ASCII_TYPE") = py::cast(B_ASCII_TYPE);

m.attr("B_URL_HTTP") = py::cast(B_URL_HTTP);

m.attr("B_URL_HTTPS") = py::cast(B_URL_HTTPS);

m.attr("B_URL_FTP") = py::cast(B_URL_FTP);

m.attr("B_URL_GOPHER") = py::cast(B_URL_GOPHER);

m.attr("B_URL_MAILTO") = py::cast(B_URL_MAILTO);

m.attr("B_URL_NEWS") = py::cast(B_URL_NEWS);

m.attr("B_URL_NNTP") = py::cast(B_URL_NNTP);

m.attr("B_URL_TELNET") = py::cast(B_URL_TELNET);

m.attr("B_URL_RLOGIN") = py::cast(B_URL_RLOGIN);

m.attr("B_URL_TN3270") = py::cast(B_URL_TN3270);

m.attr("B_URL_WAIS") = py::cast(B_URL_WAIS);

m.attr("B_URL_FILE") = py::cast(B_URL_FILE);


}
