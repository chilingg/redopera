cmake_minimum_required(VERSION 3.1)

project(redopera)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

include_directories(include/redopera)
include_directories(include/redopera/dependent)

ADD_SUBDIRECTORY(src src)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
    ADD_SUBDIRECTORY(test test)
    ADD_SUBDIRECTORY(example example)
endif()
