#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>

#include <pybind11/functional.h>  // Per supportare std::function
#include <drivers/bios.h>

namespace py = pybind11;

//struct bios_state;
//struct bios_regs;

// Wrapping class

class BiosModuleInfo {
public:
    struct bios_module_info info;

    //std::function<status_t(bios_state**)> prepare;
    std::function<status_t(bios_state*, uint8, bios_regs*)> interrupt;
    std::function<void(bios_state*)> finish;

    std::function<void*(bios_state*, size_t)> allocate_mem;
    std::function<uint32(bios_state*, void*)> physical_address;
    std::function<void*(bios_state*, uint32)> virtual_address;

    BiosModuleInfo() {
        // Initialize function pointers with null callbacks by default.
        /*info.prepare = [this](bios_state** _state) -> status_t {
            return this->prepare(_state);
        };*/
        info.interrupt = [this](bios_state* state, uint8 vector, bios_regs* regs) -> status_t {
            return this->interrupt(state, vector, regs);
        };
        info.finish = [this](bios_state* state) {
            this->finish(state);
        };
        info.allocate_mem = [this](bios_state* state, size_t size) -> void* {
            return this->allocate_mem(state, size);
        };
        info.physical_address = [this](bios_state* state, void* virtualAddress) -> uint32 {
            return this->physical_address(state, virtualAddress);
        };
        info.virtual_address = [this](bios_state* state, uint32 physicalAddress) -> void* {
            return this->virtual_address(state, physicalAddress);
        };
    }
};


PYBIND11_MODULE(bios, m)
{
py::class_<bios_regs>(m, "bios_regs")
.def_readwrite("eax", &bios_regs::eax, "")
.def_readwrite("ebx", &bios_regs::ebx, "")
.def_readwrite("ecx", &bios_regs::ecx, "")
.def_readwrite("edx", &bios_regs::edx, "")
.def_readwrite("edi", &bios_regs::edi, "")
.def_readwrite("esi", &bios_regs::esi, "")
.def_readwrite("ebp", &bios_regs::ebp, "")
.def_readwrite("eflags", &bios_regs::eflags, "")
.def_readwrite("ds", &bios_regs::ds, "")
.def_readwrite("es", &bios_regs::es, "")
.def_readwrite("fs", &bios_regs::fs, "")
.def_readwrite("gs", &bios_regs::gs, "")
;

py::class_<bios_module_info>(m, "bios_module_info")
/*
.def_readwrite("info", &bios_module_info::info, "")
//.def_readwrite("prepare", &bios_module_info::prepare, "")
//.def_readwrite("interrupt", &bios_module_info::interrupt, "")
.def_readwrite("finish", &bios_module_info::finish, "")
.def_readwrite("allocate_mem", &bios_module_info::allocate_mem, "")
.def_readwrite("physical_address", &bios_module_info::physical_address, "")
.def_readwrite("virtual_address", &bios_module_info::virtual_address, "")*/
;

.def(py::init<>())
//.def_readonly("prepare", &BiosModuleInfo::prepare)
.def_readonly("interrupt", &BiosModuleInfo::interrupt)
.def_readonly("finish", &BiosModuleInfo::finish)
.def_readonly("allocate_mem", &BiosModuleInfo::allocate_mem)
.def_readonly("physical_address", &BiosModuleInfo::physical_address)
.def_readonly("virtual_address", &BiosModuleInfo::virtual_address);
;

}
