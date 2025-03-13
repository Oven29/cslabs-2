#pragma once

#include <iostream>

namespace house {

class House {
 private:
    char* street;
    int number;
    int countOfFloors;
    int countOfApartaments;
    int id;
    static int n;

 public:
    House(char* street, int number, int countOfFloors, int countOfApartaments);
    House();
    House(const House& house);
    ~House();

    void setStreet(char* street);
    void setNumber(int number);
    void setCountOfFloors(int countOfFloors);
    void setCountOfApartaments(int countOfApartaments);

    int getId();

    friend std::ostream& operator<<(std::ostream& os, const House& house);
    friend std::istream& operator>>(std::istream& in, House& house);
    friend bool operator==(const House& el1, const House& el2);
    friend bool operator<(const House& el1, const House& el2);
    House& operator=(const House& house);

    static void readFromFile(const char* filename, House** houses, int& size);
    static void writeToFile(const char* filename, House** houses, int& size);

    static void print(House**& houses, int& size);
    static void sort(House**& houses, int& size);

    static void append(House**& houses, int& size, House* house);
    static bool remove(House**& houses, int& size, House* house);
};

}  // namespace house
