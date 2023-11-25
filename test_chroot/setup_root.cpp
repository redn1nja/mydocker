#include "setup_root.h"
#include <unistd.h>

int setup_root(const char *new_root) {
    if (chroot(new_root) == -1) {
        return -1;
    }
    return chdir("/");
}