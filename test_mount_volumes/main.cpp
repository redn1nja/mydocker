#include <iostream>
#include "bind_mount.h"

int main(int argc, char** argv){
    if (argc != 3) {
        std::cerr<< "usage: " << argv[0] << " <source> <target>"<<std::endl;
        return 1;
    }
    if (mount_dir(argv[1], argv[2]) != 0) {
        std::cerr<< "mount failed: " << argv[1] << " -> " << argv[2] << std::endl;
        return 1;
    }
    std::cout << "mount success: " << argv[1] << " -> " << argv[2] << std::endl;
    return 0;
}