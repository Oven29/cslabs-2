#include "mymath/mymath.h"
#include "printer/printer.h"

#include <iostream>

int main() {
    const int size = 5;
    int arr[size] = {1, 2, 3, 4, 5};

    printer::printlnArr(arr, size);
    std::cout << "Sum: " << mymath::sum(arr, size) << std::endl;
    std::cout << "Min: " << mymath::min(arr, size) << std::endl;
    std::cout << "Max: " << mymath::max(arr, size) << std::endl;

    return 0;
}
