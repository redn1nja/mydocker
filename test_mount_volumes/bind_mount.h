// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifndef MYDOCKER_BIND_MOUNT_H
#define MYDOCKER_BIND_MOUNT_H

#include <unistd.h>
#include <sys/mount.h>
#include <string>

int mount_dir(const std::string& name, const std::string& mountpoint);
int unmount_dir(const std::string& mountpoint);

#endif //MYDOCKER_BIND_MOUNT_H
