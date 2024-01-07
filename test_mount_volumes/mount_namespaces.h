
#ifndef MYDOCKER_MOUNT_NAMESPACES_H
#define MYDOCKER_MOUNT_NAMESPACES_H

#include <utility>
#include <iostream>
#include <cstring>
#include <functional>
#include <sstream>

constexpr std::string_view put_old = "/oldrootfs";
constexpr std::string_view loop_path = "/dev/loop";
constexpr size_t STACK_SIZE = 1024*1024;
constexpr std::string_view mount_point = "/mnt";

template <bool throws, class T, class ...Args>
class syscall_wrap{
    std::function<T(Args...)> sys;

public:
    explicit syscall_wrap(T syscall (Args...)) : sys(syscall) {}

    T operator() (Args...args){
        T res (sys(args...));
        int error_code = errno;
        if (error_code){
            if (throws) {
                std::string error = strerror(errno);
                std::cerr<<strerror(errno);
                ((std::cerr << " , " << std::forward<Args>(args)), ...);
            }
            else{
                std::cerr<<strerror(errno);
                ((std::cerr << " , " << std::forward<Args>(args)), ...);
            }
        }
        return res;
    }
};

template<typename T, bool throws, typename... Args>
syscall_wrap<throws, T, Args...> make_wrapper (T syscall (Args...))
{
    return syscall_wrap<throws, T, Args...> (syscall);
}

int pivot_root(const char *new_root, const char *put_olds);
int mount_namespace_child (void* arg);
int mount_namespace(std::string_view mount_point, char** exec_params, const std::vector<std::string>& mounts);
int create_loop(std::string_view image, std::string_view mountpoint);



#endif //MYDOCKER_MOUNT_NAMESPACES_H
