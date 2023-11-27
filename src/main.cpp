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
//    ContainerCfg cfg(argv[1]);
//    std::cout << cfg.name << std::endl;
//    std::for_each(cfg.args.begin(), cfg.args.end(), [](std::string &s) { std::cout << s << std::endl; });
//    std::cout<<cfg.root<<std::endl;
//    std::cout<<cfg.pids_limit<<std::endl;
//    std::cout<<cfg.cpu_proportion<<std::endl;
//    std::cout<<cfg.memory_limit_mb<<std::endl;
//    std::for_each(cfg.mount_points.begin(), cfg.mount_points.end(), [](std::string &s) { std::cout << s << std::endl; });
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        return 1;
    }
    Mydocker mydocker;

    struct sockaddr_in server;
    char buf[1024];
    int sd;
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        std::cerr << "mydocker: failed to create socket" << std::endl;
    }
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(port);
    int res = bind(sd, (struct sockaddr *) &server, sizeof(server));
    if (res == -1) {
        std::cerr << "mydocker: failed to bind socket" << std::endl;
    }
    listen(sd, 1);
    mydocker.psd = accept(sd, nullptr, nullptr);
    close(sd);
    for (;;) {
        int cc = readn(mydocker.psd, buf, sizeof(buf));
        if (cc == 0) {
            writen(mydocker.psd, "closed", sizeof("closed"));
            exit(EXIT_SUCCESS);
        }
        buf[cc] = '\0';
        printf("message received: %s\n", buf);
        writen(mydocker.psd, "accepted", sizeof("accepted"));
    }
    return 0;
}