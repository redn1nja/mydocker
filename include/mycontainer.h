// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifndef MYDOCKER_MYCONTAINER_H
#define MYDOCKER_MYCONTAINER_H

#include <string>
#include <vector>
#include <memory>
#include <csignal>
#include <iostream>
#include <container_cfg.h>
#include <filesystem>

extern int fd;

class Mycontainer {
private:
    std::string name;
    std::vector<char *> args;
    int pid = -1;
    int status = -1;
    MycontainerConfig config;
    bool is_running = false;
    std::string root_dir;
    std::string id;


public:
    Mycontainer() = delete;
    void mount_namespace(std::string_view mount_point, const std::string& image);
    explicit Mycontainer(MycontainerConfig config) :
        name(config.name),
        config(std::move(config)),
        is_running(false) {
        for (const auto &arg: this->config.args) {
            this->args.push_back(const_cast<char *>(arg.c_str()));
        }
        id = std::to_string(reinterpret_cast<uint64_t>(this));
        root_dir = MycontainerConfig::root + id;
        std::filesystem::create_directory(root_dir);
    }

    explicit Mycontainer(const std::string &dockerfile_path) {
        config = MycontainerConfig(dockerfile_path);
        name = config.name;
        for (auto &arg: config.args) {
            args.emplace_back(arg.data());
        }
        id = std::to_string(reinterpret_cast<uint64_t>(this));
        root_dir = MycontainerConfig::root + id;
        std::filesystem::create_directory(root_dir);

    }

    Mycontainer &operator=(const Mycontainer &other) = default;

    Mycontainer(const Mycontainer &other) = default;

    std::unique_ptr<Mycontainer> clone() { return std::make_unique<Mycontainer>(*this); }

    void start();

    void run();

    static int child_func(void *arg);

    [[nodiscard]] int getPID() const { return pid; };

    MycontainerConfig getConfig() { return config; };

    ~Mycontainer() = default;
};

std::ofstream operator<<(std::ofstream &out, const Mycontainer &mycontainer);

#endif //MYDOCKER_MYCONTAINER_H
