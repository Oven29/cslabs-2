#include "app.h"

#include <cstring>
#include <iostream>

namespace {

const char* INTERACTIVE_CMD_ARG = "-it";

}

namespace app {

ProgramMode getProgramMode(int argc, char** argv) {
    if (argc == 2 && std::strcmp(argv[1], INTERACTIVE_CMD_ARG) == 0) {
        return ProgramMode::interactive;
    }

    return ProgramMode::demonstrative;
}

void runDemonstrativeMode() {
    std::cout << "Demonstrative mode" << std::endl;
    vector::Vector<staff::Staff*> arr;

    arr.push(new staff::Staff("Ivan", 25, 1000));
    arr.push(new staff::Worker("Petr", 30, 2000, 5));
    arr.push(new staff::Engineer("Sergey", 35, 3000, "C++"));
    arr.push(new staff::Admin("Olga", 40, 5000, 10));
    print(arr);
    std::cout << "Removing element with index 2" << std::endl;
    remove(arr, 2);
    print(arr);
    std::cout << "Clearing" << std::endl;
    clear(arr);
    print(arr);
}

void runInteractiveMode() {
    std::cout << "Interactive mode" << std::endl;
}

void run(int argc, char** argv) {
    switch (getProgramMode(argc, argv)) {
        case ProgramMode::interactive: {
            std::cout << "Welcome!" << std::endl;
            runInteractiveMode();
            break;
        }
        case ProgramMode::demonstrative:
            runDemonstrativeMode();
            break;
    }
}

void print(vector::Vector<staff::Staff*>& arr) {
    if (arr.getSize() == 0) {
        std::cout << "Vector is empty" << std::endl;
        return;
    }
    for (size_t i = 0; i < arr.getSize(); ++i) {
        std::cout << i << " | ";
        arr[i]->show();
        std::cout << std::endl;
    }
}

void remove(vector::Vector<staff::Staff*>& arr, int index) {
    arr.remove(index);
}

void clear(vector::Vector<staff::Staff*>& arr) {
    arr.clear();
}

}  // namespace app
