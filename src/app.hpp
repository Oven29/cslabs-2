#pragma once

namespace app {

enum class ProgramMode {
    interactive,
    demonstrative
};

enum class InteractiveType {
    print = 1,
    read = 2,
    write = 3,
    append = 4,
    remove = 5,
    sort = 6,
    exit = 7
};

ProgramMode getProgramMode(int argc, char** argv);
void runDemonstrativeMode();
InteractiveType getInteractiveType();
void runInteractiveMode();
void run(int argc, char** argv);

}  // namespace app
