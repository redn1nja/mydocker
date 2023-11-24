#include <fstream>
#include <iostream>
#include <filesystem>
#include <unistd.h>
#include "cgroups.h"

void create_cgroup(const std::string &cgroup_name) {
    std::string cgroup_path = CGROUP_PATH + cgroup_name;
    try {
        std::filesystem::create_directory(cgroup_path);
        std::cout << "Directory created successfully.\n";
    }
    catch (const std::filesystem::filesystem_error &e) {
        std::cerr << "Failed to create directory: " << e.what() << '\n';
    }

    //not sure about this part
    pid_t pid = getpid();
    std::cout<<pid<<std::endl;
    std::ofstream procs_file(cgroup_path + "/cgroup.procs");
    procs_file << pid;
}

void set_cpu_limit(const std::string& cgroup_name, double percentage) {

}

void set_pids_limit(const std::string& cgroup_name, size_t pids_number) {

}

void set_memory_limit_mb(const std::string& cgroup_name, size_t megabytes) { }