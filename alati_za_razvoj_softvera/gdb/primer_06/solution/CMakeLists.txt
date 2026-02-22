cmake_minimum_required(VERSION 3.16)
project(MyProject VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra")

set(SOURCES
    main.cpp
    line.hpp line.cpp
    grid.hpp grid.cpp
    tests.cpp
)

add_executable(lines
    ${SOURCES}
)