// Zadatak: Iz vektora xs uzeti apsolutne vrednosti svih brojeva, zadržati samo one koji su strogo manji od 6,
// i na kraju ih transformisati u stringove za ispis.

#include <iostream>
#include <vector>
#include <functional>
#include <range/v3/view.hpp>

using namespace ranges::v3;
using namespace std::placeholders;

int main() {
    std::vector<int> xs = { -1, -3, -5, 1, 3, 5};

    // ovo je samo konstrukcija pajplajna i slozenost ovog dela koda je O(1) -> lenja evaluacija
    // operator | - pipe
    auto result = xs 
        | view::transform(abs)
        | view::filter(std::bind(std::less<>(), _1, 6))
        | view::transform([](auto value) { return std::to_string(value); });

    // tek pri ispisu se ovaj pogled pravi i slozenost u ovom trenutku je O(n)
    std::cout << result << std::endl;
}
