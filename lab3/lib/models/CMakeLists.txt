file(GLOB SOURCES "impl/${MODE}/*.c")

add_library(models STATIC ${SOURCES})

target_link_libraries(models handlers)
