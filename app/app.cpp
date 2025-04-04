#include "app.h"
#include "../src/polynomial.h"

#include <cstring>
#include <iostream>

namespace {

const char* INTERACTIVE_CMD_ARG = "-it";

void show(polynomial::Polynomial& p1, polynomial::Polynomial& p2, term::Term& x1, term::Term& x2) {
    std::cout << "x1 * x2 = " << x1 * x2 << std::endl;
    std::cout << "p1 + p2 = " << p1 + p2 << std::endl;
    std::cout << "p1 * p2 = " << p1 * p2 << std::endl;
    std::cout << "p1 * x1 = " << p1 * x1 << std::endl;
    std::cout << "p1 + x2 = " << p1 + x2 << std::endl;
}

}  // namespace

namespace app {

ProgramMode getProgramMode(int argc, char** argv) {
    if (argc == 2 && std::strcmp(argv[1], INTERACTIVE_CMD_ARG) == 0) {
        return ProgramMode::interactive;
    }

    return ProgramMode::demonstrative;
}

void runDemonstrativeMode() {
    term::Term x1(3, 2);
    term::Term x2(2, 1);

    polynomial::Polynomial p1(x1);
    p1 += x2;
    polynomial::Polynomial p2(3);
    p2 += p1;

    std::cout << "p1 = " << p1 << std::endl;
    std::cout << "p2 = " << p2 << std::endl;
    std::cout << "x1 = " << x1 << "; x2 = " << x2 << std::endl;

    show(p1, p2, x1, x2);

    polynomial::Polynomial p3(p1);
    std::cout << "p3 = " << p3 << std::endl;
    polynomial::Polynomial p4;
    p4 = p3;
    p4.setOrder(polynomial::PolynomialOrder::ascending);;
    std::cout << "p4 = " << p4 << std::endl;
}

void runInteractiveMode() {
    polynomial::Polynomial p1, p2;
    std::cout << "p1= ";
    std::cin >> p1;
    std::cout << "p2= ";
    std::cin >> p2;

    term::Term x1, x2;
    std::cout << "x1= ";
    std::cin >> x1;
    std::cout << "x2= ";
    std::cin >> x2;

    show(p1, p2, x1, x2);
}

void run(int argc, char** argv) {
    switch (getProgramMode(argc, argv)) {
        case ProgramMode::interactive: {
            std::cout << "Welcome!" << std::endl;
            runInteractiveMode();
            break;
        }
        case ProgramMode::demonstrative:
            runDemonstrativeMode();
            break;
    }
}

}  // namespace app
