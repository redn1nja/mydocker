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
    std::cout<<containers[index]->getPID()<<std::endl;
    if (attached_container_index != -1) {
        std::cerr << "Failed to listen: already listening another container" << std::endl;
    } else {
        std::cout<<"listening "<<index<<std::endl;
        std::cout << "in: " << containers[index]->getConfig().pipefd_in[1] << " out: " << containers[index]->getConfig().pipefd_out[0]<< " err: " << containers[index]->getConfig().pipefd_err[0] << std::endl;
        if (dup2(containers[index]->getConfig().pipefd_in[1], STDIN_FILENO) == -1) {
            dprintf(fd, "Failed to listen: cannot dup2 STDIN_FILENO %s \n", strerror(errno));
        }
        if(dup2( containers[index]->getConfig().pipefd_out[0], STDOUT_FILENO) == -1) {
            dprintf(fd, "Failed to listen: cannot dup2 STDOUT_FILENO %s \n", strerror(errno));
        }
        if(dup2(containers[index]->getConfig().pipefd_err[0], STDERR_FILENO) == -1) {
            dprintf(fd,"Failed to listen: cannot dup2 STDERR_FILENO %s \n", strerror(errno));
        }
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
    if (attached_container_index == -1){
        std::cerr << "Failed to detach: not listening any container" << std::endl;
        return;
    }
    dup2 (STDIN_FILENO, containers[attached_container_index]->getConfig().get_in());
    dup2 (STDOUT_FILENO, containers[attached_container_index]->getConfig().get_out());
    dup2 (STDERR_FILENO, containers[attached_container_index]->getConfig().get_err());
//    if (close(containers[attached_container_index]->getConfig().get_in()) != 0) {

//        std::cerr << "detach Mydocker: cannot close file descriptor " << containers[attached_container_index]->getConfig().get_in() << std::endl;
//    }
//    if (close(containers[attached_container_index]->getConfig().get_out()) != 0) {
//        std::cerr << "detach Mydocker: cannot close file descriptor " << containers[attached_container_index]->getConfig().get_out() << std::endl;
//    }
//    if (close(containers[attached_container_index]->getConfig().get_err()) != 0) {
//        std::cerr << "detach Mydocker: cannot close file descriptor " << containers[attached_container_index]->getConfig().get_err() << std::endl;
//    }
    attached_container_index = -1;
}

void Mydocker::list_containers() {
    for (size_t i = 0; i < containers.size(); ++i) {
        std::cout << "Container " << i << std::endl;
        std::cout << containers[i]->getConfig() << std::endl;
    }
}
