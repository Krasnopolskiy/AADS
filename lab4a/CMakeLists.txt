cmake_minimum_required(VERSION 3.0)

project(lab4a VERSION 1.0 LANGUAGES C)

set(EXECUTABLE main)

file(COPY assets/data.bin DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include_directories(lib)

add_subdirectory(lib/models models)
add_subdirectory(lib/views views)
add_subdirectory(lib/controllers controllers)

add_executable(${EXECUTABLE} main.c)

target_link_libraries(${EXECUTABLE} controllers)
