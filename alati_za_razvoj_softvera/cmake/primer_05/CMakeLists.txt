cmake_minimum_required(VERSION 3.16)
project(MyProject VERSION 1.0.0)

# omogucava testiranje -> pokrece se sa ctest u buildu
enable_testing()

add_subdirectory(stringLib)

add_executable(program
    src/main.cpp
)

target_link_libraries(program PRIVATE stringLib)
