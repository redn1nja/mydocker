// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "setup_root.h"
#include <unistd.h>

int setup_root(const char *new_root) {
    if (chroot(new_root) == -1) {
        return -1;
    }
    return chdir("/");
}