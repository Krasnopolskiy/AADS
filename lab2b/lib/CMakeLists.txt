file(GLOB COMMON_SOURCES "impl/*.c")
file(GLOB MODE_SOURCES "impl/${MODE}/*.c")

add_library(lib STATIC ${COMMON_SOURCES} ${MODE_SOURCES})
