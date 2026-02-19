add_library(stringLib 
    stringLib.hpp    
    stringLib.cpp
)
# definisanje staticke biblioteke stringLib

target_include_directories(stringLib PUBLIC "$(CMAKE_CURRENT_SOURCE_DIR)")
# gde CMake i kompajler mogu da nadju header fajlove kada se koristi stringLib