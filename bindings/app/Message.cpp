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


py::tuple GetInfoWrapper(const BMessage& self, type_code typeRequested, int32 index) {
	char *namefound_local = nullptr;
	type_code typefound_local = 0;
    int32 countfound_local = 0;

    status_t status = self.GetInfo(typeRequested, index, 
                                   &namefound_local, 
                                   &typefound_local, 
                                   &countfound_local);
    return py::make_tuple(status, 
                          (namefound_local ? namefound_local : ""), // Handles nullptr case
                          typefound_local, 
                          countfound_local);
}

py::tuple GetInfoFixedSizeWrapper(const BMessage& self, const char* name) {
	type_code typeFound = 0;
	int32 countFound = 0;
	bool fixedSize = false; //<-in case of not B_OK
	status_t status = self.GetInfo(name, &typeFound, &countFound, &fixedSize);
	return py::make_tuple(status, typeFound, countFound, fixedSize);
}

py::tuple GetInfoNameWrapper(const BMessage& self, const char* name) {
       type_code typeFound = 0;
       int32 countFound = 0;
       status_t status = self.GetInfo(name, &typeFound, &countFound);
       return py::make_tuple(status, typeFound, countFound);
}

py::tuple GetCurrentSpecifierFullWrapper(const BMessage& self) {
    int32 indexFound = 0;
    BMessage specifierFound;
    int32 whatFound = 0;
    const char* propertyFound = nullptr;
    status_t status = self.GetCurrentSpecifier(&indexFound,&specifierFound,&whatFound,&propertyFound);
    py::object py_property;
    if (status == B_OK && propertyFound != nullptr) {
        py_property = py::cast(std::string(propertyFound));//<-for security
    } else {
        py_property = py::none();
    }
    return py::make_tuple(status,indexFound,specifierFound,whatFound,py_property);
}

py::tuple PythonicFindStringsWrapper(const BMessage& self, const char* name){
	BStringList sl;
	status_t status = self.FindStrings(name,&sl);
	if (status == B_OK) {
		return py::make_tuple(status, sl);
	}
	return py::make_tuple(status, py::none());
}

py::tuple PythonicFindStringWrapper(const BMessage& self, const char* name, int32 n=0){
	const char* s;
	status_t status = self.FindString(name, n, &s);
	//return py::make_tuple(status, s); safer below
	if (status == B_OK) {
        std::string safe_string(s);
        return py::make_tuple(status, safe_string);
    }
    return py::make_tuple(status, std::string("")); 
}

py::tuple PythonicFindBStringWrapper(const BMessage& self, const char* name, int32 n=0){
	BString s;
	status_t status = self.FindString(name,n, &s);
	if (status == B_OK) {
		return py::make_tuple(status, s); 
	}
	return py::make_tuple(status, py::none());
}

py::tuple PythonicFindAlignmentWrapper(const BMessage& self, const char* name, int32 n=0){
	BAlignment a;
	status_t status = self.FindAlignment(name,n,&a);
	if (status == B_OK) {
		return py::make_tuple(status, a);
	}
	return py::make_tuple(status, py::none());
}

py::tuple PythonicFindRectWrapper(const BMessage& self, const char* name, int32 n=0){
	BRect r;
	status_t status = self.FindRect(name,n,&r);
	if (status == B_OK) {
		return py::make_tuple(status, r);
	}
	return py::make_tuple(status, py::none());
}

py::tuple PythonicFindSizeWrapper(const BMessage& self, const char* name, int32 n=0){
	BSize sz;
	status_t status = self.FindSize(name,n,&sz);
	if (status == B_OK) {
		return py::make_tuple(status, sz);
	}
	return py::make_tuple(status, py::none());
}

py::tuple PythonicFindPointWrapper(const BMessage& self, const char* name, int32 n=0){
	BPoint p;
	status_t status = self.FindPoint(name,n,&p);
	if (status == B_OK) {
		return py::make_tuple(status, p);
	}
	return py::make_tuple(status, py::none());
}

py::tuple PythonicFindInt8Wrapper(const BMessage& self, const char* name, int32 n=0){
	int8 i;
	status_t status = self.FindInt8(name, n, &i);
	if (status == B_OK) {
		return py::make_tuple(status, i);
	}
	return py::make_tuple(status, py::none());
}

py::tuple PythonicFindUInt8Wrapper(const BMessage& self, const char* name, int32 n=0){
	uint8 i;
	status_t status = self.FindUInt8(name, n, &i);
	if (status == B_OK) {
		return py::make_tuple(status, i);
	}
	return py::make_tuple(status, py::none());
}

py::tuple PythonicFindInt16Wrapper(const BMessage& self, const char* name, int32 n=0){
	int16 i;
	status_t status = self.FindInt16(name, n, &i);
	if (status == B_OK) {
		return py::make_tuple(status, i);
	}
	return py::make_tuple(status, py::none());
}

py::tuple PythonicFindUInt16Wrapper(const BMessage& self, const char* name, int32 n=0){
	uint16 i;
	status_t status = self.FindUInt16(name, n, &i);
	if (status == B_OK) {
		return py::make_tuple(status, i);
	}
	return py::make_tuple(status, py::none());
}

py::tuple PythonicFindInt32Wrapper(const BMessage& self, const char* name, int32 n=0){
	int32 i;
	status_t status = self.FindInt32(name, n, &i);
	if (status == B_OK) {
		return py::make_tuple(status, i);
	}
	return py::make_tuple(status, py::none());
}

py::tuple PythonicFindUInt32Wrapper(const BMessage& self, const char* name, int32 n=0){
	uint32 i;
	status_t status = self.FindUInt32(name, n, &i);
	if (status == B_OK) {
		return py::make_tuple(status, i);
	}
	return py::make_tuple(status, py::none());
}

py::tuple PythonicFindInt64Wrapper(const BMessage& self, const char* name, int32 n=0){
	int64 i;
	status_t status = self.FindInt64(name, n, &i);
	if (status == B_OK) {
		return py::make_tuple(status, i);
	}
	return py::make_tuple(status, py::none());
}

py::tuple PythonicFindUInt64Wrapper(const BMessage& self, const char* name, int32 n=0){
	uint64 i;
	status_t status = self.FindUInt64(name, n, &i);
	if (status == B_OK) {
		return py::make_tuple(status, i);
	}
	return py::make_tuple(status, py::none());
}

py::tuple PythonicFindBoolWrapper(const BMessage& self, const char* name, int32 n=0){
	bool b;
	status_t status = self.FindBool(name, n, &b);
	if (status == B_OK) {
		return py::make_tuple(status, b);
	}
	return py::make_tuple(status, py::none());
}

py::tuple PythonicFindFloatWrapper(const BMessage& self, const char* name, int32 n=0){
	float f;
	status_t status = self.FindFloat(name, n, &f);
	if (status == B_OK) {
		return py::make_tuple(status, f);
	}
	return py::make_tuple(status, py::none());
}

py::tuple PythonicFindDoubleWrapper(const BMessage& self, const char* name, int32 n=0){
	double d;
	status_t status = self.FindDouble(name, n, &d);
	if (status == B_OK) {
		return py::make_tuple(status, d);
	}
	return py::make_tuple(status, py::none());
}

py::tuple PythonicFindColorWrapper(const BMessage& self, const char* name, int32 n=0){
	rgb_color col;
	status_t status = self.FindColor(name,n,&col);
	if (status == B_OK) {
		return py::make_tuple(status, col);
	}
	return py::make_tuple(status, py::none());
}

py::tuple PythonicFindMessengerWrapper(const BMessage& self, const char* name, int32 n=0){
	BMessenger msgr;
	status_t status = self.FindMessenger(name,n,&msgr);
	if (status == B_OK) {
		return py::make_tuple(status, msgr);
	}
	return py::make_tuple(status, py::none());
}

py::tuple PythonicFindRefWrapper(const BMessage& self, const char* name, int32 n=0){
	entry_ref entr;
	status_t status = self.FindRef(name,n,&entr);
	if (status == B_OK) {
		return py::make_tuple(status, entr);
	}
	return py::make_tuple(status, py::none());
}

py::tuple PythonicFindNodeRefWrapper(const BMessage& self, const char* name, int32 n=0){
	node_ref nr;
	status_t status = self.FindNodeRef(name,n,&nr);
	if (status == B_OK) {
		return py::make_tuple(status, nr);
	}
	return py::make_tuple(status, py::none());
}

