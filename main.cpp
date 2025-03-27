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

int main() {
    stack::Stack<int>* st = new stack::Stack<int>();

    std::cout << "Enter number (>1): ";
    int number;
    std::cin >> number;
    if (number <= 1) {
        std::cout << "Number must be > 1" << std::endl;
        return 1;
    }

    factorizeNumber(number, st);

    std::cout << number << '=';
    st->print();
    std::cout << std::endl;

    factorizeNumber(number, st);

    stack::Stack<int>* st2 = new stack::Stack<int>();
    while (!st->empty()) {
        st2->push(st->peek());
        st->pop();
    }
    
    std::cout << number << '=';
    st2->print();
    std::cout << std::endl;

    delete st;
    delete st2;

    return 0;
}
