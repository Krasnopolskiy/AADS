file(GLOB SOURCES "impl/${MODE}/*.c")

add_library(models STATIC ${SOURCES})

if (${MODE} STREQUAL "file")
    target_link_libraries(models helpers)
endif ()
