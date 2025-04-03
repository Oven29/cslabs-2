#pragma once

#include <iostream>

namespace term {

bool isTermSymbol(const char c);

class Term {
 private:
    int k, n;
    friend class Polynomial;

 public:
    Term();
    Term(int k);
    Term(int k, int n);
    ~Term() = default;

    int getK() const;
    int getN() const;

    static Term parseTerm(char*& buf);

    friend Term operator+(const Term& el1, const Term& el2);
    friend Term operator*(const Term& el1, const Term& el2);
    void operator+=(const Term& other);
    void operator*=(const Term& other);

   bool operator==(const Term& other) const;
    bool operator>(const Term& other) const;
    bool operator<(const Term& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Term& term);
    friend std::istream& operator>>(std::istream& is, Term& term);
};

}  // namespace term
