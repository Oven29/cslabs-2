#pragma once

#include <iostream>
#include <string>

namespace app {

void run();

void task1();
void task2();
void task3();
void task4();
void task5();
void task6();
void task7();
void task8();
void task9();

class Box {
    double a;  // ширина
    double b;  // высота
    double c;  // длина
 public:
    Box() : a(0), b(0), c(0) {}
    Box(double a, double b, double c) : a(a), b(b), c(c) {}

    bool operator<(const Box& other) const;
    bool operator==(const Box& other) const;
    double getVolume() const;
    friend std::ostream& operator<<(std::ostream& os, const Box& box);
};

class Graduate {
    std::string name;  // фамилия
    double rating;     // рейтинг
 public:
    Graduate() : name(""), rating(0) {}
    Graduate(std::string name, double rating) : name(name), rating(rating) {}

    bool operator<(const Graduate& other) const;
    bool operator==(const Graduate& other) const;
    double getRating() const;
    void setRating(double rating);
    friend std::ostream& operator<<(std::ostream& os, const Graduate& graduate);
};

}  // namespace app
