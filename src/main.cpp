// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include "mydocker.h"
#include "container_cfg.h"
#include <boost/algorithm/string.hpp>

int main(int argc, char **argv) {
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
    server.sin_port = htons(atoi(argv[1]));
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
        std::string command(buf);
        boost::trim(command);
        std::vector<std::string> command_args;
        boost::split(command_args, command, boost::is_any_of(" "));
        mydocker.execute_command(command_args);
    }
    return 0;
}