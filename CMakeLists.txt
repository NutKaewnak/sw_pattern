cmake_minimum_required(VERSION 3.3)
project(sw_pattern)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_library(creader STATIC reader.cpp)
add_executable(sw_pattern ${SOURCE_FILES})
target_link_libraries(sw_pattern creader)