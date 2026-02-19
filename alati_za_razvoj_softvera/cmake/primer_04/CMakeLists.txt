cmake_minimum_required(VERSION 3.16)
project(MyProgram VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

# STATIC: staticka biblioteka -> linkuje se pre izvrsavanja, kod se bukvalno nalepi
add_library(stringLib
    stringLib.hpp
    stringLib.cpp
)

add_executable(test
    test.cpp
)

# PRIVATE -> samo test koristi biblioteku
target_link_libraries(test PRIVATE stringLib)