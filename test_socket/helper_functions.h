// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifndef MYDOCKER_HELPER_FUNCTIONS_H
#define MYDOCKER_HELPER_FUNCTIONS_H

#include <cstdio>
#include "unistd.h"
#include <cerrno>

ssize_t readn(int fd , void *buffer, size_t n);
ssize_t writen(int fd , const void *buffer , size_t n);

#endif //MYDOCKER_HELPER_FUNCTIONS_H
