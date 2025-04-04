#include "term.h"

#include <cstring>

namespace {

const int BUF_SIZE = 1024;

const char SPACE = ' ';
const char X = 'x';
const char MINUS = '-';
const char DEGREE = '^';

enum class parseState {
    k,
    d,  // wait ^
    n
};

bool isNumber(const char c) {
    return c >= '0' && c <= '9';
}

int toInt(const char c) {
    return static_cast<int>(c) - static_cast<int>('0');
}

}  // namespace

namespace term {

bool isTermSymbol(const char c) {
    return isNumber(c) || c == SPACE || c == X || c == MINUS || c == DEGREE;
}

Term::Term() : k(0), n(0){};

Term::Term(int k) : k(k), n(0){};

Term::Term(int k, int n) : k(k), n(n){};

int Term::getK() const {
    return this->k;
}

int Term::getN() const {
    return this->n;
}

Term Term::parseTerm(char*& buf) {
    parseState state = parseState::k;
    int k = 0, n = 0;
    bool negativeK = false, negativeN = false;

    while (strlen(buf)) {
        if (*buf == MINUS && state == parseState::k) {
            negativeK = true;
        } else if (*buf == MINUS && state == parseState::n) {
            negativeN = true;
        } else if (*buf == X && state == parseState::k) {
            state = parseState::d;
        } else if (*buf == DEGREE && state == parseState::d) {
            state = parseState::n;
        } else if (isNumber(*buf) && state == parseState::k) {
            k = k * 10 + toInt(*buf);
        } else if (isNumber(*buf) && state == parseState::n) {
            n = n * 10 + toInt(*buf);
        } else if (*buf != SPACE) {
            break;
        }
        ++buf;
    }

    return Term((negativeK ? -1 : 1) * ((k == 0 && n != 0) ? 1 : k), (negativeN ? -1 : 1) * (state == parseState::d ? 1 : n));
}

Term operator+(const Term& el1, const Term& el2) {
    if (el1.n != el2.n) {
        throw std::runtime_error("Terms with different powers cannot be added!");
    }

    return Term(el1.k + el2.k, el1.n);
}

Term operator*(const Term& el1, const Term& el2) {
    return Term(el1.k * el2.k, el1.n + el2.n);
}

void Term::operator+=(const Term& other) {
    *this = *this + other;
}

void Term::operator*=(const Term& other) {
    *this = *this * other;
}

bool Term::operator==(const Term& other) const {
    return this->k == other.k && this->n == other.n;
}

bool Term::operator>(const Term& other) const {
    if (this->n == other.n) {
        return this->k > other.k;
    }
    return this->n > other.n;
}

bool Term::operator<(const Term& other) const {
    return !(*this > other) && !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Term& term) {
    if (term.k == 0) {
        os << 0;
    } else if (term.n == 0) {
        os << term.k;
    } else {
        if (term.k != 1) {
            os << term.k;
        }
        os << X;
        if (term.n != 1) {
            os << DEGREE << term.n;
        }
    }

    return os;
}

std::istream& operator>>(std::istream& is, Term& term) {
    char* buffer = new char[BUF_SIZE];
    is.getline(buffer, BUF_SIZE);
    term = Term::parseTerm(buffer);
    return is;
}

}  // namespace term
