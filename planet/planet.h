#pragma once

#include <iostream>

namespace planet {

class Planet {
 private:
    const char* name;
    int diametr;
    bool hasLife;
    int countOfSatellites;

 public:
    Planet(const char* name, int diametr, bool hasLife, int countOfSatellites);
    friend std::ostream& operator<<(std::ostream& os, const Planet& vector);
};

}  // namespace planet
