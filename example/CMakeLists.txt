cmake_minimum_required(VERSION 3.1)

include_directories(${CMAKE_SOURCE_DIR}/include/redopera)

link_directories(${CMAKE_BINARY_DIR})

add_executable(triangle triangle.cpp)
target_link_libraries(triangle redopera)

add_executable(plane plane.cpp)
target_link_libraries(plane redopera)

add_executable(texts texts.cpp)
target_link_libraries(texts redopera)

add_executable(particle particle.cpp)
target_link_libraries(particle redopera)

