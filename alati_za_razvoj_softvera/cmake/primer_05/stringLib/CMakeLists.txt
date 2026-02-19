# lista header fajlova
set(HEADERS
    inc/stringLib.hpp
)

# lista src fajlova
set(SOURCES
    src/stringLib.cpp
)

add_library(stringLib
    ${HEADERS}
    ${SOURCES}
)

# onaj ko koristi biblioteku stringLib mora da zna gde su header fajlovi
# PUBLIC -> vazi i za stringLib biblioteku i za sve koji je koriste
target_include_directories(stringLib PUBLIC
   "${CMAKE_CURRENT_SOURCE_DIR}/inc"
)

add_executable(runTest
    test/test.cpp
)

target_link_libraries(runTest PRIVATE stringLib)

# dodaje test u CTest sistem
add_test(
    NAME testStringLib # ime testa
    COMMAND runTest # komanda za izvsavanje testa
)