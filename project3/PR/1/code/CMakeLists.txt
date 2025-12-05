cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "gcc")

project(Dijkstra_Sequence)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

add_executable(main ${SOURCES} main.c)