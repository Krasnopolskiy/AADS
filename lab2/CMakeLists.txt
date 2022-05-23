cmake_minimum_required(VERSION 3.0)

project(lab2 VERSION 1.0 LANGUAGES C)

set(EXECUTABLE main)
set(MODE vector)

if (NOT ${MODE} MATCHES "^(vector)|(list)")
    message(FATAL_ERROR "Stack mode is invalid")
endif ()

include_directories(lib)

add_subdirectory(lib lib)

add_executable(${EXECUTABLE} main.c)

target_link_libraries(${EXECUTABLE} lib)
