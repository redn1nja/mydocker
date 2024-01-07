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
            break;
    }
}


void Mycontainer::run() {

    create_cgroup(config.cgroup_name);
    set_pids_limit("test", config.pids_limit);
    set_memory_limit_mb("test", config.memory_limit_mb);
    set_cpu_limit("test", config.cpu_proportion);
    std::string image_path = IMAGE_PATH;
    std::string copy_path = root_dir + "/rootfs.img";
    std::filesystem::copy(image_path, copy_path, std::filesystem::copy_options::skip_existing);
    mount_namespace(root_dir, args.data(), config.mount_points, copy_path);

    //TODO do run stuff

}


int Mycontainer::child_func(void *arg) {
    auto mycontainer = static_cast<Mycontainer *>(arg);
    mycontainer->run();
    return 0;
}

