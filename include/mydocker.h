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
#include "socket_functions.h"
extern int fd;
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
    size_t attached_container_index = -1;
public:
    int fd_out = 1;
    int fd_in = 0;
    int fd_err = 2;
    int psd = 0;
    Mydocker() = default;
    ~Mydocker() = default;
    Mydocker &operator=(const Mydocker &other) = delete;
    Mydocker(const Mydocker &other) = delete;
    void run(size_t index) { containers[index]->start(); }
    template<class... Args>
    void create(Args &&...args) {
        containers.push_back(std::make_unique<Mycontainer>(std::forward<Args>(args)...));
        writen(psd, "mydocker: container created", sizeof ("mydocker: container created"));
    }
    void list_containers();
    void stop(size_t index);
    void resume(size_t index);
    void kill_container(size_t index);
    void listen(size_t index);
    void detach();
    void execute_command(const std::vector<std::string>& command_args) {
        switch (commands[command_args[0]]) {
            case CREATE:
                create(command_args[1]);
                break;
            case RUN:
                writen(psd, "mydocker: running container", sizeof ("mydocker: running container"));
                run(std::stoul(command_args[1]));
                break;
            case LIST_CONTAINERS:
                list_containers();
                break;
            case STOP:
                stop(std::stoul(command_args[1]));
                break;
            case RESUME:
                resume(std::stoul(command_args[1]));
                break;
            case KILL_CONTAINER:
                kill_container(std::stoul(command_args[1]));
                break;
            case LISTEN:
                listen(std::stoul(command_args[1]));
                writen(psd, "mydocker: listening", sizeof ("mydocker: listening"));
                break;
            case DETACH:
                detach();
                writen(psd, "mydocker: detached", sizeof ("mydocker: detached"));
                break;
            default:
                writen(psd, "mydocker: no such command", sizeof ("mydocker: no such command"));
        }
    }

};

#endif //MYDOCKER_MYDOCKER_H
