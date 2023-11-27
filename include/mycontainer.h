// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifndef MYDOCKER_MYCONTAINER_H
#define MYDOCKER_MYCONTAINER_H

#include <csignal>
#include <string>
#include <vector>
#include <memory>
#include <iostream>

class MycontainerConfig {
private:
    int des_out = 1;
    int des_in = 0;
    int des_err = 2;
public:
    static std::vector<std::string> root_mount_points;
    int pipefd_out[2];
    int pipefd_in[2];
    int pipefd_err[2];
    int namespace_flags;
    std::string cgroup_name;
    size_t memory_limit_mb = 5; // actually random values
    size_t pids_limit = 10;
    size_t cpu_proportion = 100;
    std::vector<std::string> mount_points;
    std::string root;

    [[nodiscard]] int get_in() const { return des_in; }
    [[nodiscard]] int get_out() const { return des_out; }
    [[nodiscard]] int get_err() const { return des_err; }


    void set_in(int des) { des_in = des; }
    void set_out(int des) { des_out = des; }
    void set_err(int des) { des_err = des; }

    MycontainerConfig() = delete;
    MycontainerConfig(std::vector<std::string> mount_points,
                      std::string root, int namespaces_flags) :
            mount_points(std::move(mount_points)),
            namespace_flags(namespaces_flags),
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
    };
    friend std::ostream &operator<<(std::ostream &output, const MycontainerConfig &config){
        output << "cgroup name: " << config.cgroup_name << std::endl;
        output << "memory limit (MB): " << config.memory_limit_mb << std::endl;
        output << "pids limit: " << config.pids_limit << std::endl;
        output << "cpu proportion: " << config.cpu_proportion << std::endl;
        output << "root: " << config.root << std::endl;
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
