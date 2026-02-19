#include <iostream>
#include <vector>
#include <cassert>

#include "stringLib.hpp"

int main() {

    // arrange
    const std::string data     = "hello darkness, my old friend!";
    const std::string empty    = "";
    const std::string allDels = "#########";
    const std::string mltDels = "hello darkness,,, my old friend!";
    const char del1 = ' ';
    const char del2 = ',';
    const char del3 = '#';

    const std::vector<std::string> result1 = split(data, del1);
    const std::vector<std::string> result2 = split(data, del2);
    const std::vector<std::string> result3 = split(data, del3);
    const std::vector<std::string> result4 = split(empty, del2);
    const std::vector<std::string> result5 = split(allDels, del3);
    const std::vector<std::string> result6 = split(mltDels, del2);

    const std::vector<std::string> expected_result1{"hello", "darkness,", "my", "old", "friend!"};
    const std::vector<std::string> expected_result2{"hello darkness", " my old friend!"};
    const std::vector<std::string> expected_result3{"hello darkness, my old friend!"};
    const std::vector<std::string> expected_result4{};
    const std::vector<std::string> expected_result5{};
    const std::vector<std::string> expected_result6{"hello darkness", " my old friend!"};

    // assert
    assert(result1 == expected_result1);
    assert(result2 == expected_result2);
    assert(result3 == expected_result3);
    assert(result4 == expected_result4);
    assert(result5 == expected_result5);
    assert(result6 == expected_result6);

    std::cout << "Tests passed!" << std::endl;

    return 0;
}