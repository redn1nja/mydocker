// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include "mydocker.h"
#include "container_cfg.h"

int main(int argc, char **argv) {
//    if (argc != 3) {
//        std::cerr << "Usage: " << argv[0] << " <new_root> <executable>" << std::endl;
//        return 1;
//    }
//    std::vector<char *> args;
//    std::string arg1 = argv[2];
//    args.push_back(arg1.data());
//    args.push_back(nullptr);
//    std::vector<std::string> mounts;
//    mounts.emplace_back("/tmp");
//    std::string new_root = argv[1];
//    Mydocker mydocker;
//    auto cfg = MycontainerConfig(mounts, new_root, CLONE_NEWNS);
//    mydocker.create(arg1, args,cfg);
//    mydocker.run(0);
    ContainerCfg cfg(argv[1]);
    std::cout << cfg.name << std::endl;
    std::for_each(cfg.args.begin(), cfg.args.end(), [](std::string &s) { std::cout << s << std::endl; });
    std::cout<<cfg.root<<std::endl;
    std::cout<<cfg.pids_limit<<std::endl;
    std::cout<<cfg.cpu_proportion<<std::endl;
    std::cout<<cfg.memory_limit_mb<<std::endl;
    std::for_each(cfg.mount_points.begin(), cfg.mount_points.end(), [](std::string &s) { std::cout << s << std::endl; });

return 0;
}