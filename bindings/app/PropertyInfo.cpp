#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <app/PropertyInfo.h>
#include <BeBuild.h>
#include <Flattenable.h>
#include <SupportDefs.h>
#include <TypeConstants.h>
#include <Message.h>

namespace py = pybind11;

class PyBPropertyInfo : public BPropertyInfo{
	public:
        using BPropertyInfo::BPropertyInfo;
        int32				FindMatch(BMessage* msg, int32 index, BMessage* specifier, int32 form, const char* prop, void* data = NULL) const override {
            PYBIND11_OVERLOAD(int32, BPropertyInfo, FindMatch, msg, index, specifier, form, prop, data);
        }
        bool				IsFixedSize() const override {
            PYBIND11_OVERLOAD(bool, BPropertyInfo, IsFixedSize);
        }
        type_code			TypeCode() const override {
            PYBIND11_OVERLOAD(type_code, BPropertyInfo, TypeCode);
        }
        ssize_t				FlattenedSize() const override {
            PYBIND11_OVERLOAD(ssize_t, BPropertyInfo, FlattenedSize);
        }
        status_t			Flatten(void* buffer, ssize_t size) const override {
            PYBIND11_OVERLOAD(status_t, BPropertyInfo, Flatten, buffer, size);
        }
        bool				AllowsTypeCode(type_code code) const override {
            PYBIND11_OVERLOAD(bool, BPropertyInfo, AllowsTypeCode, code);
        }
        status_t			Unflatten(type_code code, const void* buffer, ssize_t size) override {
            PYBIND11_OVERLOAD(status_t, BPropertyInfo, Unflatten, code, buffer, size);
        }
};

