cmake_minimum_required(VERSION 3.12)
project(Dijkstra_avec_Tas_Required_Files_)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Dijkstra_avec_Tas_Required_Files_
        dijkstra.cpp
        dijkstra.h
        cmake-build-debug/entree1.txt
        cmake-build-debug/entree2.txt
        main.cpp)
