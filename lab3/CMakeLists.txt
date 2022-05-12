cmake_minimum_required(VERSION 3.0)

project(lab3 VERSION 0.1 LANGUAGES C)

include_directories("${PROJECT_SOURCE_DIR}/lib-default")

set(EXECUTABLE main.out)
set(MODE file)

if (NOT ${MODE} MATCHES "^(file)|(mem)")
    message(FATAL_ERROR "You have not selected the storage mode")
endif ()

add_executable(${EXECUTABLE} main.c)

add_subdirectory(lib/models models)
add_subdirectory(lib/views views)
add_subdirectory(lib/handlers handlers)
add_subdirectory(lib/controller controller)
add_subdirectory(lib/application application)

target_link_libraries(${EXECUTABLE} application)

install(TARGETS application DESTINATION build)
