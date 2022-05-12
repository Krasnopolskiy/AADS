file(GLOB SOURCES "*.c")

add_library(views STATIC ${SOURCES})

target_link_libraries(views models)
