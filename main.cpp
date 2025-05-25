#include "src/app.h"

#include <iostream>

int main() {
    try {
        app::run();
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
