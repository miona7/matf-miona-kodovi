#include <iostream>

int main(int argc, char** argv) {
    if(argc < 2) {
        std::cerr << "Wrong number of arguments!" << std::endl;
        return -1;
    }

    int n = atoi(argv[1]);
    for(int i = 0; i < n; ++i) {
        std::cout << "Hello, Docker!" << std::endl;
    }

    return 0;
}