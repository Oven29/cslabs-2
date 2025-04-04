#pragma once

#include <cstddef>
#include <cstring>
#include <iostream>
#include <stdexcept>

namespace string {

const int BUFSIZE = 1024;

class String {
 private:
    char* str;
    size_t size;

 public:
    String() : str(nullptr), size(0) {}
    String(char* str) : str(new char[std::strlen(str) + 1]), size(std::strlen(str)) { std::strcpy(this->str, str); }
    String(const char* str) : String((char*)str) {}
    ~String() { delete[] str; }

    size_t getLength() { return size; }

    friend std::ostream& operator<<(std::ostream& os, const String& string) {
        os << string.str;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, String& string) {
        char buffer[BUFSIZE] = {};
        is >> std::setw(BUFSIZE) >> buffer;
        string = String(buffer);
        return is;
    }

    String& operator=(const String& other) {
        if (this != &other) {
            if (this->str != nullptr) {
                delete[] str;
            }
            this->size = other.size;
            this->str = new char[size + 1];
            std::strcpy(this->str, other.str);
        }
        return *this;
    }

    friend String operator+(const String& lhs, const String& rhs) {
        String result;
        result.str = new char[lhs.size + rhs.size + 1];
        std::strcpy(result.str, lhs.str);
        std::strcat(result.str, rhs.str);
        result.size = lhs.size + rhs.size;
        return result;
    }

    friend String operator+(const String& lhs, char* rhs) { return lhs + String(rhs); }

    friend String operator+(const String& lhs, const char* rhs) { return lhs + String(rhs); }

    friend void operator+=(String& lhs, const String& rhs) { lhs = lhs + rhs; }

    friend void operator+=(String& lhs, char* rhs) { lhs = lhs + rhs; }

    friend void operator+=(String& lhs, const char* rhs) { lhs = lhs + rhs; }

    friend String operator*(const String& string, const int& multiplier) {
        String result;
        result.str = new char[string.size * multiplier + 1];

        for (int i = 0; i < multiplier; i++) {
            std::strcat(result.str, string.str);
        }

        result.size = string.size * multiplier;
        return result;
    }

    friend void operator*=(String& lhs, const int& rhs) { lhs = lhs * rhs; }
};

}  // namespace string
