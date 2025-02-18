#include "planet.hpp"

#include <cstring>
#include <fstream>
#include <iostream>

namespace {

const int BUFFER_SIZE = 256;

}  // namespace

namespace planet {

int Planet::n = 0;

Planet::Planet(char* name, int diametr, bool hasLife, int countOfSatellites)
    : diametr(diametr), hasLife(hasLife), countOfSatellites(countOfSatellites) {
    this->name = new char[std::strlen(name) + 1];
    std::strcpy(this->name, name);

    id = n++;
    std::cout << "Creating planet with args ID=" << id << std::endl;
}

Planet::Planet() {
    id = n++;
    std::cout << "Creating planet without args ID=" << id << std::endl;
}

Planet::~Planet() {
    delete[] name;
    std::cout << "Deleting planet ID=" << id << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Planet& planet) {
    os << planet.id << ". " << planet.name << ": ";
    os << "diametr - " << planet.diametr << ", ";
    os << (planet.hasLife ? "has life" : "has not life") << ", ";
    os << "count of satellites - " << planet.countOfSatellites;

    return os;
}

std::istream& operator>>(std::istream& in, Planet*& planet) {
    char* name = new char[BUFFER_SIZE];
    int diametr{};
    bool hasLife{};
    int countOfSatellites{};

    in >> name >> diametr >> hasLife >> countOfSatellites;
    planet = new Planet(name, diametr, hasLife, countOfSatellites);
    delete[] name;

    return in;
}

bool operator==(const Planet& el1, const Planet& el2) {
    return el1.diametr == el2.diametr && el1.hasLife == el2.hasLife && el1.countOfSatellites == el2.countOfSatellites &&
           std::strcmp(el1.name, el2.name) == 0;
}

bool operator<(const Planet& el1, const Planet& el2) {
    return el1.diametr < el2.diametr;
}

void Planet::readFromFile(const char* filename, Planet** planets, int& size) {
    std::ifstream file(filename);
    int i = 0;
    Planet* planet = nullptr;

    while (!file.eof()) {
        file >> planet;
        planets[i++] = planet;
    }

    size = i;
}

void Planet::writeToFile(const char* filename, Planet** planets, int& size) {
    std::ofstream file(filename);

    for (int i = 0; i < size; i++) {
        file << *planets[i] << std::endl;
    }
}

void Planet::print(Planet**& planets, int& size) {
    for (int i = 0; i < size; i++) {
        std::cout << *planets[i] << std::endl;
    }
}

void Planet::sort(Planet**& planets, int& size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (*planets[j + 1] < *planets[j]) {
                std::swap(planets[j], planets[j + 1]);
            }
        }
    }
}

void Planet::append(Planet**& planets, int& size, Planet* planet) {
    if (planets != nullptr) {
        Planet** buffer = planets;
        planets = new Planet*[size + 1];
        for (int i = 0; i < size; i++) {
            planets[i] = buffer[i];
        }
        planets[size++] = planet;
        delete[] buffer;
    }
}

void Planet::remove(Planet**& planets, int& size, Planet* planet) {
    for (int i = 0; i < size; i++) {
        if (*planets[i] == *planet) {
            for (int j = i; j < size - 1; j++) {
                planets[j] = planets[j + 1];
            }
            size--;
        }
    }
}

}  // namespace planet
