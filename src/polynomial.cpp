#include "polynomial.h"

namespace polynomial {

Polynomial::Polynomial() : terms(new vector::Vector<term::Term>()), degree(0), ascendingOrder(true) {
}

Polynomial::Polynomial(int t) : Polynomial(term::Term(t)) {
}

Polynomial::Polynomial(term::Term t) : Polynomial() {
    this->terms->push(t);
    this->degree = t.getN();
}

Polynomial::Polynomial(const Polynomial& other) : degree(other.degree), ascendingOrder(other.ascendingOrder) {
    this->terms = new vector::Vector<term::Term>(*other.terms);
}

Polynomial::~Polynomial() {
    delete this->terms;
}

term::Term* Polynomial::begin() {
    return this->terms->begin();
}

term::Term* Polynomial::end() {
    return this->terms->end();
}

int Polynomial::getDegree() {
    return this->degree;
}

Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        delete this->terms;
        this->terms = new vector::Vector<term::Term>(*other.terms);
        this->degree = other.degree;
        this->ascendingOrder = other.ascendingOrder;
    }
    return *this;
}

Polynomial operator+(Polynomial& el1, Polynomial& el2) {
    Polynomial result;

    for (term::Term t : el1) {
        result += t;
    }
    for (term::Term t : el2) {
        result += t;
    }

    return result;
}

Polynomial operator*(Polynomial& el1, Polynomial& el2) {
    Polynomial result;

    for (term::Term t1 : el1) {
        for (term::Term t2 : el2) {
            result += t1 * t2;
        }
    }

    return result;
}

void Polynomial::operator+=(Polynomial& other) {
    *this = *this + other;
}

void Polynomial::operator*=(Polynomial& other) {
    *this = *this * other;
}

Polynomial& Polynomial::operator+(const term::Term& other) {
    for (term::Term& t : *this) {
        if (t.getN() == other.getN()) {
            t += other;
            return *this;
        }
    }

    this->terms->push(other);
    this->terms->sort();
    this->degree = std::max(this->degree, other.getN());
    return *this;
}

Polynomial& Polynomial::operator*(const term::Term& other) {
    for (term::Term& t : *this) {
        t *= other;
    }

    return *this;
}

void Polynomial::operator+=(const term::Term& other) {
    *this = *this + other;
}

void Polynomial::operator*=(const term::Term& other) {
    *this = *this * other;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& poly) {
    if (poly.terms->getSize() == 0) {
        return os << 0;
    }

    for (int i = 0; i < poly.terms->getSize(); i++) {
        if (poly.terms->get(i).getK() > 0 && i != 0) {
            os << "+ ";
        }
        os << poly.terms->get(i);
        if (i != poly.terms->getSize() - 1) {
            os << ' ';
        }
    }

    return os;
}

}  // namespace polynomial
