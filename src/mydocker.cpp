// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "mydocker.h"

void Mydocker::stop(size_t index) {
  if (kill(containers[index]->getPID(), SIGSTOP) == -1) {
    std::cerr << "Failed to stop container" << std::endl;
  }
}

void Mydocker::resume(size_t index) {
  if (kill(containers[index]->getPID(), SIGCONT) == -1){
    std::cerr << "Failed to resume container" << std::endl;
  }
}

void Mydocker::kill_container(size_t index) {
  if (kill(containers[index]->getPID(), SIGKILL) == -1){
    std::cerr << "Failed to kill container" << std::endl;
  }
}
