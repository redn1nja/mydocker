#include "create_namespace.h"

int move_process_to_new_ns(int flags) {
    return unshare(flags);
}

int create_process_in_new_ns(int (*child_func)(void *), void *stack, int flags, void *arg_for_child_func) {
    return clone(child_func, stack, flags, arg_for_child_func);
}

