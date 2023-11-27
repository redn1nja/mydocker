// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <cstring>
#include "unistd.h"
#include "socket_functions.h"

int main(int argc, char *argv[]) {
    struct sockaddr_in server;
    char buf[1024];
    int sd;
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        std::cerr << "test socket: failed to create socket" << std::endl;
    }
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(8000);
    int res = bind(sd, (struct sockaddr *) &server, sizeof(server));
    if (res == -1) {
        std::cerr << "test socket: failed to bind socket" << std::endl;
    }
    listen(sd, 1);
    int psd = accept(sd, nullptr, nullptr);
    close(sd);
    for (;;) {
        int cc = readn(psd, buf, sizeof(buf));
        if (cc == 0) {
            writen(psd, "closed", sizeof("closed"));
            exit(EXIT_SUCCESS);
        }
        buf[cc] = '\0';
        printf("message received: %s\n", buf);
        writen(psd, "accepted", sizeof("accepted"));
    }
}