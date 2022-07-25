cmake_minimum_required(VERSION 3.22.0)

set(CMAKE_CXX_COMPILER clang++-12)

project(nav)

add_executable(${PROJECT_NAME} main.cpp main.hpp navigation.cpp navigation.hpp)
