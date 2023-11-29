#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/String.h>

namespace py = pybind11;


void define_String(py::module_& m)
{
py::class_<BString>(m, "BString")
.def(py::init(), "")
.def(py::init<const char *>(), "", py::arg("string"))
.def(py::init<const BString &>(), "", py::arg("string"))
.def(py::init<const char *, int>(), "", py::arg("string"), py::arg("maxLength"))
.def(py::init(), "")
.def("String", &BString::String, "")
.def("Length", &BString::Length, "")
.def("CountChars", &BString::CountChars, "")
.def("CountBytes", &BString::CountBytes, "", py::arg("fromCharOffset"), py::arg("charCount"))
.def("IsEmpty", &BString::IsEmpty, "")
.def("HashValue", py::overload_cast<>(&BString::HashValue), "")
.def_static("HashValue", py::overload_cast<const char *>(&BString::HashValue), "", py::arg("string"))
.def("operator=", py::overload_cast<const BString &>(&BString::operator=), "", py::arg("string"))
.def("operator=", py::overload_cast<const char *>(&BString::operator=), "", py::arg("string"))
.def("operator=", py::overload_cast<char>(&BString::operator=), "", py::arg("c"))
.def("operator=", [](BString& self) {
    BString &  string;
    BString & r = self.operator=(string);
    return std::make_tuple(r,string);
}
, "")
.def("SetTo", py::overload_cast<const char *>(&BString::SetTo), "", py::arg("string"))
.def("SetTo", py::overload_cast<const char *, int>(&BString::SetTo), "", py::arg("string"), py::arg("maxLength"))
.def("SetTo", py::overload_cast<const BString &>(&BString::SetTo), "", py::arg("string"))
.def("Adopt", [](BString& self) {
    BString  from;
    BString & r = self.Adopt(from);
    return std::make_tuple(r,from);
}
, "")
.def("SetTo", py::overload_cast<const BString &, int>(&BString::SetTo), "", py::arg("string"), py::arg("maxLength"))
.def("Adopt", [](BString& self,int maxLength) {
    BString  from;
    BString & r = self.Adopt(from, maxLength);
    return std::make_tuple(r,from);
}
, "", py::arg("maxLength"))
.def("SetTo", py::overload_cast<char, int>(&BString::SetTo), "", py::arg("c"), py::arg("count"))
.def("SetToChars", py::overload_cast<const char *, int>(&BString::SetToChars), "", py::arg("string"), py::arg("charCount"))
.def("SetToChars", py::overload_cast<const BString &, int>(&BString::SetToChars), "", py::arg("string"), py::arg("charCount"))
.def("AdoptChars", [](BString& self,int charCount) {
    BString  from;
    BString & r = self.AdoptChars(from, charCount);
    return std::make_tuple(r,from);
}
, "", py::arg("charCount"))
.def("SetToFormat", &BString::SetToFormat, "", py::arg("format"))
.def("SetToFormatVarArgs", &BString::SetToFormatVarArgs, "", py::arg("format"), py::arg("args"))
.def("ScanWithFormat", &BString::ScanWithFormat, "", py::arg("format"))
.def("ScanWithFormatVarArgs", &BString::ScanWithFormatVarArgs, "", py::arg("format"), py::arg("args"))
.def("CopyInto", [](BString& self,int fromOffset,int length) {
    BString  into;
    BString & r = self.CopyInto(into, fromOffset, length);
    return std::make_tuple(r,into);
}
, "", py::arg("fromOffset"), py::arg("length"))
.def("CopyInto", py::overload_cast<char *, int, int>(&BString::CopyInto), "", py::arg("into"), py::arg("fromOffset"), py::arg("length"))
.def("CopyCharsInto", [](BString& self,int fromCharOffset,int charCount) {
    BString  into;
    BString & r = self.CopyCharsInto(into, fromCharOffset, charCount);
    return std::make_tuple(r,into);
}
, "", py::arg("fromCharOffset"), py::arg("charCount"))
.def("CopyCharsInto", py::overload_cast<char *, int, int, int>(&BString::CopyCharsInto), "", py::arg("into"), py::arg("intoLength"), py::arg("fromCharOffset"), py::arg("charCount"))
.def("Split", [](BString& self,const char * separator,bool noEmptyStrings) {
    BStringList  _list;
    bool r = self.Split(separator, noEmptyStrings, _list);
    return std::make_tuple(r,_list);
}
, "", py::arg("separator"), py::arg("noEmptyStrings"))
.def("__iadd__", py::overload_cast<const BString &>(&BString::operator+=), "", py::arg("string"))
.def("__iadd__", py::overload_cast<const char *>(&BString::operator+=), "", py::arg("string"))
.def("__iadd__", py::overload_cast<char>(&BString::operator+=), "", py::arg("c"))
.def("Append", py::overload_cast<const BString &>(&BString::Append), "", py::arg("string"))
.def("Append", py::overload_cast<const char *>(&BString::Append), "", py::arg("string"))
.def("Append", py::overload_cast<const BString &, int>(&BString::Append), "", py::arg("string"), py::arg("length"))
.def("Append", py::overload_cast<const char *, int>(&BString::Append), "", py::arg("string"), py::arg("length"))
.def("Append", py::overload_cast<char, int>(&BString::Append), "", py::arg("c"), py::arg("count"))
.def("AppendChars", py::overload_cast<const BString &, int>(&BString::AppendChars), "", py::arg("string"), py::arg("charCount"))
.def("AppendChars", py::overload_cast<const char *, int>(&BString::AppendChars), "", py::arg("string"), py::arg("charCount"))
.def("Prepend", py::overload_cast<const char *>(&BString::Prepend), "", py::arg("string"))
.def("Prepend", py::overload_cast<const BString &>(&BString::Prepend), "", py::arg("string"))
.def("Prepend", py::overload_cast<const char *, int>(&BString::Prepend), "", py::arg("string"), py::arg("length"))
.def("Prepend", py::overload_cast<const BString &, int>(&BString::Prepend), "", py::arg("string"), py::arg("length"))
.def("Prepend", py::overload_cast<char, int>(&BString::Prepend), "", py::arg("c"), py::arg("count"))
.def("PrependChars", py::overload_cast<const char *, int>(&BString::PrependChars), "", py::arg("string"), py::arg("charCount"))
.def("PrependChars", py::overload_cast<const BString &, int>(&BString::PrependChars), "", py::arg("string"), py::arg("charCount"))
.def("Insert", py::overload_cast<const char *, int>(&BString::Insert), "", py::arg("string"), py::arg("position"))
.def("Insert", py::overload_cast<const char *, int, int>(&BString::Insert), "", py::arg("string"), py::arg("length"), py::arg("position"))
.def("Insert", py::overload_cast<const char *, int, int, int>(&BString::Insert), "", py::arg("string"), py::arg("fromOffset"), py::arg("length"), py::arg("position"))
.def("Insert", py::overload_cast<const BString &, int>(&BString::Insert), "", py::arg("string"), py::arg("position"))
.def("Insert", py::overload_cast<const BString &, int, int>(&BString::Insert), "", py::arg("string"), py::arg("length"), py::arg("position"))
.def("Insert", py::overload_cast<const BString &, int, int, int>(&BString::Insert), "", py::arg("string"), py::arg("fromOffset"), py::arg("length"), py::arg("position"))
.def("Insert", py::overload_cast<char, int, int>(&BString::Insert), "", py::arg("c"), py::arg("count"), py::arg("position"))
.def("InsertChars", py::overload_cast<const char *, int>(&BString::InsertChars), "", py::arg("string"), py::arg("charPosition"))
.def("InsertChars", py::overload_cast<const char *, int, int>(&BString::InsertChars), "", py::arg("string"), py::arg("charCount"), py::arg("charPosition"))
.def("InsertChars", py::overload_cast<const char *, int, int, int>(&BString::InsertChars), "", py::arg("string"), py::arg("fromCharOffset"), py::arg("charCount"), py::arg("charPosition"))
.def("InsertChars", py::overload_cast<const BString &, int>(&BString::InsertChars), "", py::arg("string"), py::arg("charPosition"))
.def("InsertChars", py::overload_cast<const BString &, int, int>(&BString::InsertChars), "", py::arg("string"), py::arg("charCount"), py::arg("charPosition"))
.def("InsertChars", py::overload_cast<const BString &, int, int, int>(&BString::InsertChars), "", py::arg("string"), py::arg("fromCharOffset"), py::arg("charCount"), py::arg("charPosition"))
.def("Truncate", &BString::Truncate, "", py::arg("newLength"), py::arg("lazy")=true)
.def("TruncateChars", &BString::TruncateChars, "", py::arg("newCharCount"), py::arg("lazy")=true)
.def("Remove", &BString::Remove, "", py::arg("from"), py::arg("length"))
.def("RemoveChars", &BString::RemoveChars, "", py::arg("fromCharOffset"), py::arg("charCount"))
.def("RemoveFirst", py::overload_cast<const BString &>(&BString::RemoveFirst), "", py::arg("string"))
.def("RemoveLast", py::overload_cast<const BString &>(&BString::RemoveLast), "", py::arg("string"))
.def("RemoveAll", py::overload_cast<const BString &>(&BString::RemoveAll), "", py::arg("string"))
.def("RemoveFirst", py::overload_cast<const char *>(&BString::RemoveFirst), "", py::arg("string"))
.def("RemoveLast", py::overload_cast<const char *>(&BString::RemoveLast), "", py::arg("string"))
.def("RemoveAll", py::overload_cast<const char *>(&BString::RemoveAll), "", py::arg("string"))
.def("RemoveSet", &BString::RemoveSet, "", py::arg("setOfBytesToRemove"))
.def("RemoveCharsSet", &BString::RemoveCharsSet, "", py::arg("setOfCharsToRemove"))
.def("MoveInto", [](BString& self,int from,int length) {
    BString  into;
    BString & r = self.MoveInto(into, from, length);
    return std::make_tuple(r,into);
}
, "", py::arg("from"), py::arg("length"))
.def("MoveInto", py::overload_cast<char *, int, int>(&BString::MoveInto), "", py::arg("into"), py::arg("from"), py::arg("length"))
.def("MoveCharsInto", [](BString& self,int fromCharOffset,int charCount) {
    BString  into;
    BString & r = self.MoveCharsInto(into, fromCharOffset, charCount);
    return std::make_tuple(r,into);
}
, "", py::arg("fromCharOffset"), py::arg("charCount"))
.def("MoveCharsInto", py::overload_cast<char *, int, int, int>(&BString::MoveCharsInto), "", py::arg("into"), py::arg("intoLength"), py::arg("fromCharOffset"), py::arg("charCount"))
.def("__lt__", py::overload_cast<const BString &>(&BString::operator<), "", py::arg("string"))
.def("__le__", py::overload_cast<const BString &>(&BString::operator<=), "", py::arg("string"))
.def("__eq__", py::overload_cast<const BString &>(&BString::operator==), "", py::arg("string"))
.def("__ge__", py::overload_cast<const BString &>(&BString::operator>=), "", py::arg("string"))
.def("__gt__", py::overload_cast<const BString &>(&BString::operator>), "", py::arg("string"))
.def("__ne__", py::overload_cast<const BString &>(&BString::operator!=), "", py::arg("string"))
.def("__lt__", py::overload_cast<const char *>(&BString::operator<), "", py::arg("string"))
.def("__le__", py::overload_cast<const char *>(&BString::operator<=), "", py::arg("string"))
.def("__eq__", py::overload_cast<const char *>(&BString::operator==), "", py::arg("string"))
.def("__ge__", py::overload_cast<const char *>(&BString::operator>=), "", py::arg("string"))
.def("__gt__", py::overload_cast<const char *>(&BString::operator>), "", py::arg("string"))
.def("__ne__", py::overload_cast<const char *>(&BString::operator!=), "", py::arg("string"))
.def("operatorconstchar*", &BString::operatorconstchar*, "")
.def("Compare", py::overload_cast<const BString &>(&BString::Compare), "", py::arg("string"))
.def("Compare", py::overload_cast<const char *>(&BString::Compare), "", py::arg("string"))
.def("Compare", py::overload_cast<const BString &, int>(&BString::Compare), "", py::arg("string"), py::arg("length"))
.def("Compare", py::overload_cast<const char *, int>(&BString::Compare), "", py::arg("string"), py::arg("length"))
.def("CompareAt", &BString::CompareAt, "", py::arg("offset"), py::arg("string"), py::arg("length"))
.def("CompareChars", py::overload_cast<const BString &, int>(&BString::CompareChars), "", py::arg("string"), py::arg("charCount"))
.def("CompareChars", py::overload_cast<const char *, int>(&BString::CompareChars), "", py::arg("string"), py::arg("charCount"))
.def("ICompare", py::overload_cast<const BString &>(&BString::ICompare), "", py::arg("string"))
.def("ICompare", py::overload_cast<const char *>(&BString::ICompare), "", py::arg("string"))
.def("ICompare", py::overload_cast<const BString &, int>(&BString::ICompare), "", py::arg("string"), py::arg("length"))
.def("ICompare", py::overload_cast<const char *, int>(&BString::ICompare), "", py::arg("string"), py::arg("length"))
.def("FindFirst", py::overload_cast<const BString &>(&BString::FindFirst), "", py::arg("string"))
.def("FindFirst", py::overload_cast<const char *>(&BString::FindFirst), "", py::arg("string"))
.def("FindFirst", py::overload_cast<const BString &, int>(&BString::FindFirst), "", py::arg("string"), py::arg("fromOffset"))
.def("FindFirst", py::overload_cast<const char *, int>(&BString::FindFirst), "", py::arg("string"), py::arg("fromOffset"))
.def("FindFirst", py::overload_cast<char>(&BString::FindFirst), "", py::arg("c"))
.def("FindFirst", py::overload_cast<char, int>(&BString::FindFirst), "", py::arg("c"), py::arg("fromOffset"))
.def("FindFirstChars", py::overload_cast<const BString &, int>(&BString::FindFirstChars), "", py::arg("string"), py::arg("fromCharOffset"))
.def("FindFirstChars", py::overload_cast<const char *, int>(&BString::FindFirstChars), "", py::arg("string"), py::arg("fromCharOffset"))
.def("FindLast", py::overload_cast<const BString &>(&BString::FindLast), "", py::arg("string"))
.def("FindLast", py::overload_cast<const char *>(&BString::FindLast), "", py::arg("string"))
.def("FindLast", py::overload_cast<const BString &, int>(&BString::FindLast), "", py::arg("string"), py::arg("beforeOffset"))
.def("FindLast", py::overload_cast<const char *, int>(&BString::FindLast), "", py::arg("string"), py::arg("beforeOffset"))
.def("FindLast", py::overload_cast<char>(&BString::FindLast), "", py::arg("c"))
.def("FindLast", py::overload_cast<char, int>(&BString::FindLast), "", py::arg("c"), py::arg("beforeOffset"))
.def("FindLastChars", py::overload_cast<const BString &, int>(&BString::FindLastChars), "", py::arg("string"), py::arg("beforeCharOffset"))
.def("FindLastChars", py::overload_cast<const char *, int>(&BString::FindLastChars), "", py::arg("string"), py::arg("beforeCharOffset"))
.def("IFindFirst", py::overload_cast<const BString &>(&BString::IFindFirst), "", py::arg("string"))
.def("IFindFirst", py::overload_cast<const char *>(&BString::IFindFirst), "", py::arg("string"))
.def("IFindFirst", py::overload_cast<const BString &, int>(&BString::IFindFirst), "", py::arg("string"), py::arg("fromOffset"))
.def("IFindFirst", py::overload_cast<const char *, int>(&BString::IFindFirst), "", py::arg("string"), py::arg("fromOffset"))
.def("IFindLast", py::overload_cast<const BString &>(&BString::IFindLast), "", py::arg("string"))
.def("IFindLast", py::overload_cast<const char *>(&BString::IFindLast), "", py::arg("string"))
.def("IFindLast", py::overload_cast<const BString &, int>(&BString::IFindLast), "", py::arg("string"), py::arg("beforeOffset"))
.def("IFindLast", py::overload_cast<const char *, int>(&BString::IFindLast), "", py::arg("string"), py::arg("beforeOffset"))
.def("StartsWith", py::overload_cast<const BString &>(&BString::StartsWith), "", py::arg("string"))
.def("StartsWith", py::overload_cast<const char *>(&BString::StartsWith), "", py::arg("string"))
.def("StartsWith", py::overload_cast<const char *, int>(&BString::StartsWith), "", py::arg("string"), py::arg("length"))
.def("IStartsWith", py::overload_cast<const BString &>(&BString::IStartsWith), "", py::arg("string"))
.def("IStartsWith", py::overload_cast<const char *>(&BString::IStartsWith), "", py::arg("string"))
.def("IStartsWith", py::overload_cast<const char *, int>(&BString::IStartsWith), "", py::arg("string"), py::arg("length"))
.def("EndsWith", py::overload_cast<const BString &>(&BString::EndsWith), "", py::arg("string"))
.def("EndsWith", py::overload_cast<const char *>(&BString::EndsWith), "", py::arg("string"))
.def("EndsWith", py::overload_cast<const char *, int>(&BString::EndsWith), "", py::arg("string"), py::arg("length"))
.def("IEndsWith", py::overload_cast<const BString &>(&BString::IEndsWith), "", py::arg("string"))
.def("IEndsWith", py::overload_cast<const char *>(&BString::IEndsWith), "", py::arg("string"))
.def("IEndsWith", py::overload_cast<const char *, int>(&BString::IEndsWith), "", py::arg("string"), py::arg("length"))
.def("ReplaceFirst", py::overload_cast<char, char>(&BString::ReplaceFirst), "", py::arg("replaceThis"), py::arg("withThis"))
.def("ReplaceLast", py::overload_cast<char, char>(&BString::ReplaceLast), "", py::arg("replaceThis"), py::arg("withThis"))
.def("ReplaceAll", py::overload_cast<char, char, int>(&BString::ReplaceAll), "", py::arg("replaceThis"), py::arg("withThis"), py::arg("fromOffset")=0)
.def("Replace", py::overload_cast<char, char, int, int>(&BString::Replace), "", py::arg("replaceThis"), py::arg("withThis"), py::arg("maxReplaceCount"), py::arg("fromOffset")=0)
.def("ReplaceFirst", py::overload_cast<const char *, const char *>(&BString::ReplaceFirst), "", py::arg("replaceThis"), py::arg("withThis"))
.def("ReplaceLast", py::overload_cast<const char *, const char *>(&BString::ReplaceLast), "", py::arg("replaceThis"), py::arg("withThis"))
.def("ReplaceAll", py::overload_cast<const char *, const char *, int>(&BString::ReplaceAll), "", py::arg("replaceThis"), py::arg("withThis"), py::arg("fromOffset")=0)
.def("Replace", py::overload_cast<const char *, const char *, int, int>(&BString::Replace), "", py::arg("replaceThis"), py::arg("withThis"), py::arg("maxReplaceCount"), py::arg("fromOffset")=0)
.def("ReplaceAllChars", &BString::ReplaceAllChars, "", py::arg("replaceThis"), py::arg("withThis"), py::arg("fromCharOffset"))
.def("ReplaceChars", &BString::ReplaceChars, "", py::arg("replaceThis"), py::arg("withThis"), py::arg("maxReplaceCount"), py::arg("fromCharOffset"))
.def("IReplaceFirst", py::overload_cast<char, char>(&BString::IReplaceFirst), "", py::arg("replaceThis"), py::arg("withThis"))
.def("IReplaceLast", py::overload_cast<char, char>(&BString::IReplaceLast), "", py::arg("replaceThis"), py::arg("withThis"))
.def("IReplaceAll", py::overload_cast<char, char, int>(&BString::IReplaceAll), "", py::arg("replaceThis"), py::arg("withThis"), py::arg("fromOffset")=0)
.def("IReplace", py::overload_cast<char, char, int, int>(&BString::IReplace), "", py::arg("replaceThis"), py::arg("withThis"), py::arg("maxReplaceCount"), py::arg("fromOffset")=0)
.def("IReplaceFirst", py::overload_cast<const char *, const char *>(&BString::IReplaceFirst), "", py::arg("replaceThis"), py::arg("withThis"))
.def("IReplaceLast", py::overload_cast<const char *, const char *>(&BString::IReplaceLast), "", py::arg("replaceThis"), py::arg("withThis"))
.def("IReplaceAll", py::overload_cast<const char *, const char *, int>(&BString::IReplaceAll), "", py::arg("replaceThis"), py::arg("withThis"), py::arg("fromOffset")=0)
.def("IReplace", py::overload_cast<const char *, const char *, int, int>(&BString::IReplace), "", py::arg("replaceThis"), py::arg("withThis"), py::arg("maxReplaceCount"), py::arg("fromOffset")=0)
.def("ReplaceSet", py::overload_cast<const char *, char>(&BString::ReplaceSet), "", py::arg("setOfBytes"), py::arg("with"))
.def("ReplaceSet", py::overload_cast<const char *, const char *>(&BString::ReplaceSet), "", py::arg("setOfBytes"), py::arg("with"))
.def("ReplaceCharsSet", &BString::ReplaceCharsSet, "", py::arg("setOfChars"), py::arg("with"))
.def("__getitem__", py::overload_cast<int>(&BString::operator[]), "", py::arg("index"))
.def("__getitem__", py::overload_cast<int>(&BString::operator[]), "", py::arg("index"))
.def("ByteAt", &BString::ByteAt, "", py::arg("index"))
.def("CharAt", py::overload_cast<int, int>(&BString::CharAt), "", py::arg("charIndex"), py::arg("bytes")=NULL)
.def("CharAt", py::overload_cast<int, char *, int>(&BString::CharAt), "", py::arg("charIndex"), py::arg("buffer"), py::arg("bytes"))
.def("LockBuffer", &BString::LockBuffer, "", py::arg("maxLength"))
.def("UnlockBuffer", &BString::UnlockBuffer, "", py::arg("length")=- 1)
.def("SetByteAt", &BString::SetByteAt, "", py::arg("pos"), py::arg("to"))
.def("ToLower", &BString::ToLower, "")
.def("ToUpper", &BString::ToUpper, "")
.def("Capitalize", &BString::Capitalize, "")
.def("CapitalizeEachWord", &BString::CapitalizeEachWord, "")
.def("CharacterEscape", py::overload_cast<const char *, const char *, char>(&BString::CharacterEscape), "", py::arg("original"), py::arg("setOfCharsToEscape"), py::arg("escapeWith"))
.def("CharacterEscape", py::overload_cast<const char *, char>(&BString::CharacterEscape), "", py::arg("setOfCharsToEscape"), py::arg("escapeWith"))
.def("CharacterDeescape", py::overload_cast<const char *, char>(&BString::CharacterDeescape), "", py::arg("original"), py::arg("escapeChar"))
.def("CharacterDeescape", py::overload_cast<char>(&BString::CharacterDeescape), "", py::arg("escapeChar"))
.def("Trim", &BString::Trim, "")
.def("__lshift__", py::overload_cast<const char *>(&BString::operator<<), "", py::arg("string"))
.def("__lshift__", py::overload_cast<const BString &>(&BString::operator<<), "", py::arg("string"))
.def("__lshift__", py::overload_cast<char>(&BString::operator<<), "", py::arg("c"))
.def("__lshift__", py::overload_cast<bool>(&BString::operator<<), "", py::arg("value"))
.def("__lshift__", py::overload_cast<int>(&BString::operator<<), "", py::arg("value"))
.def("__lshift__", py::overload_cast<unsigned int>(&BString::operator<<), "", py::arg("value"))
.def("__lshift__", py::overload_cast<unsigned long>(&BString::operator<<), "", py::arg("value"))
.def("__lshift__", py::overload_cast<long>(&BString::operator<<), "", py::arg("value"))
.def("__lshift__", py::overload_cast<unsigned long long>(&BString::operator<<), "", py::arg("value"))
.def("__lshift__", py::overload_cast<long long>(&BString::operator<<), "", py::arg("value"))
.def("__lshift__", py::overload_cast<float>(&BString::operator<<), "", py::arg("value"))
.def("__lshift__", py::overload_cast<double>(&BString::operator<<), "", py::arg("value"))
.def_readwrite("Private", &BString::Private, "")
;

m.def("__lt__", py::overload_cast<const char *, const BString &>(&operator<), "", py::arg("a"), py::arg("b"));

m.def("__le__", py::overload_cast<const char *, const BString &>(&operator<=), "", py::arg("a"), py::arg("b"));

m.def("__eq__", py::overload_cast<const char *, const BString &>(&operator==), "", py::arg("a"), py::arg("b"));

m.def("__gt__", py::overload_cast<const char *, const BString &>(&operator>), "", py::arg("a"), py::arg("b"));

m.def("__ge__", py::overload_cast<const char *, const BString &>(&operator>=), "", py::arg("a"), py::arg("b"));

m.def("__ne__", py::overload_cast<const char *, const BString &>(&operator!=), "", py::arg("a"), py::arg("b"));

m.def("Compare", py::overload_cast<const BString &, const BString &>(&Compare), "", py::arg("a"), py::arg("b"));

m.def("ICompare", py::overload_cast<const BString &, const BString &>(&ICompare), "", py::arg("a"), py::arg("b"));

m.def("Compare", py::overload_cast<const BString *, const BString *>(&Compare), "", py::arg("a"), py::arg("b"));

m.def("ICompare", py::overload_cast<const BString *, const BString *>(&ICompare), "", py::arg("a"), py::arg("b"));

m.def("__getitem__", &operator[], "", py::arg("index"));

m.def("__iadd__", &operator+=, "", py::arg("string"));

m.def("__eq__", py::overload_cast<const BString &>(&operator==), "", py::arg("string"));

m.def("__lt__", py::overload_cast<const BString &>(&operator<), "", py::arg("string"));

m.def("__le__", py::overload_cast<const BString &>(&operator<=), "", py::arg("string"));

m.def("__ge__", py::overload_cast<const BString &>(&operator>=), "", py::arg("string"));

m.def("__gt__", py::overload_cast<const BString &>(&operator>), "", py::arg("string"));

m.def("__ne__", py::overload_cast<const BString &>(&operator!=), "", py::arg("string"));

m.def("__ne__", py::overload_cast<const char *>(&operator!=), "", py::arg("string"));

m.def("operatorconstchar*", &operatorconstchar*, "");

m.def("__lt__", py::overload_cast<const char *, const BString &>(&operator<), "", py::arg("str"), py::arg("string"));

m.def("__le__", py::overload_cast<const char *, const BString &>(&operator<=), "", py::arg("str"), py::arg("string"));

m.def("__eq__", py::overload_cast<const char *, const BString &>(&operator==), "", py::arg("str"), py::arg("string"));

m.def("__gt__", py::overload_cast<const char *, const BString &>(&operator>), "", py::arg("str"), py::arg("string"));

m.def("__ge__", py::overload_cast<const char *, const BString &>(&operator>=), "", py::arg("str"), py::arg("string"));

m.def("__ne__", py::overload_cast<const char *, const BString &>(&operator!=), "", py::arg("str"), py::arg("string"));

}
