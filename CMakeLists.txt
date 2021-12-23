cmake_minimum_required(VERSION 3.18)
project(triomino)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-O3)

add_executable(triomino main.cpp Board.cpp Board.h)
