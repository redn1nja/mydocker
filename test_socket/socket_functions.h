// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifndef MYDOCKER_SOCKET_FUNCTIONS_H
#define MYDOCKER_SOCKET_FUNCTIONS_H

#include <cstdio>
#include "unistd.h"
#include <cerrno>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <cstring>
#include "unistd.h"

ssize_t readn(int fd , void *buffer, size_t n);
ssize_t writen(int fd , const void *buffer , size_t n);
void create_server(int port, int &psd);
int cat(int fd, char *buffer, size_t size);

#endif //MYDOCKER_SOCKET_FUNCTIONS_H
