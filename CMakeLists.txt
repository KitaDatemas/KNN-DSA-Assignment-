cmake_minimum_required(VERSION 3.27)
project(init)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(init
        kNN.cpp
        kNN.hpp
        main.cpp
        main.hpp
        testFunc.cpp)
