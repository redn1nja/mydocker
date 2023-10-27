#ifndef MYDOCKER_BIND_MOUNT_H
#define MYDOCKER_BIND_MOUNT_H

#include <unistd.h>
#include <sys/mount.h>
#include <string>

int mount_dir(const std::string& name, const std::string& mountpoint);

#endif //MYDOCKER_BIND_MOUNT_H
