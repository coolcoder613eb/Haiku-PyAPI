#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>
#include <pybind11/numpy.h>

#include <app/Message.h>
#include <new>
#include <BeBuild.h>
#include <DataIO.h>
#include <Entry.h>
#include <Flattenable.h>
#include <OS.h>
#include <Node.h>
#include <Rect.h>
#include <Size.h>
#include <AppDefs.h>		/* For convenience */
#include <TypeConstants.h>	/* For convenience */
#include <Messenger.h>
#include <String.h>
#include <StringList.h>
#include <Alignment.h>
#include <Handler.h>

namespace py = pybind11;


status_t GetInfoWrapper(BMessage& self, type_code typeRequested, int32 index,
		std::vector<char*> nameFound, type_code* typeFound, int32* countFound) {
	return self.GetInfo(typeRequested, index,
		nameFound.data(), typeFound, countFound);
}

status_t GetCurrentSpecifierWrapper(BMessage& self, int32* index,
		BMessage* specifier, int32* _what, std::string* property) {
	const char* p;
	status_t status = self.GetCurrentSpecifier(index, specifier, _what, &p);
	*property = p;
	return status;
}

status_t FindStringWrapper(BMessage& self, const char* name,
		std::string* string) {
	const char* s;
	status_t status = self.FindString(name, &s);
	*string = s;
	return status;
}

status_t FindStringWrapper(BMessage& self, const char* name,
		int32 index, std::string* string) {
	const char* s;
	status_t status = self.FindString(name, index, &s);
	*string = s;
	return status;
}

