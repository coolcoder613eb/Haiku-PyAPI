#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <SerialPort.h>

namespace py = pybind11;

PYBIND11_MODULE(SerialPort,m)
{
py::enum_<data_rate>(m, "data_rate", "")
.value("B_0_BPS", data_rate::B_0_BPS, "")
.value("B_50_BPS", data_rate::B_50_BPS, "")
.value("B_75_BPS", data_rate::B_75_BPS, "")
.value("B_110_BPS", data_rate::B_110_BPS, "")
.value("B_134_BPS", data_rate::B_134_BPS, "")
.value("B_150_BPS", data_rate::B_150_BPS, "")
.value("B_200_BPS", data_rate::B_200_BPS, "")
.value("B_300_BPS", data_rate::B_300_BPS, "")
.value("B_600_BPS", data_rate::B_600_BPS, "")
.value("B_1200_BPS", data_rate::B_1200_BPS, "")
.value("B_1800_BPS", data_rate::B_1800_BPS, "")
.value("B_2400_BPS", data_rate::B_2400_BPS, "")
.value("B_4800_BPS", data_rate::B_4800_BPS, "")
.value("B_9600_BPS", data_rate::B_9600_BPS, "")
.value("B_19200_BPS", data_rate::B_19200_BPS, "")
.value("B_38400_BPS", data_rate::B_38400_BPS, "")
.value("B_57600_BPS", data_rate::B_57600_BPS, "")
.value("B_115200_BPS", data_rate::B_115200_BPS, "")
.value("B_230400_BPS", data_rate::B_230400_BPS, "")
.value("B_31250_BPS", data_rate::B_31250_BPS, "")
.export_values();

py::enum_<data_bits>(m, "data_bits", "")
.value("B_DATA_BITS_7", data_bits::B_DATA_BITS_7, "")
.value("B_DATA_BITS_8", data_bits::B_DATA_BITS_8, "")
.export_values();

py::enum_<stop_bits>(m, "stop_bits", "")
.value("B_STOP_BITS_1", stop_bits::B_STOP_BITS_1, "")
.value("B_STOP_BITS_2", stop_bits::B_STOP_BITS_2, "")
.export_values();

py::enum_<parity_mode>(m, "parity_mode", "")
.value("B_NO_PARITY", parity_mode::B_NO_PARITY, "")
.value("B_ODD_PARITY", parity_mode::B_ODD_PARITY, "")
.value("B_EVEN_PARITY", parity_mode::B_EVEN_PARITY, "")
.export_values();

m.attr("B_NOFLOW_CONTROL") = 0;//py::cast(B_NOFLOW_CONTROL);
m.attr("B_HARDWARE_CONTROL") = 0x00000001;//py::cast(B_HARDWARE_CONTROL);
m.attr("B_SOFTWARE_CONTROL") = 0x00000002;//py::cast(B_SOFTWARE_CONTROL);

py::class_<BSerialPort>(m, "BSerialPort")
.def(py::init(), "")
.def("Open", &BSerialPort::Open, "", py::arg("portName"))
.def("Close", &BSerialPort::Close, "")
//.def("Read", &BSerialPort::Read, "", py::arg("buf"), py::arg("count"))
.def("Read", [](BSerialPort& self, size_t count) {
	std::vector<uint8_t> buffer(count);
	ssize_t result;
	{
		py::gil_scoped_release release;
		result = self.Read(buffer.data(), count);
	}
	if (result > 0) {
		return py::bytes(reinterpret_cast<const char*>(buffer.data()), result);
	}
	return py::bytes(); 
	}, "", py::arg("count"))
//.def("Write", &BSerialPort::Write, "", py::arg("buf"), py::arg("count"))
.def("Write", [](BSerialPort& self, py::buffer data){
	py::buffer_info info = data.request();
	size_t count = info.size;
	const void* buffer = info.ptr;
	ssize_t result;
	{
		py::gil_scoped_release release;
		result = self.Write(buffer, count);
	}
	return result;
},"",py::arg("data"))
.def("SetBlocking", &BSerialPort::SetBlocking, "", py::arg("blocking"))
.def("SetTimeout", &BSerialPort::SetTimeout, "", py::arg("microSeconds"))
.def("SetDataRate", &BSerialPort::SetDataRate, "", py::arg("bitsPerSecond"))
.def("DataRate", &BSerialPort::DataRate, "")
.def("SetDataBits", &BSerialPort::SetDataBits, "", py::arg("numBits"))
.def("DataBits", &BSerialPort::DataBits, "")
.def("SetStopBits", &BSerialPort::SetStopBits, "", py::arg("numBits"))
.def("StopBits", &BSerialPort::StopBits, "")
.def("SetParityMode", &BSerialPort::SetParityMode, "", py::arg("which"))
.def("ParityMode", &BSerialPort::ParityMode, "")
.def("ClearInput", &BSerialPort::ClearInput, "")
.def("ClearOutput", &BSerialPort::ClearOutput, "")
.def("SetFlowControl", &BSerialPort::SetFlowControl, "", py::arg("method"))
.def("FlowControl", &BSerialPort::FlowControl, "")
.def("SetDTR", &BSerialPort::SetDTR, "", py::arg("asserted"))
.def("SetRTS", &BSerialPort::SetRTS, "", py::arg("asserted"))
.def("NumCharsAvailable", &BSerialPort::NumCharsAvailable, "", py::arg("waitThisMany"))
.def("IsCTS", &BSerialPort::IsCTS, "")
.def("IsDSR", &BSerialPort::IsDSR, "")
.def("IsRI", &BSerialPort::IsRI, "")
.def("IsDCD", &BSerialPort::IsDCD, "")
.def("WaitForInput", &BSerialPort::WaitForInput, "")
.def("CountDevices", &BSerialPort::CountDevices, "")
.def("GetDeviceName", &BSerialPort::GetDeviceName, "", py::arg("index"), py::arg("name"), py::arg("bufSize")=B_OS_NAME_LENGTH)
;


}
