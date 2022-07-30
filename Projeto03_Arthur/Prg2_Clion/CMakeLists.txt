cmake_minimum_required(VERSION 3.14)
project(Prg2_demo)

set(CMAKE_CXX_STANDARD 11)
include_directories(.)

add_executable(Prg2_demo main.cpp prglib.h Projeto03.cpp Projeto03.h)