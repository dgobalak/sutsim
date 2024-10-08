set(SOURCES
    sutsim.c
)

set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(sutsim STATIC ${SOURCES})
target_include_directories(sutsim PUBLIC ${INCLUDE_DIRS})