PYBIND11_MODULE(PropertyInfo,m)
{
py::enum_<value_kind>(m, "value_kind", "")
.value("B_COMMAND_KIND", value_kind::B_COMMAND_KIND, "")
.value("B_TYPE_CODE_KIND", value_kind::B_TYPE_CODE_KIND, "")
.export_values();

py::class_<compound_type>(m, "compound_type")
.def_readonly("pairs", &compound_type::pairs, "")
;

py::class_<compound_type::field_pair>(m, "field_pair")
.def_readonly("name", &compound_type::field_pair::name, "")
.def_readonly("type", &compound_type::field_pair::type, "")
;

py::class_<property_info>(m, "property_info")
.def_readwrite("name", &property_info::name, "")
.def_readonly("commands", &property_info::commands, "")
.def_readonly("specifiers", &property_info::specifiers, "")
.def_readwrite("usage", &property_info::usage, "")
.def_readwrite("extra_data", &property_info::extra_data, "")
.def_readonly("types", &property_info::types, "")
.def_readonly("ctypes", &property_info::ctypes, "")
.def_readonly("_reserved", &property_info::_reserved, "")
;

py::class_<value_info>(m, "value_info")
.def_readwrite("name", &value_info::name, "")
.def_readwrite("value", &value_info::value, "")
.def_readwrite("kind", &value_info::kind, "")
.def_readwrite("usage", &value_info::usage, "")
.def_readwrite("extra_data", &value_info::extra_data, "")
.def_readonly("_reserved", &value_info::_reserved, "")
;

py::class_<BPropertyInfo,PyBPropertyInfo>(m, "BPropertyInfo", "Class used to manage scripting.")
.def(py::init<property_info *, value_info *, bool>(), R"doc(
Initializes the object with the specified ``propertyInfo`` and ``valueInfo``.

:param prop: The properties array.
:type prop: property_info
:param value:The values array.
:type value: value_info
:param freeOnDelete: if ``True``, free the memory associated with propertyInfo and valueInfo when the object is destroyed.
:type freeOnDelete: bool
)doc", py::arg("prop")=NULL, py::arg("value")=NULL, py::arg("freeOnDelete")=false)
//.def("FindMatch", &BPropertyInfo::FindMatch, R"doc(
.def("FindMatch", [](BPropertyInfo& self, BMessage* msg, int32 index, BMessage* spec, int32 form, const char* prop, py::buffer data){
	py::buffer_info info = data.request();
	if (info.size < (ssize_t)sizeof(uint32)) {
         throw py::value_error("The provided buffer is too small (needed at least 4 bytes)");
    }
    return self.FindMatch(msg, index, spec, form, prop, info.ptr);
}, R"doc(
Finds a property match for a scripting request.

Passed a property name in ``prop``, a specifier in ``form``, and a command 
in ``msg.what``, searches the ``property_info`` array for an item supporting 
the specified scripting request. If ``index`` is nonzero, then ``FindMatch()`` 
only searches those ``property_info`` structures with the wildcard command 
(first element of command array equal to ``0``). Otherwise, it searches 
through all available ``property_info`` structures for a match. If a match 
is found, it fills the memory at ``data`` with the contents of the ``extra_data`` 
field of the match and returns the index of the match in the array. Otherwise, it returns ``B_ERROR``.

.. note::
   
   this function is kept for C++ compatibility
   
.. note::

   if the provided data buffer is smaller than 4 bytes an exception is rised.
   
:param msg: The scripting message containing the command (``what``) to match.
:type msg: BMessage
:param index: Search filter. If non-zero, the search is restricted to property info structures with a wildcard command (``0``). If ``0``, it searches all available structures.
:type index: int
:param specifier: The specifier message.
:type specifier: BMessage
:param form: The specifier form (e.g., ``B_DIRECT_SPECIFIER``).
:type form: int
:param prop: The name of the property to look for.
:type prop: str
:param data: A writable 4-byte buffer (e.g., ``bytearray(4)``). The function will write the ``extra_data`` (``uint32``) of the matching property into this buffer.
:type data: py::buffer
:return: The index of the matching property info in the array, or ``B_ERROR`` if no match is found.
:rtype: int
)doc", py::arg("msg"), py::arg("index"), py::arg("specifier"), py::arg("form"), py::arg("prop"), py::arg("data")=NULL)
.def("FindMatch", [](BPropertyInfo& self, BMessage* msg, int32 index, BMessage* spec, int32 form, const char* prop){
	uint32 extraData = 0;
    int32 resultIndex = self.FindMatch(msg, index, spec, form, prop, &extraData);
    return py::make_tuple(resultIndex, extraData);
}, R"doc(
Finds a property match for a scripting request.

Passed a property name in ``prop``, a specifier in ``form``, and a command 
in ``msg.what``, searches the ``property_info`` array for an item supporting 
the specified scripting request. If ``index`` is nonzero, then ``FindMatch()`` 
only searches those ``property_info`` structures with the wildcard command 
(first element of command array equal to ``0``). Otherwise, it searches 
through all available ``property_info`` structures for a match.

This is the Pythonic version of ``FindMatch`` that returns both the index of the 
match and the associated ``extra_data``.

:param msg: The scripting message containing the command (``what``) to match.
:type msg: BMessage
:param index: Search filter. If non-zero, the search is restricted to property info structures with a wildcard command (``0``). If ``0``, it searches all available structures.
:type index: int
:param specifier: The specifier message.
:type specifier: BMessage
:param form: The specifier form (e.g., ``B_DIRECT_SPECIFIER``).
:type form: int
:param prop: The name of the property to look for.
:type prop: str
:return: A tuple containing (match_index, extra_data):
   
   - ``match_index`` (int) The index of the matching property info in the array, or ``B_ERROR`` if no match is found.
   - ``extra_data`` (int) As property_info.extra_data is an uint32 an int is returned instead of a buffer.
   
:rtype: tuple
)doc", py::arg("msg"), py::arg("index"), py::arg("spec"), py::arg("form"), py::arg("prop"))
.def("IsFixedSize", &BPropertyInfo::IsFixedSize, R"doc(
Implements ``BFlattenable.IsFixed()`` which returns whether or not flattened objects 
of this type always have a fixed size. This case returns always ``False``.

:return: ``False``
:rtype: bool
)doc")
.def("TypeCode", &BPropertyInfo::TypeCode, R"doc(
Implements ``BFlattenable.TypeCode()`` returns the type_code its class flattens 
to. This case returns always ``B_PROPERTY_INFO_TYPE``.

:return: ``B_PROPERTY_INFO_TYPE``
:rtype: type_code
)doc")
.def("FlattenedSize", &BPropertyInfo::FlattenedSize, R"doc(
Return the size of the flattened object in bytes.

:return: The size (ssize_t) of the flattened object in bytes.
:rtype: int
)doc")
//.def("Flatten", &BPropertyInfo::Flatten, R"doc(
.def("Flatten", [](const BPropertyInfo& self, ssize_t numBytes) {
    if (numBytes <= 0) {
        return py::make_tuple((status_t)B_BAD_VALUE, py::bytes(""));
    }
    std::vector<char> buffer(numBytes);
    status_t status = self.Flatten(static_cast<void*>(buffer.data()), numBytes);
    return py::make_tuple(status, py::bytes(buffer.data(), buffer.size()));
}, R"doc(
Flatten the object into a bytes object using a user-specified size.
The status of the call is returned in a tuple along with the filled buffer.

:param numBytes: The number of bytes to allocate for the buffer.
:type numBytes: int
:return: A tuple containing the status and the flattened bytes ``(status, flattened_bytes)``:

   - ``status`` (int) ``B_OK`` or an error code 
   - ``flattened_bytes`` (bytes) the bytes stored.
   
:rtype: tuple
)doc", py::arg("numBytes"))
.def("Flatten", [](BPropertyInfo& self){
	ssize_t size = self.FlattenedSize();
	if (size < 0) {
        return py::make_tuple((status_t)size, py::bytes(""));
    }
	std::vector<char>data(size);
	//void * buffer = nullptr;
	status_t status = self.Flatten(static_cast<void*>(data.data()),size);
	return py::make_tuple(status, py::bytes(data.data(), data.size()));
}, R"doc(
Flatten the object into a bytes object, automatically calculating the required 
size.
The status of the call is returned in a tuple along with the filled buffer.

:return: A tuple containing the status and the flattened bytes ``(status, flattened_bytes)``:

   - ``status`` (int) ``B_OK`` or an error code 
   - ``flattened_bytes`` (bytes) the bytes stored.
   
:rtype: tuple
)doc")
.def("AllowsTypeCode", &BPropertyInfo::AllowsTypeCode, "", py::arg("code"))
.def("Unflatten", &BPropertyInfo::Unflatten, "", py::arg("code"), py::arg("buffer"), py::arg("size"))
.def("Properties", &BPropertyInfo::Properties, "")
.def("Values", &BPropertyInfo::Values, "")
.def("CountProperties", &BPropertyInfo::CountProperties, "")
.def("CountValues", &BPropertyInfo::CountValues, "")
.def("PrintToStream", &BPropertyInfo::PrintToStream, "")
;


}
