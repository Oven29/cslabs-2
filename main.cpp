#include <iostream>
#include "src/app.hpp"

int main(int argc, char** argv) {
    try {
        app::run(argc, argv);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
