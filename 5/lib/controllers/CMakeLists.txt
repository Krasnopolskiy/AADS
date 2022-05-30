file(GLOB SOURCES "impl/*.c")

add_library(controllers STATIC ${SOURCES})

target_link_libraries(controllers models views)
