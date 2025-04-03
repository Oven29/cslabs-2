#pragma once

#include <iostream>
#include "../collections/vector.hpp"
#include "term.h"

namespace polynomial {

enum class PolynomialOrder {
   ascending,
   decreasing,
};

class Polynomial {
 private:
    vector::Vector<term::Term>* terms;
    int degree;
    PolynomialOrder order;

 public:
    Polynomial();
    Polynomial(int t);
    Polynomial(term::Term t);
    Polynomial(const Polynomial& other);
    ~Polynomial();

    term::Term* begin();
    term::Term* end();

    int getDegree();
    void setOrder(PolynomialOrder order);

    Polynomial& operator=(const Polynomial& other);

    friend Polynomial operator+(Polynomial& el1, Polynomial& el2);
    friend Polynomial operator*(Polynomial& el1, Polynomial& el2);
    void operator+=(Polynomial& other);
    void operator*=(Polynomial& other);

    Polynomial& operator+(const term::Term& other);
    Polynomial& operator*(const term::Term& other);
    void operator+=(const term::Term& other);
    void operator*=(const term::Term& other);

    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);
    friend std::istream& operator>>(std::istream& is, Polynomial& poly);
};

}  // namespace polynomial
