// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifndef MYDOCKER_MYCONTAINER_H
#define MYDOCKER_MYCONTAINER_H

#include <csignal>
#include <string>
#include <vector>
#include <memory>

class MycontainerConfig {
public:
    static std::vector<std::string> root_mount_points;
    int pipefd_out[2];
    int pipefd_in[2];
    int pipefd_err[2];
    // шось неймспейсне софія додасть
    std::string cgroup_name;
    size_t memory_limit_mb = 5; // actually random values
    size_t pids_limit = 10;
    size_t cpu_proportion = 100;
    std::vector<std::string> mount_points;
    std::string root;

    MycontainerConfig() = delete;
    MycontainerConfig(std::vector<std::string> mount_points,
                      std::string root) :
            mount_points(std::move(mount_points)),
            root(std::move(root)) {
//        mount_root();
        if (pipe(pipefd_out) == -1) {
            perror("pipe out");
            exit(EXIT_FAILURE);
        }
        if (pipe(pipefd_in) == -1) {
            perror("pipe in");
            exit(EXIT_FAILURE);
        }
        if (pipe(pipefd_err) == -1) {
            perror("pipe err");
            exit(EXIT_FAILURE);
        }
    }
};

class Mycontainer {
private:
    std::string name;
    std::vector<char *> args; // мені здається шо це треба буде для форка
    int pid = -1;
    int status = -1;
    MycontainerConfig config;
    bool is_running;
public:
    void mount_root() const;
    Mycontainer() = delete;
    Mycontainer(std::string name,
                std::vector<char *> args,
                MycontainerConfig config) :
            name(std::move(name)),
            args(std::move(args)),
            config(std::move(config)),
            is_running(false) {}
    Mycontainer &operator=(const Mycontainer &other) = default;
    Mycontainer(const Mycontainer &other) = default;
    std::unique_ptr<Mycontainer> clone() { return std::make_unique<Mycontainer>(*this); }
    void start();
    void run();
    void stop();
    void kill();
    static int child_func(void *arg);
    [[nodiscard]] int getPID() const{return pid;};
    MycontainerConfig getConfig() {return config;};
    ~Mycontainer() = default;
};

std::ofstream operator<<(std::ofstream &out, const Mycontainer &mycontainer);

#endif //MYDOCKER_MYCONTAINER_H
