// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include "mydocker.h"

int main() {
    Mydocker mydocker;
    mydocker.create(Mycontainer{std::vector<std::string>{"./build/test_bin"},
                                std::vector<std::vector<char *>>{{"./build/test_bin", nullptr}},
                                std::vector<MycontainerConfig>{{std::vector<std::string>{}, ""}}}.clone());
    mydocker.run(0);
    return 0;
}