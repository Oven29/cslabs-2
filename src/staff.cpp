#include "staff.h"

#include <cstring>
#include <iostream>

namespace staff {

Staff::Staff(const char* name, int age, int salary) : age(age), salary(salary), name(new char[std::strlen(name) + 1]) {
    std::cout << "Staff()" << std::endl;
    std::strcpy(this->name, name);
}

Staff::~Staff() {
    std::cout << "~Staff()" << std::endl;
    delete[] name;
}

void Staff::show() const {
    std::cout << "Name: " << name << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Salary: " << salary << std::endl;
}

Worker::Worker(const char* name, int age, int salary, int experience) : Staff(name, age, salary), experience(experience) {
    std::cout << "Worker()" << std::endl;
}

Worker::~Worker() {
    std::cout << "~Worker()" << std::endl;
}

void Worker::show() const {
    Staff::show();
    std::cout << "Experience: " << experience << std::endl;
}

Engineer::Engineer(const char* name, int age, int salary, const char* specialization)
    : Staff(name, age, salary), specialization(new char[std::strlen(specialization) + 1]) {
    std::cout << "~Engineer()" << std::endl;
    std::strcpy(this->specialization, specialization);
}

Engineer::~Engineer() {
    std::cout << "~Engineer()" << std::endl;
    delete[] specialization;
}

void Engineer::show() const {
    Staff::show();
    std::cout << "Specialization: " << specialization << std::endl;
}

Admin::Admin(const char* name, int age, int salary, int countOfSubordinates) : Staff(name, age, salary), countOfSubordinates(countOfSubordinates) {
    std::cout << "Admin()" << std::endl;
}

Admin::~Admin() {
    std::cout << "~Admin()" << std::endl;
}

void Admin::show() const {
    Staff::show();
    std::cout << "Count of subordinates: " << countOfSubordinates << std::endl;
}

}  // namespace staff