py::tuple PythonicFindMessageWrapper(const BMessage& self, const char* name, int32 n=0){
	BMessage m;
	status_t status = self.FindMessage(name,n,&m);
	if (status == B_OK) {
		return py::make_tuple(status, m);
	}
	return py::make_tuple(status, py::none());
}
namespace {
std::string FourCC(uint32 code){
    char s[5] = {
        char((code >> 24) & 0xff),
        char((code >> 16) & 0xff),
        char((code >> 8) & 0xff),
        char(code & 0xff),
        0
    };

    for (int i = 0; i < 4; i++)
        if (!isprint((unsigned char)s[i]))
            return "";

    return std::string("'") + s + "'";
	}
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
m.attr("B_FIELD_NAME_LENGTH")=B_FIELD_NAME_LENGTH;
m.attr("B_PROPERTY_NAME_LENGTH")=B_PROPERTY_NAME_LENGTH;

py::class_<BMessage,std::unique_ptr<BMessage, py::nodelete>>(m, "BMessage",R"doc(
   ``BMessage`` represents a message object in Haiku, used for communication
   between ``BHandlers``, ``BLoopers``, and ``BApplications``. Messages can carry
   typed fields, references to files, archived objects, or scripting data.
)doc")
.def(py::init(), R"doc(
   Create an empty ``BMessage``.

   The message will have no fields and a `what` code equal to zero.
)doc")
.def(py::init<uint32>(), R"doc(
   Create a ``BMessage`` with a specific `what` code.

   :param what: The 'what' command identifier associated with this message.
   :type what: int
)doc", py::arg("what"))
.def(py::init<const BMessage &>(), R"doc(
   Create a copy of an existing ``BMessage``.

   This performs a deep copy of all fields and metadata.

   :param other: The message to copy.
   :type other: BMessage
)doc", py::arg("other"))

/* commented out: conceptually wrong, operator= is different from __copy__
.def("__copy__", &BMessage::operator=, R"doc(
Assign the contents of another BMessage to this one.

This performs the same deep copy as the copy constructor.

:param other: The message to copy from.
:type other: BMessage
:return: Reference to this BMessage.
:rtype: BMessage
)doc", py::arg("other"))*/

//.def("GetInfo", &GetInfoWrapper, "", py::arg("typeRequested"), py::arg("index"), py::arg("nameFound"), py::arg("typeFound"), py::arg("countFound")=NULL)
.def("GetInfo", &GetInfoWrapper, R"doc(
   Retrieve information about the N-th field of a given type.

   This version queries the *N-th field* (by index) of a specific type.
   It returns four values, including the original status code from Haiku's API.

:param typeRequested: The type code of the fields to inspect.
:type typeRequested: int
:param index: Index of the field within the group of that type.
:type index: int
:return: A tuple ``(status, name, type_code, count)``:
   
         - ``status`` (int): ``B_OK`` on success, or a Haiku error code  
         - ``name`` (str): name of the field  
         - ``type_code`` (int): the type of the field  
         - ``count`` (int): number of items stored under that name  

:rtype: tuple
)doc", py::arg("typeRequested"), py::arg("index"))
//.def("GetInfo", py::overload_cast<const char *, type_code *, int32 *>(&BMessage::GetInfo, py::const_), "", py::arg("name"), py::arg("typeFound"), py::arg("countFound")=NULL)
//.def("GetInfo", &GetInfoNameWrapper, "", py::arg("name")) //<----- this is the specific version but we use FixedSizeWrapper because it returns the same infosplus fixedSize
.def("GetInfo", &GetInfoFixedSizeWrapper, R"doc(
   Retrieve information about a field by its name.

   This function wraps all overloads of Haiku's ``BMessage::GetInfo(const char*)``.
   It provides complete information in a single call, including item count and
   whether items stored under the field are of fixed size.

:param name: The name of the field.
:type name: str
:return: A tuple ``(status, type_code, count, fixedSize)``:

         - ``status`` (int): ``B_OK`` on success, or a Haiku error code  
         - ``type_code`` (int): the type of the field  
         - ``count`` (int): number of items stored under this name  
         - ``fixedSize`` (bool): whether items have fixed size  

:rtype: tuple
)doc", py::arg("name"))
//.def("GetInfo", py::overload_cast<const char *, type_code *, bool *>(&BMessage::GetInfo, py::const_), "", py::arg("name"), py::arg("typeFound"), py::arg("fixedSize"))
//.def("GetInfo", py::overload_cast<const char *, type_code *, int32 *, bool *>(&BMessage::GetInfo, py::const_), "", py::arg("name"), py::arg("typeFound"), py::arg("countFound"), py::arg("fixedSize"))
//.def("GetInfoFixedSize", &GetInfoFixedSizeWrapper, "", py::arg("name")) //<--- comment this and use this function for GetInfo(name)
.def("CountNames", &BMessage::CountNames, R"doc(
   Count how many field names exist for a given type.

   :param type: The type code of the fields to count.
   :type type: int
   :return: Number of field names defined for that type.
   :rtype: int
)doc", py::arg("type"))
.def("IsEmpty", &BMessage::IsEmpty, R"doc(
   Check whether the message has no fields.

   :return: ``True`` if the message contains no fields.
   :rtype: bool
)doc")
.def("IsSystem", &BMessage::IsSystem, R"doc(
   Check whether this message is a system-defined message.

   :return: ``True`` if this message was generated internally by the OS.
   :rtype: bool
)doc")
.def("IsReply", &BMessage::IsReply, R"doc(
   Check whether this message is a reply to another message.

   :return: ``True`` if this is a reply message.
   :rtype: bool
)doc")
.def("PrintToStream", &BMessage::PrintToStream, R"doc(
   Print the contents of the message to the standard output.

   Useful for debugging.
)doc")
.def("Rename", &BMessage::Rename, R"doc(
   Rename an existing field.

   :param oldEntry: Current field name.
   :type oldEntry: str
   :param newEntry: New name for the field.
   :type newEntry: str
   :return: ``B_OK`` on success, or an error code.
   :rtype: int
)doc", py::arg("oldEntry"), py::arg("newEntry"))
.def("WasDelivered", &BMessage::WasDelivered, R"doc(
   Check whether this message was delivered through a message loop.

   :return: ``True`` if the message was delivered (posted,sent or dropped).
   :rtype: bool
)doc")
.def("IsSourceWaiting", &BMessage::IsSourceWaiting, R"doc(
   Check whether the sender is waiting for a reply.

   :return: ``True`` if the sender is blocked waiting.
   :rtype: bool
)doc")
.def("IsSourceRemote", &BMessage::IsSourceRemote, R"doc(
   Check whether the sender of this message is a remote application.

   :return: ``True`` if the source is remote.
   :rtype: bool
)doc")
.def("ReturnAddress", &BMessage::ReturnAddress, R"doc(
   Retrieve the reply handler/address for this message.

   :return: A ``BMessenger`` object representing the return address.
   :rtype: BMessenger
)doc")
.def("Previous", &BMessage::Previous, R"doc(
   Get the previous message in the message chain, if any.

   :return: The previous ``BMessage``, or ``None``.
   :rtype: BMessage or ``None``
)doc")
.def("WasDropped", &BMessage::WasDropped, R"doc(
   Check whether this message was delivered as a drag-and-drop message.

   :return: ``True`` if the message was dropped.
   :rtype: bool
)doc")
.def("DropPoint", &BMessage::DropPoint, R"doc(
   Return the point where this message was dropped.

   :param offset: Optional point offset to apply, defaults to ``None``.
   :type offset: BPoint, optional
   :return: The drop location as a ``BPoint``.
   :rtype: BPoint
)doc", py::arg("offset")=NULL)

.def("SendReply", py::overload_cast<uint32, BHandler *>(&BMessage::SendReply), R"doc(
   Send a reply message with the given command code.

   This overload constructs a new BMessage whose ``what`` field is set to
   ``command`` and sends it as a reply to the message currently being handled.

   Whether the reply is delivered synchronously or asynchronously depends on
   how the original message was sent:

   * If the original sender is waiting for a reply, this function blocks
     until the reply is delivered.
   * Otherwise the reply is delivered asynchronously. If ``replyTo`` is
     provided, it designates the target ``BHandler`` for the asynchronous reply.
     If ``replyTo`` is ``None``, the target chosen when the original message
     was sent (or the ``BApplication`` object) will receive the reply.

   This overload uses an infinite timeout and blocks until the reply is
   delivered or an error occurs.

:param command: The ``what`` command identifier for the generated reply.
:type command: int
:param replyTo: Optional ``BHandler`` to receive an asynchronous reply, or ``None``.
:type replyTo: BHandler, optional
:return: ``B_OK`` on success, or an error code on failure.
:rtype: int
)doc", py::arg("command"), py::arg("replyTo")=NULL)
.def("SendReply", py::overload_cast<BMessage *, BHandler *, bigtime_t>(&BMessage::SendReply), R"doc(
   Send the given ``BMessage`` as a reply to the message currently being handled.

   Delivery is synchronous if the sender of the original message is waiting
   for a reply; otherwise it is asynchronous. If ``replyTo`` is provided, it
   specifies the ``BHandler`` that will receive the asynchronous reply (if any).

   If the reply message itself requests a synchronous reply, this function
   blocks until that reply arrives.

   The ``timeout`` parameter limits how long this function waits to place
   the reply in the target port queue. If the timeout expires before the
   message is delivered, the function fails with ``B_TIMED_OUT``.

:param reply: The reply message to send.
:type reply: BMessage
:param replyTo: Optional ``BHandler`` to receive an asynchronous reply, or ``None``.
:type replyTo: BHandler, optional
:param timeout: Maximum time (in microseconds) allowed for sending.
:type timeout: int
:return: ``B_OK`` on success, or an error code on failure.
:rtype: int
)doc", py::arg("reply"), py::arg("replyTo")=NULL, py::arg("timeout")=B_INFINITE_TIMEOUT)
.def("SendReply", py::overload_cast<BMessage *, BMessenger, bigtime_t>(&BMessage::SendReply), R"doc(
   Send the given ``BMessage`` as a reply, optionally directing asynchronous
   delivery to the specified ``BMessenger``.

   This behaves like the other ``SendReply()`` overloads:

   * Delivery is synchronous if the original sender is waiting for a reply.
   * Otherwise the reply is asynchronous; ``replyTo`` designates the target
     ``BMessenger`` that will receive it.

   The ``timeout`` parameter limits the time allowed to deliver the reply to
   the recipient's message port.

:param reply: The reply message to send.
:type reply: BMessage
:param replyTo: Target messenger for asynchronous replies.
:type replyTo: BMessenger
:param timeout: Maximum send time in microseconds.
:type timeout: int
:return: ``B_OK`` on success, or an error code on failure.
:rtype: int
)doc", py::arg("reply"), py::arg("replyTo"), py::arg("timeout")=B_INFINITE_TIMEOUT)
.def("SendReply", py::overload_cast<uint32, BMessage *>(&BMessage::SendReply), R"doc(
   Send a reply message constructed from the given command code, and
   optionally wait for a synchronous reply to that reply.

   A ``BMessage`` with ``what = command`` is created and sent to the sender of
   the current message. If ``replyToReply`` is provided, this function blocks
   until the sender returns the synchronous reply contained in
   ``replyToReply``.

   This overload uses infinite timeouts for both sending the reply and
   waiting for the reply-to-reply.

:param command: The command identifier for the generated reply.
:type command: int
:param replyToReply: A ``BMessage`` that will receive the synchronous reply, or ``None``
:type replyToReply: BMessage
:return: ``B_OK`` on success, or an error code on failure.
:rtype: int
)doc", py::arg("command"), py::arg("replyToReply"))
.def("SendReply", py::overload_cast<BMessage *, BMessage *, bigtime_t, bigtime_t>(&BMessage::SendReply), R"doc(
   Send the given message as a reply and optionally wait for a synchronous
   reply to that reply, each step with its own timeout.

   If ``replyToReply`` is provided, this function blocks while waiting for
   the reply-to-reply message. The time spent sending the initial reply is
   limited by ``sendTimeout``; the time spent waiting for the reply-to-reply
   is limited by ``replyTimeout``.

   A timeout value of ``B_INFINITE_TIMEOUT`` disables time limiting for the
   corresponding phase. A timeout of 0 causes the function to return
   immediately if it would otherwise block.

:param reply: The reply message to send.
:type reply: BMessage
:param replyToReply: A message object that will be filled with the reply-to-reply, or ``None``
:type replyToReply: BMessage
:param sendTimeout: Maximum time for sending the reply.
:type sendTimeout: int
:param replyTimeout: Maximum time for waiting for the reply-to-reply.
:type replyTimeout: int
:return: ``B_OK`` on success, or an error code on failure.
:rtype: int
)doc", py::arg("reply"), py::arg("replyToReply"), py::arg("sendTimeout")=B_INFINITE_TIMEOUT, py::arg("replyTimeout")=B_INFINITE_TIMEOUT)

.def("FlattenedSize", &BMessage::FlattenedSize,  R"doc(
   Return the size, in bytes, required to flatten this message.
   
   :return: Number of bytes needed to store the flattened form.
   :rtype: int
)doc")
// TODO CHECK if this below works properly
.def("Flatten", py::overload_cast<char *, ssize_t>(&BMessage::Flatten, py::const_), R"doc(
   Flatten the message into a preallocated buffer.
   
:param buffer: The buffer where the flattened data will be stored.
:type buffer: bytearray or writable buffer
:param size: Size of the buffer in bytes.
:type size: int
:return: ``B_OK`` on success, or an error code.
:rtype: int
)doc", py::arg("buffer"), py::arg("size"))
.def("Flatten", py::overload_cast<BDataIO *, ssize_t *>(&BMessage::Flatten, py::const_), R"doc(
   Flatten the message and write it into a ``BDataIO`` stream.

:param stream: The output stream.
:type stream: BDataIO
:param size: Optional variable that will store the number of bytes written, or ``None``
:type size: int, optional
:return: ``B_OK`` on success, or an error code.
:rtype: int
)doc", py::arg("stream"), py::arg("size")=NULL)


// ### TODO: CHECK if this returns py::capsule and we should wrap this ####
.def("Unflatten", py::overload_cast<const char *>(&BMessage::Unflatten), R"doc(
   Restore the contents of the message from a flattened buffer.

:param flatBuffer: The buffer containing the flattened message.
:type flatBuffer: bytes or bytearray
:return: ``B_OK`` on success, or an error code.
:rtype: int
)doc", py::arg("flatBuffer"))
.def("Unflatten", py::overload_cast<BDataIO *>(&BMessage::Unflatten), R"doc(
   Restore the contents of the message from a ``BDataIO`` input stream.

:param stream: The input stream.
:type stream: BDataIO
:return: ``B_OK`` on success, or an error code.
:rtype: int
)doc", py::arg("stream"))

.def("AddSpecifier", py::overload_cast<const char *>(&BMessage::AddSpecifier), R"doc(
   Add a specifier targeting the given property.

:param property: The property name.
:type property: str
:return: ``B_OK`` on success, or an error code.
:rtype: int
)doc", py::arg("property"))
.def("AddSpecifier", py::overload_cast<const char *, int32>(&BMessage::AddSpecifier), R"doc(
   Add a specifier targeting the given property at a specific index.

:param property: The property name.
:type property: str
:param index: Index of the item inside the property.
:type index: int
:return: ``B_OK`` on success, or an error code.
:rtype: int
)doc", py::arg("property"), py::arg("index"))
.def("AddSpecifier", py::overload_cast<const char *, int32, int32>(&BMessage::AddSpecifier), R"doc(
   Add a specifier targeting the given property at a specific index and range.

:param property: The property name.
:type property: str
:param index: Starting index of the range.
:type index: int
:param range: Number of consecutive items in the range.
:type range: int
:return: ``B_OK`` on success, or an error code.
:rtype: int
)doc", py::arg("property"), py::arg("index"), py::arg("range"))
.def("AddSpecifier", py::overload_cast<const char *, const char *>(&BMessage::AddSpecifier), R"doc(
   Add a specifier targeting the given property and a specified name.

:param property: The property name.
:type property: str
:param name: The name to target within the property.
:type name: str
:return: ``B_OK`` on success, or an error code.
:rtype: int
)doc", py::arg("property"), py::arg("name"))
.def("AddSpecifier", py::overload_cast<const BMessage *>(&BMessage::AddSpecifier), R"doc(
   Add the specifier message to the specifier stack.

:param specifier: The specifier message to add.
:type specifier: BMessage
:return: ``B_OK`` on success, or an error code.
:rtype: int
)doc", py::arg("message"))

.def("SetCurrentSpecifier", &BMessage::SetCurrentSpecifier, R"doc(
   Sets the current specifier by its index.

   :param index: The index of the specifier to set as current.
)doc", py::arg("index"))
//.def("GetCurrentSpecifier", &GetCurrentSpecifierWrapper, "", py::arg("index"), py::arg("specifier")=NULL, py::arg("what")=NULL, py::arg("property")=NULL)
.def("GetCurrentSpecifier", &GetCurrentSpecifierFullWrapper, R"doc(
   Retrieves the full details of the current specifier.

   :returns: A tuple ``(status,indexFound,specifierFound,whatFound,py_property)``:

         - ``status`` (int): ``B_OK`` on success, or a Haiku error code  
         - ``indexFound`` (int): the index of the current specifier 
         - ``specifierFound`` (BMessage): a copy of the current specifier  
         - ``whatFound`` (int): the what data member of the specifier  
         - ``py_property`` (int): the property name in the property variable
         
   :rtype: tuple
)doc")
.def("HasSpecifiers", &BMessage::HasSpecifiers, R"doc(
   Checks whether the message has any specifiers.

   :returns: ``True`` if the message has specifiers, ``False`` otherwise.
   :rtype: bool
)doc")
.def("PopSpecifier", &BMessage::PopSpecifier, R"doc(
   Removes the top specifier from the specifier stack.

   :returns: ``B_OK`` on success, or an error code if the stack is empty.
   :rtype: int
)doc")
.def("AddAlignment", &BMessage::AddAlignment, R"doc(
   Add a ``BAlignment`` object to the message.

   :param name: The name associated with the ``BAlignment``.
   :type name: str
   :param alignment: The alignment value to add.
   :type alignment: BAlignment
   :returns: ``B_OK`` on success, or an error code otherwise.
   :rtype: int
)doc", py::arg("name"), py::arg("alignment"))
.def("AddRect", &BMessage::AddRect, R"doc(
   Add a ``BRect`` object to the message.

   :param name: The name associated with the ``BRect``.
   :type name: str
   :param rect: The ``BRect`` object to add.
   :type rect: BRect
   :returns: ``B_OK`` on success, or an error code otherwise.
   :rtype: int
)doc", py::arg("name"), py::arg("rect"))
.def("AddPoint", &BMessage::AddPoint, R"doc(
   Add a ``BPoint`` object to the message.

   :param name: The name associated with the ``BPoint``.
   :type name: str
   :param point: The ``BPoint`` object to add.
   :type point: BPoint
   :returns: ``B_OK`` on success, or an error code otherwise.
   :rtype: int
)doc", py::arg("name"), py::arg("point"))
.def("AddSize", &BMessage::AddSize, R"doc(
   Add a ``BSize`` object to the message.

   :param name: The name associated with the ``BSize``.
   :type name: str
   :param size: The ``BSize`` object to add.
   :type size: BSize
   :returns: ``B_OK`` on success, or an error code otherwise.
   :rtype: int
)doc", py::arg("name"), py::arg("size"))

.def("AddString", py::overload_cast<const char *, const char *>(&BMessage::AddString), R"doc(
   Add a string to the message.

:param name: The name associated with the string.
:type name: str
:param string: The string to add.
:type string: str
:returns: ``B_OK`` on success, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("string"))
.def("AddString", py::overload_cast<const char *, const BString &>(&BMessage::AddString), R"doc(
   Add a ``BString`` object to the message.

:param name: The name associated with the ``BString``.
:type name: str
:param string: The ``BString`` object to add.
:type string: BString
:returns: ``B_OK`` on success, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("string"))
.def("AddStrings", &BMessage::AddStrings, R"doc(
   Add multiple strings as ``BStringList`` to the message.

   :param name: The name associated with the ``BStringList``.
   :type name: str
   :param list: The ``BStringList`` containing the list of strings to add.
   :type list: BStringList
   :returns: ``B_OK`` on success, or an error code otherwise.
   :rtype: int
)doc", py::arg("name"), py::arg("list"))

.def("AddInt8", &BMessage::AddInt8, R"doc(
   Add an int8 value to the message.

   .. note::

      While this method stores a 8-bit signed integer, 
      the Python parameter 'value' must be a standard Python 'int'. 
      Passing values outside int8 range may result in truncation 
      or unexpected behavior when interpreted by the underlying C++ API.

   :param name: The name associated with the value.
   :type name: str
   :param value: The int8 value to add.
   :type value: int8
   :returns: ``B_OK`` on success, or an error code otherwise.
   :rtype: int
)doc", py::arg("name"), py::arg("value"))
.def("AddUInt8", &BMessage::AddUInt8, R"doc(
   Add a uint8 value to the message.

   .. note::

      While this method stores a 8-bit unsigned integer, 
      the Python parameter 'value' must be a standard Python 'int'. 
      Passing values outside uint8 range may result in truncation 
      or unexpected behavior when interpreted by the underlying C++ API.

   :param name: The name associated with the value.
   :type name: str
   :param value: The uint8 value to add.
   :type value: uint8
   :returns: ``B_OK`` on success, or an error code otherwise.
   :rtype: int
)doc", py::arg("name"), py::arg("value"))
.def("AddInt16", &BMessage::AddInt16, R"doc(
   Add an int16 value to the message.

   .. note::

      While this method stores a 16-bit signed integer, 
      the Python parameter 'value' must be a standard Python 'int'. 
      Passing values outside int16 range may result in truncation 
      or unexpected behavior when interpreted by the underlying C++ API.

   :param name: The name associated with the value.
   :type name: str
   :param value: The int16 value to add.
   :type value: int16
   :returns: ``B_OK`` on success, or an error code otherwise.
   :rtype: int
)doc", py::arg("name"), py::arg("value"))
.def("AddUInt16", &BMessage::AddUInt16, R"doc(
   Add a uint16 value to the message.

   .. note::

      While this method stores a 16-bit unsigned integer, 
      the Python parameter 'value' must be a standard Python 'int'. 
      Passing values outside uint16 range may result in truncation 
      or unexpected behavior when interpreted by the underlying C++ API.

   :param name: The name associated with the value.
   :type name: str
   :param value: The uint16 value to add.
   :type value: uint16
   :returns: ``B_OK`` on success, or an error code otherwise.
   :rtype: int
)doc", py::arg("name"), py::arg("value"))
.def("AddInt32", &BMessage::AddInt32, R"doc(
   Add an int32 value to the message.

   .. note::

      While this method stores a 32-bit signed integer, 
      the Python parameter 'value' must be a standard Python 'int'. 
      Passing values outside int32 range may result in truncation 
      or unexpected behavior when interpreted by the underlying C++ API.

   :param name: The name associated with the value.
   :type name: str
   :param value: The int32 value to add.
   :type value: int32
   :returns: ``B_OK`` on success, or an error code otherwise.
   :rtype: int
)doc", py::arg("name"), py::arg("value"))
.def("AddUInt32", &BMessage::AddUInt32, R"doc(
   Add a uint32 value to the message.

   .. note::

      While this method stores a 32-bit unsigned integer, 
      the Python parameter 'value' must be a standard Python 'int'. 
      Passing values outside uint32 range may result in truncation 
      or unexpected behavior when interpreted by the underlying C++ API.

   :param name: The name associated with the value.
   :type name: str
   :param value: The uint32 value to add.
   :type value: uint32
   :returns: ``B_OK`` on success, or an error code otherwise.
   :rtype: int
)doc", py::arg("name"), py::arg("value"))
.def("AddInt64", &BMessage::AddInt64, R"doc(
   Add an int64 value to the message.

   .. note::

      While this method stores a 64-bit signed integer, 
      the Python parameter 'value' must be a standard Python 'int'. 
      Passing values outside int64 range may result in truncation 
      or unexpected behavior when interpreted by the underlying C++ API.

   :param name: The name associated with the value.
   :type name: str
   :param value: The int64 value to add.
   :type value: int64
   :returns: ``B_OK`` on success, or an error code otherwise.
   :rtype: int
)doc", py::arg("name"), py::arg("value"))
.def("AddUInt64", &BMessage::AddUInt64, R"doc(
   Add a uint64 value to the message.

   .. note::

      While this method stores a 64-bit unsigned integer, 
      the Python parameter 'value' must be a standard Python 'int'. 
      Passing values outside uint64 range may result in truncation 
      or unexpected behavior when interpreted by the underlying C++ API.

   :param name: The name associated with the value.
   :type name: str
   :param value: The uint64 value to add.
   :type value: uint64
   :returns: ``B_OK`` on success, or an error code otherwise.
   :rtype: int
)doc", py::arg("name"), py::arg("value"))

.def("AddBool", &BMessage::AddBool, R"doc(
   Add a boolean value to the message.

   :param name: The name associated with the value.
   :type name: str
   :param value: The boolean value to add.
   :type value: bool
   :returns: ``B_OK`` on success, or an error code otherwise.
   :rtype: int
)doc", py::arg("name"), py::arg("value"))
.def("AddFloat", &BMessage::AddFloat, R"doc(
   Add a float value to the message.

   :param name: The name associated with the value.
   :type name: str
   :param value: The float value to add.
   :type value: float
   :returns: ``B_OK`` on success, or an error code otherwise.
   :rtype: int
)doc", py::arg("name"), py::arg("value"))
.def("AddDouble", &BMessage::AddDouble, R"doc(
   Add a double value to the message.

   :param name: The name associated with the value.
   :type name: str
   :param value: The double value to add.
   :type value: double
   :returns: ``B_OK`` on success, or an error code otherwise.
   :rtype: int
)doc", py::arg("name"), py::arg("value"))
.def("AddColor", &BMessage::AddColor, R"doc(
   Add a ``rgb_color`` object to the message.

   :param name: The name associated with the value.
   :type name: str
   :param value: The ``rgb_color`` object to add.
   :type value: rgb_color
   :returns: ``B_OK`` on success, or an error code otherwise.
   :rtype: int
)doc", py::arg("name"), py::arg("value"))
// TODO: check if necessary this below
.def("AddPointer", &BMessage::AddPointer, R"doc(
   Add a pointer to the message.

   :param name: The name associated with the pointer.
   :type name: str
   :param pointer: The pointer to add.
   :type pointer: const void*
   :returns: ``B_OK`` on success, or an error code otherwise.
   :rtype: int
)doc", py::arg("name"), py::arg("pointer"))
.def("AddMessenger", &BMessage::AddMessenger, R"doc(
   Add a ``BMessenger`` to the message.

   :param name: The name associated with the messenger.
   :type name: str
   :param messenger: The ``BMessenger`` object to add.
   :type messenger: BMessenger
   :returns: ``B_OK`` on success, or an error code otherwise.
   :rtype: int
)doc", py::arg("name"), py::arg("messenger"))

.def("AddRef", &BMessage::AddRef, R"doc(
   Add a ``entry_ref`` to the message.

   :param name: The name associated with the reference.
   :type name: str
   :param ref: The ``entry_ref`` to add.
   :type ref: entry_ref
   :returns: ``B_OK`` on success, or an error code otherwise.
   :rtype: int
)doc", py::arg("name"), py::arg("ref"))
.def("AddNodeRef", &BMessage::AddNodeRef, R"doc(
   Add a ``node_ref`` to the message.

   :param name: The name associated with the node reference.
   :type name: str
   :param ref: The ``node_ref`` to add.
   :type ref: node_ref
   :returns: ``B_OK`` on success, or an error code otherwise.
   :rtype: int
)doc", py::arg("name"), py::arg("ref"))
.def("AddMessage", &BMessage::AddMessage, R"doc(
   Add another ``BMessage`` to this message.

   :param name: The name associated with the nested message.
   :type name: str
   :param message: The ``BMessage`` object to add.
   :type message: BMessage
   :returns: ``B_OK`` on success, or an error code otherwise.
   :rtype: int
)doc", py::arg("name"), py::arg("message"))
.def("AddFlat", py::overload_cast<const char *, BFlattenable *, int32>(&BMessage::AddFlat), R"doc(
   Add a ``BFlattenable`` object to the message.

:param name: The name associated with the object.
:type name: str
:param object: The ``BFlattenable`` object to add.
:type object: BFlattenable
:param count: Number of objects to add (default is 1).
:type count: int
:returns: ``B_OK`` on success, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("object"), py::arg("count")=1)
.def("AddFlat", py::overload_cast<const char *, const BFlattenable *, int32>(&BMessage::AddFlat), R"doc(
   Add a ``const BFlattenable`` object to the message.

:param name: The name associated with the object.
:type name: str
:param object: The ``const BFlattenable`` object to add.
:type object: const BFlattenable
:param count: Number of objects to add (default is 1).
:type count: int
:returns: ``B_OK`` on success, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("object"), py::arg("count")=1)
//.def("AddData", &BMessage::AddData, "", py::arg("name"), py::arg("type"), py::arg("data"), py::arg("numBytes"), py::arg("isFixedSize")=true, py::arg("count")=1)
.def("AddData", [](BMessage& self, const char* name, type_code type, py::buffer data, ssize_t numBytes, bool isFixedSize, int32 count) { 
	py::buffer_info info = data.request();
	const void* buffer = info.ptr;
	return self.AddData(name,type,buffer,numBytes,isFixedSize,count);
},R"doc(
   Add arbitrary binary data to the message.
   The assigned type must be a specific data type; it should not be ``B_ANY_TYPE``.
   ``fixedSize`` and ``numItems`` are usefull to add an array of data under a new
   name. If ``fixedSize`` is ``True``, each item in the array must have the same number
   of bytes; otherwise, items can vary in size. ``numItems`` tells the 
   object to pre-allocate storage for some number of items. This isn't a limit,
   you can add more than numItems to the field.
   Note: For ``B_RAW_TYPE``, if you want to use ``ReplaceData``, you need to set
   ``isFixedSize`` as ``False`` if you need a different sized data

   :param name: The name associated with the data.
   :type name: str
   :param type: The type code representing the data type.
   :type type: int
   :param data: A buffer containing the data to add.
   :type data: py::buffer (e.g. bytes, bytearray, numpy.ndarray)
   :param numBytes: Number of bytes to add from the buffer.
   :type numBytes: int
   :param isFixedSize: Whether the data has a fixed size (default is ``True``).
   :type isFixedSize: bool
   :param count: Number of elements in the data array (default is 1).
   :type count: int
   :returns: ``B_OK`` on success, or an error code otherwise.
   :rtype: int
)doc", py::arg("name"), py::arg("type"), py::arg("data"), py::arg("numBytes"), py::arg("isFixedSize")=true, py::arg("count")=1)
.def("Append", &BMessage::Append,R"doc(
   Append another ``BMessage`` to this message, merging its contents.

   :param message: The ``BMessage`` object to append.
   :type message: BMessage
   :returns: ``B_OK`` on success, or an error code otherwise.
   :rtype: int
)doc", py::arg("message"))
.def("RemoveData", &BMessage::RemoveData, R"doc(
   Remove data of a specified name from the message.

   :param name: The name of the data to remove.
   :type name: str
   :param index: The index of the data to remove (default is 0).
   :type index: int
   :returns: ``B_OK`` on success, or an error code otherwise.
   :rtype: int
)doc", py::arg("name"), py::arg("index")=0)
.def("RemoveName", &BMessage::RemoveName, R"doc(
   Remove all the data associated with a given name.

   :param name: The name to remove from the message.
   :type name: str
   :returns: ``B_OK`` on success, or an error code otherwise.
   :rtype: int
)doc", py::arg("name"))
.def("MakeEmpty", &BMessage::MakeEmpty, R"doc(
   Empties the message, removing all data and specifiers.

   :returns: ``B_OK`` on success, or an error code otherwise.
   :rtype: int
)doc")

.def("FindAlignment", py::overload_cast<const char *, BAlignment *>(&BMessage::FindAlignment, py::const_), R"doc(
   Find a ``BAlignment`` object in the message by name.

:param name: The name associated with the ``BAlignment``.
:type name: str
:param alignment: Output parameter to store the found ``BAlignment``.
:type alignment: BAlignment
:returns: ``B_OK`` if the alignment is found, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("alignment"))
.def("FindAlignment", py::overload_cast<const char *, int32, BAlignment *>(&BMessage::FindAlignment, py::const_), R"doc(
   Find a ``BAlignment`` object in the message by name and index.

:param name: The name associated with the ``BAlignment``.
:type name: str
:param index: The index of the alignment to find.
:type index: int
:param alignment: Output parameter to store the found ``BAlignment``.
:type alignment: BAlignment
:returns: ``B_OK`` if the alignment is found, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("alignment"))
.def("FindAlignment", &PythonicFindAlignmentWrapper, R"doc(
   Find a ``BAlignment`` object in the message by name and (optionally) by index.
   This function returns a tuple containing the API call status and the
   resulting ``BAlignment`` object.

:param name: The name associated with the ``BAlignment``.
:type name: str
:param index: The index of the alignment to find (default is 0).
:type index: int
:returns: A tuple ``(status, object)``:

         - ``status`` (int): ``B_OK`` if the alignment is found, or an error code otherwise.
         - ``object`` (BAlignment): the ``BAlignment`` object found, ``None`` if it fails.

:rtype: tuple
)doc", py::arg("name"), py::arg("n")=0)
.def("FindRect", py::overload_cast<const char *, BRect *>(&BMessage::FindRect, py::const_), R"doc(
   Find a ``BRect`` object in the message by name.

:param name: The name associated with the ``BRect``.
:type name: str
:param rect: Output parameter to store the found ``BRect``.
:type rect: BRect
:returns: ``B_OK`` if the rectangle is found, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("rect"))
.def("FindRect", py::overload_cast<const char *, int32, BRect *>(&BMessage::FindRect, py::const_), R"doc(
   Find a ``BRect`` object in the message by name and index.

:param name: The name associated with the ``BRect``.
:type name: BRect
:param index: The index of the rectangle to find.
:type index: int
:param rect: Output parameter to store the found ``BRect``.
:type rect: BRect
:returns: ``B_OK`` if the rectangle is found, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("rect"))
.def("FindRect", &PythonicFindRectWrapper, R"doc(
   Find BRect by name and optional index, but instead filling an output parameter,
   this method returns a tuple containing the API call status and the resulting
   ``BRect`` object.

:param name: The name associated with the ``BRect``.
:type name: str
:param n: The optional index of the ``BRect`` to find (default is 0).
:type n: int, optional
:returns: A tuple ``(status, object)``:

         - ``status`` (int): ``B_OK`` if the ``BRect`` is found, or an error code otherwise.
         - ``object`` (BRect): the ``BRect`` object found, ``None`` if it fails.

:rtype: tuple
)doc", py::arg("name"), py::arg("n")=0)

.def("FindPoint", py::overload_cast<const char *, BPoint *>(&BMessage::FindPoint, py::const_), R"doc(
   Find a ``BPoint`` by name.

:param name: The name associated with the ``BPoint``.
:type name: str
:param point: Output parameter that will receive the ``BPoint``.
:type point: BPoint
:returns: ``B_OK`` if the point is found, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("point"))
.def("FindPoint", py::overload_cast<const char *, int32, BPoint *>(&BMessage::FindPoint, py::const_), R"doc(
   Find a ``BPoint`` by name and index.

:param name: The name associated with the ``BPoint``.
:type name: str
:param index: The index of the ``BPoint`` to retrieve.
:type index: int
:param point: Output parameter that will receive the ``BPoint``.
:type point: BPoint
:returns: ``B_OK`` if the point is found, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("point"))
.def("FindPoint", &PythonicFindPointWrapper, R"doc(
   Find a ``BPoint`` by name and optional index, but instead filling an output parameter, 
   this method returns a tuple containing the API call status and the resulting 
   ``BPoint`` object.

:param name: The name associated with the ``BPoint``.
:type name: str
:param n: The optional index of the ``BPoint`` to retrieve (default is 0).
:type n: int, optional
:returns: A tuple ``(status, object)``:

         - ``status`` (int): ``B_OK`` if the ``BPoint`` is found, or an error code otherwise.
         - ``object`` (BPoint): the ``BPoint`` object found, ``None`` if it fails.

:rtype: tuple
)doc", py::arg("name"), py::arg("n")=0)
.def("FindSize", py::overload_cast<const char *, BSize *>(&BMessage::FindSize, py::const_), R"doc(
   Find a ``BSize`` by name.

:param name: The name associated with the ``BSize`` object.
:type name: str
:param size: Output parameter that will receive the ``BSize``.
:type size: BSize
:returns: ``B_OK`` if the size is found, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("size"))
.def("FindSize", py::overload_cast<const char *, int32, BSize *>(&BMessage::FindSize, py::const_), R"doc(
   Find a ``BSize`` by name and index.

:param name: The name associated with the ``BSize``.
:type name: str
:param index: The index of the BSize to retrieve.
:type index: int
:param size: Output parameter that will receive the ``BSize``.
:type size: BSize
:returns: ``B_OK`` if the size is found, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("size"))
.def("FindSize", &PythonicFindSizeWrapper, R"doc(
   Find a ``BSize`` by name and optional index, but instead filling an output parameter, 
   this method returns a tuple containing the API call status and the resulting 
   ``BSize`` object.

:param name: The name associated with the ``BSize`` object.
:type name: str
:param n: The optional index of the ``BSize`` to retrieve (default is 0).
:type n: int, optional
:returns: A tuple ``(status, object)``:

         - ``status`` (int): ``B_OK`` if the ``BSize`` is found, or an error code otherwise.
         - ``object`` (BSize): the ``BSize`` object found, ``None`` if it fails.

:rtype: tuple
)doc", py::arg("name"), py::arg("n")=0)
//.def("FindString", py::overload_cast<BMessage &, const char *, std::string *>(&FindStringWrapper), "", py::arg("name"), py::arg("string"))
//.def("FindString", py::overload_cast<BMessage &, const char *, int32, std::string *>(&FindStringWrapper), "", py::arg("name"), py::arg("index"), py::arg("string"))
.def("FindString", &PythonicFindStringWrapper, R"doc(
   Find a string by name and optional index, but instead filling an output parameter, 
   this method returns a tuple containing the API call status and the resulting 
   string.

:param name: The name associated with the string.
:type name: str
:param n: The optional index of the string to retrieve (default is 0).
:type n: int, optional
:returns: A tuple ``(status, string)``:

         - ``status`` (int): ``B_OK`` if the BSize is found, or an error code otherwise.
         - ``string`` (string): the string found, (``None``) if it fails

:rtype: tuple
)doc", py::arg("name"), py::arg("n")=0)
.def("FindBString", &PythonicFindBStringWrapper, R"doc(
   Find a string by name and optional index, but instead filling an output parameter, 
   this method returns a tuple containing the API call status and the resulting 
   string as ``BString`` object.

:param name: The name associated with the string.
:type name: str
:param n: The optional index of the string to retrieve (default is 0).
:type n: int, optional
:returns: A tuple ``(status, string)``:

         - ``status`` (int): ``B_OK`` if the BSize is found, or an error code otherwise.
         - ``string`` (BString): the string found as ``BString``, ``None`` if it fails.

:rtype: tuple
)doc", py::arg("name"), py::arg("n")=0)
.def("FindString", py::overload_cast<const char *, BString *>(&BMessage::FindString, py::const_), R"doc(
   Find a string by name and write it in a ``BString`` object.

:param name: The name associated with the string.
:type name: str
:param string: Output parameter that will receive the ``BString``.
:type string: BString
:returns: ``B_OK`` if the size is found, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("string"))
.def("FindString", py::overload_cast<const char *, int32, BString *>(&BMessage::FindString, py::const_), R"doc(
   Find a string by name and index and write it in a ``BString`` object.

:param name: The name associated with the string.
:type name: str
:param index: The index of the string to retrieve.
:type index: int
:param string: Output parameter that will receive the ``BString``.
:type string: BString
:returns: ``B_OK`` if the size is found, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("string"))

.def("FindStrings", &BMessage::FindStrings, R"doc(
   Find a list of strings by name and write it in a ``BStringList`` object.

:param name: The name associated with the list of strings.
:type name: str
:param list: Output parameter that will receive the ``BStringList``.
:type list: BStringList
:returns: ``B_OK`` if the size is found, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("list"))
.def("FindStrings", &PythonicFindStringsWrapper, R"doc(
   Find a list of strings by name, but instead filling an output parameter, 
   this method returns a tuple containing the API call status and the resulting 
   ``BStringList`` object.

:param name: The name associated with the list of strings.
:type name: str
:returns: A tuple ``(status, list)``:

         - ``status`` (int): ``B_OK`` if the BSize is found, or an error code otherwise.
         - ``list`` (BStringList): the list of strings found as ``BStringList``, ``None`` if it fails.

:rtype: tuple
)doc", py::arg("name"))
//.def("FindInt8", py::overload_cast<const char *, int8 *>(&BMessage::FindInt8, py::const_), "", py::arg("name"), py::arg("value"))
//.def("FindInt8", py::overload_cast<const char *, int32, int8 *>(&BMessage::FindInt8, py::const_), "", py::arg("name"), py::arg("index"), py::arg("value"))
//.def("FindUInt8", py::overload_cast<const char *, uint8 *>(&BMessage::FindUInt8, py::const_), "", py::arg("name"), py::arg("value"))
//.def("FindUInt8", py::overload_cast<const char *, int32, uint8 *>(&BMessage::FindUInt8, py::const_), "", py::arg("name"), py::arg("index"), py::arg("value"))
.def("FindInt8",  &PythonicFindInt8Wrapper, R"doc(
   Find a int8 by name and optional index, this method returns a tuple 
   containing the API call status and the resulting int8 value.
   
   :param name: The name associated with the int8.
   :type name: str
   :param n: The optional index of the int8 to retrieve (default is 0).
   :type n: int, optional
   :returns: A tuple ``(status, value)``:

         - ``status`` (int): ``B_OK`` if the int8 is found, or an error code otherwise.
         - ``value`` (int): the int8 value, ``None`` if it fails.

   :rtype: tuple
)doc", py::arg("name"), py::arg("n")=0)
.def("FindUInt8",  &PythonicFindUInt8Wrapper, R"doc(
   Find a uint8 by name and optional index, this method returns a tuple 
   containing the API call status and the resulting uint8 value.

   :param name: The name associated with the uint8.
   :type name: str
   :param n: The optional index of the uint8 to retrieve (default is 0).
   :type n: int, optional
   :returns: A tuple ``(status, value)``:

         - ``status`` (int): ``B_OK`` if the uint8 is found, or an error code otherwise.
         - ``value`` (uint): the uint8 value, ``None`` if it fails.

   :rtype: tuple
)doc", py::arg("name"), py::arg("n")=0)
//.def("FindInt16", py::overload_cast<const char *, int16 *>(&BMessage::FindInt16, py::const_), "", py::arg("name"), py::arg("value"))
//.def("FindInt16", py::overload_cast<const char *, int32, int16 *>(&BMessage::FindInt16, py::const_), "", py::arg("name"), py::arg("index"), py::arg("value"))
//.def("FindUInt16", py::overload_cast<const char *, uint16 *>(&BMessage::FindUInt16, py::const_), "", py::arg("name"), py::arg("value"))
//.def("FindUInt16", py::overload_cast<const char *, int32, uint16 *>(&BMessage::FindUInt16, py::const_), "", py::arg("name"), py::arg("index"), py::arg("value"))
.def("FindInt16", &PythonicFindInt16Wrapper, R"doc(
   Find a int16 by name and optional index, this method returns a tuple 
   containing the API call status and the resulting int16 value. 

   :param name: The name associated with the int16.
   :type name: str
   :param n: The optional index of the int16 to retrieve (default is 0).
   :type n: int, optional
   :returns: A tuple ``(status, value)``:

         - ``status`` (int): ``B_OK`` if the int16 is found, or an error code otherwise.
         - ``value`` (int): the int16 value, ``None`` if it fails.

   :rtype: tuple
)doc", py::arg("name"), py::arg("n")=0)
.def("FindUInt16", &PythonicFindUInt16Wrapper, R"doc(
   Find a uint16 by name and optional index, this method returns a tuple 
   containing the API call status and the resulting uint16 value. 

   :param name: The name associated with the uint16.
   :type name: str
   :param n: The optional index of the uint16 to retrieve (default is 0).
   :type n: int, optional
   :returns: A tuple ``(status, value)``:

         - ``status`` (int): ``B_OK`` if the uint16 is found, or an error code otherwise.
         - ``value`` (uint): the uint16 value, ``None`` if it fails.

   :rtype: tuple
)doc", py::arg("name"), py::arg("n")=0)
//.def("FindInt32", py::overload_cast<const char *, int32 *>(&BMessage::FindInt32, py::const_), "", py::arg("name"), py::arg("value"))
//.def("FindInt32", py::overload_cast<const char *, int32, int32 *>(&BMessage::FindInt32, py::const_), "", py::arg("name"), py::arg("index"), py::arg("value"))
//.def("FindUInt32", py::overload_cast<const char *, uint32 *>(&BMessage::FindUInt32, py::const_), "", py::arg("name"), py::arg("value"))
//.def("FindUInt32", py::overload_cast<const char *, int32, uint32 *>(&BMessage::FindUInt32, py::const_), "", py::arg("name"), py::arg("index"), py::arg("value"))
.def("FindInt32", &PythonicFindInt32Wrapper, R"doc(
   Find a int32 by name and optional index, this method returns a tuple 
   containing the API call status and the resulting int32 value. 

   :param name: The name associated with the int32.
   :type name: str
   :param n: The optional index of the int32 to retrieve (default is 0).
   :type n: int, optional
   :returns: A tuple ``(status, value)``:

         - ``status`` (int): ``B_OK`` if the int32 is found, or an error code otherwise.
         - ``value`` (int): the int32 value, ``None`` if it fails.

   :rtype: tuple
)doc", py::arg("name"), py::arg("n")=0)
.def("FindUInt32", &PythonicFindUInt32Wrapper, R"doc(
   Find a uint32 by name and optional index, this method returns a tuple 
   containing the API call status and the resulting uint32 value. 

   :param name: The name associated with the uint32.
   :type name: str
   :param n: The optional index of the uint32 to retrieve (default is 0).
   :type n: int, optional
   :returns: A tuple ``(status, value)``:

         - ``status`` (int): ``B_OK`` if the uint32 is found, or an error code otherwise.
         - ``value`` (uint): the uint32 value, ``None`` if it fails.

   :rtype: tuple
)doc", py::arg("name"), py::arg("n")=0)
//.def("FindInt64", py::overload_cast<const char *, int64 *>(&BMessage::FindInt64, py::const_), "", py::arg("name"), py::arg("value"))
//.def("FindInt64", py::overload_cast<const char *, int32, int64 *>(&BMessage::FindInt64, py::const_), "", py::arg("name"), py::arg("index"), py::arg("value"))
//.def("FindUInt64", py::overload_cast<const char *, uint64 *>(&BMessage::FindUInt64, py::const_), "", py::arg("name"), py::arg("value"))
//.def("FindUInt64", py::overload_cast<const char *, int32, uint64 *>(&BMessage::FindUInt64, py::const_), "", py::arg("name"), py::arg("index"), py::arg("value"))
.def("FindInt64", &PythonicFindInt64Wrapper, R"doc(
   Find a int64 by name and optional index, this method returns a tuple 
   containing the API call status and the resulting int64 value. 

   :param name: The name associated with the int64.
   :type name: str
   :param n: The optional index of the int64 to retrieve (default is 0).
   :type n: int, optional
   :returns: A tuple ``(status, value)``:

         - ``status`` (int): ``B_OK`` if the int64 is found, or an error code otherwise.
         - ``value`` (int): the int64 value, ``None`` if it fails.

   :rtype: tuple
)doc", py::arg("name"), py::arg("n")=0)
.def("FindUInt64", &PythonicFindUInt64Wrapper, R"doc(
   Find a uint64 by name and optional index, this method returns a tuple 
   containing the API call status and the resulting uint64 value. 

   :param name: The name associated with the uint64.
   :type name: str
   :param n: The optional index of the uint64 to retrieve (default is 0).
   :type n: int, optional
   :returns: A tuple ``(status, value)``:

         - ``status`` (int): ``B_OK`` if the uint64 is found, or an error code otherwise.
         - ``value`` (uint): the uint64 value, ``None`` if it fails.

   :rtype: tuple
)doc", py::arg("name"), py::arg("n")=0)
//.def("FindBool", py::overload_cast<const char *, bool *>(&BMessage::FindBool, py::const_), "", py::arg("name"), py::arg("value"))
//.def("FindBool", py::overload_cast<const char *, int32, bool *>(&BMessage::FindBool, py::const_), "", py::arg("name"), py::arg("index"), py::arg("value"))
.def("FindBool", &PythonicFindBoolWrapper, R"doc(
   Find a bool by name and optional index, this method returns a tuple 
   containing the API call status and the resulting bool value. 

   :param name: The name associated with the bool.
   :type name: str
   :param n: The optional index of the bool to retrieve (default is 0).
   :type n: int, optional
   :returns: A tuple ``(status, value)``:

         - ``status`` (int): ``B_OK`` if the bool is found, or an error code otherwise.
         - ``value`` (bool): the bool value, ``None`` if it fails.

   :rtype: tuple
)doc", py::arg("name"), py::arg("n")=0)
//.def("FindFloat", py::overload_cast<const char *, float *>(&BMessage::FindFloat, py::const_), "", py::arg("name"), py::arg("value"))
//.def("FindFloat", py::overload_cast<const char *, int32, float *>(&BMessage::FindFloat, py::const_), "", py::arg("name"), py::arg("index"), py::arg("value"))
.def("FindFloat", &PythonicFindFloatWrapper, R"doc(
   Find a float by name and optional index, this method returns a tuple 
   containing the API call status and the resulting float value. 

   :param name: The name associated with the float.
   :type name: str
   :param n: The optional index of the float to retrieve (default is 0).
   :type n: int, optional
   :returns: A tuple ``(status, value)``:

         - ``status`` (int): ``B_OK`` if the float is found, or an error code otherwise.
         - ``value`` (float): the float value, ``None`` if it fails.

   :rtype: tuple
)doc", py::arg("name"), py::arg("n")=0)
//.def("FindDouble", py::overload_cast<const char *, double *>(&BMessage::FindDouble, py::const_), "", py::arg("name"), py::arg("value"))
//.def("FindDouble", py::overload_cast<const char *, int32, double *>(&BMessage::FindDouble, py::const_), "", py::arg("name"), py::arg("index"), py::arg("value"))
.def("FindDouble", &PythonicFindDoubleWrapper, R"doc(
   Find a double by name and optional index, this method returns a tuple 
   containing the API call status and the resulting double value. 

   :param name: The name associated with the double.
   :type name: str
   :param n: The optional index of the double to retrieve (default is 0).
   :type n: int, optional
   :returns: A tuple ``(status, value)``:

         - ``status`` (int): ``B_OK`` if the double is found, or an error code otherwise.
         - ``value`` (double): the double value, ``None`` if it fails.

   :rtype: tuple
)doc", py::arg("name"), py::arg("n")=0)

.def("FindColor", py::overload_cast<const char *, rgb_color *>(&BMessage::FindColor, py::const_), R"doc(
   Find a ``rgb_color`` object in the message by name.

:param name: The name associated with the ``rgb_color``.
:type name: str
:param value: Output parameter to store the found ``rgb_color``.
:type value: rgb_color
:returns: ``B_OK`` if the ``rgb_color`` is found, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("value"))
.def("FindColor", py::overload_cast<const char *, int32, rgb_color *>(&BMessage::FindColor, py::const_), R"doc(
   Find a ``rgb_color`` object in the message by name and index.

:param name: The name associated with the ``rgb_color``.
:type name: str
:param index: The index of the ``rgb_color`` to retrieve.
:type index: int
:param value: Output parameter to store the found ``rgb_color``.
:type value: rgb_color
:returns: ``B_OK`` if the ``rgb_color`` is found, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("value"))
.def("FindColor", &PythonicFindColorWrapper, R"doc(
   Find a ``rgb_color`` by name and optional index, but instead filling an output 
   parameter, this method returns a tuple containing the API call status and the 
   resulting ``rgb_color`` object.

:param name: The name associated with the ``rgb_color``.
:type name: str
:param n: The optional index of the ``rgb_color`` to retrieve (default is 0).
:type n: int, optional
:returns: A tuple ``(status, color)``:

         - ``status`` (int): ``B_OK`` if the ``rgb_color`` is found, or an error code otherwise.
         - ``color`` (rgb_color): the ``rgb_color`` found, ``None`` if it fails.

:rtype: tuple
)doc", py::arg("name"), py::arg("n")=0)
//.def("FindPointer", py::overload_cast<const char *, void * *>(&BMessage::FindPointer, py::const_), "", py::arg("name"), py::arg("pointer"))
//.def("FindPointer", py::overload_cast<const char *, int32, void * *>(&BMessage::FindPointer, py::const_), "", py::arg("name"), py::arg("index"), py::arg("pointer"))

.def("FindMessenger", py::overload_cast<const char *, BMessenger *>(&BMessage::FindMessenger, py::const_), R"doc(
   Find a ``BMessenger`` object in the message by name.

:param name: The name associated with the ``BMessenger``.
:type name: str
:param messenger: Output parameter to store the found ``BMessenger``.
:type messenger: BMessenger
:returns: ``B_OK`` if the ``BMessenger`` is found, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("messenger"))
.def("FindMessenger", py::overload_cast<const char *, int32, BMessenger *>(&BMessage::FindMessenger, py::const_), R"doc(
   Find a ``BMessenger`` object in the message by name and index.

:param name: The name associated with the ``BMessenger``.
:type name: str
:param index: The index of the ``BMessenger`` to retrieve.
:type index: int
:param messenger: Output parameter to store the found ``BMessenger``.
:type messenger: BMessenger
:returns: ``B_OK`` if the ``BMessenger`` is found, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("messenger"))
.def("FindMessenger", &PythonicFindMessengerWrapper, R"doc(
   Find a ``BMessenger`` by name and optional index, but instead filling an output 
   parameter, this method returns a tuple containing the API call status and the 
   resulting ``BMessenger`` object.

:param name: The name associated with the ``BMessenger``.
:type name: str
:param n: The optional index of the ``BMessenger`` to retrieve (default is 0).
:type n: int, optional
:returns: A tuple ``(status, messenger)``:

         - ``status`` (int): ``B_OK`` if the ``BMessenger`` is found, or an error code otherwise.
         - ``messenger`` (BMessenger): the ``BMessenger`` found, ``None`` if it fails.

:rtype: tuple
)doc", py::arg("name"), py::arg("n")=0)
.def("FindRef", py::overload_cast<const char *, entry_ref *>(&BMessage::FindRef, py::const_), R"doc(
   Find an ``entry_ref`` object in the message by name.

:param name: The name associated with the ``entry_ref``.
:type name: str
:param ref: Output parameter to store the found ``entry_ref``.
:type ref: entry_ref
:returns: ``B_OK`` if the ``entry_ref`` is found, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("ref"))
.def("FindRef", py::overload_cast<const char *, int32, entry_ref *>(&BMessage::FindRef, py::const_), R"doc(
   Find an ``entry_ref`` object in the message by name and index.

:param name: The name associated with the ``entry_ref``.
:type name: str
:param index: The index of the ``entry_ref`` to retrieve.
:type index: int
:param ref: Output parameter to store the found ``entry_ref``.
:type ref: entry_ref
:returns: ``B_OK`` if the ``entry_ref`` is found, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("ref"))
.def("FindRef", &PythonicFindRefWrapper, R"doc(
   Find an ``entry_ref`` by name and optional index, but instead filling an output 
   parameter, this method returns a tuple containing the API call status and the 
   resulting ``entry_ref`` object.

:param name: The name associated with the ``entry_ref``.
:type name: str
:param n: The optional index of the ``entry_ref`` to retrieve (default is 0).
:type n: int, optional
:returns: A tuple ``(status, ref)``:

         - ``status`` (int): ``B_OK`` if the ``entry_ref`` is found, or an error code otherwise.
         - ``ref`` (entry_ref): the ``entry_ref`` found, ``None`` if it fails.

:rtype: tuple
)doc", py::arg("name"), py::arg("n")=0)
.def("FindNodeRef", py::overload_cast<const char *, node_ref *>(&BMessage::FindNodeRef, py::const_), R"doc(
   Find an ``node_ref`` object in the message by name.

:param name: The name associated with the ``node_ref``.
:type name: str
:param ref: Output parameter to store the found ``node_ref``.
:type ref: node_ref
:returns: ``B_OK`` if the ``node_ref`` is found, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("ref"))
.def("FindNodeRef", py::overload_cast<const char *, int32, node_ref *>(&BMessage::FindNodeRef, py::const_), R"doc(
   Find an ``node_ref`` object in the message by name and index.

:param name: The name associated with the ``node_ref``.
:type name: str
:param index: The index of the ``node_ref`` to retrieve.
:type index: int
:param ref: Output parameter to store the found ``node_ref``.
:type ref: node_ref
:returns: ``B_OK`` if the ``node_ref`` is found, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("ref"))
.def("FindNodeRef", &PythonicFindNodeRefWrapper, R"doc(
   Find an ``node_ref`` by name and optional index, but instead filling an output 
   parameter, this method returns a tuple containing the API call status and the 
   resulting ``node_ref`` object.

:param name: The name associated with the ``node_ref``.
:type name: str
:param n: The optional index of the ``node_ref`` to retrieve (default is 0).
:type n: int, optional
:returns: A tuple ``(status, nodref)``:

         - ``status`` (int): ``B_OK`` if the ``node_ref`` is found, or an error code otherwise.
         - ``nodref`` (node_ref): the ``node_ref`` found, ``None`` if it fails.

:rtype: tuple
)doc", py::arg("name"), py::arg("n")=0)
.def("FindMessage", py::overload_cast<const char *, BMessage *>(&BMessage::FindMessage, py::const_), R"doc(
   Find an ``BMessage`` object in the message by name.

:param name: The name associated with the ``BMessage``.
:type name: str
:param message: Output parameter to store the found ``BMessage``.
:type message: BMessage
:returns: ``B_OK`` if the ``BMessage`` is found, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("message"))
.def("FindMessage", py::overload_cast<const char *, int32, BMessage *>(&BMessage::FindMessage, py::const_), R"doc(
   Find an ``BMessage`` object in the message by name and index.

:param name: The name associated with the ``BMessage``.
:type name: str
:param index: The index of the ``BMessage`` to retrieve.
:type index: int
:param message: Output parameter to store the found ``BMessage``.
:type message: BMessage
:returns: ``B_OK`` if the ``BMessage`` is found, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("message"))
.def("FindMessage", &PythonicFindMessageWrapper, R"doc(
   Find a ``BMessage`` by name and optional index, but instead filling an output 
   parameter, this method returns a tuple containing the API call status and the 
   resulting ``BMessage`` object.

:param name: The name associated with the ``BMessage``.
:type name: str
:param n: The optional index of the ``BMessage`` to retrieve (default is 0).
:type n: int, optional
:returns: A tuple ``(status, nodref)``:

         - ``status`` (int): ``B_OK`` if the ``BMessage`` is found, or an error code otherwise.
         - ``nodref`` (BMessage): the ``BMessage`` found, ``None`` if it fails.

:rtype: tuple
)doc", py::arg("name"), py::arg("n")=0)
.def("FindFlat", py::overload_cast<const char *, BFlattenable *>(&BMessage::FindFlat, py::const_), R"doc(
   Find an ``BFlattenable`` object in the message by name.

:param name: The name associated with the ``BFlattenable``.
:type name: str
:param object: Output parameter to store the found ``BFlattenable``.
:type object: BFlattenable
:returns: ``B_OK`` if the ``BFlattenable`` is found, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("object"))
.def("FindFlat", py::overload_cast<const char *, int32, BFlattenable *>(&BMessage::FindFlat, py::const_), R"doc(
   Find an ``BFlattenable`` object in the message by name and index.

:param name: The name associated with the ``BFlattenable``.
:type name: str
:param index: The index of the ``BFlattenable`` to retrieve.
:type index: int
:param object: Output parameter to store the found ``BFlattenable``.
:type object: BFlattenable
:returns: ``B_OK`` if the ``BFlattenable`` is found, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("object"))
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
}, R"doc(
   Find by name a binary data field of a specified type. If type is ``B_ANY_TYPE``, 
   the function provides the data no matter what type it actually is. 
   But if type is a specific data type, it provides the data only if 
   the name field holds data of that particular type. This method 
   returns a tuple containing the API call status and the resulting bytes object.

