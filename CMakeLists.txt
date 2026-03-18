cmake_minimum_required(VERSION 3.25.1)
project(OPTIMISATION_COMBINATOIRE LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(OptCombi
    src/main.cpp
)
target_compile_features(OptCombi PRIVATE cxx_std_17)
