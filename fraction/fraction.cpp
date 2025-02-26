#include "fraction.hpp"
#include <cmath>
#include <cstring>

namespace {

const char MINUS = '-';
const char SPACE = ' ';
const char SLASH = '/';

const int BUF_SIZE = 256;

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}

bool isNumber(const char c) {
    return c >= '0' && c <= '9';
}

int toInt(const char c) {
    return static_cast<int>(c) - 48;
}

bool isCharInString(const char* str, char ch) {
    return std::strchr(str, ch) != nullptr;
}

enum class ParseState {
    whole,
    numerator,
    denominator,
};

}  // namespace

namespace fraction {

void Fraction::simplify() {
    int g = gcd(numerator, denominator);

    numerator /= g;
    denominator /= g;
    whole += static_cast<int>(numerator / denominator);
    numerator %= denominator;
}

void Fraction::checkCorrectly() {
    if (denominator == 0) {
        throw std::invalid_argument("Denominator can't be zero");
    }
}

void Fraction::parseString(const char* str) {
    whole = 0;
    numerator = 0;
    denominator = 1;

    int strLen = std::strlen(str);
    bool negative = false;
    ParseState state = isCharInString(str, SPACE) ? ParseState::whole : ParseState::numerator;

    for (int i = 0; i < strLen; i++) {
        if (str[i] == MINUS && i == 0) {
            negative = true;
        } else if (str[i] == SPACE && state == ParseState::whole) {
            state = ParseState::numerator;
        } else if (str[i] == SLASH && state == ParseState::numerator) {
            state = ParseState::denominator;
        } else if (isNumber(str[i])) {
            switch (state) {
                case ParseState::whole:
                    whole = whole * 10 + toInt(str[i]);
                    break;
                case ParseState::numerator:
                    numerator = numerator * 10 + toInt(str[i]);
                    break;
                case ParseState::denominator:
                    denominator = denominator * 10 + toInt(str[i]);
                    break;
            }
        } else {
            throw std::invalid_argument("Invalid input string");
        }
    }

    if (negative && whole != 0) {
        whole = -1 * whole;
    } else if (negative) {
        numerator = -1 * numerator;
    }
}

Fraction::Fraction(int whole, int numerator, int denominator) : whole(whole), numerator(numerator), denominator(denominator) {
    checkCorrectly();
    simplify();
}

Fraction::Fraction(const char* str) {
    parseString(str);
    checkCorrectly();
    simplify();
}

Fraction::Fraction(int numerator = 0, int denominator = 1) : whole(0), numerator(numerator), denominator(denominator) {
    checkCorrectly();
    simplify();
}

Fraction::Fraction(double num) {
    whole = 0;
    int factor = std::pow(10, N_DEC);
    numerator = static_cast<int>(num * factor);
    denominator = factor;

    simplify();
}

Fraction Fraction::operator+(const Fraction& other) const {
    return Fraction(this->whole + other.whole, this->numerator * other.denominator + other.numerator * this->denominator,
                    this->denominator * other.denominator);
}

Fraction Fraction::operator+(double number) const {
    return *this + Fraction(number);
}

Fraction Fraction::operator+(int number) const {
    return *this + Fraction(number, 0, 1);
}

Fraction operator+(double number, const Fraction& other) {
    return other + number;
}

Fraction operator+(int number, const Fraction& other) {
    return other + number;
}

void Fraction::operator+=(const Fraction& other) {
    *this = *this + other;
}

void Fraction::operator+=(double number) {
    *this = *this + number;
}

std::ostream& operator<<(std::ostream& os, const Fraction& fraction) {
    if (fraction.whole != 0) {
        os << fraction.whole << SPACE;
    }
    os << fraction.numerator << SLASH << fraction.denominator;
    return os;
}

std::istream& operator>>(std::istream& is, Fraction& fraction) {
    char str[BUF_SIZE];
    is.getline(str, sizeof(str));
    fraction = Fraction(str);
    return is;
}

}  // namespace fraction
