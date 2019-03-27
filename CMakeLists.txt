cmake_minimum_required(VERSION 3.8)
project(demo)

set(CMAKE_CXX_STANDARD 14)

add_library(demo SHARED library.cpp linearRegression.cpp)