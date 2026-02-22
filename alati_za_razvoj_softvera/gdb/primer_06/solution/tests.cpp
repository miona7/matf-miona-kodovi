#include <iostream>
#include <sstream>

#include "grid.hpp"

namespace
{
    void assert(bool cond, const std::string& message)
    {
        if(!cond){
            std::cout << "TEST FAILED: " << message << '!' << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

    void test1()
    {
        const std::string expected_result("0 3 0 0 4 0 \n1 0 3 4 0 2 \n0 1 4 3 2 0 \n0 4 1 2 3 0 \n4 0 2 1 0 3 \n0 2 0 0 1 0 \n");
        const size_t expected_size = 4u; 
        const std::string test_file = "test1.lines";

        const auto lines = Line::readLines(test_file);
        assert(lines.size() == expected_size, "Lines not correct");
        
        Grid* grid = Grid::makeGrid(lines, false);
        grid->draw_line(lines);
        std::ostringstream result_out;
        result_out << *grid;
        std::string result = result_out.str();

        assert(result == expected_result, "Grid not correct");
        delete grid;
    }

    void test2()
    {
        const std::string expected("0 4 0 2 0 \n3 4 3 3 3 \n0 4 0 2 0 \n1 4 1 2 1 \n0 4 0 2 0 \n");
        const std::string test_file = "test2";

        const auto lines = Line::readLines(test_file);
        
        Grid* grid = Grid::makeGrid(lines);
        std::ostringstream result_out;
        result_out << *grid;
        std::string result = result_out.str();

        assert(result == expected, "Grid not correct");
        delete grid;
    }
}


void tests()
{
    test1();
    test2();
    std::cout << "Svi testovi su prosli, cestitam! :)" << std::endl;
    std::exit(EXIT_SUCCESS);
}