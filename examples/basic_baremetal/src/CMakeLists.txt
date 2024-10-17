# Build the firmware as a shared library for dynamic loading

set(SOURCES
    sutsim_hooks.c
)

set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(firmware SHARED ${SOURCES})
target_include_directories(firmware PRIVATE ${INCLUDE_DIRS})

target_link_libraries(firmware
    -Wl,--whole-archive sutsim -Wl,--no-whole-archive
)

set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined")

# Set output directory for firmware shared libraries
set_target_properties(firmware PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${SUTSIM_TEST_DIR}/sim_artifacts
)
