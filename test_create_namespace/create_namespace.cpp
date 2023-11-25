// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "create_namespace.h"

int move_process_to_new_ns(int flags) {
    return unshare(flags);
}

int create_process_in_new_ns(int (*child_func)(void *), size_t stack_size, int flags, void *arg_for_child_func) {
    return clone(child_func, create_stack(stack_size), flags, arg_for_child_func);
}

void* create_stack(size_t stack_size) {
    char* whole_stack = new char[stack_size];
    void* stack;
    void* stack_top;
    stack = whole_stack;
    stack_top = static_cast<char*>(stack) + stack_size;
    return stack_top;
}

