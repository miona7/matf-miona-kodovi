cmake_minimum_required(VERSION 3.16)
project(MyProgram VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g -Wall -Wextra")
    # postavlja pocetne opcije za Debug verziju -> -DCMAKE_BUILD_TYPE=Debug
 
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O2")
    # postavlja pocetne opcije za Release verziju -> -DCMAKE_BUILD_TYPE=Release

add_executable(program
    main.cpp
)