// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifndef MYDOCKER_CGROUPS_H
#define MYDOCKER_CGROUPS_H

#include <string>

#define CGROUP_PATH "/sys/fs/cgroup/"

constexpr size_t convert_to_mb(size_t size) { return size * 1024 * 1024; }

void create_cgroup(const std::string &cgroup_name);
void set_cpu_limit(const std::string &cgroup_name, double percentage);
void set_pids_limit(const std::string &cgroup_name, size_t pids_number);
void set_memory_limit_mb(const std::string &cgroup_name, size_t megabytes);

#endif //MYDOCKER_CGROUPS_H
