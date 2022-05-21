cmake_minimum_required(VERSION 3.0)

project(lab5 VERSION 0.1 LANGUAGES C)

set(EXECUTABLE main)

include_directories(lib)

add_subdirectory(lib/models models)
#add_subdirectory(lib/views views)
#add_subdirectory(lib/controllers controllers)

add_executable(${EXECUTABLE} main.c)

target_link_libraries(${EXECUTABLE} models)
#target_link_libraries(${EXECUTABLE} controllers)
