cmake_minimum_required(VERSION 3.9.1)

set(CMAKE_CXX_STANDARD 17)

project(PcentriVNS)

add_executable(pcentri_vns 
main.cpp
algorithm.cpp
algorithm.hpp
structures.cpp
structures.hpp
)
target_include_directories(pcentri_vns PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")