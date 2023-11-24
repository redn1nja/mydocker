cmake_minimum_required(VERSION 3.18)
project(mydocker)

set(CMAKE_CXX_STANDARD 17)

add_executable(test_bin test_binary/main.cpp)
add_executable(cgroups test_cgroups/cgroups.h test_cgroups/cgroups.cpp test_cgroups/main.cpp)
add_executable(volumes test_mount_volumes/bind_mount.h test_mount_volumes/bind_mount.cpp test_mount_volumes/main.cpp)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
