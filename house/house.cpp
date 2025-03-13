#include "house.hpp"

#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>

namespace {

const int BUFFER_SIZE = 256;
const int MAX_STREET_LEN = 20;

}  // namespace

namespace house {

int House::n = 0;

House::House(char* street, int number, int countOfFloors, int countOfApartaments)
    : number(number), countOfFloors(countOfFloors), countOfApartaments(countOfApartaments) {
    setStreet(street);
    id = n++;
}
// удаление массива

House::House() {
    id = n++;
}

House::House(const House& house) : number(house.number), countOfFloors(house.countOfFloors), countOfApartaments(house.countOfApartaments) {
    setStreet(house.street);
    id = n++;
}

House::~House() {
    delete[] street;
}

void House::setStreet(char* street) {
    if (this->street != nullptr) {
        delete[] this->street;
    }
    this->street = new char[std::strlen(street) + 1];
    std::strcpy(this->street, street);
}

void House::setNumber(int number) {
    this->number = number;
}

void House::setCountOfFloors(int countOfFloors) {
    this->countOfFloors = countOfFloors;
}

void House::setCountOfApartaments(int countOfApartaments) {
    this->countOfApartaments = countOfApartaments;
}

int House::getId() {
    return this->id;
}

std::ostream& operator<<(std::ostream& os, const House& house) {
    os << std::setw(3) << house.id;
    os << std::setw(MAX_STREET_LEN + 1) << house.street;
    os << std::setw(7) << house.number;
    os << std::setw(7) << house.countOfFloors;
    os << std::setw(12) << house.countOfApartaments;

    return os;
}

std::istream& operator>>(std::istream& in, House*& house) {
    char* street = new char[BUFFER_SIZE];
    int number{}, countOfFloors{}, countOfApartaments{};

    in >> street >> number >> countOfFloors >> countOfApartaments;

    if (strlen(street) > MAX_STREET_LEN) {
        throw std::runtime_error("Street name is too long");
    }

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

House& House::operator=(const House& house) {
    if (this != &house) {
        this->id = house.id;
        setStreet(house.street);
        this->number = house.number;
        this->countOfFloors = house.countOfFloors;
        this->countOfApartaments = house.countOfApartaments;
    }

    return *this;
}

void House::readFromFile(const char* filename, House** houses, int& size) {
    std::ifstream file(filename);

    if (!file) {
        throw std::runtime_error("Can't open file");
    }

    House* house = nullptr;
    House** buffer = new House*[BUFFER_SIZE];

    for (int i = 0; i < size; i++) {
        buffer[i] = houses[i];
    }

    while (!file.eof()) {
        file >> house;
        buffer[size++] = house;
    }

    delete[] houses;
    houses = new House*[size];
    for (int i = 0; i < size; i++) {
        houses[i] = buffer[i];
    }
    delete[] buffer;
}

void House::writeToFile(const char* filename, House** houses, int& size) {
    std::ofstream file(filename);

    if (!file) {
        throw std::runtime_error("Can't open file");
    }

    for (int i = 0; i < size; i++) {
        file << houses[i]->street << ' ' << houses[i]->number << ' ' << houses[i]->countOfFloors << ' ' << houses[i]->countOfApartaments;
        if (i != size - 1) {
            file << std::endl;
        }
    }
}

void House::print(House**& houses, int& size) {
    std::cout << " id" << std::setw(MAX_STREET_LEN + 1) << "street" << " number floors apartaments" << std::endl;

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

bool House::remove(House**& houses, int& size, House* house) {
    for (int i = 0; i < size; i++) {
        if (*houses[i] == *house) {
            for (int j = i; j < size - 1; j++) {
                houses[j] = houses[j + 1];
            }
            size--;
            return true;
        }
    }
    return false;
}

}  // namespace house
