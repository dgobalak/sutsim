# Build the firmware as a shared library for dynamic loading

add_library(firmware SHARED firmware.c)

target_include_directories(firmware PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link firmware with its dependencies (firmware_conn and models)
target_link_libraries(firmware
    freertos_with_port
    sutsim
)

# Set output directory for firmware shared libraries (to test/sim_artifacts)
set_target_properties(firmware PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../test/sim_artifacts
)
