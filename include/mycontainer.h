// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifndef MYDOCKER_MYCONTAINER_H
#define MYDOCKER_MYCONTAINER_H

#include <csignal>
#include <string>
#include <vector>
#include <memory>

class MycontainerConfig {
private:
    int pipefd[2];
    // шось неймспейсне софія додасть
    // шось сігрупне настя додасть
    std::vector<std::string> mount_points;
    std::string root;
public:
    MycontainerConfig() = delete;

    MycontainerConfig(std::vector<std::string> mount_points,
                      std::string root) :
            mount_points(std::move(mount_points)),
            root(std::move(root)) {
        if (pipe(pipefd) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }
};

class Mycontainer {
private:
    std::vector<std::string> names;
    std::vector<std::vector<char *>> args; // мені здається шо це треба буде для форка
    std::vector<int> pids;
    std::vector<int> status;
    std::vector<MycontainerConfig> config;
    std::vector<bool> is_running;
public:
    Mycontainer() = delete;
    Mycontainer(std::vector<std::string> names,
                std::vector<std::vector<char *>> args,
                std::vector<MycontainerConfig> config) :
            names(std::move(names)),
            args(std::move(args)),
            config(std::move(config)) {}

    Mycontainer &operator=(const Mycontainer &other) = default;
    Mycontainer(const Mycontainer &other) = default;
    std::unique_ptr<Mycontainer> clone() { return std::make_unique<Mycontainer>(*this); }
    void start();
    void stop();
    void kill();
    ~Mycontainer() = default;
};

std::ofstream operator<<(std::ofstream &out, const Mycontainer &mycontainer);

#endif //MYDOCKER_MYCONTAINER_H
