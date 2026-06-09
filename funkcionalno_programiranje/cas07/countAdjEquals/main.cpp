// Zadatak: Napisati sablonsku funkciju count_adj_equals koja vraca broj parova uzastopnih jednakih elemenata kolekcije.

#include <iostream>
#include <string>
#include <vector>
#include <numbers>
#include <functional>

#include <range/v3/view.hpp>

template<typename T>
                    // T je tip kolekcije a ne elemenata u njoj
int count_adj_equals(const T& collection) {
    // koristimo fju iz numeric biblioteke std::inner_product -> u originalu ona racuna skalarni proizvod dva vektora
    // u ovom slucaju mi cemo operacije + i * da zamenimo za + i == -> koristimo preoptereceni oblik ove fje 
    // T std::inner_product(InputIt1 first1, InputIt1 last1, InputIt2 first2, T init, BinaryOp1 op1, BinaryOp2 op2);
                                                                                   // spoljna operacija, unutrasnja operacija 
    return std::inner_product(
        collection.cbegin(), collection.cend() - 1, // cbegin() i cend() -> const iteratori, samo citamo kolekciju ne menjamo je
        collection.cbegin() + 1,
        0,
        // ugradjeni funkcijski objekat
        std::plus<int>(), // isto sto i [](const int& x, const int& y) { return x + y; },
        // ne znamo tip elemenata u kolekciji pa koristimo auto
        [](const auto& x, const auto& y) { return x == y ? 1 : 0; });
}

int main() {   
    const std::string text = "Hoolloovo"; 
    std::cout << count_adj_equals(text) << std::endl;

    const std::vector<double> numbers{ -1.0, 2.36, 65.4, 65.4, 65.4, -1.0, 0.0, 5.4 };
    std::cout << count_adj_equals(numbers) << std::endl;
}