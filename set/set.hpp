#include "vector.hpp"

#include <cstring>

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

template<typename T>
void quickSort(vector::Vector<T>& arr, int left, int right) {
    if (left >= right)
        return;

    T pivot = arr[left + (right - left) / 2];
    int i = left, j = right;

    while (i <= j) {
        while (compare(arr[i], pivot) < 0)
            i++;
        while (compare(arr[j], pivot) > 0)
            j--;

        if (i <= j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    if (left < j)
        quickSort(arr, left, j);
    if (i < right)
        quickSort(arr, i, right);
}

template<typename T>
int binarySearch(vector::Vector<T>& arr, T& target) {
    int left = 0;
    int right = static_cast<int>(arr.getSize()) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (compare(arr[mid], target) == 0) {
            return mid;
        } else if (compare(arr[mid], target) < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

}  // namespace

namespace set {

template<typename T>
class Set : public vector::Vector<T> {
 public:
    Set(T value);
    Set();

    void push(T value);
    void sort();
    [[nodiscard]] int find(T value);
    bool has_element(T el);

    template<typename U>
    friend Set<U> operator+(Set<U>& el1, Set<U>& el2);
    template<typename U>
    friend Set<U> operator-(Set<U>& el1, Set<U>& el2);
    template<typename U>
    friend Set<U> operator*(Set<U>& el1, Set<U>& el2);
    template<typename U>
    friend bool operator==(Set<U>& el1, Set<U>& el2);

    void operator+=(Set<T>& other);
    void operator-=(Set<T>& other);
    void operator*=(Set<T>& other);
};

template<typename T>
Set<T>::Set(T value) : vector::Vector<T>(value) {
}

template<typename T>
Set<T>::Set() : vector::Vector<T>() {
}

template<typename T>
void Set<T>::push(T value) {
    if (!has_element(value)) {
        vector::Vector<T>::push(value);
        sort();
    }
}

template<typename T>
void Set<T>::sort() {
    quickSort(*this, 0, this->getSize() - 1);
};

template<typename T>
int Set<T>::find(T value) {
    return binarySearch(*this, value);
};

template<typename T>
bool Set<T>::has_element(T el) {
    return find(el) != -1;
};

template<typename T>
Set<T> operator+(Set<T>& el1, Set<T>& el2) {
    Set<T> res = Set<T>(el1);

    for (size_t i = 0; i < el2.getSize(); i++) {
        if (!res.has_element(el2[i])) {
            res.push(el2[i]);
        }
    }

    res.sort();
    return res;
}

template<typename T>
Set<T> operator-(Set<T>& el1, Set<T>& el2) {
    Set<T> res;

    for (size_t i = 0; i < el1.getSize(); i++) {
        if (!el2.has_element(el1[i])) {
            res.push(el1[i]);
        }
    }

    res.sort();
    return res;
}

template<typename T>
Set<T> operator*(Set<T>& el1, Set<T>& el2) {
    Set<T> res;

    for (size_t i = 0; i < el1.getSize(); i++) {
        if (el2.has_element(el1[i])) {
            res.push(el1[i]);
        }
    }

    res.sort();
    return res;
}

template<typename T>
bool operator==(Set<T>& el1, Set<T>& el2) {
    if (el1.getSize() != el2.getSize()) {
        return false;
    }

    for (size_t i = 0; i < el1.getSize(); i++) {
        if (!el2.has_element(el1[i])) {
            return false;
        }
    }

    return true;
}

template<typename T>
void Set<T>::operator+=(Set<T>& other) {
    *this = *this + other;
}

template<typename T>
void Set<T>::operator-=(Set<T>& other) {
    *this = *this - other;
}

template<typename T>
void Set<T>::operator*=(Set<T>& other) {
    *this = *this * other;
}

}  // namespace set
