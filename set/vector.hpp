#pragma once

#include <cstddef>
#include <cstring>
#include <iostream>
#include <stdexcept>

namespace vector {

const size_t DEFAULT_CAPACITY = 8;
const size_t GROWTH_FACTOR = 2;
const size_t SHRINK_FACTOR = 4;

template<typename T>
class Vector {
 private:
    T* data;
    size_t size;
    size_t capacity;

    void resize();
    size_t getNewCapacity();

 public:
    Vector(T value);
    Vector();
    Vector(const Vector& other);
    ~Vector();

    [[nodiscard]] size_t getSize();
    void push(T value);
    T remove(size_t index);
    bool delete_element(T el);
    [[nodiscard]] T& get(size_t index);
    [[nodiscard]] int find(T value);
    void clean();

    Vector& operator=(const Vector& other);
    T& operator[](size_t index);

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Vector<U>& vector);
    template<typename U>
    friend std::istream& operator>>(std::istream& is, const Vector<U>& vector);
};

template<typename T>
Vector<T>::Vector(T value) : Vector() {
    push(value);
}

template<typename T>
size_t Vector<T>::getNewCapacity() {
    if (size < capacity / SHRINK_FACTOR) {
        return capacity / SHRINK_FACTOR;
    } else {
        return capacity * GROWTH_FACTOR;
    }
}

template<typename T>
void Vector<T>::resize() {
    capacity = getNewCapacity();
    T* newData = new T[capacity];

    for (size_t i = 0; i < size; i++) {
        newData[i] = data[i];
    }

    delete[] data;
    data = newData;
}

template<>
void Vector<char*>::resize() {
    capacity = getNewCapacity();
    char** newData = new char*[capacity];

    for (size_t i = 0; i < size; i++) {
        newData[i] = new char[strlen(data[i]) + 1];
        std::strcpy(newData[i], data[i]);
    }

    delete[] data;
    data = newData;
}

template<typename T>
Vector<T>::Vector() : size(0), capacity(DEFAULT_CAPACITY), data(new T[DEFAULT_CAPACITY]) {
}

template<typename T>
Vector<T>::Vector(const Vector& other) : size(0), capacity(other.capacity), data(new T[other.capacity]) {
    for (size_t i = 0; i < size; i++) {
        push(other.data[i]);
    }
}

template<typename T>
Vector<T>::~Vector() {
    clean();
}

template<typename T>
size_t Vector<T>::getSize() {
    return size;
}

template<typename T>
T& Vector<T>::get(size_t index) {
    if (index < 0 || index >= size) {
        throw std::runtime_error("Index out of range!");
    }

    if (data == nullptr) {
        throw std::runtime_error("Vector is empty!");
    }

    T& value = data[index];
    return value;
}

template<typename T>
void Vector<T>::push(T value) {
    if (data == nullptr) {
        data = new T[DEFAULT_CAPACITY];
        capacity = DEFAULT_CAPACITY;
        size = 0;
    }

    if (size == capacity) {
        resize();
    }

    data[size++] = value;
}

template<>
void Vector<char*>::push(char* value) {
    if (data == nullptr) {
        data = new char*[DEFAULT_CAPACITY];
        capacity = DEFAULT_CAPACITY;
        size = 0;
    }

    if (size == capacity) {
        resize();
    }

    data[size] = new char[strlen(value) + 1];
    std::strcpy(data[size++], value);
}

template<typename T>
T Vector<T>::remove(size_t index) {
    if (index < 0 || index >= size) {
        throw std::runtime_error("Index out of range!");
    }

    T removed = data[index];

    for (size_t i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }

    size--;
    if (size < capacity / SHRINK_FACTOR) {
        resize();
    }

    return removed;
}

template<>
char* Vector<char*>::remove(size_t index) {
    if (index < 0 || index >= size) {
        throw std::runtime_error("Index out of range!");
    }

    char* removed = new char[strlen(data[index]) + 1];
    std::strcpy(removed, data[index]);
    delete[] data[index];

    for (size_t i = index; i < size - 1; i++) {
        std::strcpy(data[i], data[i + 1]);
    }

    size--;
    if (size < capacity / SHRINK_FACTOR) {
        resize();
    }

    return removed;
}

template<typename T>
bool Vector<T>::delete_element(T el) {
    int index = find(el);

    if (index == -1) {
        return false;
    }
    remove(index);

    return true;
}

template<typename T>
int Vector<T>::find(T value) {
    for (size_t i = 0; i < size; i++) {
        if (data[i] == value) {
            return i;
        }
    }

    return -1;
}

template<typename T>
void Vector<T>::clean() {
    if (data != nullptr) {
        delete[] data;
    }

    size = 0;
    capacity = 0;
    data = nullptr;
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
    if (this != &other) {
        clean();
        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];

        for (size_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    return *this;
}

template<typename T>
T& Vector<T>::operator[](size_t index) {
    return get(index);
}

template<typename U>
std::ostream& operator<<(std::ostream& os, const Vector<U>& vector) {
    os << '[';

    for (size_t i = 0; i < vector.size; i++) {
        os << vector.data[i];
        if (i != vector.size - 1) {
            os << ", ";
        }
    }

    os << ']';
    return os;
}

}  // namespace vector
