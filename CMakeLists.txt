cmake_minimum_required(VERSION 3.25.1)
project(OPTIMISATION_COMBINATOIRE LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(OptCombi
    src/main.cpp
    src/utils.cpp

    src/graphs/adjmat.cpp
    src/graphs/graph.cpp
    src/graphs/graphAdjMatrix.cpp
    src/graphs/graphListAdj.cpp
    src/graphs/weightedgraphDefs.cpp

    src/criteria/degree.cpp
    src/criteria/connexeGraphSize.cpp

    src/neighborhood/neighborhood.cpp
    src/neighborhood/n1.cpp
    src/neighborhood/n2.cpp

    src/hill_climb/hill_climb.cpp
    
    src/gradient/gradient.cpp
)
target_compile_features(OptCombi PRIVATE cxx_std_17)
