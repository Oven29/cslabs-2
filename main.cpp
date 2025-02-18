#include "planet/planet.hpp"

#include <cstring>
#include <iostream>

int main() {
    const int BUFFER_SIZE = 256;
    const char* filename = "source.txt";

    planet::Planet** solarSystem = new planet::Planet*[BUFFER_SIZE];
    int size = 0;
    planet::Planet::readFromFile(filename, solarSystem, size);

    std::cout << std::endl << "Before sorting" << std::endl;
    planet::Planet::print(solarSystem, size);
    planet::Planet::sort(solarSystem, size);
    std::cout << std::endl << "After sorting" << std::endl;
    planet::Planet::print(solarSystem, size);

    char* plutoName = new char[6];
    std::strcpy(plutoName, "Pluno");
    planet::Planet* pluto = new planet::Planet(plutoName, 2280, 0, 1);
    delete plutoName;
    std::cout << std::endl << *pluto << " - appending to solar system" << std::endl << std::endl;
    planet::Planet::append(solarSystem, size, pluto);
    planet::Planet::print(solarSystem, size);
    planet::Planet* removePlanet = solarSystem[std::min(size, 1)];
    std::cout << std::endl << *removePlanet<< " - removing from solar system" << std::endl << std::endl;
    planet::Planet::remove(solarSystem, size, removePlanet);
    planet::Planet::print(solarSystem, size);

    delete[] solarSystem;

    return 0;
}
