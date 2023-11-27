// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "socket_functions.h"

ssize_t readn(int fd, void *buffer, size_t n) {
    ssize_t numRead;
    size_t totRead;
    char *buf;
    buf = static_cast<char *>(buffer);
    for (totRead = 0; totRead < n;) {
        numRead = read(fd, buf + totRead, n - totRead);
        if (numRead == 0)
            return totRead;
        if (numRead == -1) {
            if (errno == EINTR)
                continue;
            else
                return -1;
        }
        totRead += numRead;
        if (totRead <= n && buf[totRead - 1] == '\n'){
            return totRead;
        }
    }
    return totRead;
}

ssize_t writen(int fd, const void *buffer, size_t n) {
    ssize_t numWritten;
    size_t totWritten;
    const char *buf;
    buf = static_cast<const char *>(buffer);
    for (totWritten = 0; totWritten < n;) {
        numWritten = write(fd, buf + totWritten, n - totWritten);
        if (numWritten <= 0) {
            if (numWritten == -1 && errno == EINTR)
                continue;
            else
                return -1;
        }
        totWritten += numWritten;
    }
    return totWritten;
}

void create_server(int port, int &psd) {
    struct sockaddr_in server;
    char buf[1024];
    int sd;
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        std::cerr << "mydocker: failed to create socket" << std::endl;
    }
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(8000);
    int res = bind(sd, (struct sockaddr *) &server, sizeof(server));
    if (res == -1) {
        std::cerr << "mydocker: failed to bind socket" << std::endl;
    }
    listen(sd, 1);
    psd = accept(sd, nullptr, nullptr);
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