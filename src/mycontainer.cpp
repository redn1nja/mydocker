// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "mycontainer.h"
#include "create_namespace.h"
#include "mount_namespaces.h"
#include <iostream>
#include <wait.h>

#include <filesystem>
#include "cgroups.h"
#include "bind_mount.h"
#include "setup_root.h"
#include <unistd.h>
std::string MycontainerConfig::root = "/opt/mydocker/";

Mycontainer::Mycontainer(const std::string &dockerfile_path) {
    config = MycontainerConfig(dockerfile_path);
    name = config.name;
    for (auto& arg: config.args){
        args.emplace_back(arg.data());
    }
}


int Mycontainer::child_func(void *arg) {
    auto mycontainer = static_cast<Mycontainer *>(arg);
    mycontainer->run();
    return 0;
}


void Mycontainer::run() {
//    if (close(config.pipefd_in[1]) != 0) {
//        std::cerr << "start Mycontainer: cannot close file descriptor " << config.pipefd_in[1] << std::endl;
//    }
//    if (close(config.pipefd_out[0]) != 0) {
//        std::cerr << "start Mycontainer: cannot close file descriptor " << config.pipefd_out[0] << std::endl;
//    }
//    if (close(config.pipefd_err[0]) != 0) {
//        std::cerr << "start Mycontainer: cannot close file descriptor " << config.pipefd_err[0] << std::endl;
//    }
//    if (close(config.pipefd_in[0]) != 0) {
//        std::cerr << "start Mycontainer: cannot close file descriptor " << config.pipefd_in[0] << std::endl;
//    }
//    if (close(config.pipefd_out[1]) != 0) {
//        std::cerr << "start Mycontainer: cannot close file descriptor " << config.pipefd_out[1] << std::endl;
//    }
//    if (close(config.pipefd_err[1]) != 0) {
//        std::cerr << "start Mycontainer: cannot close file descriptor " << config.pipefd_err[1] << std::endl;
//    }
//
//    std::cout << pid << std::endl;
//    if (dup2(config.pipefd_in[0], STDIN_FILENO)!=0) {
//        dprintf(fd, "start Mycontainer: cannot dup2 STDIN_FILENO %s \n", strerror(errno));
//    }
//    if (dup2(config.pipefd_out[1], STDOUT_FILENO)!=0) {
//        dprintf(fd, "start Mycontainer: cannot dup2 STDOUT_FILENO %s \n", strerror(errno));
//    }
//    if(dup2(config.pipefd_err[1], STDERR_FILENO)!=0) {
//        dprintf(fd, "start Mycontainer: cannot dup2 STDERR_FILENO %s \n", strerror(errno));
//    }
    std::cout << "running" << std::endl;
    create_cgroup("test");
    set_pids_limit("test", 10);
    set_memory_limit_mb("test", 100);
    set_cpu_limit("test", 5);
    std::cout<<MycontainerConfig::root<<std::endl;
    std::cout<<args.size()<<std::endl;
    mount_namespace(MycontainerConfig::root, args.data());

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


void Mycontainer::start() {
    config.set_err(dup(STDERR_FILENO));
    config.set_in(dup(STDIN_FILENO));
    config.set_out(dup(STDOUT_FILENO));
    switch (pid = create_process_in_new_ns(&Mycontainer::child_func, STACK_SIZE, config.namespace_flags | SIGCHLD,
                                           this)) {
        case -1:
            std::cerr << "failed to create container" << std::endl;
            exit(EXIT_FAILURE);
        case 0:
            break;
        default:
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

