#include "mount_namespaces.h"
#include <err.h>
#include <cstdlib>
#include <sys/mount.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <filesystem>
#include <sys/stat.h>
#include <linux/loop.h>

int pivot_root(const char *new_root, const char *put_olds) {
    return syscall(SYS_pivot_root, new_root, put_olds);
}


int mount_namespace(void *arg) {
    auto **args = reinterpret_cast<char**>(arg);
    std::string new_root = args[0];
    unshare(CLONE_NEWNS);
    std::string image_path = IMAGE_PATH;

    make_wrapper<int, true>(&mount)(NULL, "/", NULL, MS_REC | MS_PRIVATE, NULL);
//    make_wrapper<int, true>(&mount)(new_root.data(), new_root.data(), NULL, MS_BIND, NULL);
    auto fd = create_loop(image_path, new_root.data());
    std::string path = new_root + put_old.data();
    make_wrapper<int, true>(&mkdir)(path.data(), 0777);;

    if (pivot_root(new_root.data(), path.data()) == -1)
        err(EXIT_FAILURE, "pivot");

    std::filesystem::current_path("/");

    make_wrapper<int, false>(&umount2)(put_old.data(), MNT_DETACH);
    std::filesystem::remove_all(put_old);
    close(fd);
    execv(args[1], &args[1]);
    exit(EXIT_FAILURE);
}

int create_loop(const std::string& image, const std::string& mountpoint){
    int loopctlfd, loopfd, backingfile;
    long devnr;
    loopctlfd = open("/dev/loop-control", O_RDWR);
    devnr = ioctl(loopctlfd, LOOP_CTL_GET_FREE);
    std::string loop_name = loop_path.data() + std::to_string(devnr);
    loopfd = open(loop_name.data(), O_RDWR);
    backingfile = open(image.data(), O_RDWR);
    ioctl(loopfd, LOOP_SET_FD, backingfile);
    make_wrapper<int, true>(&mount)(loop_name.c_str(), mountpoint.data(), "ext4", 0, NULL);
    return loopfd;
}