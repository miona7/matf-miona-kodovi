#include "grid.hpp"

void tests();

void help()
{
    std::cout << "Ako se program pokrene bez argumenata pokrecu se testovi" << std::endl;
    std::cout << "Ako je argument putanja do fajla, iscrtava se rezultujuca slika" << std::endl;
    std::exit(EXIT_SUCCESS);
}

int main(int argc, char** argv)
{
    if(argc > 2)
    {
        help();
    }

    if(argc == 1)
    {
        tests();
    }


    auto lines = Line::readLines(argv[1]);
    Grid* grid = Grid::makeGrid(lines);
    
    grid->draw_line(lines);

    std::cout << *grid;

    delete grid;
    return 0;
}
