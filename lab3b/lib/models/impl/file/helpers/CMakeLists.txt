file(GLOB SOURCES "impl/*.c")

add_library(helpers STATIC ${SOURCES})