:param name: The name associated with the data field.
:type name: str
:param type: the type code of the data excpeted.
:type type: type_code
:returns: A tuple ``(status, data)``:

         - ``status`` (int): ``B_OK`` if the specified data field is found, or an error code otherwise.
         - ``data`` (bytes): the data found, ``None`` if it fails.

:rtype: tuple
)doc", py::arg("name"), py::arg("type"))
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
}, R"doc(
   Find a binary data field of a specified type, by name and index. If type 
   is ``B_ANY_TYPE``, the function provides the data no matter what type it 
   actually is. But if type is a specific data type, it provides the data 
   only if the name field holds data of that particular type. This method 
   returns a tuple containing the API call status and the resulting bytes 
   object.

:param name: The name associated with the data field.
:type name: str
:param type: the type code of the data excpeted.
:type type: type_code
:param index: the index of the data to retrieve.
:type index: int
:returns: A tuple ``(status, data)``:

         - ``status`` (int): ``B_OK`` if the specified data field is found, or an error code otherwise.
         - ``data`` (bytes): the data found, ``None`` if it fails.

:rtype: tuple
)doc", py::arg("name"), py::arg("type"), py::arg("index"))
.def("ReplaceAlignment", py::overload_cast<const char *, const BAlignment &>(&BMessage::ReplaceAlignment), R"doc(
   Replace by name the first or the only existing ``BAlignment`` item in 
   the message with another one.
   If this call fails it returns ``B_ERROR`` in case of read-only message 
   (like while the message is being dragged), ``B_NAME_NOT_FOUND`` if name
   doesn't exist, or ``B_BAD_TYPE`` if the field doesn't contin data of the
   ``BAlignment`` type.
 
   This function is typically used to update the value of an existing
   field.

:param name: The name associated with the ``BAlignment`` field to replace.
:type name: str
:param alignment: The new ``BAlignment`` object to store.
:type alignment: BAlignment
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("alignment"))
.def("ReplaceAlignment", py::overload_cast<const char *, int32, const BAlignment &>(&BMessage::ReplaceAlignment), R"doc(
   Replace in the message an existing ``BAlignment`` item in the name array at the 
   index position with another ``BAlignment`` item. If the item is out of range, 
   the replacement fails. 

   If this call fails it returns ``B_ERROR`` in case of read-only message 
   (like while the message is being dragged), ``B_BAD_INDEX`` if the index is out
   of range, ``B_NAME_NOT_FOUND`` if name doesn't exist, or ``B_BAD_TYPE`` if the 
   field doesn't contin data of the ``BAlignment`` type.
 
   This function is typically used to update the value of an existing
   field.

:param name: The name associated with the ``BAlignment`` field to replace.
:type name: str
:param index: The index of the name array where replace the item.
:type index: int
:param alignment: The new ``BAlignment`` object to store.
:type alignment: BAlignment
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("alignment"))
.def("ReplaceRect", py::overload_cast<const char *, BRect>(&BMessage::ReplaceRect), R"doc(
   Replace by name the first or the only existing ``BRect`` item in 
   the message with another one.
   If this call fails it returns ``B_ERROR`` in case of read-only message 
   (like while the message is being dragged), ``B_NAME_NOT_FOUND`` if name
   doesn't exist, or ``B_BAD_TYPE`` if the field doesn't contin data of the
   ``BRect`` type.
 
   This function is typically used to update the value of an existing
   field.

:param name: The name associated with the ``BRect`` field to replace.
type name: str
:param rect: The new ``BRect`` object to store.
:type rect: BRect
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("rect"))
.def("ReplaceRect", py::overload_cast<const char *, int32, BRect>(&BMessage::ReplaceRect), R"doc(
   Replace in the message an existing ``BRect`` item in the name array at the 
   index position with another ``BRect`` item. If the item is out of range, 
   the replacement fails. 

   If this call fails it returns ``B_ERROR`` in case of read-only message 
   (like while the message is being dragged), ``B_BAD_INDEX`` if the index is out
   of range, ``B_NAME_NOT_FOUND`` if name doesn't exist, or ``B_BAD_TYPE`` if the 
   field doesn't contin data of the ``BRect`` type.
 
   This function is typically used to update the value of an existing
   field.

:param name: The name associated with the ``BRect`` field to replace.
:type name: str
:param index: The index of the name array where replace the item.
:type index: int
:param rect: The new ``BRect`` object to store.
:type rect: BRect
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("rect"))

