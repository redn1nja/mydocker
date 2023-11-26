// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifndef MYDOCKER_MYDOCKER_H
#define MYDOCKER_MYDOCKER_H

#include <string>
#include <vector>
#include <memory>
#include "mycontainer.h"
#include "signal.h"
#include <iostream>

class Mydocker {
private:
    std::vector<std::unique_ptr<Mycontainer>> containers;
public:
    Mydocker() = default;
    ~Mydocker() = default;
    Mydocker &operator=(const Mydocker &other) = delete;
    Mydocker(const Mydocker &other) = delete;
    void run(size_t index) { containers[index]->start(); }
    template<class... Args>
    void create(Args &&...args) {
        containers.push_back(std::make_unique<Mycontainer>(std::forward<Args>(args)...));
    }
    void list_containers();
    void stop(size_t index);
    void resume(size_t index);
    void kill_container(size_t index);
};

#endif //MYDOCKER_MYDOCKER_H
