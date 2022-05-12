file(GLOB SOURCES "${MODE}/*.c")

add_library(models STATIC ${SOURCES})

target_link_libraries(models handlers)
