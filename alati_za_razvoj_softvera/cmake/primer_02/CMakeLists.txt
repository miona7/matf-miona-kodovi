cmake_minimum_required(VERSION 3.16)
project(MyProgram VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

                    # uzmi postojecu CMAKE_CXX_FLAGS promenljivu i na kraj dodaj -g ...
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra")
    # cmake promenljiva koja sadrzi opcije za c++ kompilator

add_executable(program
    main.cpp
)