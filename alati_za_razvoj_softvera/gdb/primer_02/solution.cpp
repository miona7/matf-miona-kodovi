#include <iostream>

int factorial(int n) {
    int sol = 1;
    while(n) {
        sol *= n;
        n--;
    }
    return sol;
}

int main() {
    std::cout << "5! = " << factorial(5) << std::endl;  
    return 0;
}