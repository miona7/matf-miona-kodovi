cmake_minimum_required(VERSION 3.16)
project(MyProgram VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra")

add_executable(program
    main.cpp
    voronoi.hpp voronoi.cpp
)

