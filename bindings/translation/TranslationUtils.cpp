#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <translation/TranslationUtils.h>
#include <TranslatorRoster.h>
#include <Bitmap.h>
#include <Entry.h>
#include <DataIO.h>
#include <TextView.h>
#include <File.h>
#include <Message.h>
#include <Menu.h>

namespace py = pybind11;


PYBIND11_MODULE(TranslationUtils, m)
{
py::class_<BTranslationUtils,std::unique_ptr<BTranslationUtils, py::nodelete>>(m, "BTranslationUtils")
.def_static("GetBitmap", py::overload_cast<const char *, BTranslatorRoster *>(&BTranslationUtils::GetBitmap), "", py::arg("name"), py::arg("roster")=NULL)
.def_static("GetBitmap", py::overload_cast<uint32, int32, BTranslatorRoster *>(&BTranslationUtils::GetBitmap), "", py::arg("type"), py::arg("id"), py::arg("roster")=NULL)
.def_static("GetBitmap", py::overload_cast<uint32, const char *, BTranslatorRoster *>(&BTranslationUtils::GetBitmap), "", py::arg("type"), py::arg("name"), py::arg("roster")=NULL)
.def_static("GetBitmapFile", &BTranslationUtils::GetBitmapFile, "", py::arg("name"), py::arg("roster")=NULL)
.def_static("GetBitmap", py::overload_cast<const entry_ref *, BTranslatorRoster *>(&BTranslationUtils::GetBitmap), "", py::arg("ref"), py::arg("roster")=NULL)
.def_static("GetBitmap", py::overload_cast<BPositionIO *, BTranslatorRoster *>(&BTranslationUtils::GetBitmap), "", py::arg("stream"), py::arg("roster")=NULL)
//.def_static("SetBitmapColorSpace", &BTranslationUtils::SetBitmapColorSpace, "", py::arg("space"))
//.def_static("BitmapColorSpace", &BTranslationUtils::BitmapColorSpace, "")
.def_static("GetStyledText", py::overload_cast<BPositionIO *, BTextView *, BTranslatorRoster *>(&BTranslationUtils::GetStyledText), "", py::arg("fromStream"), py::arg("intoView"), py::arg("roster")=NULL)
.def_static("GetStyledText", py::overload_cast<BPositionIO *, BTextView *, const char *, BTranslatorRoster *>(&BTranslationUtils::GetStyledText), "", py::arg("fromStream"), py::arg("intoView"), py::arg("encoding"), py::arg("roster")=NULL)
.def_static("PutStyledText", &BTranslationUtils::PutStyledText, "", py::arg("fromView"), py::arg("intoStream"), py::arg("roster")=NULL)
.def_static("WriteStyledEditFile", py::overload_cast<BTextView *, BFile *>(&BTranslationUtils::WriteStyledEditFile), "", py::arg("fromView"), py::arg("intoFile"))
.def_static("WriteStyledEditFile", py::overload_cast<BTextView *, BFile *, const char *>(&BTranslationUtils::WriteStyledEditFile), "", py::arg("fromView"), py::arg("intoFile"), py::arg("encoding"))
.def_static("GetDefaultSettings", py::overload_cast<translator_id, BTranslatorRoster *>(&BTranslationUtils::GetDefaultSettings), "", py::arg("translator"), py::arg("roster")=NULL)
.def_static("GetDefaultSettings", py::overload_cast<const char *, int32>(&BTranslationUtils::GetDefaultSettings), "", py::arg("name"), py::arg("version"))
.def_static("AddTranslationItems", &BTranslationUtils::AddTranslationItems, "", py::arg("intoMenu"), py::arg("fromType"), py::arg("model")=NULL, py::arg("idName")=NULL, py::arg("typeName")=NULL, py::arg("roster")=NULL)
;


}
