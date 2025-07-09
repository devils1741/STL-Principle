cmake_minimum_required(VERSION 3.20)
project(stlDemo)

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

# add_executable(vector ${SOURCE_DIR}/stl_vector.cpp)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(vector ${SOURCE_DIR}/ut/ut_stl_vector.cpp)
target_link_libraries(vector ${GTEST_LIBRARIES})

add_executable(list ${SOURCE_DIR}/ut/ut_stl_list.cpp)
target_link_libraries(list ${GTEST_LIBRARIES})
