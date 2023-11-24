// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

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
    std::cout<<"press enter to unmount"<<std::endl;
    std::cin.get();
    if (unmount_dir(argv[2]) != 0) {
        std::cerr<< "unmount failed: " << argv[2] << std::endl;
        return 1;
    }
    std::cout<<"unmount success: " << argv[2] << std::endl;
    return 0;
}