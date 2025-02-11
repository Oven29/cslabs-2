#include <iostream>
#include "planet/planet.h"

int main() {
    planet::Planet mercury = planet::Planet("Mercury", 4878, false, 0);

    std::cout << mercury << std::endl;

    return 0;
}
