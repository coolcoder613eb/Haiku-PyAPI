#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>
#include <pthread.h>

#include <kernel/OS.h>

namespace py = pybind11;

unsigned long real_time_clock_wrapper() {
    return real_time_clock();
}

bigtime_t	real_time_clock_usecs_wrapper(){
	return real_time_clock_usecs();
}

bigtime_t	system_time_wrapper(){
	return system_time();
}

nanotime_t	system_time_nsecs_wrapper(){
	return system_time_nsecs();
}

int32		is_computer_on_wrapper(){
	return is_computer_on();
}

double		is_computer_on_fire_wrapper(){
	return is_computer_on_fire();
}

std::string get_area_info_name(const area_info& self) {
    return std::string(self.name);
}

void set_area_info_name(area_info& self, const std::string& name) {
    std::strncpy(self.name, name.c_str(), B_OS_NAME_LENGTH - 1);
    self.name[B_OS_NAME_LENGTH - 1] = '\0';
}
//
std::string get_port_info_name(const port_info& self) {
    return std::string(self.name);
}

void set_port_info_name(port_info& self, const std::string& name) {
    std::strncpy(self.name, name.c_str(), B_OS_NAME_LENGTH - 1);
    self.name[B_OS_NAME_LENGTH - 1] = '\0';
}
//
std::string get_sem_info_name(const sem_info& self) {
    return std::string(self.name);
}

void set_sem_info_name(sem_info& self, const std::string& name) {
    std::strncpy(self.name, name.c_str(), B_OS_NAME_LENGTH - 1);
    self.name[B_OS_NAME_LENGTH - 1] = '\0';
}
//
std::string get_team_info_args(const team_info& self) {
    return std::string(self.args);
}

void set_team_info_args(team_info& self, const std::string& args) {
    std::strncpy(self.args, args.c_str(), 64 - 1);
    self.args[64 - 1] = '\0';
}

