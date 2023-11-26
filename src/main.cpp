// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include "mydocker.h"

int main(int argc, char**argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <new_root> <executable>" << std::endl;
        return 1;
    }
    std::vector<char *> args;
    std::string arg1 = argv[2];
    args.push_back(arg1.data());
    args.push_back(nullptr);
    std::vector<std::string> mounts;
    mounts.emplace_back("/tmp");
    std::string new_root = argv[1];
    Mydocker mydocker;
    auto cfg = MycontainerConfig(mounts, new_root);
    mydocker.create(arg1, args,cfg);
    mydocker.run(0);
    return 0;
}