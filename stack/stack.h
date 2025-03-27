#pragma once

#include <iostream>

namespace stack {

template<class T, class FRIEND>
class ListNode {
 private:
    T value;
    ListNode* next;
    ListNode(void) { next = nullptr; }
    friend FRIEND;
};

template<class T>
class Stack {
    typedef class ListNode<T, Stack<T>> Node;
    Node* top;

 public:
    Stack();  // конструктор
    Stack(const Stack<T>& stack);
    ~Stack();  // освободить динамическую память
    Stack<T>& operator=(const Stack<T>& stack);

    bool empty();     // стек пустой?
    void push(T el);  // добавить узел в вершину стека
    T pop();          // удалить узел из вершины стека
    T peek();         // считать информацию из вершины стека
    void print();
};

template<class T>
Stack<T>::Stack() : top(nullptr) {
}

template<class T>
Stack<T>::Stack(const Stack<T>& stack) {
    top = nullptr;
    Node* node = stack.top;
    while (node != nullptr) {
        push(node->value);
        node = node->next;
    }
}

template<class T>
Stack<T>::~Stack() {
    while (!empty()) {
        pop();
    }
}

template<class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& stack) {
    if (this == &stack) {
        return *this;  // Защита от самоприсваивания
    }

    // Удаляем старые элементы
    while (!empty()) {
        pop();
    }

    // Копируем элементы из другого стека
    if (stack.top) {
        Node* current = stack.top;
        Node* newTop = new Node();
        newTop->value = current->value;
        this->top = newTop;

        Node* newCurrent = newTop;
        current = current->next;

        while (current) {
            Node* newNode = new Node();
            newNode->value = current->value;
            newCurrent->next = newNode;
            newCurrent = newNode;
            current = current->next;
        }
    }
    return *this;
}

template<class T>
bool Stack<T>::empty() {
    return top == nullptr;
}

template<class T>
void Stack<T>::push(T value) {
    Node* node = new Node;
    node->value = value;
    node->next = top;
    top = node;
}

template<class T>
T Stack<T>::pop() {
    T res = top->value;
    Node* node = top;
    top = top->next;
    delete node;
    return res;
}

template<class T>
T Stack<T>::peek() {
    return top->value;
}

template<class T>
void Stack<T>::print() {
    while (!empty()) {
        std::cout << pop();
        if (!empty()) {
            std::cout << " * ";
        }
    }
    std::cout << std::endl;
}

}  // namespace stack
