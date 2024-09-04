#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <media/BufferGroup.h>
#include <media/Buffer.h>

namespace py = pybind11;
using namespace BPrivate;
//using namespace BPrivate::media;
py::tuple add_buffer_wrapper(BBufferGroup& self, const buffer_clone_info& info) {
    BBuffer* buffer = nullptr;
    status_t status = self.AddBuffer(info, &buffer);

     return py::make_tuple(status, py::cast(buffer, py::return_value_policy::reference));
};

py::tuple get_buffer_list_wrapper(BBufferGroup& self, int32 buffer_count) {
    std::vector<BBuffer*> buffers(buffer_count, nullptr);
    status_t status = self.GetBufferList(buffer_count, buffers.data());

    /*if (status != 0) {
        // Handle error (e.g., raise a Python exception)
        throw py::error_already_set();
    }*/

    // Create a Python list of BBuffer objects
    py::list py_buffers;
    for (BBuffer* buffer : buffers) {
        py_buffers.append(py::cast(buffer, py::return_value_policy::reference));
    }

    return py::make_tuple(status, py_buffers);
};

PYBIND11_MODULE(BufferGroup, m)
{
//m.attr("SharedBufferList") = py::cast(SharedBufferList);
py::class_<BBufferGroup>(m, "BBufferGroup")
.def(py::init<size_t, int32, uint32, uint32>(), "", py::arg("size"), py::arg("count")=3, py::arg("placement")=B_ANY_ADDRESS, py::arg("lock")=B_FULL_LOCK)
.def(py::init(), "")
.def(py::init<int, const media_buffer_id *>(), "", py::arg("count"), py::arg("buffers"))
.def("InitCheck", &BBufferGroup::InitCheck, "")
//.def("AddBuffer", &BBufferGroup::AddBuffer, "", py::arg("info"), py::arg("_buffer")=NULL)
.def("AddBuffer", &add_buffer_wrapper, "", py::arg("info"))
.def("RequestBuffer", py::overload_cast<size_t, bigtime_t>(&BBufferGroup::RequestBuffer), "", py::arg("size"), py::arg("timeout")=B_INFINITE_TIMEOUT)
.def("RequestBuffer", py::overload_cast<BBuffer *, bigtime_t>(&BBufferGroup::RequestBuffer), "", py::arg("buffer"), py::arg("timeout")=B_INFINITE_TIMEOUT)
.def("RequestError", &BBufferGroup::RequestError, "")
.def("CountBuffers", &BBufferGroup::CountBuffers, "", py::arg("_count"))
//.def("GetBufferList", &BBufferGroup::GetBufferList, "", py::arg("bufferCount"), py::arg("_buffers"))
.def("GetBufferList", &get_buffer_list_wrapper, "", py::arg("bufferCount"))
.def("WaitForBuffers", &BBufferGroup::WaitForBuffers, "")
.def("ReclaimAllBuffers", &BBufferGroup::ReclaimAllBuffers, "")
;


}
