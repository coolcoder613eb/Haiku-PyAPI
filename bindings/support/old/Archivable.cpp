#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "support/Archivable.h"  // Assicurati che il nome del tuo file header sia corretto

namespace py = pybind11;

class PyBArchivable : public BArchivable {
public:
    // Costruttori
    using BArchivable::BArchivable;  // Eredità dei costruttori base

    // Metodo per l'archiviazione
    status_t Archive(BMessage* into, bool deep = true) const override {
        PYBIND11_OVERLOAD_PURE(status_t, BArchivable, Archive, into, deep);
    }

    // Altri metodi da esporre a Python, se necessario
};

PYBIND11_MODULE(Archivable, m) {
    py::class_<BArchivable, PyBArchivable>(m, "BArchivable")
        .def(py::init<BMessage*>())
        .def(py::init<>())
        .def("Archive", &BArchivable::Archive);

    // Aggiungi altri metodi e costruttori se necessario

    // Aggiungi altre classi wrapper se necessario
}

