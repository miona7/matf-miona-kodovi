// Zadatak 4
// Koristeći biblioteku range-v3, a bez upotrebe for, while, do-while petlji,
// komande goto, rekurzije, i algoritma std::for_each implementirati sledeći zadatak:
// Napisati program koji sa standardnog ulaza čita reč po reč i
// briše uzastopna ponavljanja iste reči. Svaku reč ispisuje u novom redu.
//
// Za ulaz:
// thunder thunder
// thunder thunder
// i was caught
// in the middle of a railroad track
// thunder thunder
// thunder thunder
//
// Treba ispisati:
// thunder
// i
// was
// caught
// in
// the
// middle
// of
// a
// railroad
// track
// thunder


#include <iostream>
#include <string>
#include <vector>
#include <iterator>

#include <range/v3/view.hpp>
#include <range/v3/action.hpp>
#include <range/v3/algorithm.hpp>
#include <range/v3/to_container.hpp>

#include <cassert>

using namespace ranges::v3;
namespace views = ranges::v3::view;
namespace actions = ranges::v3::action;
 
int main(int argc, char** argv) {   
    std::vector<std::string> allWords{
        std::istream_iterator<std::string>{std::cin}, // pocetak strima
        std::istream_iterator<std::string>{} // kraj strima
    };

    const auto words = allWords | views::unique; 

    for(auto word : words) {
        std::cout << word << std::endl;
    }
}