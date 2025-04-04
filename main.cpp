#include "app/app.h"

#include <iostream>

int main(int argc, char** argv) {
    try {
        app::run(argc, argv);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
