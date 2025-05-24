#pragma once

#include "../collections/vector.hpp"
#include "../src/staff.h"

namespace app {

enum class ProgramMode {
    interactive,
    demonstrative
};

ProgramMode getProgramMode(int argc, char** argv);
void runDemonstrativeMode();
void runInteractiveMode();
void run(int argc, char** argv);

void print(vector::Vector<staff::Staff*>& arr);
void remove(vector::Vector<staff::Staff*>& arr, int index);
void clear(vector::Vector<staff::Staff*>& arr);

enum class InteractiveType {
    add = 1,
    remove = 2,
    clear = 3,
    print = 4,
    exit = 5,
};

enum class StaffType {
    staff = 1,
    worker = 2,
    engineer = 3,
    admin = 4
};

InteractiveType getInteractiveType();
StaffType getStaffType();
void add(vector::Vector<staff::Staff*>& arr);

}  // namespace app
