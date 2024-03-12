cmake_minimum_required(VERSION 3.26)
project(Prac1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Prac1
        main.cpp
        MathExceptions.h
        Matrix.cpp
        Matrix.h
        Vector.cpp
        Vector.h)
