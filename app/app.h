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

}  // namespace app
