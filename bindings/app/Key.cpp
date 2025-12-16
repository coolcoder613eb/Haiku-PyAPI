#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <app/Key.h>
#include <DataIO.h>
#include <Message.h>
#include <ObjectList.h>
#include <String.h>

namespace py = pybind11;

class PyBKey : public BKey{
	public:
        using BKey::BKey;
        PyBKey(const BKey& key)
          : BKey(const_cast<BKey&>(key)) {}
        BKeyType			Type() const override {
        	PYBIND11_OVERLOAD(BKeyType, BKey, Type);
        }
        status_t			Flatten(BMessage& message) const override {
        	PYBIND11_OVERLOAD(status_t, BKey, Flatten, message);
        }
        status_t			Unflatten(const BMessage& message) override {
        	PYBIND11_OVERLOAD(status_t, BKey, Unflatten, message);
        }
        void				PrintToStream() override {
        	PYBIND11_OVERLOAD(void, BKey, PrintToStream);
        }
};

class PyBPasswordKey : public BPasswordKey{
	public:
        using BPasswordKey::BPasswordKey;
        PyBPasswordKey(const BPasswordKey& key)
          : BPasswordKey(const_cast<BPasswordKey&>(key)) {}
        BKeyType			Type() const override {
        	PYBIND11_OVERLOAD(BKeyType, BPasswordKey, Type);
        }
        void				PrintToStream() override {
        	PYBIND11_OVERLOAD(void, BPasswordKey, PrintToStream);
        }
};

