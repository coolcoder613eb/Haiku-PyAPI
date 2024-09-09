#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/ByteOrder.h>

namespace py = pybind11;
/*
uint64 sw_int64(uint64 arg){
	#if __GNUC__ >= 4
	return __builtin_bswap64(arg);
	#else
	return __swap_int64(arg);
}*/

#if __GNUC__ >= 4
	uint64 swap_int64(uint64 arg) {
		return __builtin_bswap64(arg);
	}
	uint32 swap_int32(uint32 arg) {
		return __builtin_bswap32(arg);
	}
	uint16 swap_int16(uint16 arg) {
		return __builtin_bswap16(arg);
	}
#else 
	extern uint64 __swap_int64(uint64 arg);
	extern uint32 __swap_int32(uint32 arg);
	extern uint16 __swap_int16(uint16 arg);
#endif



PYBIND11_MODULE(ByteOrder, m)
{
py::enum_<swap_action>(m, "swap_action", "")
.value("B_SWAP_HOST_TO_LENDIAN", swap_action::B_SWAP_HOST_TO_LENDIAN, "")
.value("B_SWAP_HOST_TO_BENDIAN", swap_action::B_SWAP_HOST_TO_BENDIAN, "")
.value("B_SWAP_LENDIAN_TO_HOST", swap_action::B_SWAP_LENDIAN_TO_HOST, "")
.value("B_SWAP_BENDIAN_TO_HOST", swap_action::B_SWAP_BENDIAN_TO_HOST, "")
.value("B_SWAP_ALWAYS", swap_action::B_SWAP_ALWAYS, "")
.export_values();

m.def("swap_data", &swap_data, "", py::arg("type"), py::arg("data"), py::arg("length"), py::arg("action"));

m.def("is_type_swapped", &is_type_swapped, "", py::arg("type"));

m.def("__swap_double", &__swap_double, "", py::arg("arg"));

m.def("__swap_float", &__swap_float, "", py::arg("arg"));
/*
m.def("__swap_int64", &__swap_int64, "", py::arg("arg"));
m.def("__swap_int32", &__swap_int32, "", py::arg("arg"));
m.def("__swap_int16", &__swap_int16, "", py::arg("arg"));
*/
#if __GNUC__ >= 4
m.def("__swap_int64", &swap_int64, "Swap bytes of a 64-bit integer");
m.def("__swap_int32", &swap_int32, "Swap bytes of a 32-bit integer");
m.def("__swap_int16", &swap_int16, "Swap bytes of a 16-bit integer");
#else
m.def("__swap_int64", &__swap_int64, "", py::arg("arg"));
m.def("__swap_int32", &__swap_int32, "", py::arg("arg"));
m.def("__swap_int16", &__swap_int16, "", py::arg("arg"));
#endif
}
