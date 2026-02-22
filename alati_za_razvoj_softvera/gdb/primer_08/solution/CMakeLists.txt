cmake_minimum_required(VERSION 3.16)
project(MyProgram VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra")

set(HEADERS
    k_means.hpp
    Point.hpp
    Points.hpp
    RandomEngine.hpp
)

set(SOURCES
    main.cpp
    k_means.cpp
    Point.cpp
    Points.cpp
    RandomEngine.cpp 
    tests.cpp
)

add_executable(k_means
    ${HEADERS}
    ${SOURCES}
)