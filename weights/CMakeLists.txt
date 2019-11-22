cmake_minimum_required(VERSION 3.10)
project(weights)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(order_weights order_weights.cpp)
target_link_libraries(order_weights ${GTEST_LIBRARIES} pthread)
