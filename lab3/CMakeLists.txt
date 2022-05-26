cmake_minimum_required(VERSION 3.0)

project(lab3 VERSION 1.0 LANGUAGES C)

set(EXECUTABLE main.out)
set(MODE mem)

if (NOT ${MODE} MATCHES "^(file)|(mem)")
    message(FATAL_ERROR "You have not selected the storage mode")
endif ()

include_directories(lib)

add_executable(${EXECUTABLE} main.c)

add_subdirectory(lib/models models)
add_subdirectory(lib/views views)
add_subdirectory(lib/controllers controllers)

target_link_libraries(${EXECUTABLE} controllers)

install(TARGETS controllers DESTINATION build)
