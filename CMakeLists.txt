cmake_minimum_required(VERSION 3.21)
project(Japanese_Crosswords_Solver)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(Japanese_Crosswords_Solver main.cpp Nonogram.h Nonogram.cpp BMPWriter.cpp BMPWriter.h)
