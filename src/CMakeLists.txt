cmake_minimum_required(VERSION 3.28)
project(SudokuValidate)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -pthread")

include_directories(C:/Users/dhruv/CLionProjects/SudokuValidate)

add_executable(nonthreads nonthreads.cpp)
add_executable(openmp openmp.cpp)
add_executable(pthread pthread.cpp)