// Zadatak: Napisati sablonsku funkciju is_sorted koja proverava da li je data kolekcija sortirana.

#include <iostream>
#include <string>
#include <vector>
#include <numeric>

#include <range/v3/view.hpp>

template<typename T>
bool is_sorted(const T& collection) {
    return std::inner_product(
        collection.cbegin(), collection.cend() - 1,
        collection.cbegin() + 1,
        true,
        std::logical_and<bool>(),
        [](const auto& x, const auto& y) { return x <= y; }
    );
}

int main() {
    const std::string text = "Hooloovoo";
    std::cout << text << ": " << is_sorted(text) << std::endl;

    const std::string word = "Almost";
    std::cout << word << ": " << is_sorted(word) << std::endl;

    const std::vector<int> numbers{ 1, 2, 3, 3, 4, 5, 6, 6, 7 };
    std::cout << "numbers: " << is_sorted(word) << std::endl;
}