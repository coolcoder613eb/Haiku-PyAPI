#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <support/SupportDefs.h>

namespace py = pybind11;


PYBIND11_MODULE(SupportDefs, m)
{
m.attr("B_EMPTY_STRING") = py::cast(B_EMPTY_STRING);

m.def("get_stack_frame", &get_stack_frame, "");//, py::arg(""));

m.def("atomic_set", py::overload_cast<int32*, int32>(&atomic_set), "", py::arg("value"), py::arg("newValue"));

m.def("atomic_get_and_set", py::overload_cast<int32*, int32>(&atomic_get_and_set), "", py::arg("value"), py::arg("newValue"));

m.def("atomic_test_and_set", py::overload_cast<int32*, int32, int32>(&atomic_test_and_set), "", py::arg("value"), py::arg("newValue"), py::arg("testAgainst"));

m.def("atomic_add", py::overload_cast<int32*, int32>(&atomic_add), "", py::arg("value"), py::arg("addValue"));

m.def("atomic_and", py::overload_cast<int32*, int32>(&atomic_and), "", py::arg("value"), py::arg("andValue"));

m.def("atomic_or", py::overload_cast<int32*, int32>(&atomic_or), "", py::arg("value"), py::arg("orValue"));

m.def("atomic_get", py::overload_cast<int32*>(&atomic_get), "", py::arg("value"));

m.def("atomic_set64", py::overload_cast<int64_t*, int64_t>(&atomic_set64), "", py::arg("value"), py::arg("newValue"));

m.def("atomic_get_and_set64", py::overload_cast<int64_t*, int64_t>(&atomic_get_and_set64), "", py::arg("value"), py::arg("newValue"));

m.def("atomic_test_and_set64", py::overload_cast<int64_t*, int64_t, int64_t>(&atomic_test_and_set64), "", py::arg("value"), py::arg("newValue"), py::arg("testAgainst"));

m.def("atomic_add64", py::overload_cast<int64_t*, int64_t>(&atomic_add64), "", py::arg("value"), py::arg("addValue"));

m.def("atomic_and64", py::overload_cast<int64_t*, int64_t>(&atomic_and64), "", py::arg("value"), py::arg("andValue"));

m.def("atomic_or64", py::overload_cast<int64_t*, int64_t>(&atomic_or64), "", py::arg("value"), py::arg("orValue"));

m.def("atomic_get64", py::overload_cast<int64_t*>(&atomic_get64), "", py::arg("value"));

m.attr("B_PRId8") = B_PRId8;
    m.attr("B_PRIi8") = B_PRIi8;
    m.attr("B_PRId16") = B_PRId16;
    m.attr("B_PRIi16") = B_PRIi16;
    m.attr("B_PRId32") = B_PRId32;
    m.attr("B_PRIi32") = B_PRIi32;
    m.attr("B_PRId64") = B_PRId64;
    m.attr("B_PRIi64") = B_PRIi64;

    m.attr("B_PRIu8") = B_PRIu8;
    m.attr("B_PRIo8") = B_PRIo8;
    m.attr("B_PRIx8") = B_PRIx8;
    m.attr("B_PRIX8") = B_PRIX8;
    m.attr("B_PRIu16") = B_PRIu16;
    m.attr("B_PRIo16") = B_PRIo16;
    m.attr("B_PRIx16") = B_PRIx16;
    m.attr("B_PRIX16") = B_PRIX16;
    m.attr("B_PRIu32") = B_PRIu32;
    m.attr("B_PRIo32") = B_PRIo32;
    m.attr("B_PRIx32") = B_PRIx32;
    m.attr("B_PRIX32") = B_PRIX32;
    m.attr("B_PRIu64") = B_PRIu64;
    m.attr("B_PRIo64") = B_PRIo64;
    m.attr("B_PRIx64") = B_PRIx64;
    m.attr("B_PRIX64") = B_PRIX64;

    m.attr("B_SCNd8") = B_SCNd8;
    m.attr("B_SCNi8") = B_SCNi8;
    m.attr("B_SCNd16") = B_SCNd16;
    m.attr("B_SCNi16") = B_SCNi16;
    m.attr("B_SCNd32") = B_SCNd32;
    m.attr("B_SCNi32") = B_SCNi32;
    m.attr("B_SCNd64") = B_SCNd64;
    m.attr("B_SCNi64") = B_SCNi64;

    m.attr("B_SCNu8") = B_SCNu8;
    m.attr("B_SCNo8") = B_SCNo8;
    m.attr("B_SCNx8") = B_SCNx8;
    m.attr("B_SCNu16") = B_SCNu16;
    m.attr("B_SCNo16") = B_SCNo16;
    m.attr("B_SCNx16") = B_SCNx16;
    m.attr("B_SCNu32") = B_SCNu32;
    m.attr("B_SCNo32") = B_SCNo32;
    m.attr("B_SCNx32") = B_SCNx32;
    m.attr("B_SCNu64") = B_SCNu64;
    m.attr("B_SCNo64") = B_SCNo64;
    m.attr("B_SCNx64") = B_SCNx64;
    // ... Aggiungi altre costanti o macro secondo necessità ...
    m.attr("B_PRIuSIZE") = B_PRIuSIZE;
    m.attr("B_PRIoSIZE") = B_PRIoSIZE;
    m.attr("B_PRIxSIZE") = B_PRIxSIZE;
    m.attr("B_PRIXSIZE") = B_PRIXSIZE;
    m.attr("B_SCNuSIZE") = B_SCNuSIZE;
    m.attr("B_SCNoSIZE") = B_SCNoSIZE;
    m.attr("B_SCNxSIZE") = B_SCNxSIZE;
    m.attr("B_PRIdSSIZE") = B_PRIdSSIZE;
    m.attr("B_PRIiSSIZE") = B_PRIiSSIZE;
    m.attr("B_SCNdSSIZE") = B_SCNdSSIZE;
    m.attr("B_SCNiSSIZE") = B_SCNiSSIZE;
    m.attr("B_PRIuADDR") = B_PRIuADDR;
    m.attr("B_PRIoADDR") = B_PRIoADDR;
    m.attr("B_PRIxADDR") = B_PRIxADDR;
    m.attr("B_PRIXADDR") = B_PRIXADDR;
    m.attr("B_SCNuADDR") = B_SCNuADDR;
    m.attr("B_SCNoADDR") = B_SCNoADDR;
    m.attr("B_PRIuPHYSADDR") = B_PRIuPHYSADDR;
    m.attr("B_PRIoPHYSADDR") = B_PRIoPHYSADDR;
    m.attr("B_PRIxPHYSADDR") = B_PRIxPHYSADDR;
    m.attr("B_PRIXPHYSADDR") = B_PRIXPHYSADDR;
    m.attr("B_SCNuPHYSADDR") = B_SCNuPHYSADDR;
    m.attr("B_SCNoPHYSADDR") = B_SCNoPHYSADDR;
    m.attr("B_SCNxPHYSADDR") = B_SCNxPHYSADDR;
    m.attr("B_PRIuGENADDR") = B_PRIuGENADDR;
    m.attr("B_PRIoGENADDR") = B_PRIoGENADDR;
    m.attr("B_PRIxGENADDR") = B_PRIxGENADDR;
    m.attr("B_PRIXGENADDR") = B_PRIXGENADDR;
    m.attr("B_SCNuGENADDR") = B_SCNuGENADDR;
    m.attr("B_SCNoGENADDR") = B_SCNoGENADDR;
    m.attr("B_SCNxGENADDR") = B_SCNxGENADDR;
    m.attr("B_PRIdOFF") = B_PRIdOFF;
    m.attr("B_PRIiOFF") = B_PRIiOFF;
    m.attr("B_PRIxOFF") = B_PRIxOFF;
    m.attr("B_SCNdOFF") = B_SCNdOFF;
    m.attr("B_SCNiOFF") = B_SCNiOFF;
    m.attr("B_SCNxOFF") = B_SCNxOFF;
    m.attr("B_PRIdDEV") = B_PRIdDEV;
    m.attr("B_PRIiDEV") = B_PRIiDEV;
    m.attr("B_PRIdINO") = B_PRIdINO;
    m.attr("B_PRIiINO") = B_PRIiINO;
    m.attr("B_PRIdBIGTIME") = B_PRIdBIGTIME;
    m.attr("B_PRIiBIGTIME") = B_PRIiBIGTIME;
}
