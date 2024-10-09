# Build the firmware as a shared library for dynamic loading

set(SOURCES
    firmware.c
    rtos_app_hooks.c
    temperature_sensor.c
)

set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(firmware SHARED ${SOURCES})
target_include_directories(firmware PRIVATE ${INCLUDE_DIRS})

target_link_libraries(firmware
    freertos_with_port
    sutsim
)

# Set output directory for firmware shared libraries (to test/sim_artifacts)
set_target_properties(firmware PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${SUTSIM_TEST_DIR}/sim_artifacts
)
