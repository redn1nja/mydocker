#include "mount_namespaces.h"
#include "bind_mount.h"
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
#include <sys/wait.h>

int pivot_root(const char *new_root, const char *put_olds) {
    return syscall(SYS_pivot_root, new_root, put_olds);
}




int create_loop(std::string_view image, std::string_view mountpoint){
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