PYBIND11_MODULE(Message,m)
{
m.attr("B_NO_SPECIFIER") = 0;
m.attr("B_DIRECT_SPECIFIER") = 1;
m.attr("B_INDEX_SPECIFIER") = 2;
m.attr("B_REVERSE_INDEX_SPECIFIER") = 3;
m.attr("B_RANGE_SPECIFIER") = 4;
m.attr("B_REVERSE_RANGE_SPECIFIER") = 5;
m.attr("B_NAME_SPECIFIER") = 6;
m.attr("B_ID_SPECIFIER") = 7;
m.attr("B_SPECIFIERS_END") = 128;

py::class_<BMessage,std::unique_ptr<BMessage, py::nodelete>>(m, "BMessage")
.def(py::init(), "")
.def(py::init<uint32>(), "", py::arg("what"))
.def(py::init<const BMessage &>(), "", py::arg("other"))
.def("operator=", &BMessage::operator=, "", py::arg("other"))
.def("GetInfo", &GetInfoWrapper, "", py::arg("typeRequested"), py::arg("index"), py::arg("nameFound"), py::arg("typeFound"), py::arg("countFound")=NULL)
.def("GetInfo", py::overload_cast<const char *, type_code *, int32 *>(&BMessage::GetInfo, py::const_), "", py::arg("name"), py::arg("typeFound"), py::arg("countFound")=NULL)
.def("GetInfo", py::overload_cast<const char *, type_code *, bool *>(&BMessage::GetInfo, py::const_), "", py::arg("name"), py::arg("typeFound"), py::arg("fixedSize"))
.def("GetInfo", py::overload_cast<const char *, type_code *, int32 *, bool *>(&BMessage::GetInfo, py::const_), "", py::arg("name"), py::arg("typeFound"), py::arg("countFound"), py::arg("fixedSize"))
.def("CountNames", &BMessage::CountNames, "", py::arg("type"))
.def("IsEmpty", &BMessage::IsEmpty, "")
.def("IsSystem", &BMessage::IsSystem, "")
.def("IsReply", &BMessage::IsReply, "")
.def("PrintToStream", &BMessage::PrintToStream, "")
.def("Rename", &BMessage::Rename, "", py::arg("oldEntry"), py::arg("newEntry"))
.def("WasDelivered", &BMessage::WasDelivered, "")
.def("IsSourceWaiting", &BMessage::IsSourceWaiting, "")
.def("IsSourceRemote", &BMessage::IsSourceRemote, "")
.def("ReturnAddress", &BMessage::ReturnAddress, "")
.def("Previous", &BMessage::Previous, "")
.def("WasDropped", &BMessage::WasDropped, "")
.def("DropPoint", &BMessage::DropPoint, "", py::arg("offset")=NULL)

.def("SendReply", py::overload_cast<uint32, BHandler *>(&BMessage::SendReply), "", py::arg("command"), py::arg("replyTo")=NULL)
.def("SendReply", py::overload_cast<BMessage *, BHandler *, bigtime_t>(&BMessage::SendReply), "", py::arg("reply"), py::arg("replyTo")=NULL, py::arg("timeout")=B_INFINITE_TIMEOUT)
.def("SendReply", py::overload_cast<BMessage *, BMessenger, bigtime_t>(&BMessage::SendReply), "", py::arg("reply"), py::arg("replyTo"), py::arg("timeout")=B_INFINITE_TIMEOUT)
.def("SendReply", py::overload_cast<uint32, BMessage *>(&BMessage::SendReply), "", py::arg("command"), py::arg("replyToReply"))
.def("SendReply", py::overload_cast<BMessage *, BMessage *, bigtime_t, bigtime_t>(&BMessage::SendReply), "", py::arg("reply"), py::arg("replyToReply"), py::arg("sendTimeout")=B_INFINITE_TIMEOUT, py::arg("replyTimeout")=B_INFINITE_TIMEOUT)

.def("FlattenedSize", &BMessage::FlattenedSize, "")

.def("Flatten", py::overload_cast<char *, ssize_t>(&BMessage::Flatten, py::const_), "", py::arg("buffer"), py::arg("size"))
.def("Flatten", py::overload_cast<BDataIO *, ssize_t *>(&BMessage::Flatten, py::const_), "", py::arg("stream"), py::arg("size")=NULL)

.def("Unflatten", py::overload_cast<const char *>(&BMessage::Unflatten), "", py::arg("flatBuffer"))
.def("Unflatten", py::overload_cast<BDataIO *>(&BMessage::Unflatten), "", py::arg("stream"))

.def("AddSpecifier", py::overload_cast<const char *>(&BMessage::AddSpecifier), "", py::arg("property"))
.def("AddSpecifier", py::overload_cast<const char *, int32>(&BMessage::AddSpecifier), "", py::arg("property"), py::arg("index"))
.def("AddSpecifier", py::overload_cast<const char *, int32, int32>(&BMessage::AddSpecifier), "", py::arg("property"), py::arg("index"), py::arg("range"))
.def("AddSpecifier", py::overload_cast<const char *, const char *>(&BMessage::AddSpecifier), "", py::arg("property"), py::arg("name"))
.def("AddSpecifier", py::overload_cast<const BMessage *>(&BMessage::AddSpecifier), "", py::arg("specifier"))

.def("SetCurrentSpecifier", &BMessage::SetCurrentSpecifier, "", py::arg("index"))
.def("GetCurrentSpecifier", &GetCurrentSpecifierWrapper, "", py::arg("index"), py::arg("specifier")=NULL, py::arg("what")=NULL, py::arg("property")=NULL)
.def("HasSpecifiers", &BMessage::HasSpecifiers, "")
.def("PopSpecifier", &BMessage::PopSpecifier, "")
.def("AddAlignment", &BMessage::AddAlignment, "", py::arg("name"), py::arg("alignment"))
.def("AddRect", &BMessage::AddRect, "", py::arg("name"), py::arg("rect"))
.def("AddPoint", &BMessage::AddPoint, "", py::arg("name"), py::arg("point"))
.def("AddSize", &BMessage::AddSize, "", py::arg("name"), py::arg("size"))

.def("AddString", py::overload_cast<const char *, const char *>(&BMessage::AddString), "", py::arg("name"), py::arg("string"))
.def("AddString", py::overload_cast<const char *, const BString &>(&BMessage::AddString), "", py::arg("name"), py::arg("string"))
.def("AddStrings", &BMessage::AddStrings, "", py::arg("name"), py::arg("list"))

.def("AddInt8", &BMessage::AddInt8, "", py::arg("name"), py::arg("value"))
.def("AddUInt8", &BMessage::AddUInt8, "", py::arg("name"), py::arg("value"))
.def("AddInt16", &BMessage::AddInt16, "", py::arg("name"), py::arg("value"))
.def("AddUInt16", &BMessage::AddUInt16, "", py::arg("name"), py::arg("value"))
.def("AddInt32", &BMessage::AddInt32, "", py::arg("name"), py::arg("value"))
.def("AddUInt32", &BMessage::AddUInt32, "", py::arg("name"), py::arg("value"))
.def("AddInt64", &BMessage::AddInt64, "", py::arg("name"), py::arg("value"))
.def("AddUInt64", &BMessage::AddUInt64, "", py::arg("name"), py::arg("value"))

.def("AddBool", &BMessage::AddBool, "", py::arg("name"), py::arg("value"))
.def("AddFloat", &BMessage::AddFloat, "", py::arg("name"), py::arg("value"))
.def("AddDouble", &BMessage::AddDouble, "", py::arg("name"), py::arg("value"))
.def("AddColor", &BMessage::AddColor, "", py::arg("name"), py::arg("value"))
.def("AddPointer", &BMessage::AddPointer, "", py::arg("name"), py::arg("pointer"))
.def("AddMessenger", &BMessage::AddMessenger, "", py::arg("name"), py::arg("messenger"))

.def("AddRef", &BMessage::AddRef, "", py::arg("name"), py::arg("ref"))
.def("AddNodeRef", &BMessage::AddNodeRef, "", py::arg("name"), py::arg("ref"))
.def("AddMessage", &BMessage::AddMessage, "", py::arg("name"), py::arg("message"))
.def("AddFlat", py::overload_cast<const char *, BFlattenable *, int32>(&BMessage::AddFlat), "", py::arg("name"), py::arg("object"), py::arg("count")=1)
.def("AddFlat", py::overload_cast<const char *, const BFlattenable *, int32>(&BMessage::AddFlat), "", py::arg("name"), py::arg("object"), py::arg("count")=1)
//.def("AddData", &BMessage::AddData, "", py::arg("name"), py::arg("type"), py::arg("data"), py::arg("numBytes"), py::arg("isFixedSize")=true, py::arg("count")=1)
.def("AddData", [](BMessage& self, const char* name, type_code type, py::buffer data, ssize_t numBytes, bool isFixedSize, int32 count) { //const void* data 
	py::buffer_info info = data.request();
	const void* buffer = info.ptr;
	return self.AddData(name,type,buffer,numBytes,isFixedSize,count);
}, "", py::arg("name"), py::arg("type"), py::arg("data"), py::arg("numBytes"), py::arg("isFixedSize")=true, py::arg("count")=1)
.def("Append", &BMessage::Append, "", py::arg("message"))
.def("RemoveData", &BMessage::RemoveData, "", py::arg("name"), py::arg("index")=0)
.def("RemoveName", &BMessage::RemoveName, "", py::arg("name"))
.def("MakeEmpty", &BMessage::MakeEmpty, "")

.def("FindAlignment", py::overload_cast<const char *, BAlignment *>(&BMessage::FindAlignment, py::const_), "", py::arg("name"), py::arg("alignment"))
.def("FindAlignment", py::overload_cast<const char *, int32, BAlignment *>(&BMessage::FindAlignment, py::const_), "", py::arg("name"), py::arg("index"), py::arg("alignment"))
.def("FindRect", py::overload_cast<const char *, BRect *>(&BMessage::FindRect, py::const_), "", py::arg("name"), py::arg("rect"))
.def("FindRect", py::overload_cast<const char *, int32, BRect *>(&BMessage::FindRect, py::const_), "", py::arg("name"), py::arg("index"), py::arg("rect"))
.def("FindPoint", py::overload_cast<const char *, BPoint *>(&BMessage::FindPoint, py::const_), "", py::arg("name"), py::arg("point"))
.def("FindPoint", py::overload_cast<const char *, int32, BPoint *>(&BMessage::FindPoint, py::const_), "", py::arg("name"), py::arg("index"), py::arg("point"))
.def("FindSize", py::overload_cast<const char *, BSize *>(&BMessage::FindSize, py::const_), "", py::arg("name"), py::arg("size"))
.def("FindSize", py::overload_cast<const char *, int32, BSize *>(&BMessage::FindSize, py::const_), "", py::arg("name"), py::arg("index"), py::arg("size"))
.def("FindString", py::overload_cast<BMessage &, const char *, std::string *>(&FindStringWrapper), "", py::arg("name"), py::arg("string"))
.def("FindString", py::overload_cast<BMessage &, const char *, int32, std::string *>(&FindStringWrapper), "", py::arg("name"), py::arg("index"), py::arg("string"))
.def("FindString", py::overload_cast<const char *, BString *>(&BMessage::FindString, py::const_), "", py::arg("name"), py::arg("string"))
.def("FindString", py::overload_cast<const char *, int32, BString *>(&BMessage::FindString, py::const_), "", py::arg("name"), py::arg("index"), py::arg("string"))

.def("FindStrings", &BMessage::FindStrings, "", py::arg("name"), py::arg("list"))
.def("FindInt8", py::overload_cast<const char *, int8 *>(&BMessage::FindInt8, py::const_), "", py::arg("name"), py::arg("value"))
.def("FindInt8", py::overload_cast<const char *, int32, int8 *>(&BMessage::FindInt8, py::const_), "", py::arg("name"), py::arg("index"), py::arg("value"))
.def("FindUInt8", py::overload_cast<const char *, uint8 *>(&BMessage::FindUInt8, py::const_), "", py::arg("name"), py::arg("value"))
.def("FindUInt8", py::overload_cast<const char *, int32, uint8 *>(&BMessage::FindUInt8, py::const_), "", py::arg("name"), py::arg("index"), py::arg("value"))
.def("FindInt16", py::overload_cast<const char *, int16 *>(&BMessage::FindInt16, py::const_), "", py::arg("name"), py::arg("value"))
.def("FindInt16", py::overload_cast<const char *, int32, int16 *>(&BMessage::FindInt16, py::const_), "", py::arg("name"), py::arg("index"), py::arg("value"))
.def("FindUInt16", py::overload_cast<const char *, uint16 *>(&BMessage::FindUInt16, py::const_), "", py::arg("name"), py::arg("value"))
.def("FindUInt16", py::overload_cast<const char *, int32, uint16 *>(&BMessage::FindUInt16, py::const_), "", py::arg("name"), py::arg("index"), py::arg("value"))
.def("FindInt32", py::overload_cast<const char *, int32 *>(&BMessage::FindInt32, py::const_), "", py::arg("name"), py::arg("value"))
.def("FindInt32", py::overload_cast<const char *, int32, int32 *>(&BMessage::FindInt32, py::const_), "", py::arg("name"), py::arg("index"), py::arg("value"))
.def("FindUInt32", py::overload_cast<const char *, uint32 *>(&BMessage::FindUInt32, py::const_), "", py::arg("name"), py::arg("value"))
.def("FindUInt32", py::overload_cast<const char *, int32, uint32 *>(&BMessage::FindUInt32, py::const_), "", py::arg("name"), py::arg("index"), py::arg("value"))
.def("FindInt64", py::overload_cast<const char *, int64 *>(&BMessage::FindInt64, py::const_), "", py::arg("name"), py::arg("value"))
.def("FindInt64", py::overload_cast<const char *, int32, int64 *>(&BMessage::FindInt64, py::const_), "", py::arg("name"), py::arg("index"), py::arg("value"))
.def("FindUInt64", py::overload_cast<const char *, uint64 *>(&BMessage::FindUInt64, py::const_), "", py::arg("name"), py::arg("value"))
.def("FindUInt64", py::overload_cast<const char *, int32, uint64 *>(&BMessage::FindUInt64, py::const_), "", py::arg("name"), py::arg("index"), py::arg("value"))

.def("FindBool", py::overload_cast<const char *, bool *>(&BMessage::FindBool, py::const_), "", py::arg("name"), py::arg("value"))
.def("FindBool", py::overload_cast<const char *, int32, bool *>(&BMessage::FindBool, py::const_), "", py::arg("name"), py::arg("index"), py::arg("value"))
.def("FindFloat", py::overload_cast<const char *, float *>(&BMessage::FindFloat, py::const_), "", py::arg("name"), py::arg("value"))
.def("FindFloat", py::overload_cast<const char *, int32, float *>(&BMessage::FindFloat, py::const_), "", py::arg("name"), py::arg("index"), py::arg("value"))
.def("FindDouble", py::overload_cast<const char *, double *>(&BMessage::FindDouble, py::const_), "", py::arg("name"), py::arg("value"))
.def("FindDouble", py::overload_cast<const char *, int32, double *>(&BMessage::FindDouble, py::const_), "", py::arg("name"), py::arg("index"), py::arg("value"))

.def("FindColor", py::overload_cast<const char *, rgb_color *>(&BMessage::FindColor, py::const_), "", py::arg("name"), py::arg("value"))
.def("FindColor", py::overload_cast<const char *, int32, rgb_color *>(&BMessage::FindColor, py::const_), "", py::arg("name"), py::arg("index"), py::arg("value"))
//.def("FindPointer", py::overload_cast<const char *, void * *>(&BMessage::FindPointer, py::const_), "", py::arg("name"), py::arg("pointer"))
//.def("FindPointer", py::overload_cast<const char *, int32, void * *>(&BMessage::FindPointer, py::const_), "", py::arg("name"), py::arg("index"), py::arg("pointer"))

.def("FindMessenger", py::overload_cast<const char *, BMessenger *>(&BMessage::FindMessenger, py::const_), "", py::arg("name"), py::arg("messenger"))
.def("FindMessenger", py::overload_cast<const char *, int32, BMessenger *>(&BMessage::FindMessenger, py::const_), "", py::arg("name"), py::arg("index"), py::arg("messenger"))
.def("FindRef", py::overload_cast<const char *, entry_ref *>(&BMessage::FindRef, py::const_), "", py::arg("name"), py::arg("ref"))
.def("FindRef", py::overload_cast<const char *, int32, entry_ref *>(&BMessage::FindRef, py::const_), "", py::arg("name"), py::arg("index"), py::arg("ref"))

.def("FindNodeRef", py::overload_cast<const char *, node_ref *>(&BMessage::FindNodeRef, py::const_), "", py::arg("name"), py::arg("ref"))
.def("FindNodeRef", py::overload_cast<const char *, int32, node_ref *>(&BMessage::FindNodeRef, py::const_), "", py::arg("name"), py::arg("index"), py::arg("ref"))
.def("FindMessage", py::overload_cast<const char *, BMessage *>(&BMessage::FindMessage, py::const_), "", py::arg("name"), py::arg("message"))
.def("FindMessage", py::overload_cast<const char *, int32, BMessage *>(&BMessage::FindMessage, py::const_), "", py::arg("name"), py::arg("index"), py::arg("message"))

.def("FindFlat", py::overload_cast<const char *, BFlattenable *>(&BMessage::FindFlat, py::const_), "", py::arg("name"), py::arg("object"))
.def("FindFlat", py::overload_cast<const char *, int32, BFlattenable *>(&BMessage::FindFlat, py::const_), "", py::arg("name"), py::arg("index"), py::arg("object"))
//.def("FindData", py::overload_cast<const char *, type_code, const void * *, ssize_t *>(&BMessage::FindData, py::const_), "", py::arg("name"), py::arg("type"), py::arg("data"), py::arg("numBytes"))
.def("FindData", [](BMessage &self, const char *name, type_code type) -> py::tuple {
    const void *vdata = nullptr;
    ssize_t numBytes;
    status_t ret = self.FindData(name, type, &vdata, &numBytes);

    if (ret == B_OK && vdata != nullptr) {
        // Converte i dati in un oggetto py::bytes
        const unsigned char *dataPtr = static_cast<const unsigned char *>(vdata);
        py::bytes result(reinterpret_cast<const char *>(dataPtr), numBytes);
        return py::make_tuple(ret, result);
    }

    return py::make_tuple(ret, py::none());
}, "", py::arg("name"), py::arg("type"))
//.def("FindData", py::overload_cast<const char *, type_code, int32, const void * *, ssize_t *>(&BMessage::FindData, py::const_), "", py::arg("name"), py::arg("type"), py::arg("index"), py::arg("data"), py::arg("numBytes"))
.def("FindData", [](BMessage &self, const char *name, type_code type, int32 index) -> py::tuple {
    const void *vdata = nullptr;
    ssize_t numBytes;
    status_t ret = self.FindData(name, type, index, &vdata, &numBytes);

    if (ret == B_OK && vdata != nullptr) {
        // Converte i dati in un oggetto py::bytes
        const unsigned char *dataPtr = static_cast<const unsigned char *>(vdata);
        py::bytes result(reinterpret_cast<const char *>(dataPtr), numBytes);
        return py::make_tuple(ret, result);
    }

    return py::make_tuple(ret, py::none());
}, "", py::arg("name"), py::arg("type"), py::arg("index"))
.def("ReplaceAlignment", py::overload_cast<const char *, const BAlignment &>(&BMessage::ReplaceAlignment), "", py::arg("name"), py::arg("alignment"))
.def("ReplaceAlignment", py::overload_cast<const char *, int32, const BAlignment &>(&BMessage::ReplaceAlignment), "", py::arg("name"), py::arg("index"), py::arg("alignment"))
.def("ReplaceRect", py::overload_cast<const char *, BRect>(&BMessage::ReplaceRect), "", py::arg("name"), py::arg("rect"))
.def("ReplaceRect", py::overload_cast<const char *, int32, BRect>(&BMessage::ReplaceRect), "", py::arg("name"), py::arg("index"), py::arg("rect"))

.def("ReplacePoint", py::overload_cast<const char *, BPoint>(&BMessage::ReplacePoint), "", py::arg("name"), py::arg("aPoint"))
.def("ReplacePoint", py::overload_cast<const char *, int32, BPoint>(&BMessage::ReplacePoint), "", py::arg("name"), py::arg("index"), py::arg("aPoint"))
.def("ReplaceSize", py::overload_cast<const char *, BSize>(&BMessage::ReplaceSize), "", py::arg("name"), py::arg("aSize"))
.def("ReplaceSize", py::overload_cast<const char *, int32, BSize>(&BMessage::ReplaceSize), "", py::arg("name"), py::arg("index"), py::arg("aSize"))
.def("ReplaceString", py::overload_cast<const char *, const char *>(&BMessage::ReplaceString), "", py::arg("name"), py::arg("string"))
.def("ReplaceString", py::overload_cast<const char *, int32, const char *>(&BMessage::ReplaceString), "", py::arg("name"), py::arg("index"), py::arg("string"))
.def("ReplaceString", py::overload_cast<const char *, const BString &>(&BMessage::ReplaceString), "", py::arg("name"), py::arg("string"))
.def("ReplaceString", py::overload_cast<const char *, int32, const BString &>(&BMessage::ReplaceString), "", py::arg("name"), py::arg("index"), py::arg("string"))

.def("ReplaceInt8", py::overload_cast<const char *, signed char>(&BMessage::ReplaceInt8), "", py::arg("name"), py::arg("value"))
.def("ReplaceInt8", py::overload_cast<const char *, int32, signed char>(&BMessage::ReplaceInt8), "", py::arg("name"), py::arg("index"), py::arg("value"))
.def("ReplaceUInt8", py::overload_cast<const char *, unsigned char>(&BMessage::ReplaceUInt8), "", py::arg("name"), py::arg("value"))
.def("ReplaceUInt8", py::overload_cast<const char *, int32, unsigned char>(&BMessage::ReplaceUInt8), "", py::arg("name"), py::arg("index"), py::arg("value"))
.def("ReplaceInt16", py::overload_cast<const char *, int16>(&BMessage::ReplaceInt16), "", py::arg("name"), py::arg("value"))
.def("ReplaceInt16", py::overload_cast<const char *, int32, int16>(&BMessage::ReplaceInt16), "", py::arg("name"), py::arg("index"), py::arg("value"))
.def("ReplaceUInt16", py::overload_cast<const char *, uint16>(&BMessage::ReplaceUInt16), "", py::arg("name"), py::arg("value"))
.def("ReplaceUInt16", py::overload_cast<const char *, int32, uint16>(&BMessage::ReplaceUInt16), "", py::arg("name"), py::arg("index"), py::arg("value"))
.def("ReplaceInt32", py::overload_cast<const char *, int32>(&BMessage::ReplaceInt32), "", py::arg("name"), py::arg("value"))
.def("ReplaceInt32", py::overload_cast<const char *, int32, int32>(&BMessage::ReplaceInt32), "", py::arg("name"), py::arg("index"), py::arg("value"))
.def("ReplaceUInt32", py::overload_cast<const char *, uint32>(&BMessage::ReplaceUInt32), "", py::arg("name"), py::arg("value"))
.def("ReplaceUInt32", py::overload_cast<const char *, int32, uint32>(&BMessage::ReplaceUInt32), "", py::arg("name"), py::arg("index"), py::arg("value"))
.def("ReplaceInt64", py::overload_cast<const char *, int64_t>(&BMessage::ReplaceInt64), "", py::arg("name"), py::arg("value"))
.def("ReplaceInt64", py::overload_cast<const char *, int32, int64_t>(&BMessage::ReplaceInt64), "", py::arg("name"), py::arg("index"), py::arg("value"))
.def("ReplaceUInt64", py::overload_cast<const char *, uint64_t>(&BMessage::ReplaceUInt64), "", py::arg("name"), py::arg("value"))
.def("ReplaceUInt64", py::overload_cast<const char *, int32, uint64_t>(&BMessage::ReplaceUInt64), "", py::arg("name"), py::arg("index"), py::arg("value"))

.def("ReplaceBool", py::overload_cast<const char *, bool>(&BMessage::ReplaceBool), "", py::arg("name"), py::arg("aBoolean"))
.def("ReplaceBool", py::overload_cast<const char *, int32, bool>(&BMessage::ReplaceBool), "", py::arg("name"), py::arg("index"), py::arg("value"))
.def("ReplaceFloat", py::overload_cast<const char *, float>(&BMessage::ReplaceFloat), "", py::arg("name"), py::arg("value"))
.def("ReplaceFloat", py::overload_cast<const char *, int32, float>(&BMessage::ReplaceFloat), "", py::arg("name"), py::arg("index"), py::arg("value"))
.def("ReplaceDouble", py::overload_cast<const char *, double>(&BMessage::ReplaceDouble), "", py::arg("name"), py::arg("value"))
.def("ReplaceDouble", py::overload_cast<const char *, int32, double>(&BMessage::ReplaceDouble), "", py::arg("name"), py::arg("index"), py::arg("value"))
.def("ReplaceColor", py::overload_cast<const char *, rgb_color>(&BMessage::ReplaceColor), "", py::arg("name"), py::arg("value"))
.def("ReplaceColor", py::overload_cast<const char *, int32, rgb_color>(&BMessage::ReplaceColor), "", py::arg("name"), py::arg("index"), py::arg("value"))
.def("ReplacePointer", py::overload_cast<const char *, const void *>(&BMessage::ReplacePointer), "", py::arg("name"), py::arg("pointer"))
.def("ReplacePointer", py::overload_cast<const char *, int32, const void *>(&BMessage::ReplacePointer), "", py::arg("name"), py::arg("index"), py::arg("pointer"))
.def("ReplaceMessenger", py::overload_cast<const char *, BMessenger>(&BMessage::ReplaceMessenger), "", py::arg("name"), py::arg("messenger"))
.def("ReplaceMessenger", py::overload_cast<const char *, int32, BMessenger>(&BMessage::ReplaceMessenger), "", py::arg("name"), py::arg("index"), py::arg("messenger"))
.def("ReplaceRef", py::overload_cast<const char *, const entry_ref *>(&BMessage::ReplaceRef), "", py::arg("name"), py::arg("ref"))
.def("ReplaceRef", py::overload_cast<const char *, int32, const entry_ref *>(&BMessage::ReplaceRef), "", py::arg("name"), py::arg("index"), py::arg("ref"))
.def("ReplaceNodeRef", py::overload_cast<const char *, const node_ref *>(&BMessage::ReplaceNodeRef), "", py::arg("name"), py::arg("ref"))
.def("ReplaceNodeRef", py::overload_cast<const char *, int32, const node_ref *>(&BMessage::ReplaceNodeRef), "", py::arg("name"), py::arg("index"), py::arg("ref"))
.def("ReplaceMessage", py::overload_cast<const char *, const BMessage *>(&BMessage::ReplaceMessage), "", py::arg("name"), py::arg("message"))
.def("ReplaceMessage", py::overload_cast<const char *, int32, const BMessage *>(&BMessage::ReplaceMessage), "", py::arg("name"), py::arg("index"), py::arg("message"))
.def("ReplaceFlat", py::overload_cast<const char *, BFlattenable *>(&BMessage::ReplaceFlat), "", py::arg("name"), py::arg("object"))
.def("ReplaceFlat", py::overload_cast<const char *, int32, BFlattenable *>(&BMessage::ReplaceFlat), "", py::arg("name"), py::arg("index"), py::arg("object"))
.def("ReplaceData", py::overload_cast<const char *, type_code, const void *, ssize_t>(&BMessage::ReplaceData), "", py::arg("name"), py::arg("type"), py::arg("data"), py::arg("numBytes"))
.def("ReplaceData", py::overload_cast<const char *, type_code, int32, const void *, ssize_t>(&BMessage::ReplaceData), "", py::arg("name"), py::arg("type"), py::arg("index"), py::arg("data"), py::arg("numBytes"))

.def("HasSameData", &BMessage::HasSameData, "", py::arg("other"), py::arg("ignoreFieldOrder")=true, py::arg("deep")=false)
/*
.def("operatornew", py::overload_cast<size_t>(&BMessage::operatornew), "", py::arg("size"))
.def("operatornew", py::overload_cast<size_t, void *>(&BMessage::operatornew), "", py::arg(""), py::arg("pointer"))
.def("operatornew", py::overload_cast<size_t, const std::nothrow_t &>(&BMessage::operatornew), "", py::arg(""), py::arg("noThrow"))
.def("operatordelete", &BMessage::operatordelete, "", py::arg("pointer"), py::arg("size"))
*/

.def("HasAlignment", &BMessage::HasAlignment, "", py::arg("name"), py::arg("n")=0)
.def("HasRect", &BMessage::HasRect, "", py::arg("name"), py::arg("n")=0)
.def("HasPoint", &BMessage::HasPoint, "", py::arg("name"), py::arg("n")=0)
.def("HasSize", &BMessage::HasSize, "", py::arg("name"), py::arg("n")=0)
.def("HasString", &BMessage::HasString, "", py::arg("name"), py::arg("n")=0)
.def("HasInt8", &BMessage::HasInt8, "", py::arg("name"), py::arg("n")=0)
.def("HasUInt8", &BMessage::HasUInt8, "", py::arg("name"), py::arg("n")=0)
.def("HasInt16", &BMessage::HasInt16, "", py::arg("name"), py::arg("n")=0)
.def("HasUInt16", &BMessage::HasUInt16, "", py::arg("name"), py::arg("n")=0)
.def("HasInt32", &BMessage::HasInt32, "", py::arg("name"), py::arg("n")=0)
.def("HasUInt32", &BMessage::HasUInt32, "", py::arg("name"), py::arg("n")=0)
.def("HasInt64", &BMessage::HasInt64, "", py::arg("name"), py::arg("n")=0)
.def("HasUInt64", &BMessage::HasUInt64, "", py::arg("name"), py::arg("n")=0)

.def("HasBool", &BMessage::HasBool, "", py::arg("name"), py::arg("n")=0)
.def("HasFloat", &BMessage::HasFloat, "", py::arg("name"), py::arg("n")=0)
.def("HasDouble", &BMessage::HasDouble, "", py::arg("name"), py::arg("n")=0)
.def("HasColor", &BMessage::HasColor, "", py::arg("name"), py::arg("n")=0)
.def("HasPointer", &BMessage::HasPointer, "", py::arg("name"), py::arg("n")=0)
.def("HasMessenger", &BMessage::HasMessenger, "", py::arg("name"), py::arg("n")=0)
.def("HasRef", &BMessage::HasRef, "", py::arg("name"), py::arg("n")=0)
.def("HasNodeRef", &BMessage::HasNodeRef, "", py::arg("name"), py::arg("n")=0)
.def("HasMessage", &BMessage::HasMessage, "", py::arg("name"), py::arg("n")=0)

.def("HasFlat", py::overload_cast<const char *, const BFlattenable *>(&BMessage::HasFlat, py::const_), "", py::arg("name"), py::arg("object"))
.def("HasFlat", py::overload_cast<const char *, int32, const BFlattenable *>(&BMessage::HasFlat, py::const_), "", py::arg("name"), py::arg("n"), py::arg("object"))
.def("HasData", &BMessage::HasData, "", py::arg("name"), py::arg(""), py::arg("n")=0)
.def("FindRect", py::overload_cast<const char *, int32>(&BMessage::FindRect, py::const_), "", py::arg("name"), py::arg("n")=0)
.def("FindPoint", py::overload_cast<const char *, int32>(&BMessage::FindPoint, py::const_), "", py::arg("name"), py::arg("n")=0)
.def("FindString", py::overload_cast<const char *, int32>(&BMessage::FindString, py::const_), "", py::arg("name"), py::arg("n")=0)

.def("FindInt8", py::overload_cast<const char *, int32>(&BMessage::FindInt8, py::const_), "", py::arg("name"), py::arg("n")=0)
.def("FindInt16", py::overload_cast<const char *, int32>(&BMessage::FindInt16, py::const_), "", py::arg("name"), py::arg("n")=0)
.def("FindInt32", py::overload_cast<const char *, int32>(&BMessage::FindInt32, py::const_), "", py::arg("name"), py::arg("n")=0)
.def("FindInt64", py::overload_cast<const char *, int32>(&BMessage::FindInt64, py::const_), "", py::arg("name"), py::arg("n")=0)
.def("FindBool", py::overload_cast<const char *, int32>(&BMessage::FindBool, py::const_), "", py::arg("name"), py::arg("n")=0)
.def("FindFloat", py::overload_cast<const char *, int32>(&BMessage::FindFloat, py::const_), "", py::arg("name"), py::arg("n")=0)
.def("FindDouble", py::overload_cast<const char *, int32>(&BMessage::FindDouble, py::const_), "", py::arg("name"), py::arg("n")=0)

.def("GetBool", py::overload_cast<const char *, bool>(&BMessage::GetBool, py::const_), "", py::arg("name"), py::arg("defaultValue")=false)
.def("GetBool", py::overload_cast<const char *, int32, bool>(&BMessage::GetBool, py::const_), "", py::arg("name"), py::arg("index"), py::arg("defaultValue"))
.def("GetInt8", py::overload_cast<const char *, signed char>(&BMessage::GetInt8, py::const_), "", py::arg("name"), py::arg("defaultValue"))
.def("GetInt8", py::overload_cast<const char *, int32, signed char>(&BMessage::GetInt8, py::const_), "", py::arg("name"), py::arg("index"), py::arg("defaultValue"))
.def("GetUInt8", py::overload_cast<const char *, unsigned char>(&BMessage::GetUInt8, py::const_), "", py::arg("name"), py::arg("defaultValue"))
.def("GetUInt8", py::overload_cast<const char *, int32, unsigned char>(&BMessage::GetUInt8, py::const_), "", py::arg("name"), py::arg("index"), py::arg("defaultValue"))
.def("GetInt16", py::overload_cast<const char *, int16>(&BMessage::GetInt16, py::const_), "", py::arg("name"), py::arg("defaultValue"))
.def("GetInt16", py::overload_cast<const char *, int32, int16>(&BMessage::GetInt16, py::const_), "", py::arg("name"), py::arg("index"), py::arg("defaultValue"))
.def("GetUInt16", py::overload_cast<const char *, uint16>(&BMessage::GetUInt16, py::const_), "", py::arg("name"), py::arg("defaultValue"))
.def("GetUInt16", py::overload_cast<const char *, int32, uint16>(&BMessage::GetUInt16, py::const_), "", py::arg("name"), py::arg("index"), py::arg("defaultValue"))
.def("GetInt32", py::overload_cast<const char *, int32>(&BMessage::GetInt32, py::const_), "", py::arg("name"), py::arg("defaultValue"))
.def("GetInt32", py::overload_cast<const char *, int32, int32>(&BMessage::GetInt32, py::const_), "", py::arg("name"), py::arg("index"), py::arg("defaultValue"))
.def("GetUInt32", py::overload_cast<const char *, uint32>(&BMessage::GetUInt32, py::const_), "", py::arg("name"), py::arg("defaultValue"))
.def("GetUInt32", py::overload_cast<const char *, int32, uint32>(&BMessage::GetUInt32, py::const_), "", py::arg("name"), py::arg("index"), py::arg("defaultValue"))
.def("GetInt64", py::overload_cast<const char *, int64_t>(&BMessage::GetInt64, py::const_), "", py::arg("name"), py::arg("defaultValue"))
.def("GetInt64", py::overload_cast<const char *, int32, int64_t>(&BMessage::GetInt64, py::const_), "", py::arg("name"), py::arg("index"), py::arg("defaultValue"))
.def("GetUInt64", py::overload_cast<const char *, uint64_t>(&BMessage::GetUInt64, py::const_), "", py::arg("name"), py::arg("defaultValue"))
.def("GetUInt64", py::overload_cast<const char *, int32, uint64_t>(&BMessage::GetUInt64, py::const_), "", py::arg("name"), py::arg("index"), py::arg("defaultValue"))
.def("GetFloat", py::overload_cast<const char *, float>(&BMessage::GetFloat, py::const_), "", py::arg("name"), py::arg("defaultValue"))
.def("GetFloat", py::overload_cast<const char *, int32, float>(&BMessage::GetFloat, py::const_), "", py::arg("name"), py::arg("index"), py::arg("defaultValue"))
.def("GetDouble", py::overload_cast<const char *, double>(&BMessage::GetDouble, py::const_), "", py::arg("name"), py::arg("defaultValue"))
.def("GetDouble", py::overload_cast<const char *, int32, double>(&BMessage::GetDouble, py::const_), "", py::arg("name"), py::arg("index"), py::arg("defaultValue"))
.def("GetColor", py::overload_cast<const char *, rgb_color>(&BMessage::GetColor, py::const_), "", py::arg("name"), py::arg("defaultValue"))
.def("GetColor", py::overload_cast<const char *, int32, rgb_color>(&BMessage::GetColor, py::const_), "", py::arg("name"), py::arg("index"), py::arg("defaultValue"))
.def("GetPointer", py::overload_cast<const char *, int32, const void *>(&BMessage::GetPointer, py::const_), "", py::arg("name"), py::arg("index"), py::arg("defaultValue")=NULL)
.def("GetPointer", py::overload_cast<const char *, const void *>(&BMessage::GetPointer, py::const_), "", py::arg("name"), py::arg("defaultValue")=NULL)
.def("GetString", py::overload_cast<const char *, const char *>(&BMessage::GetString, py::const_), "", py::arg("name"), py::arg("defaultValue")=NULL)
.def("GetString", py::overload_cast<const char *, int32, const char *>(&BMessage::GetString, py::const_), "", py::arg("name"), py::arg("index"), py::arg("defaultValue"))

// These two don't seem to be available on Haiku R1B4. Maybe they are, but just
// not in libbe.so? That would be strange... But it's also strange that the
// header files that come with R1B4 mention them.
#if (B_HAIKU_VERSION > B_HAIKU_VERSION_1_BETA_4)
.def("GetAlignment", py::overload_cast<const char *, int32, const BAlignment &>(&BMessage::GetAlignment, py::const_), "", py::arg("name"), py::arg("index"), py::arg("defaultValue"))
.def("GetAlignment", py::overload_cast<const char *, const BAlignment &>(&BMessage::GetAlignment, py::const_), "", py::arg("name"), py::arg("defaultValue"))
#endif

.def("GetRect", py::overload_cast<const char *, int32, const BRect &>(&BMessage::GetRect, py::const_), "", py::arg("name"), py::arg("index"), py::arg("defaultValue"))
.def("GetRect", py::overload_cast<const char *, const BRect &>(&BMessage::GetRect, py::const_), "", py::arg("name"), py::arg("defaultValue"))
.def("GetPoint", py::overload_cast<const char *, int32, const BPoint &>(&BMessage::GetPoint, py::const_), "", py::arg("name"), py::arg("index"), py::arg("defaultValue"))
.def("GetPoint", py::overload_cast<const char *, const BPoint &>(&BMessage::GetPoint, py::const_), "", py::arg("name"), py::arg("defaultValue"))
.def("GetSize", py::overload_cast<const char *, int32, const BSize &>(&BMessage::GetSize, py::const_), "", py::arg("name"), py::arg("index"), py::arg("defaultValue"))
.def("GetSize", py::overload_cast<const char *, const BSize &>(&BMessage::GetSize, py::const_), "", py::arg("name"), py::arg("defaultValue"))

.def("SetBool", &BMessage::SetBool, "", py::arg("name"), py::arg("value"))
.def("SetInt8", &BMessage::SetInt8, "", py::arg("name"), py::arg("value"))
.def("SetUInt8", &BMessage::SetUInt8, "", py::arg("name"), py::arg("value"))
.def("SetInt16", &BMessage::SetInt16, "", py::arg("name"), py::arg("value"))
.def("SetUInt16", &BMessage::SetUInt16, "", py::arg("name"), py::arg("value"))
.def("SetInt32", &BMessage::SetInt32, "", py::arg("name"), py::arg("value"))
.def("SetUInt32", &BMessage::SetUInt32, "", py::arg("name"), py::arg("value"))
.def("SetInt64", &BMessage::SetInt64, "", py::arg("name"), py::arg("value"))
.def("SetUInt64", &BMessage::SetUInt64, "", py::arg("name"), py::arg("value"))

.def("SetColor", &BMessage::SetColor, "", py::arg("name"), py::arg("value"))
.def("SetPointer", &BMessage::SetPointer, "", py::arg("name"), py::arg("value"))
.def("SetString", py::overload_cast<const char *, const char *>(&BMessage::SetString), "", py::arg("name"), py::arg("string"))
.def("SetString", py::overload_cast<const char *, const BString &>(&BMessage::SetString), "", py::arg("name"), py::arg("string"))
.def("SetFloat", &BMessage::SetFloat, "", py::arg("name"), py::arg("value"))
.def("SetDouble", &BMessage::SetDouble, "", py::arg("name"), py::arg("value"))
#if (B_HAIKU_VERSION > B_HAIKU_VERSION_1_BETA_4) // see comment for GetAlignment
.def("SetAlignment", &BMessage::SetAlignment, "", py::arg("name"), py::arg("value"))
#endif
.def("SetPoint", &BMessage::SetPoint, "", py::arg("name"), py::arg("value"))
.def("SetRect", &BMessage::SetRect, "", py::arg("name"), py::arg("value"))
.def("SetSize", &BMessage::SetSize, "", py::arg("name"), py::arg("value"))
.def("SetData", &BMessage::SetData, "", py::arg("name"), py::arg("type"), py::arg("data"), py::arg("numBytes"), py::arg("fixedSize")=true, py::arg("count")=1)

.def_readwrite("what", &BMessage::what, "")
;


}