.def("ReplacePoint", py::overload_cast<const char *, BPoint>(&BMessage::ReplacePoint), R"doc(
   Replace by name the first or the only existing ``BPoint`` item in 
   the message with another one.
   If this call fails it returns ``B_ERROR`` in case of read-only message 
   (like while the message is being dragged), ``B_NAME_NOT_FOUND`` if name
   doesn't exist, or ``B_BAD_TYPE`` if the field doesn't contin data of the
   ``BPoint`` type.
 
   This function is typically used to update the value of an existing
   field.

:param name: The name associated with the ``BPoint`` field to replace.
:type name: str
:param aPoint: The new ``BPoint`` object to store.
:type aPoint: BPoint
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("aPoint"))
.def("ReplacePoint", py::overload_cast<const char *, int32, BPoint>(&BMessage::ReplacePoint), R"doc(
   Replace in the message an existing ``BPoint`` item in the name array at the 
   index position with another ``BPoint`` item. If the item is out of range, 
   the replacement fails. 
   
   If this call fails it returns ``B_ERROR`` in case of read-only message 
   (like while the message is being dragged), ``B_BAD_INDEX`` if the index is out
   of range, ``B_NAME_NOT_FOUND`` if name doesn't exist, or ``B_BAD_TYPE`` if the 
   field doesn't contin data of the ``BPoint`` type.
 
   This function is typically used to update the value of an existing
   field.

:param name: The name associated with the ``BPoint`` field to replace.
:type name: str
:param index: The index of the name array where replace the item.
:type index: int
:param aPoint: The new ``BPoint`` object to store.
:type aPoint: BPoint
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("aPoint"))
.def("ReplaceSize", py::overload_cast<const char *, BSize>(&BMessage::ReplaceSize), R"doc(
   Replace by name the first or the only existing ``BSize`` item in 
   the message with another one.
   If this call fails it returns ``B_ERROR`` in case of read-only message 
   (like while the message is being dragged), ``B_NAME_NOT_FOUND`` if name
   doesn't exist, or ``B_BAD_TYPE`` if the field doesn't contin data of the
   ``BSize`` type.
 
   This function is typically used to update the value of an existing
   field.

:param name: The name associated with the BSize field to replace.
:type name: str
:param aSize: The new ``BSize`` object to store.
:type aSize: BSize
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("aSize"))
.def("ReplaceSize", py::overload_cast<const char *, int32, BSize>(&BMessage::ReplaceSize), R"doc(
   Replace in the message an existing ``BSize`` item in the name array at the 
   index position with another ``BSize`` item. If the item is out of range, 
   the replacement fails. 

   If this call fails it returns ``B_ERROR`` in case of read-only message 
   (like while the message is being dragged), ``B_BAD_INDEX`` if the index is out
   of range, ``B_NAME_NOT_FOUND`` if name doesn't exist, or ``B_BAD_TYPE`` if the 
   field doesn't contin data of the BSize type.
 
   This function is typically used to update the value of an existing
   field.

:param name: The name associated with the ``BSize`` field to replace.
:type name: str
:param index: The index of the name array where replace the item.
:type index: int
:param aSize: The new ``BSize`` object to store.
:type aSize: BSize
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("aSize"))
.def("ReplaceString", py::overload_cast<const char *, const char *>(&BMessage::ReplaceString), R"doc(
   Replace by name the first or the only existing string item in 
   the message with another one.
   If this call fails it returns ``B_ERROR`` in case of read-only message 
   (like while the message is being dragged), ``B_NAME_NOT_FOUND`` if name
   doesn't exist, or ``B_BAD_TYPE`` if the field doesn't contin data of the
   string type.
 
   This function is typically used to update the value of an existing
   field.

:param name: The name associated with the string to replace.
:type name: str
:param string: The new string to store.
:type string: str
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("string"))
.def("ReplaceString", py::overload_cast<const char *, int32, const char *>(&BMessage::ReplaceString), R"doc(
   Replace in the message an existing string item in the name array at the 
   index position with another string item. If the item is out of range, 
   the replacement fails. 

   If this call fails it returns ``B_ERROR`` in case of read-only message 
   (like while the message is being dragged), ``B_BAD_INDEX`` if the index is out
   of range, ``B_NAME_NOT_FOUND`` if name doesn't exist, or ``B_BAD_TYPE`` if the 
   field doesn't contin data of the string type.
 
   This function is typically used to update the value of an existing
   field.

:param name: The name associated with the string to replace.
:type name: str
:param index: The index of the name array where replace the item.
:type index: int
:param string: The new string to store.
:type string: str
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("string"))
.def("ReplaceString", py::overload_cast<const char *, const BString &>(&BMessage::ReplaceString), R"doc(
   Replace by name the first or the only existing ``BString`` item in 
   the message with another one.
   If this call fails it returns ``B_ERROR`` in case of read-only message 
   (like while the message is being dragged), ``B_NAME_NOT_FOUND`` if name
   doesn't exist, or ``B_BAD_TYPE`` if the field doesn't contin data of the
   ``BString`` type.
 
   This function is typically used to update the value of an existing
   field.

:param name: The name associated with the ``BString`` field to replace.
:type name: str
:param string: The new ``BString`` object to store.
:type string: BString
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("string"))
.def("ReplaceString", py::overload_cast<const char *, int32, const BString &>(&BMessage::ReplaceString), R"doc(
   Replace in the message an existing ``BString`` item in the name array at the 
   index position with another ``BString`` item. If the item is out of range, 
   the replacement fails. 

   If this call fails it returns ``B_ERROR`` in case of read-only message 
   (like while the message is being dragged), ``B_BAD_INDEX`` if the index is out
   of range, ``B_NAME_NOT_FOUND`` if name doesn't exist, or ``B_BAD_TYPE`` if the 
   field doesn't contin data of the BString type.
 
   This function is typically used to update the value of an existing
   field.

:param name: The name associated with the ``BString`` field to replace.
:type name: str
:param index: The index of the name array where replace the item.
:type index: int
:param string: The new ``BString`` object to store.
:type string: str
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("string"))

