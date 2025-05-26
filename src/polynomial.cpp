#include "polynomial.h"

#include <cstring>

namespace {

const int BUF_SIZE = 1024;

}

namespace polynomial {

Polynomial::Polynomial() : terms(new vector::Vector<term::Term>()), degree(0), order(PolynomialOrder::decreasing) {
}

Polynomial::Polynomial(int t) : Polynomial(term::Term(t)) {
}

Polynomial::Polynomial(term::Term t) : Polynomial() {
    this->terms->push(t);
    this->degree = t.getN();
}

Polynomial::Polynomial(const Polynomial& other) : degree(other.degree), order(other.order) {
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

void Polynomial::setOrder(PolynomialOrder order) {
    this->order = order;
}

Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        delete this->terms;
        this->terms = new vector::Vector<term::Term>(*other.terms);
        this->degree = other.degree;
        this->order = other.order;
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

Polynomial Polynomial::operator+(const term::Term& other) {
    Polynomial result(*this);

    if (other == term::Term()) {
        return result;
    }

    for (term::Term& t : result) {
        if (t.getN() == other.getN()) {
            t += other;
            return result;
        }
    }

    result.terms->push(other);
    result.degree = std::max(result.degree, other.getN());
    return result;
}

Polynomial Polynomial::operator*(const term::Term& other) {
    Polynomial result(*this);

    for (term::Term& t : result) {
        t *= other;
    }

    return result;
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

    poly.terms->sort();
    if (poly.order == PolynomialOrder::decreasing) {
        poly.terms->reverse();
    }

    bool isFirst = true;

    for (int i = 0; i < poly.terms->getSize(); i++) {
        int k = poly.terms->get(i).getK();
        if (k != 0) {
            if (!isFirst) {
                os << (k > 0 ? '+' : '-') << ' ';
            }
            os << poly.terms->get(i) * term::Term(k < 0 && !isFirst ? -1 : 1);
            if (i != poly.terms->getSize() - 1) {
                os << ' ';
            }
            isFirst = false;
        }
    }

    if (isFirst) {
        os << '0';
    }

    return os;
}

std::istream& operator>>(std::istream& is, Polynomial& poly) {
    char* buffer = new char[BUF_SIZE];
    is.getline(buffer, BUF_SIZE);

    while (std::strlen(buffer) && term::isTermSymbol(*buffer)) {
        poly += term::Term::parseTerm(buffer);
        while (*buffer == ' ')
            ++buffer;
        if (*buffer == '+')
            ++buffer;
    }

    if (std::strlen(buffer) && !term::isTermSymbol(*buffer)) {
        throw std::runtime_error("Invalid polynomial input!");
    }

    return is;
}

}  // namespace polynomial
