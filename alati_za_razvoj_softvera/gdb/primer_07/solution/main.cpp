#include "text.hpp"

extern void test(const std::string& path_to_test_folder);

int main(int argc, char** argv){
    if (argc == 2){
        test(argv[1]);
        return EXIT_SUCCESS;
    }
    if (argc == 3) {
        auto text = Text::fromFile(argv[1]);
        text.find_and_replace(argv[2]);

        std::cout << text << std::endl;
        return EXIT_SUCCESS;
    }

    std::cout << " - Za pokretanje testova, pokrenuti program sa putanjom ka direktorijumu gde se nalaze testovi:" << std::endl;
    std::cout << "\t./text ./test" << std::endl;
    std::cout << " - Za pokretanje konkretnog primera, argumenti su putanja ka fajlu koji sadrzi tekst i putanja ka fajlu koji sadrzi reci koje se zamenjuju:" << std::endl;
    std::cout << "\t./text ./test/test1.txt ./test/test1" << std::endl;

    return EXIT_SUCCESS;
}