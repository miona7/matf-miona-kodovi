#include "Point.hpp"
#include "Points.hpp"
#include "k_means.hpp"
#include "RandomEngine.hpp"

#include <iostream>
#include <iostream>
#include <string>
#include <filesystem>
#include <unistd.h>

namespace {
    void assert(
        bool condition,
        const std::string& test_name = "TEST",
        const std::string& message = "Test failed"
    ){
        if(!condition){
            std::cout << test_name << ": " << message << "!" << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

    std::string get_current_dir_name(std::string programPath){
        return programPath.substr(0, programPath.find_last_of('/'));
    }

    void test1() {
        //arrange
        const std::string input("name");

        //act
        const auto point = Point::fromString(input);

        //assert
        assert(input == point.getName());
    }

    void test2(){
        //arrange
        const unsigned k = 1;
        const std::string file_name = "test.txt";
        const std::vector<std::string> expected = {
            "jedan",
            "dva",
            "tri",
            "cetiri",
            "pet"
        };
        const std::vector<Point> points = {
            Point("jedan"),
            Point("dva"),
            Point("tri"),
            Point("cetiri"),
            Point("pet")
        };

        //act
        const auto alg = k_means(points, k);
        Points* p = alg[0];
        const auto result = p->getNames();

        //assert
        assert(expected.size() == result.size());
        for(size_t i = 0; i < expected.size(); ++i){
            assert(expected[i] == result[i]);
        }
    }


    void test3(std::string dir) {
        //arrange
        const auto testFilePath = dir + "/" + "test.txt";
        const unsigned k = 3;
        const std::vector<std::string> expected = {
            "sest",
            "sedam",
            "osam",
            "devet",
            "deset",
            "jedanaest",
            "osamnaest",
            "devetnaest",
            "dvadeset",
            "Lisabon",
            "Kijev",
            "Moskva",
            "Prag",
            "Bukurest",
            "Beograd"
        };
        Points::s_re.setSeed(0);

        //act
        const auto point_list = Point::readPoints(testFilePath);
        auto names = k_means(point_list, k);
        Points* largest = nullptr;
        size_t max_size = 0;
        for(auto p : names){
            auto curr_size = p->size();
            if(!largest || curr_size > max_size){
                largest = p;
                max_size = curr_size;
            }
        }

        auto result = largest->getNames();

        //assert
        assert(expected.size() == result.size());
        for(size_t i = 0; i < expected.size(); ++i){
            assert(expected[i] == result[i]);
        }
    }
}

void test(std::string programPath) {
    test1();
    test2();
    test3(get_current_dir_name(programPath));
    std::cout << "Testovi prosli, cestitam! :)" << std::endl;
    std::exit(EXIT_SUCCESS);
}