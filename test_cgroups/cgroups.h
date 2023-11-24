#ifndef MYDOCKER_CGROUPS_H
#define MYDOCKER_CGROUPS_H
#include <string>

#define CGROUP_PATH "/sys/fs/cgroup/"

void create_cgroup(const std::string& cgroup_name);
void set_cpu_limit(const std::string& cgroup_name, double percentage);
void set_pids_limit(const std::string& cgroup_name, size_t pids_number);
void set_memory_limit_mb(const std::string& cgroup_name, size_t megabytes);
#endif //MYDOCKER_CGROUPS_H
