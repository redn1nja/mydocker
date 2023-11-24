#include <iostream>
#include "mydocker.h"
int main(){
    Mydocker mydocker;
    mydocker.create(Mycontainer{std::vector<std::string>{"./build/test_bin"},
                                std::vector<std::vector<char*>>{{"./build/test_bin", nullptr}},
                                std::vector<MycontainerConfig>{{std::vector<std::string>{}, ""}}}.clone());
    mydocker.run(0);
    return 0;
}