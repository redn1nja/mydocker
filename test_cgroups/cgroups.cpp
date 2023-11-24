// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <fstream>
#include <iostream>
#include <unistd.h>
#include <filesystem>

#include "cgroups.h"

void create_cgroup(const std::string &cgroup_name) {
    std::string cgroup_folder_path = CGROUP_PATH + cgroup_name;
    try {
        std::filesystem::create_directory(cgroup_folder_path);
        std::cout << "Directory created successfully.\n";
    }
    catch (const std::filesystem::filesystem_error &e) {
        std::cerr << "Failed to create directory: " << e.what() << '\n';
        exit(EXIT_FAILURE); //TODO: change to throwing exception
    }

    //not sure about this part
    pid_t pid = getpid();
    std::cout << "pid: " << " " << pid << std::endl;
    std::ofstream procs_file(cgroup_folder_path + "/cgroup.procs");
    if (!procs_file.is_open()) {
        std::cerr << "Failed to open cgroup.procs file for cgroup " << cgroup_name << "\n";
        exit(EXIT_FAILURE);
    }
    procs_file << pid;
    procs_file.close();
}

void set_cpu_limit(const std::string &cgroup_name, double percentage) {

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

void set_memory_limit_mb(const std::string &cgroup_name, size_t megabytes) {}