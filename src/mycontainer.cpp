// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "mycontainer.h"
#include "create_namespace.h"
#include <iostream>
#include <wait.h>

#include <filesystem>
#include "cgroups.h"
#include "bind_mount.h"
#include "setup_root.h"

std::vector<std::string> MycontainerConfig::root_mount_points = {"/usr", "/lib", "/bin", "/lib64", "/proc"};

std::string create_path(const std::string &root, const std::string &path) {
    auto without_slash = path[0] == '/' ? path.substr(1) : path;
    auto pathh = std::filesystem::path(root) / without_slash;
    return pathh.string();
}

void Mycontainer::mount_root() const {
    std::cout << config.root << std::endl;
    for (auto &mount: MycontainerConfig::root_mount_points) {
        auto mount_name = create_path(config.root, mount);
        std::cout << "mounting " << mount_name << std::endl;
        create_mountpoint(mount_name);
        if (mount_dir(mount, mount_name) != 0) {
            std::cerr << "failed to mount " << mount_name << std::endl;
        }
    }
}

constexpr size_t STACK_SIZE = 1024 * 1024;

int Mycontainer::child_func(void *arg) {
    auto mycontainer = static_cast<Mycontainer *>(arg);
    mycontainer->run();
    return 0;
}

void Mycontainer::run() {
    if (pid != -1) {
        return;
    }
    std::cout << pid << std::endl;
    std::cout << "running" << std::endl;
    create_cgroup("test");
    set_pids_limit("test", 10);
    set_memory_limit_mb("test", 100);
    set_cpu_limit("test", 5);
    std::string mnt = "mnt";
    auto mountpoint = create_path(config.root, mnt);
    mount_root();
    std::cout << mountpoint << std::endl;
    create_mountpoint(mountpoint);
    std::cout << "mountpoint " << mountpoint << std::endl;
    for (auto &mount: config.mount_points) {
        auto mount_name = create_path(mountpoint, mount);
        std::cout << "mounting " << mount << std::endl;
        create_mountpoint(mount_name);
        if (mount_dir(mount, mount_name) != 0) {
            std::cerr << "failed to mount " << mount_name << std::endl;
        }
    }
    if (setup_root(config.root.c_str()) != 0) {
        std::cerr << "failed to chroot" << std::endl;
    }
    if (execvp(name.c_str(), args.data()) != 0) {
        std::cerr << "failed to run" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Mycontainer::start() {
    switch (pid = create_process_in_new_ns(&Mycontainer::child_func, STACK_SIZE, CLONE_NEWNS | SIGCHLD, this)) {
        case -1:
            std::cerr << "failed to create container" << std::endl;
            exit(EXIT_FAILURE);
        case 0:
            break;
        default:
            wait(&status);
            std::cout << "exited with status " << (status >> 8) << std::endl;
            std::string mnt = "mnt";
            auto mountpoint = create_path(config.root, mnt);
//            mount_root();
            for (auto &mount: config.mount_points) {
                auto mount_name = create_path(mountpoint, mount);
                std::cout << "umounting " << mount_name << std::endl;
                if (unmount_dir(mount_name) != 0) {
                    std::cerr << "failed to umount " << mount_name << std::endl;
                }
            }
            for (auto &mount: MycontainerConfig::root_mount_points) {
                auto mount_name = create_path(config.root, mount);
                std::cout << "umounting " << mount_name << std::endl;
                if (unmount_dir(mount_name) != 0) {
                    std::cerr << "failed to umount " << mount_name << std::endl;
                }
            }
            break;


    }
}

