#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <drivers/module.h>

namespace py = pybind11;

/*
py::object get_module_wrapper(const std::string& path) {
    module_info* info = nullptr;
    status_t status = get_module(path.c_str(), &info);

    // Crea una lista di module_info da info, se necessario
    std::vector<module_info*> info_vector;
    if (info) {
        // Supponiamo che info sia una lista terminata da nullptr
        while (*info) {
            info_vector.push_back(*info);
            ++info;
        }
    }

    // Ritorna un tuple (status, info_vector)
    return py::make_tuple(status, info_vector);
}*/
/*
std::tuple<status_t, std::vector<module_info>> get_module_wrapper(const std::string& path) {
    // Alloca un puntatore a module_info
    module_info* info = nullptr;

    // Chiama la funzione C
    status_t status = get_module(path.c_str(), &info);

    // Crea un vettore per contenere i module_info
    std::vector<module_info> info_vector;

    if (status == B_OK && info != nullptr) {
        // Itera attraverso l'array di module_info
        // Supponiamo che l'array di module_info termini con un nullptr
        module_info* current = info;
        while (*current != nullptr) {
            info_vector.push_back(*current);
            ++current;
        }
    } else {
        throw std::runtime_error("Failed to get module.");
    }

    // Ritorna il tuple (status, info_vector)
    return std::make_tuple(status, info_vector);
}*/
#include <vector>
#include <string>
#include <stdexcept>
std::tuple<status_t, std::vector<module_info>> get_module_wrapper(const std::string& path) {
    // Alloca un puntatore a array di puntatori a module_info
    module_info* info = nullptr;

    // Chiama la funzione C
    status_t status = get_module(path.c_str(), &info);

    // Crea un vettore per contenere i module_info
    std::vector<module_info> info_vector;

    if (status == B_OK && info != nullptr) {
        // Itera attraverso l'array di puntatori a module_info
        module_info* current = info;
        while (current != nullptr) {
            info_vector.push_back(*current);  // Aggiunge una copia di module_info al vettore
            ++current;
        }
    } else {
        throw std::runtime_error("Failed to get module.");
    }

    // Ritorna il tuple (status, info_vector)
    return std::make_tuple(status, info_vector);
}

/*status_t call_std_ops(module_info* info, int32_t operation, const std::vector<int>& args) {
    if (info == nullptr || info->std_ops == nullptr) {
        return -1; // Ritorna un codice di errore o un valore di default
    }

    // Preparazione dei variadic arguments
    va_list ap;
    va_start(ap, operation);
    for (int arg : args) {
        va_arg(ap, int) = arg;
    }
    va_end(ap);

    // Chiama la funzione std_ops
    return info->std_ops(operation, ap);
}*/
#include <tuple>
/*template <typename Tuple, std::size_t... I>
status_t call_with_tuple(module_info* info, int32_t operation, Tuple&& args, std::index_sequence<I...>) {
    return info->std_ops(operation, std::get<I>(args)...);
}
status_t call_std_ops(module_info* info, int32_t operation, py::args args) {
    if (info == nullptr || info->std_ops == nullptr) {
        return -1; // Codice di errore o valore di default
    }

    // Convert args to a tuple of integers
    auto args_tuple = std::make_tuple(args.cast<int>()...);

    // Call the function using the tuple and apply
    return call_with_tuple(info, operation, args_tuple, std::make_index_sequence<sizeof...(args)>());
}*/
template <typename Tuple, std::size_t... I>
status_t call_with_tuple(module_info* info, int32_t operation, Tuple&& args, std::index_sequence<I...>) {
    return info->std_ops(operation, std::get<I>(args)...);
}

status_t call_std_ops(module_info* info, int32_t operation, py::args args) {
    if (info == nullptr || info->std_ops == nullptr) {
        return -1; // Codice di errore o valore di default
    }

    // Convert py::args to a tuple of integers
    auto args_tuple = std::apply([](auto&&... elems) {
        return std::make_tuple(elems.cast<int>()...);
    }, args);

    // Call the function using the tuple and apply
    return std::apply([&](auto&&... unpackedArgs) {
        return info->std_ops(operation, unpackedArgs...);
    }, args_tuple);
}

PYBIND11_MODULE(module, m) 
{
py::class_<module_info>(m, "module_info")
.def_readwrite("name", &module_info::name, "")
.def_readwrite("flags", &module_info::flags, "")
//.def_readwrite("std_ops", &module_info::std_ops, "")

.def("call_std_ops", &call_std_ops, "Call the std_ops function", py::arg("info"), py::arg("operation"), py::arg("args"));
;

py::class_<module_dependency>(m, "module_dependency")
.def_readwrite("name", &module_dependency::name, "")
//.def_readwrite("info", &module_dependency::info, "")
.def("get_info", [](const module_dependency &self) {
            std::vector<module_info*> info_vector;
            if (self.info) {
                // Converti l'array di puntatori a module_info in un vettore di module_info*
                // Supponiamo che il numero di elementi sia conosciuto e sia 'count'
                for (int i = 0; self.info[i] != nullptr; ++i) {
                    info_vector.push_back(self.info[i]);
                }
            }
            return info_vector;
        })
.def("set_info", [](module_dependency &self, const std::vector<module_info*> &info_vector) {
            // Funzione per impostare l'array di module_info* dalla lista Python
            self.info = new module_info*[info_vector.size() + 1]; // +1 per il terminatore nullptr
            for (size_t i = 0; i < info_vector.size(); ++i) {
                self.info[i] = info_vector[i];
            }
            self.info[info_vector.size()] = nullptr; // Terminatore nullptr
        });

;

//m.def("get_module", &get_module, "", py::arg("path"), py::arg("_info"));
//nell'heaader status_t get_module(const char *path, module_info **_info);
//m.def("get_module", [](const char *path, module_info **_info){}, "", py::arg("path"), py::arg("_info"));
m.def("get_module", &get_module_wrapper, "", py::arg("path"));

m.def("put_module", &put_module, "", py::arg("path"));

m.def("get_next_loaded_module_name", &get_next_loaded_module_name, "", py::arg("cookie"), py::arg("buffer"), py::arg("_bufferSize"));

m.def("open_module_list_etc", &open_module_list_etc, "", py::arg("prefix"), py::arg("suffix"));

m.def("open_module_list", &open_module_list, "", py::arg("prefix"));

m.def("close_module_list", &close_module_list, "", py::arg("cookie"));

m.def("read_next_module_name", &read_next_module_name, "", py::arg("cookie"), py::arg("buffer"), py::arg("_bufferSize"));

}