.def("ReplaceInt8", py::overload_cast<const char *, signed char>(&BMessage::ReplaceInt8), R"doc(
   Replace by name the first or the only existing int8 item in 
   the message with another one.
   If this call fails it returns ``B_ERROR`` in case of read-only message 
   (like while the message is being dragged), ``B_NAME_NOT_FOUND`` if name
   doesn't exist, or ``B_BAD_TYPE`` if the field doesn't contin data of the
   int8 type.
 
   This function is typically used to update the value of an existing
   field.

   .. note::

      While this method stores a 8-bit signed integer, 
      the Python parameter 'value' must be a standard Python 'int'. 
      Passing values outside int8 range may result in truncation 
      or unexpected behavior when interpreted by the underlying C++ API.

:param name: The name associated with the int8 field to replace.
:type name: str
:param value: The new ``int8`` to store.
:type value: int
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("value"))
.def("ReplaceInt8", py::overload_cast<const char *, int32, signed char>(&BMessage::ReplaceInt8), R"doc(
   Replace in the message an existing int8 item in the name array at the 
   index position with another int8 item. If the item is out of range, 
   the replacement fails. 

   If this call fails it returns ``B_ERROR`` in case of read-only message 
   (like while the message is being dragged), ``B_BAD_INDEX`` if the index is out
   of range, ``B_NAME_NOT_FOUND`` if name doesn't exist, or ``B_BAD_TYPE`` if the 
   field doesn't contin data of the int8 type.
 
   This function is typically used to update the value of an existing
   field.

   .. note::

      While this method stores a 8-bit signed integer, 
      the Python parameter 'value' must be a standard Python 'int'. 
      Passing values outside int8 range may result in truncation 
      or unexpected behavior when interpreted by the underlying C++ API.

:param name: The name associated with the int8 field to replace.
:type name: str
:param index: The index of the name array where replace the item.
:type index: int
:param value: The new ``int8`` to store.
:type value: int
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("value"))
.def("ReplaceUInt8", py::overload_cast<const char *, unsigned char>(&BMessage::ReplaceUInt8), R"doc(
   Replace by name the first or the only existing uint8 item in 
   the message with another one.

   If this call fails it returns ``B_ERROR`` in case of read-only message 
   (like while the message is being dragged), ``B_NAME_NOT_FOUND`` if name
   doesn't exist, or ``B_BAD_TYPE`` if the field doesn't contin data of the
   uint8 type.
 
   This function is typically used to update the value of an existing
   field.

   .. note::

      While this method stores a 8-bit unsigned integer, 
      the Python parameter 'value' must be a standard Python 'int'. 
      Passing values outside uint8 range may result in truncation 
      or unexpected behavior when interpreted by the underlying C++ API.

:param name: The name associated with the uint8 field to replace.
:type name: str
:param value: The new ``uint8`` to store.
:type value: int
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("value"))
.def("ReplaceUInt8", py::overload_cast<const char *, int32, unsigned char>(&BMessage::ReplaceUInt8), R"doc(
   Replace in the message an existing uint8 item in the name array at the 
   index position with another uint8 item. If the item is out of range, 
   the replacement fails. 

   If this call fails it returns ``B_ERROR`` in case of read-only message 
   (like while the message is being dragged), ``B_BAD_INDEX`` if the index is out
   of range, ``B_NAME_NOT_FOUND`` if name doesn't exist, or ``B_BAD_TYPE`` if the 
   field doesn't contin data of the uint8 type.
    
   This function is typically used to update the value of an existing
   field.

   .. note::

      While this method stores a 8-bit unsigned integer, 
      the Python parameter 'value' must be a standard Python 'int'. 
      Passing values outside uint8 range may result in truncation 
      or unexpected behavior when interpreted by the underlying C++ API.

:param name: The name associated with the uint8 field to replace.
:type name: str
:param index: The index of the name array where replace the item.
:type index: int
:param value: The new ``uint8`` to store.
:type value: int
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("value"))
.def("ReplaceInt16", py::overload_cast<const char *, int16>(&BMessage::ReplaceInt16), R"doc(
   Replace by name the first or the only existing int16 item in 
   the message with another one.

   If this call fails it returns ``B_ERROR`` in case of read-only message 
   (like while the message is being dragged), ``B_NAME_NOT_FOUND`` if name
   doesn't exist, or ``B_BAD_TYPE`` if the field doesn't contin data of the
   int16 type.
 
   This function is typically used to update the value of an existing
   field.

   .. note::

      While this method stores a 16-bit signed integer, 
      the Python parameter 'value' must be a standard Python 'int'. 
      Passing values outside int16 range may result in truncation 
      or unexpected behavior when interpreted by the underlying C++ API.

:param name: The name associated with the int16 field to replace.
:type name: str
:param value: The new ``int16`` to store.
:type value: int
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("value"))
.def("ReplaceInt16", py::overload_cast<const char *, int32, int16>(&BMessage::ReplaceInt16), R"doc(
   Replace in the message an existing int16 item in the name array at the 
   index position with another int16 item. If the item is out of range, 
   the replacement fails. 

   If this call fails it returns ``B_ERROR`` in case of read-only message 
   (like while the message is being dragged), ``B_BAD_INDEX`` if the index is out
   of range, ``B_NAME_NOT_FOUND`` if name doesn't exist, or ``B_BAD_TYPE`` if the 
   field doesn't contin data of the int16 type.
 
   This function is typically used to update the value of an existing
   field.

   .. note::

      While this method stores a 16-bit signed integer, 
      the Python parameter 'value' must be a standard Python 'int'. 
      Passing values outside int16 range may result in truncation 
      or unexpected behavior when interpreted by the underlying C++ API.

:param name: The name associated with the int16 field to replace.
:type name: str
:param index: The index of the name array where replace the item.
:type index: int
:param value: The new ``int16`` to store.
:type value: int
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("value"))
.def("ReplaceUInt16", py::overload_cast<const char *, uint16>(&BMessage::ReplaceUInt16), R"doc(
   Replace by name the first or the only existing uint16 item in 
   the message with another one.

   If this call fails it returns ``B_ERROR`` in case of read-only message 
   (like while the message is being dragged), ``B_NAME_NOT_FOUND`` if name
   doesn't exist, or ``B_BAD_TYPE`` if the field doesn't contin data of the
   uint16 type.
 
   This function is typically used to update the value of an existing
   field.

   .. note::

      While this method stores a 16-bit unsigned integer, 
      the Python parameter 'value' must be a standard Python 'int'. 
      Passing values outside uint16 range may result in truncation 
      or unexpected behavior when interpreted by the underlying C++ API.

:param name: The name associated with the uint16 field to replace.
:type name: str
:param value: The new ``uint16`` to store.
:type value: int
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("value"))
.def("ReplaceUInt16", py::overload_cast<const char *, int32, uint16>(&BMessage::ReplaceUInt16), R"doc(
   Replace in the message an existing uint16 item in the name array at the 
   index position with another uint16 item. If the item is out of range, 
   the replacement fails. 

   If this call fails it returns ``B_ERROR`` in case of read-only message 
   (like while the message is being dragged), ``B_BAD_INDEX`` if the index is out
   of range, ``B_NAME_NOT_FOUND`` if name doesn't exist, or ``B_BAD_TYPE`` if the 
   field doesn't contin data of the uint16 type.
 
   This function is typically used to update the value of an existing
   field.

   .. note::

      While this method stores a 16-bit usigned integer, 
      the Python parameter 'value' must be a standard Python 'int'. 
      Passing values outside uint16 range may result in truncation 
      or unexpected behavior when interpreted by the underlying C++ API.

:param name: The name associated with the uint16 field to replace.
:type name: str
:param index: The index of the name array where replace the item.
:type index: int
:param value: The new ``uint16`` to store.
:type value: int
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("value"))
.def("ReplaceInt32", py::overload_cast<const char *, int32>(&BMessage::ReplaceInt32), R"doc(
   Replace by name the first or the only existing int32 item in 
   the message with another one.

   If this call fails it returns ``B_ERROR`` in case of read-only message 
   (like while the message is being dragged), ``B_NAME_NOT_FOUND`` if name
   doesn't exist, or ``B_BAD_TYPE`` if the field doesn't contin data of the
   int32 type.
 
   This function is typically used to update the value of an existing
   field.

   .. note::

      While this method stores a 32-bit signed integer, 
      the Python parameter 'value' must be a standard Python 'int'. 
      Passing values outside int32 range may result in truncation 
      or unexpected behavior when interpreted by the underlying C++ API.

:param name: The name associated with the int32 field to replace.
:type name: str
:param value: The new ``int32`` to store.
:type value: int
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("value"))
.def("ReplaceInt32", py::overload_cast<const char *, int32, int32>(&BMessage::ReplaceInt32), R"doc(
   Replace in the message an existing int32 item in the name array at the 
   index position with another int32 item. If the item is out of range, 
   the replacement fails. 

   If this call fails it returns ``B_ERROR`` in case of read-only message 
   (like while the message is being dragged), ``B_BAD_INDEX`` if the index is out
   of range, ``B_NAME_NOT_FOUND`` if name doesn't exist, or ``B_BAD_TYPE`` if the 
   field doesn't contin data of the int32 type.
 
   This function is typically used to update the value of an existing
   field.

   .. note::

      While this method stores a 32-bit signed integer, 
      the Python parameter 'value' must be a standard Python 'int'. 
      Passing values outside int32 range may result in truncation 
      or unexpected behavior when interpreted by the underlying C++ API.

:param name: The name associated with the int32 field to replace.
:type name: str
:param index: The index of the name array where replace the item.
:type index: int
:param value: The new ``int32`` to store.
:type value: int
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("value"))
.def("ReplaceUInt32", py::overload_cast<const char *, uint32>(&BMessage::ReplaceUInt32), R"doc(
   Replace by name the first or the only existing uint32 item in 
   the message with another one.

   If this call fails it returns ``B_ERROR`` in case of read-only message 
   (like while the message is being dragged), ``B_NAME_NOT_FOUND`` if name
   doesn't exist, or ``B_BAD_TYPE`` if the field doesn't contin data of the
   uint32 type.
 
   This function is typically used to update the value of an existing
   field.

   .. note::

      While this method stores a 32-bit unsigned integer, 
      the Python parameter 'value' must be a standard Python 'int'. 
      Passing values outside uint32 range may result in truncation 
      or unexpected behavior when interpreted by the underlying C++ API.

:param name: The name associated with the uint32 field to replace.
:type name: str
:param value: The new ``uint32`` to store.
:type value: int
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("value"))
.def("ReplaceUInt32", py::overload_cast<const char *, int32, uint32>(&BMessage::ReplaceUInt32), R"doc(
   Replace in the message an existing uint32 item in the name array at the 
   index position with another uint32 item. If the item is out of range, 
   the replacement fails. 

   If this call fails it returns ``B_ERROR`` in case of read-only message 
   (like while the message is being dragged), ``B_BAD_INDEX`` if the index is out
   of range, ``B_NAME_NOT_FOUND`` if name doesn't exist, or ``B_BAD_TYPE`` if the 
   field doesn't contin data of the uint32 type.
 
   This function is typically used to update the value of an existing
   field.

   .. note::

      While this method stores a 32-bit unsigned integer, 
      the Python parameter 'value' must be a standard Python 'int'. 
      Passing values outside uint32 range may result in truncation 
      or unexpected behavior when interpreted by the underlying C++ API.


:param name: The name associated with the uint32 field to replace.
:type name: str
:param index: The index of the name array where replace the item.
:type index: int
:param value: The new ``uint32`` to store.
:type value: int
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("value"))
.def("ReplaceInt64", py::overload_cast<const char *, int64_t>(&BMessage::ReplaceInt64), R"doc(
Replace by name the first or the only existing int64 item in 
the message with another one.
If this call fails it returns ``B_ERROR`` in case of read-only message 
(like while the message is being dragged), ``B_NAME_NOT_FOUND`` if name
doesn't exist, or ``B_BAD_TYPE`` if the field doesn't contin data of the
int64 type.
 
This function is typically used to update the value of an existing
field.

:param name: The name associated with the int64 field to replace.
:type name: str
:param value: The new ``int64`` to store.
:type value: int
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("value"))
.def("ReplaceInt64", py::overload_cast<const char *, int32, int64_t>(&BMessage::ReplaceInt64), R"doc(
Replace in the message an existing int64 item in the name array at the 
index position with another int64 item. If the item is out of range, 
the replacement fails. 

If this call fails it returns ``B_ERROR`` in case of read-only message 
(like while the message is being dragged), ``B_BAD_INDEX`` if the index is out
of range, ``B_NAME_NOT_FOUND`` if name doesn't exist, or ``B_BAD_TYPE`` if the 
field doesn't contin data of the int64 type.
 
This function is typically used to update the value of an existing
field.

:param name: The name associated with the int64 field to replace.
:type name: str
:param index: The index of the name array where replace the item.
:type index: int
:param value: The new ``int64`` to store.
:type value: int
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("value"))
.def("ReplaceUInt64", py::overload_cast<const char *, uint64_t>(&BMessage::ReplaceUInt64), R"doc(
Replace by name the first or the only existing uint64 item in 
the message with another one.
If this call fails it returns ``B_ERROR`` in case of read-only message 
(like while the message is being dragged), ``B_NAME_NOT_FOUND`` if name
doesn't exist, or ``B_BAD_TYPE`` if the field doesn't contin data of the
uint64 type.
 
This function is typically used to update the value of an existing
field.

:param name: The name associated with the uint64 field to replace.
:type name: str
:param value: The new ``uint64`` to store.
:type value: int
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("value"))
.def("ReplaceUInt64", py::overload_cast<const char *, int32, uint64_t>(&BMessage::ReplaceUInt64), R"doc(
Replace in the message an existing uint64 item in the name array at the 
index position with another uint64 item. If the item is out of range, 
the replacement fails. 

If this call fails it returns ``B_ERROR`` in case of read-only message 
(like while the message is being dragged), ``B_BAD_INDEX`` if the index is out
of range, ``B_NAME_NOT_FOUND`` if name doesn't exist, or ``B_BAD_TYPE`` if the 
field doesn't contin data of the uint64 type.
 
This function is typically used to update the value of an existing
field.

:param name: The name associated with the uint64 field to replace.
:type name: str
:param index: The index of the name array where replace the item.
:type index: int
:param value: The new ``uint64`` to store.
:type value: int
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("value"))

.def("ReplaceBool", py::overload_cast<const char *, bool>(&BMessage::ReplaceBool), R"doc(
Replace by name the first or the only existing bool item in 
the message with another one.
If this call fails it returns ``B_ERROR`` in case of read-only message 
(like while the message is being dragged), ``B_NAME_NOT_FOUND`` if name
doesn't exist, or ``B_BAD_TYPE`` if the field doesn't contin data of the
bool type.
 
This function is typically used to update the value of an existing
field.

:param name: The name associated with the bool field to replace.
:type name: str
:param value: The new ``bool`` to store.
:type value: bool
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("value"))
.def("ReplaceBool", py::overload_cast<const char *, int32, bool>(&BMessage::ReplaceBool), R"doc(
Replace in the message an existing bool item in the name array at the 
index position with another bool item. If the item is out of range, 
the replacement fails. 

If this call fails it returns ``B_ERROR`` in case of read-only message 
(like while the message is being dragged), ``B_BAD_INDEX`` if the index is out
of range, ``B_NAME_NOT_FOUND`` if name doesn't exist, or ``B_BAD_TYPE`` if the 
field doesn't contin data of the bool type.
 
This function is typically used to update the value of an existing
field.

:param name: The name associated with the bool field to replace.
:type name: str
:param index: The index of the name array where replace the item.
:type index: int
:param value: The new ``bool`` to store.
:type value: bool
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("value"))
.def("ReplaceFloat", py::overload_cast<const char *, float>(&BMessage::ReplaceFloat), R"doc(
Replace by name the first or the only existing float item in 
the message with another one.
If this call fails it returns ``B_ERROR`` in case of read-only message 
(like while the message is being dragged), ``B_NAME_NOT_FOUND`` if name
doesn't exist, or ``B_BAD_TYPE`` if the field doesn't contin data of the
float type.
 
This function is typically used to update the value of an existing
field.

:param name: The name associated with the float field to replace.
:type name: str
:param value: The new ``float`` to store.
:type value: float
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("value"))
.def("ReplaceFloat", py::overload_cast<const char *, int32, float>(&BMessage::ReplaceFloat), R"doc(
Replace in the message an existing float item in the name array at the 
index position with another float item. If the item is out of range, 
the replacement fails. 

If this call fails it returns ``B_ERROR`` in case of read-only message 
(like while the message is being dragged), ``B_BAD_INDEX`` if the index is out
of range, ``B_NAME_NOT_FOUND`` if name doesn't exist, or ``B_BAD_TYPE`` if the 
field doesn't contin data of the float type.
 
This function is typically used to update the value of an existing
field.

:param name: The name associated with the float field to replace.
:type name: str
:param index: The index of the name array where replace the item.
:type index: int
:param value: The new ``float`` to store.
:type value: float
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("value"))
.def("ReplaceDouble", py::overload_cast<const char *, double>(&BMessage::ReplaceDouble), R"doc(
Replace by name the first or the only existing double item in 
the message with another one.
If this call fails it returns ``B_ERROR`` in case of read-only message 
(like while the message is being dragged), ``B_NAME_NOT_FOUND`` if name
doesn't exist, or ``B_BAD_TYPE`` if the field doesn't contin data of the
double type.
 
This function is typically used to update the value of an existing
field.

:param name: The name associated with the double field to replace.
:type name: str
:param value: The new ``double`` to store.
:type value: double
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("value"))
.def("ReplaceDouble", py::overload_cast<const char *, int32, double>(&BMessage::ReplaceDouble), R"doc(
Replace in the message an existing double item in the name array at the 
index position with another double item. If the item is out of range, 
the replacement fails. 

If this call fails it returns ``B_ERROR`` in case of read-only message 
(like while the message is being dragged), ``B_BAD_INDEX`` if the index is out
of range, ``B_NAME_NOT_FOUND`` if name doesn't exist, or ``B_BAD_TYPE`` if the 
field doesn't contin data of the double type.
 
This function is typically used to update the value of an existing
field.

:param name: The name associated with the double field to replace.
:type name: str
:param index: The index of the name array where replace the item.
:type index: int
:param value: The new ``double`` to store.
:type value: double
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("value"))
.def("ReplaceColor", py::overload_cast<const char *, rgb_color>(&BMessage::ReplaceColor), R"doc(
Replace by name the first or the only existing ``rgb_color`` item in 
the message with another one.
If this call fails it returns ``B_ERROR`` in case of read-only message 
(like while the message is being dragged), ``B_NAME_NOT_FOUND`` if name
doesn't exist, or ``B_BAD_TYPE`` if the field doesn't contin data of the
``rgb_color`` type.
 
This function is typically used to update the value of an existing
field.

:param name: The name associated with the ``rgb_color`` field to replace.
:type name: str
:param color: The new ``rgb_color`` object to store.
:type color: rgb_color
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("color"))
.def("ReplaceColor", py::overload_cast<const char *, int32, rgb_color>(&BMessage::ReplaceColor), R"doc(
Replace in the message an existing rgb_color item in the name array at the 
index position with another ``rgb_color`` item. If the item is out of range, 
the replacement fails. 

If this call fails it returns ``B_ERROR`` in case of read-only message 
(like while the message is being dragged), ``B_BAD_INDEX`` if the index is out
of range, ``B_NAME_NOT_FOUND`` if name doesn't exist, or ``B_BAD_TYPE`` if the 
field doesn't contin data of the ``rgb_color`` type.
 
This function is typically used to update the value of an existing
field.

:param name: The name associated with the ``rgb_color`` field to replace.
:type name: str
:param index: The index of the name array where replace the item.
:type index: int
:param color: The new ``rgb_color`` object to store.
:type color: rgb_color
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("color"))
.def("ReplacePointer", py::overload_cast<const char *, const void *>(&BMessage::ReplacePointer), "", py::arg("name"), py::arg("pointer"))
.def("ReplacePointer", py::overload_cast<const char *, int32, const void *>(&BMessage::ReplacePointer), "", py::arg("name"), py::arg("index"), py::arg("pointer"))
.def("ReplaceMessenger", py::overload_cast<const char *, BMessenger>(&BMessage::ReplaceMessenger), R"doc(
Replace by name the first or the only existing ``BMessenger`` item in 
the message with another one.
If this call fails it returns ``B_ERROR`` in case of read-only message 
(like while the message is being dragged), ``B_NAME_NOT_FOUND`` if name
doesn't exist, or ``B_BAD_TYPE`` if the field doesn't contin data of the
``BMessenger`` type.
 
This function is typically used to update the value of an existing
field.

:param name: The name associated with the ``BMessenger`` field to replace.
:type name: str
:param messenger: The new ``BMessenger`` object to store.
:type messenger: BMessenger
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("messenger"))
.def("ReplaceMessenger", py::overload_cast<const char *, int32, BMessenger>(&BMessage::ReplaceMessenger), R"doc(
Replace in the message an existing ``BMessenger`` item in the name array at the 
index position with another ``BMessenger`` item. If the item is out of range, 
the replacement fails. 

If this call fails it returns ``B_ERROR`` in case of read-only message 
(like while the message is being dragged), ``B_BAD_INDEX`` if the index is out
of range, ``B_NAME_NOT_FOUND`` if name doesn't exist, or ``B_BAD_TYPE`` if the 
field doesn't contin data of the ``BMessenger`` type.
 
This function is typically used to update the value of an existing
field.

:param name: The name associated with the ``BMessenger`` field to replace.
:type name: str
:param index: The index of the name array where replace the item.
:type index: int
:param messenger: The new ``BMessenger`` object to store.
:type messenger: BMessenger
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("messenger"))
.def("ReplaceRef", py::overload_cast<const char *, const entry_ref *>(&BMessage::ReplaceRef), R"doc(
Replace by name the first or the only existing ``entry_ref`` item in 
the message with another one.
If this call fails it returns ``B_ERROR`` in case of read-only message 
(like while the message is being dragged), ``B_NAME_NOT_FOUND`` if name
doesn't exist, or ``B_BAD_TYPE`` if the field doesn't contin data of the
``entry_ref`` type.
 
This function is typically used to update the value of an existing
field.

:param name: The name associated with the ``entry_ref`` field to replace.
:type name: str
:param ref: The new ``entry_ref`` object to store.
:type ref: entry_ref
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("ref"))
.def("ReplaceRef", py::overload_cast<const char *, int32, const entry_ref *>(&BMessage::ReplaceRef), R"doc(
Replace in the message an existing ``entry_ref`` item in the name array at the 
index position with another ``entry_ref`` item. If the item is out of range, 
the replacement fails. 

If this call fails it returns ``B_ERROR`` in case of read-only message 
(like while the message is being dragged), ``B_BAD_INDEX`` if the index is out
of range, ``B_NAME_NOT_FOUND`` if name doesn't exist, or ``B_BAD_TYPE`` if the 
field doesn't contin data of the ``entry_ref`` type.
 
This function is typically used to update the value of an existing
field.

:param name: The name associated with the ``entry_ref`` field to replace.
:type name: str
:param index: The index of the name array where replace the item.
:type index: int
:param ref: The new ``entry_ref`` object to store.
:type ref: entry_ref
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("ref"))
.def("ReplaceNodeRef", py::overload_cast<const char *, const node_ref *>(&BMessage::ReplaceNodeRef), R"doc(
Replace by name the first or the only existing ``node_ref`` item in 
the message with another one.
If this call fails it returns ``B_ERROR`` in case of read-only message 
(like while the message is being dragged), ``B_NAME_NOT_FOUND`` if name
doesn't exist, or ``B_BAD_TYPE`` if the field doesn't contin data of the
``node_ref`` type.
 
This function is typically used to update the value of an existing
field.

:param name: The name associated with the ``node_ref`` field to replace.
:type name: str
:param ref: The new ``node_ref`` object to store.
:type ref: node_ref
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("ref"))
.def("ReplaceNodeRef", py::overload_cast<const char *, int32, const node_ref *>(&BMessage::ReplaceNodeRef), R"doc(
Replace in the message an existing node_ref item in the name array at the 
index position with another ``node_ref`` item. If the item is out of range, 
the replacement fails. 

If this call fails it returns ``B_ERROR`` in case of read-only message 
(like while the message is being dragged), ``B_BAD_INDEX`` if the index is out
of range, ``B_NAME_NOT_FOUND`` if name doesn't exist, or ``B_BAD_TYPE`` if the 
field doesn't contin data of the ``node_ref`` type.
 
This function is typically used to update the value of an existing
field.

:param name: The name associated with the ``node_ref`` field to replace.
:type name: str
:param index: The index of the name array where replace the item.
:type index: int
:param ref: The new ``node_ref`` object to store.
:type ref: node_ref
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("ref"))
.def("ReplaceMessage", py::overload_cast<const char *, const BMessage *>(&BMessage::ReplaceMessage), R"doc(
Replace by name the first or the only existing ``BMessage`` item in 
the message with another one.
If this call fails it returns ``B_ERROR`` in case of read-only message 
(like while the message is being dragged), ``B_NAME_NOT_FOUND`` if name
doesn't exist, or ``B_BAD_TYPE`` if the field doesn't contin data of the
``BMessage`` type.
 
This function is typically used to update the value of an existing
field.

:param name: The name associated with the ``BMessage`` field to replace.
:type name: str
:param message: The new ``BMessage`` object to store.
:type message: BMessage
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("message"))
.def("ReplaceMessage", py::overload_cast<const char *, int32, const BMessage *>(&BMessage::ReplaceMessage), R"doc(
Replace in the message an existing ``BMessage`` item in the name array at the 
index position with another ``BMessage`` item. If the item is out of range, 
the replacement fails. 

If this call fails it returns ``B_ERROR`` in case of read-only message 
(like while the message is being dragged), ``B_BAD_INDEX`` if the index is out
of range, ``B_NAME_NOT_FOUND`` if name doesn't exist, or ``B_BAD_TYPE`` if the 
field doesn't contin data of the ``BMessage`` type.
 
This function is typically used to update the value of an existing
field.

:param name: The name associated with the ``BMessage`` field to replace.
:type name: str
:param index: The index of the name array where replace the item.
:type index: int
:param message: The new ``BMessage`` object to store.
:type message: BMessage
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("message"))
.def("ReplaceFlat", py::overload_cast<const char *, BFlattenable *>(&BMessage::ReplaceFlat), R"doc(
Replace by name the first or the only existing ``BFlattenable`` item in 
the message with another one.
If this call fails it returns ``B_ERROR`` in case of read-only message 
(like while the message is being dragged), ``B_NAME_NOT_FOUND`` if name
doesn't exist, or ``B_BAD_TYPE`` if the field doesn't contin data of the
``BFlattenable`` type.
 
This function is typically used to update the value of an existing
field.

:param name: The name associated with the ``BFlattenable`` field to replace.
:type name: str
:param object: The new ``BFlattenable`` object to store.
:type object: BFlattenable
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("object"))
.def("ReplaceFlat", py::overload_cast<const char *, int32, BFlattenable *>(&BMessage::ReplaceFlat), R"doc(
Replace in the message an existing ``BFlattenable`` item in the name array at the 
index position with another ``BFlattenable`` item. If the item is out of range, 
the replacement fails. 

If this call fails it returns ``B_ERROR`` in case of read-only message 
(like while the message is being dragged), ``B_BAD_INDEX`` if the index is out
of range, ``B_NAME_NOT_FOUND`` if name doesn't exist, or ``B_BAD_TYPE`` if the 
field doesn't contin data of the ``BFlattenable`` type.
 
This function is typically used to update the value of an existing
field.

:param name: The name associated with the ``BFlattenable`` field to replace.
:type name: str
:param index: The index of the name array where replace the item.
:type index: int
:param object: The new ``BFlattenable`` object to store.
:type object: BFlattenable
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("object"))
//.def("ReplaceData", py::overload_cast<const char *, type_code, const void *, ssize_t>(&BMessage::ReplaceData),
.def("ReplaceData",[](BMessage& self, const char* name, type_code type, py::buffer data) {
	py::buffer_info info = data.request();
	const void* buffer = info.ptr;
	ssize_t numBytes = info.size * info.itemsize;
	return self.ReplaceData(name, type, buffer, numBytes);
},R"doc(
Replace by name the first or the only existing data item in 
the message with another one.
If this call fails it returns ``B_ERROR`` in case of read-only message 
(like while the message is being dragged), ``B_NAME_NOT_FOUND`` if name
doesn't exist, or ``B_BAD_TYPE`` if the field doesn't contin data of the
data type.

The type must be specific; it can't be ``B_ANY_TYPE``.

This function is typically used to update the value of an existing
field.

..note::

    if you intend to replace a ``B_RAW_TYPE`` data and the new data dimension
    is different from the current one, the data field must have been previously
    created with the isFixedSize flag set to ``False``; otherwise, this function
    returns ``B_BAD_ADDRESS``.

:param name: The name associated with the data field to replace.
:type name: str
:param type: the type code of the data.
:type type: type_code
:param data: The new data to store.
:type data: py::buffer (e.g. bytes, bytearray, numpy.ndarray)
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("type"), py::arg("data"))
//.def("ReplaceData", py::overload_cast<const char *, type_code, int32, const void *, ssize_t>(&BMessage::ReplaceData), R"doc(
.def("ReplaceData",[](BMessage& self, const char* name, type_code type, int32 index, py::buffer data) {
	py::buffer_info info = data.request();
	const void* buffer = info.ptr;
	ssize_t numBytes = info.size * info.itemsize;
	return self.ReplaceData(name, type, index, buffer, numBytes);//(ssize_t)info.size);
},R"doc(
Replace in the message an existing data field in the name array at the 
index position with other data. If the item is out of range, 
the replacement fails. 

If this call fails it returns ``B_ERROR`` in case of read-only message 
(like while the message is being dragged), ``B_BAD_INDEX`` if the index is out
of range, ``B_NAME_NOT_FOUND`` if name doesn't exist, or ``B_BAD_TYPE`` if the 
field doesn't contin data of the data type.
The type must be specific; it can't be ``B_ANY_TYPE``.
 
This function is typically used to update the value of an existing
field.

..note::

    if you intend to replace a ``B_RAW_TYPE`` data and the new data dimension
    is different from the current one, the data field must have been previously
    created with the isFixedSize flag set to ``False``; otherwise, this function
    returns ``B_BAD_ADDRESS``.

:param name: The name associated with the data field to replace.
:type name: str
:param type: the type code of the data.
:type type: type_code
:param index: The index of the name array where replace the item.
:type index: int
:param data: The new data to store.
:type data: py::buffer (e.g. bytes, bytearray, numpy.ndarray)
:returns: ``B_OK`` on success, or an error code otherwise (read description).
:rtype: int
)doc", py::arg("name"), py::arg("type"), py::arg("index"), py::arg("data"))

