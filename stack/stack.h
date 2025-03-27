#pragma once

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
    Stack();          // конструктор
    ~Stack();         // освободить динамическую память
    bool empty();     // стек пустой?
    void push(T el);  // добавить узел в вершину стека
    T pop();          // удалить узел из вершины стека
    T peek();         // считать информацию из вершины стека
};

template<class T>
Stack<T>::Stack() : top(nullptr) {
}

template<class T>
Stack<T>::~Stack() {
    while (!empty()) {
        pop();
    }
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

}  // namespace stack