area_id create_area_wrapper(const std::string &name, py::capsule &startAddress,
                            uint32_t addressSpec, size_t size, uint32_t lock,
                            uint32_t protection) {
    void *startAddressPtr = startAddress; // Converte il py::capsule in void*
    return create_area(name.c_str(), &startAddressPtr, addressSpec, size, lock, protection);
}
area_id clone_area_wrapper(const std::string &name, py::capsule &destAddress,
                           uint32_t addressSpec, uint32_t protection,
                           area_id source) {
    void *destAddressPtr = destAddress.get_pointer(); // Converte il py::capsule in void*
    return clone_area(name.c_str(), &destAddressPtr, addressSpec, protection, source);
}
PYBIND11_MODULE(OS,m)
{
/*m.attr("B_TIMEOUT") = py::cast(B_TIMEOUT);
m.attr("B_RELATIVE_TIMEOUT") = py::cast(B_RELATIVE_TIMEOUT);
m.attr("B_ABSOLUTE_TIMEOUT") = py::cast(B_ABSOLUTE_TIMEOUT);
m.attr("B_TIMEOUT_REAL_TIME_BASE") = py::cast(B_TIMEOUT_REAL_TIME_BASE);
m.attr("B_ABSOLUTE_REAL_TIME_TIMEOUT") = py::cast(B_ABSOLUTE_REAL_TIME_TIMEOUT);*/
m.attr("B_TIMEOUT") = 0x8;
m.attr("B_RELATIVE_TIMEOUT") = 0x8;
m.attr("B_ABSOLUTE_TIMEOUT") = 0x10;
m.attr("B_TIMEOUT_REAL_TIME_BASE") = 0x40;
m.attr("B_ABSOLUTE_REAL_TIME_TIMEOUT") = 0x10|0x40;
/*
m.attr("B_CAN_INTERRUPT") = py::cast(B_CAN_INTERRUPT);
m.attr("B_CHECK_PERMISSION") = py::cast(B_CHECK_PERMISSION);
m.attr("B_KILL_CAN_INTERRUPT") = py::cast(B_KILL_CAN_INTERRUPT);
m.attr("B_DO_NOT_RESCHEDULE") = py::cast(B_DO_NOT_RESCHEDULE);
m.attr("B_RELEASE_ALL") = py::cast(B_RELEASE_ALL);
m.attr("B_RELEASE_IF_WAITING_ONLY") = py::cast(B_RELEASE_IF_WAITING_ONLY);*/
m.attr("B_CAN_INTERRUPT") = 0x01;
m.attr("B_CHECK_PERMISSION") = 0x04;
m.attr("B_KILL_CAN_INTERRUPT") = 0x20;
m.attr("B_DO_NOT_RESCHEDULE") = 0x02;
m.attr("B_RELEASE_ALL") = 0x08;
m.attr("B_RELEASE_IF_WAITING_ONLY") = 0x10;

/*m.attr("B_TEAM_USAGE_SELF") = py::cast(B_TEAM_USAGE_SELF);
m.attr("B_TEAM_USAGE_CHILDREN") = py::cast(B_TEAM_USAGE_CHILDREN);*/
m.attr("B_TEAM_USAGE_SELF") = 0;
m.attr("B_TEAM_USAGE_CHILDREN") = -1;

py::enum_<thread_state>(m, "thread_state", "")
.value("B_THREAD_RUNNING", thread_state::B_THREAD_RUNNING, "")
.value("B_THREAD_READY", thread_state::B_THREAD_READY, "")
.value("B_THREAD_RECEIVING", thread_state::B_THREAD_RECEIVING, "")
.value("B_THREAD_ASLEEP", thread_state::B_THREAD_ASLEEP, "")
.value("B_THREAD_SUSPENDED", thread_state::B_THREAD_SUSPENDED, "")
.value("B_THREAD_WAITING", thread_state::B_THREAD_WAITING, "")
.export_values();
/*
m.attr("B_ONE_SHOT_ABSOLUTE_ALARM") = py::cast(B_ONE_SHOT_ABSOLUTE_ALARM);
m.attr("B_ONE_SHOT_RELATIVE_ALARM") = py::cast(B_ONE_SHOT_RELATIVE_ALARM);
m.attr("B_PERIODIC_ALARM") = py::cast(B_PERIODIC_ALARM);*/
m.attr("B_ONE_SHOT_ABSOLUTE_ALARM") = 1;
m.attr("B_ONE_SHOT_RELATIVE_ALARM") = 2;
m.attr("B_PERIODIC_ALARM") = 3;

py::enum_<topology_level_type>(m, "topology_level_type", "")
.value("B_TOPOLOGY_UNKNOWN", topology_level_type::B_TOPOLOGY_UNKNOWN, "")
.value("B_TOPOLOGY_ROOT", topology_level_type::B_TOPOLOGY_ROOT, "")
.value("B_TOPOLOGY_SMT", topology_level_type::B_TOPOLOGY_SMT, "")
.value("B_TOPOLOGY_CORE", topology_level_type::B_TOPOLOGY_CORE, "")
.value("B_TOPOLOGY_PACKAGE", topology_level_type::B_TOPOLOGY_PACKAGE, "")
.export_values();

py::enum_<cpu_platform>(m, "cpu_platform", "")
.value("B_CPU_UNKNOWN", cpu_platform::B_CPU_UNKNOWN, "")
.value("B_CPU_x86", cpu_platform::B_CPU_x86, "")
.value("B_CPU_x86_64", cpu_platform::B_CPU_x86_64, "")
.value("B_CPU_PPC", cpu_platform::B_CPU_PPC, "")
.value("B_CPU_PPC_64", cpu_platform::B_CPU_PPC_64, "")
.value("B_CPU_M68K", cpu_platform::B_CPU_M68K, "")
.value("B_CPU_ARM", cpu_platform::B_CPU_ARM, "")
.value("B_CPU_ARM_64", cpu_platform::B_CPU_ARM_64, "")
.value("B_CPU_ALPHA", cpu_platform::B_CPU_ALPHA, "")
.value("B_CPU_MIPS", cpu_platform::B_CPU_MIPS, "")
.value("B_CPU_SH", cpu_platform::B_CPU_SH, "")
.value("B_CPU_SPARC", cpu_platform::B_CPU_SPARC, "")
.value("B_CPU_RISC_V", cpu_platform::B_CPU_RISC_V, "")
.export_values();

py::enum_<cpu_vendor>(m, "cpu_vendor", "")
.value("B_CPU_VENDOR_UNKNOWN", cpu_vendor::B_CPU_VENDOR_UNKNOWN, "")
.value("B_CPU_VENDOR_AMD", cpu_vendor::B_CPU_VENDOR_AMD, "")
.value("B_CPU_VENDOR_CYRIX", cpu_vendor::B_CPU_VENDOR_CYRIX, "")
.value("B_CPU_VENDOR_IDT", cpu_vendor::B_CPU_VENDOR_IDT, "")
.value("B_CPU_VENDOR_INTEL", cpu_vendor::B_CPU_VENDOR_INTEL, "")
.value("B_CPU_VENDOR_NATIONAL_SEMICONDUCTOR", cpu_vendor::B_CPU_VENDOR_NATIONAL_SEMICONDUCTOR, "")
.value("B_CPU_VENDOR_RISE", cpu_vendor::B_CPU_VENDOR_RISE, "")
.value("B_CPU_VENDOR_TRANSMETA", cpu_vendor::B_CPU_VENDOR_TRANSMETA, "")
.value("B_CPU_VENDOR_VIA", cpu_vendor::B_CPU_VENDOR_VIA, "")
.value("B_CPU_VENDOR_IBM", cpu_vendor::B_CPU_VENDOR_IBM, "")
.value("B_CPU_VENDOR_MOTOROLA", cpu_vendor::B_CPU_VENDOR_MOTOROLA, "")
.value("B_CPU_VENDOR_NEC", cpu_vendor::B_CPU_VENDOR_NEC, "")
.value("B_CPU_VENDOR_HYGON", cpu_vendor::B_CPU_VENDOR_HYGON, "")
.value("B_CPU_VENDOR_SUN", cpu_vendor::B_CPU_VENDOR_SUN, "")
.value("B_CPU_VENDOR_FUJITSU", cpu_vendor::B_CPU_VENDOR_FUJITSU, "")
.export_values();
/*
m.attr("B_OBJECT_TYPE_FD") = py::cast(B_OBJECT_TYPE_FD);
m.attr("B_OBJECT_TYPE_SEMAPHORE") = py::cast(B_OBJECT_TYPE_SEMAPHORE);
m.attr("B_OBJECT_TYPE_PORT") = py::cast(B_OBJECT_TYPE_PORT);
m.attr("B_OBJECT_TYPE_THREAD") = py::cast(B_OBJECT_TYPE_THREAD);*/
m.attr("B_OBJECT_TYPE_FD") = 0;
m.attr("B_OBJECT_TYPE_SEMAPHORE") = 1;
m.attr("B_OBJECT_TYPE_PORT") = 2;
m.attr("B_OBJECT_TYPE_THREAD") = 3;

/*
m.attr("B_EVENT_READ") = py::cast(B_EVENT_READ);
m.attr("B_EVENT_WRITE") = py::cast(B_EVENT_WRITE);
m.attr("B_EVENT_ERROR") = py::cast(B_EVENT_ERROR);
m.attr("B_EVENT_PRIORITY_READ") = py::cast(B_EVENT_PRIORITY_READ);
m.attr("B_EVENT_PRIORITY_WRITE") = py::cast(B_EVENT_PRIORITY_WRITE);
m.attr("B_EVENT_HIGH_PRIORITY_READ") = py::cast(B_EVENT_HIGH_PRIORITY_READ);
m.attr("B_EVENT_HIGH_PRIORITY_WRITE") = py::cast(B_EVENT_HIGH_PRIORITY_WRITE);
m.attr("B_EVENT_DISCONNECTED") = py::cast(B_EVENT_DISCONNECTED);
m.attr("B_EVENT_ACQUIRE_SEMAPHORE") = py::cast(B_EVENT_ACQUIRE_SEMAPHORE);
m.attr("B_EVENT_INVALID") = py::cast(B_EVENT_INVALID);*/
m.attr("B_EVENT_READ") = 0x0001;
m.attr("B_EVENT_WRITE") = 0x0002;
m.attr("B_EVENT_ERROR") = 0x0004;
m.attr("B_EVENT_PRIORITY_READ") = 0x0008;
m.attr("B_EVENT_PRIORITY_WRITE") = 0x0010;
m.attr("B_EVENT_HIGH_PRIORITY_READ") = 0x0020;
m.attr("B_EVENT_HIGH_PRIORITY_WRITE") = 0x0040;
m.attr("B_EVENT_DISCONNECTED") = 0x0080;
m.attr("B_EVENT_ACQUIRE_SEMAPHORE") = 0x0001;
m.attr("B_EVENT_INVALID") = 0x1000;


py::class_<area_info>(m, "area_info")
.def(py::init(), "")
.def_readwrite("area", &area_info::area, "")
//.def_readwrite("name", &area_info::name, "")
.def_property("name", &get_area_info_name, &set_area_info_name, "")
.def_readwrite("size", &area_info::size, "")
.def_readwrite("lock", &area_info::lock, "")
.def_readwrite("protection", &area_info::protection, "")
.def_readwrite("team", &area_info::team, "")
.def_readwrite("ram_size", &area_info::ram_size, "")
.def_readwrite("copy_count", &area_info::copy_count, "")
.def_readwrite("in_count", &area_info::in_count, "")
.def_readwrite("out_count", &area_info::out_count, "")
.def_readwrite("address", &area_info::address, "")
;

py::class_<port_info>(m, "port_info")
.def(py::init(), "")
.def_readwrite("port", &port_info::port, "")
.def_readwrite("team", &port_info::team, "")
//.def_readwrite("name", &port_info::name, "")
.def_property("name", &get_port_info_name, &set_port_info_name, "") 
.def_readwrite("capacity", &port_info::capacity, "")
.def_readwrite("queue_count", &port_info::queue_count, "")
.def_readwrite("total_count", &port_info::total_count, "")
;

py::class_<port_message_info>(m, "port_message_info")
.def(py::init(), "")
.def_readwrite("size", &port_message_info::size, "")
.def_readwrite("sender", &port_message_info::sender, "")
.def_readwrite("sender_group", &port_message_info::sender_group, "")
.def_readwrite("sender_team", &port_message_info::sender_team, "")
;

py::class_<sem_info>(m, "sem_info")
.def(py::init(), "")
.def_readwrite("sem", &sem_info::sem, "")
.def_readwrite("team", &sem_info::team, "")
//.def_readwrite("name", &sem_info::name, "")
.def_property("name", &get_sem_info_name, &set_sem_info_name, "")
.def_readwrite("count", &sem_info::count, "")
.def_readwrite("latest_holder", &sem_info::latest_holder, "")
;

py::class_<team_info>(m, "team_info")
.def(py::init(), "")
.def_readwrite("team", &team_info::team, "")
.def_readwrite("thread_count", &team_info::thread_count, "")
.def_readwrite("image_count", &team_info::image_count, "")
.def_readwrite("area_count", &team_info::area_count, "")
.def_readwrite("debugger_nub_thread", &team_info::debugger_nub_thread, "")
.def_readwrite("debugger_nub_port", &team_info::debugger_nub_port, "")
.def_readwrite("argc", &team_info::argc, "")
//.def_readwrite("args", &team_info::args, "")
.def_property("args", &get_team_info_args, &set_team_info_args, "") 
.def_readwrite("uid", &team_info::uid, "")
.def_readwrite("gid", &team_info::gid, "")
;

py::class_<team_usage_info>(m, "team_usage_info")
.def(py::init(), "")
.def_readwrite("user_time", &team_usage_info::user_time, "")
.def_readwrite("kernel_time", &team_usage_info::kernel_time, "")
;

py::class_<thread_info>(m, "thread_info")
.def(py::init(), "")
.def_readwrite("thread", &thread_info::thread, "")
.def_readwrite("team", &thread_info::team, "")
.def_readonly("name", &thread_info::name, "")
.def_readwrite("state", &thread_info::state, "")
.def_readwrite("priority", &thread_info::priority, "")
.def_readwrite("sem", &thread_info::sem, "")
.def_readwrite("user_time", &thread_info::user_time, "")
.def_readwrite("kernel_time", &thread_info::kernel_time, "")
.def_readwrite("stack_base", &thread_info::stack_base, "")
.def_readwrite("stack_end", &thread_info::stack_end, "")
;

py::class_<cpu_info>(m, "cpu_info")
.def(py::init(), "")
.def_readwrite("active_time", &cpu_info::active_time, "")
.def_readwrite("enabled", &cpu_info::enabled, "")
.def_readwrite("current_frequency", &cpu_info::current_frequency, "")
;

py::class_<system_info>(m, "system_info")
.def(py::init(), "")
.def_readwrite("boot_time", &system_info::boot_time, "")
.def_readwrite("cpu_count", &system_info::cpu_count, "")
.def_readwrite("max_pages", &system_info::max_pages, "")
.def_readwrite("used_pages", &system_info::used_pages, "")
.def_readwrite("cached_pages", &system_info::cached_pages, "")
.def_readwrite("block_cache_pages", &system_info::block_cache_pages, "")
.def_readwrite("ignored_pages", &system_info::ignored_pages, "")
.def_readwrite("needed_memory", &system_info::needed_memory, "")
.def_readwrite("free_memory", &system_info::free_memory, "")
.def_readwrite("max_swap_pages", &system_info::max_swap_pages, "")
.def_readwrite("free_swap_pages", &system_info::free_swap_pages, "")
.def_readwrite("page_faults", &system_info::page_faults, "")
.def_readwrite("max_sems", &system_info::max_sems, "")
.def_readwrite("used_sems", &system_info::used_sems, "")
.def_readwrite("max_ports", &system_info::max_ports, "")
.def_readwrite("used_ports", &system_info::used_ports, "")
.def_readwrite("max_threads", &system_info::max_threads, "")
.def_readwrite("used_threads", &system_info::used_threads, "")
.def_readwrite("max_teams", &system_info::max_teams, "")
.def_readwrite("used_teams", &system_info::used_teams, "")
.def_readonly("kernel_name", &system_info::kernel_name, "")
.def_readonly("kernel_build_date", &system_info::kernel_build_date, "")
.def_readonly("kernel_build_time", &system_info::kernel_build_time, "")
.def_readwrite("kernel_version", &system_info::kernel_version, "")
.def_readwrite("abi", &system_info::abi, "")
;

py::class_<cpu_topology_root_info>(m, "cpu_topology_root_info")
.def(py::init(), "")
.def_readwrite("platform", &cpu_topology_root_info::platform, "")
;

py::class_<cpu_topology_package_info>(m, "cpu_topology_package_info")
.def(py::init(), "")
.def_readwrite("vendor", &cpu_topology_package_info::vendor, "")
.def_readwrite("cache_line_size", &cpu_topology_package_info::cache_line_size, "")
;

py::class_<cpu_topology_core_info>(m, "cpu_topology_core_info")
.def(py::init(), "")
.def_readwrite("model", &cpu_topology_core_info::model, "")
.def_readwrite("default_frequency", &cpu_topology_core_info::default_frequency, "")
;
/*
py::class_<union >(m, "union ")
.def_readwrite("root", &union ::root, "")
.def_readwrite("package", &union ::package, "")
.def_readwrite("core", &union ::core, "")
;
*/
py::class_<cpu_topology_node_info>(m, "cpu_topology_node_info")
.def(py::init(), "")
.def_readwrite("id", &cpu_topology_node_info::id, "")
.def_readwrite("type", &cpu_topology_node_info::type, "")
.def_readwrite("level", &cpu_topology_node_info::level, "")
//.def_readwrite("data", &cpu_topology_node_info::data, "")
.def("get_root", [](cpu_topology_node_info& self) -> cpu_topology_root_info& {
            return self.data.root;
        }, py::return_value_policy::reference)
.def("get_package", [](cpu_topology_node_info& self) -> cpu_topology_package_info& {
            return self.data.package;
        }, py::return_value_policy::reference)
.def("get_core", [](cpu_topology_node_info& self) -> cpu_topology_core_info& {
            return self.data.core;
        }, py::return_value_policy::reference);
;
/*
py::class_<>(m, "")
.def_readwrite("eax", &::eax, "")
.def_readwrite("ebx", &::ebx, "")
.def_readwrite("edx", &::edx, "")
.def_readwrite("ecx", &::ecx, "")
;*/

py::class_<cpuid_info>(m, "cpuid_info")
.def(py::init(), "")
.def_readwrite("eax_0", &cpuid_info::eax_0, "")
.def_readwrite("eax_1", &cpuid_info::eax_1, "")
.def_readwrite("eax_2", &cpuid_info::eax_2, "")
.def_readwrite("eax_3", &cpuid_info::eax_3, "")
.def_readonly("as_chars", &cpuid_info::as_chars, "")
//def property readonly?
.def("get_reg_eax",[](cpuid_info& self) -> uint32 {
	return self.regs.eax;
}, py::return_value_policy::reference)
.def("get_reg_ebx",[](cpuid_info& self) -> uint32 {
	return self.regs.ebx;
}, py::return_value_policy::reference)
.def("get_reg_edx",[](cpuid_info& self) -> uint32 {
	return self.regs.edx;
}, py::return_value_policy::reference)
.def("get_reg_ecx",[](cpuid_info& self) -> uint32 {
	return self.regs.ecx;
}, py::return_value_policy::reference)
//.def_readwrite("regs", &cpuid_info::regs, "")
;

py::class_<object_wait_info>(m, "object_wait_info")
.def(py::init(), "")
.def_readwrite("object", &object_wait_info::object, "")
.def_readwrite("type", &object_wait_info::type, "")
.def_readwrite("events", &object_wait_info::events, "")
;

//m.def("create_area", &create_area, "", py::arg("name"), py::arg("startAddress"), py::arg("addressSpec"), py::arg("size"), py::arg("lock"), py::arg("protection"));
m.def("create_area", &create_area_wrapper, "", py::arg("name"), py::arg("startAddress"), py::arg("addressSpec"), py::arg("size"), py::arg("lock"), py::arg("protection")); //in python declare "start_address = None"

//m.def("clone_area", &clone_area, "", py::arg("name"), py::arg("destAddress"), py::arg("addressSpec"), py::arg("protection"), py::arg("source"));
m.def("clone_area", &clone_area_wrapper, "", py::arg("name"), py::arg("destAddress"), py::arg("addressSpec"), py::arg("protection"), py::arg("source"));

m.def("find_area", &find_area, "", py::arg("name"));

m.def("area_for", &area_for, "", py::arg("address"));

m.def("delete_area", &delete_area, "", py::arg("id"));

m.def("resize_area", &resize_area, "", py::arg("id"), py::arg("newSize"));

m.def("set_area_protection", &set_area_protection, "", py::arg("id"), py::arg("newProtection"));

m.def("_get_area_info", &_get_area_info, "", py::arg("id"), py::arg("areaInfo"), py::arg("size"));

m.def("_get_next_area_info", &_get_next_area_info, "", py::arg("team"), py::arg("cookie"), py::arg("areaInfo"), py::arg("size"));

m.def("create_port", &create_port, "", py::arg("capacity"), py::arg("name"));

m.def("find_port", &find_port, "", py::arg("name"));

m.def("read_port", &read_port, "", py::arg("port"), py::arg("code"), py::arg("buffer"), py::arg("bufferSize"));

m.def("read_port_etc", &read_port_etc, "", py::arg("port"), py::arg("code"), py::arg("buffer"), py::arg("bufferSize"), py::arg("flags"), py::arg("timeout"));

m.def("write_port", &write_port, "", py::arg("port"), py::arg("code"), py::arg("buffer"), py::arg("bufferSize"));

m.def("write_port_etc", &write_port_etc, "", py::arg("port"), py::arg("code"), py::arg("buffer"), py::arg("bufferSize"), py::arg("flags"), py::arg("timeout"));

m.def("close_port", &close_port, "", py::arg("port"));

m.def("delete_port", &delete_port, "", py::arg("port"));

m.def("port_buffer_size", &port_buffer_size, "", py::arg("port"));

m.def("port_buffer_size_etc", &port_buffer_size_etc, "", py::arg("port"), py::arg("flags"), py::arg("timeout"));

m.def("port_count", &port_count, "", py::arg("port"));

m.def("set_port_owner", &set_port_owner, "", py::arg("port"), py::arg("team"));

m.def("_get_port_info", &_get_port_info, "", py::arg("port"), py::arg("portInfo"), py::arg("portInfoSize"));

m.def("_get_next_port_info", &_get_next_port_info, "", py::arg("team"), py::arg("cookie"), py::arg("portInfo"), py::arg("portInfoSize"));

m.def("_get_port_message_info_etc", &_get_port_message_info_etc, "", py::arg("port"), py::arg("info"), py::arg("infoSize"), py::arg("flags"), py::arg("timeout"));

m.def("create_sem", &create_sem, "", py::arg("count"), py::arg("name"));

m.def("delete_sem", &delete_sem, "", py::arg("id"));

m.def("acquire_sem", &acquire_sem, "", py::arg("id"));

m.def("acquire_sem_etc", &acquire_sem_etc, "", py::arg("id"), py::arg("count"), py::arg("flags"), py::arg("timeout"));

m.def("release_sem", &release_sem, "", py::arg("id"));

m.def("release_sem_etc", &release_sem_etc, "", py::arg("id"), py::arg("count"), py::arg("flags"));

m.def("switch_sem", &switch_sem, "", py::arg("semToBeReleased"), py::arg("id"));

m.def("switch_sem_etc", &switch_sem_etc, "", py::arg("semToBeReleased"), py::arg("id"), py::arg("count"), py::arg("flags"), py::arg("timeout"));

m.def("get_sem_count", &get_sem_count, "", py::arg("id"), py::arg("threadCount"));

m.def("set_sem_owner", &set_sem_owner, "", py::arg("id"), py::arg("team"));

m.def("_get_sem_info", &_get_sem_info, "", py::arg("id"), py::arg("info"), py::arg("infoSize"));

m.def("_get_next_sem_info", &_get_next_sem_info, "", py::arg("team"), py::arg("cookie"), py::arg("info"), py::arg("infoSize"));

m.def("kill_team", &kill_team, "", py::arg("team"));

m.def("_get_team_info", &_get_team_info, "", py::arg("id"), py::arg("info"), py::arg("size"));

m.def("_get_next_team_info", &_get_next_team_info, "", py::arg("cookie"), py::arg("info"), py::arg("size"));

m.def("_get_team_usage_info", &_get_team_usage_info, "", py::arg("team"), py::arg("who"), py::arg("info"), py::arg("size"));

m.def("spawn_thread", &spawn_thread, "", py::arg(""), py::arg("name"), py::arg("priority"), py::arg("data"));

m.def("kill_thread", &kill_thread, "", py::arg("thread"));

m.def("resume_thread", &resume_thread, "", py::arg("thread"));

m.def("suspend_thread", &suspend_thread, "", py::arg("thread"));

m.def("rename_thread", &rename_thread, "", py::arg("thread"), py::arg("newName"));

m.def("set_thread_priority", &set_thread_priority, "", py::arg("thread"), py::arg("newPriority"));

m.def("exit_thread", &exit_thread, "", py::arg("status"));

m.def("wait_for_thread", &wait_for_thread, "", py::arg("thread"), py::arg("returnValue"));

m.def("wait_for_thread_etc", &wait_for_thread_etc, "", py::arg("id"), py::arg("flags"), py::arg("timeout"), py::arg("_returnCode"));

m.def("on_exit_thread", &on_exit_thread, "", py::arg(""), py::arg("data"));

m.def("find_thread", &find_thread, "", py::arg("name"));

m.def("send_data", &send_data, "", py::arg("thread"), py::arg("code"), py::arg("buffer"), py::arg("bufferSize"));

m.def("receive_data", &receive_data, "", py::arg("sender"), py::arg("buffer"), py::arg("bufferSize"));

m.def("has_data", &has_data, "", py::arg("thread"));

m.def("snooze", &snooze, "", py::arg("amount"));

m.def("snooze_etc", &snooze_etc, "", py::arg("amount"), py::arg("timeBase"), py::arg("flags"));

m.def("snooze_until", &snooze_until, "", py::arg("time"), py::arg("timeBase"));

m.def("_get_thread_info", &_get_thread_info, "", py::arg("id"), py::arg("info"), py::arg("size"));

m.def("_get_next_thread_info", &_get_next_thread_info, "", py::arg("team"), py::arg("cookie"), py::arg("info"), py::arg("size"));

//m.def("get_pthread_thread_id", &get_pthread_thread_id, "", py::arg("thread"));

//m.def("real_time_clock", &real_time_clock, "", py::arg(""));
m.def("real_time_clock", &real_time_clock_wrapper, "");

m.def("set_real_time_clock", &set_real_time_clock, "", py::arg("secsSinceJan1st1970"));

//m.def("real_time_clock_usecs", &real_time_clock_usecs, "", py::arg(""));
m.def("real_time_clock_usecs", &real_time_clock_usecs_wrapper, "");

//m.def("system_time", &system_time, "", py::arg(""));
m.def("system_time", &system_time_wrapper, "");

//m.def("system_time_nsecs", &system_time_nsecs, "", py::arg(""));
m.def("system_time_nsecs", &system_time_nsecs_wrapper, "");

m.def("set_alarm", &set_alarm, "", py::arg("when"), py::arg("flags"));

m.def("debugger", &debugger, "", py::arg("message"));

m.def("disable_debugger", &disable_debugger, "", py::arg("state"));

//m.def("debug_printf", &debug_printf, "", py::arg("format"));

m.def("debug_vprintf", &debug_vprintf, "", py::arg("format"), py::arg("args"));

//m.def("ktrace_printf", &ktrace_printf, "", py::arg("format"));

m.def("ktrace_vprintf", &ktrace_vprintf, "", py::arg("format"), py::arg("args"));

m.def("get_system_info", &get_system_info, "", py::arg("info"));

m.def("_get_cpu_info_etc", &_get_cpu_info_etc, "", py::arg("firstCPU"), py::arg("cpuCount"), py::arg("info"), py::arg("size"));

m.def("get_cpu_topology_info", &get_cpu_topology_info, "", py::arg("topologyInfos"), py::arg("topologyInfoCount"));

m.def("get_cpuid", &get_cpuid, "", py::arg("info"), py::arg("eaxRegister"), py::arg("cpuNum"));

//m.def("is_computer_on", &is_computer_on, "", py::arg(""));
m.def("is_computer_on", &is_computer_on_wrapper, "");

//m.def("is_computer_on_fire", &is_computer_on_fire, "", py::arg(""));
m.def("is_computer_on_fire", &is_computer_on_fire_wrapper, "");

m.def("send_signal", &send_signal, "", py::arg("threadID"), py::arg("signal"));

m.def("set_signal_stack", &set_signal_stack, "", py::arg("base"), py::arg("size"));

m.def("wait_for_objects", &wait_for_objects, "", py::arg("infos"), py::arg("numInfos"));

m.def("wait_for_objects_etc", &wait_for_objects_etc, "", py::arg("infos"), py::arg("numInfos"), py::arg("flags"), py::arg("timeout"));

}