.def("HasSameData", &BMessage::HasSameData, R"doc(
Checks if the current message has the same fields and data as another message.

This method is useful for comparing the content of two BMessages, optionally 
ignoring the field order and allowing for a recursive comparison of nested 
messages.

:param other: The ``BMessage`` to compare the current message with.
:type other: BMessage
:param ignoreFieldOrder: Optional, if ``True`` (default), the field order is ignored during comparison, otherwise the field order must be identical.
:type ignoreFieldOrder: bool, optional
:param deep: Optional, if ``True``, the comparison is "deep," nested BMessages are recursively compared. If ``False`` (default), nested messages are only compared by pointer, which generally means they must be the same object.
:type deep: bool, optional
:returns: ``True`` if the two BMessages contain the same data (according to the specified options), otherwise ``False``.
:rtype: bool
)doc", py::arg("other"), py::arg("ignoreFieldOrder")=true, py::arg("deep")=false)
/*
.def("operatornew", py::overload_cast<size_t>(&BMessage::operatornew), "", py::arg("size"))
.def("operatornew", py::overload_cast<size_t, void *>(&BMessage::operatornew), "", py::arg(""), py::arg("pointer"))
.def("operatornew", py::overload_cast<size_t, const std::nothrow_t &>(&BMessage::operatornew), "", py::arg(""), py::arg("noThrow"))
.def("operatordelete", &BMessage::operatordelete, "", py::arg("pointer"), py::arg("size"))
*/

.def("HasAlignment", &BMessage::HasAlignment, R"doc(
Checks if the ``BMessage`` contains a field with the specified name and 
of type ``B_ALIGNMENT_TYPE``.

:param name: The name associated with the ``BAlignment``.
:type name: str
:param n: Optional, the index of the field entry to check (default is 0)
:type n: int, optional
:returns: ``True`` if the field exists at the name and index and is ``B_ALIGNMENT_TYPE``, otherwise ``False``.
:rtype: bool
)doc", py::arg("name"), py::arg("n")=0)
.def("HasRect", &BMessage::HasRect, R"doc(
Checks if the ``BMessage`` contains a field with the specified name and 
of type ``B_RECT_TYPE``.

:param name: The name associated with the ``BRect``.
:type name: str
:param n: Optional, the index of the field entry to check (default is 0)
:type n: int, optional
:returns: ``True`` if the field exists at the name and index and is ``B_RECT_TYPE``, otherwise ``False``.
:rtype: bool
)doc", py::arg("name"), py::arg("n")=0)
.def("HasPoint", &BMessage::HasPoint, R"doc(
Checks if the ``BMessage`` contains a field with the specified name and 
of type ``B_POINT_TYPE``.

:param name: The name associated with the ``BPoint``.
:type name: str
:param n: Optional, the index of the field entry to check (default is 0)
:type n: int, optional
:returns: ``True`` if the field exists at the name and index and is ``B_POINT_TYPE``, otherwise ``False``.
:rtype: bool
)doc", py::arg("name"), py::arg("n")=0)
.def("HasSize", &BMessage::HasSize, R"doc(
Checks if the ``BMessage`` contains a field with the specified name and 
of type ``B_SIZE_TYPE``.

:param name: The name associated with the ``BSize``.
:type name: str
:param n: Optional, the index of the field entry to check (default is 0)
:type n: int, optional
:returns: ``True`` if the field exists at the name and index and is ``B_SIZE_TYPE``, otherwise ``False``.
:rtype: bool
)doc", py::arg("name"), py::arg("n")=0)
.def("HasString", &BMessage::HasString, R"doc(
Checks if the ``BMessage`` contains a field with the specified name and 
of type ``B_STRING_TYPE``.

:param name: The name associated with the string.
:type name: str
:param n: Optional, the index of the field entry to check (default is 0)
:type n: int, optional
:returns: ``True`` if the field exists at the name and index and is ``B_STRING_TYPE``, otherwise ``False``.
:rtype: bool
)doc", py::arg("name"), py::arg("n")=0)
.def("HasInt8", &BMessage::HasInt8, R"doc(
Checks if the ``BMessage`` contains a field with the specified name and 
of type ``B_INT8_TYPE``.

:param name: The name associated with the int8.
:type name: str
:param n: Optional, the index of the field entry to check (default is 0)
:type n: int, optional
:returns: ``True`` if the field exists at the name and index and is ``B_INT8_TYPE``, otherwise ``False``.
:rtype: bool
)doc", py::arg("name"), py::arg("n")=0)
.def("HasUInt8", &BMessage::HasUInt8, R"doc(
Checks if the ``BMessage`` contains a field with the specified name and 
of type ``B_UINT8_TYPE``.

:param name: The name associated with the uint8.
:type name: str
:param n: Optional, the index of the field entry to check (default is 0)
:type n: int, optional
:returns: ``True`` if the field exists at the name and index and is ``B_UINT8_TYPE``, otherwise ``False``.
:rtype: bool
)doc", py::arg("name"), py::arg("n")=0)
.def("HasInt16", &BMessage::HasInt16, R"doc(
Checks if the ``BMessage`` contains a field with the specified name and 
of type ``B_INT16_TYPE``.

:param name: The name associated with the int16.
:type name: str
:param n: Optional, the index of the field entry to check (default is 0)
:type n: int, optional
:returns: ``True`` if the field exists at the name and index and is ``B_INT16_TYPE``, otherwise ``False``.
:rtype: bool
)doc", py::arg("name"), py::arg("n")=0)
.def("HasUInt16", &BMessage::HasUInt16, R"doc(
Checks if the ``BMessage`` contains a field with the specified name and 
of type ``B_UINT16_TYPE``.

:param name: The name associated with the uint16.
:type name: str
:param n: Optional, the index of the field entry to check (default is 0)
:type n: int, optional
:returns: ``True`` if the field exists at the name and index and is ``B_UINT16_TYPE``, otherwise ``False``.
:rtype: bool
)doc", py::arg("name"), py::arg("n")=0)
.def("HasInt32", &BMessage::HasInt32, R"doc(
Checks if the ``BMessage`` contains a field with the specified name and 
of type ``B_INT32_TYPE``.

:param name: The name associated with the int32.
:type name: str
:param n: Optional, the index of the field entry to check (default is 0)
:type n: int, optional
:returns: ``True`` if the field exists at the name and index and is ``B_INT32_TYPE``, otherwise ``False``.
:rtype: bool
)doc", py::arg("name"), py::arg("n")=0)
.def("HasUInt32", &BMessage::HasUInt32, R"doc(
Checks if the ``BMessage`` contains a field with the specified name and 
of type ``B_UINT32_TYPE``.

:param name: The name associated with the uint32.
:type name: str
:param n: Optional, the index of the field entry to check (default is 0)
:type n: int, optional
:returns: ``True`` if the field exists at the name and index and is ``B_UINT32_TYPE``, otherwise ``False``.
:rtype: bool
)doc", py::arg("name"), py::arg("n")=0)
.def("HasInt64", &BMessage::HasInt64, R"doc(
Checks if the ``BMessage`` contains a field with the specified name and 
of type ``B_INT64_TYPE``.

:param name: The name associated with the int64.
:type name: str
:param n: Optional, the index of the field entry to check (default is 0)
:type n: int, optional
:returns: ``True`` if the field exists at the name and index and is ``B_INT64_TYPE``, otherwise ``False``.
:rtype: bool
)doc", py::arg("name"), py::arg("n")=0)
.def("HasUInt64", &BMessage::HasUInt64, R"doc(
Checks if the ``BMessage`` contains a field with the specified name and 
of type ``B_UINT64_TYPE``.

:param name: The name associated with the uint64.
:type name: str
:param n: Optional, the index of the field entry to check (default is 0)
:type n: int, optional
:returns: ``True`` if the field exists at the name and index and is ``B_UINT64_TYPE``, otherwise ``False``.
:rtype: bool
)doc", py::arg("name"), py::arg("n")=0)

.def("HasBool", &BMessage::HasBool, R"doc(
Checks if the ``BMessage`` contains a field with the specified name and 
of type ``B_BOOL_TYPE``.

:param name: The name associated with the bool.
:type name: str
:param n: Optional, the index of the field entry to check (default is 0)
:type n: int, optional
:returns: ``True`` if the field exists at the name and index and is ``B_BOOL_TYPE``, otherwise ``False``.
:rtype: bool
)doc", py::arg("name"), py::arg("n")=0)
.def("HasFloat", &BMessage::HasFloat, R"doc(
Checks if the BMessage contains a field with the specified name and 
of type ``B_FLOAT_TYPE``.

:param name: The name associated with the float.
:type name: str
:param n: Optional, the index of the field entry to check (default is 0)
:type n: int, optional
:returns: ``True`` if the field exists at the name and index and is ``B_FLOAT_TYPE``, otherwise ``False``.
:rtype: bool
)doc", py::arg("name"), py::arg("n")=0)
.def("HasDouble", &BMessage::HasDouble, R"doc(
Checks if the ``BMessage`` contains a field with the specified name and 
of type ``B_DOUBLE_TYPE``.

:param name: The name associated with the double.
:type name: str
:param n: Optional, the index of the field entry to check (default is 0)
:type n: int, optional
:returns: ``True`` if the field exists at the name and index and is ``B_DOUBLE_TYPE``, otherwise ``False``.
:rtype: bool
)doc", py::arg("name"), py::arg("n")=0)
.def("HasColor", &BMessage::HasColor, R"doc(
Checks if the ``BMessage`` contains a field with the specified name and 
of type ``B_RGB_COLOR_TYPE``.

:param name: The name associated with the ``rgb_color``.
:type name: str
:param n: Optional, the index of the field entry to check (default is 0)
:type n: int, optional
:returns: ``True`` if the field exists at the name and index and is ``B_RGB_COLOR_TYPE``, otherwise ``False``.
:rtype: bool
)doc", py::arg("name"), py::arg("n")=0)
.def("HasPointer", &BMessage::HasPointer, R"doc(
Checks if the ``BMessage`` contains a field with the specified name and 
of type ``B_POINTER_TYPE``.

:param name: The name associated with the pointer.
:type name: str
:param n: Optional, the index of the field entry to check (default is 0)
:type n: int, optional
:returns: ``True`` if the field exists at the name and index and is ``B_POINTER_TYPE``, otherwise ``False``.
:rtype: bool
)doc", py::arg("name"), py::arg("n")=0)
.def("HasMessenger", &BMessage::HasMessenger, R"doc(
Checks if the ``BMessage`` contains a field with the specified name and 
of type ``B_MESSENGER_TYPE``.

:param name: The name associated with the ``BMessenger``.
:type name: str
:param n: Optional, the index of the field entry to check (default is 0)
:type n: int, optional
:returns: ``True`` if the field exists at the name and index and is ``B_MESSENGER_TYPE``, otherwise ``False``.
:rtype: bool
)doc", py::arg("name"), py::arg("n")=0)
.def("HasRef", &BMessage::HasRef, R"doc(
Checks if the BMessage contains a field with the specified name and 
of type ``B_REF_TYPE``.

:param name: The name associated with the ``entry_ref``.
:type name: str
:param n: Optional, the index of the field entry to check (default is 0)
:type n: int, optional
:returns: ``True`` if the field exists at the name and index and is ``B_REF_TYPE``, otherwise ``False``.
:rtype: bool
)doc", py::arg("name"), py::arg("n")=0)
.def("HasNodeRef", &BMessage::HasNodeRef, R"doc(
Checks if the ``BMessage`` contains a field with the specified name and 
of type ``B_NODE_REF_TYPE``.

:param name: The name associated with the ``node_ref``.
:type name: str
:param n: Optional, the index of the field entry to check (default is 0)
:type n: int, optional
:returns: ``True`` if the field exists at the name and index and is ``B_NODE_REF_TYPE``, otherwise ``False``.
:rtype: bool
)doc", py::arg("name"), py::arg("n")=0)
.def("HasMessage", &BMessage::HasMessage, R"doc(
Checks if the ``BMessage`` contains a field with the specified name and 
of type ``B_MESSAGE_TYPE``.

:param name: The name associated with the ``BMessage``.
:type name: str
:param n: Optional, the index of the field entry to check (default is 0)
:type n: int, optional
:returns: ``True`` if the field exists at the name and index and is ``B_MESSAGE_TYPE``, otherwise ``False``.
:rtype: bool
)doc", py::arg("name"), py::arg("n")=0)

// TODO CHECK THESE FUNCTIONS BELOW *******************************************************************************
.def("HasFlat", py::overload_cast<const char *, const BFlattenable *>(&BMessage::HasFlat, py::const_), R"doc(
Checks if the ``BMessage`` contains a field with the specified name that 
holds data of a type matching the given ``BFlattenable`` object.

This is typically used to check for data types like ``BRect``, ``BPoint``, 
``BFont``, or other custom classes that inherit from ``BFlattenable``.

:param name: The name of the field to search for in the message.
:type name: str
:param object: A sample ``BFlattenable`` object whose type is used for comparison against the field's data type.
:type object: BFlattenable
:returns: ``True`` if the field exists and the object data type matches the sample one, otherwise ``False``.
:rtype: bool
)doc", py::arg("name"), py::arg("object"))
.def("HasFlat", py::overload_cast<const char *, int32, const BFlattenable *>(&BMessage::HasFlat, py::const_), R"doc(
Checks if the ``BMessage`` contains a field with the specified name and
index that holds data of a type matching the given BFlattenable object.

This version allows checking a specific instance (via index 'n') when 
multiple fields share the same name.

This is typically used to check for data types like ``BRect``, ``BPoint``, 
``BFont``, or other custom classes that inherit from ``BFlattenable``.

:param name: The name of the field to search for in the message.
:type name: str
:param n: The index of the field entry to check (0 for the first).
:type n: int
:param object: A sample ``BFlattenable`` object whose type is used for comparison against the field's data type.
:type object: BFlattenable
:returns: ``True`` if the field exists and the object data type matches the sample one, otherwise ``False``.
:rtype: bool
)doc", py::arg("name"), py::arg("n"), py::arg("object"))
.def("HasData", &BMessage::HasData, R"doc(
Checks if the ``BMessage`` contains a field with the specified name and type code.

This generic method checks the presence of any typed data in the message, 
including ``B_MESSAGE_TYPE``, ``B_REF_TYPE``, and all built-in types.

:param name: The name of the field to search for.
:type name: str
:param type: The specific Haiku type code (e.g., ``B_INT32_TYPE``, ``B_MESSAGE_TYPE``) the field must match.
:type type: type_code
:param n: Optional, the index of the field entry to check. Defaults to 0 (the first entry).
:type n: int, optional
:returns: ``True`` if the field with the specified name, type code, and index exists, otherwise ``False``.
:rtype: bool

)doc", py::arg("name"), py::arg("type"), py::arg("n")=0)
//.def("FindRect", py::overload_cast<const char *, int32>(&BMessage::FindRect, py::const_), "", py::arg("name"), py::arg("n")=0)
//.def("FindRectWithStatus", &PythonicFindRectWrapper, "", py::arg("name"), py::arg("n")=0)

