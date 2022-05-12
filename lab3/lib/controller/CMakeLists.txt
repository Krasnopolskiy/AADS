file(GLOB SOURCES "*.c")

add_library(controller STATIC ${SOURCES})

target_link_libraries(controller models views)
