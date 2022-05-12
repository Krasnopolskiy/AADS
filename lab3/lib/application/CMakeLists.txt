file(GLOB SOURCES "${MODE}/*.c")

add_library(application STATIC ${SOURCES})

target_link_libraries(application controller)
