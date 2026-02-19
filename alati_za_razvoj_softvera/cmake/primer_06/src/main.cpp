#include <iostream>
#include <fstream>

#include "stringLib.hpp"

int main(int argc, char** argv) {
    if(argc < 2) {
        std::cerr << "Wrong number of arguments" << std::endl;
        return -1;
    }

    std::ifstream input(argv[1]);
    std::string line;

    unsigned linesCnt = 0;
    unsigned wordsCnt = 0;
    while(getline(input, line)) {
        linesCnt++;
        wordsCnt += split(line, ' ').size();
    }

    std::cout << "Number of lines: " << linesCnt << std::endl;
    std::cout << "Number of words: " << wordsCnt << std::endl;
    
    return 0;
}