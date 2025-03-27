#pragma once

#include <iostream>

namespace fraction {

const int N_DEC = 4;
const int MAX_INT = 1000000;

class Fraction {
 private:
    bool positive;
    int whole, numerator, denominator;

    void simplify();
    void checkCorrectly();
    void parseString(const char* str);

 public:
    Fraction();
    Fraction(int whole, int numerator, int denominator);
    Fraction(const char* str);
    Fraction(int numerator, int denominator);
    Fraction(double num);

    Fraction operator+(const Fraction& other) const;
    Fraction operator+(double number) const;
    Fraction operator+(int number) const;
    friend Fraction operator+(double number, const Fraction& other);
    friend Fraction operator+(int number, const Fraction& other);

    void operator+=(const Fraction& other);
    void operator+=(double number);

    friend std::ostream& operator<<(std::ostream& os, const Fraction& fraction);
    friend std::istream& operator>>(std::istream& is, Fraction& fraction);
};

}  // namespace fraction
