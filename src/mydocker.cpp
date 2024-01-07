// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "mydocker.h"
#include <sstream>

void Mydocker::create(const std::string &dockerfile_path) {
    if (!std::filesystem::exists(dockerfile_path)) {
        std::string error_msg =
            "mydocker: failed to create container\n" + dockerfile_path + ": no such file or directory";
        writen(psd, error_msg.c_str(), error_msg.size());
    } else if (std::filesystem::path(dockerfile_path).extension() != ".json") {
        std::string error_msg = "mydocker: failed to create container\n" + dockerfile_path + ": not a json file";
        writen(psd, error_msg.c_str(), error_msg.size());
    } else {
        containers.push_back(std::make_unique<Mycontainer>(dockerfile_path));
        writen(psd, "mydocker: container created", sizeof("mydocker: container created"));
    }
}

void Mydocker::run(size_t index) { containers[index]->start(); }

void Mydocker::list_containers() {
    for (size_t i = 0; i < containers.size(); ++i) {
        std::stringstream ss;
        ss << "Container " << i << std::endl;
        ss << containers[i]->getConfig() << std::endl;
        auto str = ss.str();
        writen(psd, str.data(), str.size());
    }
}

void Mydocker::stop(size_t index) {
    if (kill(containers[index]->getPID(), SIGSTOP) == -1) {
        std::cerr << "Failed to stop container" << std::endl;
    }
}

void Mydocker::resume(size_t index) {
    if (kill(containers[index]->getPID(), SIGCONT) == -1) {
        std::cerr << "Failed to resume container" << std::endl;
    }
}

void Mydocker::kill_container(size_t index) {
    if (kill(containers[index]->getPID(), SIGKILL) == -1) {
        writen(psd, "Failed to kill container", strlen("Failed to kill container"));
        return;
    }
    std::string kill_msg = "killed: " + std::to_string(containers[index]->getPID());
    writen(psd, kill_msg.data(), kill_msg.size());
}

void Mydocker::listen(size_t index) {
    std::cout << containers[index]->getPID() << std::endl;
    if (attached_container_index != -1) {
        std::cerr << "Failed to listen: already listening another container" << std::endl;
    } else {
        std::cout << "listening " << index << std::endl;

        //TODO do listen stuff

        attached_container_index = index;
    }
}

void Mydocker::detach() {
    if (attached_container_index == -1) {
        std::cerr << "Failed to detach: not listening any container" << std::endl;
        return;
    }

    //TODO do detach stuff

    attached_container_index = -1;
}
