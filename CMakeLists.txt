cmake_minimum_required(VERSION 3.22)

project(Graph)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SRC_LIST main.cpp graph.cpp graph_utils.cpp graph_algorithm.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST})