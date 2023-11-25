// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <cstdlib>
#include "setup_root.h"
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char** argv){
    if (argc != 2) {
        std::cerr<< "usage: " << argv[0] << " <new_root>"<<std::endl;
    }

    setup_root(argv[1]);
    std::cout << fs::current_path() << std::endl;
    return EXIT_SUCCESS;
}
