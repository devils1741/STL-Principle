cmake_minimum_required(VERSION 3.20)
project(stlDemo)

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

add_executable(vector ${SOURCE_DIR}/stl_vector.cpp)
add_executable(list ${SOURCE_DIR}/stl_vector.cpp)
