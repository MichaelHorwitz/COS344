cmake_minimum_required(VERSION 3.26)
project(NewMathLibrary)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(NewMathLibrary
        MathExceptions.h
        Matrix.cpp
        Matrix.h
        Test.cpp
        Vector.cpp
        Vector.h)
