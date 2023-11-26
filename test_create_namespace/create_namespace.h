// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifndef MYDOCKER_CREATE_NAMESPACE_H
#define MYDOCKER_CREATE_NAMESPACE_H

#include <sched.h>

int move_process_to_new_ns(int flags);
int create_process_in_new_ns(int (*child_func)(void *), size_t stack_size, int flags, void *arg_for_child_func);
void *create_stack(size_t stack_size);


#endif //MYDOCKER_CREATE_NAMESPACE_H
