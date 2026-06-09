// Zadatak: Izbaciti elemente ciji je indeks deljiv sa 3,

#include <iostream>
#include <vector>
#include <range/v3/view.hpp>

using namespace ranges::v3;

bool filterByIndex(int index) {
    return index % 3 != 0;
}

int main() {
    std::vector<int> xs{ -1, -3, -5, 1, 3, 5 };

    auto result = view::zip(xs, view::ints(1, unreachable))
                | view::filter([](const auto& value) { return filterByIndex(value.second); })
                | view::transform([](const auto& value) { return value.first; });
    
    for(const auto& v : result) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
}