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
        std::cout<<"listening "<<index<<std::endl;
//        auto in = dup(STDIN_FILENO);
//        auto out = dup(STDOUT_FILENO);
//        auto err = dup(STDERR_FILENO);
//        containers[index]->getConfig().set_in(in);
//        containers[index]->getConfig().set_out(out);
//        containers[index]->getConfig().set_err(err);
//        std::cout<< "old in " << in << " old out " << out << " old err " << err << std::endl;
        std::cout << "in: " << containers[index]->getConfig().pipefd_in[1] << " out: " << containers[index]->getConfig().pipefd_out[0]<< " err: " << containers[index]->getConfig().pipefd_err[0] << std::endl;
//        dup2(containers[index]->getConfig().pipefd_in[1], STDIN_FILENO);
//        dup2(containers[index]->getConfig().pipefd_out[0], STDOUT_FILENO);
//        dup2(containers[index]->getConfig().pipefd_err[0], STDERR_FILENO);
//        if (close(containers[index]->getConfig().pipefd_in[1]) != 0) {
//            std::cerr << "listen Mydocker: cannot close file descriptor " << containers[index]->getConfig().pipefd_in[1]
//                      << std::endl;
//        }
//        if (close(containers[index]->getConfig().pipefd_out[0]) != 0) {
//            std::cerr << "listen Mydocker: cannot close file descriptor "
//                      << containers[index]->getConfig().pipefd_out[0] << std::endl;
//        }z
//        if (close(containers[index]->getConfig().pipefd_err[0]) != 0) {
//            std::cerr << "listen Mydocker: cannot close file descriptor "
//                      << containers[index]->getConfig().pipefd_err[0] << std::endl;
//        }
        attached_container_index = index;
    }
}

void Mydocker::detach() {
//    dup2(containers[attached_container_index]->getConfig().get_in(), STDIN_FILENO);
//    dup2(containers[attached_container_index]->getConfig().get_out(), STDOUT_FILENO);
//    dup2(containers[attached_container_index]->getConfig().get_err(), STDERR_FILENO);
    if (close(containers[attached_container_index]->getConfig().get_in()) != 0) {
        std::cerr << "detach Mydocker: cannot close file descriptor " << containers[attached_container_index]->getConfig().get_in() << std::endl;
    }
    if (close(containers[attached_container_index]->getConfig().get_out()) != 0) {
        std::cerr << "detach Mydocker: cannot close file descriptor " << containers[attached_container_index]->getConfig().get_out() << std::endl;
    }
    if (close(containers[attached_container_index]->getConfig().get_err()) != 0) {
        std::cerr << "detach Mydocker: cannot close file descriptor " << containers[attached_container_index]->getConfig().get_err() << std::endl;
    }
    attached_container_index = -1;
}

void Mydocker::list_containers() {
    for (size_t i = 0; i < containers.size(); ++i) {
        std::cout << "Container " << i << std::endl;
        std::cout << containers[i]->getConfig() << std::endl;
    }
}
