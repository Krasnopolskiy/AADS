file(GLOB SOURCES "impl/*.c")

add_library(lib STATIC ${SOURCES})
