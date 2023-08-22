#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <interface/PrintJob.h>
#include <Picture.h>

namespace py = pybind11;


PYBIND11_MODULE(PrintJob,m)
{
m.attr("") = ;

py::class_<print_file_header>(m, "print_file_header")
.def_readwrite("version", &print_file_header::version, "")
.def_readwrite("page_count", &print_file_header::page_count, "")
.def_readwrite("first_page", &print_file_header::first_page, "")
.def_readwrite("_reserved", &print_file_header::_reserved, "")
;

py::class_<BPrintJob>(m, "BPrintJob")
.def(py::init<const char *>(), "", py::arg("name"))
.def("BeginJob", &BPrintJob::BeginJob, "")
.def("CommitJob", &BPrintJob::CommitJob, "")
.def("ConfigJob", &BPrintJob::ConfigJob, "")
.def("CancelJob", &BPrintJob::CancelJob, "")
.def("ConfigPage", &BPrintJob::ConfigPage, "")
.def("SpoolPage", &BPrintJob::SpoolPage, "")
.def("CanContinue", &BPrintJob::CanContinue, "")
.def("DrawView", &BPrintJob::DrawView, "", py::arg("view"), py::arg("rect"), py::arg("where"))
.def("Settings", &BPrintJob::Settings, "")
.def("SetSettings", &BPrintJob::SetSettings, "", py::arg("archive"))
.def("IsSettingsMessageValid", &BPrintJob::IsSettingsMessageValid, "", py::arg("archive"))
.def("PaperRect", &BPrintJob::PaperRect, "")
.def("PrintableRect", &BPrintJob::PrintableRect, "")
.def("GetResolution", &BPrintJob::GetResolution, "", py::arg("xDPI"), py::arg("yDPI"))
.def("FirstPage", &BPrintJob::FirstPage, "")
.def("LastPage", &BPrintJob::LastPage, "")
.def("PrinterType", &BPrintJob::PrinterType, "", py::arg("type")=NULL)
;


}
