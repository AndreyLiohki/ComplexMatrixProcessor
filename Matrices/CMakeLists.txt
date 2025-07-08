cmake_minimum_required(VERSION 3.15)
project(MatrixAlgebraProject)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(core)
add_subdirectory(algebra)
add_subdirectory(decompositions)

add_executable(MatrixApp  main.cpp)
target_link_libraries(MatrixApp 
    core
    algebra
    decompositions
)
