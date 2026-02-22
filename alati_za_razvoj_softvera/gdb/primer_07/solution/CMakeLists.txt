cmake_minimum_required(VERSION 3.16)
project(MyProgram VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra")

set(SOURCES
    main.cpp
    text.hpp text.cpp
    test.cpp
)

add_executable(text
    ${SOURCES}
)