cmake_minimum_required(VERSION 3.18)
set(PROJECT_NAME mydocker)

project(${PROJECT_NAME} C CXX)

set(CMAKE_CXX_STANDARD 17)


add_executable(${PROJECT_NAME} src/main.cpp
        include/mydocker.h src/mydocker.cpp
        include/mycontainer.h src/mycontainer.cpp
        test_create_namespace/create_namespace.cpp test_create_namespace/create_namespace.h
        test_chroot/setup_root.cpp test_chroot/setup_root.h
        test_cgroups/cgroups.h test_cgroups/cgroups.cpp
        test_mount_volumes/bind_mount.h test_mount_volumes/bind_mount.cpp
        include/container_cfg.h
)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE test_cgroups)
target_include_directories(${PROJECT_NAME} PRIVATE test_chroot)
target_include_directories(${PROJECT_NAME} PRIVATE test_create_namespace)
target_include_directories(${PROJECT_NAME} PRIVATE test_mount_volumes)

add_executable(test_bin test_binary/main.cpp)
add_executable(volumes test_mount_volumes/bind_mount.h test_mount_volumes/bind_mount.cpp test_mount_volumes/main.cpp)
add_executable(namespaces test_create_namespace/create_namespace.cpp test_create_namespace/create_namespace.h test_create_namespace/main.cpp)
add_executable(change_root test_chroot/setup_root.cpp test_chroot/setup_root.h test_chroot/main.cpp)
add_executable(cgroups test_cgroups/cgroups.h test_cgroups/cgroups.cpp test_cgroups/main.cpp)
add_executable(socket test_socket/main.cpp
        test_socket/helper_functions.cpp
        test_socket/helper_functions.h)



INSTALL(PROGRAMS
        $<TARGET_FILE:${PROJECT_NAME}>
        DESTINATION bin)

INSTALL(PROGRAMS
        $<TARGET_FILE:test_bin>
        DESTINATION bin)

INSTALL(PROGRAMS
        $<TARGET_FILE:volumes>
        DESTINATION bin)

INSTALL(PROGRAMS
        $<TARGET_FILE:namespaces>
        DESTINATION bin)

INSTALL(PROGRAMS
        $<TARGET_FILE:cgroups>
        DESTINATION bin)

INSTALL(PROGRAMS
        $<TARGET_FILE:change_root>
        DESTINATION bin)

INSTALL(PROGRAMS
        $<TARGET_FILE:socket>
        DESTINATION bin)
