// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "mydocker.h"

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
        std::cerr << "Failed to kill container" << std::endl;
    }
}

void Mydocker::listen(size_t index) {
    if (attached_container_index != -1) {
        std::cerr << "Failed to listen: already listening another container" << std::endl;
    } else {
        dup2(containers[index]->getConfig().pipefd_in[1], STDIN_FILENO);
        dup2(containers[index]->getConfig().pipefd_out[0], STDOUT_FILENO);
        dup2(containers[index]->getConfig().pipefd_err[0], STDERR_FILENO);

        if (close(containers[index]->getConfig().pipefd_in[1]) != 0) {
            std::cerr << "listen Mydocker: cannot close file descriptor " << containers[index]->getConfig().pipefd_in[1] << std::endl;
        }
        if (close(containers[index]->getConfig().pipefd_out[0]) != 0) {
            std::cerr << "listen Mydocker: cannot close file descriptor " << containers[index]->getConfig().pipefd_out[0] << std::endl;
        }
        if (close(containers[index]->getConfig().pipefd_err[0]) != 0) {
            std::cerr << "listen Mydocker: cannot close file descriptor " << containers[index]->getConfig().pipefd_err[0] << std::endl;
        }
    }
}

void Mydocker::detach() {
    // socket stuff
}

void Mydocker::list_containers() {
    for(size_t i = 0; i < containers.size(); ++i){
        std::cout << "Container " << i << std::endl;
        std::cout << containers[i]->getConfig() << std::endl;
    }
}
