cmake_minimum_required(VERSION 3.0)

project(lab1 VERSION 1.0 LANGUAGES C)

set(EXECUTABLE main)

include_directories(lib)

add_subdirectory(lib lib)

add_executable(${EXECUTABLE} main.c)

target_link_libraries(${EXECUTABLE} lib)
