cmake_minimum_required(VERSION 3.14)
project(Bacon)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
add_executable(Bacon main.cpp Mapa.cpp Mapa.h prglib.h)