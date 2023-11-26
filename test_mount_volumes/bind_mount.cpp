// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "bind_mount.h"
#include <filesystem>

int mount_dir(const std::string &name, const std::string &mountpoint) {
    return mount(name.c_str(), mountpoint.c_str(), "ext4", MS_BIND, nullptr);
}

int unmount_dir(const std::string &mountpoint) {
    return umount(mountpoint.c_str());
}

int create_mountpoint(const std::string &mountpoint) {
    return std::filesystem::create_directories(mountpoint);
}