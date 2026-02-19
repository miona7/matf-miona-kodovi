cmake_minimum_required(VERSION 3.16)
project(MyProject VERSION 1.0.0)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra --coverage")

add_subdirectory(stringLib)

add_executable(program
    src/main.cpp
)
add_executable(runTest
    stringLib/test/test.cpp
)

add_test(
    NAME testStringLib 
    COMMAND runTest
)

if(CMAKE_COMPILER_IS_GNUCXX)
    include(CodeCoverage)
    SETUP_TARGET_FOR_COVERAGE_LCOV(
        NAME coverage 
        EXECUTABLE runTest
    )
endif()

target_link_libraries(program PRIVATE stringLib)
target_link_libraries(runTest PRIVATE stringLib)