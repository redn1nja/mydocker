// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <wait.h>
#include <filesystem>
#include <unistd.h>
#include <sys/stat.h>
#include <err.h>
#include <linux/loop.h>
#include "mycontainer.h"
#include "create_namespace.h"
#include "mount_namespaces.h"
#include "cgroups.h"
#include "bind_mount.h"
#include "setup_root.h"


std::string MycontainerConfig::root = "/opt/mydocker/";


void Mycontainer::start() {
    switch (pid = create_process_in_new_ns(&Mycontainer::child_func,
                                           STACK_SIZE,
                                           config.namespace_flags | SIGCHLD,
                                           this)) {
        case -1:
            std::cerr << "failed to create container" << std::endl;
            exit(EXIT_FAILURE);
        default:
            close(sockfd[0]);
            break;
    }
}


void Mycontainer::run() {
    create_cgroup(id);
    set_pids_limit(id, config.pids_limit);
    set_memory_limit_mb(id, config.memory_limit_mb);
    set_cpu_limit(id, config.cpu_proportion);
    std::string image_path = IMAGE_PATH;
    std::string copy_path = root_dir + "/rootfs.img";
    std::filesystem::copy(image_path, copy_path, std::filesystem::copy_options::skip_existing);
    mount_namespace(root_dir, copy_path);

}


int Mycontainer::child_func(void *arg) {
    auto my_container = static_cast<Mycontainer *>(arg);
    if(dup2(my_container->sockfd[0], STDIN_FILENO) == -1){
        std::cerr << "failed to dup2: " << my_container->sockfd[0] << std::endl;
    }

    if (dup2(my_container->sockfd[0], STDOUT_FILENO) == -1) {
        std::cerr << "failed to dup2:" << my_container->sockfd[0] << std::endl;
    }
    if (dup2(my_container->sockfd[0], STDERR_FILENO) == -1) {
        std::cerr << "failed to dup2: " << my_container->sockfd[0] << std::endl;
    }

    my_container->run();
    return 0;
}

void Mycontainer::mount_namespace(std::string_view new_root, const std::string& image) {
    make_wrapper<int, true>(&mount)(NULL, "/", NULL, MS_REC | MS_PRIVATE, NULL);
    auto fd_loop = create_loop(image, new_root);
    std::string path = std::string(new_root) + put_old.data();
    std::string mount_place = std::string(new_root) + mount_point.data();
    std::cout<< mount_place << std::endl;
    for (auto &mount: config.mount_points) {
        auto this_mount = mount_place + mount;
        std::filesystem::create_directory(std::filesystem::path(this_mount));
        if (mount_dir(mount, mount_place) != 0) {
            std::cerr << "failed to mount " << mount_place << std::endl;
        }
    }
    make_wrapper<int, true>(&mkdir)(path.data(), 0777);
    std::cout<<"LALALALALAL"<<std::endl;
    switch (pid = fork()) {
        case -1:
            std::cerr<<"fork failed"<<std::endl;
            exit(EXIT_FAILURE);
        case 0:
            if (pivot_root(new_root.data(), path.data()) == -1)
                err(EXIT_FAILURE, "pivot");

            std::filesystem::current_path("/");

            make_wrapper<int, false>(&umount2)(put_old.data(), MNT_DETACH);
            std::filesystem::remove_all(put_old);

            execv(args[0], args.data());
            exit(EXIT_FAILURE);
        default:

            make_wrapper<int, false>(wait)(nullptr);
            for (auto &mount: config.mount_points) {
                if (unmount_dir(mount) != 0) {
                    std::cerr << "failed to unmount " << mount_place << std::endl;
                }
            }
            ioctl(fd_loop, LOOP_CLR_FD, 0);
            close(fd_loop);
            exit(EXIT_SUCCESS);
    }
}

