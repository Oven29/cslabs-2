#include <cstring>
#include <iostream>
#include "stack/stack.h"

namespace {

void factorizeNumber(int number, stack::Stack<int>*& stack) {
    for (int i = 2; i <= number; i++) {
        while (number % i == 0) {
            stack->push(i);
            number /= i;
        }
    }
}

}  // namespace

int main(int argc, char** argv) {
    int number = {};

    if (argc == 2 && std::strcmp(argv[1], "-it") == 0) {
        std::cout << "Enter number (>1): ";
        std::cin >> number;
        if (number <= 1) {
            std::cout << "Number must be > 1" << std::endl;
            return 1;
        }
    } else {
        number = 1360;
    }

    stack::Stack<int>* st = new stack::Stack<int>();
    factorizeNumber(number, st);

    std::cout << number << '=';
    st->print();

    factorizeNumber(number, st);

    stack::Stack<int>* st2 = new stack::Stack<int>(*st);

    std::cout << number << '=';
    st2->print();

    delete st;
    delete st2;

    return 0;
}
