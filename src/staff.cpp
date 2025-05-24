#include "staff.h"

#include <cstring>
#include <iostream>

namespace staff {

Staff::Staff(const char* name, int age, int salary) : age(age), salary(salary), name(new char[std::strlen(name) + 1]) {
    std::cout << "Staff() " << name << std::endl;
    std::strcpy(this->name, name);
}

Staff::~Staff() {
    std::cout << "~Staff() " << name << std::endl;
    delete[] name;
}

Staff::Staff(const Staff& other) : Staff(other.name, other.age, other.salary) {
}

Staff& Staff::operator=(const Staff& other) {
    if (this != &other) {
        delete[] name;
        name = new char[std::strlen(other.name) + 1];
        std::strcpy(name, other.name);
        age = other.age;
        salary = other.salary;
    }

    return *this;
}

void Staff::show() const {
    std::cout << "Name: " << name << " Age: " << age << " Salary: " << salary;
}

Worker::Worker(const char* name, int age, int salary, int experience) : Staff(name, age, salary), experience(experience) {
    std::cout << "Worker() " << name << std::endl;
}

Worker::~Worker() {
    std::cout << "~Worker() " << name << std::endl;
}

void Worker::show() const {
    Staff::show();
    std::cout << " Experience: " << experience;
}

Engineer::Engineer(const char* name, int age, int salary, const char* specialization)
    : Staff(name, age, salary), specialization(new char[std::strlen(specialization) + 1]) {
    std::cout << "Engineer() " << name << std::endl;
    std::strcpy(this->specialization, specialization);
}

Engineer::~Engineer() {
    std::cout << "~Engineer() " << name << std::endl;
    delete[] specialization;
}

void Engineer::show() const {
    Staff::show();
    std::cout << " Specialization: " << specialization;
}

Admin::Admin(const char* name, int age, int salary, int countOfSubordinates) : Staff(name, age, salary), countOfSubordinates(countOfSubordinates) {
    std::cout << "Admin() " << name << std::endl;
}

Admin::~Admin() {
    std::cout << "~Admin() " << name << std::endl;
}

void Admin::show() const {
    Staff::show();
    std::cout << " Count of subordinates: " << countOfSubordinates;
}

}  // namespace staff
