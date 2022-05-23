file(GLOB SOURCES "impl/*.c")

add_library(handlers STATIC ${SOURCES})
