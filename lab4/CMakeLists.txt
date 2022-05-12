cmake_minimum_required(VERSION 3.0)

project(lab4 VERSION 0.1 LANGUAGES C)

set(EXECUTABLE main)
set(MODE balanced)

if (NOT ${MODE} MATCHES "^(default)|(balanced)")
    message(FATAL_ERROR "You have not selected the tree mode")
endif ()

include_directories(lib-${MODE})

add_subdirectory(lib-${MODE}/models models)
add_subdirectory(lib-${MODE}/views views)
add_subdirectory(lib-${MODE}/controllers controllers)

add_executable(${EXECUTABLE} main.c)

target_link_libraries(${EXECUTABLE} controllers)
