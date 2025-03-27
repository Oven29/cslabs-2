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
    if (whole > MAX_INT || denominator > MAX_INT || numerator > MAX_INT) {
        throw std::invalid_argument("Fraction is too big");
    }
}

void Fraction::parseString(const char* str) {
    whole = 0;
    numerator = 0;
    denominator = 0;
    positive = true;

    int strLen = std::strlen(str);
    ParseState state = isCharInString(str, SPACE) ? ParseState::whole : ParseState::numerator;

    for (int i = 0; i < strLen; i++) {
        if (str[i] == MINUS && i == 0) {
            positive = false;
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
        // std::cout << "D:" << str[i] << " " << whole << " " << numerator << " " << denominator << std::endl;
    }

    if (state == ParseState::numerator) {
        throw std::invalid_argument("Invalid input string");
    }
}

Fraction::Fraction() : whole(0), numerator(0), denominator(1), positive(true) {
}

Fraction::Fraction(int whole, int numerator, int denominator)
    : whole(abs(whole)), numerator(abs(numerator)), denominator(abs(denominator)), positive(whole >= 0) {
    checkCorrectly();
    simplify();
}

Fraction::Fraction(const char* str) {
    parseString(str);
    checkCorrectly();
    simplify();
}

Fraction::Fraction(int numerator, int denominator) : whole(0), numerator(abs(numerator)), denominator(abs(denominator)), positive(numerator >= 0) {
    checkCorrectly();
    simplify();
}

Fraction::Fraction(double num) : whole(0) {
    int factor = std::pow(10, N_DEC);
    numerator = abs(static_cast<int>(num * factor));
    denominator = factor;
    positive = num >= 0;

    simplify();
}

Fraction Fraction::operator+(const Fraction& other) const {
    return Fraction((this->positive ? 1 : -1) * (this->whole * this->denominator + this->numerator) * other.denominator +
                        (other.positive ? 1 : -1) * (other.whole * other.denominator + other.numerator) * this->denominator,
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
    if (!fraction.positive) {
        os << MINUS;
    }
    if (fraction.whole != 0) {
        os << fraction.whole << SPACE;
    }
    if (fraction.numerator != 0) {
        os << fraction.numerator << SLASH << fraction.denominator;
    }
    if (fraction.numerator == 0 && fraction.whole == 0) {
        os << 0;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Fraction& fraction) {
    char str[BUF_SIZE];
    is.getline(str, sizeof(str));
    fraction = Fraction(str);
    return is;
}

}  // namespace fraction
