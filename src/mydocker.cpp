// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "mydocker.h"
#include <sstream>
#include <fcntl.h>

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
        writen(psd, "Failed to stop container\n", strlen("Failed to stop container\n"));
    }
}

void Mydocker::resume(size_t index) {
    if (kill(containers[index]->getPID(), SIGCONT) == -1) {
        writen(psd, "Failed to resume container\n", strlen("Failed to resume container\n"));
    }
}

void Mydocker::kill_container(size_t index) {
    if (kill(containers[index]->getPID(), SIGKILL) == -1) {
        writen(psd, "Failed to kill container\n", strlen("Failed to kill container\n"));
        return;
    }
    std::string kill_msg = "killed: " + std::to_string(containers[index]->getPID());
    writen(psd, kill_msg.data(), kill_msg.size());
}

void Mydocker::listen(size_t index) {
    std::cout << containers[index]->getPID() << std::endl;
    if (attached_container_index != -1) {
        writen(psd, "Failed to listen: already listening another container\n",
               strlen("Failed to listen: already listening another container\n"));
    } else {
        std::cout << "listening " << index << std::endl;

        //TODO do listen stuff
        int flags = fcntl(containers[index]->getConfig().get_sockfd()[1], F_GETFL, 0);
        if (flags == -1) {
            perror("fcntl");
        }
        flags |= O_NONBLOCK;  // Set the O_NONBLOCK flag
        if (fcntl(containers[index]->getConfig().get_sockfd()[1], F_SETFL, flags) == -1) {
            perror("fcntl");
        }
        while (true) {
            char buffer[4096];
            ssize_t bytesRead = cat(containers[index]->getConfig().get_sockfd()[1], buffer, sizeof(buffer), psd);

//            if (bytesRead <= 0) {
//                // If read returns 0 or negative value, it indicates EOF or an error.
//                break;
//            }
            // Get user input for the command
//            std::string userInput;
////            std::cout << "Enter command: ";
//            std::getline(std::cin, userInput);
//            userInput += "\n";  // Add newline to simulate pressing Enter

            // Send the command to Program B via the socket
//            write(sockfd[1], userInput.c_str(), userInput.size());
//            std::cout.write(buffer, bytesRead);

        }

        attached_container_index = index;
    }
}

void Mydocker::detach() {
    if (attached_container_index == -1) {
        writen(psd, "Failed to detach: not listening any container\n",
               strlen("Failed to detach: not listening any container\n"));
        return;
    }

    //TODO do detach stuff
    shutdown(containers[attached_container_index]->getConfig().get_sockfd()[1], SHUT_RDWR);

    attached_container_index = -1;
}
