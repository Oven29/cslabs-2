#include "house.hpp"

#include <cstring>
#include <fstream>
#include <iostream>

namespace {

const int BUFFER_SIZE = 256;

}  // namespace

namespace house {

int House::n = 0;

House::House(char* street, int number, int countOfFloors, int countOfApartaments)
    : number(number), countOfFloors(countOfFloors), countOfApartaments(countOfApartaments) {
    this->street = new char[std::strlen(street) + 1];
    std::strcpy(this->street, street);

    id = n++;
}

House::House() {
    id = n++;
}

House::~House() {
    delete[] street;
}

std::ostream& operator<<(std::ostream& os, const House& house) {
    os << house.id << ". " << house.street << ' ' << house.number;
    os << "(" << house.countOfFloors << " floors, " << house.countOfApartaments << " apartaments)";

    return os;
}

std::istream& operator>>(std::istream& in, House*& house) {
    char* street = new char[BUFFER_SIZE];
    int number{};
    int countOfFloors{};
    int countOfApartaments{};

    in >> street >> number >> countOfFloors >> countOfApartaments;
    house = new House(street, number, countOfFloors, countOfApartaments);
    delete[] street;

    return in;
}

bool operator==(const House& el1, const House& el2) {
    return el1.number == el2.number && el1.countOfFloors == el2.countOfFloors && el1.countOfApartaments == el2.countOfApartaments &&
           std::strcmp(el1.street, el2.street) == 0;
}

bool operator<(const House& el1, const House& el2) {
    return el1.countOfApartaments < el2.countOfApartaments;
}

void House::readFromFile(const char* filename, House** houses, int& size) {
    std::ifstream file(filename);
    int i = 0;
    House* house = nullptr;

    while (!file.eof()) {
        file >> house;
        houses[i++] = house;
    }

    size = i;
}

void House::writeToFile(const char* filename, House** houses, int& size) {
    std::ofstream file(filename);

    for (int i = 0; i < size; i++) {
        file << houses[i]->street << ' ' << houses[i]->number << ' ' << houses[i]->countOfFloors << ' ' << houses[i]->countOfApartaments;
        if (i != size - 1) {
            file << std::endl;
        }
    }
}

void House::print(House**& houses, int& size) {
    for (int i = 0; i < size; i++) {
        std::cout << *houses[i] << std::endl;
    }
}

void House::sort(House**& houses, int& size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (*houses[j + 1] < *houses[j]) {
                std::swap(houses[j], houses[j + 1]);
            }
        }
    }
}

void House::append(House**& houses, int& size, House* house) {
    if (houses != nullptr) {
        House** buffer = houses;
        houses = new House*[size + 1];
        for (int i = 0; i < size; i++) {
            houses[i] = buffer[i];
        }
        houses[size++] = house;
        delete[] buffer;
    }
}

void House::remove(House**& houses, int& size, House* house) {
    for (int i = 0; i < size; i++) {
        if (*houses[i] == *house) {
            for (int j = i; j < size - 1; j++) {
                houses[j] = houses[j + 1];
            }
            size--;
        }
    }
}

}  // namespace house
