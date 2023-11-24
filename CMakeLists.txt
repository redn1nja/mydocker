cmake_minimum_required(VERSION 3.18)
project(mydocker)

set(CMAKE_CXX_STANDARD 17)


add_executable(mydocker src/main.cpp
        include/mydocker.h src/mydocker.cpp
        include/mycontainer.h src/mycontainer.cpp
)
target_include_directories(mydocker PRIVATE include)
add_executable(test_bin test_binary/main.cpp)
add_executable(volumes test_mount_volumes/bind_mount.h test_mount_volumes/bind_mount.cpp test_mount_volumes/main.cpp)
add_executable(namespaces test_create_namespace/create_namespace.cpp test_create_namespace/create_namespace.h test_create_namespace/main.cpp)
