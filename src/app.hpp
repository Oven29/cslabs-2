#pragma once

#include "../house/house.hpp"

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
    edit = 7,
    exit = 8
};

enum class FieldToEdit {
    number = 1,
    countOfFloors = 2,
    countOfApartaments = 3,
};

ProgramMode getProgramMode(int argc, char** argv);
void runDemonstrativeMode();
InteractiveType getInteractiveType();
void editHouse(house::House*& el);
void runInteractiveMode();
void run(int argc, char** argv);

}  // namespace app
