cmake_minimum_required(VERSION 3.21)
project(GridMap)

set(CMAKE_CXX_STANDARD 14)

add_executable(GridMap main.cpp GridMap.cpp GridMap.h Types.h Utils.cpp Utils.h CSVReader/CSVReader.h CSVReader/CSVReader.cpp)
