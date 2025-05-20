#include "app.h"

#include <cstring>
#include <iostream>

#include "../src/staff.h"

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
    staff::Staff a("Ivan", 25, 1000);
    staff::Worker worker("Petr", 30, 2000, 5);
    worker.show();
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

}  // namespace app
