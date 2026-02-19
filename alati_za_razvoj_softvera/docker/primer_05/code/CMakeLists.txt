cmake_minimum_required(VERSION 3.16)
project(MyProgram VERSION 1.0.0)

add_subdirectory(stringLib)
# dodali smo poddirektorijum stringLib, koji sadrzi CMakeLists.txt fajl za izgradnju biblioteke stringLib

add_executable(program 
    src/main.cpp
)
add_executable(test
    stringLib/test.cpp
)

target_link_libraries(program PRIVATE
    stringLib
)
target_link_libraries(test PRIVATE
    stringLib
)
# povezali smo program i test sa bibliotekom stringLib tako da mogu da koriste funkcije definisane u toj biblioteci
# PRIVATE znaci da su zavisnosti vidljive samo unutar cilja program i test a ne i drugim ciljevima koji mogu biti definisani u projektu