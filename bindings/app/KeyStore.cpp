#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <app/KeyStore.h>
#include <Key.h>

namespace py = pybind11;


PYBIND11_MODULE(KeyStore,m)
{
py::class_<BKeyStore>(m, "BKeyStore")
.def(py::init(), "")
.def("GetKey", [](BKeyStore& self,BKeyType type,const char * identifier) {
    BKey*  key;
    status_t r = self.GetKey(type, identifier, *key);
    return std::make_tuple(r,key);
}
, "", py::arg("type"), py::arg("identifier"))
.def("GetKey", [](BKeyStore& self,BKeyType type,const char * identifier,const char * secondaryIdentifier) {
    BKey*  key;
    status_t r = self.GetKey(type, identifier, secondaryIdentifier, *key);
    return std::make_tuple(r,key);
}
, "", py::arg("type"), py::arg("identifier"), py::arg("secondaryIdentifier"))
.def("GetKey", [](BKeyStore& self,BKeyType type,const char * identifier,const char * secondaryIdentifier,bool secondaryIdentifierOptional) {
    BKey*  key;
    status_t r = self.GetKey(type, identifier, secondaryIdentifier, secondaryIdentifierOptional, *key);
    return std::make_tuple(r,key);
}
, "", py::arg("type"), py::arg("identifier"), py::arg("secondaryIdentifier"), py::arg("secondaryIdentifierOptional"))
.def("GetKey", [](BKeyStore& self,const char * keyring,BKeyType type,const char * identifier) {
    BKey*  key;
    status_t r = self.GetKey(keyring, type, identifier, *key);
    return std::make_tuple(r,key);
}
, "", py::arg("keyring"), py::arg("type"), py::arg("identifier"))
.def("GetKey", [](BKeyStore& self,const char * keyring,BKeyType type,const char * identifier,const char * secondaryIdentifier) {
    BKey*  key;
    status_t r = self.GetKey(keyring, type, identifier, secondaryIdentifier, *key);
    return std::make_tuple(r,key);
}
, "", py::arg("keyring"), py::arg("type"), py::arg("identifier"), py::arg("secondaryIdentifier"))
.def("GetKey", [](BKeyStore& self,const char * keyring,BKeyType type,const char * identifier,const char * secondaryIdentifier,bool secondaryIdentifierOptional) {
    BKey*  key;
    status_t r = self.GetKey(keyring, type, identifier, secondaryIdentifier, secondaryIdentifierOptional, *key);
    return std::make_tuple(r,key);
}
, "", py::arg("keyring"), py::arg("type"), py::arg("identifier"), py::arg("secondaryIdentifier"), py::arg("secondaryIdentifierOptional"))
.def("AddKey", py::overload_cast<const BKey &>(&BKeyStore::AddKey), "", py::arg("key"))
.def("AddKey", py::overload_cast<const char *, const BKey &>(&BKeyStore::AddKey), "", py::arg("keyring"), py::arg("key"))
.def("RemoveKey", py::overload_cast<const BKey &>(&BKeyStore::RemoveKey), "", py::arg("key"))
.def("RemoveKey", py::overload_cast<const char *, const BKey &>(&BKeyStore::RemoveKey), "", py::arg("keyring"), py::arg("key"))
.def("GetNextKey", [](BKeyStore& self,uint32 cookie) {
    BKey*  key;
    status_t r = self.GetNextKey(cookie, *key);
    return std::make_tuple(r,key);
}
, "", py::arg("cookie"))
.def("GetNextKey", [](BKeyStore& self,BKeyType type,BKeyPurpose purpose,uint32 cookie) {
    BKey*  key;
    status_t r = self.GetNextKey(type, purpose, cookie, *key);
    return std::make_tuple(r,key);
}
, "", py::arg("type"), py::arg("purpose"), py::arg("cookie"))
.def("GetNextKey", [](BKeyStore& self,const char * keyring,uint32 cookie) {
    BKey*  key;
    status_t r = self.GetNextKey(keyring, cookie, *key);
    return std::make_tuple(r,key);
}
, "", py::arg("keyring"), py::arg("cookie"))
.def("GetNextKey", [](BKeyStore& self,const char * keyring,BKeyType type,BKeyPurpose purpose,uint32 cookie) {
    BKey*  key;
    status_t r = self.GetNextKey(keyring, type, purpose, cookie, *key);
    return std::make_tuple(r,key);
}
, "", py::arg("keyring"), py::arg("type"), py::arg("purpose"), py::arg("cookie"))
.def("AddKeyring", &BKeyStore::AddKeyring, "", py::arg("keyring"))
.def("RemoveKeyring", &BKeyStore::RemoveKeyring, "", py::arg("keyring"))
.def("GetNextKeyring", [](BKeyStore& self,uint32 cookie) {
    BString  keyring;
    status_t r = self.GetNextKeyring(cookie, keyring);
    return std::make_tuple(r,keyring);
}
, "", py::arg("cookie"))
.def("SetUnlockKey", &BKeyStore::SetUnlockKey, "", py::arg("keyring"), py::arg("key"))
.def("RemoveUnlockKey", &BKeyStore::RemoveUnlockKey, "", py::arg("keyring"))
.def("SetMasterUnlockKey", &BKeyStore::SetMasterUnlockKey, "", py::arg("key"))
.def("RemoveMasterUnlockKey", &BKeyStore::RemoveMasterUnlockKey, "")
.def("AddKeyringToMaster", &BKeyStore::AddKeyringToMaster, "", py::arg("keyring"))
.def("RemoveKeyringFromMaster", &BKeyStore::RemoveKeyringFromMaster, "", py::arg("keyring"))
.def("GetNextMasterKeyring", [](BKeyStore& self,uint32 cookie) {
    BString  keyring;
    status_t r = self.GetNextMasterKeyring(cookie, keyring);
    return std::make_tuple(r,keyring);
}
, "", py::arg("cookie"))
.def("IsKeyringUnlocked", &BKeyStore::IsKeyringUnlocked, "", py::arg("keyring"))
.def("LockKeyring", &BKeyStore::LockKeyring, "", py::arg("keyring"))
.def("LockMasterKeyring", &BKeyStore::LockMasterKeyring, "")
.def("GetNextApplication", [](BKeyStore& self,uint32 cookie) {
    BString  signature;
    status_t r = self.GetNextApplication(cookie, signature);
    return std::make_tuple(r,signature);
}
, "", py::arg("cookie"))
.def("GetNextApplication", [](BKeyStore& self,const char * keyring,uint32 cookie) {
    BString  signature;
    status_t r = self.GetNextApplication(keyring, cookie, signature);
    return std::make_tuple(r,signature);
}
, "", py::arg("keyring"), py::arg("cookie"))
.def("RemoveApplication", py::overload_cast<const char *>(&BKeyStore::RemoveApplication), "", py::arg("signature"))
.def("RemoveApplication", py::overload_cast<const char *, const char *>(&BKeyStore::RemoveApplication), "", py::arg("keyring"), py::arg("signature"))
.def("GeneratePassword", [](BKeyStore& self,size_t length,uint32 flags) {
    BPasswordKey*  password;
    status_t r = self.GeneratePassword(*password, length, flags);
    return std::make_tuple(r,password);
}
, "", py::arg("length"), py::arg("flags"))
.def("PasswordStrength", &BKeyStore::PasswordStrength, "", py::arg("password"))
;


}
