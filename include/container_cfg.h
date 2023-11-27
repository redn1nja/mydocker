// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#ifndef MYDOCKER_CONTAINER_CFG_H
#define MYDOCKER_CONTAINER_CFG_H

class MycontainerConfig {
private:
    int des_in = 0;
    int des_out = 1;
    int des_err = 2;
public:
    void set_in(int in) { des_in = in; }
    void set_out(int out) { des_out = out; }
    void set_err(int err) { des_err = err; }
    int get_in() const { return des_in; }
    int get_out() const { return des_out; }
    int get_err() const { return des_err; }
    
    std::string name;
    std::string root;
    std::vector<std::string> args;
    static std::vector<std::string> root_mount_points;
    int pipefd_out[2];
    int pipefd_in[2];
    int pipefd_err[2];
    int namespace_flags;
    std::string cgroup_name;
    size_t memory_limit_mb = 100; // actually random values
    size_t pids_limit = 10;
    size_t cpu_proportion = 100;
    std::vector<std::string> mount_points;

    MycontainerConfig() = default;
    MycontainerConfig(const MycontainerConfig &other) = default;
    MycontainerConfig &operator=(const MycontainerConfig &other) = default;
    MycontainerConfig(MycontainerConfig &&other) noexcept = default;
    MycontainerConfig &operator=(MycontainerConfig &&other) noexcept = default;
    ~MycontainerConfig() = default;
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

    explicit MycontainerConfig(const std::string &dockerfile_path) {
        boost::property_tree::ptree pt;
        boost::property_tree::read_json(dockerfile_path, pt);
        name = pt.get<std::string>("bin");
        args.emplace_back(name);
        root = pt.get<std::string>("root", "$HOME/mydocker/docker_root");
        memory_limit_mb = pt.get<size_t>("memory_limit_mb", 100);
        pids_limit = pt.get<size_t>("pids_limit", 10);
        cpu_proportion = pt.get<size_t>("cpu_proportion", 20);
        cgroup_name = pt.get<std::string>("cgroup_name", "test");
        for (const auto &item: pt.get_child("mount_points")) {
            mount_points.push_back(item.second.data());
        }
        for (const auto &item: pt.get_child("args")) {
            args.push_back(item.second.data());
        }
    }

    friend std::ostream &operator<<(std::ostream &output, const MycontainerConfig &config) {
        output << "container name: " << config.name << std::endl;
        output << "cgroup name: " << config.cgroup_name << std::endl;
        output << "memory limit (MB): " << config.memory_limit_mb << std::endl;
        output << "pids limit: " << config.pids_limit << std::endl;
        output << "cpu proportion: " << config.cpu_proportion << std::endl;
        output << "root: " << config.root << std::endl;
        return output;
    }
};

#endif //MYDOCKER_CONTAINER_CFG_H
