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
#include <unordered_map>
#include "helper_functions.h"

enum commands {
    CREATE,
    RUN,
    LIST_CONTAINERS,
    STOP,
    RESUME,
    KILL_CONTAINER,
    LISTEN,
    DETACH
};

static std::unordered_map<std::string, commands> commands{{"create",          CREATE},
                                                          {"run",             RUN},
                                                          {"list_containers", LIST_CONTAINERS},
                                                          {"stop",            STOP},
                                                          {"resume",          RESUME},
                                                          {"kill_conatiner",  KILL_CONTAINER},
                                                          {"listen",          LISTEN},
                                                          {"detach",          DETACH},
};

class Mydocker {
private:
    std::vector<std::unique_ptr<Mycontainer>> containers;
    int attached_container_index = -1;
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

    void listen(size_t index);

    void detach();

    template<class... Args>
    void execute_command(const std::string &command, Args ...args, int fd) {
        switch (commands[command]) {
            case CREATE:
                create(std::forward<Args>(args)...);
            case RUN:
                run(std::forward<Args>(args)...);
            case LIST_CONTAINERS:
                list_containers(std::forward<Args>(args)...);
            case STOP:
                stop(std::forward<Args>(args)...);
            case RESUME:
                resume(std::forward<Args>(args)...);
            case KILL_CONTAINER:
                kill_container(std::forward<Args>(args)...);
            case LISTEN:
                listen(std::forward<Args>(args)...);
            case DETACH:
                detach(std::forward<Args>(args)...);
            default:
                writen(fd, "mydoker: no such command", sizeof ("mydoker: no such command"));
        }
    }

};

#endif //MYDOCKER_MYDOCKER_H
