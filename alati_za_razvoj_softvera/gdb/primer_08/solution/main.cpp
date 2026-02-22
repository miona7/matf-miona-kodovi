#include "Point.hpp"
#include "Points.hpp"
#include "k_means.hpp"

#include <iostream>
#include <algorithm>

void test(std::string programPath);

void help(){
    std::cout << "Program se poziva na 2 nacina:" << std::endl;
    std::cout << "\tBez argumenata, i onda se pokrecu testovi" << std::endl;
    std::cout << "\tSa 2 argumenta: putanja do fajla i broj klastera" << std::endl;
    std::exit(EXIT_SUCCESS);
}

int main(const int argc, const char** argv){
    if (argc == 1){
        test(argv[0]);
    }

    if (argc != 3){
        help();
    }

    auto points = Point::readPoints(argv[1]);
    auto k = std::stoul(argv[2]);

    auto result = k_means(points, k);
    Points* largest = nullptr;
    size_t max_size = 0;
    for(auto p : result){
        auto curr_size = p->size();
        if(!largest || curr_size > max_size){
            largest = p;
            max_size = curr_size;
        }
    }

    auto names = largest->getNames();
    //std::sort(names.begin(), names.end());
    for(auto& name : names){
        std::cout << name << std::endl;
    }

    for(auto p : result){
        delete p;
    }
}