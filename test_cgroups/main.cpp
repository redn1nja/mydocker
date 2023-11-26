// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>

#include "cgroups.h"

int main() {
    // verify that we run under superuser (should == 0)
    std::cout << "UID: " << getuid() << std::endl;
    std::cout << "EUID: " << geteuid() << std::endl;
    std::string cgroup_name = "my_cgroup9";
    create_cgroup(cgroup_name);
    set_cpu_limit(cgroup_name, 50);
    // set_pids_limit(cgroup_name, 6);
    set_memory_limit_mb(cgroup_name, 7);
    // should run some demanding stuff
    return 0;
}
