#include "text.hpp"

namespace {
    std::string append_path(const std::string& root, const std::string& sub){
        if(root[root.size()-1] != '/'){
            return root + '/' + sub;
        }
        return root + sub;
    }

    void test_case(const std::string& path_to_test_folder, unsigned i, const std::string& expected){
        //ARRANGE
        const auto text_file = append_path(path_to_test_folder, "test" + std::to_string(i) + ".txt");
        const auto replacements_file = append_path(path_to_test_folder, "test" + std::to_string(i));

        //ACT
        Text text = Text::fromFile(text_file);
        text.find_and_replace(replacements_file);
        const std::string result = text.text();

        //ASSERT
        if (result != expected){
            std::cerr << "Test " << i << " FAILED" << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
}

void test(const std::string& path_to_test_folder){
    test_case(path_to_test_folder, 1u, "Jesen u mom sokaku");
    test_case(path_to_test_folder, 2u, "");
    test_case(path_to_test_folder, 3u, "Da nisam napravio slovo j, ti bi se zvao ovan");
    std::cout << "Svi testovi uspesno prosli, cestitam :)" << std::endl;
}