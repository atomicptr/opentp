cmake_minimum_required(VERSION 2.6)
project(opentp)

set(Boost_USE_STATIC_LIBS ON)

if(CMAKE_SYSTEM_NAME STREQUAL Linux)
    add_definitions(-std=c++0x)
endif(CMAKE_SYSTEM_NAME STREQUAL Linux)

add_subdirectory(opentp)
add_subdirectory(example)
