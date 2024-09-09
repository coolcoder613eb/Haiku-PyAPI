#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/Job.h>

namespace py = pybind11;
using namespace BSupportKit;

class PyBJob : public BJob{
	public:
        using BJob::BJob;
        status_t			Run() override {
            PYBIND11_OVERLOAD(status_t, BJob, Run);
        }
        status_t			Execute() override {
            PYBIND11_OVERLOAD_PURE(status_t, BJob, Execute);
        }
};


PYBIND11_MODULE(Job, m)
{
py::enum_<BJobState>(m, "BJobState", "")
.value("B_JOB_STATE_WAITING_TO_RUN", BJobState::B_JOB_STATE_WAITING_TO_RUN, "")
.value("B_JOB_STATE_STARTED", BJobState::B_JOB_STATE_STARTED, "")
.value("B_JOB_STATE_IN_PROGRESS", BJobState::B_JOB_STATE_IN_PROGRESS, "")
.value("B_JOB_STATE_SUCCEEDED", BJobState::B_JOB_STATE_SUCCEEDED, "")
.value("B_JOB_STATE_FAILED", BJobState::B_JOB_STATE_FAILED, "")
.value("B_JOB_STATE_ABORTED", BJobState::B_JOB_STATE_ABORTED, "")
.export_values();

py::class_<BJobStateListener>(m, "BJobStateListener")
.def("JobStarted", &BJobStateListener::JobStarted, "", py::arg("job"))
.def("JobProgress", &BJobStateListener::JobProgress, "", py::arg("job"))
.def("JobSucceeded", &BJobStateListener::JobSucceeded, "", py::arg("job"))
.def("JobFailed", &BJobStateListener::JobFailed, "", py::arg("job"))
.def("JobAborted", &BJobStateListener::JobAborted, "", py::arg("job"))
;

py::class_<BJob,PyBJob>(m, "BJob")
.def(py::init<const BString &>(), "", py::arg("title"))
.def("InitCheck", &BJob::InitCheck, "")
.def("Run", &BJob::Run, "")
.def("Title", &BJob::Title, "")
.def("State", &BJob::State, "")
.def("Result", &BJob::Result, "")
.def("ErrorString", &BJob::ErrorString, "")
.def("TicketNumber", &BJob::TicketNumber, "")
.def("AddStateListener", &BJob::AddStateListener, "", py::arg("listener"))
.def("RemoveStateListener", &BJob::RemoveStateListener, "", py::arg("listener"))
.def("IsRunnable", &BJob::IsRunnable, "")
.def("AddDependency", &BJob::AddDependency, "", py::arg("job"))
.def("RemoveDependency", &BJob::RemoveDependency, "", py::arg("job"))
.def("CountDependencies", &BJob::CountDependencies, "")
.def("DependantJobAt", &BJob::DependantJobAt, "", py::arg("index"))
//.def_readwrite("Private", &BJob::Private, "")
;


}
