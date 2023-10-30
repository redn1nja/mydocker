#include "bind_mount.h"

int mount_dir(const std::string& name, const std::string& mountpoint){
    return mount(name.c_str(), mountpoint.c_str(), "ext4", MS_BIND, nullptr);
}

int unmount_dir(const std::string& mountpoint){
    return umount(mountpoint.c_str());
}