#include "mount_namespaces.h"
#include <sys/wait.h>
#include <sched.h>
#include <sys/mman.h>
#include <err.h>
#include <linux/loop.h>
#include <sys/ioctl.h>

int main(int argc, char *argv[]) {
    if (argc != 3){
        std::cerr<<"usage: "<<argv[0]<<" <new_root> <executable>\n";
        return EXIT_FAILURE;
    }
    std::string image_path = IMAGE_PATH;

    char *stack;
    stack = static_cast<char*>(make_wrapper<void*, true>(&mmap)(nullptr, STACK_SIZE, PROT_READ | PROT_WRITE,
                                                                MAP_PRIVATE | MAP_ANONYMOUS | MAP_STACK, -1, 0));

    if (clone(mount_namespace, stack + STACK_SIZE, CLONE_NEWNS | SIGCHLD, &argv[1]) == -1)
        err(EXIT_FAILURE, "clone");
    make_wrapper<int, true>(&wait)(nullptr);
    return EXIT_SUCCESS;
}
