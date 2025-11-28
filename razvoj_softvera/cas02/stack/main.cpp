#include <iostream>
#include "stack.hpp"

using namespace matf;

int main() {
    Stack s1;
    s1.Push(1);
    s1.Push(2);
    s1.Push(3);

    std::cout << s1 << std::endl;

    Stack s2(s1);
    std::cout << s2 << std::endl;

    // ovde se poziva konstruktor kopije, a ne operator dodele
    Stack s3 = s2;
    std::cout << s3 << std::endl;

    Stack s4;
    s4 = s3;   // ovde se poziva operator dodele 
    std::cout << s4 << std::endl;

    Stack s5;
    s5 << 43 << 44 << 45;
    std::cout << s5 << std::endl;

    element e;
    s5 >> e;
    std::cout << e << " " << s5 << std::endl;
}