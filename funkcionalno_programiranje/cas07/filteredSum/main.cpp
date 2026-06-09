// Zadatak: Napisati generičku funkciju filtered_sum koja prima predikat, 
// početnu vrednost i kolekciju, a zatim pomoću ranges biblioteke 
// filtrira elemente i sabira samo one koji ispunjavaju uslov (u ovom slučaju veće od 0).

#include <iostream>
#include <vector>
#include <functional>
#include <range/v3/view.hpp>
#include <range/v3/numeric/accumulate.hpp>

using namespace ranges::v3;

template<typename Predicate, typename Accumulator, typename Collection>
Accumulator filtered_sum(const Predicate& predicate, Accumulator init, const Collection& collection) {
    return accumulate(collection | view::filter(predicate), init);
}

int main() {
    std::vector<int> xs{ -1, -3, -5, 1, 3, 5 };

    std::cout << filtered_sum([](const auto& x) { return x > 0; }, 0, xs) << std::endl;
}