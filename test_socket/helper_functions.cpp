// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "helper_functions.h"

ssize_t readn(int fd, void *buffer, size_t n) {
    ssize_t numRead;
    size_t totRead;
    char *buf;
    buf = static_cast<char *>(buffer);
    for (totRead = 0; totRead < n;) {
        numRead = read(fd, buf, n - totRead);
        if (numRead == 0)
            return totRead;
        if (numRead == -1) {
            if (errno == EINTR)
                continue;
            else
                return -1;
        }
        totRead += numRead;
        buf += numRead;
    }
    return totRead;
}

ssize_t writen(int fd, const void *buffer, size_t n) {
    ssize_t numWritten;
    size_t totWritten;
    const char *buf;
    buf = static_cast<const char *>(buffer);
    for (totWritten = 0; totWritten < n;) {
        numWritten = write(fd, buf, n - totWritten);
        if (numWritten <= 0) {
            if (numWritten == -1 && errno == EINTR)
                continue;
            else
                return -1;
        }
        totWritten += numWritten;
        buf += numWritten;
    }
    return totWritten;
}