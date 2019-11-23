cmake_minimum_required(VERSION 3.5)

project (fib_calculator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(fib_calculator Fibonnacci.cpp)