//.def("FindPoint", py::overload_cast<const char *, int32>(&BMessage::FindPoint, py::const_), "", py::arg("name"), py::arg("n")=0)
//.def("FindPointWithStatus", &PythonicFindPointWrapper, "", py::arg("name"), py::arg("n")=0)
//.def("FindString", py::overload_cast<const char *, int32>(&BMessage::FindString, py::const_), "", py::arg("name"), py::arg("n")=0)
//.def("FindStringWithStatus", &PythonicFindStringWrapper, "", py::arg("name"), py::arg("n")=0)
//.def("FindInt8", py::overload_cast<const char *, int32>(&BMessage::FindInt8, py::const_), "", py::arg("name"), py::arg("n")=0)
//.def("FindInt8WithStatus",  &PythonicFindInt8Wrapper, "", py::arg("name"), py::arg("n")=0)
//.def("FindInt16", py::overload_cast<const char *, int32>(&BMessage::FindInt16, py::const_), "", py::arg("name"), py::arg("n")=0)
//.def("FindInt16WithStatus", &PythonicFindInt16Wrapper, "", py::arg("name"), py::arg("n")=0)
//.def("FindInt32", py::overload_cast<const char *, int32>(&BMessage::FindInt32, py::const_), "", py::arg("name"), py::arg("n")=0)
//.def("FindInt32WithStatus", &PythonicFindInt32Wrapper, "", py::arg("name"), py::arg("n")=0)
//.def("FindInt64", py::overload_cast<const char *, int32>(&BMessage::FindInt64, py::const_), "", py::arg("name"), py::arg("n")=0)
//.def("FindInt64WithStatus", &PythonicFindInt64Wrapper, "", py::arg("name"), py::arg("n")=0)
//.def("FindBool", py::overload_cast<const char *, int32>(&BMessage::FindBool, py::const_), "", py::arg("name"), py::arg("n")=0)
//.def("FindBoolWithStatus", &PythonicFindBoolWrapper, "", py::arg("name"), py::arg("n")=0)
//.def("FindFloat", py::overload_cast<const char *, int32>(&BMessage::FindFloat, py::const_), "", py::arg("name"), py::arg("n")=0)
//.def("FindFloatWithStatus", &PythonicFindFloatWrapper, "", py::arg("name"), py::arg("n")=0)
//.def("FindDouble", py::overload_cast<const char *, int32>(&BMessage::FindDouble, py::const_), "", py::arg("name"), py::arg("n")=0)
//.def("FindDoubleWithStatus", &PythonicFindDoubleWrapper, "", py::arg("name"), py::arg("n")=0)

.def("GetBool", py::overload_cast<const char *, bool>(&BMessage::GetBool, py::const_), R"doc(
Retrieves a boolean value from the field with the specified name.

This is a convenience method that simplifies retrieving a boolean from 
the message. If the field is not found, or if the field exists but is 
not of type ``B_BOOL_TYPE``, the given default value is returned.

:param name: The name of the field to retrieve the boolean from.
:type name: str
:param default_value: The value to return if the field is not found or is not of the correct type (``B_BOOL_TYPE``).
:type default_value: bool
:returns: The boolean value stored in the message, or the 'default_value' if the field doesn't exist or its type is incorrect.
:rtype: bool
)doc", py::arg("name"), py::arg("defaultValue")=false)
.def("GetBool", py::overload_cast<const char *, int32, bool>(&BMessage::GetBool, py::const_), R"doc(
Retrieves a boolean value from the field with the specified name 
and index.

This is a convenience method that simplifies retrieving a boolean from 
the message. If the field is not found, or if the field exists but is 
not of type ``B_BOOL_TYPE``, the given default value is returned.

:param name: The name of the field to retrieve the boolean from.
:type name: str
:param index: The index of the field entry to retrieve.
:typeindex: int
:param default_value: The value to return if the field is not found or is not of the correct type (``B_BOOL_TYPE``).
:type default_value: bool
:returns: The boolean value stored in the message, or the 'default_value' if the field doesn't exist or its type is incorrect.
:rtype: bool
)doc", py::arg("name"), py::arg("index"), py::arg("defaultValue"))
.def("GetInt8", py::overload_cast<const char *, signed char>(&BMessage::GetInt8, py::const_), R"doc(
Retrieves an 8-bit signed integer (int8) value from the field with 
the specified name.

This is a convenience method that simplifies retrieving an int8 from 
the message. If the field is not found, or if the field exists but is 
not of type ``B_INT8_TYPE``, the given default value is returned.

:param name: The name of the field to retrieve the int8 from.
:type name: str
:param default_value: The value to return if the field is not found or is not of the correct type (``B_INT8_TYPE``).
:type default_value: int
:returns: The 8-bit signed integer value stored in the message, or the 'default_value' if the field doesn't exist or its type is incorrect.
:rtype: int
)doc", py::arg("name"), py::arg("defaultValue"))
.def("GetInt8", py::overload_cast<const char *, int32, signed char>(&BMessage::GetInt8, py::const_), R"doc(
Retrieves an 8-bit signed integer (int8) value from the field with 
the specified name and index.

This is a convenience method that simplifies retrieving an int8 from 
the message. If the field is not found, or if the field exists but is 
not of type ``B_INT8_TYPE``, the given default value is returned.

:param name: The name of the field to retrieve the int8 from.
:type name: str
:param index: The index of the field entry to retrieve.
:type index: int
:param default_value: The value to return if the field is not found or is not of the correct type (``B_INT8_TYPE``).
:type default_value: int
:returns: The 8-bit signed integer value stored in the message, or the 'default_value' if the field doesn't exist or its type is incorrect.
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("defaultValue"))
.def("GetUInt8", py::overload_cast<const char *, unsigned char>(&BMessage::GetUInt8, py::const_), R"doc(
Retrieves an 8-bit unsigned integer (uint8) value from the field with 
the specified name.

This is a convenience method that simplifies retrieving an uint8 from 
the message. If the field is not found, or if the field exists but is 
not of type ``B_UINT8_TYPE``, the given default value is returned.

:param name: The name of the field to retrieve the uint8 from.
:type name: str
:param default_value: The value to return if the field is not found or is not of the correct type (``B_UINT8_TYPE``).
:type default_value: uint
:returns: The 8-bit unsigned integer value stored in the message, or the 'default_value' if the field doesn't exist or its type is incorrect.
:rtype: int
)doc", py::arg("name"), py::arg("defaultValue"))
.def("GetUInt8", py::overload_cast<const char *, int32, unsigned char>(&BMessage::GetUInt8, py::const_), R"doc(
Retrieves an 8-bit unsigned integer (uint8) value from the field with 
the specified name and index.

This is a convenience method that simplifies retrieving an uint8 from 
the message. If the field is not found, or if the field exists but is 
not of type ``B_UINT8_TYPE``, the given default value is returned.

:param name: The name of the field to retrieve the uint8 from.
:type name: str
:param index: The index of the field entry to retrieve.
:type index: int
:param default_value: The value to return if the field is not found or is not of the correct type (``B_UINT8_TYPE``).
:type default_value: int
:returns: The 8-bit unsigned integer value stored in the message, or the 'default_value' if the field doesn't exist or its type is incorrect.
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("defaultValue"))
.def("GetInt16", py::overload_cast<const char *, int16>(&BMessage::GetInt16, py::const_), R"doc(
Retrieves an 16-bit signed integer (int16) value from the field with 
the specified name.

This is a convenience method that simplifies retrieving an int16 from 
the message. If the field is not found, or if the field exists but is 
not of type ``B_INT16_TYPE``, the given default value is returned.

:param name: The name of the field to retrieve the int16 from.
:type name: str
:param default_value: The value to return if the field is not found or is not of the correct type (``B_INT16_TYPE``).
:type default_value: int
:returns: The 16-bit signed integer value stored in the message, or the 'default_value' if the field doesn't exist or its type is incorrect.
:rtype: int
)doc", py::arg("name"), py::arg("defaultValue"))
.def("GetInt16", py::overload_cast<const char *, int32, int16>(&BMessage::GetInt16, py::const_), R"doc(
Retrieves an 16-bit signed integer (int16) value from the field with 
the specified name and index.

This is a convenience method that simplifies retrieving an int16 from 
the message. If the field is not found, or if the field exists but is 
not of type ``B_INT16_TYPE``, the given default value is returned.

:param name: The name of the field to retrieve the int16 from.
:type name: str
:param index: The index of the field entry to retrieve.
:type index: int
:param default_value: The value to return if the field is not found or is not of the correct type (``B_INT16_TYPE``).
:type default_value: int
:returns: The 16-bit signed integer value stored in the message, or the 'default_value' if the field doesn't exist or its type is incorrect.
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("defaultValue"))
.def("GetUInt16", py::overload_cast<const char *, uint16>(&BMessage::GetUInt16, py::const_), R"doc(
Retrieves an 16-bit unsigned integer (uint16) value from the field with 
the specified name.

This is a convenience method that simplifies retrieving an uint16 from 
the message. If the field is not found, or if the field exists but is 
not of type ``B_UINT16_TYPE``, the given default value is returned.

:param name: The name of the field to retrieve the uint16 from.
:type name: str
:param default_value: The value to return if the field is not found or is not of the correct type (``B_UINT16_TYPE``).
:type default_value: int
:returns: The 16-bit unsigned integer value stored in the message, or the 'default_value' if the field doesn't exist or its type is incorrect.
:rtype: int
)doc", py::arg("name"), py::arg("defaultValue"))
.def("GetUInt16", py::overload_cast<const char *, int32, uint16>(&BMessage::GetUInt16, py::const_), R"doc(
Retrieves an 16-bit unsigned integer (uint16) value from the field with 
the specified name and index.

This is a convenience method that simplifies retrieving an uint16 from 
the message. If the field is not found, or if the field exists but is 
not of type ``B_UINT16_TYPE``, the given default value is returned.

:param name: The name of the field to retrieve the uint16 from.
:type name: str
:param index: The index of the field entry to retrieve.
:type index: int
:param default_value: The value to return if the field is not found or is not of the correct type (``B_UINT16_TYPE``).
:type default_value: int
:returns: The 16-bit unsigned integer value stored in the message, or the 'default_value' if the field doesn't exist or its type is incorrect.
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("defaultValue"))
.def("GetInt32", py::overload_cast<const char *, int32>(&BMessage::GetInt32, py::const_), R"doc(
Retrieves an 32-bit signed integer (int32) value from the field with 
the specified name.

This is a convenience method that simplifies retrieving an int32 from 
the message. If the field is not found, or if the field exists but is 
not of type ``B_INT32_TYPE``, the given default value is returned.

:param name: The name of the field to retrieve the int32 from.
:type name: str
:param default_value: The value to return if the field is not found or is not of the correct type (``B_INT32_TYPE``).
:type default_value: int
:returns: The 32-bit signed integer value stored in the message, or the 'default_value' if the field doesn't exist or its type is incorrect.
:rtype: int
)doc", py::arg("name"), py::arg("defaultValue"))
.def("GetInt32", py::overload_cast<const char *, int32, int32>(&BMessage::GetInt32, py::const_), R"doc(
Retrieves an 32-bit signed integer (int32) value from the field with 
the specified name and index.

This is a convenience method that simplifies retrieving an int32 from 
the message. If the field is not found, or if the field exists but is 
not of type ``B_INT32_TYPE``, the given default value is returned.

:param name: The name of the field to retrieve the int32 from.
:type name: str
:param index: The index of the field entry to retrieve.
:type index: int
:param default_value: The value to return if the field is not found or is not of the correct type (``B_INT32_TYPE``).
:type default_value: int
:returns: The 32-bit signed integer value stored in the message, or the 'default_value' if the field doesn't exist or its type is incorrect.
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("defaultValue"))
.def("GetUInt32", py::overload_cast<const char *, uint32>(&BMessage::GetUInt32, py::const_), R"doc(
Retrieves an 32-bit unsigned integer (uint32) value from the field with 
the specified name.

This is a convenience method that simplifies retrieving an uint32 from 
the message. If the field is not found, or if the field exists but is 
not of type ``B_UINT32_TYPE``, the given default value is returned.

:param name: The name of the field to retrieve the uint32 from.
:type name: str
:param default_value: The value to return if the field is not found or is not of the correct type (``B_UINT32_TYPE``).
:type default_value: int
:returns: The 32-bit unsigned integer value stored in the message, or the 'default_value' if the field doesn't exist or its type is incorrect.
:rtype: int
)doc", py::arg("name"), py::arg("defaultValue"))
.def("GetUInt32", py::overload_cast<const char *, int32, uint32>(&BMessage::GetUInt32, py::const_), R"doc(
Retrieves an 32-bit unsigned integer (uint32) value from the field with 
the specified name and index.

This is a convenience method that simplifies retrieving an uint32 from 
the message. If the field is not found, or if the field exists but is 
not of type ``B_UINT32_TYPE``, the given default value is returned.

:param name: The name of the field to retrieve the uint32 from.
:type name: str
:param index: The index of the field entry to retrieve.
:type index: int
:param default_value: The value to return if the field is not found or is not of the correct type (``B_UINT32_TYPE``).
:type default_value: int
:returns: The 32-bit unsigned integer value stored in the message, or the 'default_value' if the field doesn't exist or its type is incorrect.
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("defaultValue"))
.def("GetInt64", py::overload_cast<const char *, int64_t>(&BMessage::GetInt64, py::const_), R"doc(
Retrieves an 64-bit signed integer (int64) value from the field with 
the specified name.

This is a convenience method that simplifies retrieving an int64 from 
the message. If the field is not found, or if the field exists but is 
not of type ``B_INT64_TYPE``, the given default value is returned.

:param name: The name of the field to retrieve the int64 from.
:type name: str
:param default_value: The value to return if the field is not found or is not of the correct type (``B_INT64_TYPE``).
:type default_value: int
:returns: The 64-bit signed integer value stored in the message, or the 'default_value' if the field doesn't exist or its type is incorrect.
:rtype: int
)doc", py::arg("name"), py::arg("defaultValue"))
.def("GetInt64", py::overload_cast<const char *, int32, int64_t>(&BMessage::GetInt64, py::const_), R"doc(
Retrieves an 64-bit signed integer (int64) value from the field with 
the specified name and index.

This is a convenience method that simplifies retrieving an int64 from 
the message. If the field is not found, or if the field exists but is 
not of type ``B_INT64_TYPE``, the given default value is returned.

:param name: The name of the field to retrieve the int64 from.
:type name: str
:param index: The index of the field entry to retrieve.
:type index: int
:param default_value: The value to return if the field is not found or is not of the correct type (``B_INT64_TYPE``).
:type default_value: int
:returns: The 64-bit signed integer value stored in the message, or the 'default_value' if the field doesn't exist or its type is incorrect.
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("defaultValue"))
.def("GetUInt64", py::overload_cast<const char *, uint64_t>(&BMessage::GetUInt64, py::const_), R"doc(
Retrieves an 64-bit unsigned integer (uint64) value from the field with 
the specified name.

This is a convenience method that simplifies retrieving an uint64 from 
the message. If the field is not found, or if the field exists but is 
not of type ``B_UINT64_TYPE``, the given default value is returned.

:param name: The name of the field to retrieve the uint64 from.
:type name: str
:param default_value: The value to return if the field is not found or is not of the correct type (``B_UINT64_TYPE``).
:type default_value: int
:returns: The 64-bit unsigned integer value stored in the message, or the 'default_value' if the field doesn't exist or its type is incorrect.
:rtype: int
)doc", py::arg("name"), py::arg("defaultValue"))
.def("GetUInt64", py::overload_cast<const char *, int32, uint64_t>(&BMessage::GetUInt64, py::const_), R"doc(
Retrieves an 64-bit unsigned integer (uint64) value from the field with 
the specified name and index.

This is a convenience method that simplifies retrieving an uint64 from 
the message. If the field is not found, or if the field exists but is 
not of type ``B_UINT64_TYPE``, the given default value is returned.

:param name: The name of the field to retrieve the uint64 from.
:type name: str
:param index: The index of the field entry to retrieve.
:type index: int
:param default_value: The value to return if the field is not found or is not of the correct type (``B_UINT64_TYPE``).
:type default_value: int
:returns: The 64-bit unsigned integer value stored in the message, or the 'default_value' if the field doesn't exist or its type is incorrect.
:rtype: int
)doc", py::arg("name"), py::arg("index"), py::arg("defaultValue"))
.def("GetFloat", py::overload_cast<const char *, float>(&BMessage::GetFloat, py::const_), R"doc(
Retrieves a float value from the field with the specified name.

This is a convenience method that simplifies retrieving a float from 
the message. If the field is not found, or if the field exists but is 
not of type ``B_FLOAT_TYPE``, the given default value is returned.

:param name: The name of the field to retrieve the float from.
:type name: str
:param default_value: The value to return if the field is not found or is not of the correct type (``B_FLOAT_TYPE``).
:type default_value: float
:returns: The float value stored in the message, or the 'default_value' if the field doesn't exist or its type is incorrect.
:rtype: float
)doc", py::arg("name"), py::arg("defaultValue"))
.def("GetFloat", py::overload_cast<const char *, int32, float>(&BMessage::GetFloat, py::const_), R"doc(
Retrieves a float value from the field with the specified name and index.

This is a convenience method that simplifies retrieving a float from 
the message. If the field is not found, or if the field exists but is 
not of type ``B_FLOAT_TYPE``, the given default value is returned.

:param name: The name of the field to retrieve the float from.
:type name: str
:param index: The index of the field entry to retrieve.
:type index: int
:param default_value: The value to return if the field is not found or is not of the correct type (``B_FLOAT_TYPE``).
:type default_value: float
:returns: The float value stored in the message, or the 'default_value' if the field doesn't exist or its type is incorrect.
:rtype: float
)doc", py::arg("name"), py::arg("index"), py::arg("defaultValue"))
.def("GetDouble", py::overload_cast<const char *, double>(&BMessage::GetDouble, py::const_), R"doc(
Retrieves a double value from the field with the specified name.

This is a convenience method that simplifies retrieving a double from 
the message. If the field is not found, or if the field exists but is 
not of type ``B_DOUBLE_TYPE``, the given default value is returned.

:param name: The name of the field to retrieve the double from.
:type name: str
:param default_value: The value to return if the field is not found or is not of the correct type (``B_DOUBLE_TYPE``).
:type default_value: double
:returns: The double value stored in the message, or the 'default_value' if the field doesn't exist or its type is incorrect.
:rtype: double
)doc", py::arg("name"), py::arg("defaultValue"))
.def("GetDouble", py::overload_cast<const char *, int32, double>(&BMessage::GetDouble, py::const_), R"doc(
Retrieves a double value from the field with the specified name and index.

This is a convenience method that simplifies retrieving a double from 
the message. If the field is not found, or if the field exists but is 
not of type ``B_DOUBLE_TYPE``, the given default value is returned.

:param name: The name of the field to retrieve the double from.
:type name: str
:param index: The index of the field entry to retrieve.
:type index: int
:param default_value: The value to return if the field is not found or is not of the correct type (``B_DOUBLE_TYPE``).
:type default_value: double
:returns: The double value stored in the message, or the 'default_value' if the field doesn't exist or its type is incorrect.
:rtype: double
)doc", py::arg("name"), py::arg("index"), py::arg("defaultValue"))
.def("GetColor", py::overload_cast<const char *, rgb_color>(&BMessage::GetColor, py::const_), R"doc(
Retrieves a ``rgb_color`` item from the field with the specified name.

This is a convenience method that simplifies retrieving a ``rgb_color`` from 
the message. If the field is not found, or if the field exists but is 
not of type ``B_RGB_COLOR_TYPE``, the given default value is returned.

:param name: The name of the field to retrieve the ``rgb_color`` from.
:type name: str
:param default_value: The value to return if the field is not found or is not of the correct type (``B_RGB_COLOR_TYPE``).
:type default_value: rgb_color
:returns: The ``rgb_color`` item stored in the message, or the 'default_value' if the field doesn't exist or its type is incorrect.
:rtype: rgb_color
)doc", py::arg("name"), py::arg("defaultValue"))
.def("GetColor", py::overload_cast<const char *, int32, rgb_color>(&BMessage::GetColor, py::const_), R"doc(
Retrieves a ``rgb_color`` item from the field with the specified name and index.

This is a convenience method that simplifies retrieving a ``rgb_color`` from 
the message. If the field is not found, or if the field exists but is 
not of type ``B_RGB_COLOR_TYPE``, the given default value is returned.

:param name: The name of the field to retrieve the ``rgb_color`` from.
:type name: str
:param index: The index of the field entry to retrieve.
:type index: int
:param default_value: The value to return if the field is not found or is not of the correct type (``B_RGB_COLOR_TYPE``).
:type default_value: rgb_color
:returns: The ``rgb_color`` item stored in the message, or the 'default_value' if the field doesn't exist or its type is incorrect.
:rtype: rgb_color
)doc", py::arg("name"), py::arg("index"), py::arg("defaultValue"))
// TODO Test if necessary GetPointer
.def("GetPointer", py::overload_cast<const char *, int32, const void *>(&BMessage::GetPointer, py::const_), "", py::arg("name"), py::arg("index"), py::arg("defaultValue")=NULL)
.def("GetPointer", py::overload_cast<const char *, const void *>(&BMessage::GetPointer, py::const_), "", py::arg("name"), py::arg("defaultValue")=NULL)

