#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <app/KeyStore.h>
#include <Key.h>

namespace py = pybind11;


PYBIND11_MODULE(KeyStore,m)
{
py::class_<BKeyStore>(m, "BKeyStore",R"doc(
The BKeyStore lets you query, retrieve and store keys in the 
system's key store.

Instances of this object give you an easy API to interact with 
the system's keystore_server. This is the central service that 
manages storing and retrieving keys, as well as managing the 
authorizations that a user grants to individual applications.

It is important to note that all calls on this object operate 
synchronously. This means that it should not be used during the 
event loop of a visible BWindow, as this may cause drawing and 
interaction issues.

All operations are performed in the context of a keyring. All 
systems have at least the Master keyring. Many of the methods 
take the name of the keyring as its first argument. Most of the 
methods in this class have an overloaded variant that operate 
on the Master keyring. If you want to access this keyring 
through the normal methods, pass an empty string as the 
identifier to the method.
)doc")
.def(py::init(), R"doc(
Create a new BKeyStore object that you can use to query, 
retrieve and store keys in the system's key store.

This is a cheap object to make, as it has no data associated 
with it. The recommended use is to create an instance on the 
stack whenever you want to interact with the API.
)doc")
.def("GetKey", [](BKeyStore& self,BKeyType type,const char * identifier) {
    BKey* key = new BKey();
    status_t r = self.GetKey(type, identifier, *key);
    return std::make_tuple(r,key);
}, R"doc(
Query the Master keyring for a specific key.

This is a convenience method that works on the Master keyring, 
and assumes the key must have an empty secondaryIdentifier.

:param type: The type of key to match.
:type type: BKeyType (int)
:param identifier: The string with the primary identifier of the key that you are looking for.
:type identifier: str
:return: A tuple ``(status,key)``:

         - ``status`` (int) : one of these:

                              - ``B_OK`` in case the key was found and stored in key.
                              - ``B_BAD_VALUE`` in case the keyring does not exist.
                              - ``B_NOT_ALLOWED`` in case the user did not grant you access right to this keyring.
                              - ``B_ENTRY_NOT_FOUND`` in case there is no key that matches the given identifier(s).
                              - Any other error that indicates that there was a problem communicating with the keystore_server.

         - ``key`` (BKey) the key retrieved. 

:rtype: tuple (int,BKey)
)doc", py::arg("type"), py::arg("identifier"))
.def("GetKey", [](BKeyStore& self,BKeyType type,const char * identifier,const char * secondaryIdentifier) {
    BKey* key = new BKey();
    status_t r = self.GetKey(type, identifier, secondaryIdentifier, *key);
    return std::make_tuple(r,key);
}, R"doc(
Query the Master keyring for for specific key.

This is a convenience method that calls
``GetKey(const char* keyring, BKeyType type, const char* identifier, const char* secondaryIdentifier, bool secondaryIdentifierOptional, BKey& key)``.

It works on the Master keyring, it sets secondaryIdentifierOptional 
to ``False``, meaning it both identifiers are required to match.

:param type: The type of key to match.
:type type: BKeyType (int)
:param identifier: The string with the primary identifier of the key that you are looking for.
:type identifier: str
:param secondaryIdentifier: The string with the secondary identifier of the key that you are looking for.
:type secondaryIdentifier: str
:return: A tuple ``(status,key)``

         - ``status`` (int) : one of these:

                              - ``B_OK`` in case the key was found and stored in key.
                              - ``B_BAD_VALUE`` in case the keyring does not exist.
                              - ``B_NOT_ALLOWED`` in case the user did not grant you access right to this keyring.
                              - ``B_ENTRY_NOT_FOUND`` in case there is no key that matches the given identifier(s).
                              - Any other error that indicates that there was a problem communicating with the keystore_server.

         - ``key`` (BKey) the key retrieved.

:rtype: tuple (int,BKey)
)doc", py::arg("type"), py::arg("identifier"), py::arg("secondaryIdentifier"))
.def("GetKey", [](BKeyStore& self,BKeyType type,const char * identifier,const char * secondaryIdentifier,bool secondaryIdentifierOptional) {
    BKey* key = new BKey();
    status_t r = self.GetKey(type, identifier, secondaryIdentifier, secondaryIdentifierOptional, *key);
    return std::make_tuple(r,key);
}, R"doc(
Query the Master keyring for for specific key.

This is a convenience method that calls 
``GetKey(const char* keyring, BKeyType type, const char* identifier, const char* secondaryIdentifier, bool secondaryIdentifierOptional, BKey& key)``.

It works on the Master keyring.

:param type: The type of key to match.
:type type: BKeyType (int)
:param identifier: The string with the primary identifier of the key that you are looking for.
:type identifier: str
:param secondaryIdentifier: The string with the secondary identifier of the key that you are looking for.
:type secondaryIdentifier: str
:param secondaryIdentifierOptional: Indicates if the secondary identifier has to match. With ``True`` a result is returned even if the secondaryIdentifier does not match.
:type secondaryIdentifierOptional: bool
:return: A tuple ``(status,key)``

         - ``status`` (int) : one of these:

                              - ``B_OK`` in case the key was found and stored in key.
                              - ``B_BAD_VALUE`` in case the keyring does not exist.
                              - ``B_NOT_ALLOWED`` in case the user did not grant you access right to this keyring.
                              - ``B_ENTRY_NOT_FOUND`` in case there is no key that matches the given identifier(s).
                              - Any other error that indicates that there was a problem communicating with the keystore_server.

         - ``key`` (BKey) the key retrieved.

:rtype: tuple (int,BKey)
)doc", py::arg("type"), py::arg("identifier"), py::arg("secondaryIdentifier"), py::arg("secondaryIdentifierOptional"))
.def("GetKey", [](BKeyStore& self,const char * keyring,BKeyType type,const char * identifier) {
    BKey* key = new BKey();
    status_t r = self.GetKey(keyring, type, identifier, *key);
    return std::make_tuple(r,key);
}, R"doc(
Query a certain keyring for a specific key.

This is a convenience method that calls 
``GetKey(const char* keyring, BKeyType type, const char* identifier, const char* secondaryIdentifier, bool secondaryIdentifierOptional, BKey& key)``.
 
and assumes the key must have an empty secondaryIdentifier.

:param keyring: A string that identifies the keyring get the key from.
:type keyring: str
:param type: The type of key to match.
:type type: BKeyType (int)
:param identifier: The string with the primary identifier of the key that you are looking for.
:type identifier: str
:return: A tuple ``(status,key)``

         - ``status`` (int) : one of these:

                              - ``B_OK`` in case the key was found and stored in key.
                              - ``B_BAD_VALUE`` in case the keyring does not exist.
                              - ``B_NOT_ALLOWED`` in case the user did not grant you access right to this keyring.
                              - ``B_ENTRY_NOT_FOUND`` in case there is no key that matches the given identifier(s).
                              - Any other error that indicates that there was a problem communicating with the keystore_server.

         - ``key`` (BKey) the key retrieved.

:rtype: tuple (int,BKey)
)doc", py::arg("keyring"), py::arg("type"), py::arg("identifier"))
.def("GetKey", [](BKeyStore& self,const char * keyring,BKeyType type,const char * identifier,const char * secondaryIdentifier) {
    BKey* key = new BKey();
    status_t r = self.GetKey(keyring, type, identifier, secondaryIdentifier, *key);
    return std::make_tuple(r,key);
}, R"doc(
Query a certain keyring for for specific key.
Both identifiers are required to match.

:param keyring: A string that identifies the keyring get the key from.
:type keyring: str
:param type: The type of key to match.
:type type: BKeyType (int)
:param identifier: The string with the primary identifier of the key that you are looking for.
:type identifier: str
:param secondaryIdentifier: The string with the secondary identifier of the key that you are looking for.
:type identifier: str
:return: A tuple ``(status,key)``

         - ``status`` (int) : one of these:

                              - ``B_OK`` in case the key was found and stored in key.
                              - ``B_BAD_VALUE`` in case the keyring does not exist.
                              - ``B_NOT_ALLOWED`` in case the user did not grant you access right to this keyring.
                              - ``B_ENTRY_NOT_FOUND`` in case there is no key that matches the given identifier(s).
                              - Any other error that indicates that there was a problem communicating with the keystore_server.

         - ``key`` (BKey) the key retrieved.

)doc", py::arg("keyring"), py::arg("type"), py::arg("identifier"), py::arg("secondaryIdentifier"))
.def("GetKey", [](BKeyStore& self,const char * keyring,BKeyType type,const char * identifier,const char * secondaryIdentifier,bool secondaryIdentifierOptional) {
    BKey* key = new BKey();
    status_t r = self.GetKey(keyring, type, identifier, secondaryIdentifier, secondaryIdentifierOptional, *key);
    return std::make_tuple(r,key);
}, R"doc(
Query a certain keyring for for specific key.

:param keyring: A string that identifies the keyring get the key from.
:type keyring: str
:param type: The type of key to match.
:type type: BKeyType (int)
:param identifier: The string with the primary identifier of the key that you are looking for.
:type identifier: str
:param secondaryIdentifier: The string with the secondary identifier of the key that you are looking for.
:type identifier: str
:param secondaryIdentifierOptional: Indicates if the secondary identifier has to match. With ``True`` a result is returned even if the secondaryIdentifier does not match.
:type secondaryIdentifierOptional: bool
:return: A tuple ``(status,key)``

         - ``status`` (int) : one of these:

                              - ``B_OK`` in case the key was found and stored in key.
                              - ``B_BAD_VALUE`` in case the keyring does not exist.
                              - ``B_NOT_ALLOWED`` in case the user did not grant you access right to this keyring.
                              - ``B_ENTRY_NOT_FOUND`` in case there is no key that matches the given identifier(s).
                              - Any other error that indicates that there was a problem communicating with the keystore_server.

         - ``key`` (BKey) the key retrieved.

)doc", py::arg("keyring"), py::arg("type"), py::arg("identifier"), py::arg("secondaryIdentifier"), py::arg("secondaryIdentifierOptional"))
.def("AddKey", py::overload_cast<const BKey &>(&BKeyStore::AddKey), R"doc(
Add a key to the Master keyring.

This is a convenience method that calls ``AddKey(const char *, const BKey&)`` 
for the Master keyring.

:param key: The key you want to add.
:type key: BKey
:return: one of these:

         - ``B_OK`` if success
         - ``B_BAD_VALUE`` if keyring doesn't exist
         - ``B_NOT_ALLOWED`` if the user did not grant you access right to this keyring
         - ``B_NAME_IN_USE`` if there already is another key with the same primary and secondary identifiers
         - Any other error that indicates that there was a problem communicating with the keystore_server.

:rtype: int
)doc", py::arg("key"))
.def("AddKey", py::overload_cast<const char *, const BKey &>(&BKeyStore::AddKey), R"doc(
Add a key to a keyring.
This method will send the key to the keystore_server and request it to be stored in the database.
A key needs to have a unique primary and secondary identifier within the Master keyring.

:param keyring: A string that identifies the keyring you want to add the key to.
:type keyring: str
:param key: The key you want to add.
:type key: BKey
:return: one of these:

         - ``B_OK`` if success
         - ``B_BAD_VALUE`` if keyring doesn't exist
         - ``B_NOT_ALLOWED`` if the user did not grant you access right to this keyring
         - ``B_NAME_IN_USE`` if there already is another key with the same primary and secondary identifiers
         - Any other error that indicates that there was a problem communicating with the keystore_server.

:rtype: int
)doc", py::arg("keyring"), py::arg("key"))
.def("RemoveKey", py::overload_cast<const BKey &>(&BKeyStore::RemoveKey), R"doc(
Remove a key from the Master keyring.

:param key: The key you want to remove.
:type key: BKey
:return: one of these:

         - ``B_OK`` in case the key was succesfully removed.
         - ``B_BAD_VALUE`` in case the keyring does not exist.
         - ``B_NOT_ALLOWED`` in case the user did not grant you access right to this keyring.
         - ``B_ENTRY_NOT_FOUND`` in case there is no key that matches the given identifier(s).
         - Any other error that indicates that there was a problem communicating with the keystore_server.

:rtype: int
)doc", py::arg("key"))
.def("RemoveKey", py::overload_cast<const char *, const BKey &>(&BKeyStore::RemoveKey), R"doc(
This method will remove a key from a keyring. The key needs to 
match exactly with the key that is in the database of keystore_server. 
The easiest way to guarantee this, is to use the exact key you find 
using GetKey() without making any alterations.

:param keyring: A string that identifies the keyring you want to remove the key from.
:type keyring: str
:param key: The key you want to remove.
:type key: BKey
:return: one of these:

         - ``B_OK`` in case the key was succesfully removed.
         - ``B_BAD_VALUE`` in case the keyring does not exist.
         - ``B_NOT_ALLOWED`` in case the user did not grant you access right to this keyring.
         - ``B_ENTRY_NOT_FOUND`` in case there is no key that matches the given identifier(s).
         - Any other error that indicates that there was a problem communicating with the keystore_server.

:rtype: int
)doc", py::arg("keyring"), py::arg("key"))
/*  TODO documentation, waiting for cookie details from Master developers */
.def("GetNextKey", [](BKeyStore& self,uint32 cookie) {
    BKey* key = new BKey(); 
    status_t r = self.GetNextKey(cookie, *key);
    return std::make_tuple(r, key, cookie);
}, "", py::arg("cookie"))
.def("GetNextKey", [](BKeyStore& self,BKeyType type,BKeyPurpose purpose,uint32 cookie) {
	BKey* key = new BKey();
	status_t r = self.GetNextKey(type, purpose, cookie, *key);
	return std::make_tuple(r, key, cookie);
}
, "", py::arg("type"), py::arg("purpose"), py::arg("cookie"))
.def("GetNextKey", [](BKeyStore& self,const char * keyring,uint32 cookie) {
    BKey* key = new BKey();
    status_t r = self.GetNextKey(keyring, cookie, *key);
    return std::make_tuple(r,key,cookie);
}
, "", py::arg("keyring"), py::arg("cookie"))
.def("GetNextKey", [](BKeyStore& self,const char * keyring,BKeyType type,BKeyPurpose purpose,uint32 cookie) {
    BKey* key = new BKey();
    status_t r = self.GetNextKey(keyring, type, purpose, cookie, *key);
    return std::make_tuple(r,key,cookie);
}
, "", py::arg("keyring"), py::arg("type"), py::arg("purpose"), py::arg("cookie"))
/* ********************* 'til here ************************ */
.def("AddKeyring", &BKeyStore::AddKeyring, R"doc(
Create a new keyring.

:param keyring: An UTF-8 string that identifies the keyring you want to create.
:type keyring: str
:return: one of these:

         - ``B_OK`` if the keyring was succesfully added.
         - ``B_NAME_IN_USE`` if the keyring already exists.
         - Any other error in case there was an unknown error in the keystore_server, or while communicating to it.

:rtype: int
)doc", py::arg("keyring"))
.def("RemoveKeyring", &BKeyStore::RemoveKeyring, R"doc(
Remove a keyring.

:param keyring: An UTF-8 string that identifies the keyring you want to remove.
:type keyring: str
:return: one of these:

         - ``B_OK`` if the keyring was sucessfully removed.
         - ``B_ENTRY_NOT_FOUND`` if the keyring does not exist.
         - ``B_NOT_ALLOWED`` when you try to remove the Master keyring.
         - Any other error in case there was an unknown error in the keystore_server, or while communicating to it.

:rtype: int
)doc", py::arg("keyring"))
/* ********** waiting for cookie details from Master developers */
.def("GetNextKeyring", [](BKeyStore& self,uint32 cookie) {
    //BString  keyring;
    BString*  keyring = new BString();
    status_t r = self.GetNextKeyring(cookie, *keyring);
    return std::make_tuple(r,keyring,cookie);
}
, "", py::arg("cookie"))
/* ******************* 'til here ***************** */
.def("SetUnlockKey", &BKeyStore::SetUnlockKey, R"doc(
While the Haiku Book marks this function as "Not implemented", 
looking at the Haiku's source code, the current client-side API 
flattens the BKey into a BMessage with the ``KEY_STORE_SET_UNLOCK_KEY`` 
command code, includes the target keyring name, and sends it 
to the keystore_server.

However, as of hrev59xxx, the server-side implementation is incomplete. 
as the actual encryption logic in Keyring::_EncryptToFlatBuffer() 
is currently a placeholder (TODO).

In short: the function correctly transmits the new key to the server, 
but the server does not yet use it to encrypt the stored data.

:param keyring: The name of the keyring whose unlock key is to be updated
:type keyring: str
:param key: The key that will unlock the keyring.
:type key: BKey
:return: ``B_OK`` if success, otherwise ``B_ERROR`` or a Haiku error code.
:rtype: int
)doc", py::arg("keyring"), py::arg("key"))
.def("RemoveUnlockKey", &BKeyStore::RemoveUnlockKey, R"doc(
While the Haiku Book marks this function as "Not implemented", 
looking at the Haiku's source code, the current client-side API 
clears the unlock key.
:param keyring: the name of the keyring whose unlock key is to be cleared
:type keyring: str
:return: ``B_OK`` if success, otherwise ``B_ERROR`` or a Haiku error code.
:rtype: int
)doc", py::arg("keyring"))
.def("SetMasterUnlockKey", &BKeyStore::SetMasterUnlockKey, R"doc(
A convenience method that calls SetUnlockKey for master keyring.
Not implemented on server-side, look at py::meth`BKeyStore.SetUnlockKey`.

:param key: The key that will unlock the master keyring.
:type key: BKey
:return: ``B_OK`` if success, otherwise ``B_ERROR`` or a Haiku error code.
:rtype: int
)doc", py::arg("key"))
.def("RemoveMasterUnlockKey", &BKeyStore::RemoveMasterUnlockKey, R"doc(
A convenience method that calls RemoveUnlockKey for master keyring.
Marked as "Not implemented" in the Haiku Book.

:return: ``B_OK`` if success, otherwise ``B_ERROR`` or a Haiku error code.
:rtype: int
)doc")
.def("AddKeyringToMaster", &BKeyStore::AddKeyringToMaster, R"doc(
Not implemented.
This feature is not available in the current release of Haiku.
)doc", py::arg("keyring"))
.def("RemoveKeyringFromMaster", &BKeyStore::RemoveKeyringFromMaster, R"doc(
Not implemented.
This feature is not available in the current release of Haiku.
)doc", py::arg("keyring"))
/* ********** waiting for cookie details from Master developers */
.def("GetNextMasterKeyring", [](BKeyStore& self,uint32 cookie) {
    BString*  keyring = new BString();
    status_t r = self.GetNextMasterKeyring(cookie, *keyring);
    return std::make_tuple(r,keyring,cookie);
}
, "", py::arg("cookie"))
/* ******************* 'til here ***************** */
.def("IsKeyringUnlocked", &BKeyStore::IsKeyringUnlocked, R"doc(
Not implemented.
This feature is not available in the current release of Haiku.
)doc", py::arg("keyring"))
.def("LockKeyring", &BKeyStore::LockKeyring, R"doc(
Not implemented.
This feature is not available in the current release of Haiku.
)doc", py::arg("keyring"))
.def("LockMasterKeyring", &BKeyStore::LockMasterKeyring, R"doc(
Not implemented.
This feature is not available in the current release of Haiku.
)doc")
/* ********** waiting for cookie details from Master developers */
.def("GetNextApplication", [](BKeyStore& self,uint32 cookie) {
    BString*  signature = new BString();
    status_t r = self.GetNextApplication(cookie, *signature);
    return std::make_tuple(r,signature,cookie);
}
, "", py::arg("cookie"))
.def("GetNextApplication", [](BKeyStore& self,const char * keyring,uint32 cookie) {
    BString*  signature = new BString();
    status_t r = self.GetNextApplication(keyring, cookie, *signature);
    return std::make_tuple(r,signature,cookie);
}
, "", py::arg("keyring"), py::arg("cookie"))
/* ******************* 'til here ***************** */
.def("RemoveApplication", py::overload_cast<const char *>(&BKeyStore::RemoveApplication), R"doc(
Remove access for an application to the Master keyring.

:param signature: The signature of the application that you want to revoke permissions to access the keyring.
:type signature: str
:return: one of these:

         - ``B_OK`` if the application's access has been revoked.
         - ``B_NOT_ALLOWED`` in case the user did not grant you access right to this keyring.
         - ``B_ENTRY_NOT_FOUND`` if the application did not have access to this keyring.
         - Any other error in case there was an unknown error in the keystore_server, or while communicating to it.

:rtype: int
)doc", py::arg("signature"))
.def("RemoveApplication", py::overload_cast<const char *, const char *>(&BKeyStore::RemoveApplication), R"doc(
Remove access for an application to a keyring.

:param keyring: A UTF-8 string that identifies the keyring that you want to inspect granted access to.
:type keyring: str
:param signature: The signature of the application that you want to revoke permissions to access the keyring.
:type signature: str
:return: one of these:
         - ``B_OK`` if the application's access has been revoked.
         - ``B_NOT_ALLOWED`` in case the user did not grant you access right to this keyring.
         - ``B_ENTRY_NOT_FOUND`` if the application did not have access to this keyring.
         - Any other error in case there was an unknown error in the keystore_server, or while communicating to it.
:rtype: int
)doc", py::arg("keyring"), py::arg("signature"))
.def("GeneratePassword", [](BKeyStore& self,size_t length,uint32 flags) {
    BPasswordKey*  password;
    status_t r = self.GeneratePassword(*password, length, flags);
    return std::make_tuple(r,password);
}
, R"doc(
Unimplemented.
This method is currently not implemented.

:return: always ``B_ERROR``
:rtype: int
)doc", py::arg("length"), py::arg("flags"))
.def("PasswordStrength", &BKeyStore::PasswordStrength, R"doc(
Unimplemented.
This method is currently not implemented.

:return: always ``0``
:rtype: int
)doc", py::arg("password"))
;


}
