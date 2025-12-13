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

PYBIND11_MODULE(Key,m)
{
py::enum_<BKeyPurpose>(m, "BKeyPurpose", "")
.value("B_KEY_PURPOSE_ANY", BKeyPurpose::B_KEY_PURPOSE_ANY, "")
.value("B_KEY_PURPOSE_GENERIC", BKeyPurpose::B_KEY_PURPOSE_GENERIC, "")
.value("B_KEY_PURPOSE_KEYRING", BKeyPurpose::B_KEY_PURPOSE_KEYRING, "")
.value("B_KEY_PURPOSE_WEB", BKeyPurpose::B_KEY_PURPOSE_WEB, "")
.value("B_KEY_PURPOSE_NETWORK", BKeyPurpose::B_KEY_PURPOSE_NETWORK, "")
.value("B_KEY_PURPOSE_VOLUME", BKeyPurpose::B_KEY_PURPOSE_VOLUME, "")
.export_values();

py::enum_<BKeyType>(m, "BKeyType", "")
.value("B_KEY_TYPE_ANY", BKeyType::B_KEY_TYPE_ANY, "")
.value("B_KEY_TYPE_GENERIC", BKeyType::B_KEY_TYPE_GENERIC, "")
.value("B_KEY_TYPE_PASSWORD", BKeyType::B_KEY_TYPE_PASSWORD, "")
.value("B_KEY_TYPE_CERTIFICATE", BKeyType::B_KEY_TYPE_CERTIFICATE, "")
.export_values();

py::class_<BKey,PyBKey>(m, "BKey")
.def(py::init(), "")
.def(py::init<BKeyPurpose, const char *, const char *, unsigned char*, size_t>(), "", py::arg("purpose"), py::arg("identifier"), py::arg("secondaryIdentifier")=NULL, py::arg("data")=NULL, py::arg("length")=0)
.def(py::init(), "")
.def("Type", &BKey::Type, "")
.def("Unset", &BKey::Unset, "")
.def("SetTo", &BKey::SetTo, "", py::arg("purpose"), py::arg("identifier"), py::arg("secondaryIdentifier")=NULL, py::arg("data")=NULL, py::arg("length")=0)
.def("SetPurpose", &BKey::SetPurpose, "", py::arg("purpose"))
.def("Purpose", &BKey::Purpose, "")
.def("SetIdentifier", &BKey::SetIdentifier, "", py::arg("identifier"))
.def("Identifier", &BKey::Identifier, "")
.def("SetSecondaryIdentifier", &BKey::SetSecondaryIdentifier, "", py::arg("identifier"))
.def("SecondaryIdentifier", &BKey::SecondaryIdentifier, "")
.def("SetData", &BKey::SetData, "", py::arg("data"), py::arg("length"))
.def("DataLength", &BKey::DataLength, "")
.def("Data", &BKey::Data, "")
.def("GetData", &BKey::GetData, "", py::arg("buffer"), py::arg("bufferSize"))
.def("Owner", &BKey::Owner, "")
.def("CreationTime", &BKey::CreationTime, "")
.def("Flatten", [](BKey& self) {
    BMessage  message;
    status_t r = self.Flatten(message);
    return std::make_tuple(r,message);
}
, "")
.def("Unflatten", &BKey::Unflatten, "", py::arg("message"))
//.def("operator=", &BKey::operator=, "", py::arg("other"))
.def("__eq__", &BKey::operator==, "", py::arg("other"))
.def("__ne__", &BKey::operator!=, "", py::arg("other"))
.def("PrintToStream", &BKey::PrintToStream, "")
;

py::class_<BPasswordKey, BKey>(m, "BPasswordKey")
.def(py::init(), "")
.def(py::init<const char *, BKeyPurpose, const char *, const char *>(), "", py::arg("password"), py::arg("purpose"), py::arg("identifier"), py::arg("secondaryIdentifier")=NULL)
.def(py::init(), "")
.def("Type", &BPasswordKey::Type, "")
.def("SetTo", &BPasswordKey::SetTo, "", py::arg("password"), py::arg("purpose"), py::arg("identifier"), py::arg("secondaryIdentifier")=NULL)
.def("SetPassword", &BPasswordKey::SetPassword, "", py::arg("password"))
.def("Password", &BPasswordKey::Password, "")
.def("PrintToStream", &BPasswordKey::PrintToStream, "")
;


}
