cmake_minimum_required(VERSION 3.28.3)

project(tsp_dynamic)

add_executable(tsp_dynamic
    src/TSP.cpp
    src/main.cpp
)

target_include_directories(tsp_dynamic PRIVATE include)