// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifndef MYDOCKER_MYDOCKER_H
#define MYDOCKER_MYDOCKER_H

#include <string>
#include <vector>
#include <memory>
#include "mycontainer.h"
#include <csignal>
#include <iostream>
#include <unordered_map>
#include <filesystem>
#include "socket_functions.h"
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>

enum commands {
    CREATE,
    RUN,
    LIST_CONTAINERS,
    STOP,
    RESUME,
    KILL_CONTAINER,
    LISTEN,
    EXIT,
    WRONG_COMMAND
};

static std::unordered_map<std::string, commands> commands_map{{"create",          CREATE},
                                                          {"run",             RUN},
                                                          {"list_containers", LIST_CONTAINERS},
                                                          {"stop",            STOP},
                                                          {"resume",          RESUME},
                                                          {"kill_container",  KILL_CONTAINER},
                                                          {"listen",          LISTEN},
                                                          {"exit",            EXIT},
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

    void create(const std::string &dockerfile_path);

    void run(size_t index);

    void list_containers();

    void stop(size_t index);

    void resume(size_t index);

    void kill_container(size_t index);

    void listen(size_t index);

    void detach();

    void execute_command(const std::vector<std::string> &command_args) {

        commands current_command = WRONG_COMMAND;
        if(commands_map.find(command_args[0]) != commands_map.end()){
            current_command = commands_map[command_args[0]];
        }
        switch (current_command) {
            case CREATE:
                create(command_args[1]);
                break;
            case RUN:
                writen(psd, "mydocker: running container", sizeof("mydocker: running container"));
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
//                writen(psd, "mydocker: listening", sizeof("mydocker: listening"));
                break;
            case EXIT:
                writen(psd, "closed", sizeof("closed"));
                break;
            default:
                if  (! boost::starts_with(command_args[0],"detach") || command_args[0][0] != '\020'){
                    writen(psd, std::string{"mydocker: no such command '" + command_args[0] +"'"}.c_str(), std::string{"mydocker: no such command '" + command_args[0] +"'"}.size());
                }
                break;
        }
    }

};

#endif //MYDOCKER_MYDOCKER_H
