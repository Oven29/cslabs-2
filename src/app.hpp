#pragma once

namespace app {

enum class ProgramMode {
    interactive,
    demonstrative
};

ProgramMode getProgramMode(int argc, char** argv);
void runDemonstrativeMode();
void runInteractiveMode();
void run(int argc, char** argv);

}  // namespace app