.def("GetString", py::overload_cast<const char *, const char *>(&BMessage::GetString, py::const_), R"doc(
Retrieves a string from the field with the specified name.

This is a convenience method that simplifies retrieving a string from 
the message. If the field is not found, or if the field exists but is 
not of type ``B_STRING_TYPE``, the given default value is returned.

:param name: The name of the field to retrieve the string from.
:type name: str
:param default_value: The value to return if the field is not found or is not of the correct type (``B_STRING_TYPE``).
:type default_value: string
:returns: The string stored in the message, or the 'default_value' if the field doesn't exist or its type is incorrect.
:rtype: string
)doc", py::arg("name"), py::arg("defaultValue")=NULL)
.def("GetString", py::overload_cast<const char *, int32, const char *>(&BMessage::GetString, py::const_), R"doc(
Retrieves a string from the field with the specified name and index.

This is a convenience method that simplifies retrieving a string from 
the message. If the field is not found, or if the field exists but is 
not of type ``B_STRING_TYPE``, the given default value is returned.

:param name: The name of the field to retrieve the string from.
:type name: str
:param index: The index of the field entry to retrieve.
:type index: int
:param default_value: The value to return if the field is not found or is not of the correct type (``B_STRING_TYPE``).
:type default_value: string
:returns: The string stored in the message, or the 'default_value' if the field doesn't exist or its type is incorrect.
:rtype: string
)doc", py::arg("name"), py::arg("index"), py::arg("defaultValue"))

// These two don't seem to be available on Haiku R1B4. Maybe they are, but just
// not in libbe.so? That would be strange... But it's also strange that the
// header files that come with R1B4 mention them.
#if (B_HAIKU_VERSION > B_HAIKU_VERSION_1_BETA_4)
.def("GetAlignment", py::overload_cast<const char *, int32, const BAlignment &>(&BMessage::GetAlignment, py::const_), R"doc(
Retrieves a ``BAlignment`` item from the field with the specified name and index.

This is a convenience method that simplifies retrieving a ``BAlignment`` from 
the message. If the field is not found, or if the field exists but is 
not of type ``B_ALIGNMENT_TYPE``, the given default value is returned.

:param name: The name of the field to retrieve the ``BAlignment`` from.
:type name: str
:param index: The index of the field entry to retrieve.
:type index: int
:param default_value: The value to return if the field is not found or is not of the correct type (``B_ALIGNMENT_TYPE``).
:type default_value: BAlignment
:returns: The ``BAlignment`` item stored in the message, or the 'default_value' if the field doesn't exist or its type is incorrect.
:rtype: BAlignment
)doc", py::arg("name"), py::arg("index"), py::arg("defaultValue"))
.def("GetAlignment", py::overload_cast<const char *, const BAlignment &>(&BMessage::GetAlignment, py::const_), R"doc(
Retrieves a ``BAlignment`` item from the field with the specified name.

This is a convenience method that simplifies retrieving a ``BAlignment`` from 
the message. If the field is not found, or if the field exists but is 
not of type ``B_ALIGNMENT_TYPE``, the given default value is returned.

:param name: The name of the field to retrieve the BAlignment from.
:type name: str
:param default_value: The value to return if the field is not found or is not of the correct type (``B_ALIGNMENT_TYPE``).
:type default_value: BAlignment
:returns: The ``BAlignment`` item stored in the message, or the 'default_value' if the field doesn't exist or its type is incorrect.
:rtype: BAlignment
)doc", py::arg("name"), py::arg("defaultValue"))
#endif

.def("GetRect", py::overload_cast<const char *, int32, const BRect &>(&BMessage::GetRect, py::const_), R"doc(
Retrieves a ``BRect`` item from the field with the specified name and index.

This is a convenience method that simplifies retrieving a ``BRect`` from 
the message. If the field is not found, or if the field exists but is 
not of type ``B_RECT_TYPE``, the given default value is returned.

:param name: The name of the field to retrieve the ``BRect`` from.
:type name: str
:param index: The index of the field entry to retrieve.
:type index: int
:param default_value: The value to return if the field is not found or is not of the correct type (``B_RECT_TYPE``).
:type default_value: BRect
:returns: The ``BRect`` item stored in the message, or the 'default_value' if the field doesn't exist or its type is incorrect.
:rtype: BRect
)doc", py::arg("name"), py::arg("index"), py::arg("defaultValue"))
.def("GetRect", py::overload_cast<const char *, const BRect &>(&BMessage::GetRect, py::const_), R"doc(
Retrieves a ``BRect`` item from the field with the specified name.

This is a convenience method that simplifies retrieving a ``BRect`` from 
the message. If the field is not found, or if the field exists but is 
not of type ``B_RECT_TYPE``, the given default value is returned.

:param name: The name of the field to retrieve the ``BRect`` from.
:type name: str
:param default_value: The value to return if the field is not found or is not of the correct type (``B_RECT_TYPE``).
:type default_value: BRect
:returns: The ``BRect`` item stored in the message, or the 'default_value' if the field doesn't exist or its type is incorrect.
:rtype: BRect
)doc", py::arg("name"), py::arg("defaultValue"))
.def("GetPoint", py::overload_cast<const char *, int32, const BPoint &>(&BMessage::GetPoint, py::const_), R"doc(
Retrieves a ``BPoint`` item from the field with the specified name and index.

This is a convenience method that simplifies retrieving a ``BPoint`` from 
the message. If the field is not found, or if the field exists but is 
not of type ``B_POINT_TYPE``, the given default value is returned.

:param name: The name of the field to retrieve the ``BPoint`` from.
:type name: str
:param index: The index of the field entry to retrieve.
:type index: int
:param default_value: The value to return if the field is not found or is not of the correct type (``B_POINT_TYPE``).
:type default_value: BPoint
:returns: The ``BPoint`` item stored in the message, or the 'default_value' if the field doesn't exist or its type is incorrect.
:rtype: BPoint
)doc", py::arg("name"), py::arg("index"), py::arg("defaultValue"))
.def("GetPoint", py::overload_cast<const char *, const BPoint &>(&BMessage::GetPoint, py::const_), R"doc(
Retrieves a ``BPoint`` item from the field with the specified name.

This is a convenience method that simplifies retrieving a ``BPoint`` from 
the message. If the field is not found, or if the field exists but is 
not of type ``B_POINT_TYPE``, the given default value is returned.

:param name: The name of the field to retrieve the ``BPoint`` from.
:type name: str
:param default_value: The value to return if the field is not found or is not of the correct type (``B_POINT_TYPE``).
:type default_value: BPoint
:returns: The ``BPoint`` item stored in the message, or the 'default_value' if the field doesn't exist or its type is incorrect.
:rtype: BPoint
)doc", py::arg("name"), py::arg("defaultValue"))
.def("GetSize", py::overload_cast<const char *, int32, const BSize &>(&BMessage::GetSize, py::const_), R"doc(
Retrieves a ``BSize`` item from the field with the specified name and index.

This is a convenience method that simplifies retrieving a ``BSize`` from 
the message. If the field is not found, or if the field exists but is 
not of type ``B_SIZE_TYPE``, the given default value is returned.

:param name: The name of the field to retrieve the ``BSize`` from.
:type name: str
:param index: The index of the field entry to retrieve.
:type index: int
:param default_value: The value to return if the field is not found or is not of the correct type (``B_SIZE_TYPE``).
:type default_value: BSize
:returns: The ``BSize`` item stored in the message, or the 'default_value' if the field doesn't exist or its type is incorrect.
:rtype: BSize
)doc", py::arg("name"), py::arg("index"), py::arg("defaultValue"))
.def("GetSize", py::overload_cast<const char *, const BSize &>(&BMessage::GetSize, py::const_), R"doc(
Retrieves a ``BSize`` item from the field with the specified name.

This is a convenience method that simplifies retrieving a ``BSize`` from 
the message. If the field is not found, or if the field exists but is 
not of type ``B_SIZE_TYPE``, the given default value is returned.

:param name: The name of the field to retrieve the ``BSize`` from.
:type name: str
:param default_value: The value to return if the field is not found or is not of the correct type (``B_SIZE_TYPE``).
:type default_value: BSize
:returns: The ``BSize`` item stored in the message, or the 'default_value' if the field doesn't exist or its type is incorrect.
:rtype: BSize
)doc", py::arg("name"), py::arg("defaultValue"))

.def("SetBool", &BMessage::SetBool, R"doc(
Adds a boolean value to the ``BMessage``, or replaces the first existing 
value if a field with the same name already exists.

The value is stored in the message as type ``B_BOOL_TYPE``.

:param name: The name of the field to to add or modify.
:type name: str
:param value: The boolean value to be stored in the message.
:type value: bool
:returns: ``B_OK`` on success, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("value"))
.def("SetInt8", &BMessage::SetInt8, R"doc(
Adds a 8-bit signed integer (int8) value to the ``BMessage``, or replaces 
the first existing value if a field with the same name already exists.

The value is stored in the message as type ``B_INT8_TYPE``.

.. note::
   While this method stores a 8-bit signed integer, 
   the Python parameter 'value' must be a standard Python 'int'. 
   Passing values outside int8 range may result in truncation 
   or unexpected behavior when interpreted by the underlying C++ API.

:param name: The name of the field to to add or modify.
:type name: str
:param value: The 8-bit signed integer (int8) value to be stored in the message.
:type value: int
:returns: ``B_OK`` on success, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("value"))
.def("SetUInt8", &BMessage::SetUInt8, R"doc(
Adds a 8-bit unsigned integer (uint8) value to the ``BMessage``, or replaces 
the first existing value if a field with the same name already exists.

The value is stored in the message as type ``B_UINT8_TYPE``.

.. note::
   While this method stores a 8-bit unsigned integer, 
   the Python parameter 'value' must be a standard Python 'int'. 
   Passing values outside uint8 range may result in truncation 
   or unexpected behavior when interpreted by the underlying C++ API.

:param name: The name of the field to to add or modify.
:type name: str
:param value: The 8-bit unsigned integer (uint8) value to be stored in the message.
:type value: int
:returns: ``B_OK`` on success, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("value"))
.def("SetInt16", &BMessage::SetInt16, R"doc(
Adds a 16-bit signed integer (int16) value to the ``BMessage``, or replaces 
the first existing value if a field with the same name already exists.

The value is stored in the message as type ``B_INT16_TYPE``.

.. note::
   While this method stores a 16-bit signed integer, 
   the Python parameter 'value' must be a standard Python 'int'. 
   Passing values outside int16 range may result in truncation 
   or unexpected behavior when interpreted by the underlying C++ API.

:param name: The name of the field to to add or modify.
:type name: str
:param value: The 16-bit signed integer (int16) value to be stored in the message.
:type value: int
:returns: ``B_OK`` on success, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("value"))
.def("SetUInt16", &BMessage::SetUInt16, R"doc(
Adds a 16-bit unsigned integer (uint16) value to the ``BMessage``, or replaces 
the first existing value if a field with the same name already exists.

The value is stored in the message as type ``B_UINT16_TYPE``.

.. note::
   While this method stores a 16-bit unsigned integer, 
   the Python parameter 'value' must be a standard Python 'int'. 
   Passing values outside uint16 range may result in truncation 
   or unexpected behavior when interpreted by the underlying C++ API.

:param name: The name of the field to to add or modify.
:type name: str
:param value: The 16-bit unsigned integer (uint16) value to be stored in the message.
:type value: int
:returns: ``B_OK`` on success, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("value"))
.def("SetInt32", &BMessage::SetInt32, R"doc(
Adds a 32-bit signed integer (int32) value to the ``BMessage``, or replaces 
the first existing value if a field with the same name already exists.

The value is stored in the message as type ``B_INT32_TYPE``.

.. note::
   While this method stores a 32-bit signed integer, 
   the Python parameter 'value' must be a standard Python 'int'. 
   Passing values outside int32 range may result in truncation 
   or unexpected behavior when interpreted by the underlying C++ API.

:param name: The name of the field to to add or modify.
:type name: str
:param value: The 32-bit signed integer (int32) value to be stored in the message.
:type value: int
:returns: ``B_OK`` on success, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("value"))
.def("SetUInt32", &BMessage::SetUInt32, R"doc(
Adds a 32-bit unsigned integer (uint32) value to the ``BMessage``, or replaces 
the first existing value if a field with the same name already exists.

The value is stored in the message as type ``B_UINT32_TYPE``.

.. note::
   While this method stores a 32-bit unsigned integer, 
   the Python parameter 'value' must be a standard Python 'int'. 
   Passing values outside uint32 range may result in truncation 
   or unexpected behavior when interpreted by the underlying C++ API.

:param name: The name of the field to to add or modify.
:type name: str
:param value: The 32-bit unsigned integer (uint32) value to be stored in the message.
:type value: int
:returns: ``B_OK`` on success, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("value"))
.def("SetInt64", &BMessage::SetInt64, R"doc(
Adds a 64-bit signed integer (int64) value to the ``BMessage``, or replaces 
the first existing value if a field with the same name already exists.

The value is stored in the message as type ``B_INT64_TYPE``.

.. note::
   While this method stores a 64-bit signed integer, 
   the Python parameter 'value' must be a standard Python 'int'. 
   Passing values outside int64 range may result in truncation 
   or unexpected behavior when interpreted by the underlying C++ API.

:param name: The name of the field to to add or modify.
:type name: str
:param value: The 64-bit signed integer (int64) value to be stored in the message.
:type value: int
:returns: ``B_OK`` on success, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("value"))
.def("SetUInt64", &BMessage::SetUInt64, R"doc(
Adds a 64-bit unsigned integer (uint64) value to the ``BMessage``, or replaces 
the first existing value if a field with the same name already exists.

The value is stored in the message as type ``B_UINT64_TYPE``.

.. note::
   While this method stores a 64-bit unsigned integer, 
   the Python parameter 'value' must be a standard Python 'int'. 
   Passing values outside uint64 range may result in truncation 
   or unexpected behavior when interpreted by the underlying C++ API.

:param name: The name of the field to to add or modify.
:type name: str
:param value: The 64-bit unsigned integer (uint64) value to be stored in the message.
:type value: int
:returns: ``B_OK`` on success, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("value"))

.def("SetColor", &BMessage::SetColor, R"doc(
Adds a ``rgb_color`` element to the ``BMessage``, or replaces the first existing 
element if a field with the same name already exists.

The value is stored in the message as type ``B_RGB_COLOR_TYPE``.

:param name: The name of the field to to add or modify.
:type name: str
:param value: The ``rgb_color`` item to be stored in the message.
:type value: rgb_color
:returns: ``B_OK`` on success, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("value"))
//TODO test if useful or comment out
.def("SetPointer", &BMessage::SetPointer, "", py::arg("name"), py::arg("value"))

.def("SetString", py::overload_cast<const char *, const char *>(&BMessage::SetString), R"doc(
Adds a string element to the ``BMessage``, or replaces the first existing 
element if a field with the same name already exists.

The value is stored in the message as type ``B_STRING_TYPE``.

.. note: 
    ``B_ASCII_TYPE`` is the C-style for char*, but it's
    deprecated, Haiku prefers using ``B_STRING_TYPE``.

:param name: The name of the field to to add or modify.
:type name: str
:param value: The string to be stored in the message.
:type value: str
:returns: ``B_OK`` on success, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("string"))
.def("SetString", py::overload_cast<const char *, const BString &>(&BMessage::SetString), R"doc(
Adds a ``BString`` element to the ``BMessage``, or replaces the first existing 
element if a field with the same name already exists.

The value is stored in the message as type ``B_STRING_TYPE``.

:param name: The name of the field to to add or modify.
:type name: str
:param bstring: The ``BString`` item to be stored in the message.
:type bstring: BString
:returns: ``B_OK`` on success, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("bstring"))
.def("SetFloat", &BMessage::SetFloat, R"doc(
Adds a float value to the ``BMessage``, or replaces the first existing 
element if a field with the same name already exists.

The value is stored in the message as type ``B_FLOAT_TYPE``.

:param name: The name of the field to to add or modify.
:type name: str
:param value: The float value to be stored in the message.
:type value: float
:returns: ``B_OK`` on success, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("value"))
.def("SetDouble", &BMessage::SetDouble, R"doc(
Adds a double value to the ``BMessage``, or replaces the first existing 
element if a field with the same name already exists.

The value is stored in the message as type ``B_DOUBLE_TYPE``.

:param name: The name of the field to to add or modify.
:type name: str
:param value: The double value to be stored in the message.
:type value: double
:returns: ``B_OK`` on success, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("value"))
#if (B_HAIKU_VERSION > B_HAIKU_VERSION_1_BETA_4) // see comment for GetAlignment
.def("SetAlignment", &BMessage::SetAlignment, R"doc(
Adds a ``BAlignment`` item to the ``BMessage``, or replaces the first existing 
element if a field with the same name already exists.

The value is stored in the message as type ``B_ALIGNMENT_TYPE``.

:param name: The name of the field to to add or modify.
:type name: str
:param value: The ``BAlignment`` item to be stored in the message.
:type value: BAlignment
:returns: ``B_OK`` on success, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("value"))
#endif
.def("SetPoint", &BMessage::SetPoint, R"doc(
Adds a ``BPoint`` item to the ``BMessage``, or replaces the first existing 
element if a field with the same name already exists.

The value is stored in the message as type ``B_POINT_TYPE``.

:param name: The name of the field to to add or modify.
:type name: str
:param value: The ``BPoint`` item to be stored in the message.
:type value: BPoint
:returns: ``B_OK`` on success, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("value"))
.def("SetRect", &BMessage::SetRect, R"doc(
Adds a ``BRect`` item to the ``BMessage``, or replaces the first existing 
element if a field with the same name already exists.

The value is stored in the message as type ``B_RECT_TYPE``.

:param name: The name of the field to to add or modify.
:type name: str
:param value: The ``BRect`` item to be stored in the message.
:type value: BRect
:returns: ``B_OK`` on success, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("value"))
.def("SetSize", &BMessage::SetSize, R"doc(
Adds a ``BSize`` item to the ``BMessage``, or replaces the first existing 
element if a field with the same name already exists.

The value is stored in the message as type ``B_SIZE_TYPE``.

:param name: The name of the field to to add or modify.
:type name: str
:param value: The ``BSize`` item to be stored in the message.
:type value: BSize
:returns: ``B_OK`` on success, or an error code otherwise.
:rtype: int
)doc", py::arg("name"), py::arg("value"))
//.def("SetData", &BMessage::SetData, "", py::arg("name"), py::arg("type"), py::arg("data"), py::arg("numBytes"), py::arg("fixedSize")=true, py::arg("count")=1)
.def("SetData",[](BMessage& self, const char* name, type_code type, py::buffer data, ssize_t numBytes, bool isFixedSize, int32 count) { 
	py::buffer_info info = data.request();
	const void* buffer = info.ptr;
	return self.SetData(name,type,buffer,numBytes,isFixedSize,count);
}, R"doc(

   Adds or replaces raw data in the message under a specific field 
   name and type code.

   This is the most flexible method for storing non-standard, raw, 
   or compound data structures within the ``BMessage``. The data must 
   be passed as a Python buffer object (bytes,bytearray etc.). If 
   the named field exists, the first entry (or the entry at 
   'count') will be replaced.

   :param name: The name of the field to add or modify.
   :type name: str
   :param type: The specific type code (e.g., ``B_RAW_TYPE``, ``B_RECT_TYPE``) that identifies the data format.
   :type type: int
   :param data: The raw data to be stored.
   :type data: py::buffer (e.g. bytes, bytearray, numpy.ndarray)
   :param numBytes: The exact number of bytes from the 'data' buffer to write into the message.
   :type numBytes: int
   :param fixedSize: If ``True`` (default), indicates that the type code implies a fixed-size data structure (e.g., ``BRect``, ``BPoint``). If ``False``, the data size is variable (e.g., ``B_RAW_TYPE``), see ``ReplaceData`` about this.
   :type fixedSize: bool, optional
   :param count: The index of the element to replace if the field holds multiple entries. Defaults to 1.
   :type count: int, optional
   :returns: ``B_OK`` (0) on success, or an error code otherwise.
   :rtype: int
)doc", py::arg("name"), py::arg("type"), py::arg("data"), py::arg("numBytes"), py::arg("fixedSize")=true, py::arg("count")=1)
.def("__repr__", [](const BMessage& msg) {
	std::string repr = "<BMessage what=" + std::to_string(msg.what);
	std::string fourcc = FourCC(msg.what);

	if (!fourcc.empty()) {
		repr += " " + fourcc;
	}

	repr += ", fields=" + std::to_string(msg.CountNames(B_ANY_TYPE)) + ">";
	return repr;
})
.def_readwrite("what", &BMessage::what, R"doc(

   The message command code, which identifies the overall purpose or meaning of the ``BMessage``.

   The 'what' code is a 32-bit integer (type_code) often represented by four ASCII characters (e.g., 'DATA'). It is the first thing checked when a message is received to determine how it should be handled.

   :type: int
)doc")

;


}
