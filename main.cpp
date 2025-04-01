#include <iostream>

#include "set/set.hpp"

int main() {
    set::Set<int> s1;
    s1.push(1);
    s1.push(4);
    s1.push(5);
    s1.push(6);

    set::Set<int> s2;
    s2.push(1);
    s2.push(2);
    s2.push(3);
    s2.push(4);

    std::cout << s1 << " + " << s2 << " => " << s1 + s2 << std::endl;
    std::cout << s1 << " * " << s2 << " => " << s1 * s2 << std::endl;
    std::cout << s1 << " - " << s2 << " => " << s1 - s2 << std::endl;
    std::cout << s1 << " == " << s2 << " => " << (s1 == s2) << std::endl;
    set::Set<int> s3(s1);
    std::cout << s1 << " == " << s3 << " => " << (s1 == s3) << std::endl;
    s2 = s3;
    std::cout << s1 << " == " << s2 << " => " << (s1 == s2) << std::endl;

    return 0;
}
