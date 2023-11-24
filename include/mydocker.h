// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifndef MYDOCKER_MYDOCKER_H
#define MYDOCKER_MYDOCKER_H

#include <string>
#include <vector>
#include <memory>
#include "mycontainer.h"

class Mydocker{
private:
    std::vector<std::unique_ptr<Mycontainer>> containers;
public:
    Mydocker() = default;
    ~Mydocker() = default;
    Mydocker& operator=(const Mydocker& other) = delete;
    Mydocker(const Mydocker& other) = delete;
    void run(size_t index) { containers[index]->start();}
    void create(std::unique_ptr<Mycontainer> mycontainer) { containers.push_back(std::move(mycontainer)); }
    void list_containers();
    void stop(size_t index);
    void resume(size_t);
    void kill(size_t);
};

#endif //MYDOCKER_MYDOCKER_H
