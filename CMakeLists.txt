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
        test_socket/socket_functions.cpp test_socket/socket_functions.h
        test_mount_volumes/mount_namespaces.cpp
        test_mount_volumes/mount_namespaces.h
)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE test_cgroups)
target_include_directories(${PROJECT_NAME} PRIVATE test_chroot)
target_include_directories(${PROJECT_NAME} PRIVATE test_create_namespace)
target_include_directories(${PROJECT_NAME} PRIVATE test_mount_volumes)
target_include_directories(${PROJECT_NAME} PRIVATE test_socket)


add_executable(test_bin test_binary/main.cpp)
target_link_options(test_bin PRIVATE -static-libgcc -static-libstdc++ -static)
add_executable(volumes test_mount_volumes/bind_mount.h test_mount_volumes/bind_mount.cpp test_mount_volumes/main.cpp)
add_executable(namespaces test_create_namespace/create_namespace.cpp test_create_namespace/create_namespace.h test_create_namespace/main.cpp)
add_executable(change_root test_chroot/setup_root.cpp test_chroot/setup_root.h test_chroot/main.cpp)
add_executable(cgroups test_cgroups/cgroups.h test_cgroups/cgroups.cpp test_cgroups/main.cpp)
add_executable(socket test_socket/main.cpp
        test_socket/socket_functions.cpp
        test_socket/socket_functions.h)

target_compile_definitions(${PROJECT_NAME} PUBLIC IMAGE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/rootfs.img")

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
