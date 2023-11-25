// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <fstream>
#include <iostream>
#include <unistd.h>
#include <filesystem>
#include <sys/stat.h>

#include "cgroups.h"

void create_cgroup(const std::string &cgroup_name) {
    std::string cgroup_folder_path = CGROUP_PATH + cgroup_name;

    if (mkdir(cgroup_folder_path.c_str(), 0755) != 0) {
        std::cerr << "Failed to create cgroup " << cgroup_name << "\n";
    }
    else {
        std::cout << "Directory created successfully."<<std::endl;
    }

    pid_t pid = getpid();
    std::cout << "pid: " << " " << pid << std::endl;
    std::ofstream procs_file(cgroup_folder_path + "/cgroup.procs");
    if (!procs_file.is_open()) {
        std::cerr << "Failed to open cgroup.procs file for cgroup " << cgroup_name << "\n";
        exit(EXIT_FAILURE); //TODO: change to throwing exception
    }
    procs_file << pid;
    procs_file.close();
}

void add_cpu_controllers(const std::string &cgroup_name) {
    std::string cgroup_folder_path = CGROUP_PATH;
    std::ofstream cgroup_child_controllers_file(cgroup_folder_path + "/cgroup.subtree_control");

    if (!cgroup_child_controllers_file.is_open()) {
        std::cerr << "Failed to open cgroup.subtree_control file for cgroup " << cgroup_name << "\n";
        exit(EXIT_FAILURE);
    }
    cgroup_child_controllers_file << " cpu";
    cgroup_child_controllers_file << " cpuset";
    // cgroup_child_controllers_file << " io";
    // cgroup_child_controllers_file << " rdma";
    cgroup_child_controllers_file.close();
}

void set_cpu_limit(const std::string &cgroup_name, double proportion) {
    // proportion can be in the range [1, 10000].
    // doesn't make sense if we are the only child
    add_cpu_controllers(cgroup_name);
    std::string cgroup_folder_path = CGROUP_PATH + cgroup_name;
    std::ofstream cpu_weight_file(cgroup_folder_path + "/cpu.weight");

    if (!cpu_weight_file.is_open()) {
        std::cerr << "Failed to open cpu.weight file for cgroup " << cgroup_name << "\n";
        exit(EXIT_FAILURE);
    }
    cpu_weight_file << proportion;
    cpu_weight_file.close();
}

void set_pids_limit(const std::string &cgroup_name, size_t pids_number) {
    std::string cgroup_folder_path = CGROUP_PATH + cgroup_name;
    std::ofstream pids_max_file(cgroup_folder_path + "/pids.max");

    if (!pids_max_file.is_open()) {
        std::cerr << "Failed to open pids.max file for cgroup " << cgroup_name << "\n";
        exit(EXIT_FAILURE);
    }
    pids_max_file << pids_number;
    pids_max_file.close();
}

void set_memory_limit_mb(const std::string &cgroup_name, size_t megabytes) {
    std::string cgroup_folder_path = CGROUP_PATH + cgroup_name;
    std::ofstream memory_limit_file(cgroup_folder_path + "/memory.max");
    if (!memory_limit_file.is_open()) {
        std::cerr << "Failed to open memory.max file for cgroup " << cgroup_name << "\n";
        exit(EXIT_FAILURE);
    }
    memory_limit_file << convert_to_mb(megabytes);
    memory_limit_file.close();
}