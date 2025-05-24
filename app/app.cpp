#include "app.h"

#include <cstring>
#include <iostream>

namespace {

const char* INTERACTIVE_CMD_ARG = "-it";
const int BUFSIZE = 128;

}  // namespace

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
    } else {
        std::cout << "===" << std::endl;
        for (size_t i = 0; i < arr.getSize(); ++i) {
            std::cout << i << " | ";
            arr[i]->show();
            std::cout << std::endl;
        }
    }
}

void remove(vector::Vector<staff::Staff*>& arr, int index) {
    arr.remove(index);
}

void clear(vector::Vector<staff::Staff*>& arr) {
    arr.clear();
}

void add(vector::Vector<staff::Staff*>& arr) {
    staff::Staff* el{};
    char name[BUFSIZE];
    int age{}, salary{};

    switch (getStaffType()) {
        case StaffType::staff: {
            std::cout << "Enter staff (name age salary): ";
            std::cin >> name >> age >> salary;
            el = new staff::Staff(name, age, salary);
            break;
        }
        case StaffType::worker: {
            int experience{};
            std::cout << "Enter worker (name age salary experience): ";
            std::cin >> name >> age >> salary >> experience;
            el = new staff::Worker(name, age, salary, experience);
            break;
        }
        case StaffType::engineer: {
            char specialization[BUFSIZE];
            std::cout << "Enter engineer (name age salary specialization): ";
            std::cin >> name >> age >> salary >> specialization;
            el = new staff::Engineer(name, age, salary, specialization);
            break;
        }
        case StaffType::admin: {
            int countOfSubordinates{};
            std::cout << "Enter admin (name age salary countOfSubordinates): ";
            std::cin >> name >> age >> salary >> countOfSubordinates;
            el = new staff::Admin(name, age, salary, countOfSubordinates);
            break;
        }
    }

    arr.push(el);
}

StaffType getStaffType() {
    while (true) {
        std::cout << "===" << std::endl
                  << "staff - 1 " << std::endl
                  << "worker - 2" << std::endl
                  << "engineer - 3" << std::endl
                  << "admin - 4" << std::endl;

        int type{};
        std::cin >> type;

        if (type >= 1 && type <= 4) {
            return static_cast<StaffType>(type);
        }

        std::cin.clear();
        std::cout << "Invalid choice! Please enter a number between 1 and 4." << std::endl;
    }
}

InteractiveType getInteractiveType() {
    while (true) {
        std::cout << "===" << std::endl
                  << "add - 1 " << std::endl
                  << "remove - 2" << std::endl
                  << "clear - 3" << std::endl
                  << "print - 4" << std::endl
                  << "exit - 5" << std::endl;

        int type{};
        std::cin >> type;

        if (type >= 1 && type <= 5) {
            return static_cast<InteractiveType>(type);
        }

        std::cin.clear();
        std::cout << "Invalid choice! Please enter a number between 1 and 5." << std::endl;
    }
}

void runInteractiveMode() {
    bool running = true;
    vector::Vector<staff::Staff*> arr{};

    while (running) {
        switch (getInteractiveType()) {
            case InteractiveType::add:
                add(arr);
                break;
            case InteractiveType::remove: {
                std::cout << "Enter index to remove: ";
                int index{};
                std::cin >> index;
                remove(arr, index);
                std::cout << "Removed element with index " << index << std::endl;
                break;
            }
            case InteractiveType::clear:
                clear(arr);
                break;
            case InteractiveType::print:
                print(arr);
                break;
            case InteractiveType::exit:
                running = false;
                break;
        }
    }
}

}  // namespace app
