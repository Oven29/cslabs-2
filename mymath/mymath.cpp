#include "mymath.h"

namespace mymath {

int sum(int* arr, size_t size) {
    int res = 0;

    for (size_t i = 0; i < size; i++) {
        res += arr[i];
    }

    return res;
}

int min(int* arr, size_t size) {
    int res = arr[0];

    for (size_t i = 1; i < size; i++) {
        if (arr[i] < res) {
            res = arr[i];
        }
    }

    return res;
}

int max(int* arr, size_t size) {
    int res = arr[0];

    for (size_t i = 1; i < size; i++) {
        if (arr[i] > res) {
            res = arr[i];
        }
    }

    return res;
}

}
