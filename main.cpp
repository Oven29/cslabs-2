#include <iostream>
#include "set/set.hpp"
#include "set/vector.hpp"

int main() {
    const char* source = "HelloHello";
    char* myS = new char[strlen(source) + 1];
    strcpy(myS, source);

    vector::Vector<char*> v((char*)"Hello!");
    v.push((char*)"Привет!");
    v.push((char*)"Привет!");
    v.push((char*)"Привет!");
    v.push((char*)"Привет!");
    v.push((char*)"Привет!");
    std::cout << "Вектор v: " << v << std::endl;
    v.push((char*)"Привет!");
    v.push((char*)"Привет!");
    v.push((char*)"Привет!");
    std::cout << "Вектор v: " << v << std::endl;
    vector::Vector<char*> v1 = v;
    std::cout << "Вектор v1: " << v1 << std::endl;
    for (int i = 0; i < v1.getSize(); i++) {
        v1.delete_element(0);
    }
    std::cout << "Вектор v1: " << v1 << std::endl;
    set::Set<char*> s, s1, s2;
    s.push(myS);
    delete[] myS;
    s.push((char*)"Привет!");
    s.push((char*)"Привет!");
    s.push((char*)"No");
    const char* str = "Hello!";
    s.push((char*)str);
    std::cout << "Множество s: " << s << std::endl;
    s1.push((char*)"Cat");
    s1.push((char*)"No");
    s1.push((char*)"Привет!");
    std::cout << "Множество s1: " << s1 << std::endl;
    s2 = s1 - s;
    std::cout << "Множество s2=s1-s: " << s2 << std::endl;
    std::cout << "Множество s1: " << s1 << std::endl;
    std::cout << "Множество s: " << s << std::endl;
    s2 = s - s1;
    std::cout << "Множество s2=s-s1: " << s2 << std::endl;
    std::cout << "Множество s1: " << s1 << std::endl;
    std::cout << "Множество s: " << s << std::endl;
    s2 = s1 + s;
    std::cout << "Множество s2=s1+s: " << s2 << std::endl;
    std::cout << "Множество s1: " << s1 << std::endl;
    std::cout << "Множество s: " << s << std::endl;
    s2 = s1 * s;
    std::cout << "Множество s2=s1*s: " << s2 << std::endl;
    std::cout << "Множество s1: " << s1 << std::endl;
    std::cout << "Множество s: " << s << std::endl;
    set::Set<char*> s3 = s2;
    std::cout << "Множество s3=s2: " << s3 << std::endl;
    if (s3 == s2) {
        std::cout << "Множество s3=s2\n";
    } else {
        std::cout << "Множество s3!=s2\n";
    }
    if (s3 == s1) {
        std::cout << "Множество s3=s1\n";
    } else {
        std::cout << "Множество s3!=s1\n";
    }
    if (s1 == s3) {
        std::cout << "Множество s1=s3\n";
    } else {
        std::cout << "Множество s1!=s3\n";
    }
    return 0;
}
