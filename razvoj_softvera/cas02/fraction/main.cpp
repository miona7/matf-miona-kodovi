#include <iostream>
#include "fraction.hpp"

using namespace matf;

int main() {

    Fraction f1;
    std::cin >> f1;

    Fraction f2;
    std::cin >> f2;

    std::cout << f1 + f2 << std::endl;
    std::cout << double(f1 + f2) << std::endl;
}
