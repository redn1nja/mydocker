// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <wait.h>
#include <filesystem>
#include <unistd.h>
#include "mycontainer.h"
#include "create_namespace.h"
#include "mount_namespaces.h"
#include "cgroups.h"
#include "bind_mount.h"
#include "setup_root.h"


std::string MycontainerConfig::root = "/opt/mydocker/";


void Mycontainer::start() {
    config.set_err(dup(STDERR_FILENO));
    config.set_in(dup(STDIN_FILENO));
    config.set_out(dup(STDOUT_FILENO));
    switch (pid = create_process_in_new_ns(&Mycontainer::child_func,
                                           STACK_SIZE,
                                           config.namespace_flags | SIGCHLD,
                                           this)) {
        case -1:
            std::cerr << "failed to create container" << std::endl;
            exit(EXIT_FAILURE);
        case 0:
            break;
        default:

            //TODO do start stuff

//            signal(SIGCHLD, sigchld_handler);
//            if (close(config.pipefd_in[0]) != 0) {
//                std::cerr << "start Mycontainer: cannot close file descriptor " << config.pipefd_in[0] << std::endl;
//            }
//            if (close(config.pipefd_out[1]) != 0) {
//                std::cerr << "start Mycontainer: cannot close file descriptor " << config.pipefd_out[1] << std::endl;
//            }
//            if (close(config.pipefd_err[1]) != 0) {
//                std::cerr << "start Mycontainer: cannot close file descriptor " << config.pipefd_err[1] << std::endl;
//            }
//            wait(&status);
//            std::cout << "exited with status " << (status >> 8) << std::endl;
            break;
    }
}


void Mycontainer::run() {
    std::cout << "running" << std::endl;

    create_cgroup(config.cgroup_name);
    set_pids_limit("test", config.pids_limit);
    set_memory_limit_mb("test", config.memory_limit_mb);
    set_cpu_limit("test", config.cpu_proportion);
    mount_namespace(MycontainerConfig::root, args.data());

    //TODO do run stuff

//    std::string mnt = "mnt";
//    auto mountpoint = create_path(MycontainerConfig::root, mnt);
//    mount_root();
//    std::cout << mountpoint << std::endl;
//    create_mountpoint(mountpoint);
//    std::cout << "mountpoint " << mountpoint << std::endl;
//    for (auto &mount: config.mount_points) {
//        auto mount_name = create_path(mountpoint, mount);
//        std::cout << "mounting " << mount << std::endl;
//        create_mountpoint(mount_name);
//        if (mount_dir(mount, mount_name) != 0) {
//            std::cerr << "failed to mount " << mount_name << std::endl;
//        }
//    }
//    if (setup_root(MycontainerConfig::root.c_str()) != 0) {
//        std::cerr << "failed to chroot" << std::endl;
//    }
////    std::cout<<"executing"<<std::endl;
//    if (execvp(name.c_str(), args.data()) != 0) {
//        std::cerr << "failed to run" << std::endl;
//        exit(EXIT_FAILURE);
//    }
}


int Mycontainer::child_func(void *arg) {
    auto mycontainer = static_cast<Mycontainer *>(arg);
    mycontainer->run();
    return 0;
}

