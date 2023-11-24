// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <fstream>
#include <sstream>

#include "cgroups.h"

int main() {
    std::string cgroup_name = "my_cgroup";
    create_cgroup(cgroup_name);
    // set_cpu_limit(cgroup_name, 50);
    set_pids_limit(cgroup_name, 5);
    // set_memory_limit_mb(cgroup_name, 5);
    // should run some demanding stuff
    return 0;
}
