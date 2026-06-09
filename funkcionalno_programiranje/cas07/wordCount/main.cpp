// Zadatak: Iz kolekcije reci izdvojiti n najfrekventnijih (n moze biti zadato kao argument komandne linije)

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

#include <range/v3/view.hpp>
#include <range/v3/action.hpp>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/istream.hpp>

using namespace ranges::v3;

std::string stringToLower(const std::string& s) {
    return s | view::transform(tolower) | to<std::string>();
}

std::string stringAlphaNum(const std::string& s) {
    return s | view::filter(isalnum) | to<std::string>();
}

int main(int argc, char** argv) {
    const int n = argc <= 1 ? 10 : atoi(argv[1]); 

    const auto words = istream_range<std::string>(std::cin) // otvorimo stream nad ucitanim tekstom
        | view::transform(stringToLower) // prebacimo sve u mala slova
        | view::transform(stringAlphaNum) // ostavljamo samo karaktere i cifre
        | view::remove_if(&std::string::empty) // uklanjamo beline
        | to_vector // da bismo mogli da sortiramo potrebna nam je random access kolekcija tj kolekcija sa pristupom O(1)
        | action::sort;

    const auto result = words 
        | view::chunk_by(std::equal_to<>()) // grupisemo iste reci -> group_by
        | view::transform([](const auto& wordGroup) {
            const auto begin = wordGroup.begin();
            const auto end = wordGroup.end();
            const auto size = distance(begin, end);
            return std::make_pair(size, *wordGroup.begin());
        })
        | to_vector
        | action::sort;
    
    for(const auto& value : result | view::reverse | view::take(n)) {
        std::cout << value.second << " : " << value.first << std::endl;
    }
}