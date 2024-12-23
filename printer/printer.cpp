#include "printer.h"

#include <iostream>

namespace printer {

void printArr(int* arr, size_t size) {
    std::cout << '[';

    for (size_t i = 0; i < size; i++) {
        std::cout << arr[i];
        if (i != size - 1) {
            std::cout << ", ";
        }
    }

    std::cout << ']';
}

void printlnArr(int* arr, size_t size) {
    printArr(arr, size);
    std::cout << std::endl;
}

}  // namespace printer
