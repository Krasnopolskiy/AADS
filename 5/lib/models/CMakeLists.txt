file(GLOB SOURCES "impl/*.c")

add_library(models STATIC ${SOURCES})
