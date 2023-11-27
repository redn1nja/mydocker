#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#ifndef MYDOCKER_CONTAINER_CFG_H
#define MYDOCKER_CONTAINER_CFG_H

class ContainerCfg {
public:
    std::string name;
    std::string root;
    std::vector<std::string> args;
    std::vector<std::string> mount_points;
    size_t memory_limit_mb = 100;
    size_t pids_limit = 10;
    size_t cpu_proportion = 20;
    std::string cgroup_name;

    ContainerCfg() = default;
    ContainerCfg(const ContainerCfg &other) = default;
    ContainerCfg &operator=(const ContainerCfg &other) = default;
    ContainerCfg(ContainerCfg &&other) noexcept = default;
    ContainerCfg &operator=(ContainerCfg &&other) noexcept = default;
    ~ContainerCfg() = default;
    explicit ContainerCfg (const std::string &path) {
        boost::property_tree::ptree pt;
        boost::property_tree::read_json(path, pt);
        name = pt.get<std::string>("bin");
        args.emplace_back(name);
        root = pt.get<std::string>("root", "$HOME/mydocker/docker_root");
        memory_limit_mb = pt.get<size_t>("memory_limit_mb", 100);
        pids_limit = pt.get<size_t>("pids_limit", 10);
        cpu_proportion = pt.get<size_t>("cpu_proportion", 20);
        cgroup_name = pt.get<std::string>("cgroup_name", "test");
        for (const auto &item : pt.get_child("mount_points")) {
            mount_points.push_back(item.second.data());
        }
        for (const auto &item : pt.get_child("args")) {
            args.push_back(item.second.data());
        }
    }
};

#endif //MYDOCKER_CONTAINER_CFG_H
