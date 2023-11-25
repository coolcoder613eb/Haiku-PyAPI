#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>
#include <TypeConstants.h>
#include <BeBuild.h>

namespace py = pybind11;

PYBIND11_MODULE(TypeConstants, m) {
    m.attr("B_AFFINE_TRANSFORM_TYPE") = 'AMTX';
    m.attr("B_ALIGNMENT_TYPE") = 'ALGN';
    m.attr("B_ANY_TYPE") = 'ANYT';
    m.attr("B_ATOM_TYPE") = 'ATOM';
    m.attr("B_ATOMREF_TYPE") = 'ATMR';
    m.attr("B_BOOL_TYPE") = 'BOOL';
    m.attr("B_CHAR_TYPE") = 'CHAR';
    m.attr("B_COLOR_8_BIT_TYPE") = 'CLRB';
    m.attr("B_DOUBLE_TYPE") = 'DBLE';
    m.attr("B_FLOAT_TYPE") = 'FLOT';
    m.attr("B_GRAYSCALE_8_BIT_TYPE") = 'GRYB';
    m.attr("B_INT16_TYPE") = 'SHRT';
    m.attr("B_INT32_TYPE") = 'LONG';
    m.attr("B_INT64_TYPE") = 'LLNG';
    m.attr("B_INT8_TYPE") = 'BYTE';
    m.attr("B_LARGE_ICON_TYPE") = 'ICON';
    m.attr("B_MEDIA_PARAMETER_GROUP_TYPE") = 'BMCG';
    m.attr("B_MEDIA_PARAMETER_TYPE") = 'BMCT';
    m.attr("B_MEDIA_PARAMETER_WEB_TYPE") = 'BMCW';
    m.attr("B_MESSAGE_TYPE") = 'MSGG';
    m.attr("B_MESSENGER_TYPE") = 'MSNG';
    m.attr("B_MIME_TYPE") = 'MIME';
    m.attr("B_MINI_ICON_TYPE") = 'MICN';
    m.attr("B_MONOCHROME_1_BIT_TYPE") = 'MNOB';
    m.attr("B_OBJECT_TYPE") = 'OPTR';
    m.attr("B_OFF_T_TYPE") = 'OFFT';
    m.attr("B_PATTERN_TYPE") = 'PATN';
    m.attr("B_POINTER_TYPE") = 'PNTR';
    m.attr("B_POINT_TYPE") = 'BPNT';
    m.attr("B_PROPERTY_INFO_TYPE") = 'SCTD';
    m.attr("B_RAW_TYPE") = 'RAWT';
    m.attr("B_RECT_TYPE") = 'RECT';
    m.attr("B_REF_TYPE") = 'RREF';
    m.attr("B_NODE_REF_TYPE") = 'NREF';
    m.attr("B_RGB_32_BIT_TYPE") = 'RGBB';
    m.attr("B_RGB_COLOR_TYPE") = 'RGBC';
    m.attr("B_SIZE_TYPE") = 'SIZE';
    m.attr("B_SIZE_T_TYPE") = 'SIZT';
    m.attr("B_SSIZE_T_TYPE") = 'SSZT';
    m.attr("B_STRING_TYPE") = 'CSTR';
    m.attr("B_STRING_LIST_TYPE") = 'STRL';
    m.attr("B_TIME_TYPE") = 'TIME';
    m.attr("B_UINT16_TYPE") = 'USHT';
    m.attr("B_UINT32_TYPE") = 'ULNG';
    m.attr("B_UINT64_TYPE") = 'ULLG';
    m.attr("B_UINT8_TYPE") = 'UBYT';
    m.attr("B_VECTOR_ICON_TYPE") = 'VICN';
    m.attr("B_XATTR_TYPE") = 'XATR';
    m.attr("B_NETWORK_ADDRESS_TYPE") = 'NWAD';
    m.attr("B_MIME_STRING_TYPE") = 'MIMS';
    m.attr("B_ASCII_TYPE") = 'TEXT';
    
}

