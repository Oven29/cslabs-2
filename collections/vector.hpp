#pragma once

#include <cstddef>
#include <cstring>
#include <iostream>
#include <stdexcept>

namespace {

template<typename T>
int compare(T& el1, T& el2) {
    return el1 - el2;
}

template<>
int compare(char*& el1, char*& el2) {
    return std::strcmp(el1, el2);
}

template<>
int compare(const char*& el1, const char*& el2) {
    return std::strcmp(el1, el2);
}

}  // namespace

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

    size_t getNewCapacity();
    void resize();
    void quickSort(int left, int right);

 public:
    Vector();
    Vector(const Vector& other);
    ~Vector();

    [[nodiscard]] size_t getSize();
    void push(T value);
    void remove(size_t index);
    bool deleteElement(T el);
    [[nodiscard]] T& get(size_t index);
    [[nodiscard]] int find(T value);
    void sort();
    void reverse();
    void clear();

    T* begin();
    T* end();

    Vector& operator=(Vector& other);
    T& operator[](size_t index);

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Vector<U>& vector);
    template<typename U>
    friend std::istream& operator>>(std::istream& is, const Vector<U>& vector);
};

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

template<typename T>
void Vector<T>::quickSort(int left, int right) {
    if (left >= right)
        return;

    T pivot = this->get(left + (right - left) / 2);
    int i = left, j = right;

    while (i <= j) {
        while (compare(this->get(i), pivot) < 0)
            i++;
        while (compare(this->get(j), pivot) > 0)
            j--;

        if (i <= j) {
            std::swap((*this)[i], (*this)[j]);
            i++;
            j--;
        }
    }

    if (left < j)
        quickSort(left, j);
    if (i < right)
        quickSort(i, right);
}

template<typename T>
Vector<T>::Vector() : size(0), capacity(DEFAULT_CAPACITY), data(new T[DEFAULT_CAPACITY]) {
}

template<typename T>
Vector<T>::Vector(const Vector& other) {
    size = other.size;
    capacity = other.capacity;
    data = new T[capacity];

    for (size_t i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
}

template<typename T>
Vector<T>::~Vector() {
    clear();
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

template<typename T>
void Vector<T>::remove(size_t index) {
    if (index < 0 || index >= size) {
        throw std::runtime_error("Index out of range!");
    }

    delete data[index];

    for (size_t i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }

    size--;
}

template<typename T>
bool Vector<T>::deleteElement(T el) {
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
void Vector<T>::sort() {
    this->quickSort(0, this->size - 1);
}

template<typename T>
void Vector<T>::reverse() {
    for (size_t i = 0; i < size / 2; i++) {
        std::swap(data[i], data[size - i - 1]);
    }
}

template<typename T>
void Vector<T>::clear() {
    if (data != nullptr) {
        for (size_t i = 0; i < size; i++) {
            delete data[i];
        }
        delete[] data;
    }

    size = 0;
    capacity = 0;
    data = nullptr;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T>& other) {
    if (this != &other) {
        clear();
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
T* Vector<T>::begin() {
    return data;
}

template<typename T>
T* Vector<T>::end() {
    return data + size;
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
