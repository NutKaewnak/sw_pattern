cmake_minimum_required(VERSION 3.3)
project(sw_pattern)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -liconv")

set(SOURCE_FILES main.cpp creader.cpp creader.h)
add_executable(sw_pattern ${SOURCE_FILES})