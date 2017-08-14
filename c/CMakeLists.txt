cmake_minimum_required(VERSION 3.7.1)

project(collections)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_C_STANDARD 99)

include(CTest)

add_subdirectory(tharness)
add_subdirectory(linkedlist)

add_executable(library library.c)

target_link_libraries(library slinkedlist)