PYBIND11_MODULE(Key,m)
{
py::enum_<BKeyPurpose>(m, "BKeyPurpose", R"doc(
Constants for key purposes)doc")
.value("B_KEY_PURPOSE_ANY", BKeyPurpose::B_KEY_PURPOSE_ANY, R"doc(
Query the key store for keys with any purpose.

This constant does not represent a key purpose by itself, but rather is used 
in querying the key store where you do not know or care about the purpose of 
key you are looking for.
)doc")
.value("B_KEY_PURPOSE_GENERIC", BKeyPurpose::B_KEY_PURPOSE_GENERIC, R"doc(
Generic key purpose.

This type identifies keys that are not for a specific purpose.
)doc")
.value("B_KEY_PURPOSE_KEYRING", BKeyPurpose::B_KEY_PURPOSE_KEYRING, R"doc(
Keyring key purpose.

This is a key purpose that is internal to the keystore_server. It represents 
the internals of a keyring. You cannot directly access and manipulate keys 
with this purpose. Instead you can use the methods on BKeyStore to access 
keys within keyrings.
)doc")
.value("B_KEY_PURPOSE_WEB", BKeyPurpose::B_KEY_PURPOSE_WEB, R"doc(
Web key purpose.

This type refers to keys that are used on the web, such as username and 
passwords for HTTP authentication, as well as for stored usernames and 
passwords for form-based authentication.
)doc")
.value("B_KEY_PURPOSE_NETWORK", BKeyPurpose::B_KEY_PURPOSE_NETWORK, R"doc(
Network key purpose.

This type refers to keys that are used in the networking stack, such as 
WEP/WPA keys.
)doc")
.value("B_KEY_PURPOSE_VOLUME", BKeyPurpose::B_KEY_PURPOSE_VOLUME, R"doc(
Volume key purpose.

This type refers to keys that are used to lock volumes, like password for 
encryption.
)doc")
.export_values();

py::enum_<BKeyType>(m, "BKeyType", R"doc(
Constants for key types
)doc")
.value("B_KEY_TYPE_ANY", BKeyType::B_KEY_TYPE_ANY, R"doc(
Query the key store for keys of any type.

This constant does not represent a key type by itself, but rather is used 
in querying the key store where you do not know or care about the type of 
key you are looking for.
)doc")
.value("B_KEY_TYPE_GENERIC", BKeyType::B_KEY_TYPE_GENERIC, R"doc(
Generic key type.

This constant describes the type of key that does not have any particular 
content or format. They are represented by the ``BKey`` class.
)doc")
.value("B_KEY_TYPE_PASSWORD", BKeyType::B_KEY_TYPE_PASSWORD, R"doc(
The key is a password.

This key type is represented by the ``BPasswordKey`` class.
)doc")
.value("B_KEY_TYPE_CERTIFICATE", BKeyType::B_KEY_TYPE_CERTIFICATE, R"doc(
The key is a certificate. Not in use.

This key type is for future expansion. It is currently not in use.
)doc")
.export_values();

py::class_<BKey,PyBKey>(m, "BKey",R"doc(
Class that represents a generic key for or from the Haiku key store.

- A key has the following properties:
- A key type of BKeyType, which identifies the type. For a generic key (like 
  this key), it will be set to ``BKeyType.B_KEY_TYPE_GENERIC``
- A key purpose of BKeyPurpose, which identifies the purpose of the key.
- A primary identifier that identifies a specific key. (e.g. for WPA passwords, 
  this is set to the network name). This should be a valid UTF-8 string.
- A secondary identifier that can be used as additional metadata.
- The data, the actual value of the key (such as a password or a certificate). 
  This should be a valid UTF-8 string.
- Not in use: the owner identifies who created and/or owns the key. This feature 
  is not yet enabled. It will always be set to an empty string.
- Not in use: the creation time will indicate when a key was stored in the 
  central database. This feature is not yet enabled, and the value will always be 0.
)doc")
.def(py::init(), R"doc(
Constructor for an empty password key.

An empty key has no data associated with it, other than that it has a generic purpose and a password key type.
)doc")
//.def(py::init<BKeyPurpose, const char *, const char *, unsigned char*, size_t>(), "", py::arg("purpose"), py::arg("identifier"), py::arg("secondaryIdentifier")=NULL, py::arg("data")=NULL, py::arg("length")=0)
.def(py::init([](BKeyPurpose purpose,const char * identifier,const char * secondaryIdentifier,py::object data) {
	const uint8* data_ptr = NULL;
	size_t data_length = 0;
	if (!data.is_none()) {
		py::buffer buf = data.cast<py::buffer>();
		py::buffer_info info = buf.request();
		data_length = (size_t)(info.size * info.itemsize);
		data_ptr = (const uint8*)info.ptr;
		if (data_ptr == nullptr && data_length > 0) {
			throw std::runtime_error("Data buffer is invalid or null pointer received.");
		}
	}
	return new BKey(purpose, identifier, secondaryIdentifier, data_ptr, data_length);
}),R"doc(
Constructor for a generic key with the provided data.

:param purpose: The purpose of this key
:type purpose: BKeyPurpose (int)
:param identifier: A unique identifier for this key
:type identifier: str
:param secondaryIdentifier: An (optional) secondary identifier for this key, default is ``None``
:type secondaryIdentifier: str or ``None``, optional
:param data: An optional Buffer that contains the value of the key, such as the password or the certificate data, default is ``None``
:type data: py::buffer (e.g. bytes, bytearray etc.) or ``None``, optional
)doc", py::arg("purpose"), py::arg("identifier"), py::arg("secondaryIdentifier")=NULL, py::arg("data")=NULL)
.def(py::init<BKey&>(), R"doc(
Copy constructor that makes a copy of an other BKey.

:param other: the BKey to copy into this one.
:type other: BKey
)doc", py::arg("other"))
.def("Type", &BKey::Type, R"doc(
Returns the type of key.

For a generic BKey, this will always be ``BKeyType.B_KEY_TYPE_GENERIC``

:return: The type of the key
:rtype: BKeyType
)doc")
.def("Unset", &BKey::Unset, R"doc(
Reset the values of the key.

All properties of the key will be reset, except for the identifying owner.
)doc")
//.def("SetTo", &BKey::SetTo, "", py::arg("purpose"), py::arg("identifier"), py::arg("secondaryIdentifier")=NULL, py::arg("data")=NULL, py::arg("length")=0)
.def("SetTo", [](BKey& self,BKeyPurpose purpose,const char * identifier,const char * secondaryIdentifier,py::object data) {
	const uint8* data_ptr = NULL;
	size_t data_length = 0;
	if (!data.is_none()) {
		py::buffer buf = data.cast<py::buffer>();
		py::buffer_info info = buf.request();
		data_length = (size_t)(info.size * info.itemsize);
		data_ptr = (const uint8*)info.ptr;
		if (data_ptr == nullptr && data_length > 0) {
			throw std::runtime_error("Data buffer is invalid or null pointer received.");
		}
	}
	return self.SetTo(purpose, identifier, secondaryIdentifier, data_ptr, data_length);
}, R"doc(
Set the key to the specified values.

All properties of the key will be set to the parameters. If the key had a 
creation time set, it will be cleared. If there was an owner set, this piece 
of information will not be cleared.

:param purpose:The purpose of this key
:type purpose: BKeyPurpose (int)
:param identifier: A unique identifier for this key
:type identifier: str
:param secondaryIdentifier: An (optional) secondary identifier for this key, default is ``None``
:type secondaryIdentifier: str or ``None``, optional
:param data: An optional Buffer that contains the value of the key, such as the password or the certificate data, default is ``None``
:type data: py::buffer (e.g. bytes, bytearray etc.) or ``None``, optional
:return: ``B_OK`` if the changes were successful, ``B_NO_MEMORY`` in case it fails to allocate memory.
:rtype: int
)doc", py::arg("purpose"), py::arg("identifier"), py::arg("secondaryIdentifier")=NULL, py::arg("data")=NULL)
.def("SetPurpose", &BKey::SetPurpose, R"doc(
Set the purpose of the key.

:param purpose: The new purpose of the key.
:type purpose: BKeyPurpose (int)
)doc", py::arg("purpose"))
.def("Purpose", &BKey::Purpose, R"doc(
Get the purpose of the key.

:return: The actual purpose.
:rtype: BKeyPurpose (int)
)doc")
.def("SetIdentifier", &BKey::SetIdentifier, R"doc(
Set the identifier of the key.

:param identifier: The new identifier, a valid utf-8 string.
:type identifier: str
)doc", py::arg("identifier"))
.def("Identifier", &BKey::Identifier, R"doc(
Get the identifier of the key.

:return: The actual identifier.
:rtype: str
)doc")
.def("SetSecondaryIdentifier", &BKey::SetSecondaryIdentifier, R"doc(
Set the secondary identifier of the key.
:param identifier: The new secondary identifier, a valid utf-8 string
:type identifier: str
)doc", py::arg("identifier"))
.def("SecondaryIdentifier", &BKey::SecondaryIdentifier, R"doc(
Get the secondary identifier of the key.

:return: The actual secondary identifier.
:rtype: str
)doc")
//.def("SetData", &BKey::SetData, "", py::arg("data"), py::arg("length"))
.def("SetData", [](BKey& self,py::object data){
	const uint8* data_ptr = NULL;
	size_t data_length = 0;
	if (!data.is_none()) {
		py::buffer buf = data.cast<py::buffer>();
		py::buffer_info info = buf.request();
		data_length = (size_t)(info.size * info.itemsize);
		data_ptr = (const uint8*)info.ptr;
		if (data_ptr == nullptr && data_length > 0) {
			throw std::runtime_error("Data buffer is invalid or null pointer received.");
		}
	}
	return self.SetData(data_ptr, data_length);
}, R"doc(
Set the data for the key.

:param data: A buffer that contains the data of the key.
:type data: py::buffer (e.g. bytes, bytearray, etc.)
:return: ``B_OK` if the key data was updated, ``B_NO_MEMORY`` if it fails to allocate memory.
:rtype: int
)doc", py::arg("data"))
.def("DataLength", &BKey::DataLength, R"doc(
Get the size of the key in bytes.

:return: The size of the key.
:rtype: int
)doc")
//.def("Data", &BKey::Data, "")
.def("Data", [](BKey& self){
	size_t dataLength = self.DataLength();
	const uint8* dataPtr = self.Data();
	if (dataLength == 0 || dataPtr == nullptr) {
		return py::bytes("");
	}
	return py::bytes((const char*)dataPtr, dataLength);
}, R"doc(
Return the data of the key.

:return: Return the data, or ``""`` if data is ``null`` or length ``0``
:rtype: py::bytes (bytes)
)doc")
//.def("GetData", &BKey::GetData, "", py::arg("buffer"), py::arg("bufferSize"))
.def("GetData", [](BKey& self,size_t bufferSize){
	if (bufferSize == 0) {
        return py::make_tuple(B_OK, py::bytes(""));
    }
	std::vector<uint8_t> buffer(bufferSize);
	status_t result = self.GetData(buffer.data(), bufferSize);
	if (result != B_OK) {
        return py::make_tuple(result, py::bytes(""));
    }
    py::bytes data_bytes((const char*)buffer.data(), bufferSize);
	return py::make_tuple(result, data_bytes);
}, R"doc(
Return the data of the key. The User make sure the size of 
the buffer is the actual size of the key's data. If the provided 
buffer is smaller, only the bufferSize will be copied. If the 
buffer is larger, the key is copied, but the rest of the 
buffer will not be touched.

:param bufferSize: The size of the buffer to allocate and fill.
:type bufferSize: int
:return: A tuple containing the status (int) and the data (bytes).
:rtype: tuple ``(int, bytes)``
)doc", py::arg("bufferSize"))
.def("Owner", &BKey::Owner, R"doc(
Get the owner of the key.

:return: The owner.
:rtype: str
)doc")
.def("CreationTime", &BKey::CreationTime, R"doc(
Get the creation time of the key.

:return: The creation time.
:rtype: int
)doc")
.def("Flatten", [](BKey& self) {
    BMessage  message;
    status_t r = self.Flatten(message);
    return std::make_tuple(r,message);
}
, R"doc(
Flatten the key into a message.

:return: the status of the call along with the message containing the flattened key.
:rtype: A tuple ``(status, message)``:
        - ``status`` (int): ``B_OK`` if success, or a Haiku error code.
        - ``message`` (BMessage): The message containing the flattened key.
)doc")
.def("Unflatten", &BKey::Unflatten, R"doc(
Unflatten the key from a message.

:param message: The message containing the key.
:type message: BMessage
)doc", py::arg("message"))
//.def("operator=", &BKey::operator=, "", py::arg("other"))
.def("__eq__", &BKey::operator==, "", py::arg("other"))
.def("__ne__", &BKey::operator!=, "", py::arg("other"))
.def("PrintToStream", &BKey::PrintToStream, R"doc(
Dump the contents of the key to standard output.

All properties, except for the actual data of the key, 
will be printed to stdout.
)doc")
;

py::class_<BPasswordKey, PyBPasswordKey, BKey>(m, "BPasswordKey",R"doc(
Class that represents a password for or from the Haiku key store.

This is a specialized version of the BKey class, which represents 
a key of the ``BKeyType.B_KEY_TYPE_PASSWORD``.
)doc")
.def(py::init(), R"doc(
Constructor for an empty password key.

An empty key has no data associated with it, other than that it 
has a generic purpose and a password key type.
)doc")
.def(py::init<const char *, BKeyPurpose, const char *, const char *>(), R"doc(
Constructor for a password key with the provided data.

:param password: A null-terminated string that contains the password.
:type password: str
:param purpose: The purpose of this key.
:type purpose: BKeyPurpose (int)
:param identifier: A unique identifier for this key.
:type identifier: str
:param secondaryIdentifier: An (optional) secondary identifier for this key.
:type secondaryIdentifier: str, optional
)doc", py::arg("password"), py::arg("purpose"), py::arg("identifier"), py::arg("secondaryIdentifier")=NULL)
//.def(py::init(), "")
.def(py::init<BPasswordKey&>(), R"doc(
Copy constructor that makes a copy of an other BPasswordKey.

:param other: the BPasswordKey to copy into this one.
:type other: BPasswordKey
)doc", py::arg("other"))
.def("Type", &BPasswordKey::Type, R"doc(
Return the ``BKeyType.B_KEY_TYPE_PASSWORD``.

:return: ``B_KEY_TYPE_PASSWORD``, the specific BKeyType of this class.
:rtype: BKeyType (int)
)doc")
.def("SetTo", &BPasswordKey::SetTo, R"doc(
Set the key to specific values.

If the key had a creation time set, it will be cleared. If there was 
an owner set, this piece of information will not be cleared.

:param password: A null-terminated string that contains the password.
:type password: str
:param purpose: The purpose of this key.
:type purpose: BKeyPurpose (int)
:param identifier: A unique identifier for this key.
:type identifier: str
:param secondaryIdentifier: An (optional) secondary identifier for this key.
:type secondaryIdentifier: str, optional
:return: ``B_OK`` if the changes were successful, ``B_NO_MEMORY`` if it fails to allocate memory.
:rtype: int
)doc", py::arg("password"), py::arg("purpose"), py::arg("identifier"), py::arg("secondaryIdentifier")=NULL)
.def("SetPassword", &BPasswordKey::SetPassword, R"doc(
Set the password for this key.

:param password: A null-terminated string that contains the password.
:type password: str
:return: ``B_OK`` if successful, or a Haiku error code.
:rtype: int
)doc", py::arg("password"))
.def("Password", &BPasswordKey::Password, R"doc(
Get the password for the key.

:return: the password for the key.
:rtype: str
)doc")
.def("PrintToStream", &BPasswordKey::PrintToStream, R"doc(
Dump the contents of the key to standard output.

This is a debug function that helps you read the contents of the key. 
All properties, including the actual **password**, will be printed to stdout.
)doc")
;


}
