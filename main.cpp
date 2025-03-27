#include "stack/stack.h"
#include <iostream>

namespace {

void factorizeNumber(int number, stack::Stack<int>*& stack) {
    for (int i = 2; i <= number; i++) {
        while (number % i == 0) {
            stack->push(i);
            number /= i;
        }
    }
}

void printStack(stack::Stack<int>*& stack) {
    while (!stack->empty()) {
        std::cout << stack->peek();
        stack->pop();
        if (!stack->empty()) {
            std::cout << " * ";
        }
    }
}

}  // namespace

int main() {
    stack::Stack<int>* st = new stack::Stack<int>();
    int number = 3960;
    factorizeNumber(number, st);

    std::cout << number << '=';
    printStack(st);
    std::cout << std::endl;

    factorizeNumber(number, st);

    std::cout << number << '=';
    stack::Stack<int>* st2 = new stack::Stack<int>();
    while (!st->empty()) {
        st2->push(st->peek());
        st->pop();
    }
    printStack(st2);
    std::cout << std::endl;

    delete st;
    delete st2;

    return 0;
}
